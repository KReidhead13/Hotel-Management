#ifndef ROOM_H
#define ROOM_H
#include "customer.h"
#include "packages.h"

string calculateDate(string, int*);

class Room : public Customer, public Packages {
protected:
	string type;
	int beds;
	char status;
public:
	Room();

	void setType(string);
	void setBeds(int);
	void setStatus(char);
	string getType() const;
	int getBeds() const;
	char getStatus() const;

	void clear();
	int available();

	const Room operator + (int*);
	const Room operator + (const Customer*);
	const Room operator + (const Packages*);
	friend ostream& operator << (ostream&, const Room*);
	void print();

	~Room();
};

#endif