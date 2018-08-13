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

namespace ConnectFourMode{
	using std::ostream;
	using std::istream;
	using std::string;
	using std::cout;
	using std::cin;
	using std::endl;
	using std::cerr;
	using std::max;
	using std::streamsize;
	using std::numeric_limits;
	using std::ofstream;
	using std::ifstream;

	ConnectFourDiag::ConnectFourDiag(){
		setWidth(5);
		setHeight(5);
	}
	ConnectFourDiag::ConnectFourDiag(int width,int height){//two parameter constructor
		setWidth(width);
		setHeight(height);
		gameBoard = new Cell*[height];
	for(int i =0;i<height;i++){
		gameBoard[i] = new Cell[width];
	}

	for(int i=0; i<height;i++){
		for(int j=0;j<width;j++){
			gameBoard[i][j].setType(empty);
		}
	}
	}
	ConnectFourDiag::~ConnectFourDiag(){//delete the dynamic array from heap
		for(int i=0;i<getWidth();i++){
			delete [] gameBoard[i];
		}
		delete[] gameBoard;
	}
	int ConnectFourDiag::control(int playerNo,int loop){
		int x,y;
		char player;
		int count = 0;


		if(playerNo == 1)
			player = user1;
		else
			player = user2;

		for(int j=0; j < getHeight() ; ++j){
			for(int k = 0 ; k < getWidth(); ++k){
				//YILDIZ OLMAYAN NOKTALARİN KOORDİNATINI KAYDETİP ETRAFLARINI KONTROL EDİYOR
				if(gameBoard[j][k].getType() == player){
					x = j;
					y = k;

					if(sagcapraz(x,y,playerNo,player,loop) == 1  ||
						solcapraz(x,y,playerNo,player,loop) ==1){
						return 1;
					}
					
				}
				
			}	

		}
		return 0;
	}
	int ConnectFourDiag::playUserOne(string& save1,string& load1){
		int choice,i,temp;
		int winner;
		int cont;
		char harf;
		int returnValue;
		int size = getHeight();
		
		//SİZE 1 AZALTİCAGİMİZ İCİN TEMPE ATİYORUZ
		temp = size;
		returnValue = input(temp,save1,load1,choice);
		if(choice == 6){
			do{
				SaveGame(save1);//saving game
				returnValue = input(temp,save1,load1,choice);
			}while(choice == 6);
		}
		if(choice == 5){
			do{
				LoadGame(load1);//loading game
				print();
				returnValue = input(temp,save1,load1,choice);
			}while(choice == 5);
		}		
		size--;
		while(1){
			if(choice == 3){
				break;
			}
			while(!(size >= 0)){
				returnValue = input(temp,save1,load1,choice);
				size = getHeight()-1;
			}	
		 	if(gameBoard[size][returnValue].getType() == empty){
				if(size >= 0 &&  size < getHeight() && returnValue >= 0 && returnValue < getWidth()){
					gameBoard[size][returnValue].setType(user1);
					break;
				}
			}else 
				size--;
		}
		print();
		cont = control(1,4);
		if(cont == 1){
			cout << "X KAZANDI" << endl;
			return 1;
		}else return 0;
	}
	int ConnectFourDiag::playUserTwo(string& save3,string& load3){
		//like player one function
		int choice=0,i,temp;
		int winner;
		int cont;
		char harf;
		int returnValue;
		int size = getHeight();
		//SİZE 1 AZALTİCAGİMİZ İCİN TEMPE ATİYORUZ
		temp = size;
		returnValue = input(temp,save3,load3,choice);
		if(choice == 6){
			do{
				SaveGame(save3);
				returnValue = input(temp,save3,load3,choice);
			}while(choice == 6);
		}		
		if(choice == 5){
			do{
				LoadGame(load3);
				print();
				returnValue = input(temp,save3,load3,choice);
				cout << choice << endl;
			}while(choice == 5);
		}
		size--;
		while(1){
			if(choice == 3){
				break;
			}
			while(!(size >= 0)){
				returnValue = input(temp,save3,load3,choice);
				size = getHeight()-1;
			}	
		 	if(gameBoard[size][returnValue].getType() == empty){
				if(size >= 0 &&  size < getHeight() && returnValue >= 0 && returnValue < getWidth()){
					gameBoard[size][returnValue].setType(user2);
					break;
				}
			}else 
				size--;
		}
		
		print();
		cont = control(2,4);
		if(cont == 1){
			cout << "O KAZANDI" << endl;
			return 1;
		}else return 0;
		
	}
	int ConnectFourDiag::playComputer(){
		char ch;
		int cont;
		int row;
		int column;
		int random;
		bool won = false;
		for(int i=0;i<getWidth();i++){
			ch = 'a' + i ;
			column = ch - 'a';
			if(gameBoard[0][i].getType() == empty){
				row = findColumn(ch);
				gameBoard[row][column].setType(computer);

				if(control(2,4) == 1){
					won = true;
					break;
				}
				gameBoard[row][column].setType(empty);
			}else continue;
		}
		if(!won){
			for(int i=0;i<getWidth();i++){
				ch = 'a' + i ;
				column = ch - 'a';
				if(gameBoard[0][i].getType() == empty){
					row = findColumn(ch);
					gameBoard[row][column].setType(user1);
					if(control(1,4) == 1){
						gameBoard[row][column].setType(computer);
						
						won = true;
						break;
					}
					gameBoard[row][column].setType(empty);
				}else continue;
			}
		}
		while(!won){
			srand(time(NULL));
			random = rand() % getWidth();
			ch = 'a' + random;
			if(gameBoard[0][random].getType() == empty){
				won = true;	
				row = findColumn(ch);
				gameBoard[row][random].setType(computer);
			}
		}
		print();
		cont = control(2,4);
		if(cont == 1){
			cout << "O KAZANDI" << endl;
			return 1;
		}else return 0;
	}
	void ConnectFourDiag::SaveGame(string& save4){
	   char letter;
	   int k = 0;

	   ofstream myfile (save4.c_str());
	   if(myfile.is_open()){
	   //	myfile << getHeight()<< " " << getWidth() << " " << endl;
	   		for(int i = 0; i < getHeight(); i++){    
	            for(int j = 0; j < getWidth(); j++){
	                myfile << gameBoard[i][j].getType() ;
	            }
	            myfile <<endl;
	        }
	        myfile.close();
	    }else{
	     // std::cerr << "Error opening" << endl;
	      cerr << "Error opening" << endl;
	      exit(1);
	  	}
	}
	void ConnectFourDiag::LoadGame(string& load4){
	  	string satir;
		int arr[100],max=0,sira=0;
		int num=0,j=0;
		int i;
		
		for(int i=0;i<getWidth();i++){
					delete [] gameBoard[i];
				}
				delete[] gameBoard;
		
		ifstream myfile ;
		myfile.open(load4.c_str());
		while(!myfile.eof()){
			getline(myfile,satir);
			for(i=0;satir[i] != '\0';i++ ){
			}
			j++;
			arr[sira] = i;
			sira++;
		}
		max=arr[0];
		for(int k=1;k<sira;k++){
			if(max < arr[k]){
				max = arr[k];
			}
		}
		setWidth(max);
		setHeight(sira-1);
		myfile.close();

		gameBoard = new Cell*[getHeight()];

		for(int i =0;i<getHeight();i++){
			gameBoard[i] = new Cell[getWidth()];
		}
		j=0;
		myfile.open(load4.c_str());
		while(!myfile.eof()){
			getline(myfile,satir);
			for(int t=0;satir[t] != '\0';t++ ){
				if((satir[t] == user1) || (satir[t] == user2)){
				}
				gameBoard[j][t].setType(satir[t]);
			}
			j++;
		}
		myfile.close();
	}

}