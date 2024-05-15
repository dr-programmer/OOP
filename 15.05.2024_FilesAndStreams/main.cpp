#include <iostream>
#include <fstream>

using namespace std;

class A {
	int num;
	int value;
private:
	void printInfo() const {
		cout << "Num: " << num << "Value: " << value << endl;
	}
	friend void changeFields(A& obj, int num, int value);
};

void changeFields(A& obj, int num, int value) {
	obj.num = num;
	obj.value = value;
}

int main() {
	//ifstream f1("input.txt", ios::in);
	//ofstream f2("output.txt", ios::out | ios::app);
	fstream f("input.txt", ios::in | ios::out | ios::app);
	string a;
	f >> a;
	cout << a;
	f >> a;
	cout << " " << a;
	f << a;
	f.close();
	return 0;
}
