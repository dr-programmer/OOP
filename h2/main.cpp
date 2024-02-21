#include<iostream>

using namespace std;

class Vector {
private:
	int capacity;
	int size;
	int *array;

	void resize() {
		int *temp = new int[capacity];
		int oldCapacity = this->capacity / 2;
		for(int i = 0; i < oldCapacity; i++) {
			temp[i] = this->array[i];
		}
		delete [] this->array;
		this->array = temp;
	}

public:
	Vector(int capacity, int size) {
	    this->size = size;
	    this->capacity = capacity;
	    this->array = (int*) malloc(sizeof(int) * size);
	}

	void setCapacity(int capacity) {
		this->capacity = capacity;
		this->resize();
	}

	int getCapacity() {
		return this->capacity;
	}

	void setSize(int size) {
		this->size = size;
	}

	int getSize() {
		return this->size;
	}

	void print() {
	    for (int i = 0; i < this->size; i++) {
		printf("%d " , this->array[i]);
	    }
	    printf("\n");
	}

	void add(int value) {
	    if (this->size == this->capacity) {
		this->capacity = this->capacity * 2;
		this->resize();
	    }

	    this->array[this->size] = value;
	    this->size++;
	}

	void removeFirstElement() {
		for(int i = 0; i+1 < this->size; i++) {
			this->array[i] = this->array[i+1];
		}
		this->size--;
	}

	void removeLastElement() {
		this->array[--this->size] = 0;
	}

	void removeElement(int index) {
		if(index >= this->size) fprintf(stderr, "Out of bounds!\n");
		else {
			for(int i = index; i+1 < this->size; i++) {
				this->array[i] = this->array[i+1];
			}
			this->size--;
		}
	}

	~Vector() { delete [] this->array; }
};

int main() {
	const int SIZE = 0;
	const int CAPACITY = 5;

	Vector *v = new Vector(CAPACITY, SIZE);

	int count;
	cin >> count;
	for(int i = 0; i < count; i++) {
		int value;
		cin >> value;
		v->add(value);
	}
	v->print();
	cout << v->getCapacity() << endl;
	cout << v->getSize() << endl;
	v->add(11);
	v->print();
	v->removeFirstElement();
	v->print();
	v->removeLastElement();
	v->print();
	v->removeElement(1);
	v->print();
	delete v;
	return 0;
}

