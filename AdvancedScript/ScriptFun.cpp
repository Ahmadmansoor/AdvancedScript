#include "ScriptFun.h"
#include "LogWindow.h"
#include "Parser.h"
static void VarListClear() {
	ScriptFunList::VarList->Clear();
}
VarPara_temp^ GetVarx_byIndex(String^ varname, int index_) {
	VarPara_temp^ x = gcnew VarPara_temp(ScriptFunList::VarList[index_]->vartype, ScriptFunList::VarList[index_]->varname, ScriptFunList::VarList[index_]->varvalue[index_], index_);
	return x;
}
bool Varexist(String^ varname, String^% vartype_, int% index) {	// true there is variable with same name
	if (varname->StartsWith("$")) {  // in case we pass variable with $ like $x
		varname = varname->Substring(1, varname->Length - 1);
	}
	index = 0;  // clear index ( as it's a refrence variable)
	for each (VarPara^ var in ScriptFunList::VarList)
	{
		if (var->varname == varname) {
			vartype_ = var->vartype;
			return true;
		}
		index += 1;
	}
	return false;
}

// defealt value for varvalue="" and will chnaged later to "0" when var is int
void Varx_(String^ vartype, String^ varname, String^ varvalue) {
	vartype = vartype->ToLower();
	String^ oldValue="";
	if (varname->Contains(" ")) {
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "Variable must not have spaces"));
		return;
	}		
	String^ retvartype = "";
	if (vartype == "str") {
		int commaCount = 0;
		if (varvalue == "") { varvalue = "NULL"; } // in case user not define value
		String^ resolveVarValue = resolveString(varvalue, commaCount);
		if (resolveVarValue->StartsWith("\"") && (resolveVarValue->EndsWith("\""))) {  /// that mean all string is commaed 
			resolveVarValue = resolveVarValue->Substring(1, resolveVarValue->Length - 1);
			resolveVarValue = resolveVarValue->Substring(0, resolveVarValue->LastIndexOf("\"")); // get string without comma's
		}
		if (commaCount != 0) {
			varvalue = resolveVarValue;
		}		
		VarPara^ VarPara_ = gcnew VarPara(vartype, varname, varvalue, 0);
		if (ScriptFunList::VarList->Count == 0) {
			ScriptFunList::VarList->Add(VarPara_);
			_plugin_logprint(Str2ConstChar(Environment::NewLine + VarPara_->vartype + " " + VarPara_->varname + "= "+ varvalue + " :has been added"));
			return;
		}
		else {
			int indexofVar = 0;
			if (!Varexist(varname, retvartype, indexofVar)) {
				ScriptFunList::VarList->Add(VarPara_);
				_plugin_logputs(Str2ConstChar(Environment::NewLine + VarPara_->vartype + " " +VarPara_->varname  + "= " + varvalue + " :has been added"));
				return;
			}
			else {
				Script::Gui::Message("Variable already defined, it will not defined");
				_plugin_logputs(Str2ConstChar(Environment::NewLine + VarPara_->varname + " not been added"));
				return;
			}
		}
	};
	/////////////////////////////
	if (vartype == "int") {		
		/// varValue_Int : resolve vriable value as Int we will used to store it in Int variable 
		String^ OldValue_;
		String^ varValue_Int = argumentValue(varvalue, OldValue_);		
		if ((varValue_Int->StartsWith("NULL/")) || (!Information::IsNumeric(varValue_Int))) {
			Script::Gui::Message("This value can't resolve as int, it will not defined");
			_plugin_logputs(Str2ConstChar(Environment::NewLine + varname + " :not been added"));			
			return;			
		}		
		VarPara^ VarPara_ = gcnew VarPara(vartype, varname, int2Str(Hex2duint(varValue_Int)), 0);  // we store varvalue as int 
		if (ScriptFunList::VarList->Count == 0) {
			ScriptFunList::VarList->Add(VarPara_);
			_plugin_logputs(Str2ConstChar(Environment::NewLine + VarPara_->vartype + " "+ VarPara_->varname + "= 0x" + varValue_Int + "\\"+ int2Str(Hex2duint(varvalue)) + " :has been added"));
			return;
		}
		else {
			int indexofVar = 0;
			if (!Varexist(varname, retvartype, indexofVar)) {
				ScriptFunList::VarList->Add(VarPara_);
				_plugin_logputs(Str2ConstChar(Environment::NewLine + VarPara_->vartype + " " + VarPara_->varname  + "= 0x" + varValue_Int + "\\" + int2Str(Hex2duint(varvalue)) + " :has been added"));
				return;
			}
			else {
				Script::Gui::Message("Variable already defined, it will not defined");
				_plugin_logputs(Str2ConstChar(Environment::NewLine + VarPara_->varname + " :not been added"));
				return;
			}
		}
	};
	/////////////////////////////
	if (vartype == "array") {
		int commaCount = 0;
		String^ resolveVarValue = resolveString(varvalue, commaCount);
		if (resolveVarValue->StartsWith("\"") && (resolveVarValue->EndsWith("\""))) {  /// that mean all string is commaed 
			resolveVarValue = resolveVarValue->Substring(1, resolveVarValue->Length - 1);
			resolveVarValue = resolveVarValue->Substring(0, resolveVarValue->IndexOf("\"")); // get string without comma's
		}
		if (commaCount != 0) {
			varvalue = resolveVarValue;
		}
		VarPara^ VarPara_ = gcnew VarPara(vartype, varname, varvalue, 0);
		if (ScriptFunList::VarList->Count == 0) {
			ScriptFunList::VarList->Add(VarPara_);
			_plugin_logputs(Str2ConstChar(Environment::NewLine +VarPara_->vartype + " " + VarPara_->varname  + "[0]" + "= " + varvalue + " :has been added"));
			return;
		}
		else {
			int indexofVar = 0;
			if (!Varexist(varname, retvartype, indexofVar)) {
				ScriptFunList::VarList->Add(VarPara_);
				_plugin_logputs(Str2ConstChar(Environment::NewLine + VarPara_->vartype + " " + VarPara_->varname + "[0]" + "= " + varvalue + " :has been added"));
				return;
			}
			else {
				Script::Gui::Message("Variable already defined, it will not defined");
				_plugin_logputs(Str2ConstChar(Environment::NewLine + VarPara_->varname + " :not been added"));
				return;
			}
		}
	};
	/////////////////////////////
	_plugin_logputs(Str2ConstChar(Environment::NewLine + "No variable type "));

}



bool SetVarx_(String^ varname, int index_, String^ value_) {
	int indexofVar = 0;
	String^ retvartype = "";
	if (Varexist(varname, retvartype, indexofVar)) {
		varname = varname->Substring(1, varname->Length - 1);
		if (index_ > 0 && retvartype == "array") {
			ScriptFunList::VarList[indexofVar]->varvalue[index_] = value_;
			_plugin_logputs(Str2ConstChar(Environment::NewLine + varname + "[" + index_ + "]= " + value_));
			return true;
		}
		if (index_ > 0 && retvartype != "array") {
			_plugin_logputs(Str2ConstChar(Environment::NewLine + "This type not need second agruments"));
			String^ OldValue_;
			if (ScriptFunList::VarList[indexofVar]->vartype == "int") {  /// case it's int
				String^ t1 = argumentValue(value_, OldValue_);
				if ((t1->StartsWith("NULL/ ")) || !(Information::IsNumeric(t1))) {
					Script::Gui::Message("This value can't resolve to int, it will not defined");
					_plugin_logputs(Str2ConstChar(Environment::NewLine + varname + " :not been set"));
					return false;
				}
				else
				{
					ScriptFunList::VarList[indexofVar]->varvalue[0] = value_;
					_plugin_logputs(Str2ConstChar(Environment::NewLine + varname + "= " + value_ + "\\" + str2Hex(value_)));
				}
			}
			else {  /// case str
				ScriptFunList::VarList[indexofVar]->varvalue[0] = value_;
				_plugin_logputs(Str2ConstChar(Environment::NewLine + varname + "= " + value_));
			}
			return true;
		}
		if (index_ == 0) {
			if (ScriptFunList::VarList[indexofVar]->vartype == "int") {
				String^ OldValue_;
				String^ t1 = argumentValue(value_, OldValue_);
				if ((t1->StartsWith("NULL/ ")) || !(Information::IsNumeric(t1))) {   /// if the value is not int 
					Script::Gui::Message("This value can't resolve to int, it will not defined");
					_plugin_logputs(Str2ConstChar(Environment::NewLine + varname + " :not been set"));
					return false;
				}
				else
				{
					ScriptFunList::VarList[indexofVar]->varvalue[0] = value_;
					_plugin_logputs(Str2ConstChar(Environment::NewLine + varname + "= " + value_ + "\\" + str2Hex(value_)));
				}
			}
			else {  /// case str
				ScriptFunList::VarList[indexofVar]->varvalue[0] = value_;
				_plugin_logputs(Str2ConstChar(Environment::NewLine + varname + "= " + value_));
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
}

Void GetVarx_(String^ varname, int Arrayindex_) {
	int indexofVar = 0;
	String^ retvartype = "";
	if (Varexist(varname, retvartype, indexofVar)) {
		if (Arrayindex_ > 0 && retvartype == "array") {
			VarPara_temp^ x = gcnew VarPara_temp(ScriptFunList::VarList[indexofVar]->vartype, ScriptFunList::VarList[indexofVar]->varname, ScriptFunList::VarList[indexofVar]->varvalue[Arrayindex_], indexofVar);
			_plugin_logputs (Str2ConstChar(Environment::NewLine + x->varname + "[" + int2Str(Arrayindex_) + "]" + "= " + x->varvalue));
			return;
		}
		if (Arrayindex_ > 0 && retvartype != "array") {  // that's mean it's int or str  // so we will make Arrayindex_=0 as it'not array
			VarPara_temp^ x = gcnew VarPara_temp(ScriptFunList::VarList[indexofVar]->vartype, ScriptFunList::VarList[indexofVar]->varname, ScriptFunList::VarList[indexofVar]->varvalue[0], indexofVar);
			_plugin_logputs(Str2ConstChar(Environment::NewLine + "This type not need second agruments"));			
			//_plugin_logputs(Str2ConstChar(Environment::NewLine + x->varname + "= " + x->varvalue));
			if (x->vartype == "int") {
				_plugin_logputs(Str2ConstChar(Environment::NewLine + x->varname + "= " + x->varvalue + "\\" + str2Hex(x->varvalue)));
			}
			else  /// it mean str
				_plugin_logputs(Str2ConstChar(Environment::NewLine + x->varname + "= " + x->varvalue));
			return;
		}
		if (Arrayindex_ == 0) {  // this mean it's str or int
			VarPara_temp^ x = gcnew VarPara_temp(ScriptFunList::VarList[indexofVar]->vartype, ScriptFunList::VarList[indexofVar]->varname, ScriptFunList::VarList[indexofVar]->varvalue[0], indexofVar);
			if (x->vartype=="array")
				_plugin_logputs(Str2ConstChar(Environment::NewLine + x->varname + "[" + int2Str(Arrayindex_) + "]" + "= " + x->varvalue));
			else {
				if (x->vartype == "int") {
					_plugin_logputs(Str2ConstChar(Environment::NewLine + x->varname + "= " + x->varvalue + "\\" + str2Hex(x->varvalue)));
				}
				else  /// it mean str
					_plugin_logputs(Str2ConstChar(Environment::NewLine + x->varname + "= " + x->varvalue));
			}
			return ;
		}
		if (Arrayindex_ < 0) {
			_plugin_logputs(Str2ConstChar(Environment::NewLine + "Index less than Zero!!"));			
			return ;
		}
	}
	else {
		_plugin_logputs(Str2ConstChar(Environment::NewLine + "No Value for this var, or unknown Varibale"));		
		return ;
	}
}



String^ Movx_(String^ p1, String^ p2) {
	String^ cmd_ = "mov " + p1 + ",";
	String^ oldvalue = "";
	p2 = argumentValue(p2, oldvalue);  /// we will get p1 as int stored in str var , so we need to changed it to hex later
	if (!p1->StartsWith("NULL/ ")) {
		cmd_ = cmd_ + str2Hex(p2);
		return cmd_;
	}
	return "NULL/ ";
}

String^ addx_(String^ p1, String^ p2) {
	String^ cmd_ = "add " + p1 + ",";
	String^ oldvalue = "";
	p2 = argumentValue(p2, oldvalue);  /// we will get p1 as int stored in str var , so we need to changed it to hex later
	if (!p1->StartsWith("NULL/ ")) {
		cmd_ = cmd_ + str2Hex(p2);
		return cmd_;
	}
	return "NULL/ ";
}

String^ subx_(String^ p1, String^ p2) {
	String^ cmd_ = "sub " + p1 + ",";
	String^ oldvalue = "";
	p2 = argumentValue(p2, oldvalue);  /// we will get p1 as int stored in str var , so we need to changed it to hex later
	if (!p1->StartsWith("NULL/ ")) {
		cmd_ = cmd_ + str2Hex(p2);
		return cmd_;
	}
	return "NULL/ ";
}

String^ mulx_(String^ p1, String^ p2) {
	String^ cmd_ = "mul " + p1 + ",";
	String^ oldvalue = "";
	p2 = argumentValue(p2, oldvalue);  /// we will get p1 as int stored in str var , so we need to changed it to hex later
	if (!p1->StartsWith("NULL/ ")) {
		cmd_ = cmd_ + str2Hex(p2);
		return cmd_;
	}
	return "NULL/ ";
}

String^ divx_(String^ p1, String^ p2) {
	String^ cmd_ = "div " + p1 + ",";
	String^ oldvalue = "";
	p2 = argumentValue(p2, oldvalue);  /// we will get p1 as int stored in str var , so we need to changed it to hex later
	if (!p1->StartsWith("NULL/ ")) {
		cmd_ = cmd_ + str2Hex(p2);
		return cmd_;
	}
	return "NULL/ ";
}

String^ andx_(String^ p1, String^ p2) {
	String^ cmd_ = "and " + p1 + ",";
	String^ oldvalue = "";
	p2 = argumentValue(p2, oldvalue);  /// we will get p1 as int stored in str var , so we need to changed it to hex later
	if (!p1->StartsWith("NULL/ ")) {
		cmd_ = cmd_ + str2Hex(p2);
		return cmd_;
	}
	return "NULL/ ";
}

String^ orx_(String^ p1, String^ p2) {
	String^ cmd_ = "or " + p1 + ",";
	String^ oldvalue = "";
	p2 = argumentValue(p2, oldvalue);  /// we will get p1 as int stored in str var , so we need to changed it to hex later
	if (!p1->StartsWith("NULL/ ")) {
		cmd_ = cmd_ + str2Hex(p2);
		return cmd_;
	}
	return "NULL/ ";
}

String^ xorx_(String^ p1, String^ p2) {
	String^ cmd_ = "xor " + p1 + ",";
	String^ oldvalue = "";
	p2 = argumentValue(p2, oldvalue);  /// we will get p1 as int stored in str var , so we need to changed it to hex later
	if (!p1->StartsWith("NULL/ ")) {
		cmd_ = cmd_ + str2Hex(p2);
		return cmd_;
	}
	return "NULL/ ";
}

String^ shlx_(String^ p1, String^ p2) {
	String^ cmd_ = "shl " + p1 + ",";
	String^ oldvalue = "";
	p2 = argumentValue(p2, oldvalue);  /// we will get p1 as int stored in str var , so we need to changed it to hex later
	if (!p1->StartsWith("NULL/ ")) {
		cmd_ = cmd_ + str2Hex(p2);
		return cmd_;
	}
	return "NULL/ ";
}

String^ pushx_(String^ p1) {
	String^ cmd_ = "push ";
	String^ oldvalue = "";
	p1 = argumentValue(p1, oldvalue);  /// we will get p1 as int stored in str var , so we need to changed it to hex later
	if (!p1->StartsWith("NULL/ ")) {
		cmd_ = cmd_ + str2Hex(p1);
		return cmd_;
	}
	return "NULL/ ";
}

String^ popx_(String^ p1) {
	String^ cmd_ = "pop ";
	String^ oldvalue = "";
	p1 = argumentValue(p1, oldvalue);  /// we will get p1 as int stored in str var , so we need to changed it to hex later
	if (!p1->StartsWith("NULL/ ")) {
		cmd_ = cmd_ + str2Hex(p1);
		return cmd_;
	}
	return "NULL/ ";
}

String^ cmpx_(String^ p1, String^ p2) {
	String^ cmd_ = "cmp " + p1 + ",";
	String^ oldvalue = "";
	p2 = argumentValue(p2, oldvalue);  /// we will get p1 as int stored in str var , so we need to changed it to hex later
	if (!p1->StartsWith("NULL/ ")) {
		cmd_ = cmd_ + str2Hex(p2);
		return cmd_;
	}
	return "NULL/ ";
}

String^ findx_(String^ base_, String^ Searchvalue_, String^ Size_) {
	String^ cmd_ = "find ";
	String^ OldValue_;
	String^ base_s = argumentValue(base_, OldValue_);

	if (!Information::IsNumeric(base_s)) {
		_plugin_logputs(Str2ConstChar(base_s + " is not a hex"));
		return "NULL/ ";
	}
	if (Str2Int(base_s) < 0) {    /// in case the value less than 0 so no need to get the hex we just get the entered first time
		base_s = base_;
	}
	else
	{
		base_s = duint2Hex(Str2Int(base_s));
	}

	if (!base_s->StartsWith("NULL/")) {
		//duint base_x = Hex2duint(base_s);
		//if (base_x != -1) {  /// check base
		//cmd_ = cmd_ + duint2Hex(base_x) + ",";
		cmd_ = cmd_ + base_s + ",";
		String^ OldValue_;
		String^ Searchvalue_x = argumentValue(Searchvalue_, OldValue_);
		if (!Searchvalue_x->StartsWith("NULL/")) {
			cmd_ = cmd_ + Searchvalue_x;
			if (Size_ != "") {    /// if user define the size
				duint Size_x = Hex2duint(argumentValue(Size_, OldValue_));
				if (Size_x != -1) {
					cmd_ = cmd_ + "," + duint2Hex(Size_x);
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

String^ findallx_(String^ base_, String^ Searchvalue_, String^ Size_) {
	String^ cmd_ = "findall ";
	String^ OldValue_;
	String^ base_s = argumentValue(base_, OldValue_);

	if (!Information::IsNumeric(base_s)) {
		_plugin_logputs(Str2ConstChar(base_s + " is not a hex"));
		return "NULL/ ";
	}
	if (Str2Int(base_s) < 0) {    /// in case the value less than 0 so no need to get the hex we just get the entered first time
		base_s = base_;
	}
	else
	{
		base_s = duint2Hex(Str2Int(base_s));
	}

	if (!base_s->StartsWith("NULL/")) {
		//duint base_x = Hex2duint(base_s);
		//if (base_x != -1) {  /// check base
		//cmd_ = cmd_ + duint2Hex(base_x) + ",";
		cmd_ = cmd_ + base_s + ",";
		String^ OldValue_;
		String^ Searchvalue_x = argumentValue(Searchvalue_, OldValue_);
		if (!Searchvalue_x->StartsWith("NULL/")) {
			cmd_ = cmd_ + Searchvalue_x;
			if (Size_ != "") {    /// if user define the size
				duint Size_x = Hex2duint(argumentValue(Size_, OldValue_));
				if (Size_x != -1) {
					cmd_ = cmd_ + "," + duint2Hex(Size_x);
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
	String^ OldValue_;
	String^ base_s = argumentValue(base_, OldValue_);
	String^ dd = Microsoft::VisualBasic::Conversion::Hex(base_s);
	/*if (!Information::IsNumeric(base_s)) {
		_plugin_logputs(Str2ConstChar(base_s + " is not a hex"));
		return "NULL/ ";
	}*/
	String^ inValue;
	int hexOrInt = CheckHexIsValid(base_s, inValue);
	if (hexOrInt < 0) {    /// in case the value less than 0 so no need to get the hex we just get the entered first time
		base_s = "NULL/";
	}
	if (hexOrInt == 1) {
		base_s = inValue;
	}
	if ( (hexOrInt == 2) && (base_s->StartsWith("0x")) ) {
		base_s =  base_s;
	}
	
	if (!base_s->StartsWith("NULL/")) {
		//duint base_x = Hex2duint(base_s);
		//if (base_x != -1) {  /// check base
			//cmd_ = cmd_ + duint2Hex(base_x) + ",";
		cmd_ = cmd_ + base_s + ",";
			String^ OldValue_;
			String^ Searchvalue_x = argumentValue(Searchvalue_, OldValue_);
			if (!Searchvalue_x->StartsWith("NULL/")) {
				cmd_ = cmd_ + Searchvalue_x;
				if (Size_ != "") {    /// if user define the size
					duint Size_x = Hex2duint(argumentValue(Size_, OldValue_));
					if (Size_x != -1) {
						cmd_ = cmd_ + "," + duint2Hex(Size_x);
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
	for (size_t i = 0; i < mem->Length; i+=32)
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