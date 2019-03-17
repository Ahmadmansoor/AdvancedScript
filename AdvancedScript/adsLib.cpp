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
		"SectionBegin","SectionEnd" };
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
			if ((findrest->Contains("$")) || (findrest->Contains("{")) || (findrest->Contains("ads."))) { // in case resolve value form x64dbg system
				findrest = StrAnalyze(findrest, VarType::str, false);
				//return  "0x" + duint2Hex(Script::Module::BaseFromName(Str2ConstChar(findrest)));
				String^ intvalue;  /// first if it is hex value
				if (CheckHexIsValid(findrest, intvalue) > 0) {  /// it mean it is address ( hex value)
					return  "0x" + duint2Hex(Script::Module::BaseFromAddr(Str2int(intvalue)));  // resolve it as hex address 
				}
				else
				{
					return  "0x" + duint2Hex(Script::Module::BaseFromName(Str2ConstChar(findrest)));// resolve it as name of module 
				}
			}
			String^ intvalue;
			if (CheckHexIsValid(findrest, intvalue) > 0) {  /// it mean it is address ( hex value)
				return  "0x" + duint2Hex(Script::Module::BaseFromAddr(Str2int(intvalue)));
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
			_plugin_logprint(Str2ConstChar(Environment::NewLine + "no () After command(modulebase) of ads."));
			EndB = ConstCommand->Length;
			return "NULL/ ";
		}
		else
		{
			EndB = ConstCommand->Length + findrest->LastIndexOf(")") + 1;  // +1  to include ")"
			findrest = findrest->Substring(1, findrest->LastIndexOf(")") - 1); // remove ()
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
				_plugin_logprint(Str2ConstChar(Environment::NewLine + "can't resolve name or address after command(modulebase) of ads"));
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
			return "NULL/ ";
		break;
	}
	case exename: {
		EndB = ConstCommand->Length;
		char* exename = new char[MAX_STRING_SIZE];
		if (Script::Module::GetMainModuleName(exename))
			return CharArr2Str(exename);
		else
			return "NULL/ ";
		break;
	}
	case SectionBegin:  // ( address)
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
			if ((findrest->Contains("$")) || (findrest->Contains("{")) || (findrest->Contains("ads."))) { // in case resolve value form x64dbg system
				findrest = StrAnalyze(findrest, VarType::str, false);
				String^ intvalue;
				if (CheckHexIsValid(findrest, intvalue) > 0) {  /// it mean it is address ( hex value)
					return  "0x" + duint2Hex(Script::Memory::GetBase(Hex2duint(findrest)));
				}
				else
				{
					_plugin_logprint(Str2ConstChar(Environment::NewLine + "can't resolve name or address after command(modulebase) of ads"));
					return "NULL/ ";
				}
			}
			String^ intvalue;
			if (CheckHexIsValid(findrest, intvalue) > 0) {  /// it mean it is address ( hex value)
				return  "0x" + duint2Hex(Script::Memory::GetBase(Hex2duint(findrest)));
			}
			else
			{
				_plugin_logprint(Str2ConstChar(Environment::NewLine + "can't resolve name or address after command(modulebase) of ads"));
				return "NULL/ ";
			}
		}
		break;
	}

	case SectionEnd:
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
			if ((findrest->Contains("$")) || (findrest->Contains("{")) || (findrest->Contains("ads."))) { // in case resolve value form x64dbg system
				findrest = StrAnalyze(findrest, VarType::str, false);
				String^ intvalue;
				if (CheckHexIsValid(findrest, intvalue) > 0) {  /// it mean it is address ( hex value)
					duint EndSec = Script::Memory::GetSize(Hex2duint(findrest)) + Script::Memory::GetBase(Hex2duint(findrest));
					return  "0x" + duint2Hex(EndSec);
				}
				else
				{
					_plugin_logprint(Str2ConstChar(Environment::NewLine + "can't resolve name or address after command(modulebase) of ads"));
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
				_plugin_logprint(Str2ConstChar(Environment::NewLine + "can't resolve name or address after command(modulebase) of ads"));
				return "NULL/ ";
			}
		}
		break;
	}
	default: {
		_plugin_logprint(Str2ConstChar(Environment::NewLine + "no known command after ads."));
		EndB = ConstCommand->Length;
		return "NULL/ ";
		break;
	}
	}


}