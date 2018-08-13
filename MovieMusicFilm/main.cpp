/*SAMET GÜLMEZ 16104411
Hocam book.h ve book.cpp classında commentlerimi 
yazdim diger classlarda ayni ismleri yaptigi icin 
tekrardan commentleri yazmadim
*/

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
#include "music.h"
#include "movie.h"


using namespace std;
using namespace common;

int main(int argc, char const *argv[]){

	ifstream myfile;
	string line;

	//data .txt okuyorum ve ilk kelimesi ile hangi class oldugunu anliyorum
	myfile.open("data.txt");
	if(myfile.is_open()){
		getline(myfile,line);
		//hangi class oldugunu bulduktan sonra ona gore yer ayiriyorum
		if(strcmp(line.c_str(),"music") == 0){
			music *object2 = new music("data.txt");
			object2->operation();
		}	
		if(strcmp(line.c_str(),"book") == 0){
			book *object = new book("data.txt");
			object->operation();
		}
		if(strcmp(line.c_str(),"movie") == 0){
			movie *object1 = new movie("data.txt");
			object1->operation();
		}
    myfile.close();
	}else{
		cerr << "error opening!!1" << endl;
		exit(1);
	}

	

	return 0;
}