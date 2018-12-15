#pragma once
#include "HelperFunctions.h"

int GetRegisterIndex(String^ input_);
String^ tokens(String^ input, String^% VarString);
String^ BackWard(String^ input, int tokenindex);
String^ ForWard(String^ input, int tokenindex);
String^ findScriptSystemVarValue(String^ input);
String^ findVarValue(String^ input, String^% VarString);



//script test 
//varx int, x, 3
//getvarx x
//varx array, y, 1
//setvarx y, 3, 5
//getvarx y, $x * 1