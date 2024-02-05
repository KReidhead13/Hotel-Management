#include "discount.h"

Discount::Discount() {
    company = 'N';
    over = 2000;
}

Discount::Discount(char y, double x) {
    company = y;
    over = 2000;
}

ostream& operator << (ostream& out, const Discount &n) {
    if (n.getCompany() == 'Y') {
        out << "Company discount has been applied" << endl;
    }
    else {
        out << "Company discount has not been applied" << endl;
    }
    return out;
}

Discount::~Discount() {}