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
//
//% -mod
// -div


System::Void GetArg(String^ input, Generic::List<String^>^% arguments, bool brackets) { // this function use by refrence so the list will fill direct
	// the arguments are not include the Function name
	arguments = gcnew Generic::List<String^>;
	arguments->Clear(); /// we have to clear the arry just in case it have elements form previose process

	if (brackets) {
		if (input->IndexOf(")") < 0) {
			_plugin_logprint("missing ) in brackets Phrase");
			return;
		}
		input = input->Substring(input->IndexOf("(") + 1, input->Length - (input->IndexOf("(") + 1)); ///remove after first (		
		input = input->Substring(0, input->IndexOf(")"));
	}
	else {
		if (!input->Contains(" ")) { return; }
		input = input->Substring(input->IndexOf(" "), input->Length - input->IndexOf(" "))->Trim(); // remove first agument which is the Function call
	}
	String^ temp;
	//bool notfound = false;
	for (int i = 0; i <= input->Length; i++)
	{
		if (i == input->Length) {
			if (temp->Trim() != "") {
				arguments->Add(temp->Trim());
				temp = "";
			}
			break;
		}
		if (input->Substring(i, 1) != ",") {
			if (input->Substring(i, 1) == "(") {  /// in case we find function call inside
				do
				{
					temp = temp + input->Substring(i, 1);
					i += 1;
				} while ((input->Substring(i, 1) != ")" && i != input->Length));
			}
			//if ((input->Substring(i, 1) != ",") && (input->Substring(i, 1) != "\"")) {
			if (input->Substring(i, 1) != ",") {
				temp = temp + input->Substring(i, 1);
			}
			if (input->Substring(i, 1) == "\"") {  /// case some arguments have (") like a string >> "Test.txt"
				String^ restTemp = input->Substring(i + 1, input->Length - (i + 1)); // get the rest of the string (input)
				int indexOfNextcomma= restTemp->LastIndexOf("\"");
				if (indexOfNextcomma > 0) {       ///if (indexOfNextcomma < 1) {
					/*Script::Gui::Message("Something Wrong in the arguments");
					return;*/
					if ((temp != "") && (temp != "\"")) {
						temp = temp->Substring(0,temp->IndexOf("\"")) + restTemp->Substring(0, indexOfNextcomma);  // temp->Substring(0,temp->IndexOf("\"")) to remove comma at end
					}
					else
					{
						arguments->Add(restTemp->Substring(0, indexOfNextcomma));
						temp = "";
					}							
					i = i + indexOfNextcomma + 1;
				}
				/*arguments->Add(restTemp->Substring(0, indexOfNextcomma));
				temp = "";
				i = i + indexOfNextcomma + 1;*/
			}
		}
		else {
			if ( (temp != "") && (temp != " ") ){
			arguments->Add(temp->Trim());
			temp = "";
			}
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
	SEGMENTREG segment = SEG_DEFAULT;
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

char* Str2CharPTR(System::String^ string_) {	
	try
	{
		char* str2 = (char*)(void*)Marshal::StringToHGlobalAnsi(string_);
		return str2;
	}
	catch (const std::exception&)
	{

	}
	
}

//bool OnlyHexInString(String^ test) {  // it will remove 0x if it's at the beganing of the string
//	try
//	{
//		int x = Convert::ToInt64(test);
//		return true;
//	}
//	catch (MyException^ e)
//	{
//		return false;
//	}
//
//}


/// <summary> 
/// 0 not hex not numeric // 1 is numeric // 2 is hex 
/// </summary> 
int CheckHexIsValid(String^ input_,String^% intValue) {   // the return value is in int store in str var
	input_ = input_->Trim();
	// For C-style hex notation (0xFF) you can use @"\A\b(0[xX])?[0-9a-fA-F]+\b\Z"
	array <String^>^ c = { "0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F","a","b","c","d","e","f" };
#ifdef _WIN64
	//if ((input_->Length < 5) || (input_->Length > 16)) {		
	if (Information::IsNumeric(input_)) {		
		intValue = (int2Str(Hex2duint(input_)))->Trim();
		return 1;
	}	
#else
	//if ((input_->Length < 5) || (input_->Length > 8)) {
	if (Information::IsNumeric(input_)) {		
		intValue = int2Str(Hex2duint(input_));
		return 1;
	}	
#endif // _WIN64
	if (input_->Length > 2) {
		if (input_->Substring(0, 2)->ToLower() == "0x") {   /// in case have 0x at begin we removed 
			input_ = input_->Substring(2, input_->Length - 2);
		}
	}
	for (int i = 0; i < input_->Length; i++)
	{
		if (Array::IndexOf(c, input_->Substring(i, 1)) < 0) {
			intValue = "NULL/ ";
			return 0;
		}

	}	
	intValue = (int2Str(Hex2duint(input_)))->Trim();
	return 2;
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

/// it return hex from string if avalible 
/// in case the input value is int it will be converted to hex 
/// 
String^ str2Hex(String^ input,VarType inputType_, bool addx0) {
	String^ intValue;
	if (input->StartsWith("0x")) {  /// it mean its hex value
		if (CheckHexIsValid(input->Substring(2, input->Length-2), intValue) > 0) {
			if (addx0) 
				return input;			
			else			
				return input->Substring(2, input->Length - 2);			
		}		
	}
	else
	{
		int check_ = CheckHexIsValid(input, intValue);
		switch (check_)
		{		
		case 1: {   /// the value is numaric so we don't know if it's hex or int so user define it
			if (inputType_ == VarType::int_) {   /// the input value is int not hex value 
				if (addx0)
					return "0x" + duint2Hex(Str2duint(input));
				else
					return  duint2Hex(Str2duint(input));
			}
			else   /// the input value is hex 
			{
				if (addx0)
					return  input;
				else
					return  "0x" + input;
			}
			
		}
		case 2: {  ///  the value is valid hex 
			if (addx0)
				return  input;
			else
				return  "0x" + input;
		}
		default:
			return "NULL /";
		}	
	}
	return "NULL/";
}

duint Hex2duint(String^ input_) {
	if (input_->Length > 2) {
		if (input_->Substring(0, 2)->ToLower() == "0x") {
			input_ = input_->Substring(2, input_->Length - 2);
		}
	}
	String^ input_temp = input_->Trim();
	for (int i = 0; i < input_temp->Length; i++)
	{		
		if (!Information::IsNumeric(input_temp->Substring(i, 1)) && !Char::IsLetter(input_temp->Substring(i, 1), 0)) {
			return -1;
		}
	}

#ifdef _WIN64
	return __int64::Parse(reMoveSpaces(input_temp), System::Globalization::NumberStyles::HexNumber);
#else
	return __int32::Parse(reMoveSpaces(input_temp), System::Globalization::NumberStyles::HexNumber);
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
	return false;
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

int Str2int(String^ input) {   /// we need it just in case we need an int just
	int result;
	if (int::TryParse(input, result)) {
		return result;
	}
	else {
		_plugin_logprintf("can't get int from argument");
		return -1;
	}

}

duint Str2duint(String^ input_) {
#ifdef _WIN64
	duint result;
	if (duint::TryParse(input_, result)) {
		return result;
	}
	else {
		_plugin_logprintf("can't get int from argument");
		return -1;
	}
#else
	int result;
	if (int::TryParse(input_, result)) {
		return result;
	}
	else {
		_plugin_logprintf("can't get int from argument");
		return -1;
	}
#endif // _WIN64

	
}

String^ str2Asci(String^ input) {
	String^ temp;
	if (input->Length < 2)
		return "NULL/ ";
	for (int i = 0; i < input->Length; i += 2)
	{
		if ((input->Substring(i, 2) == "90") || (input->Substring(i, 2) == "00")) {
			temp = temp + ".";
		}
		else {
			int value = Convert::ToInt32(input->Substring(i, 2), 16);
			temp = temp + Char::ConvertFromUtf32(value);
		}
	}
	return temp;
}


String^ ReplaceAtIndex(String^  OriginalString, String^ oldValue, String^ newValue) {
	String^ temp = "";
	if (OriginalString->IndexOf(oldValue) >= 0) {
		int indexBegin = OriginalString->IndexOf(oldValue);
		int length_ = oldValue->Length;

		temp = OriginalString->Substring(0, indexBegin) + newValue;
		String^ x = OriginalString->Substring(indexBegin + length_, OriginalString->Length - (oldValue->Length + indexBegin));
		temp = temp + x;
	}
	return temp;
}

String^ AddZero2Addr(String^ input) {
	if (input->Trim()->StartsWith("0x")) {
		input = input->Substring(2, input->Length - 2);
	}
#ifdef _WIN64
	int len_ = 16;
#else
	int len_ = 8;
#endif
	if (input->Length >= len_)
		return input;
	int rest_ = len_ - input->Length;
	for (int i = 0; i < rest_; i++)
	{
		input = "0" + input;
	}
	//input = "0x" + input;
	return input;
}

bool IsAllSpaces(String^ input_) {
	for (int i = 0; i < input_->Length; i++)
	{
		if (input_->Substring(i, 1) != " ") {
			return false;
		}
	}
	return true;
}

VarType GetVarType(String^ vartype) {
	if (vartype == "str") {
		return VarType::str;
	}
	if (vartype == "int") {
		return VarType::int_;
	}
	if (vartype == "array") {
		return VarType::array_;
	}
	return VarType::int_;
}

Generic::List<String^>^ GetClipBoard() {
	//HANDLE clip;
	if (!OpenClipboard(NULL))
		Script::Gui::Message("Can't open clipboard");
	char* clip =(char*) GetClipboardData(CF_TEXT);
	CloseClipboard();
	String^ text = CharArr2Str(clip);
	String^ tem;
	Generic::List<String^>^ temp = gcnew Generic::List<String^>;

	for (int i = 0; i < text->Length; i++)
	{
		int dd = Microsoft::VisualBasic::Strings::Asc(text->Substring(i, 1));
		if (( Microsoft::VisualBasic::Strings::Asc(text->Substring(i,1)) != 10) && (Microsoft::VisualBasic::Strings::Asc(text->Substring(i, 1)) != 13)) { //10 is new line char
			tem += text->Substring(i, 1);
		}
		else
		{
			if (Microsoft::VisualBasic::Strings::Asc(text->Substring(i, 1)) != 13) { // just CR carriage return
				if (tem->Trim() != "") {
					temp->Add(tem);
					tem = "";
				}				
			}			
		}
		if (i == text->Length - 1) {
			if (tem->Trim() != "") {
				temp->Add(tem);
				tem = "";
			}
		}
	}	
	return temp;
}

void SetClipBoard(String^ input) {
	const char* output = Str2ConstChar(input);
	const size_t len = strlen(output) + 1;
	HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
	memcpy(GlobalLock(hMem), output, len);
	GlobalUnlock(hMem);
	OpenClipboard(0);
	EmptyClipboard();
	SetClipboardData(CF_TEXT, hMem);
	CloseClipboard();
}