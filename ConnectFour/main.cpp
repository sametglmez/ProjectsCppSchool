/*Hocam computer oynarken bekleme suresi fazla olabiliyor*/
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <map>
#include <limits>
#include <typeinfo>
#include <istream>

#include "Cell.h"
#include "ConnectFourAbstract.h"
#include "ConnectFourDiag.h"
#include "ConnectFourPlus.h"
#include "ConnectFourPlusUndo.h"



using namespace std;
using namespace ConnectFourMode;

	

int main(){
	int width,height,choice,control;
	char gameChoice,temp;

	cout << "enter game mode :";

	do{
		while(!(cin >> temp)){
			
			cout << "PLEASE ENTER u OR d Or p:";
		}
		temp = tolower(temp);
		if(temp != 'p' && temp != 'u' && temp != 'd'){
			cout << "PLEASE ENTER u OR d Or p :";
		}
	}while(temp != 'p' && temp != 'u' && temp != 'd');

	cout << "PLEASE ENTER WİDTH : ";
	cin >> width;
	cout << "PLEASE ENTER HEİGHT : ";
	cin >> height;
	
	if(temp == 'p'){
		ConnectFourPlus game6(width,height);//filename okuyan constructor cagiriliyor
		control = game6.playGame();
		if(control == 1){
			exit(1);//game had finish so exit from program
		}
	}else if(temp == 'd'){
		ConnectFourDiag game6(width,height);
		control = game6.playGame();
		if(control == 1){
			exit(1);//game had finish so exit from program
		}
	}else if(temp == 'u'){
		ConnectFourPlusUndo game6(width,height);
		control = game6.playGame();
		if(control == 1){
			exit(1);//game had finish so exit from program
		}
	}
}
