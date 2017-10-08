#include "Numbers/InfIntException.h"

namespace sbl {

    InfIntException::InfIntException(std::string msg) : message(msg) {}

    std::string InfIntException::getMessage() const {
    	return message;
    }

    std::ostream& operator << (std::ostream& out, InfIntException ex) {
    	out << "[INFINT EXCEPTION] " << ex.message;
    	return out;
    }


}
