#include "MainForm.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;


ref class Scriptargument
{
private:
	int lineNumber = 0;
public:
	int isCommandsExist(String^ input_) {
		array <String^>^ CommandsArray_ = {
			"Scriptw",
			"LogxJustAtBP",
			"LogxTemplateManager",
			"logxwindow",
			"logx",
			"logxTrace",
			"StrCompx",
			"Varx",
			"Getx",
			"Printx",
			"Setx",
			"Movx",
			"addx",
			"subx",
			"mulx",
			"andx",
			"orx",
			"xorx",
			"shlx",
			"pushx",
			"popx",
			"cmpx",
			"findx",
			"findallx",
			"findallmemx",
			"VarxClear",
			"memdump",
			"writeStr"
		};
		return Array::IndexOf(CommandsArray_, input_); // if -1 then not found 
	};
public:
	void setLineNumber(int LineNum) {
		lineNumber = LineNum;
	};
public:
	int GetLineNumber() {
		return lineNumber;
	};
};

ref class ScriptargumentClass
{
public:
	static Scriptargument^ Scriptargument_ = gcnew Scriptargument;
};

enum Commandenum {
	Scriptw,
	LogxJustAtBP,
	LogxTemplateManager,
	logxwindow,
	logx,
	logxTrace,
	StrCompx,
	Varx,
	Getx,
	Printx,
	Setx,
	Movx,
	addx,
	subx,
	mulx,
	andx,
	orx,
	xorx,
	shlx,
	pushx,
	popx,
	cmpx,
	findx,
	findallx,
	findallmemx,
	VarxClear,
	memdump,
	writeStr,
};


void readLine(String^ Line_, int MaxLine) {
	if (Line_->IndexOf(" ") >= 0) {  /// it mean this command 
		String^ cmd_ = Line_->Substring(0, Line_->IndexOf(" "));
		//ScriptargumentClass::Scriptargument_->Commandenum->
		int ret = ScriptargumentClass::Scriptargument_->isCommandsExist(cmd_->Trim());
		switch (ret)
		{
		case Scriptw:
			break;
		case LogxJustAtBP:
			break;
		case LogxTemplateManager:
			break;
		case logxwindow:
			break;
		case logx:
			break;
		case logxTrace:
			break;
		case StrCompx:
			break;
		case Varx:
			break;
		case Getx:
			break;
		case Printx:
			break;
		case Setx:
			break;
		case Movx:
			break;
		case addx:
			break;
		case subx:
			break;
		case mulx:
			break;
		case andx:
			break;
		case orx:
			break;
		case xorx:
			break;
		case shlx:
			break;
		case pushx:
			break;
		case popx:
			break;
		case cmpx:
			break;
		case findx:
			break;
		case findallx:
			break;
		case findallmemx:
			break;
		case VarxClear:
			break;
		case memdump:
			break;
		case writeStr:
			break;
		default:
			break;
		}


	}

}
