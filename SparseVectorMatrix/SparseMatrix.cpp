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
#include "SparseMatrix.h"
#include <bits/stdc++.h>



using namespace std;

SparseMatrix::SparseMatrix(){

}
SparseMatrix::SparseMatrix(string filename){
	int index1,i=0,counter=0,deger;
	double data1;
	char space;
	string line;

	ifstream myfile;
    myfile.open(filename.c_str());
    //dosyayi ilk olarak bir kere bos okuyorum ve row indexin boyutunu buluyorum boylelikle vectorlerin boyutunuda bulmus oluyorum
    if(myfile.is_open()){
    	while(!myfile.eof()){
    		myfile>>deger ;//satirdaki ilk sayiyi aliyorum ve rowindexe atiyorum
    		row.push_back(deger);
    		counter++;
    		getline(myfile,line);
    	}
    	index.resize(counter);
    	data.resize(counter);
        myfile.close();
    }else{
      cerr << "Error opening" << endl;
      exit(1);
  	}
  	myfile.open(filename.c_str());
    if(myfile.is_open()){
    	while(!myfile.eof()){
    		myfile>>deger ;   
    		getline(myfile,line);//kalan bolumu direk satir olarak okuyor ve onları bolerek index ve datalara atiyorum
            index[i].resize(count(line.begin(),line.end(),':'));
            data[i].resize(count(line.begin(),line.end(),':'));
    		divide(i,line);
    		i++;
    	}
        myfile.close();
    }else{
      cerr << "Error opening" << endl;
      exit(1);
  	}
}
//satirir bolme islemiin bu fonksiyonda yapiyorum
void SparseMatrix::divide(int num,string line){
	char* token;
	int i=2,j=0,k=0;
//bosluk ve : gorene kadar boluyorum ve tuttugum counter yardimi ile istedigim indexe veya dataya atama yapiyorum
	token = strtok(&line[1]," :");
	while( token != NULL ){
		if(i % 2 == 0){
			index[num][j] = atoi(token);
			i++;
      j++;
		}else if(i % 2 == 1){
			data[num][k] = atof(token);
			i++;
      k++;
		}
		token = strtok(NULL," :");
	}
}
//bu fonksiyonu toplama ve cikarma isleminde iki kere yaptigim icin tek fonksiyona dusurdum
//fonksiyon gelene iki classin topluyor veya cikariyor
SparseMatrix opera(char ch,const SparseMatrix& firstObject,const SparseMatrix& otherObject){
  SparseMatrix temp;
  int i=0,j=0,k=0,x=0,y=0,counter=0,o=0,p=0;

  for(;;){
    //eger iki classinde row sizeleri birbiirne esit olarak biter fonksiyon sonlandiriliyor
    if(o == firstObject.row.size() && p == otherObject.row.size())
      break;
  //eger ilk objenin boyutu biter ve diger objenin kalan elemanlar varsa kalan elemanlar sonuc clasinin belirtilen satirina ekleniyor
    if(o == firstObject.row.size()){
      int tempe = p;
      for(int b = 0; b < otherObject.row.size() - tempe ; b++){
          temp.index.push_back(otherObject.index[p]);
          temp.data.push_back(otherObject.data[p]);
          temp.row.push_back(otherObject.row[p]);
        p++;
      }
      break;
      //eger ikinci objenin boyutu biter ve diger objenin kalan elemanlar varsa kalan elemanlar sonuc clasinin belirtilen satirina ekleniyor
    }else if(p == otherObject.row.size()){
       int tempe = o;
      for(int b = 0; b < firstObject.row.size() - tempe ; b++){
          temp.index.push_back(firstObject.index[o]);
          temp.data.push_back(firstObject.data[o]);
          temp.row.push_back(firstObject.row[o]);
        o++;
      }
      break;
    }
    //eger iki objenin rowindexleri biribirine esitse bu demektirki iki satirin vectoerleri birirbiri ile toplanacaktir
    //ve burada SparseVEctor classinda yapmis oldugumuz toplama islmei yapiliyor
    if(firstObject.row[o] == otherObject.row[p]){
      vector<int> denemeindex;
      vector<double> denemedata;
      x=0;  y=0;
       for(;;){
        if(x == firstObject.index[o].size() && y == otherObject.index[p].size()){
          break;
        }
         if(x == firstObject.index[o].size()){
          int tempe = y;
          for(int f=0; f < otherObject.index[p].size() - tempe ; f++){
            denemeindex.push_back(otherObject.index[p][y]);
            denemedata.push_back(otherObject.data[p][y]);
            y++;
          }
          break;
        }else if(y == otherObject.index[p].size()){
          int tempe = x;
          for(int f=0; f < firstObject.index[o].size() - tempe; f++){
            denemeindex.push_back(firstObject.index[o][x]);
            denemedata.push_back(firstObject.data[o][x]);
            x++;
          }
          break;
        }
        if(firstObject.index[o][x] == otherObject.index[p][y]){
          denemeindex.push_back(firstObject.index[o][x]);
          if(ch == '+')
            denemedata.push_back(firstObject.data[o][x] + otherObject.data[p][y]);
          else if(ch == '-')
             denemedata.push_back(firstObject.data[o][x] - otherObject.data[p][y]);
          x++;
          y++;
        }else if(firstObject.index[o][x] < otherObject.index[p][y]){
          denemeindex.push_back(firstObject.index[o][x]);
          denemedata.push_back(firstObject.data[p][x]);
          x++;
        }else if(firstObject.index[o][x] > otherObject.index[p][y]){
          if(ch == '+')
            denemedata.push_back(firstObject.data[o][x] + otherObject.data[p][y]);
          else if(ch == '-')
            denemedata.push_back(0 - otherObject.data[p][y]);
          denemeindex.push_back(otherObject.index[p][y]);
          y++;
        }
      }
      temp.row.push_back(firstObject.row[o]);
      temp.index.push_back(denemeindex);
      temp.data.push_back(denemedata);
      o++;
      p++;
      //eger ilk objenin row indexi diger objenin indexinden kucukse kucuk olan sonuc clasinin rowindexine ekleniyor
    }else if(firstObject.row[o] < otherObject.row[p]){
         temp.index.push_back(firstObject.index[o]);
         temp.data.push_back(firstObject.data[o]);
         temp.row.push_back(firstObject.row[o]);
         o++;
          //eger ikincid objenin row indexi diger objenin indexinden kucukse kucuk olan sonuc clasinin rowindexine ekleniyor
    }else if(firstObject.row[o] > otherObject.row[p]){
         temp.index.push_back(otherObject.index[p]);
         temp.data.push_back(otherObject.data[p]);
         temp.row.push_back(otherObject.row[p]);
         p++;
    }
  }
  return temp;
}

const SparseMatrix SparseMatrix::operator +(const SparseMatrix& otherObject){
  SparseMatrix temp;
  temp = opera('+',*this,otherObject);
  return temp;
}
const SparseMatrix SparseMatrix::operator -(const SparseMatrix& otherObject){
  SparseMatrix temp;
  temp = opera('-',*this,otherObject);
  return temp;
}
SparseMatrix& SparseMatrix::operator = (const SparseMatrix& otherObject){
    // atama yapılacak classı tamamen bosaltiyorum ve bastan tekrar resize ediyorum
    //ve teker teker atamalari yapiyorum
  for(int i = 0 ; i < row.size(); i++){
      index[i].clear();
      data[i].clear();
  }
  row.clear();
  if(row.size() != otherObject.row.size()){
    row.resize(otherObject.row.size());
  }
  for(int i = 0; i < row.size(); i++){
    row[i] = otherObject.row[i];
  }
  index.resize(otherObject.index.size());
  data.resize(otherObject.data.size());

  for(int i = 0; i < row.size();i++){
    for(int j = 0; j < otherObject.index[i].size(); j++ ){
      if(j >= index[i].size()){
        index[i].push_back(otherObject.index[i][j]);
        data[i].push_back(otherObject.data[i][j]);
      }else{
        index[i][j] = otherObject.index[i][j];
        data[i][j] = otherObject.data[i][j];
      }
    }
  }
  return *this;
}
const SparseMatrix SparseMatrix::operator-()const{
  SparseMatrix temp;

  temp.row.resize(row.size());
  temp.index.resize(index.size());
  temp.data.resize(data.size());

  for(int i = 0; i < row.size();i++){
    temp.index[i].resize(index[i].size());
    temp.data[i].resize(data[i].size());
    for(int j = 0; j < index[i].size();j++){
      temp.index[i][j] = index[i][j];
      temp.data[i][j] = -data[i][j];
    }
  }
  return temp;
}
ostream& operator <<(ostream& outputStream,const SparseMatrix& otherObject){
  for(int i=0; i < otherObject.row.size(); i++){
    outputStream << otherObject.row[i] << " ";
    for(int j = 0; j < otherObject.index[i].size();j++){
      outputStream << otherObject.index[i][j] << ":" << otherObject.data[i][j] << " ";
    }
    outputStream << endl;
  }
}
SparseMatrix transpose(const SparseMatrix& otherObject){
  SparseMatrix deneme;
  int gecici,temp2,counter=0;

// ilk olarak transpose edilecek classın baska bir classa atayacagimden dolayi row size i hesapladim ve ona gore yer ayirdim
  for(int i = 0; i < otherObject.index.size(); i++){
    for(int j = 0; j < otherObject.index[i].size(); j++){
      if(deneme.row.size() == 0){
        deneme.row.push_back(otherObject.index[i][j]);
      }else if(control(deneme.row,otherObject.index[i][j]) == 1){
        deneme.row.push_back(otherObject.index[i][j]);
      }
    }
  }
   for(int i=0; i<deneme.row.size()-1;i++){ 
        for(int j=i+1; j<deneme.row.size(); j++){
            if(deneme.row[i] > deneme.row[j]){
                gecici = deneme.row[i];
                deneme.row[i] = deneme.row[j];
                deneme.row[j] = gecici;
            }
        }
    }
    //yukaridaki islemde rowun icerisini doldurdum boylelikle sizeinada ulasmis oldum
    deneme.index.resize(deneme.row.size());
    deneme.data.resize(deneme.row.size());
   
    for(int i = 0; i < otherObject.row.size(); i++){
      for(int j = 0; j < otherObject.index[i].size();j++){
        for(int k = 0 ; k < deneme.row.size();k++){
          if(deneme.row[k] == otherObject.index[i][j]){
            temp2 = k;
            break;
          }
        }
        deneme.index[temp2].push_back(otherObject.row[i]);
        deneme.data[temp2].push_back(otherObject.data[i][j]);
      }
    }
  return deneme;

}
//parameter olarak gonderilen vectorun icinde parameter olarak gonderilen sayinin olup olmadigin kontrol ediyor
int control(vector<int> cont,int num){
    for(int i = 0; i < cont.size();i++){
      if(cont[i] == num)
        return 0;
    }
    return 1;
  }
const SparseMatrix operator *(const SparseMatrix& leftObject,const SparseMatrix& rightObject){
  SparseMatrix temp,result;
  double sonuc;
  int rowSize = 0, entered = 0;
//oncelikle carpma yapilacak classlardan birini transpose diyorum ve boylelikle islemde kolaylik saglamis oluyorum
  temp = transpose(rightObject);
  // daha sonra carpma islemi yapildiktan sonra row size imin ne kadar olacagini buluyorum ve ona gore yer ayiriyorum
  //atama islemleri bir sonraki islmlerde yapilacak
  for (int i = 0; i < leftObject.row.size(); ++i)
  {
    for (int j = 0; j < temp.row.size(); ++j)
    {
        sonuc = dot(leftObject.data[i],leftObject.index[i],temp.data[j],temp.index[j]);
        if(sonuc!=0){
          if (entered == 0)
          {
            rowSize++;
          }
          entered = 1;

        }      
    }
    entered = 0;
  }
  result.index.resize(rowSize);
  result.data.resize(rowSize);
  
  rowSize = 0;
  //yukaridaki islmelerin aynisi tekrar yapiliyor ve bu islemleri sirasinda atamalar yapiliyor
  for (int i = 0; i < leftObject.row.size(); ++i)
  {
    for (int j = 0; j < temp.row.size(); ++j)
    {
        sonuc = dot(leftObject.data[i],leftObject.index[i],temp.data[j],temp.index[j]);
        if(sonuc!=0){

            if (entered == 0)
          {
            result.row.push_back(leftObject.row[i]);
            rowSize++;
          }

            result.index[rowSize-1].push_back(j+1);
            result.data[rowSize-1].push_back(sonuc);

             entered++;

        }      
    }
    entered = 0;
  }
  return result;

}
//iki vectorun carpma islemi vector classindaki dot fonksiyonu ile ayni islemi yapiyor
double dot(vector<double> num,vector<int> index,vector<double> num2,vector<int> index2){
  int i=0,j=0,size;
  double temp=0;

  for(;;){
    if(i == index.size()){
      int tempe = j;
      for(int x=0; x < index2.size() - tempe ; x++){
        temp +=num2[j]*0;
        j++;
      }
      break;
    }else if(j == index2.size()){
      int tempe = i;
      for(int x=0; x < index.size() - tempe; x++){
        temp += num[i]*0;
        i++;
      }
      break;
    }
    if(index[i] == index2[j]){
      temp += num[i] * num2[j];
      i++;
      j++;
    }else if(index[i] < index2[j]){
      temp += num[i] * 0;
      i++;
    }else if(index[i] > index2[j]){
      temp += num2[j]*0;
      j++;
    }
  }
  return temp;
}
