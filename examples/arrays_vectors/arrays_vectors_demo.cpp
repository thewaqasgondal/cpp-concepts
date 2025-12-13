#include <iostream>
#include <vector>
using namespace std;

int main() {
    cout << "=== Arrays and Vectors Demo ===\n" << endl;

    // Fixed-size arrays
    cout << "1. Fixed-Size Arrays:" << endl;
    int arr[5] = {1, 2, 3, 4, 5};
    cout << "Array elements: ";
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Size inferred from initialization
    cout << "\n2. Size Inferred Array:" << endl;
    int arr2[] = {10, 20, 30, 40};
    cout << "Array elements: ";
    for (int num : arr2) {
        cout << num << " ";
    }
    cout << endl;

    // 2D arrays
    cout << "\n3. 2D Arrays:" << endl;
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    cout << "Matrix:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    // Vectors
    cout << "\n4. Vectors (Dynamic Arrays):" << endl;

    // Empty vector
    vector<int> v1;
    cout << "Empty vector size: " << v1.size() << endl;

    // Vector with initial size and value
    vector<int> v2(5, 10);
    cout << "Vector with 5 elements of value 10: ";
    for (int num : v2) {
        cout << num << " ";
    }
    cout << endl;

    // Vector operations
    cout << "\n5. Vector Operations:" << endl;
    vector<int> v3 = {1, 2, 3};

    cout << "Original vector: ";
    for (int num : v3) cout << num << " ";
    cout << endl;

    // Add elements
    v3.push_back(4);
    v3.push_back(5);
    cout << "After push_back(4) and push_back(5): ";
    for (int num : v3) cout << num << " ";
    cout << endl;

    // Remove last element
    v3.pop_back();
    cout << "After pop_back(): ";
    for (int num : v3) cout << num << " ";
    cout << endl;

    // Access elements
    cout << "Element at index 0: " << v3[0] << endl;
    cout << "Element at index 2 (using at()): " << v3.at(2) << endl;

    // Size and capacity
    cout << "Size: " << v3.size() << endl;
    cout << "Is empty: " << (v3.empty() ? "Yes" : "No") << endl;

    // Clear vector
    v3.clear();
    cout << "After clear(), size: " << v3.size() << endl;

    // Vector of vectors (2D vector)
    cout << "\n6. 2D Vectors:" << endl;
    vector<vector<int>> matrix2d = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    cout << "2D Vector:" << endl;
    for (const auto& row : matrix2d) {
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }

    // Vector with different data types
    cout << "\n7. Vector with Strings:" << endl;
    vector<string> names = {"Alice", "Bob", "Charlie"};
    for (string name : names) {
        cout << name << " ";
    }
    cout << endl;

    return 0;
}