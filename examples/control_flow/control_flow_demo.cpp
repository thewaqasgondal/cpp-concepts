#include <iostream>
using namespace std;

int main() {
    cout << "=== Control Flow Demo ===\n" << endl;

    // If-Else statements
    cout << "1. If-Else Statements:" << endl;
    int x = 15;

    if (x > 10) {
        cout << "x (" << x << ") is greater than 10" << endl;
    } else if (x == 10) {
        cout << "x equals 10" << endl;
    } else {
        cout << "x is less than 10" << endl;
    }

    // Switch statement
    cout << "\n2. Switch Statement:" << endl;
    int day = 3;

    switch (day) {
        case 1:
            cout << "Monday" << endl;
            break;
        case 2:
            cout << "Tuesday" << endl;
            break;
        case 3:
            cout << "Wednesday" << endl;
            break;
        case 4:
            cout << "Thursday" << endl;
            break;
        case 5:
            cout << "Friday" << endl;
            break;
        default:
            cout << "Weekend or invalid day" << endl;
    }

    // For loop
    cout << "\n3. For Loop:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "Iteration " << i << endl;
    }

    // While loop
    cout << "\n4. While Loop:" << endl;
    int counter = 0;
    while (counter < 3) {
        cout << "While loop iteration " << counter << endl;
        counter++;
    }

    // Do-While loop
    cout << "\n5. Do-While Loop:" << endl;
    int do_counter = 0;
    do {
        cout << "Do-while loop iteration " << do_counter << endl;
        do_counter++;
    } while (do_counter < 3);

    // Range-based for loop (C++11)
    cout << "\n6. Range-based For Loop:" << endl;
    int numbers[] = {10, 20, 30, 40, 50};
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    // Nested loops
    cout << "\n7. Nested Loops (Multiplication Table):" << endl;
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            cout << i << " * " << j << " = " << (i * j) << "\t";
        }
        cout << endl;
    }

    // Break and continue
    cout << "\n8. Break and Continue:" << endl;
    for (int i = 0; i < 10; i++) {
        if (i == 3) {
            cout << "Skipping " << i << " (continue)" << endl;
            continue;
        }
        if (i == 7) {
            cout << "Breaking at " << i << endl;
            break;
        }
        cout << "Processing " << i << endl;
    }

    return 0;
}