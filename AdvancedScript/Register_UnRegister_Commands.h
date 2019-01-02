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
static bool VarxClear(int argc, char* argv[]);
static bool StrCompx(int argc, char* argv[]);
//Script Functions 
static bool Varx(int argc, char* argv[]);
static bool GetVarx(int argc, char* argv[]);
static bool SetVarx(int argc, char* argv[]);
static bool Movx(int argc, char* argv[]);
static bool addx(int argc, char* argv[]);
static bool subx(int argc, char* argv[]);
static bool mulx(int argc, char* argv[]);
static bool divx(int argc, char* argv[]);
static bool andx(int argc, char* argv[]);
static bool orx(int argc, char* argv[]);
static bool xorx(int argc, char* argv[]);
static bool shlx(int argc, char* argv[]);
static bool pushx(int argc, char* argv[]);
static bool popx(int argc, char* argv[]);
static bool cmpx(int argc, char* argv[]);

///
static bool findx(int argc, char* argv[]);
static bool findallx(int argc, char* argv[]);
static bool findallmemx(int argc, char* argv[]);

static bool memdump(int argc, char* argv[]);
///////////////////////
System::Void LoadTemplateFiles_();





