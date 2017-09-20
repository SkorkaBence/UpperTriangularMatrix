#include "Matrix/MatrixException.h"



MatrixException::MatrixException(std::string msg) : message(msg) {}


std::string MatrixException::getMessage() const {
	return message;
}

std::ostream& operator << (std::ostream& out, MatrixException ex) {
	out << "[MATRIX EXCEPTION] " << ex.message;
	return out;
}
