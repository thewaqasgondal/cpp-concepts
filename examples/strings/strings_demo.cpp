#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

void demonstrateStringBasics() {
    cout << "=== String Basics ===\n" << endl;

    // String creation
    string str1 = "Hello";
    string str2 = "World";
    string str3 = str1 + " " + str2;  // Concatenation

    cout << "str1: " << str1 << endl;
    cout << "str2: " << str2 << endl;
    cout << "str3 (concatenated): " << str3 << endl;

    // String operations
    cout << "\nString operations:" << endl;
    cout << "Length of str1: " << str1.length() << endl;
    cout << "Substring str1(0,3): " << str1.substr(0, 3) << endl;
    cout << "Find 'll' in str1: " << str1.find("ll") << endl;

    // Character access
    cout << "First character of str1: " << str1[0] << endl;
    cout << "Last character of str1: " << str1.back() << endl;

    // Modification
    string str4 = str1;
    str4.replace(0, 2, "Hi");
    cout << "After replace(0,2,\"Hi\"): " << str4 << endl;
}

void demonstrateStringComparison() {
    cout << "\n=== String Comparison ===\n" << endl;

    string str1 = "apple";
    string str2 = "banana";
    string str3 = "apple";

    cout << "str1: " << str1 << endl;
    cout << "str2: " << str2 << endl;
    cout << "str3: " << str3 << endl;

    // Equality comparison
    if (str1 == str2) {
        cout << "str1 == str2" << endl;
    } else {
        cout << "str1 != str2" << endl;
    }

    if (str1 == str3) {
        cout << "str1 == str3" << endl;
    }

    // Using compare()
    cout << "str1.compare(str2): " << str1.compare(str2) << endl;
    cout << "str1.compare(str3): " << str1.compare(str3) << endl;
}

void demonstrateStringAlgorithms() {
    cout << "\n=== String Algorithms ===\n" << endl;

    string str = "Hello, World!";

    cout << "Original string: " << str << endl;

    // Transform to uppercase
    string upper = str;
    transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
    cout << "Uppercase: " << upper << endl;

    // Transform to lowercase
    string lower = str;
    transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    cout << "Lowercase: " << lower << endl;

    // Reverse
    string reversed = str;
    reverse(reversed.begin(), reversed.end());
    cout << "Reversed: " << reversed << endl;

    // Find and replace all occurrences
    string text = "The quick brown fox jumps over the lazy dog";
    cout << "\nOriginal text: " << text << endl;

    size_t pos = 0;
    while ((pos = text.find("the", pos)) != string::npos) {
        text.replace(pos, 3, "THE");
        pos += 3;
    }
    cout << "After replacing 'the' with 'THE': " << text << endl;
}

void demonstrateStringStreams() {
    cout << "\n=== String Streams ===\n" << endl;

    // Output string stream
    ostringstream oss;
    oss << "Number: " << 42 << ", Pi: " << 3.14159;
    string result = oss.str();
    cout << "String stream result: " << result << endl;

    // Input string stream
    istringstream iss("123 456.78 hello");
    int num1;
    double num2;
    string word;
    iss >> num1 >> num2 >> word;

    cout << "Parsed values:" << endl;
    cout << "Integer: " << num1 << endl;
    cout << "Double: " << num2 << endl;
    cout << "String: " << word << endl;
}

int main() {
    cout << "=== C++ Strings Demo ===\n" << endl;

    demonstrateStringBasics();
    demonstrateStringComparison();
    demonstrateStringAlgorithms();
    demonstrateStringStreams();

    cout << "\n=== Summary ===" << endl;
    cout << "• std::string provides safe, easy-to-use string operations" << endl;
    cout << "• Supports concatenation, comparison, and modification" << endl;
    cout << "• Works with standard algorithms (transform, reverse, etc.)" << endl;
    cout << "• String streams for parsing and formatting" << endl;

    return 0;
}