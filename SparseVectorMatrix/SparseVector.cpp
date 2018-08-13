//----------------IMPLEMANTIN OF SPARSEVECTOR CLASS---------------
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
#include "SparseVector.h"



using namespace std;
// DEFAULT CONSTRUCTOR
SparseVector::SparseVector(){

}
//one parameter contructor 
SparseVector::SparseVector(string filename){
	int index1,counter = 2;
	double data1;
	char space;
  char* str,*deneme;
  string line;

	 ifstream myfile;
    myfile.open(filename.c_str());
    if(myfile.is_open()){//opening file
    	while(!myfile.eof()){//until end of the file
        getline(myfile,line);//satir satir okuyorum her satiri bolerek index ve dataya atiyorum
        deneme = new char[line.length()];//string okuduğum icin strtok fonksiyonunda kullanilmiyor o yuzden char pointera atiyorum
        strcpy(deneme,line.c_str());
        str = strtok(deneme,": ");// boslum ve : gorene kadar boluyorum ve bir counter tutarak moduna gore indexe veya dataya atama yapiyorum
        while(str != NULL){
          if(counter %2 == 0){
            index.push_back(atoi(str));
            counter++;
          }else if(counter %2 == 1){
            data.push_back(atof(str));
            counter++;
          }
          str = strtok(NULL,": ");
        }
    	}
        myfile.close();
    }else{
      cerr << "Error opening" << endl;// eger dosya acilmazsa veya yoksa hata bastiriyor
      exit(1);
  	}
}
const SparseVector SparseVector::operator +(const SparseVector& otherObject)const{
  int i=0,j=0,size;
  SparseVector temp;// dondureegim class

  for(;;){
    if(i == index.size() && j == otherObject.index.size()){//eger indexlerin ve dataların uzunlugu birbirine esit biterse atama islemnin bitiryor
      break;
    }
    if(i == index.size()){//eger soldaki classin indexleri erken biter diger classin kalanlari sonuca direk ekleniyor
      int tempe = j;
      for(int x=0; x < otherObject.index.size() - tempe ; x++){
        temp.index.push_back(otherObject.index[j]);
        temp.data.push_back(otherObject.data[j]+0);
        j++;
      }
      break;
    }else if(j == otherObject.index.size()){//eger sagdaki classin indexleri erken biter diger classin kalanlari sonuca direk ekleniyor
      int tempe = i;
      for(int x=0; x < index.size() - tempe; x++){
        temp.index.push_back(index[i]);
        temp.data.push_back(data[i]+0);
        i++;
      }
      break;
    }
    if(index[i] == otherObject.index[j]){//eger soldaki classın sayisi sagdaki classın indexine esitse birbirleri ile toplanarak sonuca ekleniyor
      temp.index.push_back(index[i]);
      temp.data.push_back(data[i] + otherObject.data[j]);
      i++;
      j++;
    }else if(index[i] < otherObject.index[j]){//eger classların indxeleri biribirnden farkliysa toplama yapilmaz direk sonuca yazilir 
      temp.index.push_back(index[i]);
      temp.data.push_back(data[i] + 0);
      i++;
    }else if(index[i] > otherObject.index[j]){
      temp.index.push_back(otherObject.index[j]);
      temp.data.push_back(otherObject.data[j]+0);
      j++;
    }
  }
  return temp;
}
const SparseVector SparseVector::operator -(const SparseVector& otherObject)const{
  //toplama islemindeki hersey sadece cikartma yapilarak yapiliyor
  int i=0,j=0,size;
  SparseVector temp;

  for(;;){
    if(i == index.size() && j == otherObject.index.size()){
      break;
    }
    if(i == index.size()){
      int tempe = j;
      for(int x=0; x < otherObject.index.size() - tempe ; x++){
        temp.index.push_back(otherObject.index[j]);
        temp.data.push_back(otherObject.data[j]-0);
        j++;
      }
      break;
    }else if(j == otherObject.index.size()){
      int tempe = i;
      for(int x=0; x < index.size() - tempe; x++){
        temp.index.push_back(index[i]);
        temp.data.push_back(data[i]-0);
        i++;
      }
      break;
    }
    if(index[i] == otherObject.index[j]){
      temp.index.push_back(index[i]);
      temp.data.push_back(data[i] - otherObject.data[j]);
      i++;
      j++;
    }else if(index[i] < otherObject.index[j]){
      temp.index.push_back(index[i]);
      temp.data.push_back(data[i] - 0);
      i++;
    }else if(index[i] > otherObject.index[j]){
      temp.index.push_back(otherObject.index[j]);
      temp.data.push_back(0 - otherObject.data[j]);
      j++;
    }
  }
  return temp;
}
const SparseVector SparseVector::operator-()const{
  SparseVector temp;

  for(int i = 0; i < index.size();i++){//butun degeleri giderek - ile carpiyorum
    temp.index.push_back(index[i]);
    temp.data.push_back(-data[i]);
  }
  return temp;
}
SparseVector& SparseVector::operator = (const SparseVector& otherObject){

  if(index.size() != otherObject.index.size()){//iki classin boyutlarinin kontrol ediyorum eger esit degilse ona gore tekrardan boyutlandiriyorum
    index.resize(otherObject.index.size());
    data.resize(otherObject.data.size());
  }
  for(int i=0; i < index.size();i++){
    index[i] = otherObject.index[i];
    data[i] = otherObject.data[i];
  }
  return *this;
}
ostream& operator <<(ostream& outputStream,const SparseVector& otherObject){
  for(int i=0; i < otherObject.index.size();i++){
    outputStream << otherObject.index[i] << ":" << otherObject.data[i] << " " ;
  }
}
double dot(const SparseVector& leftSide,const SparseVector& rightside){
  //toplama isleminin aynisini burada carpma islewmi uygulayarak yapiliyor
  int i=0,j=0,size;
  double temp=0;

  for(;;){
    if(i == leftSide.index.size()){
      int tempe = j;
      for(int x=0; x < rightside.index.size() - tempe ; x++){
        temp += rightside.data[j]*0;
        j++;
      }
      break;
    }else if(j == rightside.index.size()){
      int tempe = i;
      for(int x=0; x < leftSide.index.size() - tempe; x++){
        temp += leftSide.data[i]*0;
        i++;
      }
      break;
    }
    if(leftSide.index[i] == rightside.index[j]){
      temp += leftSide.data[i] * rightside.data[j];
      i++;
      j++;
    }else if(leftSide.index[i] < rightside.index[j]){
      temp += leftSide.data[i] * 0;
      i++;
    }else if(leftSide.index[i] > rightside.index[j]){
      temp += rightside.data[j]*0;
      j++;
    }
  }
  return temp;
}
