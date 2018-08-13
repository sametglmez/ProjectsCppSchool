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

#include "SparseVector.h"
#include "SparseMatrix.h"

using namespace std;

int main(int argc, char const *argv[]){
	
	ofstream outfile;
	vector<int> tile;
	outfile.open("output.txt", ios::out | ios::trunc );

	SparseVector samet("r1.txt");
	SparseVector sulo("r2.txt");
	SparseVector cigi;
	double number;
	SparseMatrix eyup("r3.txt");
	SparseMatrix enes("r4.txt");
	SparseMatrix sad;

	cout << "----------------R1--------------" << endl;
	cout << samet;
	cout << endl;
	cout << "--------------R2-----------------" << endl;
	cout << sulo;
	cout << endl;
	cigi = samet+sulo;
	cout << "-----------R1+R2----------------" << endl;
	cout << cigi;
	cout << endl;
	number = dot(sulo,samet);
	outfile << number ;
	cout <<"----------R2*R1--------------" << endl;
	cout << number;
	cout << endl;


	cout << "-----------R3--------------" << endl;
	cout << eyup;
	cout << endl;
	cout << "----------------R4------------------" << endl;
	cout << enes;
	cout << endl;
	sad = eyup+enes;
	cout << "-------------R3+R4---------------" << endl;
	cout << sad;
	cout << endl;
	sad = eyup*enes;
	cout <<"-------------R3*R4---------------" << endl;
	cout << sad;
	cout << endl;
	sad = transpose(enes);
	cout << "----------------R4--TRANSPOSE------------" << endl;
	cout << sad;
	cout << endl;
	cout << "--------------R3 NEGATiVE---------------" << endl;
	sad = -eyup;
	cout << sad;
	cout << endl;
 
	return 0;
}