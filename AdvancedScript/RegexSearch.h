#pragma once
#include "HelperFunctions.h"
namespace AdvancedScript {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Text::RegularExpressions;
	/// <summary>
	/// Summary for RegexSearch
	/// </summary>
	public ref class RegexSearch : public System::Windows::Forms::Form
	{
	public:
		RegexSearch(void)
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
		~RegexSearch()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataGridView^  DGV_Results;
	protected:

	protected:
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  AddrColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  DisAssmColumn;
	private: System::Windows::Forms::TextBox^  TB_Addr;

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  TB_Regex;
	private: System::Windows::Forms::Button^  Bu_Search;
	private: System::Windows::Forms::ContextMenuStrip^  CMS1;
	private: System::Windows::Forms::ToolStripMenuItem^  cPUToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  dumpToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exportToToolStripMenuItem;
	private: System::ComponentModel::IContainer^  components;

	private :
		ref class search__
		{
		public:
			search__(String^ addr_1, String^ disass1) {
				addr_ = addr_1;
				disass = disass1;
			}
		public:
			String^ GetAddr() {
				return addr_;
			}
		public:
			String^ GetDisass() {
				return disass;
			}
		private:
			String^ addr_;
			String^ disass;
		};

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
			this->DGV_Results = (gcnew System::Windows::Forms::DataGridView());
			this->AddrColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->DisAssmColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->CMS1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->cPUToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->dumpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exportToToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->TB_Addr = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->TB_Regex = (gcnew System::Windows::Forms::TextBox());
			this->Bu_Search = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DGV_Results))->BeginInit();
			this->CMS1->SuspendLayout();
			this->SuspendLayout();
			// 
			// DGV_Results
			// 
			this->DGV_Results->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->DGV_Results->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->DGV_Results->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->DGV_Results->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
				this->AddrColumn,
					this->DisAssmColumn
			});
			this->DGV_Results->ContextMenuStrip = this->CMS1;
			this->DGV_Results->Location = System::Drawing::Point(3, 33);
			this->DGV_Results->Name = L"DGV_Results";
			this->DGV_Results->Size = System::Drawing::Size(823, 295);
			this->DGV_Results->TabIndex = 0;
			// 
			// AddrColumn
			// 
			this->AddrColumn->FillWeight = 30;
			this->AddrColumn->HeaderText = L"Address";
			this->AddrColumn->Name = L"AddrColumn";
			this->AddrColumn->ReadOnly = true;
			// 
			// DisAssmColumn
			// 
			this->DisAssmColumn->HeaderText = L"Command";
			this->DisAssmColumn->Name = L"DisAssmColumn";
			this->DisAssmColumn->ReadOnly = true;
			// 
			// CMS1
			// 
			this->CMS1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->cPUToolStripMenuItem, this->dumpToolStripMenuItem,
					this->exportToToolStripMenuItem
			});
			this->CMS1->Name = L"CMS1";
			this->CMS1->Size = System::Drawing::Size(125, 70);
			// 
			// cPUToolStripMenuItem
			// 
			this->cPUToolStripMenuItem->Name = L"cPUToolStripMenuItem";
			this->cPUToolStripMenuItem->Size = System::Drawing::Size(124, 22);
			this->cPUToolStripMenuItem->Text = L"CPU";
			this->cPUToolStripMenuItem->Click += gcnew System::EventHandler(this, &RegexSearch::cPUToolStripMenuItem_Click);
			// 
			// dumpToolStripMenuItem
			// 
			this->dumpToolStripMenuItem->Name = L"dumpToolStripMenuItem";
			this->dumpToolStripMenuItem->Size = System::Drawing::Size(124, 22);
			this->dumpToolStripMenuItem->Text = L"Dump";
			this->dumpToolStripMenuItem->Click += gcnew System::EventHandler(this, &RegexSearch::dumpToolStripMenuItem_Click);
			// 
			// exportToToolStripMenuItem
			// 
			this->exportToToolStripMenuItem->Name = L"exportToToolStripMenuItem";
			this->exportToToolStripMenuItem->Size = System::Drawing::Size(124, 22);
			this->exportToToolStripMenuItem->Text = L"Export To";
			this->exportToToolStripMenuItem->Click += gcnew System::EventHandler(this, &RegexSearch::exportToToolStripMenuItem_Click);
			// 
			// TB_Addr
			// 
			this->TB_Addr->Location = System::Drawing::Point(120, 6);
			this->TB_Addr->Name = L"TB_Addr";
			this->TB_Addr->Size = System::Drawing::Size(136, 20);
			this->TB_Addr->TabIndex = 1;
			this->TB_Addr->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &RegexSearch::TB_Addr_MouseDoubleClick);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(6, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(108, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Address(DoubleClick)";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(279, 9);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(97, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Regex Expressions";
			// 
			// TB_Regex
			// 
			this->TB_Regex->Location = System::Drawing::Point(382, 6);
			this->TB_Regex->Name = L"TB_Regex";
			this->TB_Regex->Size = System::Drawing::Size(208, 20);
			this->TB_Regex->TabIndex = 3;
			// 
			// Bu_Search
			// 
			this->Bu_Search->Location = System::Drawing::Point(596, 4);
			this->Bu_Search->Name = L"Bu_Search";
			this->Bu_Search->Size = System::Drawing::Size(89, 23);
			this->Bu_Search->TabIndex = 5;
			this->Bu_Search->Text = L"Search";
			this->Bu_Search->UseVisualStyleBackColor = true;
			this->Bu_Search->Click += gcnew System::EventHandler(this, &RegexSearch::Bu_Search_Click);
			// 
			// RegexSearch
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(830, 331);
			this->Controls->Add(this->Bu_Search);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->TB_Regex);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->TB_Addr);
			this->Controls->Add(this->DGV_Results);
			this->Name = L"RegexSearch";
			this->Text = L"RegexSearch";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DGV_Results))->EndInit();
			this->CMS1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Bu_Search_Click(System::Object^  sender, System::EventArgs^  e) {
		String^ intvalue;  /// first if it is hex value
		String^ addrx = TB_Addr->Text;
		Bu_Search->Enabled = false;
		if (CheckHexIsValid(addrx, intvalue) > 0) {  /// it mean it is address ( hex value)

			duint base = Script::Memory::GetBase(Str2duint(intvalue));
			duint size_ = Script::Memory::GetSize(Str2duint(intvalue));
			BASIC_INSTRUCTION_INFO* basicinfo = new (BASIC_INSTRUCTION_INFO);
			if ((base==0)|| (size_==0))
			{
				Interaction::MsgBox("Getting base and size Error", MsgBoxStyle::OkOnly, "Error");
				Bu_Search->Enabled = true;
				return;
			}
			
			Generic::List<search__^>^ Datax = gcnew Generic::List<search__^>;
			duint temp = base;
			while (temp<base + size_)
			{
				DbgDisasmFastAt(temp, basicinfo);
				String^ pattern = TB_Regex->Text;			//@"\ba\w*\b";
				String^ input = CharArr2Str(basicinfo->instruction);
				Match^ m = Regex::Match(input, pattern, RegexOptions::IgnoreCase);
				if (m->Success) {
					search__^ ser = gcnew search__(duint2Hex(temp), CharArr2Str(basicinfo->instruction));
					Datax->Add(ser);
				}			
				temp += basicinfo->size;
			}
			DGV_Results->Rows->Clear();
			if (Datax->Count == 0) {
				Bu_Search->Enabled = true;
				return;
			}				
			DGV_Results->Rows->Add(Datax->Count );
			for (int i = 0; i < Datax->Count; i++)
			{
				DGV_Results->Rows[i]->Cells[0]->Value = Datax[i]->GetAddr();
				DGV_Results->Rows[i]->Cells[1]->Value = Datax[i]->GetDisass();
			}
		}
		else
		{
			Interaction::MsgBox("Address Error", MsgBoxStyle::OkOnly, "Error");
		}
		Bu_Search->Enabled = true;
	}
private: System::Void TB_Addr_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	SELECTIONDATA sel;
	GuiSelectionGet(GUI_DISASSEMBLY, &sel);
	TB_Addr->Text = duint2Hex(sel.start);
}
private: System::Void cPUToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	DbgCmdExecDirect(Str2ConstChar("dis " + DGV_Results->CurrentRow->Cells[0]->Value));
}
private: System::Void dumpToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	DbgCmdExecDirect(Str2ConstChar("dump " + DGV_Results->CurrentRow->Cells[0]->Value));
}
private: System::Void exportToToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

}
};
}
