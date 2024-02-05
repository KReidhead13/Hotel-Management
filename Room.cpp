#include "room.h"

Room::Room() {
	type = "Regular";
	beds = 2;
	status = 'A';
}

void Room::setType(string x) { type = x; }
void Room::setBeds(int x) { beds = x; }
void Room::setStatus(char x) { status = x; }
string Room::getType() const { return type; }
int Room::getBeds() const { return beds; }
char Room::getStatus() const { return status; }

void Room::clear() {
	this->setName("");
	this->setAge(0);
	this->setArrival("");
	this->setDeparture("");

	cout << "Room has been cleared" << endl;
}

int Room::available() {
	if (this->getStatus() == 'A') {
		return 1;
	}
	else {
		cout << "Room is occupied. Please select another room" << endl;
		return 2;
	}
}

const Room Room::operator + (int* n) {
	Room obj;

	obj.name = this->name;
	obj.days = this->days + *n;
	obj.departure = calculateDate(this->departure, n);
	obj.beds = this->beds;
	obj.status = this->status;

	return obj;
}

const Room Room::operator + (const Customer* n) {
	Room obj;

	obj.name = n->getName();
	obj.age = n->getAge();
	obj.arrival = n->getArrival();
	obj.departure = n->getDeparture();
	obj.days = n->getDays();
	obj.tv = this->getTV();
	obj.rservice = this->getServ();
	obj.type = this->type;
	obj.beds = this->beds;
	obj.status = 'O';

	return obj;
}

const Room Room::operator + (const Packages* n) {
	Room obj;

	obj.name = this->getName();
	obj.age = this->getAge();
	obj.arrival = this->getArrival();
	obj.departure = this->getDeparture();
	obj.days = this->getDays();
	obj.tv = n->getTV();
	obj.rservice = n->getServ();
	obj.type = this->type;
	obj.beds = this->beds;
	obj.status = 'O';

	return obj;
}

void Room::print() {
	if (status == 'A') {
		cout << "Current Guest Name: N/A" << endl;
		cout << "Days Staying: N/A" << endl;
		cout << "Room Availability: A" << endl;
	}
	else {
		cout << "Current Guest Name: " << name << endl;
		cout << "Age: " << age << endl;
		cout << "Date of Arrival: " << arrival << endl;
		cout << "Date of Departure: " << departure << endl;
		cout << "Days Staying: " << days << endl;
		cout << "Room Availability: O" << endl;
		cout << "TV Packages: " << tv << endl;
		cout << "Room Service: " << rservice << endl;
	}
	cout << "Room Type: " << type << endl;
	cout << "Number of Beds: " << beds << endl;
	cout << endl;
}

ostream& operator << (ostream& out, const Room* n) {
	if (n->getStatus() == 'A') {
		out << "Current Guest Name: N/A" << endl
			<< "Days Staying: N/A" << endl
			<< "Room Availability: A" << endl;
	}
	else {
		out << "Current Guest Name: " << n->getName() << endl
			<< "Age: " << n->getAge() << endl
			<< "Date of Arrival: " << n->getArrival() << endl
			<< "Date of Departure: " << n->getDeparture() << endl
			<< "Days Staying: " << n->getDays() << endl
			<< "Room Availability: O" << endl
			<< "TV Packages: " << n->getTV() << endl
			<< "Room Service: " << n->getServ() << endl;
	}
	out << "Room Type: " << n->getType() << endl
		<< "Number of Beds: " << n->getBeds() << endl
		<< endl;

	return out;
}

Room::~Room() {}

string calculateDate(string x, int* extend) {
	int day, month, year;
	string date;
	const int monthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	constexpr char DELIMITER = '-';

	std::istringstream stm1(x);
	char delim;
	stm1 >> year >> delim;
	stm1 >> month >> delim;
	stm1 >> day;

	day += *extend;

	if (day > monthDays[month]) {
		day -= monthDays[month - 1];
		month++;

		if (month > 12) {
			month = 01;
			year++;
		}
	}

	if (month < 10) {
		if (day < 10) {
			date = to_string(year) + "-0" + to_string(month) + "-0" + to_string(day);
		}
		else {
			date = to_string(year) + "-0" + to_string(month) + "-" + to_string(day);
		}
	}
	else {
		if (day < 10) {
			date = to_string(year) + "-" + to_string(month) + "-0" + to_string(day);
		}
		else {
			date = to_string(year) + "-" + to_string(month) + "-" + to_string(day);
		}
	}

	return date;
}