#pragma once
#include "ScriptArgumentWindow.h"
#include "ScriptFun.h"

namespace AdvancedScript {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace ScriptWindowArg;
	/// <summary>
	/// Summary for MainForm
	/// </summary>

	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:

		MainForm(void)
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
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataGridView^  DGV1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  ID;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Command;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  describe;
	private: System::Windows::Forms::ContextMenuStrip^  CMT1;
	private: System::Windows::Forms::ToolStripMenuItem^  startHereToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  pasteToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  copySelectedLineToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  insertRowsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  insertDataFromClipboardToolStripMenuItem;
	private: System::Windows::Forms::TreeView^  TrViewScript;


	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::ContextMenuStrip^  CMT_TreeView;
	private: System::Windows::Forms::ToolStripMenuItem^  deletToolStripMenuItem;

	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::TreeView^  TrViewVariable;
	private: System::Windows::Forms::Button^  Bu_ClearVariable;
	private: System::Windows::Forms::ToolStripMenuItem^  createCategoryToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  renameToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saveScriptFileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  newScriptToolStripMenuItem;



	private: System::ComponentModel::IContainer^  components;


	protected:




	protected:

	public:
		String^ ScriptFileName = String::Empty;
		bool Run = false;

	public:

	public:
	private: System::Windows::Forms::ToolStripMenuItem^  saveAsToolStripMenuItem;
	public:

	/*public: ref class LableLine
	{
	public:
		LableLine(int LableLineNumber_, String^ Lable_) {
			LableLineNumber = LableLineNumber_;
			Lable = Lable_;
		}

	private:
	public:
		int LableLineNumber;
		String^ Lable;
	};
	public:
		static Generic::List<LableLine^>^ LableLines = gcnew Generic::List<LableLine^>;

	public:static LableLine^ GetLineByLable(String^ input) {
		for each (LableLine^ var in LableLines)
		{
			if (var->Lable == input) {
				return var;
			}
		}
		return gcnew LableLine(0, "");
	}*/

	public: ref class ArraySortAssist
	{
	public:
		ArraySortAssist(int index_, String^ Cmd_, String^ disc_) {
			index = index_;
			Cmd = Cmd_;
			disc = disc_;
		}

	public:
		int index;
		String^ Cmd;
		String^ disc;
	};

			/*public:
				Generic::List<ArraySortAssist^>^ ArraySortAssist_ = gcnew Generic::List<ArraySortAssist^>;*/


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle3 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			this->DGV1 = (gcnew System::Windows::Forms::DataGridView());
			this->ID = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Command = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->describe = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->CMT1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->newScriptToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveScriptFileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveAsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->startHereToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pasteToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->copySelectedLineToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->insertRowsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->insertDataFromClipboardToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->TrViewScript = (gcnew System::Windows::Forms::TreeView());
			this->CMT_TreeView = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->createCategoryToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->renameToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->deletToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->Bu_ClearVariable = (gcnew System::Windows::Forms::Button());
			this->TrViewVariable = (gcnew System::Windows::Forms::TreeView());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DGV1))->BeginInit();
			this->CMT1->SuspendLayout();
			this->CMT_TreeView->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// DGV1
			// 
			this->DGV1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->DGV1->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle1->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle1->Font = (gcnew System::Drawing::Font(L"Courier New", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle1->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle1->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle1->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle1->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->DGV1->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
			this->DGV1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->DGV1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {
				this->ID, this->Command,
					this->describe
			});
			this->DGV1->ContextMenuStrip = this->CMT1;
			dataGridViewCellStyle3->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle3->BackColor = System::Drawing::SystemColors::Window;
			dataGridViewCellStyle3->Font = (gcnew System::Drawing::Font(L"Courier New", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle3->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle3->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle3->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle3->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->DGV1->DefaultCellStyle = dataGridViewCellStyle3;
			this->DGV1->Location = System::Drawing::Point(274, 26);
			this->DGV1->Name = L"DGV1";
			this->DGV1->Size = System::Drawing::Size(767, 504);
			this->DGV1->TabIndex = 0;
			this->DGV1->CellEndEdit += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MainForm::DGV1_CellEndEdit);
			this->DGV1->RowsAdded += gcnew System::Windows::Forms::DataGridViewRowsAddedEventHandler(this, &MainForm::DGV1_RowsAdded);
			this->DGV1->RowsRemoved += gcnew System::Windows::Forms::DataGridViewRowsRemovedEventHandler(this, &MainForm::DGV1_RowsRemoved);
			this->DGV1->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::DGV1_KeyUp);
			// 
			// ID
			// 
			dataGridViewCellStyle2->NullValue = L"0";
			this->ID->DefaultCellStyle = dataGridViewCellStyle2;
			this->ID->FillWeight = 25;
			this->ID->HeaderText = L"ID";
			this->ID->Name = L"ID";
			this->ID->ReadOnly = true;
			// 
			// Command
			// 
			this->Command->FillWeight = 200;
			this->Command->HeaderText = L"Command";
			this->Command->Name = L"Command";
			// 
			// describe
			// 
			this->describe->FillWeight = 200;
			this->describe->HeaderText = L"describe";
			this->describe->Name = L"describe";
			// 
			// CMT1
			// 
			this->CMT1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {
				this->fileToolStripMenuItem,
					this->startHereToolStripMenuItem, this->pasteToolStripMenuItem, this->copySelectedLineToolStripMenuItem, this->insertRowsToolStripMenuItem,
					this->insertDataFromClipboardToolStripMenuItem
			});
			this->CMT1->Name = L"CMT1";
			this->CMT1->Size = System::Drawing::Size(243, 136);
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->newScriptToolStripMenuItem,
					this->saveScriptFileToolStripMenuItem, this->saveAsToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(242, 22);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// newScriptToolStripMenuItem
			// 
			this->newScriptToolStripMenuItem->Name = L"newScriptToolStripMenuItem";
			this->newScriptToolStripMenuItem->Size = System::Drawing::Size(131, 22);
			this->newScriptToolStripMenuItem->Text = L"New Script";
			this->newScriptToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::newScriptToolStripMenuItem_Click);
			// 
			// saveScriptFileToolStripMenuItem
			// 
			this->saveScriptFileToolStripMenuItem->Name = L"saveScriptFileToolStripMenuItem";
			this->saveScriptFileToolStripMenuItem->Size = System::Drawing::Size(131, 22);
			this->saveScriptFileToolStripMenuItem->Text = L"Save";
			this->saveScriptFileToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::saveScriptFileToolStripMenuItem_Click);
			// 
			// saveAsToolStripMenuItem
			// 
			this->saveAsToolStripMenuItem->Name = L"saveAsToolStripMenuItem";
			this->saveAsToolStripMenuItem->Size = System::Drawing::Size(131, 22);
			this->saveAsToolStripMenuItem->Text = L"Save As";
			this->saveAsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::saveAsToolStripMenuItem_Click);
			// 
			// startHereToolStripMenuItem
			// 
			this->startHereToolStripMenuItem->Name = L"startHereToolStripMenuItem";
			this->startHereToolStripMenuItem->Size = System::Drawing::Size(242, 22);
			this->startHereToolStripMenuItem->Text = L"Run from Here";
			this->startHereToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::startHereToolStripMenuItem_Click);
			// 
			// pasteToolStripMenuItem
			// 
			this->pasteToolStripMenuItem->Name = L"pasteToolStripMenuItem";
			this->pasteToolStripMenuItem->Size = System::Drawing::Size(242, 22);
			this->pasteToolStripMenuItem->Text = L"Paste Clipboard/replace all lines";
			this->pasteToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::pasteToolStripMenuItem_Click);
			// 
			// copySelectedLineToolStripMenuItem
			// 
			this->copySelectedLineToolStripMenuItem->Name = L"copySelectedLineToolStripMenuItem";
			this->copySelectedLineToolStripMenuItem->Size = System::Drawing::Size(242, 22);
			this->copySelectedLineToolStripMenuItem->Text = L"Copy Selected Line";
			this->copySelectedLineToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::copySelectedLineToolStripMenuItem_Click);
			// 
			// insertRowsToolStripMenuItem
			// 
			this->insertRowsToolStripMenuItem->Name = L"insertRowsToolStripMenuItem";
			this->insertRowsToolStripMenuItem->Size = System::Drawing::Size(242, 22);
			this->insertRowsToolStripMenuItem->Text = L"Insert /n/ rows Here";
			this->insertRowsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::insertRowsToolStripMenuItem_Click);
			// 
			// insertDataFromClipboardToolStripMenuItem
			// 
			this->insertDataFromClipboardToolStripMenuItem->Name = L"insertDataFromClipboardToolStripMenuItem";
			this->insertDataFromClipboardToolStripMenuItem->Size = System::Drawing::Size(242, 22);
			this->insertDataFromClipboardToolStripMenuItem->Text = L"Insert Script From Clipboard";
			this->insertDataFromClipboardToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::insertDataFromClipboardToolStripMenuItem_Click);
			// 
			// TrViewScript
			// 
			this->TrViewScript->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->TrViewScript->ContextMenuStrip = this->CMT_TreeView;
			this->TrViewScript->Location = System::Drawing::Point(11, 19);
			this->TrViewScript->Name = L"TrViewScript";
			this->TrViewScript->Size = System::Drawing::Size(244, 168);
			this->TrViewScript->TabIndex = 1;
			this->TrViewScript->NodeMouseDoubleClick += gcnew System::Windows::Forms::TreeNodeMouseClickEventHandler(this, &MainForm::TrViewScript_NodeMouseDoubleClick);
			// 
			// CMT_TreeView
			// 
			this->CMT_TreeView->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->createCategoryToolStripMenuItem,
					this->renameToolStripMenuItem, this->deletToolStripMenuItem
			});
			this->CMT_TreeView->Name = L"CMT_TreeView";
			this->CMT_TreeView->Size = System::Drawing::Size(160, 70);
			// 
			// createCategoryToolStripMenuItem
			// 
			this->createCategoryToolStripMenuItem->Name = L"createCategoryToolStripMenuItem";
			this->createCategoryToolStripMenuItem->Size = System::Drawing::Size(159, 22);
			this->createCategoryToolStripMenuItem->Text = L"Create Category";
			this->createCategoryToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::createCategoryToolStripMenuItem_Click);
			// 
			// renameToolStripMenuItem
			// 
			this->renameToolStripMenuItem->Name = L"renameToolStripMenuItem";
			this->renameToolStripMenuItem->Size = System::Drawing::Size(159, 22);
			this->renameToolStripMenuItem->Text = L"Rename";
			this->renameToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::renameToolStripMenuItem_Click);
			// 
			// deletToolStripMenuItem
			// 
			this->deletToolStripMenuItem->Name = L"deletToolStripMenuItem";
			this->deletToolStripMenuItem->Size = System::Drawing::Size(159, 22);
			this->deletToolStripMenuItem->Text = L"Delet";
			this->deletToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::deletToolStripMenuItem_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left));
			this->groupBox1->Controls->Add(this->Bu_ClearVariable);
			this->groupBox1->Controls->Add(this->TrViewVariable);
			this->groupBox1->Controls->Add(this->TrViewScript);
			this->groupBox1->Location = System::Drawing::Point(7, 3);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(261, 524);
			this->groupBox1->TabIndex = 4;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Options";
			// 
			// Bu_ClearVariable
			// 
			this->Bu_ClearVariable->Location = System::Drawing::Point(11, 193);
			this->Bu_ClearVariable->Name = L"Bu_ClearVariable";
			this->Bu_ClearVariable->Size = System::Drawing::Size(119, 26);
			this->Bu_ClearVariable->TabIndex = 5;
			this->Bu_ClearVariable->Text = L"Clear Variable";
			this->Bu_ClearVariable->UseVisualStyleBackColor = true;
			this->Bu_ClearVariable->Click += gcnew System::EventHandler(this, &MainForm::Bu_ClearVariable_Click);
			// 
			// TrViewVariable
			// 
			this->TrViewVariable->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->TrViewVariable->Location = System::Drawing::Point(11, 225);
			this->TrViewVariable->Name = L"TrViewVariable";
			this->TrViewVariable->Size = System::Drawing::Size(244, 291);
			this->TrViewVariable->TabIndex = 1;
			// 
			// checkBox1
			// 
			this->checkBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->checkBox1->AutoSize = true;
			this->checkBox1->Checked = true;
			this->checkBox1->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox1->Enabled = false;
			this->checkBox1->Location = System::Drawing::Point(908, 3);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(133, 17);
			this->checkBox1->TabIndex = 0;
			this->checkBox1->Text = L"Update Script Window";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::SlateGray;
			this->ClientSize = System::Drawing::Size(1047, 534);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->DGV1);
			this->KeyPreview = true;
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::MainForm_KeyUp);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DGV1))->EndInit();
			this->CMT1->ResumeLayout(false);
			this->CMT_TreeView->ResumeLayout(false);
			this->groupBox1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MainForm_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		if (e->KeyCode == Keys::F12)
			DGV1->Focus();
	}
	private: System::Void IniLoadData() {   /// we use it to get all lable in the script to use it for Goto
		LableLineClass::LableLines->Clear();
		for (int i = 0; i < DGV1->RowCount - 1; i++)
		{
			DGV1->Rows[i]->Cells[0]->Value = i; // duint2Hex(i) + "/" + i;   // fill first colume with number 0 1 2 3 ....
			if (DGV1->Rows[i]->Cells[1]->Value != nullptr) {
				if (DGV1->Rows[i]->Cells[1]->Value->ToString()->Trim()->EndsWith(":")) {
					String^ LableHold = DGV1->Rows[i]->Cells[1]->Value->ToString()->Trim()->Substring(0, DGV1->Rows[i]->Cells[1]->Value->ToString()->Trim()->IndexOf(":"));
					LableLine^ LaL = gcnew LableLine(i, LableHold);
					LableLineClass::LableLines->Add(LaL);
				}
			}
		}
	}
	private: System::Void DGV1_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		if (e->KeyCode == Keys::F12) {
			DGV1->ClearSelection();
			if (ScriptargumentClass::Scriptargument_->GetLineNumber() == 0) {
				IniLoadData();  /// get all lable in the Script
				ScriptargumentClass::Scriptargument_->setMaxLine(DGV1->RowCount - 1);  // update max line 
			}
			if (ScriptargumentClass::Scriptargument_->GetLineNumber() < DGV1->RowCount - 1) {
				DGV1->ClearSelection();
				DGV1->Rows[ScriptargumentClass::Scriptargument_->GetLineNumber()]->Selected = true;
				if (DGV1->Rows[ScriptargumentClass::Scriptargument_->GetLineNumber()]->Cells[1]->Value != nullptr) {
					readLine(DGV1->Rows[ScriptargumentClass::Scriptargument_->GetLineNumber()]->Cells[1]->Value->ToString(), DGV1->Rows->Count);
				}
				else
					readLine("", DGV1->Rows->Count);
				
			}
			else
			{
				DGV1->ClearSelection();
				DGV1->Rows[0]->Selected = true;
				ScriptargumentClass::Scriptargument_->setLineNumber(0);
			}
			if (reten_) { reten_ = false; }
			FileVariableTreeView();
		}
		if (e->KeyCode == Keys::F11) {
			if (Run)
				Run = false;
			else
				Run = true;			

			while (Run)
			{
				Application::DoEvents();
				DGV1->ClearSelection();
				if (ScriptargumentClass::Scriptargument_->GetLineNumber() == 0) {
					IniLoadData();  /// get all lable in the Script
					ScriptargumentClass::Scriptargument_->setMaxLine(DGV1->RowCount - 1);  // update max line 
				}
				if (ScriptargumentClass::Scriptargument_->GetLineNumber() < DGV1->RowCount - 1) {
					DGV1->ClearSelection();
					DGV1->Rows[ScriptargumentClass::Scriptargument_->GetLineNumber()]->Selected = true;
					if (DGV1->Rows[ScriptargumentClass::Scriptargument_->GetLineNumber()]->Cells[1]->Value != nullptr) {
						if (!readLine(DGV1->Rows[ScriptargumentClass::Scriptargument_->GetLineNumber()]->Cells[1]->Value->ToString(), DGV1->Rows->Count)) {
							Run = false;
						}
						else
						{
							Script::Debug::Wait();
						}
					}
					else
						if (!readLine("", DGV1->Rows->Count)) {
							Run = false;
						}
						else
						{
							Script::Debug::Wait();
						}
				}
				else
				{
					DGV1->ClearSelection();
					DGV1->Rows[0]->Selected = true;
					ScriptargumentClass::Scriptargument_->setLineNumber(0);
					Run = false;
				}
				FileVariableTreeView();
				if (reten_) {   /// it mean it hit ret command
					reten_ = false;
					Run = false;
				}
				Application::DoEvents();
			}

		}
	}
	private: System::Void DGV1_RowsAdded(System::Object^  sender, System::Windows::Forms::DataGridViewRowsAddedEventArgs^  e) {
		for (int i = 0; i < DGV1->RowCount - 1; i++)
		{
			DGV1->Rows[i]->Cells[0]->Value = i; // duint2Hex(i) + "/" + i;
		}
		//IniLoadData();
	}
	private: System::Void DGV1_RowsRemoved(System::Object^  sender, System::Windows::Forms::DataGridViewRowsRemovedEventArgs^  e) {
		/*for (int i = 0; i < DGV1->RowCount - 1; i++)
		{
			DGV1->Rows[i]->Cells[0]->Value = i;
		}*/
		IniLoadData();
	}
	private: System::Void startHereToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		ScriptargumentClass::Scriptargument_->setLineNumber(DGV1->CurrentRow->Index);
	}
	private: System::Void pasteToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		DGV1->Rows->Clear();
		Generic::List<String^>^ lines = GetClipBoard();
		for (int i = 0; i < lines->Count; i++)
		{
			DGV1->Rows->Add();
			DGV1->Rows[i]->Cells[0]->Value = i;
			if (lines[i]->Contains("//")) {
				DGV1->Rows[i]->Cells[1]->Value = (lines[i]->Substring(0, lines[i]->IndexOf("//")))->Trim();
				DGV1->Rows[i]->Cells[2]->Value = (lines[i]->Substring(lines[i]->IndexOf("//") + 2, lines[i]->Length - (lines[i]->IndexOf("//") + 2)))->Trim();
			}
			else {
				DGV1->Rows[i]->Cells[1]->Value = lines[i]->Trim();
			}
		}
	}
	private: System::Void copySelectedLineToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		String^ HoldClipBoradStr = String::Empty;
		DataGridViewSelectedRowCollection^ DGVRC = DGV1->SelectedRows;
		//array<ArraySortAssist^>^ arrayRows = gcnew array<ArraySortAssist^>(DGVRC->Count);
		array<int>^ arrayRowsindex = gcnew array<int>(DGVRC->Count);
		for (int i = 0; i < DGVRC->Count; i++)
		{
			arrayRowsindex[i] = Conversion::Val(DGVRC[i]->Cells[0]->Value);

		}
		Array::Sort(arrayRowsindex);
		for (int i = 0; i < DGVRC->Count; i++)
		{
			int xx = arrayRowsindex[i];
			if (DGV1->Rows[xx]->Cells[1]->Value != nullptr) {
				if (DGV1->Rows[xx]->Cells[2]->Value == nullptr) {
					HoldClipBoradStr += DGV1->Rows[xx]->Cells[1]->Value->ToString() + Environment::NewLine;
				}
				else {
					HoldClipBoradStr += DGV1->Rows[xx]->Cells[1]->Value->ToString() + " //" + DGV1->Rows[xx]->Cells[2]->Value->ToString() + Environment::NewLine;
				}
			}

		}
		SetClipBoard(HoldClipBoradStr);
	}
	private: System::Void insertRowsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		String^ rowsCou = Interaction::InputBox("Please Enter how many rows you need", "info", "", this->Width / 2, this->Height / 2);
		if (Information::IsNumeric(rowsCou))
			DGV1->Rows->Insert(DGV1->CurrentRow->Index, Conversion::Val(rowsCou));
		else
			Script::Gui::Message(Str2ConstChar(rowsCou + " :is not int"));
	}
	private: System::Void insertDataFromClipboardToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		Generic::List<String^>^ lines = GetClipBoard();
		int rowIndex = DGV1->CurrentRow->Index;
		for (int i = 0; i < lines->Count; i++)
		{
			DGV1->Rows->Insert(rowIndex, 1);
			//DGV1->Rows[i]->Cells[0]->Value = i;
			if (lines[i]->Contains("//")) {
				DGV1->Rows[rowIndex]->Cells[1]->Value = (lines[i]->Substring(0, lines[i]->IndexOf("//")))->Trim();
				DGV1->Rows[rowIndex]->Cells[2]->Value = (lines[i]->Substring(lines[i]->IndexOf("//") + 2, lines[i]->Length - (lines[i]->IndexOf("//") + 2)))->Trim();
			}
			else {
				DGV1->Rows[rowIndex]->Cells[1]->Value = lines[i]->Trim();
			}
			rowIndex += 1;
		}

	}
	private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e) {
		if (!IO::Directory::Exists(Application::StartupPath + "\\Script")) {
			IO::Directory::CreateDirectory(Application::StartupPath + "\\Script");
			//IO::Directory::CreateDirectory(Application::StartupPath + "\\Script\\temp");
		}
		/*if (!IO::Directory::Exists(Application::StartupPath + "\\Script\\temp")) {
			IO::Directory::CreateDirectory(Application::StartupPath + "\\Script\\temp");
		}*/
		FillTrView();  // fill tree on load 

	}

	private:System::Void FillTrView() {  /// tp fill treeiew with category and files
		TrViewScript->Nodes->Clear();
		int i = 0;
		for each (String^ var in System::IO::Directory::GetDirectories(Application::StartupPath + "\\Script\\"))
		{
			TrViewScript->Nodes->Add(IO::Path::GetFileName(var));
			for each (String^ filevar in IO::Directory::GetFiles(var))
			{
				TrViewScript->Nodes[i]->Nodes->Add(IO::Path::GetFileName(filevar));
			}
			i += 1;
		}
	}

	private: System::Void LoadScriptFile(String^ filepath) {  /// load Script file in DataGridView
		DGV1->Rows->Clear();
		array<String^>^ lines = IO::File::ReadAllLines(filepath);
		int i = 0;
		for each (String^ var in lines) {
			if (var != "") {
				if (var->Contains("//")) {
					DGV1->Rows->Add();
					DGV1->Rows[i]->Cells[0]->Value = i;
					DGV1->Rows[i]->Cells[1]->Value = (var->Substring(0, var->IndexOf("//")))->Trim();
					DGV1->Rows[i]->Cells[2]->Value = (var->Substring(var->IndexOf("//") + 2, var->Length - (var->IndexOf("//") + 2)))->Trim();
				}
				else {
					DGV1->Rows->Add();
					DGV1->Rows[i]->Cells[0]->Value = i;
					DGV1->Rows[i]->Cells[1]->Value = var->Trim();
				}
				i += 1;
			}
		}
		IniLoadData();
	}

	private: System::Void SaveScriptFile(String^ filepath) {  /// Save Script file from DataGridView to Disk
		String^ HoldClipBoradStr;
		for (int i = 0; i < DGV1->RowCount; i++)
		{
			if (DGV1->Rows[i]->Cells[1]->Value != nullptr) {
				if (DGV1->Rows[i]->Cells[2]->Value == nullptr) {
					HoldClipBoradStr += DGV1->Rows[i]->Cells[1]->Value->ToString() + Environment::NewLine;
				}
				else {
					HoldClipBoradStr += DGV1->Rows[i]->Cells[1]->Value->ToString() + " //" + DGV1->Rows[i]->Cells[2]->Value->ToString() + Environment::NewLine;
				}
			}
		}
		IO::File::WriteAllText(filepath, HoldClipBoradStr);
		//FillTrView();
	}
	private: System::Void TrViewScript_NodeMouseDoubleClick(System::Object^  sender, System::Windows::Forms::TreeNodeMouseClickEventArgs^  e) {
		if (TrViewScript->SelectedNode->Level != 0) {
			LoadScriptFile(Application::StartupPath + "\\Script\\" + TrViewScript->SelectedNode->Parent->Text + "\\" + TrViewScript->SelectedNode->Text);
			ScriptargumentClass::Scriptargument_->setMaxLine(DGV1->RowCount - 1);  // update max line just in case update script through run
			ScriptFileName = TrViewScript->SelectedNode->Parent->Text + "\\" + TrViewScript->SelectedNode->Text;
		}
	}

	private: System::Void deletToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		if (Interaction::MsgBox("Are you sure??!!", MsgBoxStyle::OkCancel, "Delete") == MsgBoxResult::Ok) {
			if (TrViewScript->SelectedNode->Level == 0) {
				IO::Directory::Delete(Application::StartupPath + "\\Script\\" + TrViewScript->SelectedNode->Text, true);
				TrViewScript->SelectedNode->Remove();
				DGV1->Rows->Clear();
				ScriptFileName = "";
			}
			else
			{
				IO::File::Delete(Application::StartupPath + "\\Script\\" + TrViewScript->SelectedNode->Parent->Text + "\\" + TrViewScript->SelectedNode->Text);
				TrViewScript->SelectedNode->Remove();
				DGV1->Rows->Clear();
				ScriptFileName = "";
			}
		}
		else {
			return;
		}
	}

	private: System::Void FileVariableTreeView() {
		TrViewVariable->Nodes->Clear();
		int i = 0;
		for each (VarPara^ var in ScriptFunList::VarList)
		{
			if (var->vartype == "int") {
				TrViewVariable->Nodes->Add(var->varname);
				TrViewVariable->Nodes[i]->Nodes->Add(duint2Hex(Str2duint(var->varvalue[0])));
			}
			if (var->vartype == "str") {
				TrViewVariable->Nodes->Add(var->varname);
				TrViewVariable->Nodes[i]->Nodes->Add(var->varvalue[0]);
			}
			if (var->vartype == "array") {
				TrViewVariable->Nodes->Add(var->varname);
				for (int i1 = 0; i1 < var->arrayLength; i1++)
				{
					TrViewVariable->Nodes[i]->Nodes->Add(var->varvalue[i1]);
				}
			}
			i += 1;
		}
	}

	private: System::Void Bu_ClearVariable_Click(System::Object^  sender, System::EventArgs^  e) {
		VarListClear();
		TrViewVariable->Nodes->Clear();
	}
	private: System::Void createCategoryToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		String^ Category_ = Interaction::InputBox("Enter Category Name", "Category Name", "Category" + TrViewScript->Nodes->Count, this->Width / 2, this->Height / 2);
		if (Category_ == "") {
			Interaction::MsgBox("this Category name not Valid", MsgBoxStyle::DefaultButton1, "Error");
			return;
		}
		if (IO::Directory::Exists((Application::StartupPath + "\\Script\\" + Category_))) {
			Interaction::MsgBox("this Category is Exist", MsgBoxStyle::DefaultButton1, "Error");
			return;
		}
		else
		{
			IO::Directory::CreateDirectory(Application::StartupPath + "\\Script\\" + Category_);
			TrViewScript->Nodes->Add(Category_);
		}
	}
	private: System::Void renameToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		String^ renamed;
		if (TrViewScript->SelectedNode->Level == 0) {

			String^ Category_ = Interaction::InputBox("Enter Category Name", "Category Name", TrViewScript->SelectedNode->Text, this->Width / 2, this->Height / 2);
			if (Category_ == "") {
				Interaction::MsgBox("this Category name not Valid", MsgBoxStyle::DefaultButton1, "Error");
				return;
			}

			FileSystem::Rename(Application::StartupPath + "\\Script\\" + TrViewScript->SelectedNode->Text, Application::StartupPath + "\\Script\\" + Category_);
			TrViewScript->SelectedNode->Text = Category_;
		}
		else
		{
			String^ Category_ = Interaction::InputBox("Enter file Name", "Category Name", TrViewScript->SelectedNode->Text, this->Width / 2, this->Height / 2);
			if (Category_ == "") {
				Interaction::MsgBox("this file name not Valid", MsgBoxStyle::DefaultButton1, "Error");
				return;
			}
			if (Category_->Trim()->EndsWith(".txt")) {
				Category_ = Category_->Substring(0, Category_->IndexOf(".txt"));
			}
			FileSystem::Rename(Application::StartupPath + "\\Script\\" + TrViewScript->SelectedNode->Parent->Text + "\\" + TrViewScript->SelectedNode->Text, Application::StartupPath + "\\Script\\" + TrViewScript->SelectedNode->Parent->Text + "\\" + Category_ + ".txt");
			TrViewScript->SelectedNode->Text = Category_ + ".txt";
		}

	}
	private: System::Void newScriptToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		DGV1->Rows->Clear();
		VarListClear();
		TrViewVariable->Nodes->Clear();
		ScriptFileName = "";

	}
	private: System::Void DGV1_CellEndEdit(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
		ScriptargumentClass::Scriptargument_->setMaxLine(DGV1->RowCount - 1);  // update max line just in case update script through run
		IniLoadData();
	}
	private: System::Void saveScriptFileToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

		if (ScriptFileName != "") {
			SaveScriptFile(Application::StartupPath + "\\Script\\" + ScriptFileName);
		}
		else
		{
			saveAsToolStripMenuItem_Click(sender, e);
		}

		/*String^ Filename = Interaction::InputBox("Enter Category Name", "Category Name", "File" + TrViewScript->Nodes->Count, this->Width / 2, this->Height / 2);
		if (Filename == "") {
			Interaction::MsgBox("this Filename name not Valid", MsgBoxStyle::DefaultButton1, "Error");
			return;
		}
		if (Filename->Trim()->EndsWith(".txt")) {
			Filename = Filename->Substring(0, Filename->IndexOf(".txt"));
		}
		if (TrViewScript->SelectedNode == nullptr) {
			Interaction::MsgBox("Please Select Category ", MsgBoxStyle::DefaultButton1, "Error");
			return;
		}
		String^ Category_;

		if (TrViewScript->SelectedNode->Level == 0) {
			Category_ = TrViewScript->SelectedNode->Text;
		}
		else
		{
			Category_ = TrViewScript->SelectedNode->Parent->Text;
		}

		if (!IO::File::Exists((Application::StartupPath + "\\Script\\" + Category_ + "\\" + Filename + ".txt"))) {
			SaveScriptFile(Application::StartupPath + "\\Script\\" + Category_ + "\\" + Filename + ".txt");
			if (TrViewScript->SelectedNode->Level == 0)
				TrViewScript->SelectedNode->Nodes->Add(Filename + ".txt");
			else
				TrViewScript->SelectedNode->Parent->Nodes->Add(Filename + ".txt");
		}
		else
		{
			if (Interaction::MsgBox("this File is Exist,Over Write it ??!!", MsgBoxStyle::OkCancel, "Error") == MsgBoxResult::Ok) {
				SaveScriptFile(Application::StartupPath + "\\Script\\" + Category_ + "\\" + Filename + ".txt");
				if (TrViewScript->SelectedNode->Level == 0)
					TrViewScript->SelectedNode->Nodes->Add(Filename + ".txt");
				else
					TrViewScript->SelectedNode->Parent->Nodes->Add(Filename + ".txt");
			}
			else {
				return;
			}
		}*/

	}
	private: System::Void saveAsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		String^ Filename = Interaction::InputBox("Enter File Name", "File Name", "File" + TrViewScript->Nodes->Count, this->Width / 2, this->Height / 2);
		if (Filename == "") {
			Interaction::MsgBox("this Filename name not Valid", MsgBoxStyle::DefaultButton1, "Error");
			return;
		}
		if (Filename->Trim()->EndsWith(".txt")) {
			Filename = Filename->Substring(0, Filename->IndexOf(".txt"));
		}
		if (TrViewScript->SelectedNode == nullptr) {
			Interaction::MsgBox("Please Select Category ", MsgBoxStyle::DefaultButton1, "Error");
			return;
		}
		String^ Category_;

		if (TrViewScript->SelectedNode->Level == 0) {
			Category_ = TrViewScript->SelectedNode->Text;
		}
		else
		{
			Category_ = TrViewScript->SelectedNode->Parent->Text;
		}

		if (!IO::File::Exists((Application::StartupPath + "\\Script\\" + Category_ + "\\" + Filename + ".txt"))) {
			SaveScriptFile(Application::StartupPath + "\\Script\\" + Category_ + "\\" + Filename + ".txt");
			ScriptFileName = Category_ + "\\" + Filename + ".txt";
			if (TrViewScript->SelectedNode->Level == 0)
				TrViewScript->SelectedNode->Nodes->Add(Filename + ".txt");
			else
				TrViewScript->SelectedNode->Parent->Nodes->Add(Filename + ".txt");
		}
		else
		{
			if (Interaction::MsgBox("this File is Exist,Over Write it ??!!", MsgBoxStyle::OkCancel, "Error") == MsgBoxResult::Ok) {
				SaveScriptFile(Application::StartupPath + "\\Script\\" + Category_ + "\\" + Filename + ".txt");
				ScriptFileName = Category_ + "\\" + Filename + ".txt";
				if (TrViewScript->SelectedNode->Level == 0)
					TrViewScript->SelectedNode->Nodes->Add(Filename + ".txt");
				else
					TrViewScript->SelectedNode->Parent->Nodes->Add(Filename + ".txt");
			}
			else {
				return;
			}
		}

	}
	
};
}
