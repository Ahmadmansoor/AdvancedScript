#pragma once

namespace AdvancedScript {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;




	/// <summary>
	/// Summary for LogWindow
	/// </summary>
	public ref class LogWindow : public System::Windows::Forms::Form
	{

	public:
		////////////////////////////
		// we add this line to anable to call RTB1 from out side 
		//https://social.msdn.microsoft.com/Forums/en-US/dcc8228d-6937-450d-b4e2-e833fb1f388b/access-a-forms-public-functions-from-a-global-function-in-a-different-file?forum=Vsexpressvc
		// here we define Initialized form so we can can access it directly 
		static LogWindow^ LogWindow_ = gcnew LogWindow();
		//////////////////////////// we add some more line down to access the RichTextBox from out side of the Thread
	public:
		LogWindow(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			//TheInstance = this;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~LogWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	public: System::Windows::Forms::RichTextBox^  RTB1;
	public: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
	private: System::Windows::Forms::ContextMenuStrip^  CMS1;
	public:
	private: System::Windows::Forms::ToolStripMenuItem^  clearToolStripMenuItem;
	public:
	protected:

	protected:

	private: System::ComponentModel::IContainer^  components;
	public:
	protected:

	protected:


	protected:

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
			this->RTB1 = (gcnew System::Windows::Forms::RichTextBox());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->CMS1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->clearToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->CMS1->SuspendLayout();
			this->SuspendLayout();
			// 
			// RTB1
			// 
			this->RTB1->ContextMenuStrip = this->CMS1;
			this->RTB1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->RTB1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->RTB1->Location = System::Drawing::Point(0, 0);
			this->RTB1->Name = L"RTB1";
			this->RTB1->ReadOnly = true;
			this->RTB1->Size = System::Drawing::Size(678, 404);
			this->RTB1->TabIndex = 0;
			this->RTB1->Text = L"";
			// 
			// CMS1
			// 
			this->CMS1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->clearToolStripMenuItem });
			this->CMS1->Name = L"CMS1";
			this->CMS1->Size = System::Drawing::Size(153, 48);
			// 
			// clearToolStripMenuItem
			// 
			this->clearToolStripMenuItem->Name = L"clearToolStripMenuItem";
			this->clearToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->clearToolStripMenuItem->Text = L"Clear";
			this->clearToolStripMenuItem->Click += gcnew System::EventHandler(this, &LogWindow::clearToolStripMenuItem_Click);
			// 
			// LogWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(678, 404);
			this->Controls->Add(this->RTB1);
			this->Name = L"LogWindow";
			this->Text = L"LogWindow";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &LogWindow::LogWindow_FormClosed);
			this->Load += gcnew System::EventHandler(this, &LogWindow::LogWindow_Load);
			this->CMS1->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	public:
		static bool FormLoaded = false;  // we difine it to check if the form is loaded or not so they are no clashing to show the form 
	private: System::Void LogWindow_Load(System::Object^  sender, System::EventArgs^  e) {
		FormLoaded = true;
		AdvancedScript::LogWindow::LogWindow_->RTB1->Text = Log_Str;
	}
	private: System::Void LogWindow_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
		FormLoaded = false;
	}
			 //////////////////////////////////
			 //we add some more line down to access the RichTextBox from out side of the Thread
	public:
		static String^ Log_Str = "";  /// this will hold all Log messages
		delegate void SetTextCallback(String^ text); // delegate Function to Invoke RichTextBox for the first time
	public:
		static void RTBAppendText(String^ text) {
			if (AdvancedScript::LogWindow::LogWindow_->RTB1->InvokeRequired)
			{
				SetTextCallback^ d = gcnew SetTextCallback(RTBAppendText);
				AdvancedScript::LogWindow::LogWindow_->Invoke(d, gcnew array<System::Object^>{text});
			}
			else
			{
				AdvancedScript::LogWindow::LogWindow_->RTB1->AppendText(Environment::NewLine);
				AdvancedScript::LogWindow::LogWindow_->RTB1->AppendText(text);
			}
		}
		//////////////////////////////////
		


	private: System::Void clearToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		Log_Str = "";
		AdvancedScript::LogWindow::LogWindow_->RTB1->Text = "";
	}
};
}
