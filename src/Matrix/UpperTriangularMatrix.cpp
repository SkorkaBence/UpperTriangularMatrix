#include "Matrix/UpperTriangularMatrix.h"
#include <string>

namespace sbl {

    UpperTriangularMatrix::UpperTriangularMatrix(int s) : size(s) {
    	data.resize(this->calculateVectorLength());
    	for (int i = 0; i < data.size(); i++) {
    		data[i] = 0;
    	}
    }

    UpperTriangularMatrix::UpperTriangularMatrix(const UpperTriangularMatrix& copy) {
    	copyFrom(copy);
    }

    UpperTriangularMatrix::~UpperTriangularMatrix() {
    	data.clear();
    }

    int UpperTriangularMatrix::calculateVectorLength() const {
    	return ((1 + size) * size / 2);
    }

    int UpperTriangularMatrix::calculateVectorPosition(unsigned int x, unsigned int y) const {
    	if (x < y || x < 0 || y < 0 || x >= size || y >= size) {
    		return -1;
    	} else {
            return x - y + (((2 * size - y + 1.0) * y) / 2);
    	}
    }

    number_type& UpperTriangularMatrix::operator() (unsigned int x, unsigned int y) {
    	int index = this->calculateVectorPosition(x, y);
    	if (index >= 0 && index < data.size()) {
    		return this->data[index];
    	} else {
    		throw MatrixException("Invalid positions");
    	}
    }

    number_type UpperTriangularMatrix::operator() (unsigned int x, unsigned int y) const {
    	int index = this->calculateVectorPosition(x, y);
    	if (index >= 0 && index < data.size()) {
    		return this->data[index];
    	} else {
    		return 0;
    	}
    }

    int numDigits(number_type number) {
    	int digits = 0;
        if (number == 0) return 1;
    	if (number < 0) number *= -1;
    	while (0 < number) {
    		number /= 10;
    		digits++;
    	}
    	return digits;
    }

    std::ostream& operator << (std::ostream& out, const UpperTriangularMatrix& mx) {
    	number_type max = mx.data[0];
    	for (int i = 0; i < mx.data.size(); i++) {
    		if (max < mx.data[i]) {
    			max = mx.data[i];
    		}
    	}

    	int max_num_of_digits = numDigits(max);

    	for (int y = 0; y < mx.size; y++) {
    		for (int x = 0; x < mx.size; x++) {
    			int index = mx.calculateVectorPosition(x, y);
    			if (index >= 0 && index < mx.data.size()) {
    				int write = mx.data[index];
    				out << "[";
    				int nd = numDigits(write);
    				while (nd < max_num_of_digits) {
    					out << 0;
    					nd++;
    				}
    				out << write;
    				out << "]";
    			} else {
    				for (int i = 0; i < max_num_of_digits + 2; i++) {
    					out << " ";
    				}
    			}
    		}
    		out << std::endl;
    	}
    	return out;
    }

    bool UpperTriangularMatrix::writeData(std::ostream& out) const {
        out << size;
        for (int i = 0; i < data.size(); i++) {
            out << " " << data[i];
        }
        return true;
    }

    bool UpperTriangularMatrix::readData(std::istream& in) {
        in >> size;
    	data.resize(calculateVectorLength());
        //std::cerr << "Matrix size: " << size << " Vector size: " << data.size() << std::endl;
    	for (int i = 0; i < data.size(); i++) {
    		in >> data[i];
    	}
    	return true;
    }

    UpperTriangularMatrix& UpperTriangularMatrix::operator += (const UpperTriangularMatrix& addthis) {
    	if (this->size != addthis.size) {
    		throw MatrixException("Incompatible sizes");
    	}

    	for (int i = 0; i < this->data.size(); i++) {
    		this->data[i] += addthis.data[i];
    	}
    	return *this;
    }

    UpperTriangularMatrix UpperTriangularMatrix::operator + (const UpperTriangularMatrix& addthis) const {
    	UpperTriangularMatrix nw(*this);
    	nw += addthis;
    	return nw;
    }

    UpperTriangularMatrix& UpperTriangularMatrix::operator *= (const number_type& mult) {
    	for (int i = 0; i < this->data.size(); i++) {
    		this->data[i] *= mult;
    	}
    	return *this;
    }
    UpperTriangularMatrix UpperTriangularMatrix::operator * (const number_type& mult) const {
    	UpperTriangularMatrix nw(*this);
    	nw *= mult;
    	return nw;
    }

    UpperTriangularMatrix& UpperTriangularMatrix::operator = (const UpperTriangularMatrix& clone) {
    	copyFrom(clone);
    	return *this;
    }

    void UpperTriangularMatrix::copyFrom(const UpperTriangularMatrix& copy) {
    	size = copy.size;
    	data.resize(copy.data.size());
    	for (int i = 0; i < copy.data.size(); i++) {
    		data[i] = copy.data[i];
    	}
    }

    UpperTriangularMatrix UpperTriangularMatrix::operator * (const UpperTriangularMatrix& mult) const {
        UpperTriangularMatrix nw(size);

        for (unsigned int x = 0; x < size; x++) {
            for (unsigned int y = 0; y <= x; y++) {
                int index = calculateVectorPosition(x, y);
                if (index >= 0) {
                    //std::cerr << "POS: " << x << " " << y << std::endl;
                    int val = 0;
                    int min = (x > y ? y : x);
                    int max = (x > y ? x : y);
                    for (unsigned int t = min; t <= max; t++) {
                        int index1 = calculateVectorPosition(x, t);
                        int index2 = calculateVectorPosition(t, y);
                        //std::cerr << x << " " << t << " " << index1 << " " << t << " " << y << " " << index2 << std::endl;
                        if (index1 >= 0 && index2 >= 0) {
                            val += this->data[index2] * mult.data[index1];
                        }
                    }
                    nw.data[index] = val;
                }
            }
        }

        return nw;
    }

    int UpperTriangularMatrix::getSize() const {
        return size;
    }

}
