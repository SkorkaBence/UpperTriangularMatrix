#ifndef H_SBL_VECTOREXCEPTION
#define H_SBL_VECTOREXCEPTION

#include <iostream>
#include <string>
#include <exception>

namespace sbl {
    class VectorException : public std::exception {
    private:
    	std::string message;
    public:
    	VectorException(std::string msg);
    	std::string getMessage() const;
    	friend std::ostream& operator << (std::ostream& out, VectorException ex);
        const char * what () const throw () {
            return "VectorException";
        }
    };
}


#endif // !H_SBL_VECTOREXCEPTION
