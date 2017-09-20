#include "Matrix/UpperTriangularMatrix.h"

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
		return x - y + (size + size - y + 1) * (y) / 2;
	}
}

int& UpperTriangularMatrix::operator() (unsigned int x, unsigned int y) {
	int index = this->calculateVectorPosition(x, y);
	if (index >= 0 && index < data.size()) {
		return this->data[index];
	} else {
		throw MatrixException("Invalid positions");
	}
}

int numDigits(int number) {
	int digits = 0;
	if (number < 0) number *= -1;
	if (number == 0) return 1;
	while (number) {
		number /= 10;
		digits++;
	}
	return digits;
}

std::ostream& operator << (std::ostream& out, const UpperTriangularMatrix& mx) {
	int max = mx.data[0];
	for (int i = 0; i < mx.data.size(); i++) {
		if (mx.data[i] > max) {
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

bool UpperTriangularMatrix::operator += (const UpperTriangularMatrix& addthis) {
	if (this->size != addthis.size) {
		throw MatrixException("Incompatible sizes");
	}

	for (int i = 0; i < this->data.size(); i++) {
		this->data[i] += addthis.data[i];
	}
	return true;
}

UpperTriangularMatrix UpperTriangularMatrix::operator + (const UpperTriangularMatrix& addthis) const {
	UpperTriangularMatrix nw(*this);
	nw += addthis;
	return nw;
}

bool UpperTriangularMatrix::operator *= (const number_type& mult) {
	for (int i = 0; i < this->data.size(); i++) {
		this->data[i] *= mult;
	}
	return true;
}
UpperTriangularMatrix UpperTriangularMatrix::operator * (const number_type& mult) const {
	UpperTriangularMatrix nw(*this);
	nw *= mult;
	return nw;
}

bool UpperTriangularMatrix::operator = (const UpperTriangularMatrix& clone) {
	copyFrom(clone);
	return true;
}

void UpperTriangularMatrix::copyFrom(const UpperTriangularMatrix& copy) {
	size = copy.size;
	data.resize(copy.data.size());
	for (int i = 0; i < copy.data.size(); i++) {
		data[i] = copy.data[i];
	}
}
