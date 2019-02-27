#include "ScriptFun.h"



void VarListClear() {
	ScriptFunList::VarList->Clear();
}
VarPara_temp^ GetVarx_byIndex(String^ varname, int index_) {
	VarPara_temp^ x = gcnew VarPara_temp(ScriptFunList::VarList[index_]->vartype, ScriptFunList::VarList[index_]->varname, ScriptFunList::VarList[index_]->varvalue[index_], index_);
	return x;
}
bool Varexist(String^ varname, String^% vartype_, int% index,int% arrayLength) {	// true there is variable with same name
	if (varname->StartsWith("$")) {  // in case we pass variable with $ like $x
		varname = varname->Substring(1, varname->Length - 1);
	}
	index = 0;  // clear index ( as it's a refrence variable)
	for each (VarPara^ var in ScriptFunList::VarList)
	{
		if (var->varname == varname) {
			vartype_ = var->vartype;
			arrayLength = var->arrayLength;
			return true;
		}
		index += 1;
	}
	return false;
}

// defealt value for varvalue="" and will chnaged later to "0" when var is int
bool Varx_(String^ vartype, String^ varname, String^ varvalue) {
	vartype = vartype->ToLower();		
	if ( (varname->Contains(" ")) ) { // || (varname->Contains("$")) ) {
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "Variable must not have spaces or $"));
		return false;
	}		
	// in case var type is not array so the name of variable should not have [array index]
	if ((vartype != "array") && (varname->Contains("[")) && (varname->Contains("]"))) {
		_plugin_logputs(Str2ConstChar(Environment::NewLine + vartype + ":is not array to have [ or ]"));
		return false;
	}
	if ( (vartype == "array") && (!varname->Contains("[")) && (!varname->Contains("]")) ) {
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "array should have [ ]"));
		return false;
	}
	String^ retvartype = "";
	
	if (vartype == "str") {
		if ((varname->Contains("$")) ) {
			_plugin_logputs(Str2ConstChar(Environment::NewLine + "Variable must not have spaces or $"));
			return false;
		}
		String^ resolveVarValue = StrAnalyze(varvalue, VarType::str);		
		VarPara^ VarPara_ = gcnew VarPara(vartype, varname, resolveVarValue,1);
		if (ScriptFunList::VarList->Count == 0) {
			ScriptFunList::VarList->Add(VarPara_);
			_plugin_logprint(Str2ConstChar(Environment::NewLine + VarPara_->vartype + " " + VarPara_->varname + "= " + resolveVarValue + " :has been added"));
			return true;
		}
		else {
			int indexofVar = 0;	int arrayLength;
			if (!Varexist(varname, retvartype, indexofVar, arrayLength)) {
				ScriptFunList::VarList->Add(VarPara_);
				_plugin_logputs(Str2ConstChar(Environment::NewLine + VarPara_->vartype + " " +VarPara_->varname  + "= " + resolveVarValue + " :has been added"));
				return true;
			}
			else {
				//Script::Gui::Message("Variable already defined, it will not defined");
				_plugin_logputs(Str2ConstChar(Environment::NewLine + VarPara_->varname + " not been added"));
				return false;
			}
		}
	};
	/////////////////////////////
	if (vartype == "array") {		
		///find array length
		String^ arrayLen = varname->Substring(varname->IndexOf("[") + 1, varname->Length - (varname->IndexOf("[") + 1));  /// extrect array length
		arrayLen = arrayLen->Substring(0, arrayLen->LastIndexOf("]"));  // we used LastIndexOf in case index value calculated from array var 
		arrayLen = StrAnalyze(arrayLen, VarType::int_);
		if ((arrayLen == "NULL/") || (arrayLen=="") || (arrayLen == "0")){
			_plugin_logputs(Str2ConstChar(Environment::NewLine + "Array Length not valid"));
			return false;
		}
		varname = varname->Substring(0, varname->IndexOf("[")); /// extrect array name
		if ((varname->Contains("$"))) {
			_plugin_logputs(Str2ConstChar(Environment::NewLine + "Variable must not have spaces or $"));
			return false;
		}
		String^ resolveVarValue = StrAnalyze(varvalue, VarType::str);		
		VarPara^ VarPara_ = gcnew VarPara(vartype, varname, resolveVarValue,Str2duint(arrayLen));
		if (ScriptFunList::VarList->Count == 0) {
			ScriptFunList::VarList->Add(VarPara_);
			_plugin_logputs(Str2ConstChar(Environment::NewLine + VarPara_->vartype + " " + VarPara_->varname + "[" + duint2Hex(Str2duint(arrayLen)) + "]" + "= " + resolveVarValue + " :has been added"));
			return true;
		}
		else {
			int indexofVar = 0; int arrayLength;
			if (!Varexist(varname, retvartype, indexofVar, arrayLength)) {
				ScriptFunList::VarList->Add(VarPara_);
				_plugin_logputs(Str2ConstChar(Environment::NewLine + VarPara_->vartype + " " + VarPara_->varname + "[" + duint2Hex(Str2duint(arrayLen)) + "]" + "= " + resolveVarValue + " :has been added"));
				return true;
			}
			else {
				//Script::Gui::Message("Variable already defined, it will not defined");
				_plugin_logputs(Str2ConstChar(Environment::NewLine + VarPara_->varname + " :not been added"));
				return false;
			}
		}
	};
	/////////////////////////////
	if (vartype == "int") {		
		if ((varname->Contains("$"))) {
			_plugin_logputs(Str2ConstChar(Environment::NewLine + "Variable must not have spaces or $"));
			return false;
		}
		/// varValue_Int : resolve vriable value as Int we will used to store it in Int variable 					 
		String^ varValue_Int = StrAnalyze(varvalue, VarType::int_);  		 
		if ((varValue_Int->StartsWith("NULL/")) || (!Information::IsNumeric(varValue_Int))) {
			//Script::Gui::Message("This value can't resolve as int, it will not defined");
			_plugin_logputs(Str2ConstChar(Environment::NewLine + varname + " :not been added"));			
			return false;
		}		
		VarPara^ VarPara_ = gcnew VarPara(vartype, varname, varValue_Int, 1);  // we store varvalue as int 
		if (ScriptFunList::VarList->Count == 0) {
			ScriptFunList::VarList->Add(VarPara_);
			_plugin_logputs(Str2ConstChar(Environment::NewLine + VarPara_->vartype + " "+ VarPara_->varname + "= 0x" + duint2Hex(Str2duint(varValue_Int)) + "\\"+ varValue_Int + " :has been added"));
			return true;
		}
		else {
			int indexofVar = 0; int arrayLength;
			if (!Varexist(varname, retvartype, indexofVar, arrayLength)) {
				ScriptFunList::VarList->Add(VarPara_);
				_plugin_logputs(Str2ConstChar(Environment::NewLine + VarPara_->vartype + " " + VarPara_->varname  + "= 0x" + duint2Hex(Str2duint(varValue_Int)) + "\\" + varValue_Int + " :has been added"));
				return true;
			}
			else {
				//Script::Gui::Message("Variable already defined, it will not defined");
				_plugin_logputs(Str2ConstChar(Environment::NewLine + VarPara_->varname + " :not been added"));
				return false;
			}
		}
	};	
	/////////////////////////////
	_plugin_logputs(Str2ConstChar(Environment::NewLine + "No variable type "));
	return false;
}

bool SetVarx_(String^ varname, int index_, String^ value_) {  /// index_ is index of element at array
	int indexofVar = 0; 	String^ retvartype = "";		int arrayLength;
	if ( (Varexist(varname, retvartype, indexofVar, arrayLength)) && (varname->StartsWith("$")) ) {
		varname = varname->Substring(1, varname->Length - 1);
		if (index_ > 0 && retvartype == "array") {  // it is a array then all elements are string 			
			if (index_ > arrayLength-1) {  /// check if the requested index beyond array length
				_plugin_logputs(Str2ConstChar(Environment::NewLine + "index out of the boundary"));
				return false;
			}
			String^ resolveVarValue = StrAnalyze(value_, VarType::str);
			ScriptFunList::VarList[indexofVar]->varvalue[index_] = resolveVarValue;
			_plugin_logputs(Str2ConstChar(Environment::NewLine + varname + "[" + duint2Hex(index_) + "]= " + resolveVarValue));
			return true;
		}
		if (index_ > 0 && retvartype != "array") {
			_plugin_logputs(Str2ConstChar(Environment::NewLine + "This type not need second agruments"));
			if (ScriptFunList::VarList[indexofVar]->vartype == "int") {  /// case it's int								
				String^ varValue_Int = StrAnalyze(value_, VarType::int_);
				if ((varValue_Int->StartsWith("NULL/")) || (!Information::IsNumeric(varValue_Int))) {
					//Script::Gui::Message("This value can't resolve as int, it will not defined");
					_plugin_logputs(Str2ConstChar(Environment::NewLine + varname + " :not been added"));
					return false;
				}else {  
					ScriptFunList::VarList[indexofVar]->varvalue[0] = varValue_Int;
					_plugin_logputs(Str2ConstChar(Environment::NewLine + varname + "= 0x" + duint2Hex(Str2duint(varValue_Int)) + "\\" + varValue_Int ));
				}
			}else {  /// case str				
				String^ resolveVarValue = StrAnalyze(value_, VarType::str);
				ScriptFunList::VarList[indexofVar]->varvalue[0] = resolveVarValue;
				_plugin_logputs(Str2ConstChar(Environment::NewLine + varname + "= " + resolveVarValue));
			}
			return true;
		}
		if (index_ == 0) {
			if (ScriptFunList::VarList[indexofVar]->vartype == "int") {				
				String^ varValue_Int = StrAnalyze(value_, VarType::int_);
				if ((varValue_Int->StartsWith("NULL/")) || (!Information::IsNumeric(varValue_Int))) {
					//Script::Gui::Message("This value can't resolve as int, it will not defined");
					_plugin_logputs(Str2ConstChar(Environment::NewLine + varname + " :not been added"));
					return false;
				}
				else {
					ScriptFunList::VarList[indexofVar]->varvalue[0] = varValue_Int;
					_plugin_logputs(Str2ConstChar(Environment::NewLine + varname + "= 0x" + duint2Hex(Str2duint(varValue_Int)) + "\\" + varValue_Int));
				}
			}else {  /// case str				
				String^ resolveVarValue = StrAnalyze(value_, VarType::str);
				ScriptFunList::VarList[indexofVar]->varvalue[0] = resolveVarValue;
				_plugin_logputs(Str2ConstChar(Environment::NewLine + varname + "= " + resolveVarValue));
			}
			return true;
		}
		if (index_ < 0) {
			_plugin_logputs(Str2ConstChar(Environment::NewLine + "Index less than Zero!!"));
			return false;
		}
	}
	else {
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "No Value for this var, or unknown Varibale"));
		return false;
	}
	return false;
}

bool GetVarx_(String^ varname, int Arrayindex_) {
	int indexofVar = 0;	String^ retvartype = ""; int arrayLength;
	if (Varexist(varname, retvartype, indexofVar, arrayLength)) {
		if (Arrayindex_ > 0 && retvartype == "array") {
			if (Arrayindex_ > arrayLength-1) {  /// check if the requested index beyond array length
				_plugin_logputs(Str2ConstChar(Environment::NewLine + "index out of the boundary"));
				return false;
			}
			VarPara_temp^ x = gcnew VarPara_temp(ScriptFunList::VarList[indexofVar]->vartype, ScriptFunList::VarList[indexofVar]->varname, ScriptFunList::VarList[indexofVar]->varvalue[Arrayindex_], indexofVar);
			_plugin_logputs (Str2ConstChar(Environment::NewLine + x->varname + "[" + (duint2Hex(Arrayindex_))->Trim() + "]= " + x->varvalue));
			return true;
		}
		if (Arrayindex_ > 0 && retvartype != "array") {  // that's mean it's int or str  // so we will make Arrayindex_=0 as it'not array
			VarPara_temp^ x = gcnew VarPara_temp(ScriptFunList::VarList[indexofVar]->vartype, ScriptFunList::VarList[indexofVar]->varname, ScriptFunList::VarList[indexofVar]->varvalue[0], indexofVar);
			_plugin_logputs(Str2ConstChar(Environment::NewLine + "This type not need second agruments"));
			//_plugin_logputs(Str2ConstChar(Environment::NewLine + x->varname + "= " + x->varvalue));
			if (x->vartype == "int") {
				_plugin_logputs(Str2ConstChar(Environment::NewLine + x->varname + "= 0x" + duint2Hex(Str2duint(x->varvalue)) + "\\" + x->varvalue )) ;
			}
			else { /// it mean str
				_plugin_logputs(Str2ConstChar(Environment::NewLine + x->varname + "= " + x->varvalue));
				}
			return true;
		}
		if (Arrayindex_ == 0) {  // this mean it's str or int
			VarPara_temp^ x = gcnew VarPara_temp(ScriptFunList::VarList[indexofVar]->vartype, ScriptFunList::VarList[indexofVar]->varname, ScriptFunList::VarList[indexofVar]->varvalue[0], indexofVar);
			if (x->vartype=="array")
				_plugin_logputs(Str2ConstChar(Environment::NewLine + x->varname + "[" + (duint2Hex(Arrayindex_))->Trim() + "]= " + x->varvalue));
			else {
				if (x->vartype == "int") {
					//_plugin_logputs(Str2ConstChar(Environment::NewLine + x->varname + "= " + x->varvalue + "\\" + str2Hex(x->varvalue)));
					_plugin_logputs(Str2ConstChar(Environment::NewLine + x->varname + "= 0x" + duint2Hex(Str2duint(x->varvalue)) + "\\" + x->varvalue));
				}
				else  /// it mean str
					_plugin_logputs(Str2ConstChar(Environment::NewLine + x->varname + "= " + x->varvalue));
			}
			return true;
		}
		if (Arrayindex_ < 0) {
			_plugin_logputs(Str2ConstChar(Environment::NewLine + "Index less than Zero!!"));			
			return false;
		}
	}
	else {
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "No Value for this var, or unknown Varibale"));		
		return false;
	}
}



String^ Movx_(String^ p1, String^ p2) {
	String^ cmd_ = "mov " + p1 + ",";
	String^ oldvalue = "";
	//p2 = argumentValue(p2, oldvalue);  /// we will get p1 as int stored in str var , so we need to changed it to hex later
	p2 = StrAnalyze(p2, VarType::str);
	if (!p2->StartsWith("NULL/ ")) {
		cmd_ = cmd_ + str2Hex(p2,VarType::hex,true);
		_plugin_logputs(Str2ConstChar(Environment::NewLine + cmd_));
		return cmd_;
	}
	return "NULL/ ";
}

String^ addx_(String^ p1, String^ p2) {
	String^ cmd_ = "add " + p1 + ",";
	String^ oldvalue = "";
	//p2 = argumentValue(p2, oldvalue);  /// we will get p1 as int stored in str var , so we need to changed it to hex later
	p2 = StrAnalyze(p2, VarType::str);
	if (!p2->StartsWith("NULL/ ")) {
		cmd_ = cmd_ + str2Hex(p2, VarType::hex, true);
		_plugin_logputs(Str2ConstChar(Environment::NewLine + cmd_));
		return cmd_;
	}
	return "NULL/ ";
}

String^ subx_(String^ p1, String^ p2) {
	String^ cmd_ = "sub " + p1 + ",";
	String^ oldvalue = "";
	//p2 = argumentValue(p2, oldvalue);  /// we will get p1 as int stored in str var , so we need to changed it to hex later
	p2 = StrAnalyze(p2, VarType::str);
	if (!p2->StartsWith("NULL/ ")) {
		cmd_ = cmd_ + str2Hex(p2, VarType::hex, true);
		_plugin_logputs(Str2ConstChar(Environment::NewLine + cmd_));
		return cmd_;
	}
	return "NULL/ ";
}

String^ mulx_(String^ p1, String^ p2) {
	String^ cmd_ = "mul " + p1 + ",";
	String^ oldvalue = "";
	//p2 = argumentValue(p2, oldvalue);  /// we will get p1 as int stored in str var , so we need to changed it to hex later
	p2 = StrAnalyze(p2, VarType::str);
	if (!p2->StartsWith("NULL/ ")) {
		cmd_ = cmd_ + str2Hex(p2, VarType::hex, true);
		_plugin_logputs(Str2ConstChar(Environment::NewLine + cmd_));
		return cmd_;
	}
	return "NULL/ ";
}

String^ divx_(String^ p1, String^ p2) {
	String^ cmd_ = "div " + p1 + ",";
	String^ oldvalue = "";
	//p2 = argumentValue(p2, oldvalue);  /// we will get p1 as int stored in str var , so we need to changed it to hex later
	p2 = StrAnalyze(p2, VarType::str);
	if (!p2->StartsWith("NULL/ ")) {
		cmd_ = cmd_ + str2Hex(p2, VarType::hex, true);
		_plugin_logputs(Str2ConstChar(Environment::NewLine + cmd_));
		return cmd_;
	}
	return "NULL/ ";
}

String^ andx_(String^ p1, String^ p2) {
	String^ cmd_ = "and " + p1 + ",";
	String^ oldvalue = "";
	//p2 = argumentValue(p2, oldvalue);  /// we will get p1 as int stored in str var , so we need to changed it to hex later
	p2 = StrAnalyze(p2, VarType::str);
	if (!p2->StartsWith("NULL/ ")) {
		cmd_ = cmd_ + str2Hex(p2, VarType::hex, true);
		_plugin_logputs(Str2ConstChar(Environment::NewLine + cmd_));
		return cmd_;
	}
	return "NULL/ ";
}

String^ orx_(String^ p1, String^ p2) {
	String^ cmd_ = "or " + p1 + ",";
	String^ oldvalue = "";
	//p2 = argumentValue(p2, oldvalue);  /// we will get p1 as int stored in str var , so we need to changed it to hex later
	p2 = StrAnalyze(p2, VarType::str);
	if (!p2->StartsWith("NULL/ ")) {
		cmd_ = cmd_ + str2Hex(p2, VarType::hex, true);
		_plugin_logputs(Str2ConstChar(Environment::NewLine + cmd_));
		return cmd_;
	}
	return "NULL/ ";
}

String^ xorx_(String^ p1, String^ p2) {
	String^ cmd_ = "xor " + p1 + ",";
	String^ oldvalue = "";
	//p2 = argumentValue(p2, oldvalue);  /// we will get p1 as int stored in str var , so we need to changed it to hex later
	p2 = StrAnalyze(p2, VarType::str);
	if (!p2->StartsWith("NULL/ ")) {
		cmd_ = cmd_ + str2Hex(p2, VarType::hex, true);
		_plugin_logputs(Str2ConstChar(Environment::NewLine + cmd_));
		return cmd_;
	}
	return "NULL/ ";
}

String^ shlx_(String^ p1, String^ p2) {
	String^ cmd_ = "shl " + p1 + ",";
	String^ oldvalue = "";
	//p2 = argumentValue(p2, oldvalue);  /// we will get p1 as int stored in str var , so we need to changed it to hex later
	p2 = StrAnalyze(p2, VarType::str);
	if (!p2->StartsWith("NULL/ ")) {
		cmd_ = cmd_ + str2Hex(p2, VarType::hex, true);
		_plugin_logputs(Str2ConstChar(Environment::NewLine + cmd_));
		return cmd_;
	}
	return "NULL/ ";
}

String^ pushx_(String^ p1) {
	String^ cmd_ = "push ";
	String^ oldvalue = "";
	//p1 = argumentValue(p1, oldvalue);  /// we will get p1 as int stored in str var , so we need to changed it to hex later
	p1 = StrAnalyze(p1, VarType::str);
	if (!p1->StartsWith("NULL/ ")) {
		cmd_ = cmd_ + str2Hex(p1, VarType::hex, true);
		_plugin_logputs(Str2ConstChar(Environment::NewLine + cmd_));
		return cmd_;
	}
	return "NULL/ ";
}

String^ popx_(String^ p1) {
	String^ cmd_ = "pop ";
	String^ oldvalue = "";
	//p1 = argumentValue(p1, oldvalue);  /// we will get p1 as int stored in str var , so we need to changed it to hex later
	p1 = StrAnalyze(p1, VarType::str);
	if (!p1->StartsWith("NULL/ ")) {
		cmd_ = cmd_ + str2Hex(p1, VarType::hex, true);
		_plugin_logputs(Str2ConstChar(Environment::NewLine + cmd_));
		return cmd_;
	}
	return "NULL/ ";
}

String^ cmpx_(String^ p1, String^ p2) {
	p1 = StrAnalyze(p1, VarType::str);
	String^ cmd_ = "cmp " + p1 + ",";
	String^ oldvalue = "";
	//p2 = argumentValue(p2, oldvalue);  /// we will get p1 as int stored in str var , so we need to changed it to hex later
	p2 = StrAnalyze(p2, VarType::str);
	if (!p2->StartsWith("NULL/ ")) {
		cmd_ = cmd_ + str2Hex(p2, VarType::hex, true);
		_plugin_logputs(Str2ConstChar(Environment::NewLine + cmd_));
		return cmd_;
	}
	return "NULL/ ";
}

bool GetArraySize_(String^ varArrName, String^ varname) {
	int indexofVar = 0; 	String^ retvartype = "";		int arrayLength;
	int indexofVarArr = 0; 	String^ retvartypeArr = "";		int arrayLengthArr;
	if ((Varexist(varArrName->Trim(), retvartypeArr, indexofVarArr, arrayLengthArr)) && (varArrName->StartsWith("$"))) {
		if ((Varexist(varname->Trim(), retvartype, indexofVar, arrayLength)) && (varname->StartsWith("$"))) {
			if (retvartype == "array") {
				_plugin_logputs(Str2ConstChar(Environment::NewLine + "Sorry not support array now, maybe later"));
				return false;
			}
			else
			{
				ScriptFunList::VarList[indexofVar]->varvalue[0]=int2Str(ScriptFunList::VarList[indexofVarArr]->arrayLength);
				return true;
			}
		}
		else
		{
			_plugin_logputs(Str2ConstChar(Environment::NewLine + "No Value for this var, or unknown Varibale"));
			return false;
		}
	}
	else
	{
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "No Value for this var, or unknown Varibale"));
		return false;
	}

}

bool InputBox_(String^ varname,int index_, String^ message_ , String^ title) {
	int indexofVar = 0; 	String^ retvartype = "";		int arrayLength;
	if ((Varexist(varname->Trim(), retvartype, indexofVar, arrayLength))) {
		varname = varname->Substring(1, varname->Length - 1);		
		if (retvartype == "array") {
			if (index_ > ScriptFunList::VarList[indexofVar]->arrayLength - 1) {
				_plugin_logputs(Str2ConstChar(Environment::NewLine + "value out of array index"));
				return false;
			}
			message_ = StrAnalyze(message_,VarType::str);
			String^ userInput = Interaction::InputBox(message_, title, "", System::Windows::Forms::Application::OpenForms[0]->Width / 2, System::Windows::Forms::Application::OpenForms[0]->Height / 2);
			ScriptFunList::VarList[indexofVar]->varvalue[index_] = userInput;
			return true;
		}
		if (retvartype == "str") {
			message_ = StrAnalyze(message_, VarType::str);
			String^ userInput = Interaction::InputBox(message_, title, "", System::Windows::Forms::Application::OpenForms[0]->Width / 2, System::Windows::Forms::Application::OpenForms[0]->Height / 2);
			ScriptFunList::VarList[indexofVar]->varvalue[index_] = userInput;
			return true;
		}
		else  // case int
		{
			message_ = StrAnalyze(message_, VarType::str);
			String^ userInput = Interaction::InputBox(message_, title, "", System::Windows::Forms::Application::OpenForms[0]->Width / 2, System::Windows::Forms::Application::OpenForms[0]->Height / 2);
			String^ intValue;
			if (CheckHexIsValid(userInput, intValue) > 0) {
				ScriptFunList::VarList[indexofVar]->varvalue[index_] = intValue;
				return true;
			}
			else
			{
				_plugin_logputs(Str2ConstChar(Environment::NewLine + "Variable is int and input is not int or hex"));
				return false;
			}
		}
	}
	else {
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "No Value for this var, or unknown Varibale"));
		return false;
	}
	return false;
}

bool ResizeArray_(String^ varname, int AddSub ) {	// resizeArr(array, added amount)
	int indexofVar = 0; 	String^ retvartype = "";		int arrayLength;
	if ((Varexist(varname->Trim(), retvartype, indexofVar, arrayLength)) && (varname->StartsWith("$"))) {
		varname = varname->Substring(1, varname->Length - 1);
		if (retvartype == "array") { 			
			if (ScriptFunList::VarList[indexofVar]->arrayLength + AddSub <= 0) {
				_plugin_logputs(Str2ConstChar(Environment::NewLine + "Array length can't be less or equal 0"));
				return false;
			}
			else
			{
				ScriptFunList::VarList[indexofVar]->ResizeArr(AddSub);
				return true;
			}
			
		}
		else
		{
			_plugin_logputs(Str2ConstChar(Environment::NewLine + "This is not an array"));
			return false;
		}
	}
	else {
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "No Value for this var, or unknown Varibale"));
		return false;
	}	
}

bool Write2File_(String^ filepath, bool append_,String^ data_) {	//  write2File(path,over_append(true),data
	String^ data_x= StrAnalyze(data_, VarType::str);
	if (data_x->Contains("NULL/")) {
		return false;
	}
	if (append_) {
		IO::File::AppendAllText( filepath, Environment::NewLine + data_x);
		return true;
	}
	else
	{
		IO::File::WriteAllText(filepath, data_x);
		return true;
	}
}

String^ findx_(String^ base_, String^ Searchvalue_, String^ Size_) {
	String^ cmd_ = "find ";	
	String^ base_s = StrAnalyze(base_,VarType::str);	
	if (!base_s->StartsWith("NULL/")) {		
		cmd_ = cmd_ + base_s + ",";			
		String^ Searchvalue_x = StrAnalyze(Searchvalue_, VarType::str);
		if (Searchvalue_x->StartsWith("0x")) {
			Searchvalue_x = Searchvalue_x->Substring(2, Searchvalue_x->Length - 2);
		}
		if ((!Searchvalue_x->StartsWith("\"")) && (!Searchvalue_x->EndsWith("\""))) {   /// check if it between comma ""
			Searchvalue_x = "\"" + Searchvalue_x + "\"";
		}
		if (!Searchvalue_x->StartsWith("NULL/")) {
			cmd_ = cmd_ + Searchvalue_x;
			if (Size_ != "") {    /// if user define the size
				//duint Size_x = Hex2duint(argumentValue(Size_, OldValue_));
				String^ Size_x = StrAnalyze(Size_, VarType::str);
				if (!Size_x->StartsWith("NULL/")) {
					cmd_ = cmd_ + "," + Size_x;
					return cmd_;
				}
				else
					return "NULL/ ";
			}
			else {
				return cmd_;
			}
		}
		else
			return "NULL/ ";		
	}
	else
		return "NULL/ ";
}

String^ findallx_(String^ base_, String^ Searchvalue_, String^ Size_) {
	String^ cmd_ = "findall ";
	String^ base_s = StrAnalyze(base_, VarType::str);	
	if (!base_s->StartsWith("NULL/")) {		
		cmd_ = cmd_ + base_s + ",";		
		String^ Searchvalue_x = StrAnalyze(Searchvalue_, VarType::str);
		if (Searchvalue_x->StartsWith("0x")) {
			Searchvalue_x = Searchvalue_x->Substring(2, Searchvalue_x->Length - 2);
		}
		if ((!Searchvalue_x->StartsWith("\"")) && (!Searchvalue_x->EndsWith("\""))) {   /// check if it between comma ""
			Searchvalue_x = "\"" + Searchvalue_x + "\"";
		}
		if (!Searchvalue_x->StartsWith("NULL/")) {
			cmd_ = cmd_ + Searchvalue_x;
			if (Size_ != "") {    /// if user define the size
				//duint Size_x = Hex2duint(argumentValue(Size_, OldValue_));
				String^ Size_x = StrAnalyze(Size_, VarType::str);
				if (!Size_x->StartsWith("NULL/")) {
					cmd_ = cmd_ + "," + Size_x;
					return cmd_;
				}
				else
					return "NULL/ ";
			}
			else {
				return cmd_;
			}
		}
		else
			return "NULL/ ";
		/*}
		else
		return "NULL/ ";*/
	}
	else
		return "NULL/ ";
}

String^ findallmemx_(String^ base_, String^ Searchvalue_, String^ Size_) {
	String^ cmd_ = "findallmem ";
	String^ base_s = StrAnalyze(base_, VarType::str);	
	if (!base_s->StartsWith("NULL/")) {		
		cmd_ = cmd_ + base_s + ",";
			String^ Searchvalue_x = StrAnalyze(Searchvalue_, VarType::str);
			if (Searchvalue_x->StartsWith("0x")) {
				Searchvalue_x = Searchvalue_x->Substring(2, Searchvalue_x->Length - 2);
			}
			if ((!Searchvalue_x->StartsWith("\"")) && (!Searchvalue_x->EndsWith("\""))) {   /// check if it between comma ""
				Searchvalue_x = "\"" + Searchvalue_x + "\"";
			}
			if (!Searchvalue_x->StartsWith("NULL/")) {
				cmd_ = cmd_ + Searchvalue_x;
				if (Size_ != "") {    /// if user define the size
					//duint Size_x = Hex2duint(argumentValue(Size_, OldValue_));
					String^ Size_x = StrAnalyze(Size_, VarType::str);
					if (!Size_x->StartsWith("NULL/")) {
						cmd_ = cmd_ + "," + Size_x;
						return cmd_;
					}
					else
						return "NULL/ ";
				}
				else {
					return cmd_;
				}
			}
			else
				return "NULL/ ";
		/*}
		else
			return "NULL/ ";*/
	}else
		return "NULL/ ";
}



bool dumpmem(String^ addr , String^ size,String^ para) {
	String^ mem = StringFormatInline_Str("{mem;" + size + "@" + addr + "}");
	String^ addr_ = AddZero2Addr(addr);
	for (int i = 0; i < mem->Length; i+=32)
	{
		String^ temp = Environment::NewLine + addr_ + "         "+ mem->Substring(i, 32) + "        " + str2Asci(mem->Substring(i, 32)) ;
		AdvancedScript::LogWindow::LogWindow_->Log_Str = AdvancedScript::LogWindow::Log_Str + Environment::NewLine + temp;
		if (AdvancedScript::LogWindow::LogWindow_->FormLoaded) {
			AdvancedScript::LogWindow::LogWindow_->RTBAppendText(temp);
		}
		_plugin_logprint(Str2ConstChar(temp));
		addr_ = AddZero2Addr(duint2Hex((Hex2duint(addr_) + 16)));
	}
	return true;
}


bool WriteStr_(duint address, String^ text, bool replace) {
	String^ intValue;
	const char* text_ = Str2ConstChar(text);
	if (CheckHexIsValid(duint2Hex(address), intValue)>0) {
		if (!replace) {
			return Script::Memory::Write(address, text_, sizeof(text_),&address);
		}
		else
		{
			char* temptext = new char[MAX_STRING_SIZE];			
			if (DbgGetStringAt(address, temptext)) {
				int dd = strlen(temptext);
				String^ temptext_ = CharArr2Str(temptext);				
				if (temptext_->StartsWith("L\"")) {
					temptext_ = temptext_->Substring(2, temptext_->Length - 2);  // remove L"
					temptext_ = temptext_->Substring(0, temptext_->Length - 1);	 // remove last "				 
					for (int i = 0; i < (temptext_->Length * 2) + 1; i++)  // 0 terminate
					{
						duint v = address + i;
						byte zero = Convert::ToChar(0);						
						Script::Memory::Write(v , &zero, 1, &v);	//temptext[i] = 0;
					}					
					return Script::Memory::Write(address, text_, sizeof(text_), &address);									
				}
				else
				{
					temptext_ = temptext_->Substring(1, temptext_->Length - 1); // remove "
					temptext_ = temptext_->Substring(0, temptext_->Length - 1); // remove last "
					for (int i = 0; i < (temptext_->Length + 1); i++)  // 0 terminate
					{
						duint v = address + i;
						byte zero = Convert::ToChar(0);
						Script::Memory::Write(v, &zero, 1, &v);	//temptext[i] = 0;
					}
					return Script::Memory::Write(address, text_, sizeof(text_), &address);
				}
			}
			else
			{
				_plugin_logputs(Str2ConstChar(Environment::NewLine + "Can't read the address:" + duint2Hex(address)));
				return false;
			}
		}
	}
	return true;
}

bool gotox_(String^ input, String^% lineNumber) {
	Generic::List<String^>^ arguments;
	GetArg(input, arguments);
	String^ arrayIndex;
	switch ((arguments->Count))
	{
	case 1: {		
		/// first we check if its decimal it should hold d at the end 
		if ((arguments[0]->EndsWith("d")) && (Information::IsNumeric((arguments[0]->Substring(0, arguments[0]->Length - 1))))) {
			lineNumber = arguments[0]->Substring(0, arguments[0]->Length - 1);
			return true;
		}
		else  /// if its not decimal then we should analyze the string if it's hex value 
		{
			lineNumber = StrAnalyze(arguments[0], VarType::int_);
			if (!Information::IsNumeric(lineNumber)) {   /// in case the value not numric that mean it could be a Lable				
				LableLine^ LLine = GetLineByLable(arguments[0]);
				if (LLine->Lable != "") {
					lineNumber = int2Str(LLine->LableLineNumber);
					return true;
				}
				else
				{
					_plugin_logputs(Str2ConstChar(Environment::NewLine + lineNumber + " : true line is incorect"));
					return false;
				}
			}
		}	
		break;
	}
	default:
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
		return false;
	}
}

bool ifCond(String^ input, String^% lineNumber) {  // if condtion ( > < = != ),type (int, str ),line number if true ,line number if false
	Generic::List<String^>^ arguments;
	GetArg(input, arguments);
	String^ arrayIndex;
	switch ((arguments->Count))
	{
	case 4: {
		String^ trueline; String^ falseline;
		/// first we check if its decimal it should hold d at the end 
		if ( (arguments[2]->EndsWith("d")) && (Information::IsNumeric((arguments[2]->Substring(0, arguments[2]->Length - 1))))) {
			trueline = arguments[2]->Substring(0, arguments[2]->Length - 1);			
		}
		else  /// if its not decimal then we should analyze the string if it's hex value 
		{
			trueline = StrAnalyze(arguments[2], VarType::int_);
			if (!Information::IsNumeric(trueline)) {   /// in case the value not numric that mean it could be a Lable				
				LableLine^ LLine = GetLineByLable(arguments[2]);
				if (LLine->Lable != ""){
					trueline = int2Str(LLine->LableLineNumber);
				}
				else
				{
					_plugin_logputs(Str2ConstChar(Environment::NewLine + trueline +  " : true line is incorect"));
					return false;
				}
			}			
		}

		/// first we check if its decimal it should hold d at the end 
		if ((arguments[3]->EndsWith("d")) && (Information::IsNumeric((arguments[3]->Substring(0, arguments[3]->Length - 1))))) {
			falseline = arguments[3]->Substring(0, arguments[3]->Length - 1);
		}
		else  /// if its not decimal then we should analyze the string if it's hex value 
		{
			falseline = StrAnalyze(arguments[3], VarType::int_);
			if (!Information::IsNumeric(falseline)) {   /// in case the value not numric that mean it could be a Lable				
				LableLine^ LLine = GetLineByLable(arguments[3]);
				if (LLine->Lable != "") {
					falseline = int2Str(LLine->LableLineNumber);
				}
				else
				{
					_plugin_logputs(Str2ConstChar(Environment::NewLine + falseline + " : true line is incorect"));
					return false;
				}
			}
		}							
		String ^ ret = condtion_(arguments[0], arguments[1]);
		if (!ret->StartsWith("NULL/")) {
			if (Str2bool(ret)) {
				lineNumber = trueline;
			}
			else
			{
				lineNumber = falseline;
			}
		}
		return true;
	}
	default:
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "worng arguments"));
		return false;
	}
}


String^ condtion_(String^ input,String^ typo) {
	if ((input->Contains("!=")) && (!input->StartsWith("!="))) {
		String^ left_ = input->Substring(0, input->IndexOf("!="))->Trim();
		String^ right_ = input->Substring(input->IndexOf("!=") + 1, input->Length - (input->IndexOf("!=") + 1))->Trim();
		if (typo == "int") {
			left_ = StrAnalyze(left_, VarType::int_);
			right_ = StrAnalyze(right_, VarType::int_);
			if ((left_->StartsWith("NULL/")) || (right_->StartsWith("NULL/")))
				return "NULL/";
			if (!Information::IsNumeric(left_) || !Information::IsNumeric(right_))
				return "NULL/";
			if (Conversion::Val(left_) != Conversion::Val(right_))
				return "1";  // true
			else
				return "0";  // false
		}
		else if (typo == "str")
		{
			left_ = StrAnalyze(left_, VarType::str);
			right_ = StrAnalyze(right_, VarType::str);
			if ((left_->StartsWith("NULL/")) || (right_->StartsWith("NULL/")))
				return "NULL/";

		/*	string.Compare(string1, string2);
			If str1 is less than str2, it returns - 1.
			If str1 is equal to str2, it returns 0.
			If str1 is greater than str2, it returns 1.*/

			if (String::Compare(left_, right_) == 0) // he we check not equal so the retun should be the oppsite.
				return "0";  // false
			else
				return "1";  // true
		}
	}

	if ((input->Contains("=")) && (!input->StartsWith("="))) {
		String^ left_ = input->Substring(0, input->IndexOf("="))->Trim();
		String^ right_ = input->Substring(input->IndexOf("=")+1,input->Length - (input->IndexOf("=") + 1))->Trim();
		if (typo == "int") {
			left_ = StrAnalyze(left_,VarType::int_);
			right_ = StrAnalyze(right_, VarType::int_);
			if ((left_->StartsWith("NULL/")) || (right_->StartsWith("NULL/")))
				return "NULL/";
			if (!Information::IsNumeric(left_) || !Information::IsNumeric(right_))
				return "NULL/";
			if (Conversion::Val(left_) == Conversion::Val(right_))
				return "1";  // true
			else
				return "0";  // false
		}
		else if (typo == "str")
		{
			left_ = StrAnalyze(left_, VarType::str);
			right_ = StrAnalyze(right_, VarType::str);
			if ((left_->StartsWith("NULL/")) || (right_->StartsWith("NULL/")))
				return "NULL/";
			if (String::Compare(left_ ,right_)==0)
				return "1";  // true
			else
				return "0";  // false
		}		
	}

	if ((input->Contains(">")) && (!input->StartsWith(">"))) {
		String^ left_ = input->Substring(0, input->IndexOf(">"))->Trim();
		String^ right_ = input->Substring(input->IndexOf(">") + 1, input->Length - (input->IndexOf(">") + 1))->Trim();
		if (typo == "int") {
			left_ = StrAnalyze(left_, VarType::int_);
			right_ = StrAnalyze(right_, VarType::int_);
			if ((left_->StartsWith("NULL/")) || (right_->StartsWith("NULL/")))
				return "NULL/";
			if (!Information::IsNumeric(left_) || !Information::IsNumeric(right_))
				return "NULL/";
			if (Conversion::Val(left_) > Conversion::Val(right_))
				return "1";  // true
			else
				return "0";  // false
		}
		else if (typo == "str")
		{
			left_ = StrAnalyze(left_, VarType::str);
			right_ = StrAnalyze(right_, VarType::str);
			if ((left_->StartsWith("NULL/")) || (right_->StartsWith("NULL/")))
				return "NULL/";
			if (String::Compare(left_, right_) == 1)
				return "1";  // true
			else
				return "0";  // false
		}
	}

	if ((input->Contains("<")) && (!input->StartsWith("<"))) {
		String^ left_ = input->Substring(0, input->IndexOf("<"))->Trim();
		String^ right_ = input->Substring(input->IndexOf("<") + 1, input->Length - (input->IndexOf("<") + 1))->Trim();
		if (typo == "int") {
			left_ = StrAnalyze(left_, VarType::int_);
			right_ = StrAnalyze(right_, VarType::int_);
			if ((left_->StartsWith("NULL/")) || (right_->StartsWith("NULL/")))
				return "NULL/";
			if (!Information::IsNumeric(left_) || !Information::IsNumeric(right_))
				return "NULL/";
			if (Conversion::Val(left_) < Conversion::Val(right_))
				return "1";  // true
			else
				return "0";  // false
		}
		else if (typo == "str")
		{
			left_ = StrAnalyze(left_, VarType::str);
			right_ = StrAnalyze(right_, VarType::str);
			if ((left_->StartsWith("NULL/")) || (right_->StartsWith("NULL/")))
				return "NULL/";
			if (String::Compare(left_, right_) == -1)
				return "1";  // true
			else
				return "0";  // false
		}
	}
}

