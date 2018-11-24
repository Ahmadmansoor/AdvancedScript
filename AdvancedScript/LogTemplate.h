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

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::ListBox^  LB_TemplateName;
	private: System::Windows::Forms::TextBox^  TB_TemplateData;
	private: System::Windows::Forms::PictureBox^  PB_Remove;

	private: System::Windows::Forms::PictureBox^  PB_Add;
	private: System::Windows::Forms::PictureBox^  PB_Rename;
	private: System::Windows::Forms::PictureBox^  PB_save;



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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(LogTemplate::typeid));
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->PB_save = (gcnew System::Windows::Forms::PictureBox());
			this->PB_Rename = (gcnew System::Windows::Forms::PictureBox());
			this->PB_Remove = (gcnew System::Windows::Forms::PictureBox());
			this->PB_Add = (gcnew System::Windows::Forms::PictureBox());
			this->TB_TemplateData = (gcnew System::Windows::Forms::TextBox());
			this->LB_TemplateName = (gcnew System::Windows::Forms::ListBox());
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB_save))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB_Rename))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB_Remove))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB_Add))->BeginInit();
			this->SuspendLayout();
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->PB_save);
			this->groupBox1->Controls->Add(this->PB_Rename);
			this->groupBox1->Controls->Add(this->PB_Remove);
			this->groupBox1->Controls->Add(this->PB_Add);
			this->groupBox1->Controls->Add(this->TB_TemplateData);
			this->groupBox1->Controls->Add(this->LB_TemplateName);
			this->groupBox1->Location = System::Drawing::Point(7, 4);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(824, 397);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			// 
			// PB_save
			// 
			this->PB_save->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"PB_save.Image")));
			this->PB_save->Location = System::Drawing::Point(235, 19);
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
			this->PB_Rename->Location = System::Drawing::Point(163, 19);
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
			this->PB_Remove->Location = System::Drawing::Point(92, 19);
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
			this->PB_Add->Location = System::Drawing::Point(24, 19);
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
			this->TB_TemplateData->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->TB_TemplateData->Location = System::Drawing::Point(322, 19);
			this->TB_TemplateData->Multiline = true;
			this->TB_TemplateData->Name = L"TB_TemplateData";
			this->TB_TemplateData->ReadOnly = true;
			this->TB_TemplateData->Size = System::Drawing::Size(493, 368);
			this->TB_TemplateData->TabIndex = 1;
			// 
			// LB_TemplateName
			// 
			this->LB_TemplateName->FormattingEnabled = true;
			this->LB_TemplateName->Location = System::Drawing::Point(6, 71);
			this->LB_TemplateName->Name = L"LB_TemplateName";
			this->LB_TemplateName->Size = System::Drawing::Size(297, 316);
			this->LB_TemplateName->TabIndex = 0;
			this->LB_TemplateName->SelectedIndexChanged += gcnew System::EventHandler(this, &LogTemplate::LB_TemplateName_SelectedIndexChanged);
			// 
			// LogTemplate
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(837, 408);
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
	

	};
}
