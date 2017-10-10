#ifndef  H_SBL_UPPERTRIANGULARMATRIX
#define H_SBL_UPPERTRIANGULARMATRIX

#include <vector>
#include <iostream>
#include <fstream>
#include "Matrix/MatrixException.h"
#include "Storage/Vector.h"

typedef int number_type;

namespace sbl {
    class UpperTriangularMatrix {
    protected:
    	int size;
    	sbl::vector<number_type> data;

    	int calculateVectorLength() const;
    	int calculateVectorPosition(unsigned int x, unsigned int y) const;

    	void copyFrom(const UpperTriangularMatrix& copy);
    public:
    	UpperTriangularMatrix(int s);
    	UpperTriangularMatrix(const UpperTriangularMatrix& copy);
    	~UpperTriangularMatrix();

    	number_type& operator () (unsigned int x, unsigned int y);
        number_type operator () (unsigned int x, unsigned int y) const;
    	UpperTriangularMatrix& operator += (const UpperTriangularMatrix& addthis);
    	UpperTriangularMatrix operator + (const UpperTriangularMatrix& addthis) const;
    	UpperTriangularMatrix& operator *= (const number_type& mult);
    	UpperTriangularMatrix operator * (const number_type& mult) const;
    	UpperTriangularMatrix& operator = (const UpperTriangularMatrix& clone);
        UpperTriangularMatrix operator * (const UpperTriangularMatrix& mult) const;

        bool writeData(std::ostream& out) const;
        bool readData(std::istream& in);
        int getSize() const;

    	friend std::ostream& operator << (std::ostream& out, const UpperTriangularMatrix& mx);
    };

}

#endif // ! H_SBL_UPPERTRIANGULARMATRIX
