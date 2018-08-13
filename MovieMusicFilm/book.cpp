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
#include <cmath>
#include <iomanip>

#include "book.h"

namespace common{

	using namespace std;

	book::book(string filename){
		ifstream myfile;
		string line;
		int counter = 0,sayi = 0;
		// reading file for how many line have file
		myfile.open(filename.c_str());
		if(myfile.is_open()){
			while(!myfile.eof()){
				getline(myfile,line);
				counter++;
			}
	    myfile.close();
		}else{
			cerr << "error opening!!1" << endl;
			exit(1);
		}
		//after the learn size of line resize the variable
		for(int f = 0 ; f < counter-1 ; f++){
			title.resize(counter-1);
			authors.resize(counter-1);
			year.resize(counter-1);
			tags.resize(counter-1);
		}
		//and again open the file and reading all each line and dividing
		myfile.open(filename.c_str());
		getline(myfile,line);
		if(myfile.is_open()){
			while(!myfile.eof()){
				getline(myfile,line);
				full.push_back(line);
				divide(line,sayi);
				sayi++;
			}
	    myfile.close();
		}else{
			cerr << "error opening!!1" << endl;
			exit(1);
		}
		//in sorting some space is not good so eraseing space in variables only head of the string
		for(int i = 0 ; i < title.size() ; i++){
			while(title[i][0] == ' ' || title[i][0] == '	'){
				title[i].erase(title[i].begin() + 0);
			}
		}
		//in sorting some space is not good so eraseing space in variables only head of the string
		for(int i = 0 ; i < authors.size() ; i++){
			while(authors[i][0] == ' ' || authors[i][0] == '	'){
				authors[i].erase(authors[i].begin() + 0);
			}
		}
		//in sorting some space is not good so eraseing space in variables only head of the string
		for(int i = 0 ; i < year.size() ; i++){
			while(year[i][0] == ' ' || year[i][0] == '	'){
				year[i].erase(year[i].begin() + 0);
			}
		}
		//in sorting some space is not good so eraseing space in variables only head of the string
		for(int i = 0 ; i < tags.size() ; i++){
			while(tags[i][0] == ' ' || tags[i][0] == '	'){
				tags[i].erase(tags[i].begin() + 0);
			}
		}
	}
	//in this funciton divide all line and assign string to class varibles vector
	void book::divide(string line,int sayi){
		char *token;
		string temp;
		char *samet = new char[line.length()];
		int j = 0,num = 2, counter = 0;
		int i = 0;
		strcpy(samet,line.c_str());

		for(i ; i < line.length(); i++){
			if(line[i] == '"'){
				j = i+1;
				for( j ; j < line.length(); j++){
					if(line[j] == '"'){
						if(j == i+1){//bburada iki tane tirnagin yan yana geldigini anliyorum yani icleri bos
							temp.append(" ");
						}
						break;
					}else{
						temp.push_back(samet[j]);
					}
				}
				i = j+1;
				number.push_back(0);
				//if counter == 0 it means title
				if(counter == 0){
					title[sayi] = temp;
					counter++;
				//if counter == 0 it means authors
				}else if(counter == 1){
					authors[sayi] = temp;
					counter++;
				//if counter == 0 it means year
				}else if(counter == 2){
					year[sayi] = temp;
					counter++;
				//if counter == 0 it means tags
				}else if(counter == 3){
					tags[sayi] = temp;
					counter++;
				}
				temp.clear();
			}
		}
	}

	int book::search(string vocab,string field){
		int i = 0;
		if(strcmp(field.c_str(),"title") == 0){
			//this iterator starting from begin
			vector<string>::iterator p = title.begin();
			for(p ; p != title.end(); p++ ){
				//eger findsearch fonksiyonu bir donduryse yani arana kelimeyi bulduysa ve kelimenin bulundugu cumle missing field degilse bulundugunu satiri donduruyorum
				if(findSearch(vocab,title[i]) == 1 && number[i] != 2) {
					return i;
				}
				i++;
			}
		}else if(strcmp(field.c_str(),"authors") == 0){
			vector<string>::iterator p = authors.begin();
			for(p ; p != authors.end(); p++ ){
				//eger findsearch fonksiyonu bir donduryse yani arana kelimeyi bulduysa ve kelimenin bulundugu cumle missing field degilse bulundugunu satiri donduruyorum
				if(findSearch(vocab,authors[i]) == 1 && number[i] != 2){
					return i;
				}
				i++;
			}
		}else if(strcmp(field.c_str(),"year") == 0){
			vector<string>::iterator p = year.begin();
			for(p ; p != year.end(); p++ ){
				//eger findsearch fonksiyonu bir donduryse yani arana kelimeyi bulduysa ve kelimenin bulundugu cumle missing field degilse bulundugunu satiri donduruyorum
				if(findSearch(vocab,year[i]) == 1 && number[i] != 2){
					return i;
				}
				i++;
			}
		}else if(strcmp(field.c_str(),"tags") == 0){
			vector<string>::iterator p = tags.begin();
			for(p ; p != tags.end(); p++ ){
				//eger findsearch fonksiyonu bir donduryse yani arana kelimeyi bulduysa ve kelimenin bulundugu cumle missing field degilse bulundugunu satiri donduruyorum
				if(findSearch(vocab,tags[i]) == 1 && number[i] != 2){
					return i;
				}
				i++;
			}
		}
		return -1;
	}
	//find the given vocab in given sentence
	int book::findSearch(string vocab,string temp){
		string gecici;
		gecici.resize(vocab.length());

		for(int i = 0 ; i < temp.length(); i++){
			for(int j = 0 ; j < vocab.length(); j++){
				gecici[j] = temp[i+j];
			}
			
			if(strcmp(gecici.c_str(),vocab.c_str()) == 0)
				return 1;
		}
		return 0;		
	}
	//like a main function
	void book::operation(){
		ofstream myfile;
		ifstream file;
		string gecici;
		int counter = 0;

		myfile.open("output.txt");
		if(myfile.is_open()){
			myfile << "Catalog Read: book" << endl;
		}
		//number vectoru tuttum burada belirledigin sayilar ile duplicate veya missing field olup olmadigin anliyorum
		for(int i = 0 ; i < full.size() ; i++){
			for(int j = i+1 ; j < full.size(); j++){
				if(title[i] == title[j])
					number[j] = 1;
			}
		}
		//using excepiton in here
		for(int i = 0; i < full.size(); i++){
			try{
				for(i ; i < full.size(); i++){
					counter = 0;
					for(int j = 0; j < full[i].length(); j++){
						//her "" isaretinde sayi sayiyorum
						if(full[i][j] == '"'){
							counter++;
						}
					}
					//eger bu sayilar 8 den az ise demekki bir veya daha fazla field eksik demektir
					if(counter != 8){
						number[i] = 2;
						throw full[i];
					}
				}
			}
			//ve firlattigim excepitonu burada yakaliyorum
			catch(string e){
				myfile << "Exception: missing field" << endl << e << endl;
			}
		}
		//duplicate entry icin excepiton firlatiyorum
		for(int i = 0 ; i < full.size() ; i++){
			try{
				if(number[i] == 1)
					throw full[i];
				
			}
			catch(string f){
				myfile << "Exception: dublicate entry" << endl << f << endl;
			}
		}
		//dosyadaki satir sayisini bulmak icin command.txt tekrar acip okuyorum
		file.open("command.txt");
		if(file.is_open()){
			int counter = 0;
			while(!file.eof()){
				getline(file,gecici);
				counter++;
			}
			myfile << counter << " unique entries" << endl;
		}
		//diger komutlar icin dosyayi tekrar okuyorum
		file.close();
		file.open("command.txt");
		if(file.is_open()){
			string tempe;
			while(!file.eof()){
				getline(file,gecici);
				tempe = gecici;
				//dividecommand ile search komutumu yoksa sort komutumu oldugunu anliyorum
				if(divideCommand(gecici) == 1){
					int num = 2,num1 = 0;
					char arr[100];
					//kelimeleri bolerek aranan kelimeyi hangi fieldde aranmaai gerektigini buluyorum
					char *token = strtok(&gecici[0],"\"");
					while(token != NULL){
						if(num %2 == 1 && num1 == 0){
							strcpy(arr,token);
							num1++;
						}else if(num %2 == 1 && num1 == 1){
								int i = search(arr,token);
								if(i >= 0 && i < 5){
									myfile << tempe << endl;
									myfile << full[i] << endl;
								}else{
									myfile << "Exception : command is wrong" << endl;
									myfile << tempe << endl;
								}
						}
						num++;
						token = strtok(NULL,"\"");
					}
				}else{
					//burada sort islemini yapiyorum
					string titleee;
					for(int i = 0; i < gecici.length() ; i++){
						if(gecici[i] == '"'){
							for(int j = i+1 ; j < gecici.length()-1; j++){
								titleee.push_back(gecici[j]);
							}
							break;
						}
					}
					//titleee hangi fieldi sort etmem gerektigini tutuyor
					vector<int> sira ;
					if(titleee == "title"){
						sira = sort(title,titleee);
					}else if(titleee == "authors"){
						sira = sort(authors,titleee);
					}else if(titleee == "year"){
						sira = sort(year,titleee);
					}else if(titleee == "tags"){
						sira = sort(tags,titleee);
					}else{
						myfile << "Exception : command is wrong" << endl;
					}
					//sort fonksiyonu bana sort isleminden sonraki siralamayi tutan bir int vector donduruyor ve ona gore dosyaya yazdiriyorum
					myfile << "Sort \"" << titleee <<"\"" << endl;
					for(int i = 0 ; i < sira.size() ; i++){
						if(number[sira[i]] != 2){
							myfile << full[sira[i]] << endl;
						}
					}
				}
			}
		}
	}
	vector<int> book::sort(vector<string> name,string field){
		
		vector<int> temp;
		vector<string> hold;
		string flag;
		int gecici,counter = 0;
		//sorta missing field olanları ve dublicate olanları katmayacagimiz icin eleme yapiyorum
		for(int i = 0 ; i < name.size()-counter; i++){
			if( number[i] != 2 && number[i] != 1){
				hold.push_back(name[i]);
				temp.push_back(i);
			}
		}			
		//eledikelrimi hold vectorunde tutuorum
		//year fieldi sort etmek diger fieldlara gore biraz daha farkli oldugu icin ayri ayri islemler yapiyorum
		if(field == "year"){
			for(int i = 0 ; i < hold.size()-1 ; i++){
				for(int j = i+1 ; j < hold.size() ; j++){
					if(atoi(hold[i].c_str()) > atoi(hold[j].c_str())){
						gecici = temp[i];
						flag = hold[i];
						temp[i] = temp[j];
						hold[i] = hold[j];
						temp[j] = gecici;
						hold[j] = flag;
					}
				}
			}
		}else{
			//teker teker butun kelimelerin birbirine olan alfebetik sirasi kontrol ediliyor ve ona gore bastan diziliyor
			for(int i = 1 ; i < hold.size() ; i++){
				for(int j = 1 ; j < hold.size() ; j++){
					if(strcmp(hold[j-1].c_str(),hold[j].c_str()) > 0){
						gecici = temp[j-1];
						flag = hold[j-1];
						temp[j-1] = temp[j];
						hold[j-1] = hold[j];
						temp[j] = gecici;
						hold[j] = flag;
					}
				}
			}
		}
		return temp;
	}
	//komutun search mu sort mu oldugu anlasiliyor
	int book::divideCommand(string line){
		char *token;
		token = strtok(&line[0]," ");
		while(token != NULL){
			if(strcmp(token,"search") == 0)
				return 1;
			token = strtok(NULL," ");
		}
		return 2;
	}
}