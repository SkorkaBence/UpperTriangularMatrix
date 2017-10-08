#ifndef H_SBL_INFNT
#define H_SBL_INFNT

#include <iostream>
#include <stdint.h>
#include "Storage/Vector.h"

typedef uint8_t infint_vector_number;
typedef sbl::vector<infint_vector_number> infint_vector;

namespace sbl {
    class InfInt {
    private:
    	int base = 256;

    	bool negative = false;
    	infint_vector num;

    	void removeLeadingZeros();

    public:
    	InfInt();
    	InfInt(int startpoint);
    	InfInt(const InfInt& copythis);

    	void changeBase(int newbase);

    	void convertFrom(int in);
    	int toInt() const;
    	std::string toString() const;
    	std::string getDigits() const;

    	InfInt& operator += (InfInt addthis);
    	InfInt& operator *= (InfInt multthis);

    	InfInt operator + (const InfInt& val2) const;
    	InfInt operator * (const InfInt& val2) const;

    	bool operator == (const InfInt& val2) const;
    	bool operator == (const int& val2) const;
    	bool operator < (const InfInt& val2) const;

    	friend std::ostream& operator << (std::ostream& out, const InfInt& data);
    };
}

#endif // !H_SBL_INFNT
