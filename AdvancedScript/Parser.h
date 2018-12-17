#pragma once
#include "HelperFunctions.h"

int GetRegisterIndex(String^ input_);
String^ tokens(String^ input, String^% VarString);
String^ BackWard(String^ input, int tokenindex, String^% VarString);
String^ ForWard(String^ input, int tokenindex, String^% VarString);
String^ findScriptSystemVarValue(String^ input);
String^ findVarValue(String^ input, String^% VarString);
String^ ReplaceAtIndex(String^  OriginalString, String^ oldValue, String^ newValue);


//script test 

//varx str, search, "4533C94533C033"
//varx str, base, { rdx }
//findallmemx $base, $search
//mov rdi, ref.addr(0)
//
//findallmem 0x10000, "4533C94533C033"
//mov rdi, ref.addr(0)


//varx int, x, 90
//varx int, x1, 5
//getvarx x
//getvarx x1
//varx array, y, 1
//setvarx y, 110, 100
//getvarx y, 10 + $x + $x1 + 5




//varx int, x, 3
//varx int, x1, 5
//getvarx x
//getvarx x1
//varx array, y, 1
//setvarx y, 3, 9
//setvarx y, 10, 100
//getvarx y, $x * 1
//getvarx y, 1 + $x + $x1 + 1





//varx int, x, 3
//getvarx x
//varx array, y, 1
//setvarx y, 3, 5
//getvarx y, $x * 1