#pragma once
#include "ScriptArgumentWindow.h"
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
	private: System::ComponentModel::IContainer^  components;
	

	protected:




	protected:




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
			this->startHereToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pasteToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DGV1))->BeginInit();
			this->CMT1->SuspendLayout();
			this->SuspendLayout();
			// 
			// DGV1
			// 
			this->DGV1->AllowUserToOrderColumns = true;
			this->DGV1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
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
			this->DGV1->Location = System::Drawing::Point(1, 1);
			this->DGV1->Name = L"DGV1";
			this->DGV1->Size = System::Drawing::Size(1042, 454);
			this->DGV1->TabIndex = 0;
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
			this->CMT1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->startHereToolStripMenuItem,
					this->pasteToolStripMenuItem
			});
			this->CMT1->Name = L"CMT1";
			this->CMT1->Size = System::Drawing::Size(158, 48);
			// 
			// startHereToolStripMenuItem
			// 
			this->startHereToolStripMenuItem->Name = L"startHereToolStripMenuItem";
			this->startHereToolStripMenuItem->Size = System::Drawing::Size(157, 22);
			this->startHereToolStripMenuItem->Text = L"Start Here";
			this->startHereToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::startHereToolStripMenuItem_Click);
			// 
			// pasteToolStripMenuItem
			// 
			this->pasteToolStripMenuItem->Name = L"pasteToolStripMenuItem";
			this->pasteToolStripMenuItem->Size = System::Drawing::Size(157, 22);
			this->pasteToolStripMenuItem->Text = L"Paste Clipboard";
			this->pasteToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::pasteToolStripMenuItem_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1044, 596);
			this->Controls->Add(this->DGV1);
			this->KeyPreview = true;
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->DGV1))->EndInit();
			this->CMT1->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void DGV1_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		if (e->KeyCode == Keys::F12) {
			DGV1->ClearSelection();
			if (ScriptargumentClass::Scriptargument_->GetLineNumber() < DGV1->RowCount-1) {				
				DGV1->ClearSelection();
				DGV1->Rows[ScriptargumentClass::Scriptargument_->GetLineNumber()]->Selected = true;
				readLine(DGV1->Rows[ScriptargumentClass::Scriptargument_->GetLineNumber()]->Cells[1]->Value->ToString(), DGV1->Rows->Count);
			}
			else
			{
				DGV1->ClearSelection();
				DGV1->Rows[0]->Selected = true;
				ScriptargumentClass::Scriptargument_->setLineNumber(0);
			}
		}
	}
	private: System::Void DGV1_RowsAdded(System::Object^  sender, System::Windows::Forms::DataGridViewRowsAddedEventArgs^  e) {
		for (int i = 0; i < DGV1->RowCount - 1; i++)
		{
			DGV1->Rows[i]->Cells[0]->Value = i;
		}
	}
	private: System::Void DGV1_RowsRemoved(System::Object^  sender, System::Windows::Forms::DataGridViewRowsRemovedEventArgs^  e) {
		for (int i = 0; i < DGV1->RowCount - 1; i++)
		{
			DGV1->Rows[i]->Cells[0]->Value = i;
		}
	}
private: System::Void startHereToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	ScriptargumentClass::Scriptargument_->setLineNumber(DGV1->CurrentRow->Index - 1);
}		 
private: System::Void pasteToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	DGV1->Rows->Clear();		
	char* line=GetClipBoard(); 
	int i = 0;
	/*while ((line = MyClassScriptArray::ScriptArray->ReadLine()) != nullptr)
	{
		DGV1->Rows->Add();
		DGV1->Rows[i]->Cells[0]->Value = i;
		DGV1->Rows[i]->Cells[1]->Value = line;
		i += 1;
	}*/
	
}

};
}
