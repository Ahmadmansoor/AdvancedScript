#pragma once
//#include "HelperFunctions.h"
#include "Register_UnRegister_Commands.h"
//#include "ScriptFun.h"


using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Drawing;

namespace ScriptWindowArg {

	ref class Scriptargument
	{
		/*public:
			Boolean ispaused = false;*/
	private:
		int CurrentlineIndex = 0;
		int MaxLine = 0;
		Color OldColor;
		int OldLineIndex = 0;
	public:
		int isCommandsExist(String^ input_) {
			array <String^>^ CommandsArray_ = {
				/*"scriptw",
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
				"writestr",*/
				"if",
				"goto"
			};
			return Array::IndexOf(CommandsArray_, input_->ToLower()); // if -1 then not found 
		};
	public:
		int CommandsNeedwait(String^ input_) {   /// this command need time to finish so we will make wait clock gif so user no thing it is not responding
			array <String^>^ CommandsArray_ = {
				"BPxx",
				"findallmemx"
			};
			return Array::IndexOf(CommandsArray_, input_->ToLower()); // if -1 then not found 
		};
	public:	void setCurrentlineIndex(int LineIndx) {
		CurrentlineIndex = LineIndx;
	}
	public: void SetOldlineIndex_Color(int OldLineIndex_, Color color_) {
		OldColor = color_;
		OldLineIndex = OldLineIndex_;
	}
	public: void setOldColor(Color color_) {
		OldColor = color_;
	}
	public: Color GetOldColor() {
		return OldColor;
	}
	public:	void setMaxLine(int MaxLine_) {
		MaxLine = MaxLine_;
	}
	public:	int GetMaxLine() {
		return MaxLine;
	}
	public:	int GetCurrentlineIndex() {
		return CurrentlineIndex;
	}
	public:	void SetOldlineIndex(int OldLineIndex_) {
		OldLineIndex = OldLineIndex_;
	}
	public:	int GetOldlineIndex() {
		return OldLineIndex;
	}
	};

	ref class ScriptargumentClass
	{
	public:
		static Scriptargument^ Scriptargument_ = gcnew Scriptargument;
	};

	enum Commandenum {
		//no need any more we left them to x64dbg to handle
		/*scriptw,
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
		writestr,*/
		ifx,
		goto_
	};

	bool reten_ = false;

	bool readLine(String^ Line_, int MaxLine) {
		bool ret_ = false;
		/// remove description if exist 
		if (Line_->Contains("//"))
			Line_ = Line_->Substring(0, Line_->IndexOf("//"));

		if (Line_->Trim()->EndsWith(":")) {
			ScriptargumentClass::Scriptargument_->setCurrentlineIndex(ScriptargumentClass::Scriptargument_->GetCurrentlineIndex() + 1);
			return true;
		}
		if (Line_->Trim() == "") {
			ScriptargumentClass::Scriptargument_->setCurrentlineIndex(ScriptargumentClass::Scriptargument_->GetCurrentlineIndex() + 1);
			return true;
		}
		if (Line_->Trim()->ToLower() == "ret") {
			///reset Script
			//ScriptargumentClass::Scriptargument_->SetOldlineIndex(0);
			//ScriptargumentClass::Scriptargument_->setCurrentlineIndex(0);
			reten_ = true;
			return true;
		}
		/// case of assign variable directly without use Setx Function
		if ((Line_->Trim()->StartsWith("$")) && (Line_->Trim()->Contains("="))) {
			String^ getVar = Line_->Trim()->Substring(0, Line_->Trim()->IndexOf("="));
			int indexofVar = 0; 	String^ retvartype = ""; int arrayLength;
			if (Varexist(getVar, retvartype, indexofVar, arrayLength)) {
				String^ cmd1 = "Setx " + Line_->Trim();
				cmd1 = cmd1->Replace("=", ",");
				ScriptargumentClass::Scriptargument_->setCurrentlineIndex(ScriptargumentClass::Scriptargument_->GetCurrentlineIndex() + 1);
				return SetxByString(Str2CharPTR(cmd1));
			}
		}
		

		//IspausedClass::IspausedClass_->ispaused = false;  /// rest is pause till the debugger back to pause

		if (Line_->Trim()->IndexOf(" ") > 0) {  /// >0 it mean it has command at the begining			
			String^ cmd_ = Line_->Substring(0, Line_->IndexOf(" "));
			int CmdExist = ScriptargumentClass::Scriptargument_->isCommandsExist(cmd_->Trim());
			if (CmdExist >= 0) {
				switch (CmdExist)
				{
					/*case ScriptWindowArg::scriptw:
						break;
					case ScriptWindowArg::logxjustatbp:
						ret_ = ::cbLogxJustAtBP(0, &argv);
						break;
					case ScriptWindowArg::logxtemplatemanager:
						break;
					case ScriptWindowArg::logxwindow:
						break;
					case ScriptWindowArg::logx:
						ret_ = ::logx(0, &argv);
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
						break;*/
				case ScriptWindowArg::ifx:
				{
					String^ Line2Jmp_;
					ret_ = ifCond(Line_, Line2Jmp_, ScriptargumentClass::Scriptargument_->GetCurrentlineIndex());
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

						ScriptargumentClass::Scriptargument_->setCurrentlineIndex(Line2Jmp);
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
						ScriptargumentClass::Scriptargument_->setCurrentlineIndex(Line2Jmp);
						return true;
					}
				}
				default: // case non of them begin with command
					ret_ = DbgCmdExecDirect(Str2ConstChar(Line_));
					break;
				}
				if (ret_) {
					ScriptargumentClass::Scriptargument_->setCurrentlineIndex(ScriptargumentClass::Scriptargument_->GetCurrentlineIndex() + 1);
					return ret_;
				}
				else
				{
					//Script::Gui::Message(Str2ConstChar("this Line have error" + Environment::NewLine + Line_));
					_plugin_logputs(Str2ConstChar("this Line have error" + Environment::NewLine + Line_));
				}
			}
			else
			{
				ret_ = DbgCmdExecDirect(Str2ConstChar(Line_));
				//Script::Debug::Wait();
				if (ret_) {
					ScriptargumentClass::Scriptargument_->setCurrentlineIndex(ScriptargumentClass::Scriptargument_->GetCurrentlineIndex() + 1);
					return ret_;
				}
				else
				{
					//Script::Gui::Message(Str2ConstChar("this Line have error" + Environment::NewLine + Line_));
					_plugin_logputs(Str2ConstChar("this Line have error" + Environment::NewLine + Line_));
				}
				return ret_;

			}
		}
		else
		{
			ret_ = DbgCmdExecDirect(Str2ConstChar(Line_));
			//Script::Debug::Wait();
			if (ret_) {
				ScriptargumentClass::Scriptargument_->setCurrentlineIndex(ScriptargumentClass::Scriptargument_->GetCurrentlineIndex() + 1);
				return ret_;
			}
			else
			{
				//Script::Gui::Message(Str2ConstChar("this Line have error" + Environment::NewLine + Line_));
				_plugin_logputs(Str2ConstChar("this Line have error" + Environment::NewLine + Line_));
			}
			return ret_;
		}

		return ret_;

	}

	void waitPauseProcess() {
		if (!DbgIsDebugging())
			return;
		do
		{
			//Threading::Thread::Sleep(100);
			Application::DoEvents();
		} while (!IspausedClass::IspausedClass_->ispaused);

	}


	bool Need_wait(String^ cmd_) {
		if (cmd_->Trim()->Contains(" ")) {
			cmd_ = cmd_->Substring(0, cmd_->IndexOf(" "));  /// get command
			int Need_wait = ScriptargumentClass::Scriptargument_->CommandsNeedwait(cmd_->ToLower()->Trim());
			if (Need_wait >= 0) {
				return true;
			}
		}
		return false;
	}

}