#pragma once
#include "HelperFunctions.h"
#include "Register_UnRegister_Commands.h"
#include "ScriptFun.h"
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;


namespace ScriptWindowArg {
 
	ref class Scriptargument
	{
	private:
		int lineNumber = 0;
		int MaxLine = 0;
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
				"writestr",
				"if",
				"goto"
			};
			return Array::IndexOf(CommandsArray_, input_->ToLower()); // if -1 then not found 
		};
	public:
		void setLineNumber(int LineNum) {
			lineNumber = LineNum;
		};
	public:
		void setMaxLine(int MaxLine_) {
			MaxLine = MaxLine_;
		}
	public:
		int GetMaxLine() {
			return MaxLine ;
		}
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
		ifx,
		goto_,
	};


	bool readLine(String^ Line_, int MaxLine) {
		bool ret_ = false;
		if (Line_->Trim()->EndsWith(":")) {
			ScriptargumentClass::Scriptargument_->setLineNumber(ScriptargumentClass::Scriptargument_->GetLineNumber() + 1);
			return true;
		}
		if (Line_->Trim() == "") {
			ScriptargumentClass::Scriptargument_->setLineNumber(ScriptargumentClass::Scriptargument_->GetLineNumber() + 1);
			return true;
		}
		if (Line_->Trim()->IndexOf(" ") > 0) {  /// >0 it mean it has command at the begining			
			String^ cmd_ = Line_->Substring(0, Line_->IndexOf(" "));

			int CmdExist = ScriptargumentClass::Scriptargument_->isCommandsExist(cmd_->Trim());
			if (CmdExist >= 0) {
				char* argv = new char[50];
				//argv[1] = Str2CharPTR(Line_);
				strcpy(argv, Str2CharPTR(Line_));
				//_plugin_logputs(argv);
				switch (CmdExist)
				{
				case ScriptWindowArg::scriptw:
					break;
				case ScriptWindowArg::logxjustatbp:
					ret_ = ::cbLogxJustAtBP(0, &argv);
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
					ret_ = Varx(0, &argv);
					break;
				case ScriptWindowArg::getx:
					ret_ = GetVarx(0, &argv);
					break;
				case ScriptWindowArg::printx:
					ret_ = GetVarx(0, &argv);
					break;
				case ScriptWindowArg::setx:
					ret_ = SetVarx(0, &argv);
					break;
				case ScriptWindowArg::movx:
					ret_ = ::Movx(0, &argv);
					break;
				case ScriptWindowArg::addx:
					ret_ = ::addx(0, &argv);
					break;
				case ScriptWindowArg::subx:
					ret_ = ::subx(0, &argv);
					break;
				case ScriptWindowArg::mulx:
					ret_ = ::mulx(0, &argv);
					break;
				case ScriptWindowArg::andx:
					ret_ = ::andx(0, &argv);
					break;
				case ScriptWindowArg::orx:
					ret_ = ::orx(0, &argv);
					break;
				case ScriptWindowArg::xorx:
					ret_ = ::xorx(0, &argv);
					break;
				case ScriptWindowArg::shlx:
					ret_ = ::shlx(0, &argv);
					break;
				case ScriptWindowArg::pushx:
					ret_ = ::pushx(0, &argv);
					break;
				case ScriptWindowArg::popx:
					ret_ = ::popx(0, &argv);
					break;
				case ScriptWindowArg::cmpx:
					ret_ = ::cmpx(0, &argv);
					break;
				case ScriptWindowArg::findx:
					ret_ = ::findx(0, &argv);
					break;
				case ScriptWindowArg::findallx:
					ret_ = ::findallx(0, &argv);
					break;
				case ScriptWindowArg::findallmemx:
					ret_ = ::findallmemx(0, &argv);
					break;
				case ScriptWindowArg::varxclear:
					ret_ = ::VarxClear(0, &argv);
					break;
				case ScriptWindowArg::memdump:
					ret_ = ::memdump(0, &argv);
					break;
				case ScriptWindowArg::writestr:
					ret_ = ::WriteStr(0, &argv);
					break;
				case ScriptWindowArg::ifx:
				{
					String^ Line2Jmp_;
					ret_ = ifCond(Line_, Line2Jmp_);
					if (!ret_) {
						break;
					}
					int Line2Jmp = Str2duint(Line2Jmp_);
					int MaxLine = ScriptargumentClass::Scriptargument_->GetMaxLine();
					if (Line2Jmp > MaxLine) {
						ret_ = false;
					}
					else
					{
						ScriptargumentClass::Scriptargument_->setLineNumber(Line2Jmp);
						return true;
					}
					break; 
				}
				case ScriptWindowArg::goto_: {
					String^ Line2Jmp_;
					ret_ = gotox_(Line_, Line2Jmp_);
					if (!ret_) {
						break;
					}
					int Line2Jmp = Str2duint(Line2Jmp_);
					int MaxLine = ScriptargumentClass::Scriptargument_->GetMaxLine();
					if (Line2Jmp > MaxLine) {
						ret_ = false;
					}
					else
					{
						ScriptargumentClass::Scriptargument_->setLineNumber(Line2Jmp);
						return true;
					}
				}
				default: // case non of them begin with command
					ret_ = DbgCmdExecDirect(Str2ConstChar(Line_));
					break;
				}
				if (ret_) {
					ScriptargumentClass::Scriptargument_->setLineNumber(ScriptargumentClass::Scriptargument_->GetLineNumber() + 1);
					return ret_;
				}
				else
				{
					Script::Gui::Message(Str2ConstChar("this Line have error" + Environment::NewLine + Line_));
				}
			}
			else
			{
				ret_ = DbgCmdExecDirect(Str2ConstChar(Line_));
				if (ret_) {
					ScriptargumentClass::Scriptargument_->setLineNumber(ScriptargumentClass::Scriptargument_->GetLineNumber() + 1);
					return ret_;
				}
				else
				{
					Script::Gui::Message(Str2ConstChar("this Line have error" + Environment::NewLine + Line_));
				}
				return ret_;

			}
		}
		return ret_;

	}

}