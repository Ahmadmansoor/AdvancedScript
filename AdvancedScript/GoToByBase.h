#pragma once
#include "HelperFunctions.h"
namespace AdvancedScript {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace Microsoft::VisualBasic;

	/// <summary>
	/// Summary for GoToByBase
	/// </summary>
	public ref class GoToByBase : public System::Windows::Forms::Form
	{
	public:
		GoToByBase(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~GoToByBase()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::TextBox^  TB_OldAddress;
	protected:

	private: System::Windows::Forms::TextBox^  TB_oldBase;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  LB_FileName;

	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::TextBox^  TB_NewBase;
	private: System::Windows::Forms::CheckBox^  CB_RVA;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->TB_OldAddress = (gcnew System::Windows::Forms::TextBox());
			this->TB_oldBase = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->LB_FileName = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->TB_NewBase = (gcnew System::Windows::Forms::TextBox());
			this->CB_RVA = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->CB_RVA);
			this->groupBox1->Controls->Add(this->TB_OldAddress);
			this->groupBox1->Controls->Add(this->TB_oldBase);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Location = System::Drawing::Point(4, 2);
			this->groupBox1->Margin = System::Windows::Forms::Padding(5, 4, 5, 4);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Padding = System::Windows::Forms::Padding(5, 4, 5, 4);
			this->groupBox1->Size = System::Drawing::Size(275, 242);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Set outer data here";
			// 
			// TB_OldAddress
			// 
			this->TB_OldAddress->Location = System::Drawing::Point(99, 56);
			this->TB_OldAddress->Multiline = true;
			this->TB_OldAddress->Name = L"TB_OldAddress";
			this->TB_OldAddress->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->TB_OldAddress->Size = System::Drawing::Size(166, 150);
			this->TB_OldAddress->TabIndex = 3;
			this->TB_OldAddress->WordWrap = false;
			this->TB_OldAddress->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &GoToByBase::TB_OldAddress_MouseDoubleClick);
			this->TB_OldAddress->MouseHover += gcnew System::EventHandler(this, &GoToByBase::TB_OldAddress_MouseHover);
			// 
			// TB_oldBase
			// 
			this->TB_oldBase->Location = System::Drawing::Point(99, 24);
			this->TB_oldBase->Name = L"TB_oldBase";
			this->TB_oldBase->Size = System::Drawing::Size(166, 26);
			this->TB_oldBase->TabIndex = 2;
			this->TB_oldBase->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(9, 103);
			this->label2->Margin = System::Windows::Forms::Padding(5, 0, 5, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(86, 19);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Address\'s";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(17, 29);
			this->label1->Margin = System::Windows::Forms::Padding(5, 0, 5, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(78, 19);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Old Base";
			// 
			// LB_FileName
			// 
			this->LB_FileName->AutoSize = true;
			this->LB_FileName->Location = System::Drawing::Point(6, 22);
			this->LB_FileName->Margin = System::Windows::Forms::Padding(5, 0, 5, 0);
			this->LB_FileName->Name = L"LB_FileName";
			this->LB_FileName->Size = System::Drawing::Size(94, 19);
			this->LB_FileName->TabIndex = 2;
			this->LB_FileName->Text = L"File Name :";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(8, 53);
			this->label4->Margin = System::Windows::Forms::Padding(5, 0, 5, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(87, 19);
			this->label4->TabIndex = 3;
			this->label4->Text = L"File base :";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->TB_NewBase);
			this->groupBox2->Controls->Add(this->LB_FileName);
			this->groupBox2->Controls->Add(this->label4);
			this->groupBox2->Location = System::Drawing::Point(4, 249);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(275, 100);
			this->groupBox2->TabIndex = 4;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Current file:";
			// 
			// TB_NewBase
			// 
			this->TB_NewBase->Location = System::Drawing::Point(103, 50);
			this->TB_NewBase->Name = L"TB_NewBase";
			this->TB_NewBase->ReadOnly = true;
			this->TB_NewBase->Size = System::Drawing::Size(162, 26);
			this->TB_NewBase->TabIndex = 4;
			this->TB_NewBase->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->TB_NewBase->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &GoToByBase::TB_NewBase_MouseDoubleClick);
			this->TB_NewBase->MouseHover += gcnew System::EventHandler(this, &GoToByBase::TB_NewBase_MouseHover);
			// 
			// CB_RVA
			// 
			this->CB_RVA->AutoSize = true;
			this->CB_RVA->Location = System::Drawing::Point(21, 140);
			this->CB_RVA->Name = L"CB_RVA";
			this->CB_RVA->Size = System::Drawing::Size(61, 23);
			this->CB_RVA->TabIndex = 4;
			this->CB_RVA->Text = L"RVA";
			this->CB_RVA->UseVisualStyleBackColor = true;
			// 
			// GoToByBase
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(10, 19);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(289, 353);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Margin = System::Windows::Forms::Padding(5, 4, 5, 4);
			this->MaximizeBox = false;
			this->Name = L"GoToByBase";
			this->Text = L"GoToByBase";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void TB_NewBase_MouseHover(System::Object^  sender, System::EventArgs^  e) {
		ToolTip^ toolTip = gcnew ToolTip;
		toolTip->SetToolTip(TB_NewBase, " DbClick on CPU Window to Get Module Base");
	}
	private: System::Void TB_OldAddress_MouseHover(System::Object^  sender, System::EventArgs^  e) {
		ToolTip^ toolTip = gcnew ToolTip;
		toolTip->SetToolTip(TB_NewBase, " DbClick on line to go to");
	}
	private: System::Void TB_OldAddress_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		duint Offset_ = 0;
		duint NewAddr = 0;
		String^ intvalue_oldBase;
		String^ intvalue_oldAddress;
		String^ intvalue_NewBase;
		if (!CB_RVA->Checked) {
			if (TB_oldBase->Text == "") {
				Interaction::MsgBox("fill Old base Pls", MsgBoxStyle::OkOnly, "Error");
				return;
			}			
			if (CheckHexIsValid(TB_oldBase->Text, intvalue_oldBase) == 0) {
				Interaction::MsgBox("Old base is wrong", MsgBoxStyle::OkOnly, "Error");
				return;
			}
		}
		String^ currentLine = GetCurrentLine();
		if (currentLine->Trim() == "") {
			return;
		}
		if (currentLine->Contains(" ")) {
			currentLine = currentLine->Substring(0, currentLine->IndexOf(" "));
		}

		if (CheckHexIsValid(currentLine->Trim(), intvalue_oldAddress) == 0) {
			Interaction::MsgBox("Current Line is wrong", MsgBoxStyle::OkOnly, "Error");
			return;
		}

		if (TB_NewBase->Text == "") {
			Interaction::MsgBox("fill new base Pls", MsgBoxStyle::OkOnly, "Error");
			return;
		}
		if (CheckHexIsValid(TB_NewBase->Text, intvalue_NewBase) == 0) {
			Interaction::MsgBox("Current base is wrong", MsgBoxStyle::OkOnly, "Error");
			return;
		}
		if (!CB_RVA->Checked) {
			Offset_ = Str2duint(intvalue_oldAddress) - Str2duint(intvalue_oldBase);
		}
		else
		{
			Offset_ = Str2duint(intvalue_oldAddress);
		}
		NewAddr = Str2duint(intvalue_NewBase) + Offset_;
		DbgCmdExecDirect(Str2ConstChar("dis " + duint2Hex(NewAddr)));

	}

	private: String^ GetCurrentLine() {
		int CurrentLine = TB_OldAddress->GetLineFromCharIndex(TB_OldAddress->GetFirstCharIndexOfCurrentLine());
		return TB_OldAddress->Lines[CurrentLine];
	}
	private: System::Void TB_NewBase_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		duint base_ = Script::Module::BaseFromAddr(Script::Gui::SelectionGetStart(Script::Gui::DisassemblyWindow));
		TB_NewBase->Text = duint2Hex(base_);
		char* name_ = new char[255];
		Script::Module::NameFromAddr(base_, name_);
		LB_FileName->Text = "File Name : " + CharArr2Str(name_);
	}
	};
}
