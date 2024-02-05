#include "customer.h"

struct Date {
	int day;
	int month;
	int year;
};

Customer::Customer() {
	name = "";
	age = 0;
	arrival = "";
	departure = "";
	days = 0;
}

void Customer::setName(string x) { name = x; }
void Customer::setAge(int x) { age = x; }
void Customer::setArrival(string x) { 
	arrival = x; 
	days = calculateDays(arrival, departure);
}
void Customer::setDeparture(string x) { 
	departure = x; 
	days = calculateDays(arrival, departure);
}
string Customer::getName() const { return name; }
int Customer::getAge() const { return age; }
string Customer::getArrival() const { return arrival; }
string Customer::getDeparture() const { return departure; }
int Customer::getDays() const { return days; }

void Customer::info() {
	string n, k, j;
	int x;

	cout << "Please enter the following information" << endl;
	cout << "Customer name: ";
	cin >> n;
	cout << "Age: ";
	cin >> x;
	
	this->setName(n);
	this->setAge(x);

	do {
		cout << "Date of Arrival (in format yyyy-mm-dd): ";
		cin >> k;
		cout << "Date of Departure: ";
		cin >> j;
		cout << endl;

		this->setArrival(k);
		this->setDeparture(j);

		if (this->getDays() < 1) {
			cout << "Customer cannot stay less than 1 day. Please re-enter" << endl;
		}
		else {
			break;
		}
	} while (true);
}

void Customer::print() {
	cout << "Customer Name: " << this->getName() << endl
		 << "Customer Age: " << this->getAge() << endl
		 << "Date of Arrival: " << this->getArrival() << endl
		 << "Date of Departure: " << this->getDeparture() << endl
		 << "Number of Days Staying: " << this->getDays() << endl;
}

Customer::~Customer() {}

int calculateDays(string x, string y) {
	Date date1, date2;
	int days;
	const int monthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	constexpr char DELIMITER = '-';

	std::istringstream stm1(x);
	char delim;
	stm1 >> date1.year >> delim;
	stm1 >> date1.month >> delim;
	stm1 >> date1.day;

	std::istringstream stm2(y);
	stm2 >> date2.year >> delim;
	stm2 >> date2.month >> delim;
	stm2 >> date2.day;

	long int n1 = date1.year * 365 + date1.day;

	for (int i = 0; i < date1.month - 1; i++) {
		n1 += monthDays[i];
	}	
	n1 += countLeapYears(date1.year, date1.month);

	long int n2 = date2.year * 365 + date2.day;

	for (int i = 0; i < date2.month - 1; i++) {
		n2 += monthDays[i];
	}
	n2 += countLeapYears(date2.year, date2.month);

	days = (n2 - n1);

	return days;
}

int countLeapYears(int y, int m) {
	int years = y;

	if (m <= 2)
		years--;

	return (years / 4 - years / 100 + years / 400);
}