#pragma once
#include "PluginBasic.h"

using namespace System;
using namespace Microsoft::VisualBasic;
using namespace Runtime::InteropServices;
using namespace System::Collections;

///////////////////////////////////////////////////////////////////Helper Functions
String^ reMoveSpaces(String^ input_);
String^ CharArr2Str(char input_[]);
String^ duint2Hex(duint input_);
String^ charPTR2String(char* input);
String^ ClearSlash_etc(String^ input);
String^ GetAPIName_LableWay(duint Addr_);

duint Hex2duint(String^ input_);

const char* Str2ConstChar(System::String^ string_);
bool Str2bool(String^ input_);
bool OnlyHexInString(String^ test);
char* StringFormatInline_(String^ format);
String^ StringFormatInline_Str(String^ format);

System::Void GetArg(String^ input, Generic::List<String^>^% arguments);

///////////////////////////////////////////////////////////////////Helper Functions
ref class MyException : public System::Exception {};


