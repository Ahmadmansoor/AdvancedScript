#pragma once
#include "HelperFunctions.h"
#include "Register_UnRegister_Commands.h"
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
			int CmdExist = ScriptargumentClass::Scriptargument_->isCommandsExist(cmd_->Trim());
			if (CmdExist >= 0) {
				char* argv = new char[50] ;
				//argv[1] = Str2CharPTR(Line_);
				strcpy(argv, Str2CharPTR(Line_));
				//_plugin_logputs(argv);
				switch (CmdExist)
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
					Varx(0, &argv);
					break;
				case ScriptWindowArg::getx:
					GetVarx(0, &argv);
					break;
				case ScriptWindowArg::printx:
					GetVarx(0, &argv);
					break;
				case ScriptWindowArg::setx:
					SetVarx(0, &argv);
					break;
				case ScriptWindowArg::movx:
					SetVarx(0, &argv);
					break;
				case ScriptWindowArg::addx:
					::addx(0, &argv);
					break;
				case ScriptWindowArg::subx:
					::subx(0, &argv);
					break;
				case ScriptWindowArg::mulx:
					::mulx(0, &argv);
					break;
				case ScriptWindowArg::andx:
					::andx(0, &argv);
					break;
				case ScriptWindowArg::orx:
					::orx(0, &argv);
					break;
				case ScriptWindowArg::xorx:
					::xorx(0, &argv);
					break;
				case ScriptWindowArg::shlx:
					::shlx(0, &argv);
					break;
				case ScriptWindowArg::pushx:
					::pushx(0, &argv);
					break;
				case ScriptWindowArg::popx:
					::popx(0, &argv);
					break;
				case ScriptWindowArg::cmpx:
					::cmpx(0, &argv);
					break;
				case ScriptWindowArg::findx:
					::findx(0, &argv);
					break;
				case ScriptWindowArg::findallx:
					::findallx(0, &argv);
					break;
				case ScriptWindowArg::findallmemx:
					::findallmemx(0, &argv);
					break;
				case ScriptWindowArg::varxclear:
					::VarxClear(0, &argv);
					break;
				case ScriptWindowArg::memdump:
					::memdump(0, &argv);
					break;
				case ScriptWindowArg::writestr:
					::WriteStr(0, &argv);
					break;
				default: // case non of them begin with command
					DbgCmdExecDirect(Str2ConstChar(Line_));
					break;
				}
				ScriptargumentClass::Scriptargument_->setLineNumber(ScriptargumentClass::Scriptargument_->GetLineNumber() + 1);
				return;
			}
			else
			{
				ScriptargumentClass::Scriptargument_->setLineNumber(ScriptargumentClass::Scriptargument_->GetLineNumber() + 1);
				DbgCmdExecDirect(Str2ConstChar(Line_));
				return;

			}
		}

	}

}