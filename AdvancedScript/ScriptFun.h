#pragma once

#include "HelperFunctions.h"


static ref class VarPara_temp
{
public:
	VarPara_temp(String^ vartype_, String^ varname_, String^ varvalue_, int i) {
		if (varvalue_ == nullptr) {
			varvalue_ = "NULL";
		}

		if (i !=-1){
		if (vartype_ == "array") {
			vartype = vartype_;
			varname = varname_;
			varvalue = varvalue_;
		}
		else {
			vartype = vartype_;
			varname = varname_;
			varvalue = varvalue_;
		}
		}
		else {
			vartype = "";
			varname = "";
			varvalue = "";
		}

		/*if ((vartype_ == "str") || (vartype_ == "int")) {
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
			varvalue[0] = varvalue_;
		}
		if ((vartype_ != "str") && (vartype_ != "int") && (vartype_ != "array")) {
			vartype = "";
			varname = "";
			varvalue = gcnew array<String^>(1);
			varvalue[0] = varvalue_;
		}*/
	}

public:
	String^ vartype;
	String^ varname;
	String^ varvalue;
};

static void VarListClear();
/////
void Varx_(String^ vartype, String^ varname, String^ varvalue = "");
VarPara_temp^ GetVarx_(String^ varname, int index);
bool SetVarx_(String^ varname, String^ value_, int index_=0);
String^ argumentValue(String^ argument);


