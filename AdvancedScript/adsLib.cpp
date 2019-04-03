#pragma once
#include "adsLib.h"
#include "Parser.h"
#include "ScriptFun.h"


String^ Get_adsValue(String^ input, int% EndB) {
	bool found = false;
	int ConstIndex = -1;
	String^ ConstCommand;
	
	if (input->StartsWith(" ")) {
		_plugin_logprint(Str2ConstChar(Environment::NewLine + "space exist After ads."));
		return "NULL/ ";
	}

	String^ input_ = input->ToLower()->Trim();
	array <String^>^ ListConst = { "exebase","modulebase","SectionSize","exefolderpath","exename",
		"SectionBegin","SectionEnd","GetAPIName","GetArraySize","ReadStr","GetdesCallJmp","isInArray","isAddrBelongSection" };
	//// we we add item to the list go to Ads_Variables_AutoCompleteLoad and add line to add it to autocomplete
	for (int i = 0; i < ListConst->Length; i++)
	{
		if (input_->StartsWith(ListConst[i]->ToLower())) {
			ConstIndex = i;
			ConstCommand = ListConst[i];
			found = true;
			break;
		}
	}
	if (!found)
		return "NULL/ ";
	switch (ConstIndex)
	{
	case exebase: {
		///EndB = input->IndexOf(ConstCommand) + ConstCommand->Length; in case have begin with space
		EndB = ConstCommand->Length;
		return "0x" + duint2Hex(Script::Module::GetMainModuleBase());
		break;
	}
	case modulebase:  /// (name of module or address )
	{
		String^ findrest = input_->Substring(ConstCommand->Length, input_->Length - ConstCommand->Length);
		if ((!findrest->Contains("(")) && (!findrest->Contains(")"))) {
			_plugin_logprint(Str2ConstChar(Environment::NewLine + "no () After command(modulebase) of ads."));
			EndB = ConstCommand->Length;
			return "NULL/ ";
		}
		else
		{
			EndB = ConstCommand->Length + findrest->LastIndexOf(")") + 1;  // +1  to include ")"
			findrest = findrest->Substring(1, findrest->LastIndexOf(")") - 1); // remove ()
			findrest = findrest->Trim();
			if ((findrest->Contains("$")) || (findrest->Contains("{")) || (findrest->Contains("ads."))) { // in case resolve value form x64dbg system
				findrest = StrAnalyze(findrest, VarType::str, false);
				//return  "0x" + duint2Hex(Script::Module::BaseFromName(Str2ConstChar(findrest)));
				String^ intvalue;  /// first if it is hex value
				if (CheckHexIsValid(findrest, intvalue) > 0) {  /// it mean it is address ( hex value)
					return  "0x" + duint2Hex(Script::Memory::GetBase(Str2int(intvalue)));  // resolve it as hex address 
				}
				else
				{
					return  "0x" + duint2Hex(Script::Module::BaseFromName(Str2ConstChar(findrest)));// resolve it as name of module 
				}
			}
			String^ intvalue;
			if (CheckHexIsValid(findrest, intvalue) > 0) {  /// it mean it is address ( hex value)
				return  "0x" + duint2Hex(Script::Memory::GetBase(Str2int(intvalue)));
			}
			else
			{
				_plugin_logprint(Str2ConstChar(Environment::NewLine + "can't resolve name or address after command(modulebase) of ads"));
				return "NULL/ ";
			}
		}
		break;
	}
	case SectionSize:		// (address)
	{
		String^ findrest = input_->Substring(ConstCommand->Length, input_->Length - ConstCommand->Length);
		if ((!findrest->Contains("(")) && (!findrest->Contains(")"))) {
			_plugin_logprint(Str2ConstChar(Environment::NewLine + "no () After command(SectionSize) of ads."));
			EndB = ConstCommand->Length;
			return "NULL/ ";
		}
		else
		{
			EndB = ConstCommand->Length + findrest->LastIndexOf(")") + 1;  // +1  to include ")"
			findrest = findrest->Substring(1, findrest->LastIndexOf(")") - 1); // remove ()
			findrest = findrest->Trim();
			if ((findrest->Contains("$")) || (findrest->Contains("{")) || (findrest->Contains("ads."))) { // in case resolve value form x64dbg system
				findrest = StrAnalyze(findrest, VarType::str, false);
				//return  "0x" + duint2Hex(Script::Module::SizeFromAddr(Str2ConstChar(findrest)));
			}
			String^ intvalue;
			if (CheckHexIsValid(findrest, intvalue) > 0) {  /// it mean it is address ( hex value)
				return  "0x" + duint2Hex(Script::Memory::GetSize(Hex2duint(findrest)));
			}
			else
			{
				_plugin_logprint(Str2ConstChar(Environment::NewLine + "can't resolve address after command(SectionSize) of ads"));
				return "NULL/ ";
			}
		}
		break;
	}
	case exefolderpath: {
		EndB = ConstCommand->Length;
		char* path_ = new char[MAX_STRING_SIZE];
		if (Script::Module::GetMainModulePath(path_))
			return CharArr2Str(path_);
		else
			_plugin_logprint(Str2ConstChar(Environment::NewLine + "couldn't get the path"));
			return "NULL/ ";
		break;
	}
	case exename: {
		EndB = ConstCommand->Length;
		char* exename = new char[MAX_STRING_SIZE];
		if (Script::Module::GetMainModuleName(exename))
			return CharArr2Str(exename);
		else
			_plugin_logprint(Str2ConstChar(Environment::NewLine + "couldn't get the name"));
			return "NULL/ ";
		break;
	}
	case SectionBegin:  // ( address)
	{
		String^ findrest = input_->Substring(ConstCommand->Length, input_->Length - ConstCommand->Length);
		if ((!findrest->Contains("(")) && (!findrest->Contains(")"))) {
			_plugin_logprint(Str2ConstChar(Environment::NewLine + "no () After command(SectionBegin) of ads."));
			EndB = ConstCommand->Length;
			return "NULL/ ";
		}
		else
		{
			EndB = ConstCommand->Length + findrest->LastIndexOf(")") + 1;  // +1  to include ")"
			findrest = findrest->Substring(1, findrest->LastIndexOf(")") - 1); // remove ()
			findrest = findrest->Trim();
			if ((findrest->Contains("$")) || (findrest->Contains("{")) || (findrest->Contains("ads."))) { // in case resolve value form x64dbg system
				findrest = StrAnalyze(findrest, VarType::str, false);
				String^ intvalue;
				if (CheckHexIsValid(findrest, intvalue) > 0) {  /// it mean it is address ( hex value)
					return  "0x" + duint2Hex(Script::Memory::GetBase(Hex2duint(findrest)));
				}
				else
				{
					_plugin_logprint(Str2ConstChar(Environment::NewLine + "can't resolve  address after command(SectionBegin) of ads"));
					return "NULL/ ";
				}
			}
			String^ intvalue;
			if (CheckHexIsValid(findrest, intvalue) > 0) {  /// it mean it is address ( hex value)
				return  "0x" + duint2Hex(Script::Memory::GetBase(Hex2duint(findrest)));
			}
			else
			{
				_plugin_logprint(Str2ConstChar(Environment::NewLine + "can't resolve address after command(SectionBegin) of ads"));
				return "NULL/ ";
			}
		}
		break;
	}

	case SectionEnd:  // ( address)
	{
		String^ findrest = input_->Substring(ConstCommand->Length, input_->Length - ConstCommand->Length);
		if ((!findrest->Contains("(")) && (!findrest->Contains(")"))) {
			_plugin_logprint(Str2ConstChar(Environment::NewLine + "no () After command(SectionEnd) of ads."));
			EndB = ConstCommand->Length;
			return "NULL/ ";
		}
		else
		{
			EndB = ConstCommand->Length + findrest->LastIndexOf(")") + 1;  // +1  to include ")"
			findrest = findrest->Substring(1, findrest->LastIndexOf(")") - 1); // remove ()
			findrest = findrest->Trim();
			if ((findrest->Contains("$")) || (findrest->Contains("{")) || (findrest->Contains("ads."))) { // in case resolve value form x64dbg system
				findrest = StrAnalyze(findrest, VarType::str, false);
				String^ intvalue;
				if (CheckHexIsValid(findrest, intvalue) > 0) {  /// it mean it is address ( hex value)
					duint EndSec = Script::Memory::GetSize(Hex2duint(findrest)) + Script::Memory::GetBase(Hex2duint(findrest));
					return  "0x" + duint2Hex(EndSec);
				}
				else
				{
					_plugin_logprint(Str2ConstChar(Environment::NewLine + "can't resolve address after command(SectionEnd) of ads"));
					return "NULL/ ";
				}
			}
			String^ intvalue;
			if (CheckHexIsValid(findrest, intvalue) > 0) {  /// it mean it is address ( hex value)
				duint EndSec = Script::Memory::GetSize(Hex2duint(findrest)) + Script::Memory::GetBase(Hex2duint(findrest));
				return  "0x" + duint2Hex(EndSec);
			}
			else
			{
				_plugin_logprint(Str2ConstChar(Environment::NewLine + "can't resolve address after command(SectionEnd) of ads"));
				return "NULL/ ";
			}
		}
		break;
	}
	case GetAPIName_:  // ( address)
	{
		String^ findrest = input_->Substring(ConstCommand->Length, input_->Length - ConstCommand->Length);
		if ((!findrest->Contains("(")) && (!findrest->Contains(")"))) {
			_plugin_logprint(Str2ConstChar(Environment::NewLine + "no () After command(GetAPIName) of ads."));
			EndB = ConstCommand->Length;
			return "NULL/ ";
		}
		else
		{
			EndB = ConstCommand->Length + findrest->LastIndexOf(")") + 1;  // +1  to include ")"
			findrest = findrest->Substring(1, findrest->LastIndexOf(")") - 1); // remove ()
			findrest = findrest->Trim();
			if ((findrest->Contains("$")) || (findrest->Contains("{")) || (findrest->Contains("ads."))) { // in case resolve value form x64dbg system
				findrest = StrAnalyze(findrest, VarType::str, false);
				String^ intvalue;
				if (CheckHexIsValid(findrest, intvalue) > 0) {  /// it mean it is address ( hex value)					
					return  GetAPIName_LableWay(Hex2duint(findrest));
				}
				else
				{
					_plugin_logprint(Str2ConstChar(Environment::NewLine + "can't resolve address after command(GetAPIName) of ads"));
					return "NULL/ ";
				}
			}
			String^ intvalue;
			if (CheckHexIsValid(findrest, intvalue) > 0) {  /// it mean it is address ( hex value)
				return  GetAPIName_LableWay(Hex2duint(findrest));
			}
			else
			{
				_plugin_logprint(Str2ConstChar(Environment::NewLine + "can't resolve address after command(GetAPIName) of ads"));
				return "NULL/ ";
			}

			
		}
		break;
	}
	case GetArraySize__:  // ( address)
	{
		String^ findrest = input_->Substring(ConstCommand->Length, input_->Length - ConstCommand->Length);
		if ((!findrest->Contains("(")) && (!findrest->Contains(")"))) {
			_plugin_logprint(Str2ConstChar(Environment::NewLine + "no () After command(GetArraySize) of ads."));
			EndB = ConstCommand->Length;
			return "NULL/ ";
		}
		else
		{
			EndB = ConstCommand->Length + findrest->LastIndexOf(")") + 1;  // +1  to include ")"
			findrest = findrest->Substring(1, findrest->LastIndexOf(")") - 1); // remove ()			
			findrest = findrest->Trim();
			int indexofVar = 0; 	String^ retvartype = "";		int arrayLength;
			if ((Varexist(findrest->Trim(), retvartype, indexofVar, arrayLength)) && (findrest->StartsWith("$"))) {
				if (retvartype == "array") {
					_plugin_logputs(Str2ConstChar(Environment::NewLine + findrest + ": 0x" + duint2Hex(ScriptFunList::VarList[indexofVar]->arrayLength) + "/" + int2Str(ScriptFunList::VarList[indexofVar]->arrayLength)));
					return duint2Hex(ScriptFunList::VarList[indexofVar]->arrayLength);
				}
			}else
			{
				_plugin_logprint(Str2ConstChar(Environment::NewLine + "this is not array "));
				return "NULL/ ";
			}
		}
		break;
	}
	case ReadStr__:  // ( address)
	{
		String^ findrest = input_->Substring(ConstCommand->Length, input_->Length - ConstCommand->Length);
		if ((!findrest->Contains("(")) || (!findrest->Contains(")"))) {
			_plugin_logprint(Str2ConstChar(Environment::NewLine + "no () After command(GetArraySize) of ads."));
			EndB = ConstCommand->Length;
			return "NULL/ ";
		}
		else
		{
			EndB = ConstCommand->Length + findrest->LastIndexOf(")") + 1;  // +1  to include ")"
			findrest = findrest->Substring(1, findrest->LastIndexOf(")") - 1); // remove ()			
			findrest = findrest->Trim();

			String^ addr = StrAnalyze(findrest, VarType::str, true);
			String^ intValue;
			if (CheckHexIsValid(addr, intValue) == 0) {
				_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng address"));
				return "NULL/ ";
			}
			char* Read_Str2_ = new char[MAX_STRING_SIZE];
			if (DbgGetStringAt(Hex2duint(addr), Read_Str2_)) {
				String^ Read_Str2 = CharArr2Str(Read_Str2_);
				//return ReadStr_(arguments[0], Read_Str2);
				if (Read_Str2->Trim()->StartsWith("L\"")) {
					Read_Str2 = Read_Str2->Substring(2, Read_Str2->Length - 2);  /// remove L"
					if (Read_Str2->EndsWith("\""))
						Read_Str2 = Read_Str2->Substring(0, Read_Str2->Length - 1);  /// remove last "
				}
				if (Read_Str2->Trim()->StartsWith("\"")) {
					Read_Str2 = Read_Str2->Substring(1, Read_Str2->Length - 1);  /// remove "
					if (Read_Str2->EndsWith("\""))
						Read_Str2 = Read_Str2->Substring(0, Read_Str2->Length - 1);  /// remove last "
				}
				return Read_Str2;
			}
			else {
				_plugin_logputs(Str2ConstChar("Can't read the string at this address: " + addr));
				return  "NULL/ ";
			}
		}
		break;
	}
	case GetdesCallJmp__:  //(address)
	{
		String^ findrest = input_->Substring(ConstCommand->Length, input_->Length - ConstCommand->Length);
		if ((!findrest->Contains("(")) || (!findrest->Contains(")"))) {
			_plugin_logprint(Str2ConstChar(Environment::NewLine + "no () After command(GetdesCallJmp) of ads."));
			EndB = ConstCommand->Length;
			return "NULL/ ";
		}
		else
		{
			EndB = ConstCommand->Length + findrest->LastIndexOf(")") + 1;  // +1  to include ")"
			findrest = findrest->Substring(1, findrest->LastIndexOf(")") - 1); // remove ()			
			findrest = findrest->Trim();

			String^ addr = StrAnalyze(findrest, VarType::str, true);  /// resolve
			
			String^ addr_;
			BASIC_INSTRUCTION_INFO* basicinfo = new (BASIC_INSTRUCTION_INFO);
			DbgDisasmFastAt(Hex2duint(addr), basicinfo);
			String^ CallCommand = CharArr2Str(basicinfo->instruction);
			if ((!CallCommand->Trim()->ToLower()->StartsWith("call")) && (!CallCommand->Trim()->ToLower()->StartsWith("jmp"))) {
				return "NULL/ ";
			}
			if (CallCommand->Trim()->ToLower()->StartsWith("call")) {
				addr_ = CallCommand->Substring(4, CallCommand->Length - 4);
				return addr_;
			}
			if (CallCommand->Trim()->ToLower()->StartsWith("jmp")) {
				addr_ = CallCommand->Substring(3, CallCommand->Length - 3);
				return addr_;
			}
		}
		break;
	}

	case isInArray_:  //(text,arrayName)   /// used with if command
	{
		String^ findrest = input_->Substring(ConstCommand->Length, input_->Length - ConstCommand->Length);
		if ((!findrest->Contains("(")) && (!findrest->Contains(")"))) {
			_plugin_logprint(Str2ConstChar(Environment::NewLine + "no () After command(GetArraySize) of ads."));
			EndB = ConstCommand->Length;
			return "NULL/ ";
		}
		else
		{
			EndB = ConstCommand->Length + findrest->LastIndexOf(")") + 1;  // +1  to include ")"
			findrest = findrest->Substring(1, findrest->LastIndexOf(")") - 1); // remove ()			
			findrest = findrest->Trim();
			if (!findrest->Contains(",")) { // we need to check the argument 
				_plugin_logprint(Str2ConstChar(Environment::NewLine + "wrong arguments for (isInArray) of ads."));
				return "NULL/ ";
			}
			String^ argu1 = findrest->Substring(0, findrest->IndexOf(","));
			String^ argu2 = findrest->Substring(findrest->IndexOf(",")+1 , findrest->Length - (findrest->IndexOf(",") +1 ));
			argu1 = StrAnalyze(argu1, VarType::str, false);  /// resolve
			int indexofVar = 0; 	String^ retvartype = "";		int arrayLength;
			if ((Varexist(argu2->Trim(), retvartype, indexofVar, arrayLength)) && (argu2->StartsWith("$"))) {
				if (retvartype == "array") {
					for (int i = 0; i < ScriptFunList::VarList[indexofVar]->arrayLength; i++)
					{
						if (ScriptFunList::VarList[indexofVar]->varvalue[i]->ToLower()->Trim() == argu1->Trim()->ToLower()) {
							return "1";
						}
					}
					return "0";
				}
			}
			else
			{
				_plugin_logputs(Str2ConstChar(Environment::NewLine + "This is not array "));
				return "NULL/ ";
			}			
		}
		break;
	}

	case isAddrBelongSection:  //(addr,any addr of the section)   /// used with if command
	{
		String^ findrest = input_->Substring(ConstCommand->Length, input_->Length - ConstCommand->Length);
		if ((!findrest->Contains("(")) && (!findrest->Contains(")"))) {
			_plugin_logprint(Str2ConstChar(Environment::NewLine + "no () After command(GetArraySize) of ads."));
			EndB = ConstCommand->Length;
			return "NULL/ ";
		}
		else
		{
			EndB = ConstCommand->Length + findrest->LastIndexOf(")") + 1;  // +1  to include ")"
			findrest = findrest->Substring(1, findrest->LastIndexOf(")") - 1); // remove ()			
			findrest = findrest->Trim();
			if (!findrest->Contains(",")) { // we need to check the argument 
				_plugin_logprint(Str2ConstChar(Environment::NewLine + "wrong arguments for (isAddrBelongSection) of ads."));
				return "NULL/ ";
			}
			String^ argu1 = findrest->Substring(0, findrest->IndexOf(","));
			String^ argu2 = findrest->Substring(findrest->IndexOf(",") + 1, findrest->Length - (findrest->IndexOf(",") + 1));
			argu1 = StrAnalyze(argu1, VarType::str, false);  /// resolve
			argu2 = StrAnalyze(argu2, VarType::str, false);  /// resolve
			if ((argu1->Contains("NULL/")) || (argu2->Contains("NULL/"))) {
				_plugin_logprint(Str2ConstChar(Environment::NewLine + "can't resolve argumments"));
				return "NULL/ ";
			}
			duint SctionBegin; duint SctionEnd;
			SctionBegin = Script::Memory::GetBase(Hex2duint(argu2));
			SctionEnd = Script::Memory::GetSize(Hex2duint(argu2)) + Script::Memory::GetBase(Hex2duint(argu2));
			if ((Hex2duint(argu1) >= SctionBegin) && (Hex2duint(argu1) <= SctionEnd))
				return "1";			
			else
				return "0";

		}
		break;
	}

	default: {
		_plugin_logprint(Str2ConstChar(Environment::NewLine + "no known command after ads."));
		EndB = ConstCommand->Length;
		return "NULL/ ";
		break;
	}
			 return "NULL/ ";
	}


}