#include<stdio.h>
#include<stdlib.h>

struct vector_t {
    int capacity;
    int size;
    int* array;
};

typedef struct vector_t vector;

int *resize(int *arr, int capacity) {
	if(!arr) return NULL;
	int *temp = new int[capacity];
	int oldCapacity = capacity / 2;
	for(int i = 0; i < oldCapacity; i++) {
		temp[i] = arr[i];
	}
	delete [] arr;
	return temp;
}

void initialize_vector(vector* v) {
    for (int i = 0; i < v->size; i++) {
        v->array[i] = i * 5;
    }
}

void print_vector(vector* v) {
    for (int i = 0; i < v->size; i++) {
        printf("%d " , v->array[i]);
    }
    printf("\n");
}

void create_vector(vector* v, int capacity, int size) {
    v->size = size;
    v->capacity = capacity;
    v->array = (int*) malloc(sizeof(int) * size);
}

void add(vector* v, int value) {
    if (v->size == v->capacity) {
        v->capacity = v->capacity * 2;
        v->array = resize(v->array, v->capacity);
    }

    v->array[v->size] = value;
    v->size++;
}

void deleteVector(vector *v) {
	v->capacity = 0;
	v->size = 0;
	delete [] v->array;
	v->array = NULL;
}

void removeFirstElement(vector *v) {
	for(int i = 0; i+1 < v->size; i++) {
		v->array[i] = v->array[i+1];
	}
	v->size--;
}

void removeLastElement(vector *v) {
	v->array[--v->size] = 0;
}

void removeElement(vector *v, int index) {
	if(index >= v->size) fprintf(stderr, "Out of bounds!\n");
	else {
		for(int i = index; i+1 < v->size; i++) {
			v->array[i] = v->array[i+1];
		}
		v->size--;
	}
}

int main() {
    vector v;
    
    const int SIZE = 2;
    const int CAPACITY = 5;
    
    create_vector(&v, CAPACITY, SIZE);
    initialize_vector(&v);
    print_vector(&v);

    add(&v, 1);
    add(&v, 2);
    add(&v, 3);
    add(&v, 4);

    print_vector(&v);

    removeFirstElement(&v);
    print_vector(&v);

    removeLastElement(&v);
    print_vector(&v);

    removeElement(&v, 11);
    removeElement(&v, 2);
    print_vector(&v);

    deleteVector(&v);
    print_vector(&v);

    return 0;
}
