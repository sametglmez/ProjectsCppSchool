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

#include "music.h"

namespace common{

	using namespace std;

	music::music(string filename){
		ifstream myfile;
		string line;
		int counter = 0,sayi = 0;

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
		for(int f = 0 ; f < counter-1 ; f++){
			title.resize(counter-1);
			artist.resize(counter-1);
			year.resize(counter-1);
			genre.resize(counter-1);
		}

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
		for(int i = 0 ; i < title.size() ; i++){
			while(title[i][0] == ' ' || title[i][0] == '	'){
				title[i].erase(title[i].begin() + 0);
			}
		}
		for(int i = 0 ; i < artist.size() ; i++){
			while(artist[i][0] == ' ' || artist[i][0] == '	'){
				artist[i].erase(artist[i].begin() + 0);
			}
		}
		for(int i = 0 ; i < year.size() ; i++){
			while(year[i][0] == ' ' || year[i][0] == '	'){
				year[i].erase(year[i].begin() + 0);
			}
		}
		for(int i = 0 ; i < genre.size() ; i++){
			while(genre[i][0] == ' ' || genre[i][0] == '	'){
				genre[i].erase(genre[i].begin() + 0);
			}
		}
	}
	void music::divide(string line,int sayi){
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
						if(j == i+1){
							temp.append(" ");
						}
						break;
					}else{
						temp.push_back(samet[j]);
					}
				}
				i = j+1;
				number.push_back(0);
				if(counter == 0){
					title[sayi] = temp;
					counter++;
				}else if(counter == 1){
					artist[sayi] = temp;
					counter++;
				}else if(counter == 2){
					year[sayi] = temp;
					counter++;
				}else if(counter == 3){
					genre[sayi] = temp;
					counter++;
				}
				temp.clear();
			}
		}
	}
	int music::search(string vocab,string field){
		int i = 0;
		if(strcmp(field.c_str(),"title") == 0){
			vector<string>::iterator p = title.begin();
			for(p ; p != title.end(); p++ ){
				if(findSearch(vocab,title[i]) == 1)
					return i;
				i++;
			}
		}else if(strcmp(field.c_str(),"artists") == 0){
			vector<string>::iterator p = artist.begin();
			for(p ; p != artist.end(); p++ ){
				if(findSearch(vocab,artist[i]) == 1)
					return i;
				i++;
			}
		}else if(strcmp(field.c_str(),"year") == 0){
			vector<string>::iterator p = year.begin();
			for(p ; p != year.end(); p++ ){
				if(findSearch(vocab,year[i]) == 1)
					return i;
				i++;
			}
		}else if(strcmp(field.c_str(),"genre") == 0){
			vector<string>::iterator p = genre.begin();
			for(p ; p != genre.end(); p++ ){
				if(findSearch(vocab,genre[i]) == 1)
					return i;
				i++;
			}
		}
		return -1;
	}
	int music::findSearch(string vocab,string temp){
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
	void music::operation(){
		ofstream myfile;
		ifstream file;
		string gecici;
		int counter = 0;

		myfile.open("output.txt");
		if(myfile.is_open()){
			myfile << "Catalog Read: book" << endl;
		}
		for(int i = 0 ; i < full.size() ; i++){
			for(int j = i+1 ; j < full.size(); j++){
				if(title[i] == title[j])
					number[j] = 1;
			}
		}
		for(int i = 0; i < full.size(); i++){
			try{
				for(i ; i < full.size(); i++){
					counter = 0;
					for(int j = 0; j < full[i].length(); j++){
						if(full[i][j] == '"'){
							counter++;
						}
					}
					if(counter != 8){
						number[i] = 2;
						throw full[i];
					}
				}
			}
			catch(string e){
				myfile << "Exception: missing field" << endl << e << endl;
			}
		}
		for(int i = 0 ; i < full.size() ; i++){
			try{
				if(number[i] == 1)
					throw full[i];
				
			}
			catch(string f){
				myfile << "Exception: dublicate entry" << endl << f << endl;
			}
		}
		file.open("command.txt");
		if(file.is_open()){
			int counter = 0;
			while(!file.eof()){
				getline(file,gecici);
				counter++;
			}
			myfile << counter << " unique entries" << endl;
		}
		file.close();
		file.open("command.txt");
		if(file.is_open()){
			string tempe;
			while(!file.eof()){
				getline(file,gecici);
				tempe = gecici;
				if(divideCommand(gecici) == 1){
					int num = 2,num1 = 0;
					char arr[100];
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
					string titleee;
					for(int i = 0; i < gecici.length() ; i++){
						if(gecici[i] == '"'){
							for(int j = i+1 ; j < gecici.length()-1; j++){
								titleee.push_back(gecici[j]);
							}
							break;
						}
					}
					vector<int> sira ;
					if(titleee == "title"){
						sira = sort(title,titleee);
					}else if(titleee == "artist"){
						sira = sort(artist,titleee);
					}else if(titleee == "year"){
						sira = sort(year,titleee);
					}else if(titleee == "genre"){
						sira = sort(genre,titleee);
					}else{
						myfile << "Exception : command is wrong" << endl;
					}
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
	vector<int> music::sort(vector<string> name,string field){
		
		vector<int> temp;
		vector<string> hold;
		string flag;
		int gecici,counter = 0;
		
		for(int i = 0 ; i < name.size()-counter; i++){
			if(number[i] != 2 && number[i] != 1){
				hold.push_back(name[i]);
				temp.push_back(i);
			}
		}
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
	int music::divideCommand(string line){
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
