#include <fstream>
#include "price.h"

int menuSelection();			// Function definitions
void roomSelection(int*, int*);
void showGuests(Room*);
void guestRecord(Room*, int*);
void editGuest(Room*);
void removeGuest(Room*, int*);
void billCustomer(Room*);
void writeBill(Price*);
char confirmation();

int main() {
	int* function = new int();		// Declaring variables using dynamic memory allocation
	int* floor = new int();
	int* number = new int();
	int* guests = new int(0);
	char confirm;
	Customer* n = new Customer();
	Packages* p = new Packages();

	Room* rooms = new Room[2 * 8];			// Creating 2D array for rooms using dynamic memory allocation
	(rooms + 1 * 8 + 7)->setType("VIP");

	cout << "Welcome to Best Eastern's Hotel Program" << endl;

	do {
		*function = menuSelection();		// Get user selection

		if (*function == 1) {			// If input is 1 add new customer info
			if (*guests < 16) {			// Check to see if hotel is full
				n->info();				// Get guest info 

				do {					// Loop for confirmation of user info
					n->print();												// Print guest info for confirmation
					cout << "Is this information correct? (Y/N): ";

					confirm = confirmation();		// Error checking confirmation

					if (confirm == 'N') {		// If confirmation is denied re-enter info
						n->info();
					}
					else {
						break;			// Break loop if confirmation is approved
					}
				} while (true);

				p->selection();

				roomSelection(floor, number);													// Get desired floor and room number
				cout << "Customer has selected room: " << *floor << "0" << *number << endl;		// Output room

				if (*floor == 2 && *number == 8) {									// Check for VIP suite selection
					cout << "This is a VIP room. Is this okay? (Y/N): ";			// Ask confirmation of VIP

					confirm = confirmation();				// Error checking confirmation

					if (confirm == 'N') {					// If VIP is not wanted re-select room
						roomSelection(floor, number);
					}
				}
				if ((rooms + (*floor - 1) * 8 + (*number - 1))->getName() != "") {			// Check for room occupancy
					cout << "Room is already occupied. Please choose another" << endl;
					roomSelection(floor, number);											// Re-select room
				}
				*(rooms + (*floor - 1) * 8 + (*number - 1)) = *(rooms + (*floor - 1) * 8 + (*number - 1)) + n;		// If everything is confirmed with no restrictions add guest to room using overloaded operator
				*(rooms + (*floor - 1) * 8 + (*number - 1)) = *(rooms + (*floor - 1) * 8 + (*number - 1)) + p;
				cout << "Customer has been added to system" << endl;												// Output that addition was successful

				(*guests)++;		// Increase number guests currently in hotel
			}
			else {
				cout << "Hotel is currently full" << endl;
			}
		}
		if (*function == 2) {				// If input is 2 view current customers info and room number
			if (*guests > 0) {				// Check if any guests are there
				showGuests(rooms);			// Function to display info
			}
			else {
				cout << "The hotel is currently empty" << endl;			// Output if there are no guests
			}
		}
		if (*function == 3) {
			if (*guests > 0) {				// Check if any guests are there
				guestRecord(rooms, guests);
			}
			else {
				cout << "The hotel is currently empty" << endl;			// Output if there are no guests
			}
		}
		if (*function == 4) {				// If input is 4 bill customer 
			if (*guests > 0) {				// Check if any guests are there
				billCustomer(rooms);		// Function to bill customer
			}
			else {
				cout << "The hotel is currently empty. Cannot print bill" << endl;			// Output if there are no guests
			}
		}
		if (*function == 5) {			// If input is 5 exit program loop
			break;
		}

	} while (true);

	delete[] rooms;										// Delete 2D array
	delete function, floor, number, guests, n;			// Delete variables
	return 0;											// Exit program
}

int menuSelection() {
	int choice;			// Create choice variable

	do {
		cout << endl << "Please select an option" << endl << "\t1. Customer Reservations" << endl << "\t2. View Current Guests" << endl
			<< "\t3. Change Guest Record" << endl << "\t4. Bill Customer" << endl << "\t5. Exit" << endl;
		cin >> choice;

		if (choice > 5 || choice < 1) {
			cout << endl << "Error: invalid option - must be between 1 and 5" << endl;		// Check if choice is an option, if not re-choose
		}
		else {
			break;			// Exit loop if choice is available
		}
	} while (true);
	cout << endl;

	return choice;		// Send choice back
}

void roomSelection(int* floor, int* number) {		// Function is self-explanatory
	int f, n;

	cout << "Please choose a floor (1 or 2): ";

	do {
		cin >> f;

		if (f != 1 && f != 2) {
			cout << "Invalid Entry - Try Again: ";
		}
		else {
			break;
		}
	} while (true);

	cout << "Please choose a room (1 to 8): ";

	do {
		cin >> n;

		if (n < 1 || n > 8) {
			cout << "Invalid Entry - Try Again: ";
		}
		else {
			break;
		}
	} while (true);

	*floor = f;
	*number = n;
}

void showGuests(Room* rooms) {
	ofstream input("status.txt");

	cout << "Current Room Information" << endl;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 8; j++) {											// Cycle through all rooms
			input << "Room Number: " << i+1 << "0" << j+1 << endl;
			input << (rooms + i * 8 + j);

			if ((rooms + i * 8 + j)->getName() != "") {							// If room isnt empty output info and room number
				cout << "Room Number: " << i + 1 << '0' << j + 1 << endl;
				(rooms + i * 8 + j)->print();
			}
		}
	}

	input.close();
}

void guestRecord(Room* rooms, int* guests) {
	int* choice = new int;

	do {
		cout << "Please select an option" << endl << "\t1. Edit Guest Reservation" << endl << "\t2. Remove Guest Reservation" << endl;
		cin >> *choice;

		if (*choice > 2 || *choice < 1) {
			cout << endl << "Error: invalid option - must be between 1 or 2" << endl;		// Check if choice is an option, if not re-choose
		}
		else {
			break;			// Exit loop if choice is available
		}
	} while (true);
	cout << endl;

	if (*choice == 1) {
		editGuest(rooms);
	}
	else {
		removeGuest(rooms, guests);
	}
}

void editGuest(Room* rooms) {
	int* check = new int(0);				// Create variable with dynamic memory allocation
	int* extend = new int;
	char confirm;
	string* name = new string();

	cout << "Please enter the name of customer to edit: ";		// Enter customer to be edited
	cin >> *name;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 8; j++) {									// Cycle through rooms for customer
			if ((rooms + i * 8 + j)->getName() == *name) {				// If found continue editing
				cout << "How many days would you wish to extend " << *name << "'s reservation?: ";
				cin >> *extend;

				*(rooms + i * 8 + j) = *(rooms + i * 8 + j) + extend;
				cout << "Reservation has been extended " << *extend << " days. New departure is: " << (rooms + i * 8 + j)->getDeparture() << endl;

				cout << endl << "Do you wish to change package details?: ";

				confirm = confirmation();

				if (confirm == 'Y') {
					(rooms + i * 8 + j)->selection();
					cout << "Package details have been updated" << endl;
				}
			}
			else {
				(*check)++;		// If room is empty increase check
			}
		}
	}
	if (*check == 16) {			// If check reaches max rooms, output that no customers were found
		cout << "No current customers match that name" << endl;
	}

	delete check, name;		// Delete remaining variables	
}

void removeGuest(Room* rooms, int* guests) {
	int* check = new int(0);				// Create variable with dynamic memory allocation
	char confirm;
	string* name = new string();

	cout << "Please enter the name of customer being removed: ";		// Enter customer to be removed
	cin >> *name;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 8; j++) {									// Cycle through rooms for customer
			if ((rooms + i * 8 + j)->getName() == *name) {				// If found continue removal process
				cout << "You are removing " << *name << "'s reservation. Are you sure?: ";

				confirm = confirmation();

				if (confirm == 'Y') {
					(rooms + i * 8 + j)->clear();						// Remove guest
					(*guests)--;
					cout << "Reservation has been removed" << endl;
				}
				else {
					cout << "Removal has been cancelled" << endl;
				}
			}
			else {
				(*check)++;		// If room is empty increase check
			}
		}
	}
	if (*check == 16) {			// If check reaches max rooms, output that no customers were found
		cout << "No current customers match that name" << endl;
	}

	delete check, name;		// Delete remaining variables	
}

void billCustomer(Room* rooms) {
	int* check = new int(0);				// Create variable with dynamic memory allocation
	char confirm;
	string* name = new string();
	Discount* d = new Discount();

	cout << "Please enter the name of customer being billed: ";		// Enter customer to be billed
	cin >> *name;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 8; j++) {									// Cycle through rooms for customer
			if ((rooms + i * 8 + j)->getName() == *name) {				// If found continue billing process
				cout << "Is there a company discount (Y/N): ";			
				
				confirm = confirmation();								// Error checking confirmation

				d->setCompany(confirm);									// Set company discount
				cout << *d << endl;										// Output whether company discount has been applied using overloaded operator

				Price* p = new Price((rooms + i * 8 + j), d);			// Create price object using constructor with room object and discount object and dynamic memory allocation

				p->print();												// Output price before disocunt and tax using polymorphism
				cout << "The customer's total after tax and discounts is: $" << p->discount() << endl;		// Output price after using discount function
				writeBill(p);

				delete p;		// Delete price object
			}
			else {
				(*check)++;		// If room is empty increase check
			}
		}
	}
	if (*check == 16) {			// If check reaches max rooms, output that no customers were found
		cout << "No current customers match that name" << endl;
	}

	delete check, name, d;		// Delete remaining variables
}

void writeBill(Price* p) {
	ofstream input("bill.txt", ios::app);

	input << p;

	input.close();
}

char confirmation() {
	char confirm;

	do {						// Loop for error checking when inputting confirmation
		cin >> confirm;			// Get confirmation
		cout << endl;

		if (confirm != 'Y' && confirm != 'N') {
			cout << "Error: invalid option - must be Y or N. Try again: ";		// Re-enter if different from Y or N
		}
		else {
			break;			// Exit loop if correct response
		}
	} while (true);

	return confirm;
}