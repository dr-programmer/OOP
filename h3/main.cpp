#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

// Use only char*, no direct usage of the C++ string is allowed!

class String {
    char* value;
public:
	// Default constructor
	String() { cout << "In defauly constructor" << endl; }

	// Custom constructor
	String(const char * const str) {
		this->value = new char[strlen(str) + 1];
		strcpy(this->value, str);
		cout << "In custom constructor" << endl;
	}

	// Copy constructor
	String(const String& str) {
		this->value = new char[strlen(str.value) + 1];
		strcpy(this->value, str.value);
		cout << "In copy constructor" << endl;
	}

	// Overload operator=
	String& operator=(const String& str) {
		if(this == &str) return *this;
		this->value = new char[strlen(str.value) + 1];
		strcpy(this->value, str.value);
		return *this;
	}

	// Getter and setter
	char *getValue() const {
		return this->value;
	}
	void setValue(char * const str) {
		this->value = str;
	}

	//Destructor
	~String() {
		delete [] this->value;
		cout << "In destructor" << endl;
	}

	// Length method
	// String* str = new String("ABC");
	// cout << str->length() << endl; -> Output should be 3
	int length() const {
		return strlen(this->value);
	}

	// Concat method 
	// String* str = new String("ABC"); 
	// str->concat("abc");
	// cout << str->getValue() << endl; -> Output should be ABCabc
	// If an empty char array is given as argument, then show an error message (or throw an exception)
	void concat(const char * const str) {
		if(!str) { cout << "Error: attempt to concatenate NULL to this->value" << endl; return; }
		this->value = (char *)realloc(this->value, sizeof(char) * (this->length() + strlen(str)) + 1);
		strcat(this->value, str);
	}

	// Replace method
	// String* str = new String("ABC"); 
	// Case 1: 
	// str->replace(1, "DEFGH");
	// cout << str->getValue() << endl; -> Output should be ADEFGHC
	// Case 2:
	// str->replace(0, "DEFGH");
	// cout << str->getValue() << endl; -> Output should be DEFGHBC
	// Case 3:
	// str->replace(2, "DEFGH");
	// cout << str->getValue() << endl; -> Output should be ABDEFGH
	// !!! If the index is out of bounds (< 0 or > length), then show an error message (or throw an exception)
	void replace(const int index, const char * const str) {
		if(!str) { cout << "Error: arrempt to replace a field in this->value with NULL" << endl; return; }
		int thisSize = this->length();
		if(index < 0 || index >= thisSize) { 
			cout << "Error: in function String::replace() - insert index out of bounds" << endl;
			return;
		}
		this->value = (char *)realloc(this->value, sizeof(char) * (thisSize + strlen(str)) + 1);
		char *temp = new char[strlen(str + index + 1)];
		strcpy(temp, this->value + index + 1);
		strcpy(this->value + index, str);
		strcat(this->value, temp);
		delete [] temp;
	}
};

// Write driver code to show every functionality of the class:
// all the constructors, destructor, all methods (except getters and setters)
int main() {
	String *s1 = new String();
	String *s2 = new String("string");
	String *s3 = new String(*s2);
	*s1 = *s3;
	cout << s1->getValue() << " " << s2->getValue() << " " << s3->getValue() << endl;
	cout << s3->length() << endl;
	s3->concat(NULL);
	s3->concat(": Hello, World!");
	cout << s3->getValue() << endl << "size = " << s3->length() << endl;
	s3->replace(3, NULL);
	s3->replace(-1, "-->");
	s3->replace(6, "-->");
	cout << s3->getValue() << endl << "size = " << s3->length() << endl;
	delete s1;
	delete s2;
	delete s3;
	return 0;
}
