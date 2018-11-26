#pragma once
#include "HelperFunctions.h"
namespace AdvancedScript {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for LogTemplate
	/// </summary>



	public ref class LogTemplate : public System::Windows::Forms::Form
	{
	public:
		LogTemplate(void)
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
		~LogTemplate()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::ComponentModel::IContainer^  components;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>

	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::ListBox^  LB_TemplateName;
	private: System::Windows::Forms::TextBox^  TB_TemplateData;
	private: System::Windows::Forms::PictureBox^  PB_Remove;

	private: System::Windows::Forms::PictureBox^  PB_Add;
	private: System::Windows::Forms::PictureBox^  PB_Rename;
	private: System::Windows::Forms::PictureBox^  PB_save;
	private: System::Windows::Forms::ContextMenuStrip^  CMS1;




	private: System::Windows::Forms::ToolStripMenuItem^  disassemblyOfInstructionToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  addressOfInstructionToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  signedDecimal3ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  unsignedDecimal57329171ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  zeroPrefixedPointer0000000410007683ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  stringPointerThisIsAStringToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  hex3C28AToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  addressInfo00401010moduleEntryPointToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  headerToolStripMenuItem;
	private: System::Windows::Forms::TextBox^  TB_info;




	public:
		ref class TemplateClass
		{
		public:
			TemplateClass(String^ TemplateName_, String^ TemplateData_) {
				TemplateName = TemplateName_;
				TemplateData = TemplateData_;
			}

		public:
			String^ TemplateName; // it's same as Template file name 
			String^ TemplateData; // it contain the Template text
		};

	public:
		static Generic::List<TemplateClass^>^ TemplateClassList = gcnew Generic::List<TemplateClass^>();


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(LogTemplate::typeid));
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->PB_save = (gcnew System::Windows::Forms::PictureBox());
			this->PB_Rename = (gcnew System::Windows::Forms::PictureBox());
			this->PB_Remove = (gcnew System::Windows::Forms::PictureBox());
			this->PB_Add = (gcnew System::Windows::Forms::PictureBox());
			this->TB_TemplateData = (gcnew System::Windows::Forms::TextBox());
			this->CMS1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->headerToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->addressOfInstructionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->disassemblyOfInstructionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->signedDecimal3ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->unsignedDecimal57329171ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->zeroPrefixedPointer0000000410007683ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->stringPointerThisIsAStringToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->hex3C28AToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->addressInfo00401010moduleEntryPointToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->LB_TemplateName = (gcnew System::Windows::Forms::ListBox());
			this->TB_info = (gcnew System::Windows::Forms::TextBox());
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB_save))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB_Rename))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB_Remove))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB_Add))->BeginInit();
			this->CMS1->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->TB_info);
			this->groupBox1->Controls->Add(this->PB_save);
			this->groupBox1->Controls->Add(this->PB_Rename);
			this->groupBox1->Controls->Add(this->PB_Remove);
			this->groupBox1->Controls->Add(this->PB_Add);
			this->groupBox1->Controls->Add(this->TB_TemplateData);
			this->groupBox1->Controls->Add(this->LB_TemplateName);
			this->groupBox1->Location = System::Drawing::Point(7, 4);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(751, 392);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			// 
			// PB_save
			// 
			this->PB_save->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"PB_save.Image")));
			this->PB_save->Location = System::Drawing::Point(186, 19);
			this->PB_save->Name = L"PB_save";
			this->PB_save->Size = System::Drawing::Size(40, 41);
			this->PB_save->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB_save->TabIndex = 5;
			this->PB_save->TabStop = false;
			this->PB_save->Click += gcnew System::EventHandler(this, &LogTemplate::PB_save_Click);
			// 
			// PB_Rename
			// 
			this->PB_Rename->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"PB_Rename.Image")));
			this->PB_Rename->Location = System::Drawing::Point(128, 19);
			this->PB_Rename->Name = L"PB_Rename";
			this->PB_Rename->Size = System::Drawing::Size(40, 41);
			this->PB_Rename->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB_Rename->TabIndex = 4;
			this->PB_Rename->TabStop = false;
			this->PB_Rename->Click += gcnew System::EventHandler(this, &LogTemplate::PB_Rename_Click);
			// 
			// PB_Remove
			// 
			this->PB_Remove->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"PB_Remove.Image")));
			this->PB_Remove->Location = System::Drawing::Point(74, 19);
			this->PB_Remove->Name = L"PB_Remove";
			this->PB_Remove->Size = System::Drawing::Size(40, 41);
			this->PB_Remove->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB_Remove->TabIndex = 3;
			this->PB_Remove->TabStop = false;
			this->PB_Remove->Click += gcnew System::EventHandler(this, &LogTemplate::PB_Remove_Click);
			// 
			// PB_Add
			// 
			this->PB_Add->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"PB_Add.Image")));
			this->PB_Add->Location = System::Drawing::Point(17, 19);
			this->PB_Add->Name = L"PB_Add";
			this->PB_Add->Size = System::Drawing::Size(40, 41);
			this->PB_Add->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB_Add->TabIndex = 2;
			this->PB_Add->TabStop = false;
			this->PB_Add->Click += gcnew System::EventHandler(this, &LogTemplate::PB_Add_Click);
			// 
			// TB_TemplateData
			// 
			this->TB_TemplateData->BackColor = System::Drawing::Color::PeachPuff;
			this->TB_TemplateData->ContextMenuStrip = this->CMS1;
			this->TB_TemplateData->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->TB_TemplateData->Location = System::Drawing::Point(250, 19);
			this->TB_TemplateData->Multiline = true;
			this->TB_TemplateData->Name = L"TB_TemplateData";
			this->TB_TemplateData->ReadOnly = true;
			this->TB_TemplateData->Size = System::Drawing::Size(493, 360);
			this->TB_TemplateData->TabIndex = 1;
			// 
			// CMS1
			// 
			this->CMS1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(9) {
				this->headerToolStripMenuItem,
					this->addressOfInstructionToolStripMenuItem, this->disassemblyOfInstructionToolStripMenuItem, this->signedDecimal3ToolStripMenuItem,
					this->unsignedDecimal57329171ToolStripMenuItem, this->zeroPrefixedPointer0000000410007683ToolStripMenuItem, this->stringPointerThisIsAStringToolStripMenuItem,
					this->hex3C28AToolStripMenuItem, this->addressInfo00401010moduleEntryPointToolStripMenuItem
			});
			this->CMS1->Name = L"contextMenuStrip1";
			this->CMS1->Size = System::Drawing::Size(316, 202);
			// 
			// headerToolStripMenuItem
			// 
			this->headerToolStripMenuItem->Name = L"headerToolStripMenuItem";
			this->headerToolStripMenuItem->Size = System::Drawing::Size(315, 22);
			this->headerToolStripMenuItem->Text = L"Header";
			this->headerToolStripMenuItem->Click += gcnew System::EventHandler(this, &LogTemplate::headerToolStripMenuItem_Click);
			// 
			// addressOfInstructionToolStripMenuItem
			// 
			this->addressOfInstructionToolStripMenuItem->Name = L"addressOfInstructionToolStripMenuItem";
			this->addressOfInstructionToolStripMenuItem->Size = System::Drawing::Size(315, 22);
			this->addressOfInstructionToolStripMenuItem->Text = L"Address of Instruction";
			this->addressOfInstructionToolStripMenuItem->Click += gcnew System::EventHandler(this, &LogTemplate::addressOfInstructionToolStripMenuItem_Click);
			// 
			// disassemblyOfInstructionToolStripMenuItem
			// 
			this->disassemblyOfInstructionToolStripMenuItem->Name = L"disassemblyOfInstructionToolStripMenuItem";
			this->disassemblyOfInstructionToolStripMenuItem->Size = System::Drawing::Size(315, 22);
			this->disassemblyOfInstructionToolStripMenuItem->Text = L"Disassembly of Instruction";
			this->disassemblyOfInstructionToolStripMenuItem->Click += gcnew System::EventHandler(this, &LogTemplate::disassemblyOfInstructionToolStripMenuItem_Click);
			// 
			// signedDecimal3ToolStripMenuItem
			// 
			this->signedDecimal3ToolStripMenuItem->Name = L"signedDecimal3ToolStripMenuItem";
			this->signedDecimal3ToolStripMenuItem->Size = System::Drawing::Size(315, 22);
			this->signedDecimal3ToolStripMenuItem->Text = L"signed decimal / -3";
			this->signedDecimal3ToolStripMenuItem->Click += gcnew System::EventHandler(this, &LogTemplate::signedDecimal3ToolStripMenuItem_Click);
			// 
			// unsignedDecimal57329171ToolStripMenuItem
			// 
			this->unsignedDecimal57329171ToolStripMenuItem->Name = L"unsignedDecimal57329171ToolStripMenuItem";
			this->unsignedDecimal57329171ToolStripMenuItem->Size = System::Drawing::Size(315, 22);
			this->unsignedDecimal57329171ToolStripMenuItem->Text = L"unsigned decimal / 57329171";
			this->unsignedDecimal57329171ToolStripMenuItem->Click += gcnew System::EventHandler(this, &LogTemplate::unsignedDecimal57329171ToolStripMenuItem_Click);
			// 
			// zeroPrefixedPointer0000000410007683ToolStripMenuItem
			// 
			this->zeroPrefixedPointer0000000410007683ToolStripMenuItem->Name = L"zeroPrefixedPointer0000000410007683ToolStripMenuItem";
			this->zeroPrefixedPointer0000000410007683ToolStripMenuItem->Size = System::Drawing::Size(315, 22);
			this->zeroPrefixedPointer0000000410007683ToolStripMenuItem->Text = L"zero prefixed pointer / 0000000410007683";
			this->zeroPrefixedPointer0000000410007683ToolStripMenuItem->Click += gcnew System::EventHandler(this, &LogTemplate::zeroPrefixedPointer0000000410007683ToolStripMenuItem_Click);
			// 
			// stringPointerThisIsAStringToolStripMenuItem
			// 
			this->stringPointerThisIsAStringToolStripMenuItem->Name = L"stringPointerThisIsAStringToolStripMenuItem";
			this->stringPointerThisIsAStringToolStripMenuItem->Size = System::Drawing::Size(315, 22);
			this->stringPointerThisIsAStringToolStripMenuItem->Text = L"string pointer /  this is a string";
			this->stringPointerThisIsAStringToolStripMenuItem->Click += gcnew System::EventHandler(this, &LogTemplate::stringPointerThisIsAStringToolStripMenuItem_Click);
			// 
			// hex3C28AToolStripMenuItem
			// 
			this->hex3C28AToolStripMenuItem->Name = L"hex3C28AToolStripMenuItem";
			this->hex3C28AToolStripMenuItem->Size = System::Drawing::Size(315, 22);
			this->hex3C28AToolStripMenuItem->Text = L"hex / 3C28A";
			this->hex3C28AToolStripMenuItem->Click += gcnew System::EventHandler(this, &LogTemplate::hex3C28AToolStripMenuItem_Click);
			// 
			// addressInfo00401010moduleEntryPointToolStripMenuItem
			// 
			this->addressInfo00401010moduleEntryPointToolStripMenuItem->Name = L"addressInfo00401010moduleEntryPointToolStripMenuItem";
			this->addressInfo00401010moduleEntryPointToolStripMenuItem->Size = System::Drawing::Size(315, 22);
			this->addressInfo00401010moduleEntryPointToolStripMenuItem->Text = L"address info / 00401010 <module.EntryPoint>";
			this->addressInfo00401010moduleEntryPointToolStripMenuItem->Click += gcnew System::EventHandler(this, &LogTemplate::addressInfo00401010moduleEntryPointToolStripMenuItem_Click);
			// 
			// LB_TemplateName
			// 
			this->LB_TemplateName->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->LB_TemplateName->FormattingEnabled = true;
			this->LB_TemplateName->ItemHeight = 16;
			this->LB_TemplateName->Location = System::Drawing::Point(6, 71);
			this->LB_TemplateName->Name = L"LB_TemplateName";
			this->LB_TemplateName->Size = System::Drawing::Size(238, 116);
			this->LB_TemplateName->TabIndex = 0;
			this->LB_TemplateName->SelectedIndexChanged += gcnew System::EventHandler(this, &LogTemplate::LB_TemplateName_SelectedIndexChanged);
			// 
			// TB_info
			// 
			this->TB_info->Location = System::Drawing::Point(6, 200);
			this->TB_info->Multiline = true;
			this->TB_info->Name = L"TB_info";
			this->TB_info->ReadOnly = true;
			this->TB_info->Size = System::Drawing::Size(237, 178);
			this->TB_info->TabIndex = 6;
			// 
			// LogTemplate
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(765, 401);
			this->Controls->Add(this->groupBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->Name = L"LogTemplate";
			this->Text = L"LogTemplate";
			this->Load += gcnew System::EventHandler(this, &LogTemplate::LogTemplate_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB_save))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB_Rename))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB_Remove))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB_Add))->EndInit();
			this->CMS1->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void LogTemplate_Load(System::Object^  sender, System::EventArgs^  e) {
		//check if the template folder is created (exist)
		if (!IO::Directory::Exists(Application::StartupPath + "\\LogTemplate")) {
			IO::Directory::CreateDirectory(Application::StartupPath + "\\LogTemplate");
		}
		else {
			LoadTemplateFiles();
		}
	}
	private: System::Void LoadTemplateFiles() {
		if (IO::Directory::Exists(Application::StartupPath + "\\LogTemplate")) {
			for each (String^ file_ in IO::Directory::GetFiles(Application::StartupPath + "\\LogTemplate"))
			{
				String^ templatedata = IO::File::ReadAllText(file_);
				String^ templateName = IO::Path::GetFileName(file_);
				TemplateListAdd(templateName, templatedata);
				LB_TemplateName->Items->Add(templateName);
			}
		}
		if (TemplateClassList->Count > 0) {
			LB_TemplateName->SelectedIndex = 0;
			TB_TemplateData->ReadOnly = false;
			TB_TemplateData->Text = TemplateClassList[0]->TemplateData;
		}
	}
	private: System::Void PB_Add_Click(System::Object^  sender, System::EventArgs^  e) {
		if (IO::Directory::Exists(Application::StartupPath + "\\LogTemplate")) {
			String^ TemplateName = Microsoft::VisualBasic::Interaction::InputBox("Please Enter name for template", "Create new Template", "Template" + LB_TemplateName->Items->Count, this->Height / 2, this->Width / 2);
			if (TemplateName != "") {
				LB_TemplateName->Items->Add(TemplateName);
				IO::File::WriteAllText(Application::StartupPath + "\\LogTemplate\\" + TemplateName, "");
				TemplateListAdd(TemplateName, "");
			}
		}
		else { Microsoft::VisualBasic::Interaction::MsgBox("LogTemplate not exist", Microsoft::VisualBasic::MsgBoxStyle::DefaultButton1, "Error"); }

	}
	private: System::Void PB_Remove_Click(System::Object^  sender, System::EventArgs^  e) {
		TemplateListRemoveAt(LB_TemplateName->GetItemText(LB_TemplateName->SelectedItem), TB_TemplateData->Text);
	}

	private: System::Void PB_Rename_Click(System::Object^  sender, System::EventArgs^  e) {
		String^ TemplateName_ = Microsoft::VisualBasic::Interaction::InputBox("Please Enter name for template", "Create new Template", "Template" + LB_TemplateName->Items->Count, this->Height / 2, this->Width / 2);
		if (TemplateName_ != "") {
			TemplateListUpdatebyName(LB_TemplateName->GetItemText(LB_TemplateName->SelectedItem), TemplateName_, TB_TemplateData->Text);
			LB_TemplateName->Text = TemplateName_;
		}
	}
	private: System::Void PB_save_Click(System::Object^  sender, System::EventArgs^  e) {
		TemplateListUpdatebyName(LB_TemplateName->GetItemText(LB_TemplateName->SelectedItem), LB_TemplateName->GetItemText(LB_TemplateName->SelectedItem), TB_TemplateData->Text);
		Microsoft::VisualBasic::Interaction::MsgBox("Done", Microsoft::VisualBasic::MsgBoxStyle::DefaultButton1, "Info");
	}

	private: System::Void LB_TemplateName_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		TB_TemplateData->ReadOnly = false;
		int index_ = LB_TemplateName->SelectedIndex;
		for each (TemplateClass^ var in TemplateClassList)
		{
			if (var->TemplateName == LB_TemplateName->GetItemText(LB_TemplateName->SelectedItem)) {
				TB_TemplateData->Text = var->TemplateData;
				break;
			}

		}
	}
	private: System::Void TemplateListAdd(String^ TemplateName, String^ templatedata) {
		TemplateClass^ TemplateClass_ = gcnew TemplateClass(TemplateName, templatedata);
		TemplateClassList->Add(TemplateClass_);
	}

	private: System::Void TemplateListRemoveAt(String^ TemplateName, String^ templatedata) {
		for (int x = 0; x < TemplateClassList->Count; ++x) {
			if (TemplateName == TemplateClassList[x]->TemplateName && templatedata == TemplateClassList[x]->TemplateData) {
				TemplateClassList->RemoveAt(x);
				IO::File::Delete(Application::StartupPath + "\\LogTemplate\\" + TemplateName);
				LB_TemplateName->Items->RemoveAt(LB_TemplateName->SelectedIndex);
			}
		}
	}
	private: System::Void TemplateListUpdatebyName(String^ TemplateName, String^ TemplateNameNew, String^ templatedata) {
		for each (TemplateClass^ var in TemplateClassList)
		{
			if (var->TemplateName == TemplateName && TemplateName == TemplateNameNew) {
				var->TemplateData = templatedata;
				IO::File::WriteAllText(Application::StartupPath + "\\LogTemplate\\" + TemplateName, templatedata);

			}
			if (var->TemplateData == templatedata && TemplateName != TemplateNameNew) {
				var->TemplateName = TemplateName;
				IO::File::Move(Application::StartupPath + "\\LogTemplate\\" + TemplateName, Application::StartupPath + "\\LogTemplate\\" + TemplateNameNew);
			}
		}
	}



	private: System::Void headerToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		TB_TemplateData->Paste("(h\\   .....  \\h1)");
		TB_info->Text = "This is Header can appear one time or always, depended on the number after last h " + Environment::NewLine + "\\h1 one time " + Environment::NewLine + "\\h it always appear";
	}
	private: System::Void addressOfInstructionToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		TB_TemplateData->Paste("{p:cip}");
		TB_info->Text = "cip mean RIP now";// +Environment::NewLine + "{p:0x32635241}";
	}
	private: System::Void disassemblyOfInstructionToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		TB_TemplateData->Paste("{i:cip}");
		TB_info->Text = "cip mean RIP now , you can replace cip with address if you want and it will get disassemble at that address" + Environment::NewLine + "{i:0x32635241}";
	}
	private: System::Void signedDecimal3ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		TB_TemplateData->Paste("{d:cip}");
		TB_info->Text = "cip mean RIP now , you can replace cip with an address if you want " + Environment::NewLine + "{d:0x32635241}";
	}
	private: System::Void unsignedDecimal57329171ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		TB_TemplateData->Paste("{u:cip}");
		TB_info->Text = "cip mean RIP now , you can replace cip with an address if you want" + Environment::NewLine + "{u:0x32635241}";
	}
	private: System::Void zeroPrefixedPointer0000000410007683ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		TB_TemplateData->Paste("{p:cip}");
		TB_info->Text = "cip mean RIP now , you can replace cip with an address if you want, it return number with it's mising 00000" + Environment::NewLine + "{p:0x32635241}";
	}
	private: System::Void stringPointerThisIsAStringToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		TB_TemplateData->Paste("{s:cip}");
		TB_info->Text = "cip mean RIP now , you can replace cip with an address if you want it will return the string at that memory if it exist" + Environment::NewLine + "{s:0x32635241}";
	}
	private: System::Void hex3C28AToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		TB_TemplateData->Paste("{x:cip}");
		TB_info->Text = "cip mean RIP now , you can replace cip with an address if you want, it return hex value of the address" + Environment::NewLine + "{x:0x32635241}";
	}
	private: System::Void addressInfo00401010moduleEntryPointToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		TB_TemplateData->Paste("{a:cip}");
		TB_info->Text = "cip mean RIP now , you can replace cip with an address if you want, address info: 00401010 <module.EntryPoint>" + Environment::NewLine + "{a:0x32635241}";
	}
	};
}
