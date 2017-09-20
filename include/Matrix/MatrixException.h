#ifndef H_MATRIXEXCEPTION
#define H_MATRIXEXCEPTION

#include <iostream>
#include <string>

class MatrixException {
private:
	std::string message;
public:
	MatrixException(std::string msg);
	std::string getMessage() const;
	friend std::ostream& operator << (std::ostream& out, MatrixException ex);
};


#endif // !H_MATRIXEXCEPTION
