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
		value_1 = value_ + temp->Substring(i + 1, 1);
		if ((Varexist(value_, vartype, index_)) && (!Varexist(value_1, vartype, index_t))) {
			VarString2Replace = value_;
			return ScriptFunList::VarList[index_]->varvalue[arrayIndex];
		}
	}
	return "NULL/ ";
}

String^ findVarValue(String^ input, String^% VarString) {  /// find the variable begin with $ like $x or $x[1]  // this VarString will used for replacing string
	String^ ArrayIndexValue = "";
	String^ var_name = "";
	String^ vartype_ = ""; int indexofVar = 0;
	if (!input->Contains("$")) {
		return "NULLx/ no Variable name";  // this mean there are no variable in this string
	}
	else {
		VarString = "$";
		input = input->Substring(1, input->Length - 1);  // we reomved $ from the begining 
	}
	if ((input->IndexOf("[") > 0) && (input->IndexOf("$") < 0)) {  // variable is Array  /// we must check if there are another var ( contain $ ) so we not mix with other var's		
		var_name = input->Substring(0, input->IndexOf("["));  // get Var name	
		/// need to check if this value is variable too we need to pass it to argumentValue
		/*String^ OldValue_;
		var_name = argumentValue(var_name, OldValue_);
		if (var_name->StartsWith("NULL/ ")) {
			return "NULL/ Can't resolve the variable" + input;
		}*/
		if (Varexist(var_name->Trim(), vartype_, indexofVar)) { /// check if var exist  // we clear space here just , because we need to build VarString
			if (vartype_ == "array" && input->IndexOf("]") > 0) { // var type must be array and the rest of string must have close ]
				for (size_t i = input->IndexOf("[") + 1; i < input->Length; i++) //get index of var
				{
					if (input->Substring(i, 1) != "]") {
						ArrayIndexValue = ArrayIndexValue + input->Substring(i, 1);
					}
					else {
						//String^ xx = input->Substring(0, input->IndexOf("]"));
						VarString = VarString + input; // this is the end index of var we will used later to replace string
						break;
					}
				}
				String^ OldValue_;
				ArrayIndexValue = argumentValue(ArrayIndexValue, OldValue_);  /// now check if the index, maybe Numeric or variable
				if (ArrayIndexValue->StartsWith("NULL/")) {
					return "NULL/ something go wrong in resolve index";
				}
				/*if (!Information::IsNumeric(ArrayIndexValue)) {
					return "NULL/ array index is not Numeric";/// that something wrong in the index of the array
				}*/
				String^ intValue;
				if (CheckHexIsValid(ArrayIndexValue, intValue) == 0) {
					return "NULL/ array index is not Numeric";/// that something wrong in the index of the array 
				}
				else {
					int ArrayIndexValue_ = Str2Int(intValue);  /// x Conversion::Val(ArrayIndexValue);
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
		var_name = input->Substring(0, input->IndexOf(" "));  // get Var name	and clear spaces	
		if (Varexist(var_name->Trim(), vartype_, indexofVar)) { /// check if var exist	
			VarString = "$" + var_name; // this is the end index of var we will used later to replace string
			return ScriptFunList::VarList[indexofVar]->varvalue[0]; // return the value of the var					
		}
		else {
			/// there are space but the string till space not have value or variable 
			//return "NULL/ could'nt get the Variable name";
			var_name = input;  // get Var name	and clear spaces
						   /// we need to find the variable like getvarx y,$x*1
						   /// $x*1  after $ >> x*1 so no space here so we need to find var by tokens
			var_name = readVarName(var_name, 0, VarString);  ////<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
			if (!var_name->StartsWith("NULL/ ")) { /// check if var exist			
				VarString = "$" + VarString; // Get the old string which we will replce later
				return var_name;
			}
			else {
				return "NULL/ Variable not in the list";
			}
		}
	}
	else {  /// there are no space at the end we need to search the rest of the string
	   //return "NULL/ could'nt get the Variable name";
		var_name = input;  // get Var name	and clear spaces
		/// we need to find the variable like getvarx y,$x*1
		/// $x*1  after $ >> x*1 so no space here so we need to find var by tokens
		var_name = readVarName(var_name, 0, VarString);  ////<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		if (!var_name->StartsWith("NULL/ ")) { /// check if var exist			
			VarString = "$" + VarString; // Get the old string which we will replce later
			return var_name;
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
	//String^ value_1 = ""; // we used to check if we need to go more far like [55 * 23 ]
	//String^ OldValue_;
	array <String^>^ tokens_ = { "*" ,"/" ,"+" ,"-" ,"$" ," " ,"(",")" };
	tokenindex = tokenindex + 1; // exclude token form the string
	if (tokenindex + 1 > temp->Length)
		return "NULL/ ";  /// token at the end of string
	else {

		temp = temp->Substring(tokenindex, temp->Length - tokenindex); // get value before token
		int i1 = temp->Length;
		while (temp->Substring(i1 + 1, 1) == " ")  /// count how many spaces
		{
			VarString = " " +VarString ;
			if (i1 + 1 > input->Length) { break; } // if we reach the begin of the string
			i1 += 1;
		}
		temp = (temp->Substring(tokenindex))->Trim(); /// remove all spaces before token like >>  55   + 10
		int i = temp->Length - 1;
		while (tokens_->IndexOf(tokens_, temp->Substring(i, 1)) < 0) /// should not be in this list
		{
			value_ = temp->Substring(i, 1) + value_;
			if (i - 1 < 0) { break; } // if we reach the begin of the string
			i -= 1;
		}
		VarString = value_ + VarString;
		String^ intValue;
		if (CheckHexIsValid(value_, intValue) > 0) {   /// check it if it's hex(number) value 
			return intValue;
		}
		else {  /// that mean it hold variable or something else
			String^ oldvalue1;
			return argumentValue(value_, oldvalue1);
		}
	}
	return "NULL/ ";
																	 
	//String^ temp = input;
	//String^ value_ = "";
	//String^ value_1 = ""; // we used to check if we need to go more far like 5 * 23 ]	
	//String^ OldValue_;
	//if (tokenindex + 1 > input->Length) {
	//	return "NULL/ ";  /// token at the end of string
	//}
	//else
	//{
	//	if (temp->Substring(tokenindex, 1) == " ") { /// if the next char of token is space we skip it  note we add 1 to tokenindex , so we are at next chat of token
	//		temp = temp->Substring(tokenindex + 1, temp->Length - (tokenindex + 1));  /// we pass this First space
	//		VarString = " ";
	//	}
	//	else {
	//		temp = temp->Substring(tokenindex, temp->Length - tokenindex); /// take all string after tokenindex
	//	}
	//	for (size_t i = 0; i < temp->Length; i++)
	//	{
	//		value_ = value_ + temp->Substring(i, 1);
	//		if (i + 1 == temp->Length) { /// if this later is the end of string 
	//			VarString = VarString + value_;  /// in case VarString hold space
	//			return argumentValue(value_->Trim(), OldValue_);
	//		}
	//		if (temp->Substring(i + 1, 1) == " ") {  /// as there are still some char's left (i + 1 > 0)	
	//			VarString = VarString + value_;  /// in case VarString hold space 
	//			return argumentValue(value_->Trim(), OldValue_);
	//		}

	//		array <String^>^ tokens_ = { "*" ,"+","-","/" };
	//		//tokens_->IndexOf(tokens_, temp->Substring(i + 1, 1));
	//		//if ( temp->Substring(i + 1, 1) == " ") {  /// as there are still some char's left (i + 1 > 0)	
	//		if (tokens_->IndexOf(tokens_, temp->Substring(i + 1, 1)) >0) {  /// as there are still some char's left (i + 1 > 0)	
	//			VarString = VarString + value_;  /// in case VarString hold space 
	//			return argumentValue(value_->Trim(), OldValue_);
	//		}

	//		value_1 = value_ + temp->Substring(i + 1, 1);
	//		if ((!argumentValue(value_, OldValue_)->StartsWith("NULL/ ")) && (argumentValue(value_1, OldValue_)->StartsWith("NULL/ "))) {
	//			VarString = VarString + value_1;
	//			return argumentValue(value_1->Trim(), OldValue_);
	//		}
	//	}
	//}
	//return "NULL/ ";
}

String^ BackWard(String^ input, int tokenindex, String^% VarString) {
	String^ temp = input;
	String^ value_ = "";
	//String^ value_1 = ""; // we used to check if we need to go more far like [55 * 23 ]
	//String^ OldValue_;
	array <String^>^ tokens_ = { "*" ,"/" ,"+" ,"-" ,"$" ," " ,"(",")" };
	if (tokenindex - 1 < 0)
		return "NULL/ ";  /// token at the begin of string
	else {

		temp = temp->Substring(0, tokenindex); // get value before token
		int i1 = temp->Length;
		while (temp->Substring(i1 - 1, 1) == " ")  /// count how many spaces
		{			
			VarString = VarString + " ";
			if (i1 - 1 < 0) { break; } // if we reach the begin of the string
			i1 -= 1;
		}
		temp = (temp->Substring(0, tokenindex))->Trim(); /// remove all spaces before token like >>  55   + 10
		int i = temp->Length -1;		
		while (tokens_->IndexOf(tokens_, temp->Substring(i , 1)) < 0) /// should not be in this list
		{			
			value_ = temp->Substring(i , 1) + value_;
			if (i - 1 < 0) { break; } // if we reach the begin of the string
			i -= 1;
		}
		VarString = value_ + VarString;
		String^ intValue;
		if (CheckHexIsValid(value_, intValue) > 0) {   /// check it if it's hex(number) value 
			return intValue;
		}
		else {  /// that mean it hold variable or something else
			String^ oldvalue1;
			return argumentValue(value_,oldvalue1);
		}		
	}
	return "NULL/ ";
	//if (tokenindex - 1 < 0)
	//	return "NULL/ ";  /// token at the begin of string
	//else {
	//	if (temp->Substring(tokenindex - 1, 1) == " ") {  /// if the before char of token is space we skip it 
	//		temp = temp->Substring(0, tokenindex - 1); /// begin from after space  like  55 +
	//		VarString = " ";
	//	}
	//	else {
	//		temp = temp->Substring(0, tokenindex); /// then we get the rest of the string form index 0 till the token index
	//		//VarString = temp;
	//	}
	//	for (size_t i = temp->Length; i > 0; i--)
	//	{
	//		value_ = temp->Substring(i - 1, 1) + value_;
	//		if (i - 1 == 0) {
	//			VarString = value_ + VarString;  /// in case VarString hold space 
	//			return argumentValue(value_->Trim(), OldValue_);
	//		}
	//		if (temp->Substring(i - 1, 1) == " ") { /// as there are still some char's left (i - 1 > 0)
	//			VarString = value_ + VarString;  /// in case VarString hold space 
	//			return argumentValue(value_->Trim(), OldValue_);
	//		}
	//		value_1 = temp->Substring(i - 2, 1) + value_;  /// we check the next char with previous one if it can have a value or related variable
	//		if ((!argumentValue(value_->Trim(), OldValue_)->StartsWith("NULL/ ")) && (argumentValue(value_1->Trim(), OldValue_)->StartsWith("NULL/ "))) {
	//			VarString = value_1 + VarString;
	//			return argumentValue(value_1->Trim(), OldValue_);
	//		}
	//	}
	//}
	//return "NULL/ ";
}

String^ tokens(String^ input, String^% VarString) {
	// check for * first 
	String^ VarString1 = "";
	String^ VarString2 = "";
	String^ para1 = ""; 	String^ para2 = "";
	if (input->StartsWith("-")) {   /// in case we have negtive numbers
		String^ IntValue;
		if (CheckHexIsValid(input->Substring(1, input->Length - 1), IntValue) > 0) {
			return "-" + int2Str(Hex2duint(input->Substring(1, input->Length - 1)));  /// we return the value as int add (-) to it
		}
		else {
			return input;
		}

	}
	if (input->IndexOf("*") > 0) { /// should be bigger than 0 , token should not be at the begining of the exprsion 		
		para1 = BackWard(input, input->IndexOf("*"), VarString1);
		para2 = ForWard(input, input->IndexOf("*") + 1, VarString2);  // we begin after token		
		VarString = VarString1 + "*" + VarString2;
		if ((!Information::IsNumeric(para1)) || !Information::IsNumeric(para2))
			return "NULL/ ";
		else {
			return Conversion::Str(Conversion::Val(para1) * Conversion::Val(para2));
		}
	}

	if (input->IndexOf("/") > 0) { /// should be bigger than 0 , token should not be at the begining of the exprsion 		
		para1 = BackWard(input, input->IndexOf("/"), VarString1);
		para2 = ForWard(input, input->IndexOf("/") + 1, VarString2);
		VarString = VarString1 + "/" + VarString2;
		if ((!Information::IsNumeric(para1)) || !Information::IsNumeric(para2))
			return "NULL/ ";
		else {
			return Conversion::Str(Conversion::Val(para1) / Conversion::Val(para2));
		}
	}

	if (input->IndexOf("+") > 0) { /// should be bigger than 0 , token should not be at the begining of the exprsion 		
		para1 = BackWard(input, input->IndexOf("+"), VarString1);
		para2 = ForWard(input, input->IndexOf("+") + 1, VarString2);
		VarString = VarString1 + "+" + VarString2;
		if ((!Information::IsNumeric(para1)) || !Information::IsNumeric(para2)) {
			_plugin_logprint("one of this arguments are not numeric");
			return "NULL/ ";
		}
		else {
			return Conversion::Str(Conversion::Val(para1) + Conversion::Val(para2));
		}
	}

	if (input->IndexOf("-") > 0) { /// should be bigger than 0 , token should not be at the begining of the exprsion 		
		para1 = BackWard(input, input->IndexOf("-"), VarString1);
		para2 = ForWard(input, input->IndexOf("-") + 1, VarString2);
		VarString = VarString1 + "-" + VarString2;
		if ((!Information::IsNumeric(para1)) || !Information::IsNumeric(para2))
			return "NULL/ ";
		else {
			return Conversion::Str(Conversion::Val(para1) - Conversion::Val(para2));
		}
	}

}

String^ findHexValue(String^ input, String^% oldvalue_) {
	String^ temp;
	if (input->IndexOf("0x") >= 0) {
		input = input->Substring(input->IndexOf("0x") + 2, input->Length - (input->IndexOf("0x") + 2));
		oldvalue_ = "0x";
	}
	else
	{
		return "NULL/ ";
	}
	for (size_t i = 0; i < input->Length; i++)
	{
		String^ intValue1; String^ intValue2;
		if (CheckHexIsValid(input->Substring(i, 1), intValue1)  > 0) {  // if the char not hex or numeric 
			temp = temp + input->Substring(i, 1);
			if (i + 1 < input->Length) {
				if (CheckHexIsValid(input->Substring(i + 1, 1), intValue2) == 0) {
					oldvalue_ = oldvalue_ + temp;
					break;
					//return  int2Str(Hex2duint(temp));    /// now we return the value as int stored in str var
				}
			}
		}
	}
	return  int2Str(Hex2duint(temp));    /// now we return the value as int stored in str var
}

String^ resolveString(String^ input, int% commaCount) {   //// used to resolve strings in str or array vriables 
	String^ temp = "";
	if (input->StartsWith("\"") && (input->EndsWith("\""))) {  /// that mean all string is commaed 
		commaCount = 2;
		return input->Substring(1, input->LastIndexOf("\"") - 1);
	}
	for (size_t i = 0; i < input->Length; i++)
	{
		if (input->Substring(i, 1) == "\"") {
			commaCount += 1;
		}
	}
	if (commaCount % 2 != 0) {  /// check if there is an open comma for each comma
		commaCount = -1;
		return input;
	}
	if (commaCount == 0) {  /// in case there are no comma
		String^ OldValue_;
		return argumentValue(input, OldValue_);

	}
	for (size_t i = 0; i < input->Length; i++)
	{
		if (input->Substring(i, 1) != "\"") {
			temp = temp + input->Substring(i, 1);
		}
		if (i + 1 < input->Length) {
			if (input->Substring(i + 1, 1) == "\"") {
				String^ OldValue_;
				temp = argumentValue(temp->Trim(), OldValue_);  /// reolve this str in case it return NULL we take the old value (which could be half resolved)
				if (temp->StartsWith("NULL/ ")) {
					temp = OldValue_;
				}
				int NextCommaIndex = 1 + input->IndexOf("\"", i + 1);
				String^ StringafterComma = input->Substring(NextCommaIndex, input->Length - NextCommaIndex);
				temp = temp + StringafterComma;
				temp = temp->Substring(0, temp->Length - 1);  /// remove the next comma
				i = i + NextCommaIndex + StringafterComma->Length;  /// now jmp to the next comma
			}
		}
	}
	return temp;
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


String^ argumentValue(String^ argument, String^% OldValue_) {  /// return the <<int>> if possible ,value of the argument storing in string var
	OldValue_ = argument; // rest the value	
	int isNumOrHex = 0; String^ intValue;
	if (CheckHexIsValid(argument, intValue) > 0) {  // <<< need to know if it's whole str is number or hex 	
		//switch (isNumOrHex)
		//{
		//case 1: {
		argument = int2Str(Hex2duint(intValue)); /// if the value is number we get the int value form the hex value
		return argument;
		//}
		//case 2: {
		//	argument = int2Str(Hex2duint(argument));// it mean it's already hex format (000045FAB) and we convert it to int we store it in str var
		//	return argument;
		//}
		//default:
		//	break;
		//}
	}
	//////////////////////////////////////
	int commaCount = 0;
	//argument = resolveString(argument, commaCount);
	if (argument->StartsWith("\"") && (argument->EndsWith("\""))) {  /// that mean all string is commaed 
		return argument;
	}
	//////////////////////////////////////
	if (argument->IndexOf("0x") >= 0) {  /// check if we have a hex value in the string
		while (argument->IndexOf("0x") >= 0) {
			String^ replaceValue = "";
			String^ oldvalue;
			String^ tempinput = argument->Substring(argument->IndexOf("0x"), argument->Length - argument->IndexOf("0x"));  // we take the part which have hex value
			replaceValue = findHexValue(tempinput, oldvalue);	  /// return as int		
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
			String^ inValue;
			if (CheckHexIsValid(replaceValue, inValue) > 0) {
				replaceValue = inValue;
			}
			else {
				replaceValue = "NULL/";
			}

			/*int hexOrInt = CheckHexIsValid(replaceValue, inValue);
			if (hexOrInt < 0) {    /// in case the value less than 0 so no need to get the hex we just get the entered first time
				replaceValue = "NULL/";
			}
			if (hexOrInt == 1) {
				replaceValue = inValue;
			}
			if (hexOrInt == 2) {
				replaceValue = replaceValue;
			}*/
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
		String^ tempInput = argument;
		while (argument->IndexOf("$") >= 0)
		{
			String^ oldValue = "";
			tempInput = argument->Substring(argument->IndexOf("$"), argument->Length - argument->IndexOf("$"));
			tempInput = findVarValue(tempInput, oldValue);
			int isNumOrHex1 = 0; String^ intValue1;
			if (CheckHexIsValid(tempInput, intValue1) > 0) {  // <<< need to know if it's number or hex 
				tempInput = intValue1;
			}
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


	if ((argument->Contains("*")) || (argument->Contains("+")) || (argument->Contains("-")) || (argument->Contains("/"))) {  /// I will do it later
		while ((argument->Contains("*")) || (argument->Contains("+")) || (argument->Contains("-")) || (argument->Contains("/")))
		{
			String^ tempInput = argument;
			String^ oldValue = "";
			int commaCount;
			tempInput = tokens(tempInput, oldValue);  /// we will get them as int value			
			if (tempInput->StartsWith("NULL/")) {
				OldValue_ = argument;
				_plugin_logprint(Str2ConstChar(tempInput));
				return "NULL/ ";
			}
			else {
				argument = ReplaceAtIndex(argument, oldValue, tempInput);
			}
			if (Information::IsNumeric(argument)) {  /// in case it back negtive value
				if (Str2Int(argument) < 0) {
					break;
				}
			}
		}
	}

	return argument;
}



