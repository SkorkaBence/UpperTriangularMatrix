#ifndef H_VECTOREXCEPTION
#define H_VECTOREXCEPTION

#include <iostream>
#include <string>

namespace sbl {
    class VectorException {
    private:
    	std::string message;
    public:
    	VectorException(std::string msg);
    	std::string getMessage() const;
    	friend std::ostream& operator << (std::ostream& out, VectorException ex);
    };
}


#endif // !H_VECTOREXCEPTION
