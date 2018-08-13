//---------DEFINITION OF SPARSEVECTOR CLASS----------
#ifndef SPARSEVECTOR_H
#define SPARSEVECTOR_H

using namespace std;

class SparseVector{
public:
	SparseVector();
	SparseVector(string filename);
	const SparseVector operator +(const SparseVector& otherObject)const;
	const SparseVector operator -(const SparseVector& otherObject)const;
	const SparseVector operator-()const;
	SparseVector& operator = (const SparseVector& otherObject);
	friend ostream& operator <<(ostream& outputStream,const SparseVector& otherObject);
	friend double dot(const SparseVector& leftSide,const SparseVector& rightside);
	vector<int> index;
	vector<double> data;

private:

};
#endif