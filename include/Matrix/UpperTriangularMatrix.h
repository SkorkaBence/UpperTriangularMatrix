#ifndef  H_UPPERTRIANGULARMATRIX
#define H_UPPERTRIANGULARMATRIX

#include <vector>
#include <iostream>
#include "Matrix/MatrixException.h"

typedef int number_type;

class UpperTriangularMatrix {
private:
	int size;
	std::vector<number_type> data;

	int calculateVectorLength() const;
	int calculateVectorPosition(unsigned int x, unsigned int y) const;

	void copyFrom(const UpperTriangularMatrix& copy);

public:
	UpperTriangularMatrix(int s);
	UpperTriangularMatrix(const UpperTriangularMatrix& copy);
	~UpperTriangularMatrix();

	int& operator () (unsigned int x, unsigned int y);
	bool operator += (const UpperTriangularMatrix& addthis);
	UpperTriangularMatrix operator + (const UpperTriangularMatrix& addthis) const;
	bool operator *= (const number_type& mult);
	UpperTriangularMatrix operator * (const number_type& mult) const;
	bool operator = (const UpperTriangularMatrix& clone);

	friend std::ostream& operator << (std::ostream& out, const UpperTriangularMatrix& mx);
};



#endif // ! H_UPPERTRIANGULARMATRIX
