#include "price.h"

Price::Price() {
    Rate = 0;
    Tax = 0;
    Extra = 0;
    Total = 0;
    Subtotal = 0;
}

Price::Price(Room* obj1, Discount* obj2) : Room(*obj1), Discount(*obj2) {
    if (obj1->getType() == "VIP") {
        Rate = 200;
    }
    else {
        Rate = 100;
    }

    Extra = 0;

    if (obj1->getTV() == 'Y') {
        Extra += 50;
    }
    if (obj1->getServ() == 'Y') {
        Extra += 100;
    }

    Tax = 1.13;
    Total = Extra + (Rate * obj1->getDays());
    Subtotal = 0;
}

double Price::getTotal() const { return Total; }
double Price::getRate() const { return Rate; }
double Price::getExtra() const { return Extra; }
double Price::getTax() const { return Tax; }
double Price::getSubtotal() const { return Subtotal; }

void Price::print() {
    cout << "The customer's total before tax and discounts is: $" << this->getTotal() << endl;
}

double Price::discount() {
    if (Total > this->getOver()) {
        Subtotal = Total * 0.95;

        if (this->getCompany() == 'Y') {
            Subtotal *= 0.8;

            if (age > 65) {
                Subtotal *= 0.9;
            }
        }
        else {
            if (age > 65) {
                Subtotal *= 0.9;
            }
        }
    }
    else {
        Subtotal = Total;

        if (this->getCompany() == 'Y') {
            Subtotal *= 0.8;

            if (age > 65) {
                Subtotal *= 0.9;
            }
        }
        else {
            if (age > 65) {
                Subtotal *= 0.9;
            }
        }
    }

    return (Subtotal * 1.13);
}

ostream& operator << (ostream& out, const Price* n) {
    out << "--------- Customer Bill ---------" << endl
        << "Customer Name: " << n->getName() << endl
        << "Customer Age: " << n->getAge() << endl
        << "Date of Arrival: " << n->getArrival() << endl
        << "Date of Departure: " << n->getDeparture() << endl
        << "Number of Days Staying: " << n->getDays() << endl
        << "Room Type: " << n->getType() << endl
        << "Number of Beds: " << n->getBeds() << endl
        << "Room Rate: $" << n->getRate() << "/night" << endl
        << "TV uprgrade package: $";

    if (n->getTV() == 'Y') {
        out << "50" << endl;
    }
    else {
        out << '0' << endl;
    }

    out << "Room service package: $";

    if (n->getServ() == 'Y') {
        out << "100" << endl;
    }
    else {
        out << '0' << endl;
    }

    out << "Price before Tax and Discounts: $" << n->getTotal() << endl
        << "Company Discount: " << n->getCompany() << endl
        << "Age Discount: ";

    if (n->getAge() > 65) {
        out << 'Y' << endl;
    }
    else {
        out << 'N' << endl;
    }

    out << "Spending Discount: ";

    if (n->getTotal() > n->getOver()) {
        out << 'Y' << endl;
    }
    else {
        out << 'N' << endl;
    }

    out << "Tax Rate: " << (n->getTax() - 1) * 100 << "%" << endl
        << "Price after Tax and Discounts: $" << (n->getSubtotal() * n->getTax()) << endl << endl;

    return out;
}


Price::~Price() {}