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
	using namespace AutocompleteMenuNS;
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




	private: System::Windows::Forms::TreeView^  TrViewScript;


	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::ContextMenuStrip^  CMT_TreeView;
	private: System::Windows::Forms::ToolStripMenuItem^  deletToolStripMenuItem;


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
	private: System::Windows::Forms::PictureBox^  PB_wait;






	public:
		static String^ LoadAllText_ = String::Empty;
	public:
		TextBox^ tb1;
	public:

	public:
	private: System::Windows::Forms::ToolStripMenuItem^  saveAsToolStripMenuItem;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPage_CommandHelp;
	private: System::Windows::Forms::TabPage^  tabPage_Log;
	private: System::Windows::Forms::TextBox^  TB_CommandHelp;


			 ////////////////
	public:ref class HelpLoad
	{
	private:
		String^ cmd;
		String^ info;

	public:
		HelpLoad(String^ cmd_, String^ info_) {
			cmd = cmd_->Trim()->ToLower();
			info = info_;
		}
	public:
		String^ Getcmd_() {
			return cmd;
		}
	public:
		String^ Getinfo_() {
			return info;
		}
	};
	public:
		Generic::List<HelpLoad^>^ HelpLoad_List = gcnew Generic::List<HelpLoad^>;
	private: System::Windows::Forms::ListBox^  LB_Function;
	private: System::Windows::Forms::Button^  Bu_VarListRefresh;
	private: System::Windows::Forms::CheckBox^  CB_AutoUpdate;
	private: System::Windows::Forms::ContextMenuStrip^  CMT_VariableList;
	private: System::Windows::Forms::ToolStripMenuItem^  removeVariableToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  followToCPUToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  followToDumpToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  copyToClipboardToolStripMenuItem;
	private: AutocompleteMenuNS::AutocompleteMenu^  autocomplete_List;

	private:


	private: System::Windows::Forms::RichTextBox^  RTB_Script;
	public:
		///////////

	public: ref class Variables
	{
	public:
		Variables(int index_, String^ Cmd_) {
			index = index_;
			Cmd = Cmd_;
		}
	public:
		bool is_indexExist(int index_) {
			if (index_ == index)
				return true;
			else
				return false;
		}
	public: int GetIndex() {
		return index;
	}
	public: String^ GetCmd() {
		return Cmd;
	}
	public: void updateCmd(String^ cmd_) {
		Cmd = cmd_;
	}
	private:
		int index;
		String^ Cmd;
	};


	public:
		Generic::List<Variables^>^ Variables_List = gcnew Generic::List<Variables^>;

		/////////////////
	public: ref class AutoCompleteMainList
	{
	public:
		AutoCompleteMainList(String^ cmd_, String^ describ, Color^ color_) {
			Cmd = cmd_;
			descriB = describ;
			coloR = color_;
		}
	public: bool isComdExist(String^ inputCmd) {
		if (inputCmd == Cmd) {
			return true;
		}
		else
		{
			return false;
		}
	}

	private:
		String^ Cmd;
		String^ descriB;
		Color^ coloR;
	};

			Generic::List<AutoCompleteMainList^>^ autoCompleteMainList = gcnew Generic::List<AutoCompleteMainList^>;

			///////////////
	public:
		int GetRTB_lineNum() {
			int cursorPosition = RTB_Script->SelectionStart;
			int lineIndex = RTB_Script->GetLineFromCharIndex(cursorPosition);
			return lineIndex;
		}
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
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle4 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle6 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle5 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
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
			this->TrViewScript = (gcnew System::Windows::Forms::TreeView());
			this->CMT_TreeView = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->createCategoryToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->renameToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->deletToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->CB_AutoUpdate = (gcnew System::Windows::Forms::CheckBox());
			this->Bu_VarListRefresh = (gcnew System::Windows::Forms::Button());
			this->Bu_ClearVariable = (gcnew System::Windows::Forms::Button());
			this->TrViewVariable = (gcnew System::Windows::Forms::TreeView());
			this->CMT_VariableList = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->removeVariableToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->followToCPUToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->followToDumpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->copyToClipboardToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PB_wait = (gcnew System::Windows::Forms::PictureBox());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage_CommandHelp = (gcnew System::Windows::Forms::TabPage());
			this->LB_Function = (gcnew System::Windows::Forms::ListBox());
			this->TB_CommandHelp = (gcnew System::Windows::Forms::TextBox());
			this->tabPage_Log = (gcnew System::Windows::Forms::TabPage());
			this->autocomplete_List = (gcnew AutocompleteMenuNS::AutocompleteMenu());
			this->RTB_Script = (gcnew System::Windows::Forms::RichTextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DGV1))->BeginInit();
			this->CMT1->SuspendLayout();
			this->CMT_TreeView->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->CMT_VariableList->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB_wait))->BeginInit();
			this->tabControl1->SuspendLayout();
			this->tabPage_CommandHelp->SuspendLayout();
			this->SuspendLayout();
			// 
			// DGV1
			// 
			this->DGV1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->DGV1->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			dataGridViewCellStyle4->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle4->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle4->Font = (gcnew System::Drawing::Font(L"Courier New", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle4->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle4->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle4->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle4->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->DGV1->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle4;
			this->DGV1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->DGV1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {
				this->ID, this->Command,
					this->describe
			});
			this->DGV1->ContextMenuStrip = this->CMT1;
			dataGridViewCellStyle6->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle6->BackColor = System::Drawing::SystemColors::Window;
			dataGridViewCellStyle6->Font = (gcnew System::Drawing::Font(L"Courier New", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle6->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle6->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle6->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle6->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->DGV1->DefaultCellStyle = dataGridViewCellStyle6;
			this->DGV1->Location = System::Drawing::Point(274, 11);
			this->DGV1->Name = L"DGV1";
			this->DGV1->Size = System::Drawing::Size(746, 115);
			this->DGV1->TabIndex = 0;
			// 
			// ID
			// 
			dataGridViewCellStyle5->NullValue = L"0";
			this->ID->DefaultCellStyle = dataGridViewCellStyle5;
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
			this->CMT1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->fileToolStripMenuItem,
					this->startHereToolStripMenuItem
			});
			this->CMT1->Name = L"CMT1";
			this->CMT1->Size = System::Drawing::Size(153, 48);
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->newScriptToolStripMenuItem,
					this->saveScriptFileToolStripMenuItem, this->saveAsToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(152, 22);
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
			this->startHereToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->startHereToolStripMenuItem->Text = L"Run from Here";
			this->startHereToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::startHereToolStripMenuItem_Click);
			// 
			// TrViewScript
			// 
			this->TrViewScript->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->TrViewScript->ContextMenuStrip = this->CMT_TreeView;
			this->TrViewScript->Location = System::Drawing::Point(11, 19);
			this->TrViewScript->Name = L"TrViewScript";
			this->TrViewScript->Size = System::Drawing::Size(244, 168);
			this->TrViewScript->TabIndex = 0;
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
			this->groupBox1->Controls->Add(this->CB_AutoUpdate);
			this->groupBox1->Controls->Add(this->Bu_VarListRefresh);
			this->groupBox1->Controls->Add(this->Bu_ClearVariable);
			this->groupBox1->Controls->Add(this->TrViewVariable);
			this->groupBox1->Controls->Add(this->TrViewScript);
			this->groupBox1->Location = System::Drawing::Point(7, 3);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(261, 606);
			this->groupBox1->TabIndex = 1;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Options";
			// 
			// CB_AutoUpdate
			// 
			this->CB_AutoUpdate->AutoSize = true;
			this->CB_AutoUpdate->Location = System::Drawing::Point(92, 199);
			this->CB_AutoUpdate->Name = L"CB_AutoUpdate";
			this->CB_AutoUpdate->Size = System::Drawing::Size(83, 17);
			this->CB_AutoUpdate->TabIndex = 7;
			this->CB_AutoUpdate->Text = L"AutoUpdate";
			this->CB_AutoUpdate->UseVisualStyleBackColor = true;
			// 
			// Bu_VarListRefresh
			// 
			this->Bu_VarListRefresh->Location = System::Drawing::Point(10, 193);
			this->Bu_VarListRefresh->Name = L"Bu_VarListRefresh";
			this->Bu_VarListRefresh->Size = System::Drawing::Size(81, 26);
			this->Bu_VarListRefresh->TabIndex = 3;
			this->Bu_VarListRefresh->Text = L"Refresh list";
			this->Bu_VarListRefresh->UseVisualStyleBackColor = true;
			this->Bu_VarListRefresh->Click += gcnew System::EventHandler(this, &MainForm::Bu_VarListRefresh_Click);
			// 
			// Bu_ClearVariable
			// 
			this->Bu_ClearVariable->Location = System::Drawing::Point(174, 193);
			this->Bu_ClearVariable->Name = L"Bu_ClearVariable";
			this->Bu_ClearVariable->Size = System::Drawing::Size(81, 26);
			this->Bu_ClearVariable->TabIndex = 1;
			this->Bu_ClearVariable->Text = L"Clear Variable";
			this->Bu_ClearVariable->UseVisualStyleBackColor = true;
			this->Bu_ClearVariable->Click += gcnew System::EventHandler(this, &MainForm::Bu_ClearVariable_Click);
			// 
			// TrViewVariable
			// 
			this->TrViewVariable->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->TrViewVariable->ContextMenuStrip = this->CMT_VariableList;
			this->TrViewVariable->Location = System::Drawing::Point(11, 225);
			this->TrViewVariable->Name = L"TrViewVariable";
			this->TrViewVariable->Size = System::Drawing::Size(244, 373);
			this->TrViewVariable->TabIndex = 2;
			// 
			// CMT_VariableList
			// 
			this->CMT_VariableList->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->removeVariableToolStripMenuItem,
					this->followToCPUToolStripMenuItem, this->followToDumpToolStripMenuItem, this->copyToClipboardToolStripMenuItem
			});
			this->CMT_VariableList->Name = L"CMT_VariableList";
			this->CMT_VariableList->Size = System::Drawing::Size(172, 92);
			// 
			// removeVariableToolStripMenuItem
			// 
			this->removeVariableToolStripMenuItem->Name = L"removeVariableToolStripMenuItem";
			this->removeVariableToolStripMenuItem->Size = System::Drawing::Size(171, 22);
			this->removeVariableToolStripMenuItem->Text = L"Remove Variable";
			this->removeVariableToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::removeVariableToolStripMenuItem_Click);
			// 
			// followToCPUToolStripMenuItem
			// 
			this->followToCPUToolStripMenuItem->Name = L"followToCPUToolStripMenuItem";
			this->followToCPUToolStripMenuItem->Size = System::Drawing::Size(171, 22);
			this->followToCPUToolStripMenuItem->Text = L"Follow to CPU";
			this->followToCPUToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::followToCPUToolStripMenuItem_Click);
			// 
			// followToDumpToolStripMenuItem
			// 
			this->followToDumpToolStripMenuItem->Name = L"followToDumpToolStripMenuItem";
			this->followToDumpToolStripMenuItem->Size = System::Drawing::Size(171, 22);
			this->followToDumpToolStripMenuItem->Text = L"Follow to Dump";
			this->followToDumpToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::followToDumpToolStripMenuItem_Click);
			// 
			// copyToClipboardToolStripMenuItem
			// 
			this->copyToClipboardToolStripMenuItem->Name = L"copyToClipboardToolStripMenuItem";
			this->copyToClipboardToolStripMenuItem->Size = System::Drawing::Size(171, 22);
			this->copyToClipboardToolStripMenuItem->Text = L"CopyTo Clipboard";
			this->copyToClipboardToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::copyToClipboardToolStripMenuItem_Click);
			// 
			// PB_wait
			// 
			this->PB_wait->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"PB_wait.Image")));
			this->PB_wait->Location = System::Drawing::Point(891, 3);
			this->PB_wait->Name = L"PB_wait";
			this->PB_wait->Size = System::Drawing::Size(193, 197);
			this->PB_wait->TabIndex = 5;
			this->PB_wait->TabStop = false;
			this->PB_wait->Visible = false;
			// 
			// tabControl1
			// 
			this->tabControl1->Alignment = System::Windows::Forms::TabAlignment::Left;
			this->tabControl1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tabControl1->Controls->Add(this->tabPage_CommandHelp);
			this->tabControl1->Controls->Add(this->tabPage_Log);
			this->tabControl1->Location = System::Drawing::Point(277, 442);
			this->tabControl1->Multiline = true;
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(807, 167);
			this->tabControl1->TabIndex = 6;
			// 
			// tabPage_CommandHelp
			// 
			this->tabPage_CommandHelp->BackColor = System::Drawing::Color::Silver;
			this->tabPage_CommandHelp->Controls->Add(this->LB_Function);
			this->tabPage_CommandHelp->Controls->Add(this->TB_CommandHelp);
			this->tabPage_CommandHelp->Location = System::Drawing::Point(23, 4);
			this->tabPage_CommandHelp->Name = L"tabPage_CommandHelp";
			this->tabPage_CommandHelp->Padding = System::Windows::Forms::Padding(3);
			this->tabPage_CommandHelp->Size = System::Drawing::Size(780, 159);
			this->tabPage_CommandHelp->TabIndex = 0;
			this->tabPage_CommandHelp->Text = L"CommandHelp";
			// 
			// LB_Function
			// 
			this->LB_Function->FormattingEnabled = true;
			this->LB_Function->Location = System::Drawing::Point(4, 5);
			this->LB_Function->Name = L"LB_Function";
			this->LB_Function->Size = System::Drawing::Size(114, 147);
			this->LB_Function->TabIndex = 1;
			this->LB_Function->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::LB_Function_SelectedIndexChanged);
			// 
			// TB_CommandHelp
			// 
			this->TB_CommandHelp->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->autocomplete_List->SetAutocompleteMenu(this->TB_CommandHelp, nullptr);
			this->TB_CommandHelp->BackColor = System::Drawing::Color::Black;
			this->TB_CommandHelp->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->TB_CommandHelp->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->TB_CommandHelp->Location = System::Drawing::Point(117, 3);
			this->TB_CommandHelp->Multiline = true;
			this->TB_CommandHelp->Name = L"TB_CommandHelp";
			this->TB_CommandHelp->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->TB_CommandHelp->Size = System::Drawing::Size(660, 152);
			this->TB_CommandHelp->TabIndex = 0;
			// 
			// tabPage_Log
			// 
			this->tabPage_Log->BackColor = System::Drawing::Color::DimGray;
			this->tabPage_Log->ForeColor = System::Drawing::Color::Red;
			this->tabPage_Log->Location = System::Drawing::Point(23, 4);
			this->tabPage_Log->Name = L"tabPage_Log";
			this->tabPage_Log->Padding = System::Windows::Forms::Padding(3);
			this->tabPage_Log->Size = System::Drawing::Size(780, 159);
			this->tabPage_Log->TabIndex = 1;
			this->tabPage_Log->Text = L"Log";
			// 
			// autocomplete_List
			// 
			this->autocomplete_List->AppearInterval = 150;
			this->autocomplete_List->Colors = (cli::safe_cast<AutocompleteMenuNS::Colors^>(resources->GetObject(L"autocomplete_List.Colors")));
			this->autocomplete_List->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
			this->autocomplete_List->ImageList = nullptr;
			this->autocomplete_List->Items = gcnew cli::array< System::String^  >(0);
			this->autocomplete_List->TargetControlWrapper = nullptr;
			// 
			// RTB_Script
			// 
			this->RTB_Script->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->autocomplete_List->SetAutocompleteMenu(this->RTB_Script, this->autocomplete_List);
			this->RTB_Script->ContextMenuStrip = this->CMT1;
			this->RTB_Script->Location = System::Drawing::Point(276, 137);
			this->RTB_Script->Name = L"RTB_Script";
			this->RTB_Script->Size = System::Drawing::Size(761, 269);
			this->RTB_Script->TabIndex = 7;
			this->RTB_Script->TabStop = false;
			this->RTB_Script->Text = L"";
			this->RTB_Script->WordWrap = false;
			this->RTB_Script->TextChanged += gcnew System::EventHandler(this, &MainForm::RTB_Script_TextChanged);
			this->RTB_Script->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::RTB_Script_KeyDown);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::SlateGray;
			this->ClientSize = System::Drawing::Size(1091, 616);
			this->Controls->Add(this->RTB_Script);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->PB_wait);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->DGV1);
			this->KeyPreview = true;
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::MainForm_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::MainForm_KeyUp);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DGV1))->EndInit();
			this->CMT1->ResumeLayout(false);
			this->CMT_TreeView->ResumeLayout(false);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->CMT_VariableList->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB_wait))->EndInit();
			this->tabControl1->ResumeLayout(false);
			this->tabPage_CommandHelp->ResumeLayout(false);
			this->tabPage_CommandHelp->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion


	private: System::Void IniLoadData() {   /// we use it to get all lable in the script to use it for Goto
											//Done
		LableLineClass::LableLines->Clear();
		Variables_List->Clear();
		//for (int i = 0; i < DGV1->RowCount - 1; i++)
		//{
		//	DGV1->Rows[i]->Cells[0]->Value = i; // duint2Hex(i) + "/" + i;   // fill first colume with number 0 1 2 3 ....
		//	if (DGV1->Rows[i]->Cells[1]->Value != nullptr) {
		//		if (DGV1->Rows[i]->Cells[1]->Value->ToString()->Trim()->EndsWith(":")) {  // find lables
		//			String^ LableHold = DGV1->Rows[i]->Cells[1]->Value->ToString()->Trim()->Substring(0, DGV1->Rows[i]->Cells[1]->Value->ToString()->Trim()->IndexOf(":"));
		//			LableLine^ LaL = gcnew LableLine(i, LableHold);
		//			LableLineClass::LableLines->Add(LaL);
		//		}
		//		if (DGV1->Rows[i]->Cells[1]->Value->ToString()->ToLower()->Trim()->StartsWith("varx")) {  // find variables
		//			if (DGV1->Rows[i]->Cells[1]->Value->ToString()->Contains(",")) {
		//				//String^ cmd = DGV1->Rows[i]->Cells[1]->Value->ToString()->Trim()->Substring(0, DGV1->Rows[i]->Cells[1]->Value->ToString()->Trim()->IndexOf(","));
		//				String^ cmd = DGV1->Rows[i]->Cells[1]->Value->ToString()->Trim();
		//				if ((!cmd->Contains(",")) || (cmd->Trim()->IndexOf(",") + 1 >= cmd->Trim()->Length))  ///// in case we write varx int and not continue 
		//					return;
		//				Generic::List<String^>^ arguments;
		//				GetArg(cmd, arguments);
		//				if (arguments->Count < 2)
		//					return;
		//				if (arguments[0]->ToLower() == "array") {
		//					arguments[1] = arguments[1]->Substring(0, arguments[1]->IndexOf("["));
		//				}
		//				Variables^ LaL = gcnew Variables(i, "$" + arguments[1]);
		//				Variables_List->Add(LaL);
		//			}
		//		}
		//	}
		//}

		for (int i = 0; i < RTB_Script->Lines->Length; i++)
		{
			if (RTB_Script->Lines[i]->Trim() != "") {
				if (RTB_Script->Lines[i]->Trim()->EndsWith(":")) {  // find lables
					String^ LableHold = RTB_Script->Lines[i]->Trim()->Substring(0, RTB_Script->Lines[i]->Trim()->IndexOf(":"));
					LableLine^ LaL = gcnew LableLine(i, LableHold);
					LableLineClass::LableLines->Add(LaL);
				}
				if (RTB_Script->Lines[i]->Trim()->ToLower()->Trim()->StartsWith("varx")) {  // find variables
					if (RTB_Script->Lines[i]->Trim()->Contains(",")) {
						String^ cmd = RTB_Script->Lines[i]->Trim();
						if ((!cmd->Contains(",")) || (cmd->Trim()->IndexOf(",") + 1 >= cmd->Trim()->Length))  ///// in case we write varx int and not continue 
							return;
						Generic::List<String^>^ arguments;
						GetArg(cmd, arguments);
						if (arguments->Count < 2)
							return;
						if (arguments[0]->ToLower() == "array") {
							if (arguments[1]->Contains("[")) {  // check if it has [ for the array
								arguments[1] = arguments[1]->Substring(0, arguments[1]->IndexOf("["));
							}
						}
						Variables^ LaL = gcnew Variables(i, "$" + arguments[1]);
						Variables_List->Add(LaL);
					}
				}
			}
		}

	}


	private: System::Void startHereToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		ScriptargumentClass::Scriptargument_->setLineNumber(GetRTB_lineNum());
	}


	private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e) {
		this->Text = L"AdvancedScript " + CharArr2Str(ads_version) + " For x64dbg / Coded by Ahmadmansoor / exetools";
		if (!IO::Directory::Exists(Application::StartupPath + "\\Script")) {
			IO::Directory::CreateDirectory(Application::StartupPath + "\\Script");
		}
		if (IO::File::Exists(Application::StartupPath + "\\plugins\\HelpAdvancedScript.txt")) {  // load help command			
			array<String^>^ LoadText = IO::File::ReadAllLines(Application::StartupPath + "\\plugins\\HelpAdvancedScript.txt");
			for (int i = 0; i < LoadText->Length; i++)
			{
				String^ temp = LoadText[i];
				if (temp->StartsWith("///")) {
					i += 1;
					if (i >= LoadText->Length)
						break;
					String^ command = LoadText[i];
					String^ infos = String::Empty;
					bool findback = true;
					while (!LoadText[i]->StartsWith("///"))
					{
						i += 1;
						if (i >= LoadText->Length)
							break;
						if (findback) {
							infos = LoadText[i];
						}
						else
						{
							infos = infos + Environment::NewLine + LoadText[i];
						}
						findback = false;
					}
					HelpLoad^ HelpLoad_ = gcnew HelpLoad(command, infos);
					HelpLoad_List->Add(HelpLoad_);
					i -= 1;  /// back to /// place for check 
				}
			}
		}
		for (int i = 0; i < HelpLoad_List->Count; i++)
		{
			LB_Function->Items->Add(HelpLoad_List[i]->Getcmd_());
		}
		FillTrView();  // fill tree on load 
		//TB_CommandHelp->Text = LoadAllText_;

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

		RTB_Script->Text = "";
		RTB_Script->Text = IO::File::ReadAllText(filepath);
		RTB_Script->Text = RTB_Script->Text->Trim();   /// trim unneeded spaces at the end of the file
		//IniLoadData();   no needed because it already doen by RTB_Script_TextChanged
	}

	private: System::Void SaveScriptFile(String^ filepath) {  /// Save Script file from DataGridView to Disk		
		IO::File::WriteAllText(filepath, RTB_Script->Text);
		Microsoft::VisualBasic::Interaction::MsgBox("Done", MsgBoxStyle::DefaultButton1, "Confirm");

	}
	private: System::Void TrViewScript_NodeMouseDoubleClick(System::Object^  sender, System::Windows::Forms::TreeNodeMouseClickEventArgs^  e) {
		if (TrViewScript->SelectedNode == nullptr)
			return;
		if (TrViewScript->SelectedNode->Level != 0) {
			LoadScriptFile(Application::StartupPath + "\\Script\\" + TrViewScript->SelectedNode->Parent->Text + "\\" + TrViewScript->SelectedNode->Text);
			ScriptargumentClass::Scriptargument_->setMaxLine(RTB_Script->Lines->Length);  // update max line just in case update script through run
			ScriptFileName = TrViewScript->SelectedNode->Parent->Text + "\\" + TrViewScript->SelectedNode->Text;
		}
	}

	private: System::Void deletToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		if (TrViewScript->SelectedNode == nullptr)
			return;
		if (Interaction::MsgBox("Are you sure??!!", MsgBoxStyle::OkCancel, "Delete") == MsgBoxResult::Ok) {
			if (TrViewScript->SelectedNode->Level == 0) {
				IO::Directory::Delete(Application::StartupPath + "\\Script\\" + TrViewScript->SelectedNode->Text, true);
				TrViewScript->SelectedNode->Remove();
				RTB_Script->Clear();
				ScriptFileName = "";
			}
			else
			{
				IO::File::Delete(Application::StartupPath + "\\Script\\" + TrViewScript->SelectedNode->Parent->Text + "\\" + TrViewScript->SelectedNode->Text);
				TrViewScript->SelectedNode->Remove();
				RTB_Script->Clear();
				ScriptFileName = "";
			}
		}
		else {
			return;
		}
	}

	private: System::Void FileVariableTreeView() {
		int ParentNode, SubNode;   /// we use it to restore the place of the treeView
		if (TrViewVariable->SelectedNode != nullptr) {
			ParentNode = TrViewVariable->SelectedNode->Parent->Index;
			SubNode = TrViewVariable->SelectedNode->Index;
		}
		else {
			SubNode = 0;
			ParentNode = 0;
		}

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
		if (ScriptFunList::VarList->Count > 0) {
			TreeNode^ treeNode = TrViewVariable->Nodes[ParentNode]->Nodes[SubNode];
			TrViewVariable->SelectedNode = treeNode;

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
		if (TrViewScript->SelectedNode == nullptr)
			return;
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
		RTB_Script->Clear();
		VarListClear();
		TrViewVariable->Nodes->Clear();
		ScriptFileName = "";

	}


	private: System::Void saveScriptFileToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

		if (ScriptFileName != "") {
			SaveScriptFile(Application::StartupPath + "\\Script\\" + ScriptFileName);
		}
		else
		{
			saveAsToolStripMenuItem_Click(sender, e);
		}
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
	private: System::Void MainForm_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		if (e->KeyCode == Keys::F12)
			RTB_Script->Focus();
		if (e->KeyCode == Keys::F11)
			RTB_Script->Focus();
	}
	private: System::Void MainForm_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		if (e->Modifiers == Keys::Control) {
			/// send save Script
			if (e->KeyCode == Keys::S) {
				if (ScriptFileName != "") {
					SaveScriptFile(Application::StartupPath + "\\Script\\" + ScriptFileName);
				}
				else
				{
					saveAsToolStripMenuItem_Click(sender, e);
				}
			}
			/// send Get Function list
			/*if (e->KeyCode == Keys::J) {
			tb->AutoCompleteMode = AutoCompleteMode::SuggestAppend;
			tb->AutoCompleteCustomSource = Ads_Variables_AutoCompleteLoad();
			tb->AutoCompleteSource = AutoCompleteSource::CustomSource;
			tb->Location = DGV1->GetCellDisplayRectangle(1, DGV1->CurrentRow->Index, false).Location;
			tb->Location = Point(DGV1->Left + tb->Left, DGV1->Top + tb->Top + DGV1->CurrentRow->Height);
			tb->Visible = true;
			tb->Width = DGV1->Columns[1]->Width / 2;
			tb->Focus();
			}*/
		}
	}

	private: System::Void LB_Function_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		TB_CommandHelp->Text = HelpLoad_List[LB_Function->SelectedIndex]->Getinfo_();
	}
	private: System::Void Bu_VarListRefresh_Click(System::Object^  sender, System::EventArgs^  e) {
		FileVariableTreeView();
	}
	private: System::Void removeVariableToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		if (TrViewVariable->SelectedNode != nullptr) {
			if (TrViewVariable->SelectedNode->Level == 0) {
				ScriptFunList::VarList->RemoveAt(TrViewVariable->SelectedNode->Index);
				TrViewVariable->SelectedNode->Remove();
			}
			else
			{
				ScriptFunList::VarList->RemoveAt(TrViewVariable->SelectedNode->Parent->Index);
				TrViewVariable->SelectedNode->Parent->Remove();
			}
		}
	}
	private: System::Void followToCPUToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		if (TrViewVariable->SelectedNode != nullptr) {
			if (TrViewVariable->SelectedNode->Level != 0) {
				String^ intValue;
				if (CheckHexIsValid(TrViewVariable->SelectedNode->Text, intValue) > 0)
					DbgCmdExecDirect(Str2ConstChar("dis " + TrViewVariable->SelectedNode->Text));
			}
		}
	}
	private: System::Void followToDumpToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		if (TrViewVariable->SelectedNode != nullptr) {
			if (TrViewVariable->SelectedNode->Level != 0) {
				String^ intValue;
				if (CheckHexIsValid(TrViewVariable->SelectedNode->Text, intValue) > 0)
					DbgCmdExecDirect(Str2ConstChar("dump " + TrViewVariable->SelectedNode->Text));
			}
		}
	}
	private: System::Void copyToClipboardToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		if (TrViewVariable->SelectedNode != nullptr) {
			if (TrViewVariable->SelectedNode->Level == 0) {
				VarPara^ x = ScriptFunList::VarList[TrViewVariable->SelectedNode->Index];
				if (x->vartype == "array") {
					String^ temp = String::Empty;
					for (int i = 0; i < x->arrayLength; i++)
					{
						temp = temp + x->varvalue[i] + Environment::NewLine;
					}
					SetClipBoard(temp);
				}
				else
				{
					SetClipBoard(x->varvalue[0]);
				}
			}
			else
			{
				SetClipBoard(TrViewVariable->SelectedNode->Text);

			}
		}

	}
	private: System::Void RTB_Script_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		IniLoadData();
	}

			 ////////////////////////////////////////////////////////////////
	private: System::Void Fill_Functions_AutoCompleteLoad()
	{
		//AutoCompleteStringCollection^ str = gcnew AutoCompleteStringCollection();
		autocomplete_List->ClearItem();
		array<String^>^ list;
		if (IO::File::Exists(Application::StartupPath + "\\plugins\\AdvSconfig.txt")) {
			list = IO::File::ReadAllLines(Application::StartupPath + "\\plugins\\AdvSconfig.txt");
		}
		else
		{
			return;
		}
		String^ cmd; String^ describ; Color^ color_;
		String^ temp;
		for (int i = 0; i < list->Length; i++)
		{
			temp = list[i];
			if ((temp->Contains(";")) && (temp->EndsWith(";"))) {
				cmd = temp->Substring(0, temp->IndexOf(";"));
				temp = temp->Substring(temp->IndexOf(";") + 1, temp->Length - (temp->IndexOf(";") + 1));
				if (temp->EndsWith(";")) {
					describ = temp->Substring(0, temp->IndexOf(";"));
					if (temp->EndsWith(";")) {
						color_ = Color::FromName(temp->Substring(0, temp->IndexOf(";")));
					}
					else
					{
						color_ = Color::Black;
					}
				}
				else
					describ = " ";
				autocomplete_List->AddItem(gcnew MulticolumnAutocompleteItem(gcnew array<String^> { "This is", "", "used for something"}, "This is", true, true));
			}
		}

		////MulticolumnAutocompleteItem^ s = gcnew MulticolumnAutocompleteItem(gcnew array<String^> { "test", "name" }, "This is ",true,true);
		//autocomplete_List->ClearItem();
		//autocomplete_List->AddItem(gcnew MulticolumnAutocompleteItem(gcnew array<String^> { "This is", "" ,"used for something"}, "This is", true, true));
		//autocomplete_List->AddItem("Varx");		
		//autocomplete_List->AddItem("Getx");
		//autocomplete_List->AddItem("Setx");
		//autocomplete_List->AddItem("Movx");
		//autocomplete_List->AddItem("addx");
		//autocomplete_List->AddItem("subx");
		//autocomplete_List->AddItem("mulx");
		//autocomplete_List->AddItem("divx");

		//autocomplete_List->AddItem("andx");
		//autocomplete_List->AddItem("orx");
		//autocomplete_List->AddItem("xorx");
		//autocomplete_List->AddItem("shlx");
		//autocomplete_List->AddItem("pushx");
		//autocomplete_List->AddItem("popx");
		//autocomplete_List->AddItem("cmpx");
		//autocomplete_List->AddItem("findx");
		//autocomplete_List->AddItem("findallx");
		//autocomplete_List->AddItem("findallmemx");
		//autocomplete_List->AddItem("VarxClear");
		//autocomplete_List->AddItem("memdump");

		//autocomplete_List->AddItem("writelist");
		//autocomplete_List->AddItem("Readlist");
		//autocomplete_List->AddItem("BPxx");
		//autocomplete_List->AddItem("bpcx");
		//autocomplete_List->AddItem("bpex");
		//autocomplete_List->AddItem("bpdx");
		//autocomplete_List->AddItem("bphx");
		//autocomplete_List->AddItem("bphcx");
		//autocomplete_List->AddItem("bphex");
		//autocomplete_List->AddItem("bphdx");
		//autocomplete_List->AddItem("bpmx");
		//autocomplete_List->AddItem("asmx");

		//autocomplete_List->AddItem("GetAPIName");
		//autocomplete_List->AddItem("ResizeArray");
		//autocomplete_List->AddItem("GetArraySize");
		//autocomplete_List->AddItem("Write2File");
		//autocomplete_List->AddItem("inputbox");
		//autocomplete_List->AddItem("commentsetx");
		//autocomplete_List->AddItem("GetdesCallJmp");

		///// x64dbg function
		//autocomplete_List->AddItem("run");
		//autocomplete_List->AddItem("ego");
		//autocomplete_List->AddItem("pause");
		//autocomplete_List->AddItem("StepInto");
		//autocomplete_List->AddItem("StepOver");
		//autocomplete_List->AddItem("StepOut");


		//autocomplete_List->AddItem = list;
	/*	str->Clear();
		str->Add("Varx");
		str->Add("Getx");
		str->Add("Setx");
		str->Add("Movx");
		str->Add("addx");
		str->Add("subx");
		str->Add("mulx");
		str->Add("divx");

		str->Add("andx");
		str->Add("orx");
		str->Add("xorx");
		str->Add("shlx");
		str->Add("pushx");
		str->Add("popx");
		str->Add("cmpx");
		str->Add("findx");
		str->Add("findallx");
		str->Add("findallmemx");
		str->Add("VarxClear");
		str->Add("memdump");

		str->Add("writeStr");
		str->Add("ReadStr");
		str->Add("BPxx");
		str->Add("bpcx");
		str->Add("bpex");
		str->Add("bpdx");
		str->Add("bphx");
		str->Add("bphcx");
		str->Add("bphex");
		str->Add("bphdx");
		str->Add("bpmx");
		str->Add("asmx");

		str->Add("GetAPIName");
		str->Add("ResizeArray");
		str->Add("GetArraySize");
		str->Add("Write2File");
		str->Add("inputbox");
		str->Add("commentsetx");
		str->Add("GetdesCallJmp");

		/// x64dbg function
		str->Add("run");
		str->Add("ego");
		str->Add("pause");
		str->Add("StepInto");
		str->Add("StepOver");
		str->Add("StepOut");*/

	}

			 //private: AutoCompleteStringCollection^ Ads_Variables_AutoCompleteLoad()
			 //{
			 //	AutoCompleteStringCollection^ str = gcnew AutoCompleteStringCollection();
			 //	//str->Clear();
			 //	str->Add("ads.exebase ");
			 //	str->Add("ads.modulebase( ");
			 //	str->Add("ads.SectionSize( ");
			 //	str->Add("ads.exefolderpath ");
			 //	str->Add("ads.exename ");
			 //	str->Add("ads.SectionBegin( ");
			 //	str->Add("ads.SectionEnd( ");	
			 //	str->Add("ads.GetAPIName( ");
			 //	str->Add("ads.GetArraySize( ");
			 //	str->Add("ads.ReadStr( ");
			 //	str->Add("ads.GetdesCallJmp( ");
			 //	str->Add("ads.isInArray( ");
			 //	str->Add("ads.isAddrBelongSection( ");
			 //	for (int i = 0; i < Variables_List->Count; i++)
			 //	{
			 //		str->Add(Variables_List[i]->GetCmd());
			 //	}
			 //	return str;
			 //}	

	private: System::Void RTB_Script_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		if (e->KeyCode == Keys::F12) {
			//Functions_AutoCompleteLoad();
			if (ScriptargumentClass::Scriptargument_->GetLineNumber() == 0) {
				IniLoadData();  /// get all lable in the Script
				ScriptargumentClass::Scriptargument_->setMaxLine(DGV1->RowCount - 1);  // update max line 
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
					if (Need_wait) {
						PB_wait->Visible = true;
						PB_wait->Top = this->Height / 2;
						PB_wait->Left = this->Width / 2;
					}
					readLine(DGV1->Rows[ScriptargumentClass::Scriptargument_->GetLineNumber()]->Cells[1]->Value->ToString(), DGV1->Rows->Count);
				}
				else {
					PB_wait->Visible = true;
					PB_wait->Top = this->Height / 2;
					PB_wait->Left = this->Width / 2;
					readLine("", DGV1->Rows->Count);
				}

			}
			else
			{
				DGV1->ClearSelection();
				DGV1->Rows[0]->Selected = true;
				ScriptargumentClass::Scriptargument_->setLineNumber(0);
				PB_wait->Visible = false;
			}
			if (reten_) { reten_ = false; }
			if (CB_AutoUpdate->Checked)
				FileVariableTreeView();
			PB_wait->Visible = false;
			DGV1->FirstDisplayedScrollingRowIndex = DGV1->SelectedRows[0]->Index;
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
						if (Need_wait) {
							PB_wait->Visible = true;
						}
						if (!readLine(DGV1->Rows[ScriptargumentClass::Scriptargument_->GetLineNumber()]->Cells[1]->Value->ToString(), DGV1->Rows->Count)) {
							Run = false;
						}
						else
						{
							//Script::Debug::Wait();  // problem in compile under x32 platform
							waitPauseProcess();
						}
					}
					else
						if (!readLine("", DGV1->Rows->Count)) {
							Run = false;
						}
						else
						{
							//Script::Debug::Wait();
							waitPauseProcess();

						}
				}
				else
				{
					DGV1->ClearSelection();
					DGV1->Rows[0]->Selected = true;
					ScriptargumentClass::Scriptargument_->setLineNumber(0);
					Run = false;
				}
				PB_wait->Visible = false;
				if (CB_AutoUpdate->Checked)
					FileVariableTreeView();
				if (reten_) {   /// it mean it hit ret command
					DGV1->Rows[0]->Selected = true;
					ScriptargumentClass::Scriptargument_->setLineNumber(0);
					reten_ = false;
					Run = false;
				}
				PB_wait->Visible = false;
				DGV1->FirstDisplayedScrollingRowIndex = DGV1->SelectedRows[0]->Index;

				Application::DoEvents();
			}

		}
	}

	};
}
