#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <iostream>
#include <sstream>

using namespace std;

int calculateDays(string, string);
int countLeapYears(int, int);

class Customer {
protected:
	string name;
	int age;
	string arrival;
	string departure;
	int days;
public:
	Customer();

	void setName(string);
	void setAge(int);
	void setArrival(string);
	void setDeparture(string);
	string getName() const;
	int getAge() const;
	string getArrival() const;
	string getDeparture() const;
	int getDays() const;

	void info();

	virtual void print();

	virtual ~Customer();
};

#endif