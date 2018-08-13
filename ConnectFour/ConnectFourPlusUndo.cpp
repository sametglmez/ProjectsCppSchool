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
#include "ConnectFourPlus.h"
#include "ConnectFourPlusUndo.h"

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
	ConnectFourPlusUndo::ConnectFourPlusUndo(){
		setWidth(5);
		setHeight(5);
	}
	ConnectFourPlusUndo::ConnectFourPlusUndo(int width,int height){//two parameter constructor
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
	ConnectFourPlusUndo::~ConnectFourPlusUndo(){//delete the dynamic array from heap
		for(int i=0;i<getWidth();i++){
			delete [] gameBoard[i];
		}
		delete[] gameBoard;
	}
	void ConnectFourPlusUndo::undoBack(){
		int num;
		num = Undo.back();
		for(int i=getHeight()-1;i>=0;i--){
			if(gameBoard[i][num].getType() == empty){
				gameBoard[i+1][num].setType(empty);
			}
		}
		Undo.pop_back();
	}
	int ConnectFourPlusUndo::playUserOne(string& save1,string& load1){
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
				if(Undo.size() == 0){
					cout << " Board is Empty " << endl;
					break;
				}else{
					undoBack();
					break;
				}
			}
			while(!(size >= 0)){
				returnValue = input(temp,save1,load1,choice);
				size = getHeight()-1;
			}	
		 	if(gameBoard[size][returnValue].getType() == empty){
				if(size >= 0 &&  size < getHeight() && returnValue >= 0 && returnValue < getWidth()){
					gameBoard[size][returnValue].setType(user1);
					Undo.push_back(returnValue);
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
	int ConnectFourPlusUndo::playUserTwo(string& save3,string& load3){
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
				if(Undo.size() == 0){
					cout << " Board is Empty " << endl;
					break;
				}else{
					undoBack();
					break;
				}
			}
			while(!(size >= 0)){
				returnValue = input(temp,save3,load3,choice);
				size = getHeight()-1;
			}	
		 	if(gameBoard[size][returnValue].getType() == empty){
				if(size >= 0 &&  size < getHeight() && returnValue >= 0 && returnValue < getWidth()){
					gameBoard[size][returnValue].setType(user2);
					Undo.push_back(returnValue);
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
	int ConnectFourPlusUndo::playComputer(){
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
				Undo.push_back(random);
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
	void ConnectFourPlusUndo::SaveGame(string& save4){
	   char letter;
	   int k = 0,num;
	   num = Undo.size();

	   ofstream myfile (save4.c_str());
	 //  myfile << num;
	   if(myfile.is_open()){
	   		for(int i=0;i < num;i++){
	   			myfile << Undo[i];
	   			//Undo.pop_back();
	   		}
	   		myfile << endl;
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
	void ConnectFourPlusUndo::LoadGame(string& load4){
	  	string satir;
		int arr[100],max=0,sira=0;
		int num=0,j=0,i,sizeOfVector;

		sizeOfVector = Undo.size();

		for(int i=0;i<getWidth();i++){
					delete [] gameBoard[i];
				}
				delete[] gameBoard;
		
		ifstream myfile ;

		gameBoard = new Cell*[getHeight()];
		for(int i =0;i<getHeight();i++){
			gameBoard[i] = new Cell[getWidth()];
		}
		myfile.open(load4.c_str());
		for(int i=0;i<sizeOfVector;i++){
			Undo.pop_back();
		}
		
		getline(myfile,satir);
		
		for(int i =0;satir[i] != '\0';i++){
			Undo.push_back(satir[i] -48);
			cout << Undo.back() << endl;
		}
		
		//cout << Undo.size()<<"-------";
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