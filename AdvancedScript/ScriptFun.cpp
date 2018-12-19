#include "ScriptFun.h"
#include "LogWindow.h"

static void VarListClear() {
	ScriptFunList::VarList->Clear();
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
	if (varname->Contains(" ")) {
		_plugin_logprintf("Variable must not have spaces");
		return;
	}
	String^ varvalue_ = argumentValue(varvalue);  /// resolve vriable value
	if (!varvalue_->StartsWith("NULL/")) {  /// that mean the argument is string
		varvalue = varvalue_;
	}
	else
	{
		_plugin_logprintf(Str2ConstChar(Environment::NewLine + "Can't get hex value, var not been added"));
		return;
	}
	String^ retvartype = "";
	if (vartype == "str") {
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
				_plugin_logprintf(Str2ConstChar(Environment::NewLine + VarPara_->vartype + " " +VarPara_->varname  + "= " + varvalue + " :has been added"));
				return;
			}
			else {
				Script::Gui::Message("Variable already defined, it will not defined");
				_plugin_logprintf(Str2ConstChar(Environment::NewLine + VarPara_->varname + " not been added"));
				return;
			}
		}
	};
	/////////////////////////////
	if (vartype == "int") {
		VarPara^ VarPara_ = gcnew VarPara(vartype, varname, varvalue, 0);
		duint intValue_=0;
		/// we have to check it if the value is Numeric or hex 
		if (!CheckHexIsValid(varvalue, intValue_)) {   
			Script::Gui::Message("This is not hex value can converted to int, it will not defined");
			_plugin_logprintf(Str2ConstChar(Environment::NewLine + VarPara_->varname + " :not been added"));
			return;
		}	
		//VarPara_->varvalue[0] = Conversion::Str(intValue_);  // now we set the value as duint >>> no need we will save the value as hex in the var
		if (ScriptFunList::VarList->Count == 0) {
			ScriptFunList::VarList->Add(VarPara_);
			_plugin_logprintf(Str2ConstChar(Environment::NewLine + VarPara_->vartype + " "+ VarPara_->varname + "= " + varvalue + " :has been added"));
			return;
		}
		else {
			int indexofVar = 0;
			if (!Varexist(varname, retvartype, indexofVar)) {
				ScriptFunList::VarList->Add(VarPara_);
				_plugin_logprintf(Str2ConstChar(Environment::NewLine + VarPara_->vartype + " " + VarPara_->varname  + "= " + varvalue + " :has been added"));
				return;
			}
			else {
				Script::Gui::Message("Variable already defined, it will not defined");
				_plugin_logprintf(Str2ConstChar(Environment::NewLine + VarPara_->varname + " :not been added"));
				return;
			}
		}
	};
	/////////////////////////////
	if (vartype == "array") {
		VarPara^ VarPara_ = gcnew VarPara(vartype, varname, varvalue, 0);
		if (ScriptFunList::VarList->Count == 0) {
			ScriptFunList::VarList->Add(VarPara_);
			_plugin_logprintf(Str2ConstChar(Environment::NewLine +VarPara_->vartype + " " + VarPara_->varname  + "[0]" + "= " + varvalue + " :has been added"));
			return;
		}
		else {
			int indexofVar = 0;
			if (!Varexist(varname, retvartype, indexofVar)) {
				ScriptFunList::VarList->Add(VarPara_);
				_plugin_logprintf(Str2ConstChar(Environment::NewLine + VarPara_->vartype + " " + VarPara_->varname + "[0]" + "= " + varvalue + " :has been added"));
				return;
			}
			else {
				Script::Gui::Message("Variable already defined, it will not defined");
				_plugin_logprintf(Str2ConstChar(Environment::NewLine + VarPara_->varname + " :not been added"));
				return;
			}
		}
	};
	/////////////////////////////
	_plugin_logprintf(Str2ConstChar(Environment::NewLine + "No variable type "));

}

VarPara_temp^ GetVarx_byIndex(String^ varname, int index_) {
	VarPara_temp^ x = gcnew VarPara_temp(ScriptFunList::VarList[index_]->vartype, ScriptFunList::VarList[index_]->varname, ScriptFunList::VarList[index_]->varvalue[index_], index_);
	return x;
}

Void GetVarx_(String^ varname, int Arrayindex_) {
	int indexofVar = 0;
	String^ retvartype = "";
	if (Varexist(varname, retvartype, indexofVar)) {
		if (Arrayindex_ > 0 && retvartype == "array") {
			VarPara_temp^ x = gcnew VarPara_temp(ScriptFunList::VarList[indexofVar]->vartype, ScriptFunList::VarList[indexofVar]->varname, ScriptFunList::VarList[indexofVar]->varvalue[Arrayindex_], indexofVar);
			_plugin_logprintf (Str2ConstChar(Environment::NewLine + x->varname + "[" + int2Str(Arrayindex_) + "]" + "= " + x->varvalue));
			return;
		}
		if (Arrayindex_ > 0 && retvartype != "array") {  // that's mean it's int or str  // so we will make Arrayindex_=0 as it'not array
			VarPara_temp^ x = gcnew VarPara_temp(ScriptFunList::VarList[indexofVar]->vartype, ScriptFunList::VarList[indexofVar]->varname, ScriptFunList::VarList[indexofVar]->varvalue[0], indexofVar);
			_plugin_logprintf(Str2ConstChar(Environment::NewLine + "This type not need second agruments"));			
			_plugin_logprintf(Str2ConstChar(Environment::NewLine + x->varname + "= " + x->varvalue));
			return;
		}
		if (Arrayindex_ == 0) {  // this mean it's str or int
			VarPara_temp^ x = gcnew VarPara_temp(ScriptFunList::VarList[indexofVar]->vartype, ScriptFunList::VarList[indexofVar]->varname, ScriptFunList::VarList[indexofVar]->varvalue[0], indexofVar);
			if (x->vartype=="array")
				_plugin_logprintf(Str2ConstChar(Environment::NewLine + x->varname + "[" + int2Str(Arrayindex_) + "]" + "= " + x->varvalue));
			else
				_plugin_logprintf(Str2ConstChar(Environment::NewLine + x->varname + "= " + x->varvalue));
			return ;
		}
		if (Arrayindex_ < 0) {
			_plugin_logprintf(Str2ConstChar(Environment::NewLine + "Index less than Zero!!"));			
			return ;
		}
	}
	else {
		_plugin_logprintf(Str2ConstChar(Environment::NewLine + "No Value for this var, or unknown Varibale"));		
		return ;
	}
}

bool SetVarx_(String^ varname, int index_, String^ value_) {
	int indexofVar = 0;
	String^ retvartype = "";

	duint intValue = 0; bool Hextype_;     
	if (CheckHexIsValid(value_, intValue, Hextype_)) {
		if (Hextype_)
			value_ = int2Str(intValue);
	}

	if (Varexist(varname, retvartype, indexofVar)) {
		if (index_ > 0 && retvartype == "array") {
			ScriptFunList::VarList[indexofVar]->varvalue[index_] = value_;
			_plugin_logprintf(Str2ConstChar(Environment::NewLine + varname + "[" + index_ + "]= " + value_));
			return true;
		}
		if (index_ > 0 && retvartype != "array") {
			_plugin_logprintf(Str2ConstChar(Environment::NewLine + "This type not need second agruments"));
			return false;
		}
		if (index_ == 0) {
			ScriptFunList::VarList[indexofVar]->varvalue[0] = value_;
			_plugin_logprintf(Str2ConstChar(Environment::NewLine + varname + "= " + value_));
			return true;
		}
		if (index_ < 0) {
			_plugin_logprintf(Str2ConstChar(Environment::NewLine + "Index less than Zero!!"));
			return false;
		}
	}
	else {
		_plugin_logprintf(Str2ConstChar(Environment::NewLine + "No Value for this var, or unknown Varibale"));
		return false;
	}
}

String^ findallmemx_(String^ base_, String^ Searchvalue_, String^ Size_) {
	String^ cmd_ = "findallmem ";
	String^ base_s = argumentValue(base_);
	if (!base_s->StartsWith("NULL/")) {
		duint base_x = Hex2duint(base_s);
		if (base_x != -1) {  /// check base
			cmd_ = cmd_ + duint2Hex(base_x) + ",";
			String^ Searchvalue_x = argumentValue(Searchvalue_);
			if (!Searchvalue_x->StartsWith("NULL/")) {
				cmd_ = cmd_ + Searchvalue_x;
				if (Size_ != "") {    /// if user define the size
					duint Size_x = Hex2duint(argumentValue(Size_));
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
		}
		else
			return "NULL/ ";
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