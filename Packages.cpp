#include "packages.h"

Packages::Packages() {
    tv = 'N';
    rservice = 'N';
}

char Packages::getTV() const{
    return tv;
}

void Packages::setTV(char t) {
    tv = t;
}

char Packages::getServ() const{
    return rservice;
}

void Packages::setServ(char s) {
    rservice = s;
}

void Packages::selection() {
	char x, y;

	cout << "Please select customer package" << endl;
	cout << "Extended TV Service (Y/N): ";
	cin >> x;

	do {
		if (x != 'Y' && x != 'N') {
			cout << "Invalid Entry. Try Again: ";
			cin >> x;
		}
		else {
			break;
		}
	} while (true);

	cout << "Room Service: ";
	cin >> y;

	do {
		if (y != 'Y' && y != 'N') {
			cout << "Invalid Entry. Try Again: ";
			cin >> y;
		}
		else {
			break;
		}
	} while (true);

	this->setTV(x);
	this->setServ(y);
	cout << endl;
}

Packages::~Packages() {}