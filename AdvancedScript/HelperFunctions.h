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
duint Str2duint(String^ input_);
duint Hex2duint(String^ input_);
String^ str2Asci(String^ input);
String^ ReplaceAtIndex(String^  OriginalString, String^ oldValue, String^ newValue);
String^ AddZero2Addr(String^ input);

String^ str2Hex(String^ input);
bool IsAllSpaces(String^ input_);

template<class T>
String^ int2Str(T input_) {
	//if (Information::IsNumeric(input_)) {
		return Conversion::Str(input_);
	//}
	//return "NULL/ ";
}

const char* Str2ConstChar(System::String^ string_);
bool Str2bool(String^ input_);
int CheckHexIsValid(String^ input_, String^% intValue);
char* StringFormatInline_(String^ format);
String^ StringFormatInline_Str(String^ format);

enum VarType
{
	int_,
	str,
	array_,
};

VarType GetVarType(String^ vartype);

System::Void GetArg(String^ input, Generic::List<String^>^% arguments, bool brackets=false);

///////////////////////////////////////////////////////////////////Helper Functions
ref class MyException : public System::Exception {};


