#include <iostream>
#include <cstring>
#include <exception>
#include <string>

using namespace std;

class Registry
{
protected:
	char *registryName;
	string *records;
	size_t numberOfRecords;

public:
	static int numberOfActiveRegistries;
	Registry() {
		registryName = new char[1];
		records = new string[2];
		numberOfRecords = 2;
		numberOfActiveRegistries++;
	}

    Registry(const char *registryName, const string *records, size_t numberOfRecords) {
	    if(numberOfRecords <= 0) throw "Error - <= 0!";
	    if(records == nullptr || registryName == nullptr) throw "Error - nullptr!";
	    this->registryName = (char *)registryName;
	    this->records = (string *)records;
	    this->numberOfRecords = numberOfRecords;
	    numberOfActiveRegistries++;

    }

    Registry(const Registry &other) {
	this->registryName = other.registryName;
	this->records = other.records;
	this->numberOfRecords = other.numberOfRecords;
        numberOfActiveRegistries++;

    }

    ~Registry() {
	delete [] records;
	delete [] registryName;
	numberOfActiveRegistries--;
    }

    Registry &operator=(const Registry &other) {
	if(this == &other) return *this;
	this->registryName = other.registryName;
	this->records = other.records;
	this->numberOfRecords = other.numberOfRecords;
	return *this;
    }

    static int getActiveRegistries() {
        return numberOfActiveRegistries;
    }

    void printRegistryInformation() const {
	cout << registryName << endl;
	for(size_t i = 0; i < numberOfRecords; i++) {
		cout << records[i] << endl;
	}
    }
};

class PhoneRegistry : public Registry
{
    string *phoneNumbers;
    size_t numberOfPhoneNumbers;

public:
    PhoneRegistry(const char *registryName, const string *records, size_t numberOfRecords, const string *phoneNumbers, size_t numberOfPhoneNumbers) : Registry(registryName, records, numberOfRecords){
	if(numberOfPhoneNumbers <= 0) throw "Error - <= 0!";
	if(phoneNumbers == nullptr) throw "Error - nullptr!";
	this->phoneNumbers = (string *) phoneNumbers;
	this->numberOfPhoneNumbers = numberOfPhoneNumbers;
    }

    PhoneRegistry(const PhoneRegistry &other) : Registry(other.registryName, other.records, other.numberOfRecords){
	this->phoneNumbers = other.phoneNumbers;
	this->numberOfPhoneNumbers = other.numberOfPhoneNumbers;
    }

    ~PhoneRegistry() {
	delete [] phoneNumbers;
	delete [] records;
	delete [] registryName;
    }

    PhoneRegistry &operator=(const PhoneRegistry &other) {
	if(this == &other) return *this;
	this->registryName = other.registryName;
	this->records = other.records;
	this->numberOfRecords = other.numberOfRecords;
	this->phoneNumbers = other.phoneNumbers;
	this->numberOfPhoneNumbers = other.numberOfPhoneNumbers;
	return *this;
    }

    void printRegistryInformation() const {
	cout << registryName << endl;
	for(size_t i = 0; i < numberOfRecords; i++) {
		cout << records[i] << " ";
		if(i < numberOfPhoneNumbers) cout << phoneNumbers[i] << endl;
		else cout << "-" << endl;
	}
    }
};

int Registry::numberOfActiveRegistries = 0;

int main() {
	string records[] = {"ha", "hi", "hz"};
	Registry *r = new Registry("Hello", records, 3);
	r->printRegistryInformation();
	string phones[] = {"111", "222"};
	PhoneRegistry *test = new PhoneRegistry("Hello", records, 3, phones, 2);
	test->printRegistryInformation();
	cout << "Ready" << endl;
	return 0;
}
