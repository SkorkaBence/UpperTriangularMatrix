#ifndef H_SBL_MATRIXEXCEPTION
#define H_SBL_MATRIXEXCEPTION

#include <iostream>
#include <string>
#include <exception>

namespace sbl {
    class MatrixException : public std::exception {
    private:
    	std::string message;
    public:
    	MatrixException(std::string msg);
    	std::string getMessage() const;
    	friend std::ostream& operator << (std::ostream& out, MatrixException ex);
        const char * what () const throw () {
            return "MatrixException";
        }
    };
}


#endif // !H_SBL_MATRIXEXCEPTION
