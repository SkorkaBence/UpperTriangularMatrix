#include "Storage/VectorException.h"

namespace sbl {

    VectorException::VectorException(std::string msg) : message(msg) {}

    std::string VectorException::getMessage() const {
    	return message;
    }

    std::ostream& operator << (std::ostream& out, VectorException ex) {
    	out << "[VECTOR EXCEPTION] " << ex.message;
    	return out;
    }


}
