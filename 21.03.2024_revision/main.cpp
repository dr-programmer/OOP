#include <iostream>

using namespace std;

class Human {
	string firstName;
	string lastName;
public:
	Human() {}
	Human(string firstName) : firstName(firstName) {}
	Human(string firstName, string lastName) : Human(firstName) {
		this->lastName = lastName;
	}
};

int main() {
	Human *h = new Human("Pesho");
	Human *h1 = new Human();
	Human *h2 = new Human("Pesho", "Goshov");
	return 0;
}
