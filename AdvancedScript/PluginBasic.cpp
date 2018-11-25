#include "pluginBasic.h"
#include "Register_UnRegister_Commands.h"
#define plugin_name "AdvancedScript"
#define plugin_version 1

int pluginHandle;
HWND hwndDlg;
int hMenu;
int hMenuDisasm;
int hMenuDump;
int hMenuStack;
extern bool LogOff_;

PROCESS_INFORMATION* fdProcessInfo_x;


PLUG_EXPORT void CBBREAKPOINT(CBTYPE cbType, PLUG_CB_BREAKPOINT* info)
{
	//dprintf("hit breakpoint on address %p\n", info->breakpoint->addr);	
	if (LogOff_) { /// we will Enable Log on BP just so we make EnableLog
		GuiEnableLog();		
	}	
}

PLUG_EXPORT void CBSTOPDEBUG(CBTYPE cbType, PLUG_CB_STOPDEBUG* info)
{
	//dprintf("hit breakpoint on address %p\n", info->breakpoint->addr);	
	if (LogOff_) { /// we will Enable Log on BP just so we make DisableLog
		GuiDisableLog();
	}
}

PLUG_EXPORT void CBRESUMEDEBUG(CBTYPE cbType, PLUG_CB_RESUMEDEBUG* info)
{
	if (LogOff_) { /// we will Enable Log on BP just so we make DisableLog
		GuiDisableLog();
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
