#include <iostream>

using namespace std;

enum City {
	SOFIA,
	PLOVDIV,
	BURGAS
};

class A {
protected:
	int a;
	City city;
public:
	virtual void test() {
		cout << "In A test()" << endl;
	}

	virtual void testAgain() = 0; // -> fully virtual; the class is an Abstract (it cannot have instances)

	// static polymorhpism
	int foo(int x) {
		return x + 5;
	}

	int foo(int x, int y) {
		return x + y;
	}
};

class B : public A {
public:
	void test() override { // override is optional
		cout << "In B test()" << endl;
	}

	void testAgain() {
		cout << "In B testAgain()" << endl;
	}
	void printCity() {
		cout << city << endl; 
	}
};

class C : public A {
public:
	void testAgain() {
		cout << "In C testAgain()" << endl;
	}
};

int main() { /*
	A* a = new A();
	cout << a->foo(10) << endl;
	cout << a->foo(10, 15) << endl;
	a->test();
	*/
	B* b = new B();
	b->test();

	A* a1 = new B();
	a1->test();

	C* a2 = new C();
	a2->test();

	b->printCity();
	return 0;
}
