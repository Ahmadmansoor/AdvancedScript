#pragma once
#include "PluginBasic.h"
extern int pluginHandle;
void RegisterCommands(PLUG_INITSTRUCT* initStruct);
static bool cbMainForm(int argc, char* argv[]);
static bool cbLogAtBP(int argc, char* argv[]);
static bool test(int argc, char* argv[]);
static bool LogTemplateManager(int argc, char* argv[]);