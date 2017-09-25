#ifndef  H_IMENU
#define H_IMENU

#include <iostream>

class IMenu {
protected:
    std::ostream out;
public:
	IMenu(std::ostream o);

    void show() : virtual;
};

#endif // ! H_IMENU
