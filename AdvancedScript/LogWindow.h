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
		// we add this line to anable to call RTB1 from out side 
		//https://social.msdn.microsoft.com/Forums/en-US/dcc8228d-6937-450d-b4e2-e833fb1f388b/access-a-forms-public-functions-from-a-global-function-in-a-different-file?forum=Vsexpressvc
		static LogWindow^ TheInstance; 
		LogWindow(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			TheInstance = this;
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
	private: System::Windows::Forms::RichTextBox^  RTB1;
	protected:

	protected:

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
			this->RTB1 = (gcnew System::Windows::Forms::RichTextBox());
			this->SuspendLayout();
			// 
			// RTB1
			// 
			this->RTB1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->RTB1->Location = System::Drawing::Point(0, 0);
			this->RTB1->Name = L"RTB1";
			this->RTB1->Size = System::Drawing::Size(678, 404);
			this->RTB1->TabIndex = 0;
			this->RTB1->Text = L"";
			// 
			// LogWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(678, 404);
			this->Controls->Add(this->RTB1);
			this->Name = L"LogWindow";
			this->Text = L"LogWindow";
			this->Load += gcnew System::EventHandler(this, &LogWindow::LogWindow_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void LogWindow_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	public:	System::Void RTB1_Log(String^ Input) {
			AdvancedScript::LogWindow::RTB1->AppendText(Input);
		}
	
	};
}
