#pragma once
#include "HelperFunctions.h"
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;


namespace ScriptWindowArg {

	ref class Scriptargument
	{
	private:
		int lineNumber = 0;
	public:
		int isCommandsExist(String^ input_) {
			array <String^>^ CommandsArray_ = {
				"scriptw",
				"logxjustatbp",
				"logxtemplatemanager",
				"logxwindow",
				"logx",
				"logxtrace",
				"strcompx",
				"varx",
				"getx",
				"printx",
				"setx",
				"movx",
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
				"varxclear",
				"memdump",
				"writestr"
			};
			return Array::IndexOf(CommandsArray_, input_->ToLower()); // if -1 then not found 
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
		scriptw,
		logxjustatbp,
		logxtemplatemanager,
		logxwindow,
		logx,
		logxtrace,
		strcompx,
		varx,
		getx,
		printx,
		setx,
		movx,
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
		varxclear,
		memdump,
		writestr,
	};


	void readLine(String^ Line_, int MaxLine) {
		if (Line_->Trim()->IndexOf(" ") > 0) {  /// >0 it mean it has command at the begining
			String^ cmd_ = Line_->Substring(0, Line_->IndexOf(" "));
			int ret = ScriptargumentClass::Scriptargument_->isCommandsExist(cmd_->Trim());
			//Generic::List<String^>^ arguments;
			//GetArg(Line_, arguments); // this function use by refrence so the list will fill direct	
			char* argv[] = { " " };
			argv[1] = Str2CharPTR(Line_);
			switch (ret)
			{
			case ScriptWindowArg::scriptw:
				break;
			case ScriptWindowArg::logxjustatbp:
				break;
			case ScriptWindowArg::logxtemplatemanager:
				break;
			case ScriptWindowArg::logxwindow:
				break;
			case ScriptWindowArg::logx:
				break;
			case ScriptWindowArg::logxtrace:
				break;
			case ScriptWindowArg::strcompx:
				break;
			case ScriptWindowArg::varx:
				break;
			case ScriptWindowArg::getx:
				break;
			case ScriptWindowArg::printx:
				break;
			case ScriptWindowArg::setx:
				break;
			case ScriptWindowArg::movx:
				break;
			case ScriptWindowArg::addx:
				break;
			case ScriptWindowArg::subx:
				break;
			case ScriptWindowArg::mulx:
				break;
			case ScriptWindowArg::andx:
				break;
			case ScriptWindowArg::orx:
				break;
			case ScriptWindowArg::xorx:
				break;
			case ScriptWindowArg::shlx:
				break;
			case ScriptWindowArg::pushx:
				break;
			case ScriptWindowArg::popx:
				break;
			case ScriptWindowArg::cmpx:
				break;
			case ScriptWindowArg::findx:
				break;
			case ScriptWindowArg::findallx:
				break;
			case ScriptWindowArg::findallmemx:
				break;
			case ScriptWindowArg::varxclear:
				break;
			case ScriptWindowArg::memdump:
				break;
			case ScriptWindowArg::writestr:
				break;
			default:
				break;
			}		

		}

	}

}