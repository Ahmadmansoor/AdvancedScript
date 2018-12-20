#pragma once
#include "Parser.h"
#include "ScriptFun.h"
#include "LogTemplate.h"

//////////////////////////////////////////////
//notes:
//- all numbers are decimal
//- all hex numbers are begin with 0x  x small latter

//////////////////////////////////////////////

int GetRegisterIndex(String^ input_) {
	array <String^>^ RegisterEnum_ = { "DR0" ,"DR1" ,"DR2" ,"DR3" ,"DR6" ,
		"DR7" ,"EAX" ,"AX" ,"AH" ,"AL" ,"EBX" ,"BX" ,"BH" ,"BL" ,"ECX" ,
		"CX" ,"CH" ,"CL" ,"EDX" ,"DX" ,"DH" ,"DL" ,"EDI" ,"DI" ,"ESI" ,
		"SI" ,"EBP" ,"BP" ,"ESP" ,"SP" ,"EIP" ,"RAX" ,"RBX" ,"RCX" ,"RDX" ,
		"RSI" ,"SIL" ,"RDI" ,"DIL" ,"RBP" ,"BPL" ,"RSP" ,"SPL" ,"RIP" ,
		"R8" ,"R8D" ,"R8W" ,"R8B" ,"R9" ,"R9D" ,"R9W" ,"R9B" ,"	R10" ,"R10D" ,
		"R10W" ,"R10B" ,"R11" ,"R11D" ,"R11W" ,"R11B" ,"R12" ,"R12D" ,"R12W" ,
		"R12B" ,"R13" ,"R13D" ,"R13W" ,"R13B" ,"R14" ,"R14D" ,"R14W" ,"R14B" ,
		"R15" ,"R15D" ,"R15W" ,"R15B" ,"CIP" ,"CSP" ,"CAX" ,"CBX" ,"CCX" ,"CDX" ,
		"CDI" ,"CSI" ,"CBP" ,"	CFLAGS" };

	return RegisterEnum_->IndexOf(RegisterEnum_, input_); // if -1 then not found 
}

String^ readVarName(String^ input, int arrayIndex, String^% VarString2Replace) {
	String^ temp = input;
	String^ value_ = "";
	String^ value_1 = "";
	String^ vartype = "";
	int index_ = 0;
	int index_t = 0;
	for (size_t i = 0; i < temp->Length; i++)
	{
		value_ = value_ + temp->Substring(i, 1);
		if (i + 1 == temp->Length) {	/// if this later is the end of string 
			if (Varexist(value_, vartype, index_)) {
				VarString2Replace = value_;
				return ScriptFunList::VarList[index_]->varvalue[arrayIndex];
			}
			else {
				return "NULL/ ";
			}
		}
		//if (i + 1 < temp->Length) {
		if (temp->Substring(i + 1, 1) == " ") { /// if the next letter is space
			if (Varexist(value_, vartype, index_)) {
				VarString2Replace = value_;
				return ScriptFunList::VarList[index_]->varvalue[arrayIndex];
			}
		}
		//}
		/*else {
			return "NULL/ ";
		}*/
		value_1 = value_1 + temp->Substring(i + 1, 1);
		if ((Varexist(value_, vartype, index_)) && (!Varexist(value_1, vartype, index_t))) {
			VarString2Replace = value_;
			return ScriptFunList::VarList[index_]->varvalue[arrayIndex];
		}
	}
	return "NULL/ ";
}

String^ findVarValue(String^ input, String^% VarString) {  /// find the variable begin with $ like $x or $x[1]  // this VarString will used for replacing string
	String^ ArrayIndexValue = "";
	String^ var_ = "";
	String^ vartype_ = ""; int indexofVar = 0;
	if (!input->Contains("$")) {
		return "NULLx/ no Variable name";  // this mean there are no variable in this string
	}
	else {
		VarString = "$";
		input = input->Substring(1, input->Length - 1);  // we reomved $ from the begining 
	}
	if (input->IndexOf("[") > 0) {  // variable is Array  /// must be bigger than 0 because var has name ;)			
		var_ = input->Substring(0, input->IndexOf("[") - 1);  // get Var name	
		/// need to check if this value is variable too we need to pass it to argumentValue
		String^ OldValue_;
		var_ = argumentValue(var_, OldValue_);
		if (var_->StartsWith("NULL/ ")) {
			return "NULL/ Can't resolve index of the variable" + input;
		}
		if (Varexist(var_->Trim(), vartype_, indexofVar)) { /// check if var exist  // we clear space here just , because we need to build VarString
			if (vartype_ == "array" && input->IndexOf("]") > 0) { // var type must be array and the rest of string must have close ]
				for (size_t i = input->IndexOf("[") + 1; i < input->Length; i++) //get index of var
				{
					if (input->Substring(i, 1) != "]") {
						ArrayIndexValue = ArrayIndexValue + input->Substring(i, 1);
					}
					else {
						VarString = VarString + var_ + input->Substring(input->IndexOf("["), input->Length - input->IndexOf("]", input->IndexOf("["))); // this is the end index of var we will used later to replace string
						break;
					}
				}
				String^ OldValue_;
				ArrayIndexValue = argumentValue(ArrayIndexValue, OldValue_);  /// now check if the index, maybe Numeric or variable
				if (ArrayIndexValue->StartsWith("NULL/")) {
					return "NULL/ something go wrong";
				}
				if (!Information::IsNumeric(ArrayIndexValue)) {
					return "NULL/ array index is not Numeric";/// that something wrong in the index of the array 
				}
				else {
					int ArrayIndexValue_ = Conversion::Val(ArrayIndexValue);
					return ScriptFunList::VarList[indexofVar]->varvalue[ArrayIndexValue_]; // return the value of the array var
				}
			}
			else
			{
				return "NULL/ Variable not as an array in the list, or u missing ]";/// that something wrong in the index of the array 
			}
		}
		else {
			return "NULL/ Variable not in the list";/// that something wrong in the index of the array 
		}
	}
	if (input->IndexOf(" ") > 0) {  /// var is int or str		
		var_ = input->Substring(0, input->IndexOf(" "));  // get Var name	and clear spaces	
		if (Varexist(var_->Trim(), vartype_, indexofVar)) { /// check if var exist	
			VarString = "$" + var_; // this is the end index of var we will used later to replace string
			return ScriptFunList::VarList[indexofVar]->varvalue[0]; // return the value of the var					
		}
		else {
			/// there are space but the string till space not have value or variable 
			//return "NULL/ could'nt get the Variable name";
			var_ = input;  // get Var name	and clear spaces
						   /// we need to find the variable like getvarx y,$x*1
						   /// $x*1  after $ >> x*1 so no space here so we need to find var by tokens
			var_ = readVarName(var_, 0, VarString);  ////<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			if (!var_->StartsWith("NULL/ ")) { /// check if var exist			
				VarString = "$" + VarString; // Get the old string which we will replce later
				return var_;
			}
			else {
				return "NULL/ Variable not in the list";
			}
		}
	}
	else {  /// there are no space at the end we need to search the rest of the string
	   //return "NULL/ could'nt get the Variable name";
		var_ = input;  // get Var name	and clear spaces
		/// we need to find the variable like getvarx y,$x*1
		/// $x*1  after $ >> x*1 so no space here so we need to find var by tokens
		var_ = readVarName(var_, 0, VarString);  ////<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		if (!var_->StartsWith("NULL/ ")) { /// check if var exist			
			VarString = "$" + VarString; // Get the old string which we will replce later
			return var_;
		}
		else {
			return "NULL/ Variable not in the list";
		}
	}
	return "NULL/ no Variable name";  // this mean there are no variable in this string 
}

String^ findScriptSystemVarValue(String^ input) {
	if (input->IndexOf("}") > 0) {
		//String^ VarString = input->Substring(input->IndexOf("{", input->Length - input->IndexOf("}")));
		return StringFormatInline_Str(input);
	}
	else
	{
		return "NULL/ Missing } at the end";
	}


}

String^ ForWard(String^ input, int tokenindex, String^% VarString) { /// tokenindex is hold the index of token
	String^ temp = input;
	String^ value_ = "";
	String^ value_1 = ""; // we used to check if we need to go more far like 5 * 23 ]	
	String^ OldValue_;
	if (tokenindex + 1 > input->Length) {
		return "NULL/ ";  /// token at the end of string
	}
	else
	{
		if (temp->Substring(tokenindex, 1) == " ") { /// if the next char of token is space we skip it  note we add 1 to tokenindex , so we are at next chat of token
			temp = temp->Substring(tokenindex + 1, temp->Length - (tokenindex + 1));  /// we pass this First space
			VarString = " ";
		}
		else {
			temp = temp->Substring(tokenindex, temp->Length - tokenindex); /// take all string after tokenindex
		}
		for (size_t i = 0; i < temp->Length; i++)
		{
			value_ = value_ + temp->Substring(i, 1);
			if (i + 1 == temp->Length) { /// if this later is the end of string 
				VarString = VarString + value_;  /// in case VarString hold space
				return argumentValue(value_->Trim(), OldValue_);
			}
			if (temp->Substring(i + 1, 1) == " ") {  /// as there are still some char's left (i + 1 > 0)	
				VarString = VarString + value_;  /// in case VarString hold space 
				return argumentValue(value_->Trim(), OldValue_);
			}

			array <String^>^ tokens_ = { "*" ,"+","-","/" };
			//tokens_->IndexOf(tokens_, temp->Substring(i + 1, 1));
			//if ( temp->Substring(i + 1, 1) == " ") {  /// as there are still some char's left (i + 1 > 0)	
			if (tokens_->IndexOf(tokens_, temp->Substring(i + 1, 1)) >0 ) {  /// as there are still some char's left (i + 1 > 0)	
				VarString = VarString + value_;  /// in case VarString hold space 

				return "NULL/ ";
			}

			value_1 = value_ + temp->Substring(i + 1, 1);
			if ((!argumentValue(value_, OldValue_)->StartsWith("NULL/ ")) && (argumentValue(value_1, OldValue_)->StartsWith("NULL/ "))) {
				VarString = VarString + value_1;
				return argumentValue(value_1->Trim(), OldValue_);
			}
		}
	}
	return "NULL/ ";
}

String^ BackWard(String^ input, int tokenindex, String^% VarString) {
	String^ temp = input;
	String^ value_ = "";
	String^ value_1 = ""; // we used to check if we need to go more far like [55 * 23 ]
	String^ OldValue_;
	if (tokenindex - 1 < 0)
		return "NULL/ ";  /// token at the begin of string
	else {
		if (temp->Substring(tokenindex - 1, 1) == " ") {  /// if the before char of token is space we skip it 
			temp = temp->Substring(0, tokenindex - 1); /// begin from after space  like  55 +
			VarString = " ";
		}
		else {
			temp = temp->Substring(0, tokenindex); /// then we get the rest of the string form index 0 till the token index
			//VarString = temp;
		}
		for (size_t i = temp->Length; i > 0; i--)
		{
			value_ = temp->Substring(i - 1, 1) + value_;
			if (i - 1 == 0) {
				VarString = value_ + VarString;  /// in case VarString hold space 
				return argumentValue(value_->Trim(), OldValue_);
			}
			if (temp->Substring(i - 1, 1) == " ") { /// as there are still some char's left (i - 1 > 0)
				VarString = value_ + VarString;  /// in case VarString hold space 
				return argumentValue(value_->Trim(), OldValue_);
			}
			value_1 = temp->Substring(i - 2, 1) + value_;  /// we check the next char with previous one if it can have a value or related variable
			if ((!argumentValue(value_->Trim(), OldValue_)->StartsWith("NULL/ ")) && (argumentValue(value_1->Trim(), OldValue_)->StartsWith("NULL/ "))) {
				VarString = value_1 + VarString;
				return argumentValue(value_1->Trim(), OldValue_);
			}
		}
	}
	return "NULL/ ";
}

String^ tokens(String^ input, String^% VarString) {
	// check for * first 
	String^ VarString1 = "";
	String^ VarString2 = "";
	String^ para1 = ""; 	String^ para2 = "";

	if (input->IndexOf("*") > 0) { /// should be bigger than 0 , token should not be at the begining of the exprsion 		
		para1 = BackWard(input, input->IndexOf("*"), VarString1);
		para2 = ForWard(input, input->IndexOf("*") + 1, VarString2);  // we begin after token
		VarString = VarString1 + "*" + VarString2;
		if ((!Information::IsNumeric(para1)) || !Information::IsNumeric(para2))
			return "NULL/ ";
		else
			return Conversion::Str(Conversion::Val(para1) * Conversion::Val(para2));
	}

	if (input->IndexOf("/") > 0) { /// should be bigger than 0 , token should not be at the begining of the exprsion 		
		para1 = BackWard(input, input->IndexOf("/"), VarString1);
		para2 = ForWard(input, input->IndexOf("/") + 1, VarString2);
		VarString = VarString1 + "+" + VarString2;
		if ((!Information::IsNumeric(para1)) || !Information::IsNumeric(para2))
			return "NULL/ ";
		else
			return Conversion::Str(Conversion::Val(para1) / Conversion::Val(para2));

	}

	if (input->IndexOf("+") > 0) { /// should be bigger than 0 , token should not be at the begining of the exprsion 		
		para1 = BackWard(input, input->IndexOf("+"), VarString1);
		para2 = ForWard(input, input->IndexOf("+") + 1, VarString2);
		VarString = VarString1 + "+" + VarString2;

		if ((!Information::IsNumeric(para1)) || !Information::IsNumeric(para2)) {	
			_plugin_logprint("one of this arguments are not numeric");
			return "NULL/ ";
		}
		else
			return Conversion::Str(Conversion::Val(para1) + Conversion::Val(para2));
	}

	if (input->IndexOf("-") > 0) { /// should be bigger than 0 , token should not be at the begining of the exprsion 		
		para1 = BackWard(input, input->IndexOf("-"), VarString1);
		para2 = ForWard(input, input->IndexOf("-") + 1, VarString2);
		VarString = VarString1 + "+" + VarString2;
		if ((!Information::IsNumeric(para1)) || !Information::IsNumeric(para2))
			return "NULL/ ";
		else
			return Conversion::Str(Conversion::Val(para1) - Conversion::Val(para2));

	}

}

String^ findHexValue(String^ input) {
	String^ temp;
	if (input->IndexOf("0x") >= 0) {
		input = input->Substring(input->IndexOf("0x") + 2, input->Length - (input->IndexOf("0x") + 2));
	}
	else
	{
		return "NULL/ ";
	}
	for (size_t i = 0; i < input->Length; i++)
	{
		if (CheckHexIsValid(input->Substring(i, 1))) {
			temp = temp + input->Substring(i, 1);
			if (i + 1 < input->Length) {
				if (!CheckHexIsValid(input->Substring(i+1, 1))) {
					return temp;
				}
			}
		}
	}
	return temp;
}

String^ resolveString(String^ input, int% commaCount) {
	String^ temp = "";
	
	for (size_t i = 0; i < input->Length; i++)
	{
		if (input->Substring(i, 1) == "\"") {
			commaCount += 1;
		}
	}
	if (commaCount % 2 != 0) {  /// check if there is an open comma for each comma
		commaCount = 0;
		return input;
	}

	for (size_t i = 0; i < input->Length; i++)
	{
		if (input->Substring(i, 1) != "\"") {
			temp = temp + input->Substring(i, 1);
		}
		else
		{
			String^ OldValue_;
			temp = argumentValue(temp, OldValue_);  /// reolve this str in case it return NULL we take the old value (which could be half resolved)
			if (temp->StartsWith("NULL/ ")) {
				temp = OldValue_;
			}
			int NextCommaIndex = input->IndexOf("\"", i + 1);
			String^ StringafterComma = input->Substring(i+1 , NextCommaIndex - (i+1)) ;
			temp = temp + StringafterComma;
			i = i + NextCommaIndex + 1;  /// now jmp to the next comma
		}
	}
	return temp;
}

String^ argumentValue(String^ argument, String^% OldValue_) {  /// return the <<int>> value of the argument as string
	//String^ Originalargument = argument;
	OldValue_ = ""; // rest the value
	if (Information::IsNumeric(argument)) {   /// check if int number
		return argument;
	}
	if (argument->IndexOf("0x") >= 0) {  /// check if hex
		while (argument->IndexOf("0x") >= 0) {
			String^ replaceValue = "";
			String^ oldvalue = argument->Substring(argument->IndexOf("0x"), argument->Length - argument->IndexOf("0x"));
			replaceValue = int2Str(Hex2duint(findHexValue(oldvalue)));
			OldValue_ = oldvalue;
			if (!replaceValue->StartsWith("NULL/")) {
				argument = ReplaceAtIndex(argument, oldvalue, replaceValue);
			}
			else			
				return "NULL/ ";
		}
	}

	if ((argument->IndexOf("{") >= 0) && (argument->IndexOf("}", argument->IndexOf("{")) >= 0)) {
		while (argument->IndexOf("{") >= 0) {
			String^ replaceValue = "";
			String^ oldvalue = argument->Substring(argument->IndexOf("{"), argument->IndexOf("}") + 1);
			replaceValue = findScriptSystemVarValue(oldvalue);
			OldValue_ = oldvalue;
			if (!replaceValue->StartsWith("NULL/")) {
				argument = ReplaceAtIndex(argument, oldvalue, replaceValue);
			}
			else
			{
				return "NULL/ ";
			}

		}
	}
	/// find Variables Local System from VarList ,all variable should have $ at the begining like $x or $x[1]
	if (argument->Contains("$")) {
		while (argument->IndexOf("$") >= 0)
		{
			String^ tempInput = argument;
			String^ oldValue = "";
			tempInput = tempInput->Substring(tempInput->IndexOf("$"), tempInput->Length - tempInput->IndexOf("$"));
			tempInput = findVarValue(tempInput, oldValue);
			OldValue_ = oldValue;
			if (tempInput->StartsWith("NULL/")) {
				_plugin_logprint(Str2ConstChar(tempInput));
				return "NULL/ ";
			}
			else {
				//argument = argument->Replace (VarString, tempInput);
				argument = ReplaceAtIndex(argument, oldValue, tempInput);
			}
		}
	}

	//////////////////////////////////////
	int commaCount = 0;
	argument = resolveString(argument, commaCount);
	//////////////////////////////////////
	if ((argument->Contains("*")) || (argument->Contains("+")) || (argument->Contains("-")) || (argument->Contains("/"))) {  /// I will do it later
		while ((argument->Contains("*")) || (argument->Contains("+")) || (argument->Contains("-")) || (argument->Contains("/")))
		{
			String^ tempInput = argument;
			String^ oldValue = "";
			int commaCount;			
			tempInput = tokens(tempInput, oldValue);
			//OldValue_ = oldValue;
			if (tempInput->StartsWith("NULL/")) {
				OldValue_ = argument;
				_plugin_logprint(Str2ConstChar(tempInput));
				return "NULL/ ";
			}
			else {
				argument = ReplaceAtIndex(argument, oldValue, tempInput);
			}
		}
	}

	/*if (Originalargument == argument) {
		_plugin_logprint("This argument not pass the check");
		return "NULL/ ";
	}*/

	return argument;
}



bool CheckexcutedCmd(String^ cmd_) {
	Generic::List<String^>^ arguments;
	AdvancedScript::LogTemplate::TemplateClass^ TemplateClassFound;
	String^ OldValue_;

	if (cmd_->StartsWith("mem(") || cmd_->StartsWith("mem (")) {
		GetArg(cmd_->Substring(cmd_->IndexOf("("), cmd_->Length - cmd_->IndexOf("(")), arguments, true);
		String^ addr = argumentValue(arguments[0], OldValue_);
		String^ Size_ = argumentValue(arguments[1], OldValue_);
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
	}
	_plugin_logprint(Str2ConstChar(argumentValue(cmd_, OldValue_)));
	return true;
}

