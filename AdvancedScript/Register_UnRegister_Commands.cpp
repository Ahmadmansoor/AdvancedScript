#include "Register_UnRegister_Commands.h"
#include "MainForm.h"
#include "LogTemplate.h"
#include "HelperFunctions.h"
#include "Parser.h"
#include "LogWindow.h"
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
bool LogOff_ = false;

//Managed types cannot be declared in an unmanaged context.
//Since.NET does not support global variables, attempting to declare a global variable
//with a managed type results in that error.You have to declare managed types members of
//a managed class or managed structure, not as globals.You would also get this error if you
//attempted to declare a member of type TcpClient in an native class (i.e.a class definition
//that does not include the "ref" keyword).You can only use native types as globals.
//https://stackoverflow.com/questions/11419459/c-declaring-a-managed-variable-in-a-native-code
ref class ManagedGlobals {
public:
	static Generic::List<AdvancedScript::LogTemplate::TemplateClass^>^ TemplateClassList_ = gcnew Generic::List<AdvancedScript::LogTemplate::TemplateClass^>;

};

System::Void TemplateListAdd(String^ TemplateName, String^ templatedata) {
	AdvancedScript::LogTemplate::TemplateClass^ TemplateClass_ = gcnew AdvancedScript::LogTemplate::TemplateClass(TemplateName, templatedata);
	ManagedGlobals::TemplateClassList_->Add(TemplateClass_);
}
System::Void LoadTemplateFiles_() {
	ManagedGlobals::TemplateClassList_->Clear();
	if (IO::Directory::Exists(Application::StartupPath + "\\LogTemplate")) {
		for each (String^ file_ in IO::Directory::GetFiles(Application::StartupPath + "\\LogTemplate"))
		{
			String^ templatedata = IO::File::ReadAllText(file_);
			String^ templateName = IO::Path::GetFileName(file_);
			TemplateListAdd(templateName, templatedata);
		}
	}
}
bool  GetTemplate(String^ TemplateName, AdvancedScript::LogTemplate::TemplateClass^% TemplateClassFound) {
	for (size_t i = 0; i < ManagedGlobals::TemplateClassList_->Count; i++)
	{
		if (ManagedGlobals::TemplateClassList_[i]->TemplateName == TemplateName) {
			TemplateClassFound = ManagedGlobals::TemplateClassList_[i];
			return true;
		}
	}
	return false;
}
////////////////////////////////////////////////////////  WE NEED to fill this List of Template's at fist load
void RegisterCommands(PLUG_INITSTRUCT* initStruct)
{
	_plugin_logprintf("[AdvancedScript] pluginHandle: %d\n", pluginHandle);


	if (!_plugin_registercommand(pluginHandle, "AdvancedScript", cbMainForm, false))
		_plugin_logputs("[AdvancedScript] error registering the \AdvancedScript\ command!");

	if (!_plugin_registercommand(pluginHandle, "LogJustAtBP", cbLogJustAtBP, false))
		_plugin_logputs("[AdvancedScript] error registering the \AdvancedScript\ command!");

	if (!_plugin_registercommand(pluginHandle, "test_", test, false))
		_plugin_logputs("[AdvancedScript] error registering the \AdvancedScript\ command!");

	if (!_plugin_registercommand(pluginHandle, "LogTemplateManager", LogTemplateManager, false))
		_plugin_logputs("[AdvancedScript] error registering the \AdvancedScript\ command!");

	if (!_plugin_registercommand(pluginHandle, "logx", logx, false))
		_plugin_logputs("[AdvancedScript] error registering the \AdvancedScript\ command!");

	if (!_plugin_registercommand(pluginHandle, "logx_window", logx_window, false))
		_plugin_logputs("[AdvancedScript] error registering the \AdvancedScript\ command!");

	//LoadTemplateFiles();
		
}
////////////////////////////////////////////////////////////////////////////////////////////////////
static bool test(int argc, char* argv[]) {
	if (argc != 2) { _plugin_logprintf("worng arguments"); return false; }
	String^ temp = charPTR2String(argv[0]);
	temp = temp->Substring(temp->IndexOf(" ") + 1, temp->Length - (temp->IndexOf(" ") + 1));
	String^ xc = "Rax = 0 " + Environment::NewLine + "test work ";
	int c = ManagedGlobals::TemplateClassList_->Count;
	//xc->Replace("0", temp);
	//static AdvancedScript::LogTemplate::TemplateClassList^ g;
	_plugin_logprintf(Str2ConstChar(xc));
}
////////////////////////////////////////////////////////////////////////////////////////////////////
static void ShowDialog_IATFixer()
{
	AdvancedScript::MainForm IATFixer;
	IATFixer.ShowDialog();
}

static bool cbMainForm(int argc, char* argv[])
{
	_plugin_logputs("[MainForm] Loading Form!");
	///////////////////////////////////////////////////////////////////////////////////////
	// this will keep form activate and x64dbg unable to do it's work by excuted commands 
	//ScriptS::IATFixer IATFixer;
	//IATFixer.ShowDialog();
	///////////////////////////////////////////////////////////////////////////////////////

	// we used this (New Thread) to Create our Form in new Thread so we able to comunicated with x64dbg
	// and be able to send command let go to address or do some  other commands 
	System::Threading::Thread^ thread_ = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(&ShowDialog_IATFixer));
	thread_->Start();

	return true;
}

static bool cbLogJustAtBP(int argc, char* argv[]) {
	if (argc != 2) { _plugin_logprintf("worng arguments"); return false; }
	String^ temp = charPTR2String(argv[0]);
	temp = temp->Substring(temp->IndexOf(" ") + 1, temp->Length - (temp->IndexOf(" ") + 1));
	LogOff_ = Str2bool(temp);
	if (LogOff_) {
		GuiDisableLog();
	}
	else {
		GuiEnableLog();
	}

	return true;
}

static void ShowDialog_TemplateManager()
{
	AdvancedScript::LogTemplate LogTemplate;
	LogTemplate.ShowDialog();
}
static bool LogTemplateManager(int argc, char* argv[]) {
	if (argc > 1) { _plugin_logprintf("worng arguments"); return false; }
	String^ temp = charPTR2String(argv[0]);
	Threading::Thread^ thread_ = gcnew Threading::Thread(gcnew Threading::ThreadStart(&ShowDialog_TemplateManager));
	thread_->Start();
	return true;
}

static void ShowDialog_LogWindow()
{
	AdvancedScript::LogWindow LogWindow;
	LogWindow.ShowDialog();
}
static bool logx_window(int argc, char* argv[]) {
	if (argc > 1) { _plugin_logprintf("worng arguments"); return false; }
	String^ temp = charPTR2String(argv[0]);
	Threading::Thread^ thread_ = gcnew Threading::Thread(gcnew Threading::ThreadStart(&ShowDialog_LogWindow));
	thread_->Start();
	return true;
}

static bool logx(int argc, char* argv[]) {
	Generic::List<String^>^ arguments;
	AdvancedScript::LogTemplate::TemplateClass^ TemplateClassFound;
	GetArg(charPTR2String(argv[0]), arguments); // this function use by refrence so the list will fill direct

	if (arguments->Count < 1) { _plugin_logprintf("worng arguments"); return false; }
	if (GetTemplate(arguments[0], TemplateClassFound)) {
		////////////////////////////////
		//const char* format; size_t resultSize; char* result = new char[MAX_STRING_SIZE];
		//format = (Str2ConstChar(TemplateClassFound->TemplateData));
		//DbgFunctions is a way to get any Functions vaule in the enum of it 
		// here we get the String Format In a line
		//DbgFunctions()->StringFormatInline(format, MAX_STRING_SIZE, result);
		//_plugin_logprintf(result);
		////////////////////////////////
		AdvancedScript::LogWindow::TheInstance->RTB1_Log(TemplateClassFound->TemplateData);
		_plugin_logprintf(StringFormatInline_(TemplateClassFound->TemplateData));
	}
	return true;
}

static bool logTrace(int argc, char* argv[]) {


}