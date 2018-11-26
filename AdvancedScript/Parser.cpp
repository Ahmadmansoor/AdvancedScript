#pragma once
#include "Parser.h"
//#include "PluginBasic.h"


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

	return RegisterEnum_->IndexOf(RegisterEnum_,input_); // if -1 then not found 
}

//System::String^ LogxParaser(String^ input) {
//
//}


