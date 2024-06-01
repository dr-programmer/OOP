#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

#define SALARY_MIN 910.00
#define SALARY_MAX 2500.00
#define IS_SALARY_NOT_IN_RANGE(SALARY) SALARY < SALARY_MIN || SALARY > SALARY_MAX

class Employee;

class EmployeePayments {
protected:
	double *salaries;
	unsigned int size;
	unsigned int capacity;
	string employeeName;

	void resize() {
		this->capacity *= 2;
		this->salaries = (double *)realloc(this->salaries, this->capacity * sizeof(double));
	}
public:
	EmployeePayments() {
		employeeName = "";
		capacity = 2;
		size = 1;
		salaries = new double[capacity];
		salaries[0] = SALARY_MIN;
	}
	EmployeePayments(const double * const salaries, 
			 const unsigned int size, 
			 const unsigned int capacity, 
			 const string employeeName)
	{
		this->capacity = capacity;
		this->size = size;
		this->salaries = new double[this->capacity];
		for(unsigned int i = 0; i < this->size; i++) {
			if(IS_SALARY_NOT_IN_RANGE(salaries[i])) 
				throw "cannot create object [EmployeePayments] with given salary not in bounds";
			this->salaries[i] = salaries[i];
		}
		this->employeeName = employeeName;
	}
	EmployeePayments(const EmployeePayments& obj) 
		: EmployeePayments(obj.salaries, obj.size, obj.capacity, obj.employeeName) {}
	EmployeePayments& operator=(const EmployeePayments& obj) {
		if(this == &obj) return *this;
		this->capacity = obj.capacity;
		this->size = obj.size;
		delete [] this->salaries;
		this->salaries = new double[this->capacity];
		for(unsigned int i = 0; i < this->size; i++) {
			this->salaries[i] = obj.salaries[i];
		}
		this->employeeName = obj.employeeName;
		return *this;
	}
	double *getSalaries() const {
		return this->salaries;
	}
	unsigned int getSize() const {
		return this->size;
	}
	unsigned int getCapacity() const {
		return this->capacity;
	}
	string getEmployeeName() const {
		return this->employeeName;
	}
	void addSalary(double salary) {
		if(IS_SALARY_NOT_IN_RANGE(salary)) throw "attempt to push a salary not in bounds";
		if(size == capacity) resize();
		salaries[size++] = salary;
	}
	
	friend istream& operator>>(istream &in, Employee &obj);
};

#define AGE_MAX 65
#define IS_AGE_NOT_IN_RANGE(AGE) AGE < 0 || AGE > AGE_MAX

class Person {
protected:
	string name;
	unsigned int age;
public:
	static unsigned int numberOfPeople;

	Person() = default;
	Person(const string name, const int age) {
		if(name.empty()) throw "cannot create object [Person] with empty name [string]";
		if(IS_AGE_NOT_IN_RANGE(age)) throw "cannot create object [Person] with age not in bounds";
		this->name = name;
		this->age = (unsigned int)age;
		numberOfPeople++;
	}
	Person(const Person& obj) : Person(obj.name, obj.age) {}
	Person& operator=(const Person& obj) {
		if(this == &obj) return *this;
		this->name = obj.name;
		this->age = obj.age;
		return *this;
	}
	string getName() const {
		return this->name;
	}
	unsigned int getAge() const {
		return this->age;
	}
	unsigned int getNumberOfPeople() const {
		return this->numberOfPeople;
	}
	~Person() {
		numberOfPeople--;
	}
};

unsigned int Person::numberOfPeople = 0;

#define EXPERIENCE_MIN 1
#define IS_EXPERIENCE_NOT_IN_RANGE(EXP) EXP < EXPERIENCE_MIN

class Employee : public Person {
protected:
	string position;
	unsigned int experience;
	EmployeePayments salaries{nullptr, 0, 1, ""};
public:
	Employee() = default;
	Employee(const string name, 
		 const int age, 
		 const string position, 
		 const int experience, 
		 EmployeePayments salaries)
		: Person(name, age)
	{
		if(position.empty()) throw "cannot create object [Employee] with empty position [string]";
		if(IS_EXPERIENCE_NOT_IN_RANGE(experience)) 
			throw "cannot create object [Employee] with experience not in bounds";
		this->position = position;
		this->experience = (unsigned int)experience;
		this->salaries = salaries;
	}
	Employee(const Employee& obj) 
		: Employee(obj.name, obj.age, obj.position, obj.experience, obj.salaries) {}
	Employee& operator=(const Employee& obj) {
		if(this == &obj) return *this;
		this->name = obj.name;
		this->age = obj.age;
		this->position = obj.position;
		this->experience = obj.experience;
		this->salaries = obj.salaries;
		return *this;
	}
	string getPosition() const {
		return this->position;
	}
	unsigned int getExperience() const {
		return this->experience;
	}
	EmployeePayments& getSalaries() {
		return this->salaries;
	}
	double calculateAverageSalary() const {
		double *values = salaries.getSalaries();
		unsigned int size = salaries.getSize();
		double average = 0;
		for(unsigned int i = 0; i < size; i++) {
			average += values[i];
		}
		return average / size;
	}

	friend istream& operator>>(istream &in, Employee &obj);
	friend ostream& operator<<(ostream &out, Employee &obj);
};

istream& operator>>(istream &in, Employee &obj) {
	string name, firstName, lastName;
	in >> firstName >> lastName;
	name = firstName + " " + lastName;
	int age;
	in >> age;
	string position;
	in >> position;
	int experience;
	in >> experience;
	if(name.empty()) throw "cannot give empty name to employee";
	if(IS_AGE_NOT_IN_RANGE(age)) throw "employee age out of bounds";
	if(position.empty()) throw "cannot give empty position to employee";
	if(IS_EXPERIENCE_NOT_IN_RANGE(experience)) throw "employee experience out of bounds";
	obj.name = name;
	obj.age = age;
	obj.position = position;
	obj.experience = experience;
	obj.salaries.employeeName = name;
	cout << name << age << position << experience << endl;
	return in;
}
ostream& operator<<(ostream &out, Employee &obj) {
	out 
	<< obj.name 
	<< " " << obj.age 
	<< " " << obj.position 
	<< " " << obj.experience 
	<< " " << obj.calculateAverageSalary() 
	<< endl;
	return out;
}

#define IS_DEPARTMENT_NOT_VALID(DEP) DEP != "delivery" \
					     && DEP != "marketing" \
					     && DEP != "sales" \
					     && DEP != "human resources"

class Manager : public Person {
protected:
	string department;
public:
	Manager() = default;
	Manager(const string name, const int age, const string department) : Person(name, age) {
		if(department.empty()) throw "cannot create object [Manager] with department [string] empty";
		if(IS_DEPARTMENT_NOT_VALID(department)) 
			throw "cannot create object [Manager] with invalid department [string]";
		this->department = department;
	}
	Manager(const Manager& obj) : Manager(obj.name, obj.age, obj.department) {}
	Manager& operator=(const Manager& obj) {
		if(this == &obj) return *this;
		this->name = obj.name;
		this->age = obj.age;
		this->department = obj.department;
		return *this;
	}
	string getDepartment() const {
		return this->department;
	}
	void payEmployeeByName(const string employeeName, vector<Employee> &employees, const double salary) {
		unsigned short added = 0;
		for(auto &e : employees) {
			if(e.getName() == employeeName) {
				added = 1;
				e.getSalaries().addSalary(salary);
			}
		}
		if(added == 0) throw "attempt to give salary [double] to non-existing employee [Employee]";
	}

	friend istream& operator>>(istream &in, Manager &obj);
	friend ostream& operator<<(ostream &out, Manager &obj);
};

istream& operator>>(istream &in, Manager &obj) {
	string name, firstName, lastName;
	in >> firstName >> lastName;
	name = firstName + " " + lastName;
	int age;
	in >> age;
	string department;
	in >> department;
	if(department == "human") {
		string temp;
		in >> temp;
		department += " " + temp;
	}
	if(name.empty()) throw "cannot give empty name to manager";
	if(IS_AGE_NOT_IN_RANGE(age)) throw "manager age out of bounds";
	if(department.empty()) throw "cannot give empty department to manager";
	obj.name = name;
	obj.age = age;
	obj.department = department;
	cout << name << age << department << endl;
	return in;
}
ostream& operator<<(ostream &out, Manager &obj) {
	out << obj.name << " " << obj.age << " " << obj.department << endl;
	return out;
}

class FileManager {
protected:
	const string ifile;
	const string ofile;

	vector<Manager> managers;
	vector<Employee> employees, delivery, marketing, sales, human_resources;
public:
	FileManager(const string ifile, const string ofile) : ifile(ifile), ofile(ofile) {}
	void read() {
		ifstream file(ifile);
		string line;
		while(getline(file, line)) {
			stringstream sLine(line);
	
			string type;
			sLine >> type;
			if(type == "e") {
				Employee temp_e;
				temp_e.numberOfPeople++;
				sLine >> temp_e;
				employees.push_back(temp_e);
			}
			else if(type == "m") {
				Manager temp_m;
				temp_m.numberOfPeople++;
				sLine >> temp_m;
				managers.push_back(temp_m);
				string temp_string;
				while(sLine >> temp_string) {
					Employee e;
					string e_name(temp_string);
					sLine >> temp_string;
					e_name += " " + temp_string;
					for(auto &emp : employees) {
						if(emp.getName() == e_name) {
							e = emp;
						}
					}
					string department = temp_m.getDepartment();
					sLine >> temp_string;
					double salary;
					try {
						salary = stod(temp_string);
					} catch(const char * const str) { cout << str << endl; }
					if(department == "delivery") {
						unsigned short found = 0;
						for(auto &temp : delivery) {
							if(temp.getName() == e_name) found = 1;
						}
						if(!found) delivery.push_back(e);
						managers.back().payEmployeeByName(e_name, delivery, salary);
						cout << "Salary: " << salary << endl;
						cout << delivery[0].getSalaries().getEmployeeName() << endl;
					}
					else if(department == "marketing") {
						unsigned short found = 0;
						for(auto &temp : marketing) {
							if(temp.getName() == e_name) found = 1;
						}
						if(!found) marketing.push_back(e);
						managers.back().payEmployeeByName(e_name, marketing, salary);
					}
					else if(department == "sales") {
						unsigned short found = 0;
						for(auto &temp : sales) {
							if(temp.getName() == e_name) found = 1;
						}
						if(!found) sales.push_back(e);
						managers.back().payEmployeeByName(e_name, sales, salary);

					}
					else if(department == "human resources") {
						unsigned short found = 0;
						for(auto &temp : human_resources) {
							if(temp.getName() == e_name) found = 1;
						}
						if(!found) human_resources.push_back(e);
						managers.back().payEmployeeByName(e_name, human_resources, salary);

					}

				}
			}
			else throw "attempt to read undefined person type";
		}
		file.close();
	}
	void write() {
		ofstream file(ofile, ios::trunc);
		for(auto &m : managers) {
			string department = m.getDepartment();
			file << m;
			if(department == "delivery") {
				for(auto &d : delivery) {
					file << "\t";
					file << d;
				}
			}
			else if(department == "marketing") {
				for(auto &m : marketing) {
					file << "\t";
					file << m;
				}
			}
			else if(department == "sales") {
				for(auto &s : sales) {
					file << "\t";
					file << s;
				}
			}
			else if(department == "human resources") {
				for(auto &h : human_resources) {
					file << "\t";
					file << h;
				}
			}
		}
	}
};

int main() {
	try {
		FileManager fileManager("ifile.txt", "ofile.txt");
		fileManager.read();
		fileManager.write();
	} catch(const char * const message) {
		cout << "Error: " << message << endl;
	}
	return 0;
}
