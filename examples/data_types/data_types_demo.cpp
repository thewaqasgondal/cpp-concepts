#include <iostream>
#include <limits>
using namespace std;

int main() {
    cout << "=== C++ Data Types Demo ===\n" << endl;

    // Integer types
    cout << "Integer Types:" << endl;
    int age = 25;
    unsigned int count = 100;
    short small_num = 32767;
    long big_num = 2147483647L;
    long long very_big = 9223372036854775807LL;

    cout << "int age = " << age << endl;
    cout << "unsigned int count = " << count << endl;
    cout << "short small_num = " << small_num << endl;
    cout << "long big_num = " << big_num << endl;
    cout << "long long very_big = " << very_big << endl;

    // Floating point types
    cout << "\nFloating Point Types:" << endl;
    float pi_float = 3.14159f;
    double pi_double = 3.141592653589793;
    long double pi_long_double = 3.141592653589793238L;

    cout << "float pi = " << pi_float << endl;
    cout << "double pi = " << pi_double << endl;
    cout << "long double pi = " << pi_long_double << endl;

    // Character and boolean
    cout << "\nCharacter and Boolean:" << endl;
    char letter = 'A';
    bool is_true = true;
    bool is_false = false;

    cout << "char letter = '" << letter << "'" << endl;
    cout << "bool is_true = " << (is_true ? "true" : "false") << endl;
    cout << "bool is_false = " << (is_false ? "true" : "false") << endl;

    // Size of types
    cout << "\nSize of Data Types (in bytes):" << endl;
    cout << "sizeof(int) = " << sizeof(int) << endl;
    cout << "sizeof(float) = " << sizeof(float) << endl;
    cout << "sizeof(double) = " << sizeof(double) << endl;
    cout << "sizeof(char) = " << sizeof(char) << endl;
    cout << "sizeof(bool) = " << sizeof(bool) << endl;

    // Constants
    cout << "\nConstants:" << endl;
    const int MAX_SIZE = 100;
    const double GRAVITY = 9.81;

    cout << "const int MAX_SIZE = " << MAX_SIZE << endl;
    cout << "const double GRAVITY = " << GRAVITY << endl;

    // Static variable demo
    static int counter = 0;
    counter++;
    cout << "\nStatic variable counter = " << counter << endl;

    return 0;
}