//DEFİNİTON OF SPARSEMATRİX

#include "SparseVector.h"

#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

using namespace std;

class SparseMatrix{
public:
	SparseMatrix();
	SparseMatrix(string filename);
	const SparseMatrix operator +(const SparseMatrix& otherObject);
	const SparseMatrix operator -(const SparseMatrix& otherObject);
	const SparseMatrix operator-()const;
	SparseMatrix& operator = (const SparseMatrix& otherObject);
	friend ostream& operator <<(ostream& outputStream,const SparseMatrix& otherObject);
	friend SparseMatrix transpose(const SparseMatrix& otherObject); 
	void divide(int num,string line);
	friend SparseMatrix opera(char ch,const SparseMatrix& firstObject,const SparseMatrix& otherObject);

	vector<int> row;
	vector<vector<int> > index;
	vector<vector<double> > data;
private:

};
const SparseMatrix operator *(const SparseMatrix& leftObject,const SparseMatrix& rightObject);
double dot(vector<double> num,vector<int> index,vector<double> num2,vector<int> index2);
int control(vector<int> cont,int num);
#endif