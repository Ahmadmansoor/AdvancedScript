#include "Register_UnRegister_Commands.h"
#include "LogTemplate.h"
#include "HelperFunctions.h"
#include "Parser.h"
#include "LogWindow.h"
#include "ScriptFun.h"
#include "MainForm.h"

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
ref class ManagedGlobals {
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
	for (int i = 0; i < ManagedGlobals::TemplateClassList_->Count; i++)
	{
		if (ManagedGlobals::TemplateClassList_[i]->TemplateName->ToLower() == TemplateName->ToLower()) {
			TemplateClassFound = ManagedGlobals::TemplateClassList_[i];
			return true;
		}
	}
	return false;
}
void registerCommand(const char* command, CBPLUGINCOMMAND cbCommand, bool debugonly)
{
	if (!_plugin_registercommand(pluginHandle, command, cbCommand, debugonly))
		_plugin_logprintf("[AdvancedScript] error registering the \"%s\" command!\n", command);
}
////////////////////////////////////////////////////////  WE NEED to fill this List of Template's at fist load
void RegisterCommands(PLUG_INITSTRUCT* initStruct)
{
	_plugin_logputs(Str2ConstChar(Environment::NewLine + "[AdvancedScript 2.8 ] || Coded By AhmadMansoor /exetools "));
	_plugin_logputs(Str2ConstChar(Environment::NewLine));

	registerCommand("Scriptw", cbMainForm, false);
	registerCommand("test_", test, false);

	/////////Logx....
	registerCommand("LogxJustAtBP", cbLogxJustAtBP, true);

	registerCommand("LogxTemplateManager", LogxTemplateManager, false);

	registerCommand("logxwindow", logx_window, false);

	registerCommand("logx", logx, false);

	registerCommand("logxTrace", logxTrace, false);
	/////////Logx....//////////
	registerCommand("StrCompx", StrCompx, false);

	/////////Script Commands....//////////
	registerCommand("Varx", Varx, false);

	registerCommand("Getx", GetVarx, false);
	registerCommand("Printx", GetVarx, false);


	registerCommand("Setx", SetVarx, false);

	/// Script instruments equivalent in x64dbg 
	registerCommand("Movx", Movx, true);
	registerCommand("addx", addx, true);
	registerCommand("subx", subx, true);
	registerCommand("mulx", mulx, true);
	registerCommand("divx", divx, true);
	registerCommand("andx", andx, true);
	registerCommand("orx", orx, true);
	registerCommand("xorx", xorx, true);
	registerCommand("shlx", shlx, true);

	registerCommand("pushx", pushx, true);
	registerCommand("popx", popx, true);

	registerCommand("cmpx", cmpx, true);
	////
	registerCommand("findx", findx, true);
	registerCommand("findallx", findallx, true);
	registerCommand("findallmemx", findallmemx, true);
	////
	registerCommand("VarxClear", VarxClear, false);
	registerCommand("memdump", memdump, true);
	////
	registerCommand("writeStr", WriteStr, true);
	registerCommand("ReadStr", ReadStr, true);

	registerCommand("BPxx", BPxx, true);
	registerCommand("bpcx", bpcx, true);
	registerCommand("bpex", bpex, true);
	registerCommand("bpdx", bpdx, true);
	registerCommand("bphx", bphx, true);
	registerCommand("bphcx", bphcx, true);
	registerCommand("bphex", bphex, true);
	registerCommand("bphdx", bphdx, true);
	registerCommand("bpmx", bpmx, true);
	registerCommand("asmx", asmx, true);

	registerCommand("GetAPIName", GetAPIName, true);
	registerCommand("ResizeArray", ResizeArray, false);
	registerCommand("GetArraySize", GetArraySize, false);
	registerCommand("Write2File", Write2File, false);
	registerCommand("inputbox", InputBox, false);

	registerCommand("cmtx", commentset, true);

	_plugin_logputs(Str2ConstChar(Environment::NewLine));
}
////////////////////////////////////////////////////////////////////////////////////////////////////
static bool test(int argc, char* argv[]) {
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments); // this function use by refrence so the list will fill direct	
	switch (arguments->Count)
	{
	case 1: {
		duint x=Script::Memory::GetSize(Hex2duint(arguments[0]));
		//char* text_ = new char[MAX_STRING_SIZE];
		////DbgGetStringAt(Script::Register::Get(Script::Register::RCX), text_);
		//_plugin_logprint(text_);
		/*String^ AsmcommandStr = StringFormatInline_Str(arguments[0]);
		DbgCmdExecDirect(Str2ConstChar("cmt " + AsmcommandStr));*/
		break;
	}
	case 2: {
		break;
	}
	default:
		_plugin_logputs("worng arguments");
		return false;
	}
	//DbgScriptCmdExec("{jmp res}");


	// for script goto line
	//DbgScriptSetIp(3);

	/*SELECTIONDATA sel;
	GuiSelectionGet(GUI_DUMP, &sel);
	unsigned char* x = new unsigned char[255];
	DbgMemRead(sel.start, x, 16);
	const char f = x[5];
	return true;*/

	/*char* text_ = new char[MAX_STRING_SIZE];
	DbgGetStringAt(Script::Register::Get(Script::Register::RSI), text_);
	_plugin_logputs(text_);
	DbgGetStringAt(Script::Register::Get(Script::Register::RDI), text_);
	_plugin_logputs(text_);
	DbgGetStringAt(Script::Register::Get(Script::Register::R8), text_);
	_plugin_logputs(text_);
	unsigned char* xc=new unsigned char[MAX_STRING_SIZE] ;
	const char* l = "test";
	memcpy(xc, l, sizeof(l));
	Script::Memory::WriteByte(Script::Register::Get(Script::Register::R8), xc[0]);*/

	//ScriptFunList::VarList[0]->ResizeArr(10);
	//unsigned char x; // = new  char[MAX_STRING_SIZE];
	//String^ d = StringFormatInline_Str("{rip");
	//duint h = Hex2duint(d);
	//x = Script::Memory::ReadByte(h);

	return true;

}
////////////////////////////////////////////////////////////////////////////////////////////////////
static void ShowDialog_Script()
{
	AdvancedScript::MainForm ScriptWindow;
	ScriptWindow.ShowDialog();
}

static bool cbMainForm(int argc, char* argv[])
{
	_plugin_logputs("[Script Window] Loading.......!");
	///////////////////////////////////////////////////////////////////////////////////////
	// this will keep form activate and x64dbg unable to do it's work by excuted commands 
	//ScriptS::IATFixer IATFixer;
	//IATFixer.ShowDialog();
	///////////////////////////////////////////////////////////////////////////////////////

	// we used this (New Thread) to Create our Form in new Thread so we able to comunicated with x64dbg
	// and be able to send command let go to address or do some  other commands 
	System::Threading::Thread^ thread_ = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(&ShowDialog_Script));
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
		_plugin_logputs("worng arguments");
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
	if (argc > 1) { _plugin_logputs("worng arguments"); return false; }
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
	if (argc > 1) { _plugin_logputs("worng arguments"); return false; }
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
			if (!CheckexcutedCmd(arguments[0])) {
				AdvancedScript::LogWindow::LogWindow_->Log_Str = AdvancedScript::LogWindow::Log_Str + Environment::NewLine + StrAnalyze(arguments[0], VarType::str, true);
				if (AdvancedScript::LogWindow::LogWindow_->FormLoaded) {
					AdvancedScript::LogWindow::LogWindow_->RTBAppendText(StrAnalyze(arguments[0], VarType::str, true));
				}
			}
		}
		break;
	}
	default:
		_plugin_logputs("worng arguments");
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
		_plugin_logputs("Trcer is off now");
	}
	if (!GetTemplate(ManagedGlobals::logxTraceArg2, TemplateClassFound)) {
		Script::Gui::Message("No Template with this name");
		LogTraceOn = false;
		_plugin_logputs("Trcer is off now");
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
	if ((arguments->Count != 3) && (arguments->Count != 1)) { _plugin_logputs("worng arguments"); return false; }
	if (arguments[0] != "on" && arguments[0] != "off")
	{
		_plugin_logputs("worng arguments on/off"); return false;
	}
	if (arguments[0] == "on") {
		if (!IO::Directory::Exists(Application::StartupPath + "\\LogTrace")) {
			IO::Directory::CreateDirectory(Application::StartupPath + "\\LogTrace");
		}
		if (!GetTemplate(arguments[1], TemplateClassFound)) {
			LogTraceOn = false;
			_plugin_logputs("worng Template name, Trcer is off now");
			return false;
		}
		else {
			TemplateData_ = Str2ConstChar(TemplateClassFound->TemplateData);
		}
		_plugin_logputs("Trcer is on now");
		LogTraceOn = true;
		TraceFile_ = Str2ConstChar(Application::StartupPath + "\\LogTrace\\" + arguments[2] + ".txt");
	}
	else if (arguments[0] == "off") {
		LogTraceOn = false;
		_plugin_logputs("Trcer is off now");
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
		_plugin_logputs("worng Template name");
		return;
	}
	switch ((arguments->Count))
	{
	case 4: {
		String^ addr_temp = StringFormatInline_Str(arguments[2]);
		duint addr = Hex2duint(addr_temp);  /// the address of String in the memory targed which need to comapre with 
		if (addr == -1) {
			_plugin_logputs(Str2ConstChar("can't Getting Address!! maybe you forget { , because it should follow x64dbg string format "));
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
			_plugin_logputs(Str2ConstChar("Can't read the string at this address: " + duint2Hex(addr)));
			DbgCmdExec("run");
			return;
		}

		_plugin_logputs(Str2ConstChar(Target_Str2Compare));

		String^ UserStr = arguments[3];
		if (!Target_Str2Compare->ToLower()->Trim()->Contains(UserStr->ToLower()->Trim())) {
			_plugin_logputs(Str2ConstChar(Target_Str2Compare));
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
		_plugin_logputs("worng arguments");
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
		return Varx_(arguments[0], arguments[1]); // varvalue will make it ""		
	}
	case 3: {
		return Varx_(arguments[0], arguments[1], arguments[2]);
	}
	default:
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
		return false;
	}
	return true;
}

static bool SetVarx(int argc, char* argv[]) {			//Setx_(String^ varname, int index_,String^ value_)
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments); // this function use by refrence so the list will fill direct	
	String^ arrayIndex;
	switch ((arguments->Count))
	{
	case 2: {
		if ((arguments[0]->Contains("[")) && (arguments[0]->Contains("]"))) { // this is array var
			//arrayIndex = arguments[0]->Substring(arguments[0]->IndexOf("[") + 1, arguments[0]->Length - (arguments[0]->IndexOf("]") - 1));
			arrayIndex = arguments[0]->Substring(arguments[0]->IndexOf("[") + 1, arguments[0]->Length - (arguments[0]->IndexOf("[") + 1));
			arrayIndex = arrayIndex->Substring(0, arrayIndex->LastIndexOf("]"));
			//arrayIndex = argumentValue(arguments[1], OldValue_);
			arrayIndex = GetArgValueByType(arrayIndex, VarType::int_);
			if ((arrayIndex->StartsWith("NULL/")) || (!Information::IsNumeric(arrayIndex))) {
				_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng index of array"));
				return false;
			}
			else
			{  /// we checkd that array index is int, need to check the value of the array
				return SetVarx_(arguments[0]->Substring(0, arguments[0]->IndexOf("["))->Trim(), (int)Str2duint(arrayIndex->Trim()), arguments[1]);
			}

		}
		else  /// var is str or int
		{
			return SetVarx_(arguments[0], 0, arguments[1]);
		}
	}
	default:
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
		return false;
	}
}

static bool GetVarx(int argc, char* argv[]) { //GetVarx_(String^ varname,int index)
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments); // this function use by refrence so the list will fill direct	
	switch ((arguments->Count))
	{
	case 1: {  // case the var is int or str so the value at index=0
		if (!arguments[0]->StartsWith("$")) {
			_plugin_logputs(Str2ConstChar(Environment::NewLine + "wrong variable name"));
			return false;
		}
		if (!arguments[0]->Contains("[")) {  /// this mean it's int or str
			GetVarx_(arguments[0], 0);
			return true;
		}
		if ((arguments[0]->Contains("[")) && (arguments[0]->Contains("]"))) {  /// this mean it's array
			String^  arrayIndex = arguments[0]->Substring(arguments[0]->IndexOf("[") + 1, arguments[0]->Length - (arguments[0]->IndexOf("[") + 1));
			arrayIndex = arrayIndex->Substring(0, arrayIndex->LastIndexOf("]"));
			arrayIndex = GetArgValueByType(arrayIndex, VarType::int_);
			if ((arrayIndex->StartsWith("NULL/")) || (!Information::IsNumeric(arrayIndex))) {
				_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng index of array"));
				return false;
			}
			else
			{  /// we checkd that array index is int, need to check the value of the array
				GetVarx_(arguments[0]->Substring(0, arguments[0]->IndexOf("[")), (int)Str2duint(arrayIndex));
			}
		}
		else {
			_plugin_logputs(Str2ConstChar(Environment::NewLine + "missing []"));
			return false;
		}
		break;
	}
	default:
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
		break;
	}
	return true;
}



static bool Movx(int argc, char* argv[]) { //Varx_(String^ vartype, String^ varname, String^ varvalue="")
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments); // this function use by refrence so the list will fill direct	

	switch ((arguments->Count))
	{
	case 2: {
		String^ cmd = Movx_(arguments[0], arguments[1]);
		if (!cmd->Contains("NULL/")) {
			return DbgCmdExecDirect(Str2ConstChar(cmd));
			//break;
		}
		else
		{
			_plugin_logputs(Str2ConstChar(Environment::NewLine + "Couldn't read argument 2"));
			return false;
		}
	}
	default:
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
		return false;
	}
	return true;
}

static bool addx(int argc, char* argv[]) { //Varx_(String^ vartype, String^ varname, String^ varvalue="")
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments); // this function use by refrence so the list will fill direct	

	switch ((arguments->Count))
	{
	case 2: {
		String^ cmd = addx_(arguments[0], arguments[1]);
		if (!cmd->Contains("NULL/")) {
			return DbgCmdExecDirect(Str2ConstChar(cmd));			
		}
		else
		{
			_plugin_logputs(Str2ConstChar(Environment::NewLine + "Couldn't read argument 2"));
			return false;
		}
	}
	default:
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
		return false;
	}
	return true;
}

static bool subx(int argc, char* argv[]) { //Varx_(String^ vartype, String^ varname, String^ varvalue="")
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments); // this function use by refrence so the list will fill direct	

	switch ((arguments->Count))
	{
	case 2: {
		String^ cmd = subx_(arguments[0], arguments[1]);
		if (!cmd->Contains("NULL/")) {
			return DbgCmdExecDirect(Str2ConstChar(cmd));			
		}
		else
		{
			_plugin_logputs(Str2ConstChar(Environment::NewLine + "Couldn't read argument 2"));
			return false;
		}
	}
	default:
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
		return false;
	}
	return true;
}

static bool mulx(int argc, char* argv[]) { //Varx_(String^ vartype, String^ varname, String^ varvalue="")
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments); // this function use by refrence so the list will fill direct	

	switch ((arguments->Count))
	{
	case 2: {
		String^ cmd = mulx_(arguments[0], arguments[1]);
		if (!cmd->Contains("NULL/")) {
			return DbgCmdExecDirect(Str2ConstChar(cmd));
			
		}
		else
		{
			_plugin_logputs(Str2ConstChar(Environment::NewLine + "Couldn't read argument 2"));
			return false;
		}
	}
	default:
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
		return false;
	}
	return true;
}

static bool divx(int argc, char* argv[]) { //Varx_(String^ vartype, String^ varname, String^ varvalue="")
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments); // this function use by refrence so the list will fill direct	

	switch ((arguments->Count))
	{
	case 2: {
		String^ cmd = divx_(arguments[0], arguments[1]);
		if (!cmd->Contains("NULL/")) {
			return DbgCmdExecDirect(Str2ConstChar(cmd));
			
		}
		else
		{
			_plugin_logputs(Str2ConstChar(Environment::NewLine + "Couldn't read argument 2"));
			return false;
		}
	}
	default:
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
		return false;
	}
	return true;
}

static bool cmpx(int argc, char* argv[]) { //Varx_(String^ vartype, String^ varname, String^ varvalue="")
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments); // this function use by refrence so the list will fill direct	

	switch ((arguments->Count))
	{
	case 2: {
		String^ cmd = cmpx_(arguments[0], arguments[1]);
		if (!cmd->Contains("NULL/")) {
			return DbgCmdExecDirect(Str2ConstChar(cmd));
			
		}
		else
		{
			_plugin_logputs(Str2ConstChar(Environment::NewLine + "Couldn't read argument 2"));
			return false;
		}
	}
	default:
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
		return false;
	}
	return true;
}

static bool andx(int argc, char* argv[]) { //Varx_(String^ vartype, String^ varname, String^ varvalue="")
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments); // this function use by refrence so the list will fill direct	

	switch ((arguments->Count))
	{
	case 2: {
		String^ cmd = andx_(arguments[0], arguments[1]);
		if (!cmd->Contains("NULL/")) {
			return DbgCmdExecDirect(Str2ConstChar(cmd));			
		}
		else
		{
			_plugin_logputs(Str2ConstChar(Environment::NewLine + "Couldn't read argument 2"));
			return false;
		}
	}
	default:
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
		return false;
	}
	return true;
}

static bool orx(int argc, char* argv[]) { //Varx_(String^ vartype, String^ varname, String^ varvalue="")
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments); // this function use by refrence so the list will fill direct	

	switch ((arguments->Count))
	{
	case 2: {
		String^ cmd = orx_(arguments[0], arguments[1]);
		if (!cmd->Contains("NULL/")) {
			return DbgCmdExecDirect(Str2ConstChar(cmd));
			
		}
		else
		{
			_plugin_logputs(Str2ConstChar(Environment::NewLine + "Couldn't read argument 2"));
			return false;
		}
	}
	default:
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
		return false;
	}
	return true;
}

static bool xorx(int argc, char* argv[]) { //Varx_(String^ vartype, String^ varname, String^ varvalue="")
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments); // this function use by refrence so the list will fill direct	

	switch ((arguments->Count))
	{
	case 2: {
		String^ cmd = xorx_(arguments[0], arguments[1]);
		if (!cmd->Contains("NULL/")) {
			return DbgCmdExecDirect(Str2ConstChar(cmd));
			
		}
		else
		{
			_plugin_logputs(Str2ConstChar(Environment::NewLine + "Couldn't read argument 2"));
			return false;
		}
	}
	default:
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
		return false;
	}
	return true;
}

static bool shlx(int argc, char* argv[]) { //Varx_(String^ vartype, String^ varname, String^ varvalue="")
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments); // this function use by refrence so the list will fill direct	

	switch ((arguments->Count))
	{
	case 2: {
		String^ cmd = shlx_(arguments[0], arguments[1]);
		if (!cmd->Contains("NULL/")) {
			return DbgCmdExecDirect(Str2ConstChar(cmd));
			
		}
		else
		{
			_plugin_logputs(Str2ConstChar(Environment::NewLine + "Couldn't read argument 2"));
			return false;
		}
	}
	default:
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
		return false;
	}
	return true;
}

static bool pushx(int argc, char* argv[]) { //Varx_(String^ vartype, String^ varname, String^ varvalue="")
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments); // this function use by refrence so the list will fill direct	

	switch ((arguments->Count))
	{
	case 1: {
		String^ cmd = pushx_(arguments[0]);
		if (!cmd->Contains("NULL/")) {
			return DbgCmdExecDirect(Str2ConstChar(cmd));
			
		}
		else
		{
			_plugin_logputs(Str2ConstChar(Environment::NewLine + "Couldn't read argument 2"));
			return false;
		}
	}
	default:
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
		return false;
	}
	return true;
}

static bool popx(int argc, char* argv[]) { //Varx_(String^ vartype, String^ varname, String^ varvalue="")
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments); // this function use by refrence so the list will fill direct	

	switch ((arguments->Count))
	{
	case 1: {
		String^ cmd = popx_(arguments[0]);
		if (!cmd->Contains("NULL/")) {
			return DbgCmdExecDirect(Str2ConstChar(cmd));			
		}
		else
		{
			_plugin_logputs(Str2ConstChar(Environment::NewLine + "Couldn't read argument 2"));
			return false;
		}
	}
	default:
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
		return false;
	}
	return true;
}

static bool findx(int argc, char* argv[]) { // findallmemx(String^ base_, String^ Searchvalue_,String^ Size_) 
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments); // this function use by refrence so the list will fill direct	

	switch ((arguments->Count))
	{
	case 2: {
		String^ cmd = findx_(arguments[0], arguments[1]);
		return DbgCmdExecDirect(Str2ConstChar(cmd));		
	}
	case 3: {
		String^ cmd = findx_(arguments[0], arguments[1], arguments[2]);
		return DbgCmdExecDirect(Str2ConstChar(cmd));		
	}
	default:
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
		break;
	}
	return false;
}

static bool findallx(int argc, char* argv[]) { // findallmemx(String^ base_, String^ Searchvalue_,String^ Size_) 
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments); // this function use by refrence so the list will fill direct	

	switch ((arguments->Count))
	{
	case 2: {
		String^ cmd = findallx_(arguments[0], arguments[1]);
		return DbgCmdExecDirect(Str2ConstChar(cmd));		
	}
	case 3: {
		String^ cmd = findallx_(arguments[0], arguments[1], arguments[2]);
		return DbgCmdExecDirect(Str2ConstChar(cmd));		
	}
	default:
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
		break;
	}
	return false;
}

static bool findallmemx(int argc, char* argv[]) { // findallmemx(String^ base_, String^ Searchvalue_,String^ Size_) 
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments); // this function use by refrence so the list will fill direct	

	switch ((arguments->Count))
	{
	case 2: {
		String^ cmd = findallmemx_(arguments[0], arguments[1]);
		return DbgCmdExecDirect(Str2ConstChar(cmd));
		
	}
	case 3: {
		String^ cmd = findallmemx_(arguments[0], arguments[1], arguments[2]);
		return DbgCmdExecDirect(Str2ConstChar(cmd));
		
	}
	default:
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
		break;
	}
	return false;
}


static bool VarxClear(int argc, char* argv[]) {  /// clear all variables 
	VarListClear();
	return true;
}

static bool memdump(int argc, char* argv[]) {  /// dump memory to log window like windbg style
	//00007ff8`02f42280  cc c3 cc cc cc cc cc cc - 0f 1f 84 00 00 00 00 00  ................
	//00007ff8`02f42290  cc c3 cc cc cc cc cc cc - 0f 1f 84 00 00 00 00 00  ................
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments); // this function use by refrence so the list will fill direct	

	String^ addr = StrAnalyze(arguments[0], VarType::str, true);
	String^ Size_ = StrAnalyze(arguments[1], VarType::str);
	if ((addr->StartsWith("NULL/ ")) || (Size_->StartsWith("NULL/ "))) {
		_plugin_logprint("wrong arguments for memdump command");
		return false;
	}
	switch (arguments->Count)
	{
	case 2: {
		dumpmem(addr, Size_);
		return true;
	}
	case 3: {
		dumpmem(addr, Size_, arguments[2]);
		return true;
	}
	default:
		_plugin_logprint("wrong arguments for memdump command");
		return false;
	}
	return true;
}



static bool WriteStr(int argc, char* argv[]) { //WriteStr(duint address, String^ text, bool replace)
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments); // this function use by refrence so the list will fill direct	

	switch ((arguments->Count))
	{
	case 3: {
		String^ addr = StrAnalyze(arguments[0], VarType::str, true);
		String^ intValue;

		if (CheckHexIsValid(addr, intValue) == 0) {
			_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng address"));
			return false;
		}
		String^ text_ = StrAnalyze(arguments[1], VarType::str);
		bool replace_ = Str2bool(arguments[2]);
		WriteStr_(Str2duint(intValue), text_, replace_);
		break;
	}
	default:
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
		return false;
	}
	return true;
}

static bool ReadStr(int argc, char* argv[]) { //ReadStr(variable,duint address)
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments); // this function use by refrence so the list will fill direct	

	switch ((arguments->Count))
	{
	case 2: {
		String^ addr = StrAnalyze(arguments[1], VarType::str, true);
		String^ intValue;

		if (CheckHexIsValid(addr, intValue) == 0) {
			_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng address"));
			return false;
		}
		char* Read_Str2_ = new char[MAX_STRING_SIZE];
		if (DbgGetStringAt(Hex2duint(addr), Read_Str2_)) {
			String^ Read_Str2 = CharArr2Str(Read_Str2_);
			return ReadStr_(arguments[0], Read_Str2);
		}
		else {
			_plugin_logputs(Str2ConstChar("Can't read the string at this address: " + addr));
			return  false;
		}		
		break;
	}
	default:
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
		return false;
	}
	return false;
}

/// BP 

static bool BPxx(int argc, char* argv[]) {
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments); // this function use by refrence so the list will fill direct	

	switch ((arguments->Count))
	{
	case 1: {
		String^ cmd = StrAnalyze(arguments[0], VarType::str, true);
		if (!cmd->Contains("NULL")) {
			cmd = "bp " + cmd;
			return DbgCmdExecDirect(Str2ConstChar(cmd));			
		}
		else
		{
			_plugin_logputs(Str2ConstChar(Environment::NewLine + cmd + "worng arguments"));
			return false;
		}
		break;
	}
	case 2: {
		String^ addr = StrAnalyze(arguments[0], VarType::str, true);
		String^ BPname = StrAnalyze(arguments[1], VarType::str);
		if ((!addr->Contains("NULL")) && (!BPname->Contains("NULL"))) {
			String^ cmd = "bp " + addr + "," + BPname;
			return DbgCmdExecDirect(Str2ConstChar(cmd));
			
		}
		else
		{
			_plugin_logputs(Str2ConstChar(Environment::NewLine + addr + " " + BPname));
			_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
			return false;
		}
		break;
	}
	case 3: {
		String^ addr = StrAnalyze(arguments[0], VarType::str, true);
		String^ BPname = StrAnalyze(arguments[1], VarType::str);
		String^ BPType = StrAnalyze(arguments[2], VarType::str);
		if ((!addr->Contains("NULL")) && (!BPname->Contains("NULL")) && (!BPname->Contains("NULL"))) {
			String^ cmd = "bp " + addr + "," + BPname + "," + BPType;
			return DbgCmdExecDirect(Str2ConstChar(cmd));
			
		}
		else
		{
			_plugin_logputs(Str2ConstChar(Environment::NewLine + addr + " " + BPname + " " + BPType));
			_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
			return false;
		}
		break;
	}
	default:
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
		return false;
	}
	return true;
}

static bool bpcx(int argc, char* argv[]) {
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments); // this function use by refrence so the list will fill direct	

	switch ((arguments->Count))
	{
	case 1: {
		String^ cmd = StrAnalyze(arguments[0], VarType::str, true);
		if (!cmd->Contains("NULL")) {
			cmd = "bpc " + cmd;
			return DbgCmdExecDirect(Str2ConstChar(cmd));
			
		}
		else
		{
			_plugin_logputs(Str2ConstChar(Environment::NewLine + cmd + "worng arguments"));
			return false;
		}
		break;
	}
	default:
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
		return false;
	}
	return true;
}

static bool bpex(int argc, char* argv[]) {
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments);

	switch ((arguments->Count))
	{
	case 1: {
		String^ cmd = StrAnalyze(arguments[0], VarType::str, true);
		if (!cmd->Contains("NULL")) {
			cmd = "bpe " + cmd;
			return DbgCmdExecDirect(Str2ConstChar(cmd));
			
		}
		else
		{
			_plugin_logputs(Str2ConstChar(Environment::NewLine + cmd + "worng arguments"));
			return false;
		}
		break;
	}
	default:
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
		return false;
	}
	return true;
}

static bool bpdx(int argc, char* argv[]) {
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments);

	switch ((arguments->Count))
	{
	case 1: {
		String^ cmd = StrAnalyze(arguments[0], VarType::str, true);
		if (!cmd->Contains("NULL")) {
			cmd = "bpd " + cmd;
			return DbgCmdExecDirect(Str2ConstChar(cmd));
			
		}
		else
		{
			_plugin_logputs(Str2ConstChar(Environment::NewLine + cmd + "worng arguments"));
			return false;
		}
		break;
	}
	default:
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
		return false;
	}
	return true;
}

static bool bphx(int argc, char* argv[]) {
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments); // this function use by refrence so the list will fill direct	

	switch ((arguments->Count))
	{
	case 1: {
		String^ cmd = StrAnalyze(arguments[0], VarType::str, true);
		if (!cmd->Contains("NULL")) {
			cmd = "bph " + cmd;
			return DbgCmdExecDirect(Str2ConstChar(cmd));
			
		}
		else
		{
			_plugin_logputs(Str2ConstChar(Environment::NewLine + cmd + "worng arguments"));
			return false;
		}
		break;
	}
	case 2: {
		String^ addr = StrAnalyze(arguments[0], VarType::str, true);
		String^ BPname = StrAnalyze(arguments[1], VarType::str);
		if ((!addr->Contains("NULL")) && (!BPname->Contains("NULL"))) {
			String^ cmd = "bph " + addr + "," + BPname;
			return DbgCmdExecDirect(Str2ConstChar(cmd));
			
		}
		else
		{
			_plugin_logputs(Str2ConstChar(Environment::NewLine + addr + " " + BPname));
			_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
			return false;
		}
		break;
	}
	case 3: {
		String^ addr = StrAnalyze(arguments[0], VarType::str, true);
		String^ BPname = StrAnalyze(arguments[1], VarType::str);
		String^ BPType = StrAnalyze(arguments[2], VarType::str);
		if ((!addr->Contains("NULL")) && (!BPname->Contains("NULL")) && (!BPname->Contains("NULL"))) {
			String^ cmd = "bph " + addr + "," + BPname + "," + BPType;
			return DbgCmdExecDirect(Str2ConstChar(cmd));			
		}
		else
		{
			_plugin_logputs(Str2ConstChar(Environment::NewLine + addr + " " + BPname + " " + BPType));
			_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
			return false;
		}
		break;
	}
	default:
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
		return false;
	}
	return true;
}

static bool bphcx(int argc, char* argv[]) {
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments);

	switch ((arguments->Count))
	{
	case 1: {
		String^ cmd = StrAnalyze(arguments[0], VarType::str, true);
		if (!cmd->Contains("NULL")) {
			cmd = "bphc " + cmd;
			return DbgCmdExecDirect(Str2ConstChar(cmd));			
		}
		else
		{
			_plugin_logputs(Str2ConstChar(Environment::NewLine + cmd + "worng arguments"));
			return false;
		}
		break;
	}
	default:
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
		return false;
	}
	return true;
}

static bool bphex(int argc, char* argv[]) {
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments);

	switch ((arguments->Count))
	{
	case 1: {
		String^ cmd = StrAnalyze(arguments[0], VarType::str, true);
		if (!cmd->Contains("NULL")) {
			cmd = "bphe " + cmd;
			return DbgCmdExecDirect(Str2ConstChar(cmd));			
		}
		else
		{
			_plugin_logputs(Str2ConstChar(Environment::NewLine + cmd + "worng arguments"));
			return false;
		}
		break;
	}
	default:
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
		return false;
	}
	return true;
}


static bool bphdx(int argc, char* argv[]) {
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments);

	switch ((arguments->Count))
	{
	case 1: {
		String^ cmd = StrAnalyze(arguments[0], VarType::str, true);
		if (!cmd->Contains("NULL")) {
			cmd = "bphd " + cmd;
			return DbgCmdExecDirect(Str2ConstChar(cmd));			
		}
		else
		{
			_plugin_logputs(Str2ConstChar(Environment::NewLine + cmd + "worng arguments"));
			return false;
		}
		break;
	}
	default:
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
		return false;
	}
	return true;
}

static bool bpmx(int argc, char* argv[]) {
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments); // this function use by refrence so the list will fill direct	

	switch ((arguments->Count))
	{
	case 1: {
		String^ cmd = StrAnalyze(arguments[0], VarType::str, true);
		if (!cmd->Contains("NULL")) {
			cmd = "bpm " + cmd;
			return DbgCmdExecDirect(Str2ConstChar(cmd));
			
		}
		else
		{
			_plugin_logputs(Str2ConstChar(Environment::NewLine + cmd + "worng arguments"));
			return false;
		}
		break;
	}
	case 2: {
		String^ addr = StrAnalyze(arguments[0], VarType::str, true);
		String^ BPname = StrAnalyze(arguments[1], VarType::str);
		if ((!addr->Contains("NULL")) && (!BPname->Contains("NULL"))) {
			String^ cmd = "bpm " + addr + "," + BPname;
			return DbgCmdExecDirect(Str2ConstChar(cmd));
			
		}
		else
		{
			_plugin_logputs(Str2ConstChar(Environment::NewLine + addr + " " + BPname));
			_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
			return false;
		}
		break;
	}
	case 3: {
		String^ addr = StrAnalyze(arguments[0], VarType::str, true);
		String^ BPname = StrAnalyze(arguments[1], VarType::str);
		String^ BPType = StrAnalyze(arguments[2], VarType::str);
		if ((!addr->Contains("NULL")) && (!BPname->Contains("NULL")) && (!BPname->Contains("NULL"))) {
			String^ cmd = "bpm " + addr + "," + BPname + "," + BPType;
			return DbgCmdExecDirect(Str2ConstChar(cmd));
			
		}
		else
		{
			_plugin_logputs(Str2ConstChar(Environment::NewLine + addr + " " + BPname + " " + BPType));
			_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
			return false;
		}
		break;
	}
	default:
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
		return false;
	}
	return true;
}

static bool asmx(int argc, char* argv[]) { // asmx ( addr , Instruction , fill with nops
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments); // this function use by refrence so the list will fill direct	

	switch ((arguments->Count))
	{

	case 2: {
		String^ addr = StrAnalyze(arguments[0], VarType::str, true);
		if (!addr->StartsWith("0x")) {
			addr = "0x" + addr;
		}
		String^ Instruction = StrAnalyze(arguments[1], VarType::str, true);
		//bool FillNops = Str2bool(arguments[2]);
		if ((!Instruction->StartsWith("\"")) && (!Instruction->EndsWith("\""))) {
			Instruction = "\"" + Instruction + "\"";
		}
		if ((!addr->Contains("NULL")) && (!Instruction->Contains("NULL"))) {
			String^ cmd =  "asm " + addr + "," + Instruction ;			
			return DbgCmdExecDirect(Str2ConstChar(cmd));			 
		}
		else
		{
			_plugin_logputs(Str2ConstChar(Environment::NewLine + addr + " " + Instruction));
			_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
			return false;
		}
		break;
	}
	case 3: {
		String^ addr = StrAnalyze(arguments[0], VarType::str, true);
		if (!addr->StartsWith("0x")) {
			addr = "0x" + addr;
		}
		String^ Instruction = StrAnalyze(arguments[1], VarType::str, true);
		if ((!Instruction->StartsWith("\"")) && (!Instruction->EndsWith("\""))) {
			Instruction = "\"" + Instruction + "\"";
		}
		//String^ BPType = StrAnalyze(arguments[2], VarType::str);
		if ((!addr->Contains("NULL")) && (!Instruction->Contains("NULL")) && (!Instruction->Contains("NULL"))) {
			String^ cmd = "asm " + addr + "," + Instruction + ",\"" + "1\""  ;
			return DbgCmdExec(Str2ConstChar(cmd));			 
		}
		else
		{
			_plugin_logputs(Str2ConstChar(Environment::NewLine + addr + " " + Instruction + " " + arguments[2]));
			_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
			return false;
		}
		break;
	}
	default:
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
		return false;
	}
	return true;
}


static bool GetAPIName(int argc, char* argv[]) {  //GetAPIName_ (String^ varname , duint addrress)
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments);
	switch ((arguments->Count))
	{

	case 2: {
		String^ addr = StrAnalyze(arguments[1], VarType::str, true);	 // check is addr is valid 
		if ((!addr->Contains("NULL"))) {
			String^ intValue;
			if (CheckHexIsValid(addr, intValue) > 0) {
				/////////////////
				if (!arguments[0]->StartsWith("$")) {   /// check if the var is valid
					_plugin_logputs(Str2ConstChar(Environment::NewLine + "wrong variable name"));
					return false;
				}
				if (!arguments[0]->Contains("[")) {  /// this mean it's int or str
					SetVarx_(arguments[0], 0, GetAPIName_LableWay(Hex2duint(addr)));
					return true;
				}
				if ((arguments[0]->Contains("[")) && (arguments[0]->Contains("]"))) {  /// this mean it's array
					String^  arrayIndex = arguments[0]->Substring(arguments[0]->IndexOf("[") + 1, arguments[0]->Length - (arguments[0]->IndexOf("[") + 1));
					arrayIndex = arrayIndex->Substring(0, arrayIndex->LastIndexOf("]"));
					arrayIndex = GetArgValueByType(arrayIndex, VarType::int_);
					if ((arrayIndex->StartsWith("NULL/")) || (!Information::IsNumeric(arrayIndex))) {
						_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng index of array"));
						return false;
					}
					else
					{  /// we checkd that array index is int, need to check the value of the array
						SetVarx_(arguments[0]->Substring(0, arguments[0]->IndexOf("[")), (int)Str2duint(arrayIndex), GetAPIName_LableWay(Hex2duint(addr)));
					}
				}
				else {
					_plugin_logputs(Str2ConstChar(Environment::NewLine + "missing []"));
					return false;
				}
				/////////

				return true;
			}
			else
			{
				_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng Address" + addr));
				return false;
			}

		}
		else
		{
			_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
			return false;
		}
		break;
	}
	default:
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
		return false;
	}
	return true;
}

static bool ResizeArray(int argc, char* argv[]) { //resizeArr(array,added amount)
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments);
	switch ((arguments->Count))
	{
	case 2: {
		String^ ResizeAmount = StrAnalyze(arguments[1], VarType::int_);  /// in case there are variable
		if (ResizeAmount->Contains("NULL/")) {
			_plugin_logputs(Str2ConstChar(Environment::NewLine + "Can't get ResizeAmount as int: " + ResizeAmount));
			return false;
		}
		return ResizeArray_(arguments[0], Str2int(ResizeAmount));
	}
	default:
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
		return false;
	}
	return true;
}


static bool GetArraySize(int argc, char* argv[]) {   // GetArraySize( Array var name, var as input)
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments);
	switch ((arguments->Count))
	{
	case 2: {
		return GetArraySize_(arguments[0], arguments[1]);
	}
	default:
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
		return false;
	}
	return true;

}

static bool Write2File(int argc, char* argv[]) {  // write2File(path,over_append(true),data
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments);
	switch ((arguments->Count))
	{
	case 3: {
		String^ pathfile;
		if (arguments[0]->StartsWith("$")) {  /// that mesn its variable
			String^ path_ = StrAnalyze(arguments[0], VarType::str);
			if (!path_->Contains("NULL/")) {
				if (!path_->EndsWith(".txt")) {
					_plugin_logputs(Str2ConstChar(Environment::NewLine + "not ended with .txt"));
					return false;
				}				
				if (!IO::Directory::Exists(IO::Path::GetDirectoryName(path_))) {
					_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng path"));
					return false;
				}
			}
			else
			{
				_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng path"));
				return false;
			}
			pathfile = StrAnalyze(arguments[0], VarType::str);
		}
		else
		{
			if (!arguments[0]->EndsWith(".txt")) {
				_plugin_logputs(Str2ConstChar(Environment::NewLine + "not ended with .txt"));
				return false;
			}
			if (arguments[0]->Contains("\\")) {  /// check it if it's path file				
				if (!IO::Directory::Exists(IO::Path::GetDirectoryName(arguments[0]))) {
					_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng path"));
					return false;
				}
			}
			else
			{
				_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng path"));
				return false;
			}
			pathfile = arguments[0];
		}


		return Write2File_(pathfile, Str2bool(arguments[1]),arguments[2]);
	}
	default:
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
		return false;
	}
	return true;

}


static bool InputBox(int argc, char* argv[]) {  // inputBox ( variable,String message,String title)
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments);
	switch ((arguments->Count))
	{
	case 3: {
		if ((arguments[0]->Contains("[")) && (arguments[0]->Contains("]"))) {  /// this mean it's array
			String^  arrayIndex = arguments[0]->Substring(arguments[0]->IndexOf("[") + 1, arguments[0]->Length - (arguments[0]->IndexOf("[") + 1));
			arrayIndex = arrayIndex->Substring(0, arrayIndex->LastIndexOf("]"));
			arrayIndex = GetArgValueByType(arrayIndex, VarType::int_);
			if ((arrayIndex->StartsWith("NULL/")) || (!Information::IsNumeric(arrayIndex))) {
				_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng index of array"));
				return false;
			}
			else
			{  /// we checkd that array index is int, need to check the value of the array
				return InputBox_(arguments[0]->Substring(0, arguments[0]->IndexOf("[")), Str2int(arrayIndex), arguments[1], arguments[2]);
			}
		}
		else  // case int and str
		{
			return InputBox_(arguments[0], 0, arguments[1], arguments[2]);
		}
		return false;
	}
	default:
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
		return false;
	}	
	return false;

}

static bool commentset(int argc, char* argv[]) {  // commentset ( Addr , String message)
	Generic::List<String^>^ arguments;
	GetArg(charPTR2String(argv[0]), arguments);
	switch ((arguments->Count))
	{
	case 2: {		
		String^ Addr = StrAnalyze(arguments[0], VarType::int_);
		if (Information::IsNumeric(Addr)) {
			return DbgCmdExecDirect(Str2ConstChar("cmt " + str2Hex(Addr, VarType::int_, true) + "," + StrAnalyze(arguments[1], VarType::str)));
		}	
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "can't resolve Address"));
		return false;
	}
	default:
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
		return false;
	}
	return false;
}