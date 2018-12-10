#pragma once
#include "PluginBasic.h"
extern int pluginHandle;
void RegisterCommands(PLUG_INITSTRUCT* initStruct);
static bool cbMainForm(int argc, char* argv[]);
static bool cbLogxJustAtBP(int argc, char* argv[]);
static bool test(int argc, char* argv[]);
static bool LogxTemplateManager(int argc, char* argv[]);
static bool logx(int argc, char* argv[]);
static bool logx_window(int argc, char* argv[]);
static bool logxTrace(int argc, char* argv[]);
static void StrComp_BP();
static bool StrCompx(int argc, char* argv[]);
///////////////////////
System::Void LoadTemplateFiles_();





