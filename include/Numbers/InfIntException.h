#ifndef H_SBL_INFINTEXCEPTION
#define H_SBL_INFINTEXCEPTION

#include <iostream>
#include <string>
#include <exception>

namespace sbl {
    class InfIntException : public std::exception {
    private:
    	std::string message;
    public:
    	InfIntException(std::string msg);
    	std::string getMessage() const;
    	friend std::ostream& operator << (std::ostream& out, InfIntException ex);
        const char * what () const throw () {
            return "InfIntException";
        }
    };
}


#endif // !H_SBL_INFINTEXCEPTION
