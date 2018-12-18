#include "Register_UnRegister_Commands.h"
#include "MainForm.h"
#include "LogTemplate.h"
#include "HelperFunctions.h"
#include "Parser.h"
#include "LogWindow.h"
#include "ScriptFun.h"
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;


bool LogOff_ = false;
bool log2LogWindowAtBP = false;
bool LogTraceOn = false;
bool cx = false;



//Managed types cannot be declared in an unmanaged context.
//Since.NET does not support global variables, attempting to declare a global variable
//with a managed type results in that error.You have to declare managed types members of
//a managed class or managed structure, not as globals.You would also get this error if you
//attempted to declare a member of type TcpClient in an native class (i.e.a class definition
//that does not include the "ref" keyword).You can only use native types as globals.
//https://stackoverflow.com/questions/11419459/c-declaring-a-managed-variable-in-a-native-code
static ref class ManagedGlobals {
public:
	static Generic::List<AdvancedScript::LogTemplate::TemplateClass^>^ TemplateClassList_ = gcnew Generic::List<AdvancedScript::LogTemplate::TemplateClass^>;
	static String^ TraceFilePath = "";
	static String^ TraceFilename = "";
	static String^ TraceTemplate = "";
	static String^ logxTraceArg2 = ""; // we used we need to pass it to callback Show_DialogSave because pass parameter is a little complex :(
	static String^ temp = "";
};

const char* TraceFile_ = new char[MAX_STRING_SIZE]; // to get Trace file Path+name
const char* TemplateData_ = new char[MAX_STRING_SIZE]; // to get Template Data 


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
	if (ManagedGlobals::TemplateClassList_->Count == 0) {
		LoadTemplateFiles_();
	}
	for (size_t i = 0; i < ManagedGlobals::TemplateClassList_->Count; i++)
	{
		if (ManagedGlobals::TemplateClassList_[i]->TemplateName->ToLower() == TemplateName->ToLower()) {
			TemplateClassFound = ManagedGlobals::TemplateClassList_[i];
			return true;
		}
	}
	return false;
}
////////////////////////////////////////////////////////  WE NEED to fill this List of Template's at fist load
void RegisterCommands(PLUG_INITSTRUCT* initStruct)
{
	_plugin_logprintf("[AdvancedScript 1.8] || Coded By AhmadMansoor /exetools ");
	_plugin_logprint(Str2ConstChar(Environment::NewLine));

	/*if (!_plugin_registercommand(pluginHandle, "AdvancedScript", cbMainForm, false))
		_plugin_logputs("[AdvancedScript] error registering the \AdvancedScript\ command!");*/
	if (!_plugin_registercommand(pluginHandle, "test_", test, false))
		_plugin_logputs("[AdvancedScript] error registering the \AdvancedScript\ command!");

	/////////Logx....
	if (!_plugin_registercommand(pluginHandle, "LogxJustAtBP", cbLogxJustAtBP, false))
		_plugin_logputs("[AdvancedScript] error registering the \AdvancedScript\ command!");

	if (!_plugin_registercommand(pluginHandle, "LogxTemplateManager", LogxTemplateManager, false))
		_plugin_logputs("[AdvancedScript] error registering the \AdvancedScript\ command!");

	if (!_plugin_registercommand(pluginHandle, "logxwindow", logx_window, false))
		_plugin_logputs("[AdvancedScript] error registering the \AdvancedScript\ command!");

	if (!_plugin_registercommand(pluginHandle, "logx", logx, false))
		_plugin_logputs("[AdvancedScript] error registering the \AdvancedScript\ command!");

	if (!_plugin_registercommand(pluginHandle, "logxTrace", logxTrace, false))
		_plugin_logputs("[AdvancedScript] error registering the \AdvancedScript\ command!");
	/////////Logx....//////////
	if (!_plugin_registercommand(pluginHandle, "StrCompx", StrCompx, false))
		_plugin_logputs("[AdvancedScript] error registering the \AdvancedScript\ command!");

	/////////Script Commands....//////////
	if (!_plugin_registercommand(pluginHandle, "Varx", Varx, false))
		_plugin_logputs("[AdvancedScript] error registering the \AdvancedScript\ command!");

	if (!_plugin_registercommand(pluginHandle, "GetVarx", GetVarx, false))
		_plugin_logputs("[AdvancedScript] error registering the \AdvancedScript\ command!");
	if (!_plugin_registercommand(pluginHandle, "PrintVarx", GetVarx, false))
		_plugin_logputs("[AdvancedScript] error registering the \AdvancedScript\ command!");


	if (!_plugin_registercommand(pluginHandle, "SetVarx", SetVarx, false))
		_plugin_logputs("[AdvancedScript] error registering the \AdvancedScript\ command!");
	if (!_plugin_registercommand(pluginHandle, "MovVarx", SetVarx, false))
		_plugin_logputs("[AdvancedScript] error registering the \AdvancedScript\ command!");

	if (!_plugin_registercommand(pluginHandle, "findallmemx", findallmemx, false))
		_plugin_logputs("[AdvancedScript] error registering the \AdvancedScript\ command!");

}
////////////////////////////////////////////////////////////////////////////////////////////////////
static bool test(int argc, char* argv[]) {
	//Generic::List<String^>^ arguments;
	//GetArg(charPTR2String(argv[0]), arguments); // this function use by refrence so the list will fill direct	
	//switch (arguments->Count)
	//{
	//case 1: {
	//	char* text_ = new char[MAX_STRING_SIZE];
	//	//DbgGetStringAt(Script::Register::Get(Script::Register::RCX), text_);
	//	_plugin_logprint(text_);
	//	break;
	//}
	//case 2: {
	//	break;
	//}
	//default:
	//	_plugin_logprintf("worng arguments");
	//	return false;
	//}
	//DbgScriptCmdExec("{jmp res}");


	// for script goto line
	//DbgScriptSetIp(3);
	
	SELECTIONDATA sel;
	GuiSelectionGet(GUI_DUMP, &sel);
	unsigned char* x = new unsigned char[255];
	DbgMemRead(sel.start,x,16);
	const char f = x[5];
	return true;
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

//cbLogxJustAtBP arg1,arg2 
//arg1=true/false-on/off-1/0 Enable to log at BP at x64dbg log window
//arg1=true/false-on/off-1/0 Enable to log at BP at AdvancedScript log window << this one is optional
static bool cbLogxJustAtBP(int argc, char* argv[]) {
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments); // this function use by refrence so the list will fill direct	
	switch (arguments->Count)
	{
	case 1: {
		LogOff_ = Str2bool(arguments[0]);
		if (LogOff_) {
			GuiDisableLog();
		}
		else { GuiEnableLog(); }
		break;
	}
	case 2: {
		LogOff_ = Str2bool(arguments[0]);
		if (LogOff_) {
			GuiDisableLog();
		}
		else { GuiEnableLog(); }
		log2LogWindowAtBP = Str2bool(arguments[1]);
		break;
	}
	default:
		_plugin_logprintf("worng arguments");
		return false;
	}
	return true;
}

static void ShowDialog_TemplateManager()
{
	AdvancedScript::LogTemplate LogTemplate;
	LogTemplate.ShowDialog();
}
static bool LogxTemplateManager(int argc, char* argv[]) {
	if (argc > 1) { _plugin_logprintf("worng arguments"); return false; }
	String^ temp = charPTR2String(argv[0]);
	Threading::Thread^ thread_ = gcnew Threading::Thread(gcnew Threading::ThreadStart(&ShowDialog_TemplateManager));
	thread_->Start();
	return true;
}

static void ShowDialog_LogWindow()
{
	AdvancedScript::LogWindow::LogWindow_->ShowDialog();
}
static bool logx_window(int argc, char* argv[]) {
	if (argc > 1) { _plugin_logprintf("worng arguments"); return false; }
	String^ temp = charPTR2String(argv[0]);
	Threading::Thread^ thread_ = gcnew Threading::Thread(gcnew Threading::ThreadStart(&ShowDialog_LogWindow));
	thread_->Start();
	return true;
}

static bool logx(int argc, char* argv[]) {  // it need agument Template name like this <<logx Template0>>
	Generic::List<String^>^ arguments;
	AdvancedScript::LogTemplate::TemplateClass^ TemplateClassFound;
	GetArg(charPTR2String(argv[0]), arguments); // this function use by refrence so the list will fill direct
	switch ((arguments->Count))
	{
	case 1: {
		if (GetTemplate(arguments[0], TemplateClassFound)) {
			AdvancedScript::LogWindow::LogWindow_->Log_Str = AdvancedScript::LogWindow::Log_Str + Environment::NewLine + charPTR2String(StringFormatInline_(TemplateClassFound->TemplateData));
			if (AdvancedScript::LogWindow::LogWindow_->FormLoaded) {
				AdvancedScript::LogWindow::LogWindow_->RTBAppendText(charPTR2String(StringFormatInline_((TemplateClassFound->TemplateData))));
			}
			_plugin_logprintf(StringFormatInline_(TemplateClassFound->TemplateData));
		}
		else {
			CheckexcutedCmd(arguments[0]);
		}
		break;
	}	
	default:
		_plugin_logprintf("worng arguments");
		return false;
	}	


	return true;
}

static void Show_DialogSave() {
	AdvancedScript::LogTemplate::TemplateClass^ TemplateClassFound;
	FolderBrowserDialog^ FolderBrowserDialog_ = gcnew FolderBrowserDialog();
	FolderBrowserDialog_->ShowDialog();
	ManagedGlobals::TraceFilePath = FolderBrowserDialog_->SelectedPath;
	if (ManagedGlobals::TraceFilePath == "") {
		Script::Gui::Message("worng file,Trcer is off now");
		LogTraceOn = false;
		_plugin_logprintf("Trcer is off now");
	}
	if (!GetTemplate(ManagedGlobals::logxTraceArg2, TemplateClassFound)) {
		Script::Gui::Message("No Template with this name");
		LogTraceOn = false;
		_plugin_logprintf("Trcer is off now");
		ManagedGlobals::TraceFilePath = "";
	}
	else {
		//ManagedGlobals::TraceTemplate = TemplateClassFound->TemplateName;
		ManagedGlobals::TraceTemplate = TemplateClassFound->TemplateData;
	}
}
static bool logxTrace(int argc, char* argv[]) { //logxTrace on/off,TemplateName,TraceFilename
	Generic::List<String^>^ arguments;
	AdvancedScript::LogTemplate::TemplateClass^ TemplateClassFound;

	GetArg(charPTR2String(argv[0]), arguments); // this function use by refrence so the list will fill direct

	//if ((arguments->Count != 2) && (arguments->Count != 1) && (arguments->Count != 3)) { _plugin_logprintf("worng arguments"); return false; }
	if ((arguments->Count != 3) && (arguments->Count != 1)) { _plugin_logprintf("worng arguments"); return false; }
	if (arguments[0] != "on" && arguments[0] != "off")
	{
		_plugin_logprintf("worng arguments on/off"); return false;
	}
	if (arguments[0] == "on") {
		if (!IO::Directory::Exists(Application::StartupPath + "\\LogTrace")) {
			IO::Directory::CreateDirectory(Application::StartupPath + "\\LogTrace");
		}
		if (!GetTemplate(arguments[1], TemplateClassFound)) {
			LogTraceOn = false;
			_plugin_logprintf("worng Template name, Trcer is off now");
			return false;
		}
		else {
			TemplateData_ = Str2ConstChar(TemplateClassFound->TemplateData);
		}
		_plugin_logprintf("Trcer is on now");
		LogTraceOn = true;
		TraceFile_ = Str2ConstChar(Application::StartupPath + "\\LogTrace\\" + arguments[2] + ".txt");
	}
	else if (arguments[0] == "off") {
		LogTraceOn = false;
		_plugin_logprintf("Trcer is off now");
		return false;
	}


	// we will save direct on the x64dbg folder 
	/*if ((arguments->Count != 2) && (arguments->Count != 1) && (arguments->Count != 3)) { _plugin_logprintf("worng arguments"); return false; }
	if (arguments[0] == "on") {
		LogTraceOn = true;
		_plugin_logprintf("Trcer is on now");
		//here we will ask the user where to save
		Threading::Thread^ thread = gcnew Threading::Thread(gcnew Threading::ThreadStart(&Show_DialogSave));
		thread->SetApartmentState(Threading::ApartmentState::STA);
		thread->Start();
	}else if (arguments[0] == "off") {
		LogTraceOn = false;
		_plugin_logprintf("Trcer is off now");
		ManagedGlobals::TraceFilePath = "";
	}
	ManagedGlobals::logxTraceArg2 = arguments[1];
	ManagedGlobals::TraceFilename = arguments[2];*/
	return true;
}


static bool StrCompx(int argc, char* argv[]) {
	ManagedGlobals::temp = CharArr2Str(argv[0]);
	Threading::Thread^ x = gcnew Threading::Thread(gcnew Threading::ThreadStart(&StrComp_BP));
	x->Start();
	GuiUpdateCallStack();
	return true;
}
//Conditional breakpoint compare strings
// StrCompx resume(true/false), logTemplate , Address , UserString2Compare
static void StrComp_BP() {
	Generic::List<String^>^ arguments;
	AdvancedScript::LogTemplate::TemplateClass^ TemplateClassFound;
	GetArg(ManagedGlobals::temp, arguments); // this function use by refrence so the list will fill direct	
	if (!GetTemplate(arguments[1], TemplateClassFound)) {
		LogTraceOn = false;
		_plugin_logprintf("worng Template name");
		return;
	}
	switch ((arguments->Count))
	{
	case 4: {
		String^ addr_temp = StringFormatInline_Str(arguments[2]);
		duint addr = Hex2duint(addr_temp);  /// the address of String in the memory targed which need to comapre with 
		if (addr == -1) {
			_plugin_logprintf(Str2ConstChar("can't Getting Address!! maybe you forget { , because it should follow x64dbg string format "));
			DbgCmdExec("run");
			return;
		}

		String^ Target_Str2Compare;
		//Application::DoEvents();
		Threading::Thread::Sleep(1000);
		//Application::DoEvents();

		char* Str2Compare_ = new char[MAX_STRING_SIZE];
		if (DbgGetStringAt(addr, Str2Compare_)) {
			Target_Str2Compare = CharArr2Str(Str2Compare_);
		}
		else {
			_plugin_logprintf(Str2ConstChar("Can't read the string at this address: " + duint2Hex(addr)));
			DbgCmdExec("run");
			return;
		}

		_plugin_logprintf(Str2ConstChar(Target_Str2Compare));

		String^ UserStr = arguments[3];
		if (!Target_Str2Compare->ToLower()->Trim()->Contains(UserStr->ToLower()->Trim())) {
			_plugin_logprintf(Str2ConstChar(Target_Str2Compare));
			DbgCmdExec("run");
		}
		else {
			if (Str2bool(arguments[0])) {  /// resume runing after hit the BP
				DbgCmdExecDirect(Str2ConstChar("logx " + TemplateClassFound->TemplateName));
				DbgCmdExec("run"); // we use this command because (Script::Debug::Run();) make starnge behavier 
				// as it run in one thread so no command can respond later
			}
			else {
				DbgCmdExecDirect(Str2ConstChar("logx " + TemplateClassFound->TemplateName));
			}
		}
		break;
	}
	default:
		_plugin_logprintf("worng arguments");
		return;
		break;
	}
	return;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// Register Script commands 

static bool Varx(int argc, char* argv[]) { //Varx_(String^ vartype, String^ varname, String^ varvalue="")
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments); // this function use by refrence so the list will fill direct	

	switch ((arguments->Count))
	{
	case 2: {
		Varx_(arguments[0], arguments[1]); // varvalue will make it ""
		break;
	}
	case 3: {
		Varx_(arguments[0], arguments[1], arguments[2]);
		break;
	}
	default:
		_plugin_logprintf("worng arguments");
		break;
	}
	return true;
}

static bool GetVarx(int argc, char* argv[]) { //GetVarx_(String^ varname,int index)
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments); // this function use by refrence so the list will fill direct	

	switch ((arguments->Count))
	{
	case 1: {  // case the var is int or str so the value at index=0
		VarPara_temp^ x = GetVarx_(arguments[0], 0);
		if (x->varname != "")
			_plugin_logprintf(Str2ConstChar(Environment::NewLine + x->varname + "= " + x->varvalue));
		break;
	}
	case 2: { // case the var is Array so we need the index of this array 
		String^ arguments1 = argumentValue(arguments[1]);
		if (Information::IsNumeric(arguments1)) {
			VarPara_temp^ x = GetVarx_(arguments[0], Str2Int(arguments1));
			if (x->varname != "")
				_plugin_logprintf(Str2ConstChar(Environment::NewLine + x->varname + "= " + x->varvalue));
		}
		else {
			_plugin_logprintf(Str2ConstChar(Environment::NewLine + arguments[1] + " :This value is wrong"));
		}
		break;
	}
	default:
		_plugin_logprintf("worng arguments");
		break;
	}
	return true;
}


static bool SetVarx(int argc, char* argv[]) {			//SetVarx_(String^ varname, int index_,String^ value_)
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments); // this function use by refrence so the list will fill direct	

	switch ((arguments->Count))
	{
	case 2: {  // case the var is int or str so the value at index=0
		SetVarx_(arguments[0], 0, argumentValue(arguments[1]));
		break;
	}
	case 3: { // case the var is Array so we need the index of this array 
		if (Information::IsNumeric(arguments[1])) {
			SetVarx_(arguments[0], Str2Int(arguments[1]), arguments[2]);
		}
		else {
			String^ temp = argumentValue(arguments[1]);
			if (Information::IsNumeric(temp)) {
				SetVarx_(arguments[0], 0, temp);
			}
			else {
				_plugin_logprintf(Str2ConstChar(Environment::NewLine + arguments[1] + " :This value is wrong"));
			}
		}
		break;
	}
	default:
		_plugin_logprintf("worng arguments");
		break;
	}
	return true;
}

static bool findallmemx(int argc, char* argv[]) { // findallmemx(String^ base_, String^ Searchvalue_,String^ Size_) 
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments); // this function use by refrence so the list will fill direct	
	
	switch ((arguments->Count))
	{
	case 2: {
		String^ cmd = findallmemx_(arguments[0], arguments[1]);
		DbgCmdExecDirect(Str2ConstChar(cmd));
		return true;
	}
	case 3: {
		String^ cmd = findallmemx_(arguments[0], arguments[1], arguments[2]);
		DbgCmdExecDirect(Str2ConstChar(cmd));
		return true;
	}
	default:
		_plugin_logprintf("worng arguments");
		break;
	}
	return false;
}