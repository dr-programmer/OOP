#include <iostream>

using namespace std;

class Car {
private:
	string model;
	string make;
	double topSpeed;

public:
	Car() {
		cout << "Default constructor\n";
	}
	Car(string model) {
		cout << "In custom constructor 1\n";
		this->model = model;
	}
	Car(string model, string make, double topSpeed) {
		cout << "In custom constructor 2\n";
		this->model = model;
		this->make = make;
		this->topSpeed;
	}
	string getModel() {
		return this->model;
	}
	void setModel(string model) {
		this->model = model;
	}
	string getMake() {
		return this->make;
	}
	void setMake(string make) {
		this->make = make;
	}
	double getTopSpeed() {
		return topSpeed;
	}
	void setTopSpeed(double topSpeed) {
		this->topSpeed = topSpeed;
	}
	void prinInformation() {
		cout << "======" << this->getModel() << endl;
		cout << "======" << this->getMake() << endl;
		cout << "======" << this->getTopSpeed() << endl;
	}
	~Car() {
		cout << "In default Destructor ...\n";
	}
};

int main() {
	Car *c = new Car();
	Car *c1 = new Car("Arteon");
	string model, make;
	double topSpeed;

	cin >> model;
	cin >> make;
	cin >> topSpeed;

	c->setModel(model);
	c->setMake(make);
	c->setTopSpeed(topSpeed);

	cout << "====== " << c->getModel() << endl;
	cout << "====== " << c->getMake() << endl;
	cout << "====== " << c->getTopSpeed() << endl;
	return 0;
}
