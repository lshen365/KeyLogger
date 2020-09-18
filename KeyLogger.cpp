// KeyLogger.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <Windows.h>
#include <iostream>
#include <conio.h>
using namespace std;

void findLetterEfficient(){
	string currentSentence = "";
	while (1){
		currentSentence += char(getch());
		if (GetAsyncKeyState(VK_RETURN) & 1) { //Return to Print Line
			cout << currentSentence << endl;
			currentSentence = "";
		}
		if ((GetAsyncKeyState(VK_CONTROL) & 1) && (GetAsyncKeyState(0x48)) & 1){ //Ctrl + H To Exit
			cout<<"Goodbye"<<endl;
			return;
		}
	}

}


int main()

	findLetterEfficient();
	return 0;
}
