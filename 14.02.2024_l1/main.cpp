#include <iostream>
#include <stdlib.h>

// New types: string, bool

using namespace std;

void foo(int **arr, size_t size) {
	int *newArr = new int[size * 2];
	for(int i = 0; i < size; i++) {
		newArr[i] = (*arr)[i];
	}
	delete [] *arr;
	*arr = newArr;
}

int *allocateMemoryForOneInt() {
	return new int;
}

int main() {
	int *a1 = new int[3];
	a1[0] = 1;
	a1[1] = 2;
	a1[2] = 3;
	foo(&a1, 3);
	int *a = (int *)malloc(sizeof(int) * 10);
	free(a);
	int *b = new int[10];
	delete [] b;
	int *temp = allocateMemoryForOneInt();
	delete temp;
	return 0;
}
