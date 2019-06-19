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
	public:
	private:
		int currentPostion = 0;
	public:
	private: System::Windows::Forms::ToolStripMenuItem^  saveAsToolStripMenuItem;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPage_CommandHelp;
	private: System::Windows::Forms::TabPage^  tabPage_Log;
	private: System::Windows::Forms::TextBox^  TB_CommandHelp;
	private: System::Windows::Forms::ToolStripMenuItem^  refrshToolStripMenuItem;
	private: System::Windows::Forms::Button^  Bu_OpenScript;
	private: System::Windows::Forms::TextBox^  TB_ScriptFileName;

	private: System::Windows::Forms::Label^  Label_ScriptLineIndex;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;



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
	public:
		int HelpLoad_List_indexbyCmd(String^ inputCmd) {
			int Counter = 0;
			for each (HelpLoad^ var in HelpLoad_List)
			{
				if (var->Getcmd_()->ToLower() == inputCmd->ToLower()) {
					return Counter;
				}
				Counter += 1;
			}
			return -1;
		}
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
		Variables(int index_, String^ Cmd_, String^ comments_) {
			index = index_;
			Cmd = Cmd_;
			comments = comments_;
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
	public: String^ Getcomments() {
		return comments;
	}
	public: void updateCmd(String^ cmd_) {
		Cmd = cmd_;
	}
	private:
		int index;
		String^ Cmd;
		String^ comments;
	};


	public:
		Generic::List<Variables^>^ Variables_List = gcnew Generic::List<Variables^>;

		/////////////////
	public: ref class AutoCompleteMainList
	{
	public:
		AutoCompleteMainList(String^ cmd_, String^ describ, Color color_) {
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
	public:
		String^ GetCmd() {
			return Cmd;
		}
	public:
		String^ GetdescriB() {
			return descriB;
		}
	public:
		Color GetcoloR() {
			return coloR;
		}
	private:
		String^ Cmd;
		String^ descriB;
		Color coloR;
	};
			/// we will save this for later use as base of the AutoComplete List
			//it will be loaded at main form loaded 
			Generic::List<AutoCompleteMainList^>^ autoCompleteMainList = gcnew Generic::List<AutoCompleteMainList^>;
			///////////////
			/// this list will get all of autoCompleteMainList and variable and Labels  
			Generic::List<AutoCompleteMainList^>^ autoCompleteFlexibleList = gcnew Generic::List<AutoCompleteMainList^>;

			///////////////

	public:
		/// <summary>
		/// get index of the line in the Richtextbox
		/// </summary>
		int GetRTB_lineNum() {
			int cursorPosition = RTB_Script->SelectionStart;
			int lineIndex = RTB_Script->GetLineFromCharIndex(cursorPosition);
			return lineIndex;
		}
	public:
		/// <summary>
		/// get index of the line in the Richtextbox by cursor Position
		/// </summary>
		int GetRTB_lineNumByPostion(int cursorPosition) {
			//int cursorPosition = RTB_Script->SelectionStart;
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->CMT1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->newScriptToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveScriptFileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveAsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->startHereToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->refrshToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
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
			this->TB_ScriptFileName = (gcnew System::Windows::Forms::TextBox());
			this->Bu_OpenScript = (gcnew System::Windows::Forms::Button());
			this->Label_ScriptLineIndex = (gcnew System::Windows::Forms::Label());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->CMT1->SuspendLayout();
			this->CMT_TreeView->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->CMT_VariableList->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB_wait))->BeginInit();
			this->tabControl1->SuspendLayout();
			this->tabPage_CommandHelp->SuspendLayout();
			this->SuspendLayout();
			// 
			// CMT1
			// 
			this->CMT1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->fileToolStripMenuItem,
					this->startHereToolStripMenuItem, this->refrshToolStripMenuItem
			});
			this->CMT1->Name = L"CMT1";
			this->CMT1->Size = System::Drawing::Size(153, 70);
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
			// refrshToolStripMenuItem
			// 
			this->refrshToolStripMenuItem->Name = L"refrshToolStripMenuItem";
			this->refrshToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->refrshToolStripMenuItem->Text = L"Refrsh";
			this->refrshToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::refrshToolStripMenuItem_Click);
			// 
			// TrViewScript
			// 
			this->TrViewScript->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->TrViewScript->ContextMenuStrip = this->CMT_TreeView;
			this->TrViewScript->Location = System::Drawing::Point(11, 19);
			this->TrViewScript->Name = L"TrViewScript";
			this->TrViewScript->Size = System::Drawing::Size(244, 185);
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
			this->CB_AutoUpdate->Location = System::Drawing::Point(171, 212);
			this->CB_AutoUpdate->Name = L"CB_AutoUpdate";
			this->CB_AutoUpdate->Size = System::Drawing::Size(83, 17);
			this->CB_AutoUpdate->TabIndex = 2;
			this->CB_AutoUpdate->Text = L"AutoUpdate";
			this->CB_AutoUpdate->UseVisualStyleBackColor = true;
			// 
			// Bu_VarListRefresh
			// 
			this->Bu_VarListRefresh->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->Bu_VarListRefresh->Location = System::Drawing::Point(11, 572);
			this->Bu_VarListRefresh->Name = L"Bu_VarListRefresh";
			this->Bu_VarListRefresh->Size = System::Drawing::Size(81, 26);
			this->Bu_VarListRefresh->TabIndex = 1;
			this->Bu_VarListRefresh->Text = L"Refresh list";
			this->Bu_VarListRefresh->UseVisualStyleBackColor = true;
			this->Bu_VarListRefresh->Click += gcnew System::EventHandler(this, &MainForm::Bu_VarListRefresh_Click);
			// 
			// Bu_ClearVariable
			// 
			this->Bu_ClearVariable->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->Bu_ClearVariable->Location = System::Drawing::Point(174, 572);
			this->Bu_ClearVariable->Name = L"Bu_ClearVariable";
			this->Bu_ClearVariable->Size = System::Drawing::Size(81, 26);
			this->Bu_ClearVariable->TabIndex = 3;
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
			this->TrViewVariable->Location = System::Drawing::Point(11, 211);
			this->TrViewVariable->Name = L"TrViewVariable";
			this->TrViewVariable->Size = System::Drawing::Size(244, 355);
			this->TrViewVariable->TabIndex = 4;
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
			this->PB_wait->Location = System::Drawing::Point(555, 173);
			this->PB_wait->Name = L"PB_wait";
			this->PB_wait->Size = System::Drawing::Size(193, 197);
			this->PB_wait->TabIndex = 5;
			this->PB_wait->TabStop = false;
			this->PB_wait->Visible = false;
			this->PB_wait->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::PB_wait_MouseDoubleClick);
			this->PB_wait->MouseHover += gcnew System::EventHandler(this, &MainForm::PB_wait_MouseHover);
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
			this->LB_Function->TabIndex = 0;
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
			this->TB_CommandHelp->TabIndex = 1;
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
			this->autocomplete_List->AllowsTabKey = true;
			this->autocomplete_List->AppearInterval = 150;
			this->autocomplete_List->Colors = (cli::safe_cast<AutocompleteMenuNS::Colors^>(resources->GetObject(L"autocomplete_List.Colors")));
			this->autocomplete_List->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
			this->autocomplete_List->ImageList = nullptr;
			this->autocomplete_List->Items = gcnew cli::array< System::String^  >(0);
			this->autocomplete_List->MaximumSize = System::Drawing::Size(800, 350);
			this->autocomplete_List->MinFragmentLength = 1;
			this->autocomplete_List->SearchPattern = L"^[$\\w\\.]";
			this->autocomplete_List->TargetControlWrapper = nullptr;
			this->autocomplete_List->Selected += gcnew System::EventHandler<AutocompleteMenuNS::SelectedEventArgs^ >(this, &MainForm::autocomplete_List_Selected);
			// 
			// RTB_Script
			// 
			this->RTB_Script->AcceptsTab = true;
			this->RTB_Script->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->autocomplete_List->SetAutocompleteMenu(this->RTB_Script, this->autocomplete_List);
			this->RTB_Script->ContextMenuStrip = this->CMT1;
			this->RTB_Script->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->RTB_Script->Location = System::Drawing::Point(277, 34);
			this->RTB_Script->Name = L"RTB_Script";
			this->RTB_Script->Size = System::Drawing::Size(807, 402);
			this->RTB_Script->TabIndex = 0;
			this->RTB_Script->TabStop = false;
			this->RTB_Script->Text = L"";
			this->RTB_Script->WordWrap = false;
			this->RTB_Script->TextChanged += gcnew System::EventHandler(this, &MainForm::RTB_Script_TextChanged);
			this->RTB_Script->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::RTB_Script_KeyDown);
			this->RTB_Script->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::RTB_Script_KeyUp);
			this->RTB_Script->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::RTB_Script_MouseDown);
			// 
			// TB_ScriptFileName
			// 
			this->autocomplete_List->SetAutocompleteMenu(this->TB_ScriptFileName, nullptr);
			this->TB_ScriptFileName->Location = System::Drawing::Point(364, 8);
			this->TB_ScriptFileName->Name = L"TB_ScriptFileName";
			this->TB_ScriptFileName->Size = System::Drawing::Size(468, 20);
			this->TB_ScriptFileName->TabIndex = 7;
			// 
			// Bu_OpenScript
			// 
			this->Bu_OpenScript->Location = System::Drawing::Point(277, 4);
			this->Bu_OpenScript->Name = L"Bu_OpenScript";
			this->Bu_OpenScript->Size = System::Drawing::Size(81, 26);
			this->Bu_OpenScript->TabIndex = 5;
			this->Bu_OpenScript->Text = L"OpenScript";
			this->Bu_OpenScript->UseVisualStyleBackColor = true;
			this->Bu_OpenScript->Click += gcnew System::EventHandler(this, &MainForm::Bu_OpenScript_Click);
			// 
			// Label_ScriptLineIndex
			// 
			this->Label_ScriptLineIndex->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->Label_ScriptLineIndex->AutoSize = true;
			this->Label_ScriptLineIndex->Location = System::Drawing::Point(842, 11);
			this->Label_ScriptLineIndex->Name = L"Label_ScriptLineIndex";
			this->Label_ScriptLineIndex->Size = System::Drawing::Size(241, 13);
			this->Label_ScriptLineIndex->TabIndex = 8;
			this->Label_ScriptLineIndex->Text = L"..............................................................................";
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->Filter = L"text Files|*.txt|All files|*.*";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::SlateGray;
			this->ClientSize = System::Drawing::Size(1091, 616);
			this->Controls->Add(this->TB_ScriptFileName);
			this->Controls->Add(this->Bu_OpenScript);
			this->Controls->Add(this->PB_wait);
			this->Controls->Add(this->RTB_Script);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->Label_ScriptLineIndex);
			this->KeyPreview = true;
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::MainForm_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::MainForm_KeyUp);
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
			this->PerformLayout();

		}
#pragma endregion



	private: System::Void startHereToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		ScriptargumentClass::Scriptargument_->setCurrentlineIndex(GetRTB_lineNum());
		SetNextLineColor_StepOn(ScriptargumentClass::Scriptargument_->GetOldlineIndex(), ScriptargumentClass::Scriptargument_->GetCurrentlineIndex());
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
		Fill_FunctionsAutoComplete_AtLoad();  /// load AutoComplete main List 
		ScriptargumentClass::Scriptargument_->setOldColor(RTB_Script->BackColor);
		//TB_OldValue = RTB_Script->Lines;
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
		/*RTB_Script->Text = "";
		RTB_Script->Text = IO::File::ReadAllText(filepath);
		RTB_Script->Text = RTB_Script->Text->Trim();   /// trim unneeded spaces at the end of the file	*/

		try {
			ScanMode = true;
			RTB_Script->LoadFile(filepath, RichTextBoxStreamType::RichText);
			IniLoadData();
		}
		catch (ArgumentException^ ex) {
			ScanMode = true;
			RTB_Script->LoadFile(filepath, RichTextBoxStreamType::PlainText);
			IniLoadData();
			highlight_AllRTB_Script();
		}
	}

	private: System::Void SaveScriptFile(String^ filepath) {  /// Save Script file from DataGridView to Disk		
		//IO::File::WriteAllText(filepath, RTB_Script->Text);
		RTB_Script->SaveFile(filepath, RichTextBoxStreamType::RichText);
		Microsoft::VisualBasic::Interaction::MsgBox("Done", MsgBoxStyle::DefaultButton1, "Confirm");

	}
	private: System::Void TrViewScript_NodeMouseDoubleClick(System::Object^  sender, System::Windows::Forms::TreeNodeMouseClickEventArgs^  e) {
		if (TrViewScript->SelectedNode == nullptr)
			return;
		if (TrViewScript->SelectedNode->Level != 0) {
			LoadScriptFile(Application::StartupPath + "\\Script\\" + TrViewScript->SelectedNode->Parent->Text + "\\" + TrViewScript->SelectedNode->Text);
			ScriptargumentClass::Scriptargument_->setMaxLine(RTB_Script->Lines->Length);  // update max line just in case update script through run
			ScriptargumentClass::Scriptargument_->SetOldlineIndex(0);
			ScriptargumentClass::Scriptargument_->setCurrentlineIndex(0);
			ScriptFileName = TrViewScript->SelectedNode->Parent->Text + "\\" + TrViewScript->SelectedNode->Text;
			ScriptFileName = Application::StartupPath + "\\Script\\" + ScriptFileName;  /// I add the path to solve save external files
			TB_ScriptFileName->Text = ScriptFileName;
		}
		//highlight_AllRTB_Script();
	}
	private: System::Void Bu_OpenScript_Click(System::Object^  sender, System::EventArgs^  e) {
		openFileDialog1->ShowDialog();
		ScriptFileName = openFileDialog1->FileName;
		LoadScriptFile(ScriptFileName);
		ScriptargumentClass::Scriptargument_->setMaxLine(RTB_Script->Lines->Length);  // update max line just in case update script through run
		ScriptargumentClass::Scriptargument_->SetOldlineIndex(0);
		ScriptargumentClass::Scriptargument_->setCurrentlineIndex(0);
		TB_ScriptFileName->Text = ScriptFileName;
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
				TB_ScriptFileName->Text = "";
			}
			else
			{
				IO::File::Delete(Application::StartupPath + "\\Script\\" + TrViewScript->SelectedNode->Parent->Text + "\\" + TrViewScript->SelectedNode->Text);
				TrViewScript->SelectedNode->Remove();
				RTB_Script->Clear();
				ScriptFileName = "";
				TB_ScriptFileName->Text = "";
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
		TB_ScriptFileName->Text = "";

	}


	private: System::Void saveScriptFileToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		if (ScriptFileName != "") {
			//SaveScriptFile(Application::StartupPath + "\\Script\\" + ScriptFileName);			
			SaveScriptFile(ScriptFileName);
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
			ScriptFileName = Application::StartupPath + "\\Script\\" + Category_ + "\\" + Filename + ".txt";
			SaveScriptFile(ScriptFileName);
			//SaveScriptFile(Application::StartupPath + "\\Script\\" + Category_ + "\\" + Filename + ".txt");
			//ScriptFileName = Category_ + "\\" + Filename + ".txt";			
			TB_ScriptFileName->Text = ScriptFileName;
			if (TrViewScript->SelectedNode->Level == 0)
				TrViewScript->SelectedNode->Nodes->Add(Filename + ".txt");
			else
				TrViewScript->SelectedNode->Parent->Nodes->Add(Filename + ".txt");
		}
		else
		{
			if (Interaction::MsgBox("this File is Exist,Over Write it ??!!", MsgBoxStyle::OkCancel, "Error") == MsgBoxResult::Ok) {
				ScriptFileName = Application::StartupPath + "\\Script\\" + Category_ + "\\" + Filename + ".txt";
				SaveScriptFile(ScriptFileName);
				//SaveScriptFile(Application::StartupPath + "\\Script\\" + Category_ + "\\" + Filename + ".txt");
				//ScriptFileName = Category_ + "\\" + Filename + ".txt";				
				TB_ScriptFileName->Text = ScriptFileName;
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
					//SaveScriptFile(Application::StartupPath + "\\Script\\" + ScriptFileName);
					SaveScriptFile(ScriptFileName);
				}
				else
				{
					saveAsToolStripMenuItem_Click(sender, e);
				}
			}
			if (e->KeyCode == Keys::J) {
				autocomplete_List->AutoPopup = true;
				Fill_VariableAutoComplete();
				autocomplete_List->Show(RTB_Script, true);
			}
		}
		if (e->KeyCode == Keys::F5) {
			IniLoadData();
			highlight_AllRTB_Script();
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

	private: System::Void RTB_Script_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		currentPostion = RTB_Script->SelectionStart;
	}
	private: System::Void refrshToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		IniLoadData();
		for (int i = 0; i < RTB_Script->Lines->Length; i++)
		{
			highlight_Line_ByLineIndex(i);
		}
	}
	private: System::Void IniLoadData() {   /// we use it to get all lable in the script to use it for Goto
											//Done
		LableLineClass::LableLines->Clear();

		Variables_List->Clear();
		for (int i = 0; i < RTB_Script->Lines->Length; i++)
		{
			if (RTB_Script->Lines[i]->Trim() != "") {
				if (RTB_Script->Lines[i]->Trim()->EndsWith(":")) {  // find lables
					String^ LableHold = RTB_Script->Lines[i]->Trim()->Substring(0, RTB_Script->Lines[i]->Trim()->IndexOf(":"));
					LableLine^ LaL = gcnew LableLine(i, LableHold);
					LableLineClass::LableLines->Add(LaL);
				}
				if ((RTB_Script->Lines[i]->Trim()->ToLower()->Trim()->StartsWith("varx")) || (RTB_Script->Lines[i]->Trim()->ToLower()->Trim()->StartsWith("var"))) {  // find variables					
					if (RTB_Script->Lines[i]->Trim()->ToLower()->Trim()->Length < 4)
						return;
					if (RTB_Script->Lines[i]->Trim()->ToLower()->Trim()->Substring(3, 1) != " ") {  //StartsWith("var")
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
							if (arguments[1]->Contains("//")) {
								arguments[1] = arguments[1]->Substring(0, arguments[1]->IndexOf("//"))->Trim();  /// trim to remove extra spaces
							}
							//// check for comments 
							String^ Comments = " ";
							if (RTB_Script->Lines[i]->Trim()->Contains("//")) {
								Comments = RTB_Script->Lines[i]->Trim()->Substring(RTB_Script->Lines[i]->Trim()->IndexOf("//") + 2, RTB_Script->Lines[i]->Trim()->Length - (RTB_Script->Lines[i]->Trim()->IndexOf("//") + 2));
							}
							Variables^ LaL = gcnew Variables(i, arguments[1], Comments);  // for variable case Varx varType,VarName,VarValue
							Variables_List->Add(LaL);
							LaL = gcnew Variables(i, "$" + arguments[1], Comments);
							Variables_List->Add(LaL);
						}
					}
					else
					{
						String^ cmd = RTB_Script->Lines[i]->Trim();
						Generic::List<String^>^ arguments;
						GetArg(cmd, arguments);
						if (arguments->Count < 1)
							return;
						if (arguments[0]->Contains("//")) {
							arguments[0] = arguments[0]->Substring(0, arguments[0]->IndexOf("//"))->Trim();  /// trim to remove extra spaces
						}
						//// check for comments 
						String^ Comments = " ";
						if (RTB_Script->Lines[i]->Trim()->Contains("//")) {
							Comments = RTB_Script->Lines[i]->Trim()->Substring(RTB_Script->Lines[i]->Trim()->IndexOf("//") + 2, RTB_Script->Lines[i]->Trim()->Length - (RTB_Script->Lines[i]->Trim()->IndexOf("//") + 2));
						}
						Variables^ LaL = gcnew Variables(i, arguments[0], Comments);  // for variable case Varx varType,VarName,VarValue
						Variables_List->Add(LaL);
					}

				}
			}
		}
		Fill_AllAutoComplete();
	}
#pragma region AutoComplete_Related
	private: System::Void Fill_FunctionsAutoComplete_AtLoad()  /// this will load all variables form AdvSconfig file
	{
		autocomplete_List->ClearItem();
		array<String^>^ list;
		if (IO::File::Exists(Application::StartupPath + "\\plugins\\AdvSconfig.txt")) {
			list = IO::File::ReadAllLines(Application::StartupPath + "\\plugins\\AdvSconfig.txt");
		}
		else
		{
			return;
		}
		String^ cmd; String^ describ; Color color_;
		String^ temp;
		for (int i = 0; i < list->Length; i++)
		{
			temp = list[i];
			if (temp != "") {
				if ((temp->Contains(";")) && (temp->EndsWith(";"))) {
					cmd = temp->Substring(0, temp->IndexOf(";"));
					temp = temp->Substring(temp->IndexOf(";") + 1, temp->Length - (temp->IndexOf(";") + 1));
					if (temp->EndsWith(";")) {
						describ = temp->Substring(0, temp->IndexOf(";"));
						if (temp->EndsWith(";")) {
							temp = temp->Substring(temp->IndexOf(";") + 1, temp->Length - (temp->IndexOf(";") + 1));
							color_ = Color::FromName(temp->Substring(0, temp->IndexOf(";")));
						}
						else
						{
							color_ = Color::Black;
						}
					}
					else
						describ = " ";

					AutoCompleteMainList^ mainList = gcnew AutoCompleteMainList(cmd, describ, color_);
					autoCompleteMainList->Add(mainList);  /// we will save this for later use as base of the AutoComplete List
					autoCompleteFlexibleList->Add(mainList);
					// fill menu with items 
					autocomplete_List->AddItem(gcnew MulticolumnAutocompleteItem(gcnew array<String^> { cmd, describ}, cmd, true, true));
				}
			}
		}
	}

	private: System::Void autocomplete_List_Selected(System::Object^  sender, AutocompleteMenuNS::SelectedEventArgs^  e) {
		AutocompleteItem^ autocompleteItem = e->Item;
		String^ temp = autocompleteItem->Text->Trim();
		if (temp->Contains("(")) {   /// remove () if exist like ads.ReadStr()
			temp = temp->Substring(0, temp->IndexOf("("));
		}
		if (temp->Contains(",")) {   /// remove , if exist like ads.ReadStr()
			temp = temp->Substring(0, temp->IndexOf(","));
		}
		int index_ = HelpLoad_List_indexbyCmd(temp);
		if (index_ != -1)// get the word form the selected autocomplete menu 
			TB_CommandHelp->Text = HelpLoad_List[index_]->Getinfo_();
		highlight_Line_ByLineIndex(GetRTB_lineNum());
		//highlight_FromSelectedAutoComplete(autocompleteItem->Text);
	}
	private: System::Void Fill_MainAutoComplete()
	{
		autocomplete_List->ClearItem();
		for (int i = 0; i < autoCompleteMainList->Count; i++)
		{
			autocomplete_List->AddItem(gcnew MulticolumnAutocompleteItem(gcnew array<String^> { autoCompleteMainList[i]->GetCmd(), autoCompleteMainList[i]->GetdescriB()}, autoCompleteMainList[i]->GetCmd(), true, true));
		}
	}
	private: System::Void Fill_AllAutoComplete()
	{
		autocomplete_List->ClearItem();
		autoCompleteFlexibleList->Clear();
		autoCompleteFlexibleList->AddRange(autoCompleteMainList);
		for (size_t i1 = 0; i1 < Variables_List->Count; i1++)
		{
			AutoCompleteMainList^ tempItem;
			tempItem = gcnew AutoCompleteMainList(Variables_List[i1]->GetCmd(), Variables_List[i1]->Getcomments(), Color::OrangeRed);
			autoCompleteFlexibleList->Add(tempItem);
		}

		for (int i = 0; i < autoCompleteFlexibleList->Count; i++)  //for (int i = 0; i < autoCompleteMainList->Count; i++)
		{
			autocomplete_List->AddItem(gcnew MulticolumnAutocompleteItem(gcnew array<String^> { autoCompleteFlexibleList[i]->GetCmd(), autoCompleteFlexibleList[i]->GetdescriB()}, autoCompleteFlexibleList[i]->GetCmd(), true, true));
		}
	}
	private: System::Void Fill_VariableAutoComplete()
	{
		autocomplete_List->ClearItem();
		Fill_MainAutoComplete();
		for (int i1 = 0; i1 < Variables_List->Count; i1++)
		{
			autocomplete_List->AddItem(gcnew MulticolumnAutocompleteItem(gcnew array<String^> { Variables_List[i1]->GetCmd(), Variables_List[i1]->Getcomments()}, Variables_List[i1]->GetCmd(), true, true));
		}

	}
#pragma endregion

	private: System::Void RTB_Script_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		if (ScanMode) {
			ScanMode = false;
			return;
		}
		int OldLine = RTB_Script->GetLineFromCharIndex(currentPostion);
		int CurrentLine = RTB_Script->GetLineFromCharIndex(RTB_Script->SelectionStart);
		IniLoadData();
		if (OldLine < CurrentLine) {
			for (int i = OldLine; i <= CurrentLine; i++)
			{
				highlight_Line_ByLineIndex(i);
			}
		}
		if (OldLine > CurrentLine) {
			for (int i = CurrentLine; i <= OldLine; i++)
			{
				highlight_Line_ByLineIndex(i);
			}
		}
		if (OldLine == CurrentLine) {
			highlight_Line_ByLineIndex(CurrentLine);
		}
		//highlight_Line();
	}
#pragma region highlight_system
			 /// we will used it when select item from Autocomplete_list
	private:System::Void highlight_FromSelectedAutoComplete(String^ word) {
		//String^ word;
		int startIndex = 0;
		AutoCompleteMainList^ tempItem;
		for (int i = 0; i < autoCompleteFlexibleList->Count; i++)
		{
			if (autoCompleteFlexibleList[i]->GetCmd()->ToLower()->StartsWith(word->Trim()->ToLower())) {
				tempItem = gcnew AutoCompleteMainList(autoCompleteFlexibleList[i]->GetCmd(), autoCompleteFlexibleList[i]->GetdescriB(), autoCompleteFlexibleList[i]->GetcoloR());
				break;
			}
		}
		if (tempItem == nullptr)
			return;
		word = word->Trim()->ToLower();  /// trim spaces and make lower in case we have lower case words
		if (word->Contains("(")) {   /// remove () if exist like ads.ReadStr()
			word = word->Substring(0, word->IndexOf("("));
		}
		if (word->Contains(",")) {   /// remove , if exist like ads.ReadStr()
			word = word->Substring(0, word->IndexOf(","));
		}
		int LineIndex = GetRTB_lineNum();  ///get  line number(index)		
		if ((LineIndex == 0) && (RTB_Script->Lines[LineIndex] == nullptr))  /// check if the line index is first line and line not have string
			return;
		String^ text = RTB_Script->Lines[LineIndex];
		//if (text != nullptr) {
		if (text->ToLower()->Contains(word))  /// search text in lower case
		{
			int index = -1;
			int selectStart = RTB_Script->SelectionStart;
			index = RTB_Script->SelectionStart - tempItem->GetCmd()->Length; //		word->Length;
			if (index < 0)
				return;
			RTB_Script->Select((index + startIndex), word->Length);
			RTB_Script->SelectionColor = tempItem->GetcoloR();
			RTB_Script->Select(selectStart, 0);
			index = word->Length;
			RTB_Script->SelectionColor = Color::Black;
		}
	}

	private:System::Void highlight_Line() {
		int currentPlace = RTB_Script->SelectionStart;
		String^ word; int startIndex = 0;
		int LineIndex = GetRTB_lineNum();  ///get  line number(index)
		int FirstCharIndexFromLine = RTB_Script->GetFirstCharIndexFromLine(LineIndex);  // Get First Char Index From current Line
		int Index_ofLineBegin = FirstCharIndexFromLine;
		//if ((LineIndex == 0) && (RTB_Script->Lines[LineIndex] == nullptr))  /// check if the line index is first line and line not have string
		if (RTB_Script->Lines->Length < 0)  /// check if the line index is not have string
			return;
		try
		{
			if (RTB_Script->Lines[LineIndex]->Trim() == "")  /// check if the line index is just spaces
				return;
		}
		catch (System::IndexOutOfRangeException^ ex)
		{
			return;
		}
		String^ text = RTB_Script->Lines[LineIndex];  /// get string of the line
		if (text != nullptr) {
			for (int i = 0; i < autoCompleteFlexibleList->Count; i++)
			{
				word = autoCompleteFlexibleList[i]->GetCmd()->Trim()->ToLower();  /// trim spaces and make lower in case we have lower case words
				if (word->Contains("(")) {   /// remove () if exist like ads.ReadStr()
					word = word->Substring(0, word->IndexOf("("));
				}
				if (word->Contains(",")) {   /// remove , if exist 
					word = word->Substring(0, word->IndexOf(","));
				}

				if (text->ToLower()->Contains(word))  /// search text in lower case in this line 
				{
					int index = Index_ofLineBegin;
					int Check_index = currentPlace - autoCompleteFlexibleList[i]->GetCmd()->Length;
					if (Check_index < 0)
						return;
					index = 0; /// rest index to begin of line
					//while ((RTB_Script->Text->ToLower()->IndexOf(word, index, word->Length)) != -1)
					//while ((index = RTB_Script->Text->ToLower()->IndexOf(word, (index), StringComparison::Ordinal)) != -1)
					while ((index = text->ToLower()->IndexOf(word, (index), StringComparison::Ordinal)) != -1)
					{
						//RTB_Script->Select((index + startIndex), word->Length);
						bool noneed = false;
						if (index - 1 > 0) {
							if ((Char::IsLetter(text[index - 1])) || (text[index - 1] == (Char)"$")) {
								noneed = true;
							}
						}
						if (index + word->Length + 1 < text->Length) {
							Char^ xx = text[index + word->Length];
							if (Char::IsLetter(text[index + word->Length + 1])) {
								noneed = true;
							}
						}
						if (!noneed) {
							RTB_Script->Select((index + FirstCharIndexFromLine), word->Length);
							RTB_Script->SelectionColor = autoCompleteFlexibleList[i]->GetcoloR();
							RTB_Script->Select(FirstCharIndexFromLine + index + word->Length, text->Length - (index + word->Length));
							RTB_Script->SelectionColor = Color::Black;
						}
						index += word->Length;
					}
				}
			}
			if (RTB_Script->Lines[LineIndex]->Contains("//")) {
				int indexOfComment = RTB_Script->Lines[LineIndex]->IndexOf("//");
				indexOfComment = indexOfComment + FirstCharIndexFromLine;
				RTB_Script->Select(indexOfComment, RTB_Script->Lines[LineIndex]->Length - RTB_Script->Lines[LineIndex]->IndexOf("//"));
				RTB_Script->SelectionColor = Color::LightGreen;
			}
		}
		RTB_Script->Select(currentPlace, 0);
	}

	private: bool ScanMode = false; /// we used it because when we cann RTB_Script->Select it fire RTB_Script_TextChanged which will make it too slow
	private:System::Void highlight_Line_ByLineIndex(int LineIndex) {
		int currentPlace = RTB_Script->SelectionStart;
		String^ word; int startIndex = 0;
		//int LineIndex = GetRTB_lineNum();  ///get  line number(index)
		int FirstCharIndexFromLine = RTB_Script->GetFirstCharIndexFromLine(LineIndex);  // Get First Char Index From current Line
		int Index_ofLineBegin = FirstCharIndexFromLine;
		//if ((LineIndex == 0) && (RTB_Script->Lines[LineIndex] == nullptr))  /// check if the line index is first line and line not have string
		if (RTB_Script->Lines->Length < 0)  /// check if the line index is not have string
			return;
		try
		{
			if (RTB_Script->Lines[LineIndex]->Trim() == "")  /// check if the line index is just spaces
				return;
		}
		catch (System::IndexOutOfRangeException^ ex)
		{
			return;
		}
		String^ text = RTB_Script->Lines[LineIndex];  /// get string of the line
		if (text != nullptr) {
			/// rest line color just in case old set
			ScanMode = true;
			RTB_Script->Select(FirstCharIndexFromLine, text->Length);
			RTB_Script->SelectionColor = Color::Black;

			for (int i = 0; i < autoCompleteFlexibleList->Count; i++)
			{
				word = autoCompleteFlexibleList[i]->GetCmd()->Trim()->ToLower();  /// trim spaces and make lower in case we have lower case words
				if (word->Contains("(")) {   /// remove () if exist like ads.ReadStr()
					word = word->Substring(0, word->IndexOf("("));
				}
				if (word->Contains(",")) {   /// remove , if exist 
					word = word->Substring(0, word->IndexOf(","));
				}

				if (text->ToLower()->Contains(word))  /// search text in lower case in this line 
				{
					int index = Index_ofLineBegin;
					int Check_index = currentPlace - autoCompleteFlexibleList[i]->GetCmd()->Length;
					if (Check_index < 0)
						return;
					index = 0; /// rest index to begin of line
							   //while ((RTB_Script->Text->ToLower()->IndexOf(word, index, word->Length)) != -1)
							   //while ((index = RTB_Script->Text->ToLower()->IndexOf(word, (index), StringComparison::Ordinal)) != -1)
					while ((index = text->ToLower()->IndexOf(word, (index), StringComparison::Ordinal)) != -1)
					{
						//RTB_Script->Select((index + startIndex), word->Length);
						bool noneed = false;
						if (index - 1 >= 0) {
							if ((Char::IsLetter(text[index - 1])) || (text->Substring(index - 1, 1) == "$") || (text->Substring(index - 1, 1) == ".")) {
								noneed = true;
							}
						}
						if (index + word->Length + 1 <= text->Length) {
							//Char^ xx = text[index + word->Length];
							if (Char::IsLetter(text[index + word->Length])) {
								noneed = true;
							}
						}
						if (!noneed) {
							ScanMode = true;
							RTB_Script->Select((FirstCharIndexFromLine + index), word->Length);
							RTB_Script->SelectionColor = autoCompleteFlexibleList[i]->GetcoloR();
							ScanMode = true;
							if (index + word->Length + 1 < text->Length) {
								RTB_Script->Select(FirstCharIndexFromLine + index + 1 + word->Length, 0);
								RTB_Script->SelectionColor = Color::Black;
							}
							//else {
								//RTB_Script->Select(FirstCharIndexFromLine + index + word->Length, text->Length - (index + word->Length));
								//RTB_Script->SelectionColor = Color::Black;
							//}
						}
						/*else
						{
							ScanMode = true;
							RTB_Script->Select(FirstCharIndexFromLine + index, 0);
							RTB_Script->SelectionColor = Color::Black;
						}*/
						index += word->Length;
					}
				}
			}
			if (RTB_Script->Lines[LineIndex]->Contains("//")) {
				int indexOfComment = RTB_Script->Lines[LineIndex]->IndexOf("//");
				indexOfComment = indexOfComment + FirstCharIndexFromLine;
				ScanMode = true;
				RTB_Script->Select(indexOfComment, RTB_Script->Lines[LineIndex]->Length - RTB_Script->Lines[LineIndex]->IndexOf("//"));
				RTB_Script->SelectionColor = Color::LightGreen;
			}
		}
		RTB_Script->Select(currentPlace, 0);
	}

	private:System::Void highlight_AllRTB_Script() {
		for (int i = 0; i < RTB_Script->Lines->Length; i++)
		{
			highlight_Line_ByLineIndex(i);
		}

	}


#pragma endregion

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	private: System::Void RTB_Script_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		currentPostion = RTB_Script->SelectionStart;
		if (e->KeyCode == Keys::Oem2) {
			if (RTB_Script->Lines[GetRTB_lineNum()]->Contains("//")) {
				int OldcursorPosition = RTB_Script->SelectionStart;
				int sss = RTB_Script->Lines[GetRTB_lineNum()]->IndexOf("//");
				int ff = RTB_Script->Lines[GetRTB_lineNum()]->Length;
				RTB_Script->Select(OldcursorPosition - 2, 2);
				RTB_Script->SelectionColor = Color::LightGreen;
				RTB_Script->Select(OldcursorPosition, 0);
			}
		}
		if (e->KeyCode == Keys::Enter) {
			RTB_Script->SelectionColor = Color::Black; // to rest color again
		}
		if ((e->KeyCode == Keys::Oemcomma) || (e->KeyCode == Keys::Space)) {
			int OldcursorPosition = RTB_Script->SelectionStart;
			int Line_index = GetRTB_lineNum();
			if (!RTB_Script->Lines[GetRTB_lineNum()]->Contains("//")) {
				RTB_Script->Select(OldcursorPosition - 1, 1);
				RTB_Script->SelectionColor = Color::Black; // to rest color again
				RTB_Script->Select(OldcursorPosition, 0);
			}
			else {
				if (GetRTB_lineNumByPostion(RTB_Script->Text->IndexOf("//", OldcursorPosition)) == Line_index) {
					if (GetRTB_lineNumByPostion(RTB_Script->Text->IndexOf("//", OldcursorPosition)) > OldcursorPosition) {
						RTB_Script->Select(OldcursorPosition - 1, 1);
						RTB_Script->SelectionColor = Color::Black; // to rest color again
						RTB_Script->Select(OldcursorPosition, 0);
					}
				}
			}


		}

	}

	private: Color PreviousLineColor = SystemColors::Control;
	private: System::Void SetNextLineColor_StepOn(int oldLine, int CurrentLine) {
		if (CurrentLine == ScriptargumentClass::Scriptargument_->GetMaxLine())
		{
			ScanMode = true;  /// RTB_Script->Select will fire RTB_Script->Edit so we disable
			RTB_Script->Select(RTB_Script->GetFirstCharIndexFromLine(oldLine), RTB_Script->Lines[oldLine]->Length);
			RTB_Script->SelectionBackColor = ScriptargumentClass::Scriptargument_->GetOldColor();
			ScanMode = true;  /// RTB_Script->Select will fire RTB_Script->Edit so we disable
			ScriptargumentClass::Scriptargument_->setCurrentlineIndex(0);
			RTB_Script->Select(RTB_Script->GetFirstCharIndexFromLine(0), RTB_Script->Lines[0]->Length);
			RTB_Script->SelectionBackColor = Color::Yellow;
			RTB_Script->Select(RTB_Script->GetFirstCharIndexFromLine(0), 0);
			ScriptargumentClass::Scriptargument_->SetOldlineIndex(0);
			return;
		}
		if ((CurrentLine == 0) && (oldLine == 0)) {
			ScanMode = true;  /// RTB_Script->Select will fire RTB_Script->Edit so we disable
			RTB_Script->Select(RTB_Script->GetFirstCharIndexFromLine(CurrentLine), RTB_Script->Lines[CurrentLine]->Length);
			RTB_Script->SelectionBackColor = Color::Yellow;
			RTB_Script->Select(RTB_Script->GetFirstCharIndexFromLine(CurrentLine), 0);
			ScriptargumentClass::Scriptargument_->SetOldlineIndex(CurrentLine);
			return;
		}
		//if ((oldLine < CurrentLine) && ((CurrentLine != ScriptargumentClass::Scriptargument_->GetMaxLine())))
		if ((oldLine < CurrentLine) || (oldLine > CurrentLine))
		{
			ScanMode = true;  /// RTB_Script->Select will fire RTB_Script->Edit so we disable
			RTB_Script->Select(RTB_Script->GetFirstCharIndexFromLine(oldLine), RTB_Script->Lines[oldLine]->Length);
			RTB_Script->SelectionBackColor = ScriptargumentClass::Scriptargument_->GetOldColor();

			ScanMode = true;  /// RTB_Script->Select will fire RTB_Script->Edit so we disable
			RTB_Script->Select(RTB_Script->GetFirstCharIndexFromLine(CurrentLine), RTB_Script->Lines[CurrentLine]->Length);
			RTB_Script->SelectionBackColor = Color::Yellow;
			RTB_Script->Select(RTB_Script->GetFirstCharIndexFromLine(CurrentLine), 0);
			ScriptargumentClass::Scriptargument_->SetOldlineIndex(CurrentLine);
			return;
		}
	}
	private: System::Void RTB_Script_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		if (e->KeyCode == Keys::F12) {
			autocomplete_List->AutoPopup = false;
			if (ScriptargumentClass::Scriptargument_->GetCurrentlineIndex() == 0) {
				IniLoadData();  /// get all lable in the Script
				ScriptargumentClass::Scriptargument_->setMaxLine(RTB_Script->Lines->Length);  // update max line				
				ScriptargumentClass::Scriptargument_->SetOldlineIndex_Color(0, RTB_Script->BackColor);  /// save old line index and it's color
			}
			if (ScriptargumentClass::Scriptargument_->GetCurrentlineIndex() < RTB_Script->Lines->Length) {
				SetNextLineColor_StepOn(ScriptargumentClass::Scriptargument_->GetOldlineIndex(), ScriptargumentClass::Scriptargument_->GetCurrentlineIndex());
				if (RTB_Script->Lines[ScriptargumentClass::Scriptargument_->GetCurrentlineIndex()]->Trim() != "") {
					readLine(RTB_Script->Lines[ScriptargumentClass::Scriptargument_->GetCurrentlineIndex()], ScriptargumentClass::Scriptargument_->GetMaxLine());
					PB_wait->Visible = true;
					PB_wait->Top = this->Height / 2;
					PB_wait->Left = this->Width / 2;
					waitPauseProcess();
					PB_wait->Visible = false;
				}
				else {
					readLine("", ScriptargumentClass::Scriptargument_->GetMaxLine());
				}

			}
			else
			{
				SetNextLineColor_StepOn(ScriptargumentClass::Scriptargument_->GetOldlineIndex(), ScriptargumentClass::Scriptargument_->GetCurrentlineIndex());
				PB_wait->Visible = false;
			}
			if (reten_) { reten_ = false; }
			if (CB_AutoUpdate->Checked)
				FileVariableTreeView();
			PB_wait->Visible = false;
		}
		///////////////////////
		if (e->KeyCode == Keys::F11) {
			autocomplete_List->AutoPopup = false;
			if (Run)
				Run = false;
			else
				Run = true;

			while (Run)
			{
				//Application::DoEvents();
				if (ScriptargumentClass::Scriptargument_->GetCurrentlineIndex() == 0) {
					IniLoadData();  /// get all lable in the Script
					ScriptargumentClass::Scriptargument_->setMaxLine(RTB_Script->Lines->Length);  // update max line				
					ScriptargumentClass::Scriptargument_->SetOldlineIndex_Color(0, RTB_Script->BackColor);  /// save old line index and it's color
				}
				if (ScriptargumentClass::Scriptargument_->GetCurrentlineIndex() < RTB_Script->Lines->Length) {
					SetNextLineColor_StepOn(ScriptargumentClass::Scriptargument_->GetOldlineIndex(), ScriptargumentClass::Scriptargument_->GetCurrentlineIndex());
					if (RTB_Script->Lines[ScriptargumentClass::Scriptargument_->GetCurrentlineIndex()] != "") {
						/*if (Need_wait(RTB_Script->Lines[ScriptargumentClass::Scriptargument_->GetCurrentlineIndex()])) {
							PB_wait->Visible = true;
							PB_wait->Top = this->Height / 2;
							PB_wait->Left = this->Width / 2;
							waitPauseProcess();
						}*/
						if (!readLine(RTB_Script->Lines[ScriptargumentClass::Scriptargument_->GetCurrentlineIndex()], ScriptargumentClass::Scriptargument_->GetMaxLine())) {
							Run = false;
						}
						else
						{
							//Script::Debug::Wait();  // problem in compile under x32 platform
							PB_wait->Visible = true;
							PB_wait->Top = this->Height / 2;
							PB_wait->Left = this->Width / 2;
							waitPauseProcess();
							PB_wait->Visible = false;
						}
					}
					else {
						if (!readLine("", ScriptargumentClass::Scriptargument_->GetMaxLine())) {
							Run = false;
						}
						else
						{
							PB_wait->Visible = true;
							PB_wait->Top = this->Height / 2;
							PB_wait->Left = this->Width / 2;
							waitPauseProcess();
							PB_wait->Visible = false;

						}
					}
				}
				else {
					SetNextLineColor_StepOn(ScriptargumentClass::Scriptargument_->GetOldlineIndex(), ScriptargumentClass::Scriptargument_->GetCurrentlineIndex());
					PB_wait->Visible = false;
					Run = false;
				}
				PB_wait->Visible = false;
				if (CB_AutoUpdate->Checked)
					FileVariableTreeView();
				if (reten_) {   /// it mean it hit ret command					
					SetNextLineColor_StepOn(ScriptargumentClass::Scriptargument_->GetOldlineIndex(), ScriptargumentClass::Scriptargument_->GetCurrentlineIndex());
					PB_wait->Visible = false;
					reten_ = false;
					Run = false;
				}
				PB_wait->Visible = false;
				Application::DoEvents();
			}
		}
	}

			 //private: System::Void DGV1_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 //	if (e->KeyCode == Keys::F12) {
			 //		DGV1->ClearSelection();
			 //		if (ScriptargumentClass::Scriptargument_->GetLineNumber() == 0) {
			 //			IniLoadData();  /// get all lable in the Script
			 //			ScriptargumentClass::Scriptargument_->setMaxLine(DGV1->RowCount - 1);  // update max line 
			 //		}
			 //		if (ScriptargumentClass::Scriptargument_->GetLineNumber() < DGV1->RowCount - 1) {
			 //			DGV1->ClearSelection();
			 //			DGV1->Rows[ScriptargumentClass::Scriptargument_->GetLineNumber()]->Selected = true;
			 //			if (DGV1->Rows[ScriptargumentClass::Scriptargument_->GetLineNumber()]->Cells[1]->Value != nullptr) {
			 //				if (Need_wait) {
			 //					PB_wait->Visible = true;
			 //					PB_wait->Top = this->Height / 2;
			 //					PB_wait->Left = this->Width / 2;
			 //				}
			 //				readLine(DGV1->Rows[ScriptargumentClass::Scriptargument_->GetLineNumber()]->Cells[1]->Value->ToString(), DGV1->Rows->Count);
			 //			}
			 //			else {
			 //				PB_wait->Visible = true;
			 //				PB_wait->Top = this->Height / 2;
			 //				PB_wait->Left = this->Width / 2;
			 //				readLine("", DGV1->Rows->Count);
			 //			}
			 //		}
			 //		else
			 //		{
			 //			DGV1->ClearSelection();
			 //			DGV1->Rows[0]->Selected = true;
			 //			ScriptargumentClass::Scriptargument_->setLineNumber(0);
			 //			PB_wait->Visible = false;
			 //		}
			 //		if (reten_) { reten_ = false; }
			 //		if (CB_AutoUpdate->Checked)
			 //			FileVariableTreeView();
			 //		PB_wait->Visible = false;
			 //		DGV1->FirstDisplayedScrollingRowIndex = DGV1->SelectedRows[0]->Index;
			 //	}

			 //	if (e->KeyCode == Keys::F11) {
			 //		if (Run)
			 //			Run = false;
			 //		else
			 //			Run = true;
			 //		while (Run)
			 //		{
			 //			Application::DoEvents();
			 //			DGV1->ClearSelection();
			 //			if (ScriptargumentClass::Scriptargument_->GetLineNumber() == 0) {
			 //				IniLoadData();  /// get all lable in the Script
			 //				ScriptargumentClass::Scriptargument_->setMaxLine(DGV1->RowCount - 1);  // update max line 
			 //			}
			 //			if (ScriptargumentClass::Scriptargument_->GetLineNumber() < DGV1->RowCount - 1) {
			 //				DGV1->ClearSelection();
			 //				DGV1->Rows[ScriptargumentClass::Scriptargument_->GetLineNumber()]->Selected = true;
			 //				if (DGV1->Rows[ScriptargumentClass::Scriptargument_->GetLineNumber()]->Cells[1]->Value != nullptr) {
			 //					if (Need_wait) {
			 //						PB_wait->Visible = true;
			 //					}
			 //					if (!readLine(DGV1->Rows[ScriptargumentClass::Scriptargument_->GetLineNumber()]->Cells[1]->Value->ToString(), DGV1->Rows->Count)) {
			 //						Run = false;
			 //					}
			 //					else
			 //					{
			 //						//Script::Debug::Wait();  // problem in compile under x32 platform
			 //						waitPauseProcess();
			 //					}
			 //				}
			 //				else
			 //					if (!readLine("", DGV1->Rows->Count)) {
			 //						Run = false;
			 //					}
			 //					else
			 //					{
			 //						//Script::Debug::Wait();
			 //						waitPauseProcess();
			 //					}
			 //			}
			 //			else
			 //			{
			 //				DGV1->ClearSelection();
			 //				DGV1->Rows[0]->Selected = true;
			 //				ScriptargumentClass::Scriptargument_->setLineNumber(0);
			 //				Run = false;
			 //			}
			 //			PB_wait->Visible = false;
			 //			if (CB_AutoUpdate->Checked)
			 //				FileVariableTreeView();
			 //			if (reten_) {   /// it mean it hit ret command
			 //				DGV1->Rows[0]->Selected = true;
			 //				ScriptargumentClass::Scriptargument_->setLineNumber(0);
			 //				reten_ = false;
			 //				Run = false;
			 //			}
			 //			PB_wait->Visible = false;
			 //			DGV1->FirstDisplayedScrollingRowIndex = DGV1->SelectedRows[0]->Index;
			 //			Application::DoEvents();
			 //		}
			 //	}
			 //}

	private: System::Void PB_wait_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		IspausedClass::IspausedClass_->ispaused = true;
		Run = false;
	}
	private: System::Void PB_wait_MouseHover(System::Object^  sender, System::EventArgs^  e) {
		ToolTip^ SetToolTip_= gcnew ToolTip;
		SetToolTip_->SetToolTip(PB_wait, "Double Click to stop the Script");		
	}
};
}
