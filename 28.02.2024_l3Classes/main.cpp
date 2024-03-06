#include <iostream>

using namespace std;

class Bachelor {
	int roses;
	bool bald;
	bool rich;

public:

	// Copy constructor
	Bachelor(const Bachelor& bachelor) {
		this->roses = bachelor.roses;
		this->bald = bachelor.bald;
		this->rich = bachelor.rich;
	}

	// Operator
	Bachelor& operator=(const Bachelor& bachelor) {
		if(this == &bachelor) return *this;
		this->roses = bachelor.roses;
		this->bald = bachelor.bald;
		this->rich = bachelor.rich;

		return *this;
	}

	Bachelor() {
		cout << "In default constructor ..." << endl;
	}

	Bachelor(int roses, bool bald, bool rich) {
		cout << "In custom constructor ..." << endl;
		this->roses = roses;
		this->bald = bald;
		this->rich = rich;
	}

	void setRoses(int roses) {
		this->roses = roses;
	}

	void setBald(bool bald) {
		this->bald = bald;
	}

	void setRich(bool rich) {
		this->rich = rich;
	}

	int getRoses() {
		return this->roses;
	}

	bool isBald() {
		return this->bald;
	}

	bool isRich() {
		return this->rich;
	}

	~Bachelor() {
		cout << "In destructor ..." << endl;
	}
};

int main() {
	Bachelor b;
	Bachelor *b1 = new Bachelor(26, 1, 0);
	Bachelor *b2 = new Bachelor(1, 0, 1);
	Bachelor *b3 = new Bachelor(*b1);

	cout << b1 << endl;
	cout << b2 << endl;

	// Shallow copy
	// b2 = b1;
	
	// Deep copy
	*b2 = *b1;

	cout << b2->isBald() << endl;
	cout << b1->isBald() << endl;

	cout << b2 << endl;
	cout << b1 << endl;

	int d = 10;
	int& a = d;
	d = 15;
	cout << a << endl;
	return 0;
}
