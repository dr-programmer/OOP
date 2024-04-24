#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <climits>
#include <stdlib.h>

using namespace std;

class Operation {
protected:
	string name;
	string symbol;
public:
	Operation(string name, string symbol) {
		if(name.empty()) throw "Error: cannot assign empty string: name";
		if(symbol.empty()) throw "Error: cannot assign empty string: symbol";
		this->name = name;
		this->symbol = symbol;	
	}
	Operation(const Operation& temp) {
		if(name.empty()) throw "Error: cannot assign empty string: name";
		if(symbol.empty()) throw "Error: cannot assign empty string: symbol";
		this->name = temp.name;
		this->symbol = temp.symbol;
	}
	Operation& operator=(const Operation& temp) {
		if(this == &temp) return *this;
		this->name = temp.name;
		this->symbol = temp.symbol;
		return *this;
	}
	virtual double execute(const double d1, const double d2) = 0;
	string getName() const {
		return this->name;
	}
	string getSymbol() const {
		return this->symbol;
	}
	void setName(string name) {
		if(name.empty()) throw "Error: cannot assign empty string: name";
		this->name = name;
	}
	void setSymbol(string symbol) {
		if(symbol.empty()) throw "Error: cannot assign empty string: symbol";
		this->symbol = symbol;
	}
};

class AddOperation : public Operation {
public:
	AddOperation(string name, string symbol) : Operation(name, symbol) {}
	AddOperation(const AddOperation& temp) : Operation(temp) {}
	AddOperation& operator=(const AddOperation& temp) {
		if(this == &temp) return *this;
		this->name = temp.name;
		this->symbol = temp.symbol;
		return *this;
	}
	double execute(const double d1, const double d2) {
		return d1 + d2;
	}
};

class SubtractOperation : public Operation {
public:
	SubtractOperation(string name, string symbol) : Operation(name, symbol) {}
	SubtractOperation(const SubtractOperation& temp) : Operation(temp) {}
	SubtractOperation& operator=(const SubtractOperation& temp) {
		if(this == &temp) return *this;
		this->name = temp.name;
		this->symbol = temp.symbol;
		return *this;
	}
	double execute(const double d1, const double d2) {
		return d1 - d2;
	}
};

class MultiplyOperation : public Operation {
public:
	MultiplyOperation(string name, string symbol) : Operation(name, symbol) {}
	MultiplyOperation(const MultiplyOperation& temp) : Operation(temp) {}
	MultiplyOperation& operator=(const MultiplyOperation& temp) {
		if(this == &temp) return *this;
		this->name = temp.name;
		this->symbol = temp.symbol;
		return *this;
	}
	double execute(const double d1, const double d2) {
		return d1 * d2;
	}
};

class DivideOperation : public Operation {
public:
	DivideOperation(string name, string symbol) : Operation(name, symbol) {}
	DivideOperation(const DivideOperation& temp) : Operation(temp) {}
	DivideOperation& operator=(const DivideOperation& temp) {
		if(this == &temp) return *this;
		this->name = temp.name;
		this->symbol = temp.symbol;
		return *this;
	}
	double execute(const double d1, const double d2) {
		return d1 / d2;
	}
};

class PowerOperation : public Operation {
public:
	PowerOperation(string name, string symbol) : Operation(name, symbol) {}
	PowerOperation(const PowerOperation& temp) : Operation(temp) {}
	PowerOperation& operator=(const PowerOperation& temp) {
		if(this == &temp) return *this;
		this->name = temp.name;
		this->symbol = temp.symbol;
		return *this;
	}
	double execute(const double d1, const double d2) {
		return pow(d1, d2);
	}
};

class RootOperation : public Operation {
public:
	RootOperation(string name, string symbol) : Operation(name, symbol) {}
	RootOperation(const RootOperation& temp) : Operation(temp) {}
	RootOperation& operator=(const RootOperation& temp) {
		if(this == &temp) return *this;
		this->name = temp.name;
		this->symbol = temp.symbol;
		return *this;
	}
	double execute(const double d1, const double d2) {
		if(d1 < 0 || d2 < 0) throw "Error: cannot root negative numbers";
		return pow(d1, 1/d2);
	}
};

class Calculator {
protected:
	char *name;
	size_t numberOfSupportedOperations;
	size_t capacityForOperations;
	Operation **operations;
	static double numberOfSuccessfulCalculations;
public:
	Calculator() {
		capacityForOperations = 2;
		operations = new Operation*[2];
		name = new char[1];
	}
	Calculator(const char *name, size_t n, Operation **ops) {
		if(n < 1) throw "Error: operation capacity less than 1";
		if(name == nullptr || name[0] == '\0') throw "Error: empty name";
		if(ops == nullptr) throw "Error: ops given as nullptr";
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
		this->capacityForOperations = n;
		this->numberOfSupportedOperations = n;
		operations = new Operation*[n];
		if(ops != NULL) for(unsigned int i = 0; i < n; i++) {
			operations[i] = ops[i];
		}
	}
	Calculator(const Calculator& temp) : Calculator(temp.name, temp.capacityForOperations, temp.operations) {}
	Calculator& operator=(const Calculator& temp) {
		if(this == &temp) return *this;
		this->name = new char[strlen(temp.name) + 1];
		strcpy(this->name, temp.name);
		this->capacityForOperations = temp.capacityForOperations;
		this->numberOfSupportedOperations = temp.numberOfSupportedOperations;
		this->operations = new Operation*[this->capacityForOperations];
		if(temp.operations != NULL) for(unsigned int i = 0; i < temp.numberOfSupportedOperations; i++) {
			this->operations[i] = temp.operations[i];
		}
		return *this;
	}
	~Calculator() {
		for(unsigned int i = 0; i < numberOfSupportedOperations; i++) {
			delete operations[i];
		}
		delete [] operations;
		delete [] name;
	}
	void listSupportedOperations() {
		for(unsigned int i = 0; i < this->numberOfSupportedOperations; i++) {
			cout << this->operations[i]->getSymbol() << " - " << this->operations[i]->getName() << endl;
		}
	}
	void listInputFormat() {
		cout << "<num1>  <symbol>  <num2> … <numN> = \\n" << endl;
	}
	void addOperation(const Operation *op) {
		if(this->numberOfSupportedOperations >= this->capacityForOperations) {
			this->capacityForOperations *= 2;
			this->operations = (Operation **)realloc(this->operations, 
					this->capacityForOperations * sizeof(Operation *));
		}
		this->operations[this->numberOfSupportedOperations++] = (Operation *)op;
	}
	void startCalculating() {
		string temp;
		double result;
		cin >> temp;
		//cout << "Init: " << temp << endl;
		try {
			result = stod(temp);
		} catch(invalid_argument) {
			cout << "Error parsing input" << endl;
			return;
		}
		while(1) {
			cin >> temp;
			//cout << "Temp = " << temp << endl;
			if(temp == "=") break;
			char flag = 0;
			for(unsigned int i = 0; i < this->numberOfSupportedOperations; i++) {
				if(operations[i]->getSymbol() == temp) {
					flag = 1;
					cin >> temp;
					double secondValue;
					try {
						secondValue = stod(temp);
					} catch(invalid_argument) {
						cout << "Error parsing input" << endl;
						return;
					}
					result = operations[i]->execute(result, secondValue);
					break;
				}
			}
			if(!flag) {
				cout << "Error parsing input" << endl;
				return;
			}

		}
		this->numberOfSuccessfulCalculations++;
		cout << result << endl;
	}
};

double Calculator::numberOfSuccessfulCalculations = 0;

int main() {
	string cName;
	Operation *ops[10] = {0};
	int opIndex = 0;
	while(1) {
		cout << "Enter calculator's name: ";
		getline(cin, cName);
		cout << "Enter operations: (End input with 'end')" << endl;
		string symbol, temp, name;
		int flag = 0;
		while(1) {
			cin >> symbol;
			if(symbol == "+") {
				cin >> temp >> name;
				ops[opIndex++] = new AddOperation(name, symbol);
			}
			else if(symbol == "-") {
				cin >> temp >> name;
				ops[opIndex++] = new SubtractOperation(name, symbol);
			}
			else if(symbol == "*") {
				cin >> temp >> name;
				ops[opIndex++] = new MultiplyOperation(name, symbol);
			}
			else if(symbol == "/") {
				cin >> temp >> name;
				ops[opIndex++] = new DivideOperation(name, symbol);
			}
			else if(symbol == "**") {
				cin >> temp >> name;
				ops[opIndex++] = new PowerOperation(name, symbol);
			}
			else if(symbol == "V") {
				cin >> temp >> name;
				ops[opIndex++] = new RootOperation(name, symbol);
			}
			else if(symbol == "end") break;
			else {
				flag = 1;
				char buffer[100];
				fgets(buffer, 100, stdin);
				for(; opIndex >= 0; opIndex--) {
					delete ops[opIndex];
				}
				break;
			}
		}
		if(flag) continue;
		break;
	}
	Calculator *c = new Calculator(cName.c_str(), opIndex, ops);
	while(1) {
		cout << "1: List supported Operations" << endl;
		cout << "2: List input format" << endl;
		cout << "3: Start calculating" << endl;
		cout << "4: Exit" << endl;
		string sInput;
		int input = 0;
		cin >> sInput;
		try {
			input = stod(sInput);
		} catch(invalid_argument) {
			continue;
		}
		switch(input) {
			case 1:
				c->listSupportedOperations();
				break;
			case 2:
				c->listInputFormat();
				break;
			case 3:
				c->startCalculating();
				char buff[100];
				fgets(buff, 100, stdin);
				break;
			case 4:
				delete(c);
				exit(0);
			default:
				fgets(buff, 100, stdin);
				continue;
		}
	}
	return 0;
}
