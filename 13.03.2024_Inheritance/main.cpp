#include <iostream>

using namespace std;

// inheritance

class Exception {
protected:
	string message;

public:
	Exception() {
		cout << "In Exception constructor" << endl;
		this->message = "empty";
	}

	void throwException() {
		throw string("Invalid argument");
	}
};

class UnsupportedOperationException : public Exception {

public:
	UnsupportedOperationException() {
		cout << "In UnspportedOperationException constructor" << endl;
		cout << message << endl;
	}

	void throwException() {
		throw string("Invalid argument 2");
	}
};

int main() {
	Exception e;
	try {
		e.throwException();
	} catch(string message) {
		cout << message << endl;
	}
	UnsupportedOperationException *test = new UnsupportedOperationException();
	//Exception *test = new UnsupportedOperationException();
	try {
		test->throwException();
		//UnsupportedOperationException::throwException();
	} catch(string message) {
		cout << message << endl; 
	}
	return 0;
}
