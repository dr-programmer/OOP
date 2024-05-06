#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <stdlib.h>
#include <typeinfo>

using namespace std;

class Operation {
protected:
	string name;
	string symbol;
public:
	Operation() = default;
	Operation(string name, string symbol) {
		if(name.empty()) throw "Error: cannot assign empty string: name";
		if(symbol.empty()) throw "Error: cannot assign empty string: symbol";
		this->name = name;
		this->symbol = symbol;	
	}
	Operation(const Operation& temp) {
		if(temp.name.empty()) throw "Error: cannot assign empty string: name";
		if(temp.symbol.empty()) throw "Error: cannot assign empty string: symbol";
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
	AddOperation() : Operation("add", "+") {}
	AddOperation(const Operation& temp) : Operation(temp) {}
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
	SubtractOperation() : Operation("sub", "-") {}
	SubtractOperation(const Operation& temp) : Operation(temp) {}
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
	MultiplyOperation() : Operation("mul", "*") {}
	MultiplyOperation(const Operation& temp) : Operation(temp) {}
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
	DivideOperation() : Operation("div", "/") {}
	DivideOperation(const Operation& temp) : Operation(temp) {}
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
	PowerOperation() : Operation("pow", "**") {}
	PowerOperation(const Operation& temp) : Operation(temp) {}
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
	RootOperation() : Operation("root", "V") {}
	RootOperation(const Operation& temp) : Operation(temp) {}
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
	const char *name;
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
		char *temp_name = new char[strlen(name) + 1];
		strcpy(temp_name, name);
		this->name = temp_name;
		this->capacityForOperations = n;
		this->numberOfSupportedOperations = 0;
		operations = new Operation*[n];
		for(unsigned int i = 0; i < n; i++) {
			this->addOperation(ops[i]);
			//cout << &ops[i] << " | " << &this->operations[i] << endl;
		}
	}
	Calculator(const Calculator& temp) : Calculator(temp.name, temp.capacityForOperations, temp.operations) {}
	Calculator& operator=(const Calculator& temp) {
		if(this == &temp) return *this;
		delete [] this->name;
		for(unsigned int i = 0; i < this->numberOfSupportedOperations; i++) {
			//cout << &temp.operations[i] << " | " << &this->operations[i] << endl;
			delete this->operations[i];
		}
		delete [] this->operations;
		char *temp_name = new char[strlen(temp.name) + 1];
		strcpy(temp_name, temp.name);
		this->name = temp_name;
		this->capacityForOperations = temp.capacityForOperations;
		this->numberOfSupportedOperations = 0;
		this->operations = new Operation*[this->capacityForOperations];
		for(unsigned int i = 0; i < temp.numberOfSupportedOperations; i++) {
			this->addOperation(temp.operations[i]);
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
	Calculator& addOperation(const Operation *op) {
		if(this->numberOfSupportedOperations >= this->capacityForOperations) {
			this->capacityForOperations *= 2;
			this->operations = (Operation **)realloc(this->operations, 
					this->capacityForOperations * sizeof(Operation *));
		}
		const type_info& op_type = typeid(*op);
		Operation *temp_operation;
		if(op_type == typeid(AddOperation)) {
			temp_operation = new AddOperation(*op);
		}
		else if(op_type == typeid(SubtractOperation)) {
			temp_operation = new SubtractOperation(*op);
		}
		else if(op_type == typeid(MultiplyOperation)) {
			temp_operation = new MultiplyOperation(*op);
		}
		else if(op_type == typeid(DivideOperation)) {
			temp_operation = new DivideOperation(*op);
		}
		else if(op_type == typeid(PowerOperation)) {
			temp_operation = new PowerOperation(*op);
		}
		else if(op_type == typeid(RootOperation)) {
			temp_operation = new RootOperation(*op);
		}
		this->operations[this->numberOfSupportedOperations++] = temp_operation;
		return *this;
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
				ops[opIndex++] = new AddOperation();
			}
			else if(symbol == "-") {
				ops[opIndex++] = new SubtractOperation();
			}
			else if(symbol == "*") {
				ops[opIndex++] = new MultiplyOperation();
			}
			else if(symbol == "/") {
				ops[opIndex++] = new DivideOperation();
			}
			else if(symbol == "**") {
				ops[opIndex++] = new PowerOperation();
			}
			else if(symbol == "V") {
				ops[opIndex++] = new RootOperation();
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
			cin >> temp;
			getline(cin, name);
			int startIndex = name.find_first_not_of(' ');
			int endIndex = name.find_last_not_of(' ');
			name = name.substr(startIndex, endIndex - startIndex + 1);
			ops[opIndex-1]->setName(name);
			ops[opIndex-1]->setSymbol(symbol);
		}
		if(flag) continue;
		break;
	}
	try {
		Calculator *c = new Calculator(cName.c_str(), opIndex, ops);
		for(; opIndex >= 0; opIndex--) {
			delete ops[opIndex];
		}
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
	} catch(const char *message) { cout << message << endl; }
	return 0;
}
