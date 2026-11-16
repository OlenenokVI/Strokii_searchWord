#include <iostream>
#include <string>
#include <limits>
#include <io.h>	
#include <fcntl.h>

wchar_t BigLetter(wchar_t c) {
	if (c >= L'a' && c <= L'z'){ 
		return c - 32; 
	}
	if (c >= L'а' && c <= L'я') { 
		return c - 32; 
	}
	if (c == L'ё') { 
		return L'Ё'; 
	}
	return c;
}

wchar_t SmallLetter(wchar_t c) {
	if (c >= L'A' && c <= L'Z') { 
		return c + 32; 
	}
	if (c >= L'А' && c <= L'Я') { 
		return c + 32; 
	}
	if (c == L'Ё') { 
		return L'ё'; 
	}
	return c;
}

std::wstring SmallString(const std::wstring& str) {
	std::wstring result = L"";
	for (std::size_t i = 0; i < str.length(); i++) {
		result += SmallLetter(str[i]);
	}
	return result;
}

bool Punctuation(wchar_t c) {
	return c == L'.' || c == L',' || c == L'!' || c == L'?' || c == L';' || c == L':' ||
		c == L'-' || c == L'(' || c == L')' || c == L'"' ;
}

bool findWord(std::wstring& sentence, std::wstring& searchWord) {
	if (sentence.empty() || searchWord.empty()) {
		return false;
	}

	std::wstring smallerSearchWord = SmallString(searchWord);
	std::wstring currentWord = L"";

	for (std::size_t i = 0; i <= sentence.length(); i++) {
		if (i == sentence.length() || sentence[i] == L' ' || Punctuation(sentence[i])) {

			if (!currentWord.empty()) {
				std::wstring lowerCurrentWord = SmallString(currentWord);
				if (lowerCurrentWord == smallerSearchWord) {
					return true; 
				}
				currentWord = L"";
			}
		}
		else {
			currentWord += sentence[i];
		}
	}

	return false;
}


int main() {
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stdout), _O_U16TEXT);

	std::wstring input;
	std::wcout << L"Введите предложение: ";
	std::getline(std::wcin, input);

	if (input.empty()) {
		std::wcout << L"\nСтрока пуста\n\n";
		return 0;
	}

	std::wstring result = L"";
	bool NewWord = true;

	for (std::size_t i = 0; i < input.length(); i++) {
		wchar_t c = input[i];

		if (c == L' ') {
			result += c;
			NewWord = true;
		}
		else {
			if (NewWord == true) {
				result += BigLetter(c);
				NewWord = false;
			}
			else {
				result += SmallLetter(c);
			}
		}
	}

	if (!result.empty() && result.back() != L'.') {
		result += L'.';
	}

	std::wcout << "\n--------------------------------------------------";
	std::wcout << L"\nИзмененное предложение: " << result << L"\n\n";

	std::wcout << L"\t << 4 >>\n";

	std::wstring sentence;
	std::wstring searchWord;

	std::wcout << L"Введите предложение: ";
	std::getline(std::wcin, sentence);

	std::wcout << L"Введите слово для поиска: ";
	std::getline(std::wcin, searchWord);

	bool result_4_5 = findWord(sentence, searchWord);

	std::wcout << "\n--------------------------------------------------";
	if (result_4_5) {
		std::wcout << L"\nCлово найдено!\n\n ";
	}
	else {
		std::wcout << L"\nCлово не найдено(\n\n";
	}

	return 0;
}