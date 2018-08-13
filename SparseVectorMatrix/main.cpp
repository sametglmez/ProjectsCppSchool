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

	SparseVector sample("r1.txt");
	SparseVector sample1("r2.txt");
	SparseVector cigi;
	double number;
	SparseMatrix sample2("r3.txt");
	SparseMatrix sample3("r4.txt");
	SparseMatrix sad;

	cout << "----------------R1--------------" << endl;
	cout << sample;
	cout << endl;
	cout << "--------------R2-----------------" << endl;
	cout << sample1;
	cout << endl;
	cigi = sample+sample1;
	cout << "-----------R1+R2----------------" << endl;
	cout << cigi;
	cout << endl;
	number = dot(sample1,sample);
	outfile << number ;
	cout <<"----------R2*R1--------------" << endl;
	cout << number;
	cout << endl;


	cout << "-----------R3--------------" << endl;
	cout << sample2;
	cout << endl;
	cout << "----------------R4------------------" << endl;
	cout << sample3;
	cout << endl;
	sad = sample2+sample3;
	cout << "-------------R3+R4---------------" << endl;
	cout << sad;
	cout << endl;
	sad = sample2*sample3;
	cout <<"-------------R3*R4---------------" << endl;
	cout << sad;
	cout << endl;
	sad = transpose(sample3);
	cout << "----------------R4--TRANSPOSE------------" << endl;
	cout << sad;
	cout << endl;
	cout << "--------------R3 NEGATiVE---------------" << endl;
	sad = -sample2;
	cout << sad;
	cout << endl;
 
	return 0;
}
