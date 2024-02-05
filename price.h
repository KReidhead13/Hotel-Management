#ifndef PRICE_H
#define PRICE_H
#include "room.h"
#include "discount.h"
#include "packages.h"

class Price : public Room, public Discount {
protected:
	double Rate;
	double Tax;
	double Extra;
	double Total;
	double Subtotal;
public:
	Price();
	Price(Room*, Discount*);

	void setRate(double rate) {Rate = rate;}
	double getExtra() const;
	double getTotal() const;
	double getRate() const;
	double getTax() const;
	double getSubtotal() const;

	double discount();
	void print();

	friend ostream& operator << (ostream&, const Price*);

	~Price();
};

#endif 
