#include "Numbers/InfInt.h"

#include "Numbers/InfIntException.h"
#include <sstream>
#include <string>

namespace sbl {
    InfInt::InfInt() {
    	convertFrom(0);
    }

    InfInt::InfInt(int startpoint) {
    	convertFrom(startpoint);
    }

    InfInt::InfInt(const InfInt& copythis) {
    	this->negative = copythis.negative;
    	this->base = copythis.base;
    	this->num.clear();
    	this->num.resize(copythis.num.size());
    	for (int i = 0; i < copythis.num.size(); i++) {
    		this->num[i] = copythis.num[i];
    	}
    }

    void InfInt::convertFrom(int in) {
    	num.clear();
    	num.reserve(30);
    	negative = in < 0;
    	if (negative) {
    		in = -in;
    	}
    	while (in > 0) {
    		num.push_back(in % base);
    		in /= base;
    	}
    }

    void InfInt::removeLeadingZeros() {
    	while (num.size() > 1 && num[num.size() - 1] == 0) {
    		num.pop_back();
    	}
    }

    InfInt& InfInt::operator += (InfInt addthis) {
    	if (base != addthis.base) {
    		throw InfIntException("Bases are not matching");
    	}

    	int max = num.size();
    	if (max < addthis.num.size()) {
    		max = addthis.num.size();
    	}
    	max++;

    	while (num.size() < max) {
    		num.push_back(0);
    	}

    	infint_vector copy(this->num);

    	int carry = 0;
    	for (int i = 0; i < max; i++) {
    		int newval = copy[i];
    		if (i < addthis.num.size()) {
    			if (addthis.negative) {
    				newval -= addthis.num[i];
    			}
    			else {
    				newval += addthis.num[i];
    			}
    		}
    		newval += carry;
    		carry = 0;
    		while (newval >= base) {
    			newval -= base;
    			carry++;
    		}
    		this->num[i] = newval;
    	}

    	removeLeadingZeros();

    	return *this;
    }

    InfInt& InfInt::operator *= (InfInt multthis) {
    	if (base != multthis.base) {
    		throw InfIntException("Bases are not matching");
    	}

    	int max = num.size() + multthis.num.size() + 1;

    	infint_vector copy(this->num);

    	while (num.size() < max) {
    		num.push_back(0);
    	}

    	for (int i = 0; i < num.size(); i++) {
    		num[i] = 0;
    	}

    	for (int i1 = 0; i1 < copy.size(); i1++) {
    		int carry = 0;
    		for (int i2 = 0; i2 < multthis.num.size(); i2++) {
    			int a = num[i1 + i2];
    			a += carry + copy[i1] * multthis.num[i2];
    			carry = a / base;
    			a = a % base;
    			num[i1 + i2] = a;
    		}
    		num[i1 + multthis.num.size()] += carry;
    	}

    	removeLeadingZeros();

    	return *this;
    }

    int InfInt::toInt() const {
    	int val = 0;

    	for (int i = 0; i < num.size(); i++) {
    		val *= base;
    		val += num[i];
    	}

    	if (negative) {
    		val = -val;
    	}

    	return val;
    }

    std::string InfInt::toString() const {
    	std::stringstream ss;
    	ss << *this;
    	return ss.str();
    }

    std::string InfInt::getDigits() const {
    	std::stringstream ss;
    	for (int i = this->num.size() - 1; i >= 0; i--) {
    		ss << "{";
    		ss << (int)this->num[i];
    		ss << "}";
    	}
    	return ss.str();
    }

    void InfInt::changeBase(int newbase) {
    	int number = toInt();
    	base = newbase;
    	convertFrom(number);
    }

    std::ostream& operator << (std::ostream& out, const InfInt& data) {
    	if (data.base == 10) {
    		if (data.negative) {
    			out << "-";
    		}

    		for (int i = data.num.size() - 1; i >= 0; i--) {
    			out << (int)data.num[i];
    		}
    	}
    	else {
    		InfInt newnumber = 0;
    		newnumber.base = 10;
    		InfInt bs;
    		bs.base = 10;
    		bs.convertFrom(data.base);
    		InfInt val;
    		val.base = 10;

    		for (int i = data.num.size() - 1; i >= 0; i--) {
    			val.convertFrom(data.num[i]);

    			newnumber *= bs;
    			newnumber += val;
    		}

    		newnumber.negative = data.negative;

    		out << newnumber;
    	}

    	return out;
    }

    InfInt InfInt::operator + (const InfInt& val2) const {
    	InfInt newnum = *this;
    	newnum += val2;
    	return newnum;
    }

    InfInt InfInt::operator * (const InfInt& val2) const  {
    	InfInt newnum = *this;
    	newnum *= val2;
    	return newnum;
    }

    bool InfInt::operator == (const InfInt& val2) const {
    	if (this->base != val2.base) {
    		throw InfIntException("Bases are not matching");
    	}

    	if (this->num.size() != val2.num.size()) {
    		return false;
    	}

    	for (int i = 0; i < this->num.size(); i++) {
    		if (this->num[i] != val2.num[i]) {
    			return false;
    		}
    	}

    	return true;
    }

    bool InfInt::operator == (const int& val2) const {
    	InfInt temp = val2;
    	return *this == temp;
    }

    bool InfInt::operator < (const InfInt& val2) const {
    	if (this->base != val2.base) {
    		throw InfIntException("Bases are not matching");
    	}

    	if (this->num.size() < val2.num.size() && this->num[this->num.size() - 1] != 0) {
    		return true;
    	}
    	else if (val2.num.size() < this->num.size() && val2.num[val2.num.size() - 1] != 0) {
    		return false;
    	}

    	if (*this == 488) {
    		char asd = 'x';
    	}

    	for (int i = this->num.size() - 1; i >= 0; i--) {
    		if (this->num[i] < val2.num[i]) {
    			return true;
    		}
    		else if (this->num[i] > val2.num[i]) {
    			return false;
    		}
    	}

    	return false;
    }
}
