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
};