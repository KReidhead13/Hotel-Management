#ifndef DISCOUNT_H
#define DISCOUNT_H
#include <iostream>

using namespace std;

class Discount {
private:
    char company;
    double over;
public:
    Discount();
    Discount(char, double);

    char getCompany() const { return company; }
    void setCompany(char n) { company = n; }
    double getOver() const { return over; }
    void setOver(double x) { over = x; }

    friend ostream& operator << (ostream&, const Discount&);

    ~Discount();
};

#endif