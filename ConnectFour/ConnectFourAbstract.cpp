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


namespace ConnectFourMode{
	using std::ostream;
	using std::istream;
	using std::string;
	using std::cout;
	using std::vector;
	using std::cin;
	using std::endl;
	using std::cerr;
	using std::max;
	using std::streamsize;
	using std::numeric_limits;
	using std::ofstream;
	using std::ifstream;

	ConnectFourAbstract::ConnectFourAbstract(){//no parameter constructor 
	setWidth(5);
	setHeight(5);
	}

	int ConnectFourAbstract::getWidth()const{return width;}// getter of width
	int ConnectFourAbstract::getHeight()const{return height;}// getter of height
	Cell ** ConnectFourAbstract::getBoard(){return gameBoard;}
	ConnectFourAbstract::ConnectFourAbstract(int width,int height){//two parameter constructor
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
	ConnectFourAbstract::ConnectFourAbstract(const ConnectFourAbstract& cell1){
		gameBoard = new Cell*[getHeight()];
			for(int i =0;i<getHeight();i++){
				gameBoard[i] = new Cell[getWidth()];
			}
		
		setWidth(cell1.getWidth());
		setHeight(cell1.getHeight());
		
		for(int i=0;i<cell1.getHeight();i++){
			for(int j=0;j<cell1.getWidth();j++){
				gameBoard[i][j].setType(cell1.gameBoard[i][j].getType()); 
			}
		}
	}
	ConnectFourAbstract::~ConnectFourAbstract(){//delete the dynamic array from heap
		for(int i=0;i<getWidth();i++){
			delete [] gameBoard[i];
		}
		delete[] gameBoard;
	}
	void ConnectFourAbstract::setWidth(const int width){
		this->width = width;
	}
	void ConnectFourAbstract::setHeight(const int height){
		this->height = height;
	}

	//initializing for no parameter constructor or two parameter constructor
	void ConnectFourAbstract::initialize(){
		gameBoard = new Cell*[getHeight()];
		for(int i =0;i<getHeight();i++){
			gameBoard[i] = new Cell[getWidth()];
		}

		for(int i=0; i<getHeight();i++){
			for(int j=0;j<getWidth();j++){
				gameBoard[i][j].setType(empty);
			}
		}
	}
	//initializing for filenmae constructor

	//printh the current board
	void ConnectFourAbstract::print(){
		int i,k;
		char f,a;
		
		for(int k=0;k<getWidth();++k){

			a = 'a' + k;
			cout << a << " " ;
		}
		cout<< endl;
		
		for (int i = 0; i < getHeight(); i++){
	   
		    for (int j = 0; j < getWidth(); j++){
		    	cout << gameBoard[i][j].getType();
		    	cout << " ";
		    }
		   cout << endl;
		}
		
	}
	//play function for single game
	int ConnectFourAbstract::playGame(){
		int size,i;
		int turn=0;
		string save;
		string load;
		char temp;

		cout << "player|computer :" ;
		do{
			while(!(cin >> temp)){
				
				cout << "PLEASE ENTER p OR c :";
			}
			temp = tolower(temp);
			if(temp != 'p' && temp != 'c'){
				cout << "PLEASE ENTER p OR c :";
			}
		}while(temp != 'p' && temp != 'c');

		print();
		if(temp == 'p'){
			while(1){
				//İF PLAYER WANTS TO USER TO USER USİNG WHİS LOOP
				if((playUserOne(save,load) == 1) ){
					return 1;//if return 1 finisihing the game
					break;
				}
				if((playUserTwo(save,load) == 1)){
					return 1;
					break;
				}
				//control for board is full or not
				turn =turn +2;  
				if(turn == getWidth() * getHeight()){
					cout << "BOARD İS FULL DRAW" << endl;
					break;
				}			
			}

		}else{
			while(1){

				//İF PLAYER WANTS TO USER TO COMPUTER USİNG THİS LOOP
				if((playUserOne(save,load) == 1) || (playComputer()== 1)){
					return 1;
					break;
				}
				turn =turn +2;  
				if(turn ==getWidth() * getHeight()){
					cout << "BOARD İS FULL DRAW"<< endl;
					break;
				}			
			}
		}
		cout << " THE END" << endl;	
	}
	//taking input for sibgle game
	int ConnectFourAbstract::input(const int size, string& save,string& load,int& choice){	
		char attack,letter;
		int k,i;
		char temp[80];
		char *fileName;
		string opcode;
		
		cout << "PLEASE ENTER YOUR CHOİCE : ";
		cout << endl;
		//STRİNGİ PARCALİYARAK KOMUT ALİYORUM
		cin.get();
		cin.get(temp,80);
		if(strlen(temp) == 0){
			exit(1);
		}
		choice = 0;
		if((strcmp(temp,"undo") == 0) || strcmp(temp,"UNDO") == 0){
			choice = 3;
			letter = 'a';
		}else{

			fileName = std::strtok(temp," ");
		    if (fileName != NULL) {
		        fileName = strtok(NULL," ");
		    }
			//doing it fot puttin \0 last place to array
			for ( i = 0; i < temp[i]!='\0'; ++i)
			{
				
			}
			// user enter string and ı am seperate string for load or save
			temp[i] ='\0';
			string opcode = temp;
			attack = opcode[0];
			if(opcode.length() != 1){
				for ( i = 0; i < fileName[i]!='\0'; ++i)
				{

				}
				fileName[i] ='\0';
			}
			while(1){
				if(choice == 3)
					break;
				//İSALPHA CONTROL İNPUT FOR LETTER OR OTHERS
				if(opcode.length() == 1 && (isalpha(attack)) && (attack >= 'a' && attack < 'a'+getWidth()) || (attack >= 'A' && attack < 'A'+getWidth() )){
					break;
				}else if(opcode == "load" || opcode == "LOAD"){
					load = fileName;
					choice = 5;
					break;
				}else if(opcode == "save" || opcode == "SAVE"){
					save = fileName;
					choice = 6;
					break;
				}else{
					cout << "WRONG CHOİCE! PLEASE AGAİN ENTER YOUR CHOİCE : " ;
					cin.get();
					cin.get(temp,80);
					fileName = std::strtok(temp, " ");
				    if (fileName != NULL) {
				        fileName = strtok(NULL, " ");
				    }
					attack = temp[0];
				}
			}
		}
		//İF USER ENTER A CAPİTAL LETTER OR SMALL LETTER .İTS DOİNG USEFUL THEM
			letter = tolower(attack);
			 k = letter  - 'a';
			 return k;
		}
	int ConnectFourAbstract::playUserOne(string& save1,string& load1){
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
	int ConnectFourAbstract::playUserTwo(string& save3,string& load3){
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
	// control function of all game
	int ConnectFourAbstract::control(int playerNo,int loop){
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
					if(downControl(x,y,playerNo,player,loop) == 1 ||
						sideContro(x,y,playerNo,player,loop) ==1 ||
						sagcapraz(x,y,playerNo,player,loop) == 1  ||
						solcapraz(x,y,playerNo,player,loop) ==1 ){ 
						
						return 1;
					}
				}
			}	
		}
		return 0;
	}
	//DOWN CONTROL FOR FİND THE WİNNER
	int ConnectFourAbstract::downControl(int x,int y,int playerNo,char player,int loop){
		int score = 0;
		for(int i=0;i<loop;++i){
			if(x-i >= 0){//Boardun disina cikmamasini kontrol ediyor
				if(gameBoard[x-i][y].getType() == player){
					score++;
				}
			}
		}
		if(score == loop){
			return 1;
		
		}else{
			score = 0;
			return 0;
		}
	}
	//SİDE CONTROL FOR FİND THE WİNNER
	int ConnectFourAbstract::sideContro(int x,int y,int playerNo,char player,int loop){

		int score = 0;
		for(int i=0;i<loop;++i){
			if(y+i < getWidth()){
				if(gameBoard[x][y+i].getType() == player)
					score++;
			}
		}
			if(score == loop){
				return 1;
			}else{
				score = 0;
				return 0;
			}
	}
	//DİOGNAL CONTROL FOR FİND THE WİNNER
	int ConnectFourAbstract::sagcapraz(int x,int y,int playerNo,char player,int loop){
		int score = 0;
		for(int i=0;i<loop;++i){
			if((x-i >= 0) && (y-i >=0 )){
				if(gameBoard[x-i][y-i].getType() == player)
					score++;

			}
		}
			if(score == loop){
				return 1;
			}else{
				score = 0;
				return 0;
			}
	}
	//DİOGNAL CONTROL FOR FİND THE WİNNER
	int ConnectFourAbstract::solcapraz(int x,int y,int playerNo,char player,int loop){
		int score = 0;
			for(int i=0;i<loop;++i){
				
				if((x-i >= 0) && (y+i < getWidth() )){
					if(gameBoard[x-i][y+i].getType() == player)
						score++;
				}
			}
			if(score == loop){
				return 1;
			}else{
				score = 0;
				return 0;
			}
	}
	// here play for computer
	int ConnectFourAbstract::playComputer(){
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
	// find a column for play computer
	int ConnectFourAbstract::findColumn(char ch){
		int harf;
		int temp;
		int live=0;
		temp = getHeight();
		harf = ch - 'a';
		while(gameBoard[temp-1][harf].getType() != empty){
			temp--;
		}
		return temp-1;
	}
	void ConnectFourAbstract::SaveGame(string& save4){
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
	void ConnectFourAbstract::LoadGame(string& load4){
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
