#ifndef PACKAGES_H
#define PACKAGES_H
#include <iostream>

using namespace std;

class Packages {
protected:
    char tv;
    char rservice;
public:
    Packages();

    char getTV() const;
    void setTV(char t);
    char getServ() const;
    void setServ(char r);

    void selection();

    ~Packages();
};

#endif