#include "pluginBasic.h"
#include "Register_UnRegister_Commands.h"
#include "HelperFunctions.h"
#include "LogTemplate.h"
#include "LogWindow.h"
#define plugin_name "AdvancedScript"
#define plugin_version 1

int pluginHandle;
HWND hwndDlg;
int hMenu;
int hMenuDisasm;
int hMenuDump;
int hMenuStack;
extern bool LogOff_;
extern bool LogTraceOn;
extern const char* TraceFile_;
extern const char* TemplateData_;
extern bool log2LogWindowAtBP;

PROCESS_INFORMATION* fdProcessInfo_x;

PLUG_EXPORT void CBBREAKPOINT(CBTYPE cbType, PLUG_CB_BREAKPOINT* info)
{
	///////////////////////// check for Log at BP >>cbLogxJustAtBP
	if (LogOff_) { /// we will Enable Log on BP just so we make EnableLog
		GuiEnableLog();
	}
	if (log2LogWindowAtBP) {
		AdvancedScript::LogWindow::LogWindow_->Log_Str = AdvancedScript::LogWindow::Log_Str + Environment::NewLine + charPTR2String(StringFormatInline_(CharArr2Str(info->breakpoint->logText)));
		if (AdvancedScript::LogWindow::LogWindow_->FormLoaded) {
			AdvancedScript::LogWindow::LogWindow_->RTBAppendText(charPTR2String(StringFormatInline_((CharArr2Str(info->breakpoint->logText)))));
		}
	}
	/////////////////////////

}

PLUG_EXPORT void CBSTOPDEBUG(CBTYPE cbType, PLUG_CB_STOPDEBUG* info)
{
	//dprintf("hit breakpoint on address %p\n", info->breakpoint->addr);	
	if (LogOff_) { /// we will disEnable Log because it's not BP
		GuiDisableLog();
	}
}

PLUG_EXPORT void CBRESUMEDEBUG(CBTYPE cbType, PLUG_CB_RESUMEDEBUG* info)
{
	if (LogOff_) { /// we will disEnable Log  because it's not BP
		GuiDisableLog();
	}
}

PLUG_EXPORT void CBSTEPPED(CBTYPE cbType, PLUG_CB_STEPPED* info)
{
	//duint x=Script::Register::Get(Script::Register::RIP);
	if (LogOff_) { /// we will Enable Log on BP just so we make DisableLog
		GuiDisableLog();
	}
	////////////////////
	//here we will check if Tracer is Enable so we'll log to the file 
	if (LogTraceOn) {
		String^ templateRet = StringFormatInline_Str(CharArr2Str((char*)TemplateData_));
		if (!IO::File::Exists(charPTR2String((char*)TraceFile_))) {
			IO::FileStream^ x = IO::File::Create(charPTR2String((char*)TraceFile_));
			x->Close();
		}
		IO::File::AppendAllText(charPTR2String((char*)TraceFile_), templateRet);
	}
}


PLUG_EXPORT void CBCREATEPROCESS(CBTYPE cbType, PLUG_CB_CREATEPROCESS* info)
{
	//here I could't recive the PLUG_CB_CREATEPROCESS I don't know why but could recive part of the strcture
	//fdProcessInfo_x = new (PROCESS_INFORMATION);
	//fdProcessInfo_x = info->fdProcessInfo;
	//LoadTemplateFiles();
	if (LogOff_) { /// we will Enable Log on BP just so we make DisableLog
		GuiDisableLog();
	}

}

//Initialize your plugin data here.
PLUG_EXPORT bool pluginit(PLUG_INITSTRUCT* initStruct)
{
	initStruct->sdkVersion = plugin_version;
	initStruct->sdkVersion = PLUG_SDKVERSION;
	strcpy(initStruct->pluginName, plugin_name);
	pluginHandle = initStruct->pluginHandle;
	RegisterCommands(initStruct);

	return true; //Return false to cancel loading the plugin.
}

//Deinitialize your plugin data here.
PLUG_EXPORT void plugstop()
{
}


//Do GUI/Menu related things here.
PLUG_EXPORT void plugsetup(PLUG_SETUPSTRUCT* setupStruct)
{
	hwndDlg = setupStruct->hwndDlg;
	hMenu = setupStruct->hMenu;
	hMenuDisasm = setupStruct->hMenuDisasm;
	hMenuDump = setupStruct->hMenuDump;
	hMenuStack = setupStruct->hMenuStack;

}
