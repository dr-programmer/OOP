#include <iostream>
#include <string>

using namespace std;

enum EngineType {
	PETROL,
	DIESEL,
	ELECTRIC,
	HYBRID
};

class Vehicle {
protected:
	int year;
	enum EngineType engineType;
public:
	virtual void printInfo() = 0;
	Vehicle(int year, enum EngineType engineType) {
		this->year = year;
		this->engineType = engineType;
	}
	virtual ~Vehicle() {}
};

enum City {
	MILAN,
	SOFIA,
	PLOVDIV
};

enum Country {
	BULGARIA,
	ITALY,
	SPAIN
};

class Car : public Vehicle {
protected:
	string model;
	string make;
	double horsepower;
public:
	Car(int year, enum EngineType engineType, string model, string make, double horsepower) 
		: Vehicle(year, engineType)
	{
		this->model = model;
		this->make = make;
		this->horsepower = horsepower;
	}
	~Car() {}
	void printInfo() {
		cout << this->model << this->make << this->horsepower << this->year << this->engineType << endl;
	}
};

class Train : public Vehicle {
protected:
	int seatNumber;
	enum City startPoint;
	enum City endPoint;
public:
	Train(int year, enum EngineType engineType, int seatNumber, enum City sP, enum City eP) 
		: Vehicle(year, engineType)
	{
		this->seatNumber = seatNumber;
		this->startPoint = sP;
		this->endPoint = eP;
	}
	~Train() {}
	void printInfo() {
		cout << this->seatNumber
		       	<< this->startPoint 
			<< this->endPoint << this->year << this->engineType << endl;
	}
};

class Plain : public Vehicle {
protected:
	int seatNumber;
	enum Country startPoint;
	enum Country endPoint;
public:
	Plain(int year, enum EngineType engineType, int sN, enum Country sP, enum Country eP) 
		: Vehicle(year, engineType)
	{
		this->seatNumber = sN;
		this->startPoint = sP;
		this->endPoint = eP;
	}
	~Plain() {}
	void printInfo() {
		cout << this->seatNumber
		       	<< this->startPoint 
			<< this->endPoint << this->year << this->engineType << endl;
	}
};

int main() {
	Vehicle *v1 = new Car(2000, HYBRID, "car", "fast", 1000);
	v1->printInfo();
	Vehicle *v2 = new Train(2000, ELECTRIC, 1, SOFIA, PLOVDIV);
	v2->printInfo();
	Vehicle *v3 = new Plain(2000, PETROL, 3, BULGARIA, ITALY);
	v3->printInfo();
	return 0;
}
