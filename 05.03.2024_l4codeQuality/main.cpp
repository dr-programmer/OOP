#include <iostream>

using namespace std;

class Test {
	int value;
public:
	static int t;
	Test() {
		cout << "in" << endl;
		this->value = 10;
		cout << ++t << endl;
	}

	Test(int value) {
		this->value = value;
	}

	Test(const Test& test) {
		this->value = value;
	}

	Test& operator=(const Test& test) {
		if(this == &test) return *this;
		this->value = test.getValue();
		return *this;
	}

	int getValue() const {
		return this->value;
	}

	void setValue(const int value) {
		this->value = value;
	}
};

int Test::t = 5;

static string getMessage() {
	return NULL;
}

int foo() {
	static int a = 0;
	return a++;
}

int main() {
	int a = 10;
	int b = 20;
	int c = 30;
	const int *x = &a;
	int * const y = &b;
	const int * const z = &c;

	for(int i = 0; i < 5; i++) {
		cout << foo() << endl;	
	}

	Test t1;
	Test t2;
	Test t3;
	cout << t1.t << t2.t << t3.t << endl;
	return 0;
}
