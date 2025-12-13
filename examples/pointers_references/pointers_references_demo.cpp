#include <iostream>
using namespace std;

void incrementByValue(int x) {
    x++;
    cout << "Inside incrementByValue: x = " << x << endl;
}

void incrementByReference(int& x) {
    x++;
    cout << "Inside incrementByReference: x = " << x << endl;
}

void incrementByPointer(int* x) {
    (*x)++;
    cout << "Inside incrementByPointer: *x = " << *x << endl;
}

int main() {
    cout << "=== Pointers and References Demo ===\n" << endl;

    // Basic pointers
    cout << "1. Basic Pointers:" << endl;
    int x = 10;
    int* ptr = &x;

    cout << "x = " << x << endl;
    cout << "&x = " << &x << endl;
    cout << "ptr = " << ptr << endl;
    cout << "*ptr = " << *ptr << endl;

    // Modifying through pointer
    *ptr = 20;
    cout << "After *ptr = 20:" << endl;
    cout << "x = " << x << endl;
    cout << "*ptr = " << *ptr << endl;

    // Null pointer
    cout << "\n2. Null Pointer:" << endl;
    int* nullPtr = nullptr;
    cout << "nullPtr = " << nullPtr << endl;
    if (nullPtr == nullptr) {
        cout << "nullPtr is null" << endl;
    }

    // Pointer arithmetic
    cout << "\n3. Pointer Arithmetic:" << endl;
    int arr[5] = {10, 20, 30, 40, 50};
    int* p = arr;

    cout << "Array elements using pointer arithmetic:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "*(p + " << i << ") = " << *(p + i) << endl;
    }

    // References
    cout << "\n4. References:" << endl;
    int y = 100;
    int& ref = y;

    cout << "y = " << y << endl;
    cout << "ref = " << ref << endl;
    cout << "&y = " << &y << endl;
    cout << "&ref = " << &ref << endl;

    // Modifying through reference
    ref = 200;
    cout << "After ref = 200:" << endl;
    cout << "y = " << y << endl;
    cout << "ref = " << ref << endl;

    // References in functions
    cout << "\n5. References in Functions:" << endl;
    int value = 5;

    cout << "Original value: " << value << endl;
    incrementByValue(value);
    cout << "After incrementByValue: " << value << endl;

    incrementByReference(value);
    cout << "After incrementByReference: " << value << endl;

    incrementByPointer(&value);
    cout << "After incrementByPointer: " << value << endl;

    // Const pointers
    cout << "\n6. Const Pointers:" << endl;

    int a = 10;
    const int* ptr1 = &a;     // Pointer to const int
    int* const ptr2 = &a;     // Const pointer to int
    const int* const ptr3 = &a; // Const pointer to const int

    cout << "*ptr1 = " << *ptr1 << endl;
    cout << "*ptr2 = " << *ptr2 << endl;
    cout << "*ptr3 = " << *ptr3 << endl;

    // Pointer to pointer
    cout << "\n7. Pointer to Pointer:" << endl;
    int** ptrToPtr = &ptr;
    cout << "ptr = " << ptr << endl;
    cout << "*ptrToPtr = " << *ptrToPtr << endl;
    cout << "**ptrToPtr = " << **ptrToPtr << endl;

    // Array of pointers
    cout << "\n8. Array of Pointers:" << endl;
    int val1 = 1, val2 = 2, val3 = 3;
    int* ptrArray[3] = {&val1, &val2, &val3};

    for (int i = 0; i < 3; i++) {
        cout << "*ptrArray[" << i << "] = " << *ptrArray[i] << endl;
    }

    return 0;
}