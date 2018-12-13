#include "ScriptFun.h"

static public ref class VarPara
{
public:
	VarPara(String^ vartype_, String^ varname_, String^ varvalue_, int i) {
		if ((vartype_ == "str") || (vartype_ == "int")) {
			vartype = vartype_;
			varname = varname_;
			varvalue = gcnew array<String^>(1);
			if (vartype_ == "str")
				varvalue[i] = varvalue_;
			if (vartype_ == "int" && varvalue_ == "") {
				varvalue[i] = "0";
			}
			else { varvalue[i] = varvalue_; }

		}
		if (vartype_ == "array") {
			vartype = vartype_;
			varname = varname_;
			varvalue = gcnew array<String^>(500);
			/*for each (String^ var in varvalue)
			{
				var = "";
			}*/
			varvalue[0] = varvalue_;
		}
		if ((vartype_ != "str") && (vartype_ != "int") && (vartype_ != "array")) {
			vartype = "";
			varname = "";
			varvalue = gcnew array<String^>(1);
			varvalue[0] = varvalue_;
		}
	}

public:
	String^ vartype;
	String^ varname;
	array <String^>^ varvalue;
};

static ref class ScriptFunList {
public:
	static Generic::List<VarPara^>^ VarList = gcnew Generic::List<VarPara^>;

};

static void VarListClear() {
	ScriptFunList::VarList->Clear();
}
static bool Varexist(String^ varname, String^% vartype_, int% index) {	// true there is variable with same name
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
	String^ retvartype = "";
	if (vartype == "str") {
		VarPara^ VarPara_ = gcnew VarPara(vartype, varname, varvalue, 0);
		if (ScriptFunList::VarList->Count == 0) {
			ScriptFunList::VarList->Add(VarPara_);
			_plugin_logprintf(Str2ConstChar(Environment::NewLine + VarPara_->varname + " :has been added"));
			return;
		}
		else {
			int indexofVar = 0;
			if (!Varexist(varname, retvartype, indexofVar)) {
				ScriptFunList::VarList->Add(VarPara_);
				_plugin_logprintf(Str2ConstChar(Environment::NewLine + VarPara_->varname + " :has been added"));
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
		if (ScriptFunList::VarList->Count == 0) {
			ScriptFunList::VarList->Add(VarPara_);
			_plugin_logprintf(Str2ConstChar(Environment::NewLine + VarPara_->varname + " :has been added"));
			return;
		}
		else {
			int indexofVar = 0;
			if (!Varexist(varname, retvartype, indexofVar)) {
				ScriptFunList::VarList->Add(VarPara_);
				_plugin_logprintf(Str2ConstChar(Environment::NewLine + VarPara_->varname + " :has been added"));
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
			_plugin_logprintf(Str2ConstChar(Environment::NewLine + VarPara_->varname + " :has been added"));
			return;
		}
		else {
			int indexofVar = 0;
			if (!Varexist(varname, retvartype, indexofVar)) {
				ScriptFunList::VarList->Add(VarPara_);
				_plugin_logprintf(Str2ConstChar(Environment::NewLine + VarPara_->varname + " :has been added"));
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

VarPara_temp^ GetVarx_(String^ varname, int index_) {
	int indexofVar = 0;
	String^ retvartype = "";
	if (Varexist(varname, retvartype, indexofVar)) {
		if (index_ > 0 && retvartype == "array") {
			VarPara_temp^ x = gcnew VarPara_temp(ScriptFunList::VarList[indexofVar]->vartype, ScriptFunList::VarList[indexofVar]->varname, ScriptFunList::VarList[indexofVar]->varvalue[index_], indexofVar);
			return x;
		}
		if (index_ > 0 && retvartype != "array") {
			_plugin_logprintf(Str2ConstChar(Environment::NewLine + "This type not need second agruments"));
			VarPara_temp^ x = gcnew VarPara_temp("", "", "", -1);
			return x;
		}
		if (index_ == 0) {
			VarPara_temp^ x = gcnew VarPara_temp(ScriptFunList::VarList[indexofVar]->vartype, ScriptFunList::VarList[indexofVar]->varname, ScriptFunList::VarList[indexofVar]->varvalue[0], indexofVar);
			return x;
		}
		if (index_ < 0) {
			_plugin_logprintf(Str2ConstChar(Environment::NewLine + "Index less than Zero!!"));
			VarPara_temp^ x = gcnew VarPara_temp("", "", "", -1);
			return x;
		}
	}
	else {
		_plugin_logprintf(Str2ConstChar(Environment::NewLine + "No Value for this var, or unknown Varibale"));
		VarPara_temp^ x = gcnew VarPara_temp("", "", "", -1);
		return x;
	}
}

bool SetVarx_(String^ varname,String^ value_, int index_) {
	int indexofVar = 0;
	String^ retvartype = "";
	if (Varexist(varname, retvartype, indexofVar)) {
		if (index_ > 0 && retvartype == "array") {				
		ScriptFunList::VarList[indexofVar]->varvalue[index_] = value_;	
		return true;
		}
		if (index_ > 0 && retvartype != "array") {
			_plugin_logprintf(Str2ConstChar(Environment::NewLine + "This type not need second agruments"));			
			return false;
		}
		if (index_ == 0) {
			ScriptFunList::VarList[indexofVar]->varvalue[0]=value_;
			return true;
		}			
		if (index_ < 0) {
			_plugin_logprintf(Str2ConstChar(Environment::NewLine + "Index less than Zero!!"));			
			return true;
		}
	}
	else {
		_plugin_logprintf(Str2ConstChar(Environment::NewLine + "No Value for this var, or unknown Varibale"));		
		return false;
	}
}