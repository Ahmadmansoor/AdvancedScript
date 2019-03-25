#pragma once
#include "HelperFunctions.h"

String^ Get_adsValue(String^ input, int% EndB);

enum ads_Enum
{
	exebase,
	modulebase,
	SectionSize,
	exefolderpath,
	exename,
	SectionBegin,
	SectionEnd,
	GetAPIName_,
	GetArraySize__,
	ReadStr__,
	GetdesCallJmp__,
	isInArray_,
	isAddrBelongSection,
};