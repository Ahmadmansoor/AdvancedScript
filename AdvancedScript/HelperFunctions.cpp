#include "HelperFunctions.h"
#include <msclr/marshal.h>
#include "LogTemplate.h"

//C and C++ deal with backslashes as escape sequences by default.
//You got to tell C to not use your backslash as an escape sequence by adding an extra backslash to your string.
//These are the common escape sequences :
//\a - Bell(beep)
//\b - Backspace
//\f - Formfeed
//\n - New line
//\r - Carriage Return
//\t - Horizontal Tab
//\\ - Backslash
//\' - Single Quotation Mark
//\" - Double Quatation Mark
//\ooo - Octal Representation
//\xdd - Hexadecimal Representaion


System::Void GetArg(String^ input, Generic::List<String^>^% arguments) { // this function use by refrence so the list will fill direct
	// the arguments are not include the Function name
	arguments = gcnew Generic::List<String^>;
	arguments->Clear(); /// we have to clear the arry just in case it have elements form previose process
	if (!input->Contains(" ")) { return; }
	input = input->Substring(input->IndexOf(" "), input->Length - input->IndexOf(" "))->Trim(); // remove first agument which is the Function call
	String^ temp;
	//bool notfound = false;
	for (size_t i = 0; i <= input->Length; i++)
	{
		if (i == input->Length) {
			if (temp->Trim() != "") {
				arguments->Add(temp->Trim());
				temp = "";
			}
			break;
		}
		if (input->Substring(i, 1) != ",") {
			//if ((input->Substring(i, 1) != ",") && (input->Substring(i, 1) != "\"")) {
			if (input->Substring(i, 1) != ",") {
				temp = temp + input->Substring(i, 1);
			}
			//if (input->Substring(i, 1) == "\"") {  /// case some arguments have (") like a string >> "Test.txt"
			//	String^ restTemp = input->Substring(i + 1, input->Length - (i + 1)); // get the rest of the string (input)
			//	int indexOfNextcomma= restTemp->IndexOf("\"");
			//	if (indexOfNextcomma < 1) {
			//		Script::Gui::Message("Something Wrong in the arguments");
			//		return;
			//	}
			//	arguments->Add(restTemp->Substring(0, indexOfNextcomma));
			//	temp = "";
			//	i = i + indexOfNextcomma + 1;
			//}
		}
		else {
			arguments->Add(temp->Trim());
			temp = "";
		}
	}
}

char* StringFormatInline_(String^ format) {
	char* result = new char[MAX_STRING_SIZE];
	size_t resultSize = MAX_STRING_SIZE;
	const char* format_ = Str2ConstChar(format);
	DbgFunctions()->StringFormatInline(format_, MAX_STRING_SIZE, result);
	return result;
}

String^ StringFormatInline_Str(String^ format) {
	char* result = new char[MAX_STRING_SIZE];
	size_t resultSize = MAX_STRING_SIZE;
	const char* format_ = Str2ConstChar(format);
	DbgFunctions()->StringFormatInline(format_, MAX_STRING_SIZE, result);
	return charPTR2String(result);
}

String^ GetAPIName_LableWay(duint Addr_) {
	SEGMENTREG segment;
	char* text = new char[MAX_STRING_SIZE];
	char* ModuleName = new char[MAX_STRING_SIZE]();
	DbgGetModuleAt(Addr_, ModuleName);
	DbgGetLabelAt(Addr_, segment, text);
	return(charPTR2String(ModuleName) + "." + charPTR2String(text));
}

const char* Str2ConstChar(System::String^ string_) {
	IntPtr p = Marshal::StringToHGlobalAnsi(string_);
	const char* linkStr = static_cast<char*>(p.ToPointer());
	return linkStr;
}


bool OnlyHexInString(String^ test) {  // it will remove 0x if it's at the beganing of the string
	try
	{
		int x = Convert::ToInt64(test);
		return true;
	}
	catch (MyException^ e)
	{
		return false;
	}

}


String^ CharArr2Str(char input_[]) {
	return gcnew String(input_);
}


String^ ClearSlash_etc(String^ input) {
	String^ temp;
	for (int i = 0; i < input->Length - 1; ++i) {
		//if (input->Substring(i, 1) != "\\" || input->Substring(i, 1) != ":") {
		if (Char::IsDigit(input, i) || Char::IsLetter(input, i) || input->Substring(i, 1) == ".") {
			temp = temp + input->Substring(i, 1);
		}
	}
	return temp;
}

String^ charPTR2String(char* input) {

	//String^ temp = gcnew String(input);
	//const char* t = static_cast<const char*>(input);
	std::string temp2(input);
	std::wstring temp(temp2.begin(), temp2.end());
	String^ temp1 = gcnew String(temp.c_str());
	return temp1;

}

duint Hex2duint(String^ input_) {
	if (input_->Length > 2) {
		if (input_->Substring(0, 2)->ToLower() == "0x") {
			input_ = input_->Substring(2, input_->Length - 2);
		}
	}
	for (size_t i = 0; i < input_->Length; i++)
	{
		if (!Information::IsNumeric(input_->Substring(i, 1)) && !Char::IsLetter(input_->Substring(i, 1), 0)) {
			return -1;
		}
	}

#ifdef _WIN64
	return __int64::Parse(reMoveSpaces(input_), System::Globalization::NumberStyles::HexNumber);
#else
	return __int32::Parse(reMoveSpaces(input_), System::Globalization::NumberStyles::HexNumber);
#endif //_WIN64


}


String^ duint2Hex(duint input_) {
	try
	{
#ifdef _WIN64
		return Conversion::Hex(input_);
#else
		int tem = input_;
		return Conversion::Hex(tem);
#endif //_WIN64

	}
	catch (const std::exception&)
	{
		return "";
	}
}


bool Str2bool(String^ input_) {
	try
	{
		if (input_->Trim()->ToLower() == "true") {
			return true;
		}
		if (input_->Trim()->ToLower() == "false")
		{
			return false;
		}

		if (input_->Trim()->ToLower() == "on") {
			return true;
		}
		if (input_->Trim()->ToLower() == "off")
		{
			return false;
		}

		if (input_->Trim()->ToLower() == "1") {
			return true;
		}
		if (input_->Trim()->ToLower() == "0")
		{
			return false;
		}

		Script::Gui::Message("The arrgaments can't convert to bool, the default value will be false");
		return false;
	}
	catch (const std::exception&)
	{
		Script::Gui::Message("error in arrgaments can't convert to bool");
	}
}

String^ reMoveSpaces(String^ input_) {
	String^ temp;
	for (int i = 0; i < input_->Length; ++i) {
		if (input_->Substring(i, 1) != " ") {
			temp = temp + input_->Substring(i, 1);
		}
	}
	return temp;
}
