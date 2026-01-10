#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
using namespace std;
namespace fs = filesystem;

void demonstrateFileOutput() {
    cout << "=== File Output ===\n" << endl;

    // Writing to a file
    ofstream outfile("example.txt");
    if (!outfile) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    outfile << "Hello, File I/O!" << endl;
    outfile << "This is a demonstration of C++ file operations." << endl;
    outfile << "Line 3: Numbers and text can be mixed." << endl;
    outfile << 42 << " " << 3.14 << " " << true << endl;

    outfile.close();
    cout << "Data written to example.txt" << endl;
}

void demonstrateFileInput() {
    cout << "\n=== File Input ===\n" << endl;

    // Reading from a file
    ifstream infile("example.txt");
    if (!infile) {
        cerr << "Error opening file for reading!" << endl;
        return;
    }

    string line;
    cout << "Contents of example.txt:" << endl;
    while (getline(infile, line)) {
        cout << line << endl;
    }

    infile.close();
}

void demonstrateBinaryFiles() {
    cout << "\n=== Binary File I/O ===\n" << endl;

    // Writing binary data
    ofstream binfile("data.bin", ios::binary);
    if (!binfile) {
        cerr << "Error opening binary file for writing!" << endl;
        return;
    }

    vector<int> numbers = {1, 2, 3, 4, 5, 100, 200, 300};
    binfile.write(reinterpret_cast<const char*>(numbers.data()),
                  numbers.size() * sizeof(int));
    binfile.close();
    cout << "Binary data written to data.bin" << endl;

    // Reading binary data
    ifstream binread("data.bin", ios::binary);
    if (!binread) {
        cerr << "Error opening binary file for reading!" << endl;
        return;
    }

    vector<int> read_numbers(numbers.size());
    binread.read(reinterpret_cast<char*>(read_numbers.data()),
                 read_numbers.size() * sizeof(int));
    binread.close();

    cout << "Binary data read back: ";
    for (int num : read_numbers) {
        cout << num << " ";
    }
    cout << endl;
}

void demonstrateStringStreams() {
    cout << "\n=== String Streams ===\n" << endl;

    // Output string stream
    ostringstream oss;
    oss << "Name: " << "Alice" << endl;
    oss << "Age: " << 30 << endl;
    oss << "Score: " << 95.5 << endl;

    string result = oss.str();
    cout << "String stream result:" << endl << result << endl;

    // Input string stream
    istringstream iss("42 3.14 hello world");
    int i;
    double d;
    string s1, s2;

    iss >> i >> d >> s1 >> s2;
    cout << "Parsed values:" << endl;
    cout << "int: " << i << endl;
    cout << "double: " << d << endl;
    cout << "string1: " << s1 << endl;
    cout << "string2: " << s2 << endl;
}

void demonstrateFileOperations() {
    cout << "\n=== File System Operations ===\n" << endl;

    // Create a directory
    fs::create_directory("test_dir");
    cout << "Created directory: test_dir" << endl;

    // Create a file in the directory
    ofstream testfile("test_dir/test.txt");
    testfile << "This is a test file in a subdirectory." << endl;
    testfile.close();

    // Check if file exists
    if (fs::exists("test_dir/test.txt")) {
        cout << "File test_dir/test.txt exists" << endl;
    }

    // Get file size
    auto size = fs::file_size("test_dir/test.txt");
    cout << "File size: " << size << " bytes" << endl;

    // List directory contents
    cout << "Contents of test_dir:" << endl;
    for (const auto& entry : fs::directory_iterator("test_dir")) {
        cout << "  " << entry.path() << endl;
    }

    // Remove file and directory
    fs::remove("test_dir/test.txt");
    fs::remove("test_dir");
    cout << "Cleaned up test directory and file" << endl;
}

void demonstrateErrorHandling() {
    cout << "\n=== Error Handling ===\n" << endl;

    // Try to open a non-existent file
    ifstream nonexistent("nonexistent.txt");
    if (!nonexistent) {
        cout << "Failed to open nonexistent.txt (expected)" << endl;
    }

    // Check stream state
    ofstream test("test.txt");
    test << "test";
    test.close();

    ifstream read_test("test.txt");
    string content;
    read_test >> content;
    cout << "Read: " << content << endl;

    // Check for end of file
    if (read_test.eof()) {
        cout << "Reached end of file" << endl;
    }

    // Check for errors
    if (read_test.fail()) {
        cout << "Stream is in fail state" << endl;
    }

    read_test.close();
    fs::remove("test.txt");
}

void demonstrateCSVProcessing() {
    cout << "\n=== CSV Processing Example ===\n" << endl;

    // Create a CSV file
    ofstream csv("data.csv");
    csv << "Name,Age,City" << endl;
    csv << "Alice,25,New York" << endl;
    csv << "Bob,30,San Francisco" << endl;
    csv << "Charlie,35,Chicago" << endl;
    csv.close();

    // Read and parse CSV
    ifstream csv_read("data.csv");
    string line;
    getline(csv_read, line); // Skip header

    cout << "Parsed CSV data:" << endl;
    while (getline(csv_read, line)) {
        stringstream ss(line);
        string name, age_str, city;
        getline(ss, name, ',');
        getline(ss, age_str, ',');
        getline(ss, city, ',');

        int age = stoi(age_str);
        cout << "Name: " << name << ", Age: " << age << ", City: " << city << endl;
    }

    csv_read.close();
    fs::remove("data.csv");
}

int main() {
    cout << "=== C++ File I/O Demo ===\n" << endl;

    demonstrateFileOutput();
    demonstrateFileInput();
    demonstrateBinaryFiles();
    demonstrateStringStreams();
    demonstrateFileOperations();
    demonstrateErrorHandling();
    demonstrateCSVProcessing();

    // Clean up remaining files
    fs::remove("example.txt");
    fs::remove("data.bin");

    cout << "\n=== Summary ===" << endl;
    cout << "• ofstream: Writing to files" << endl;
    cout << "• ifstream: Reading from files" << endl;
    cout << "• Binary I/O: Raw data reading/writing" << endl;
    cout << "• String streams: In-memory string manipulation" << endl;
    cout << "• Filesystem library: Directory and file operations" << endl;
    cout << "• Error handling: Checking stream states" << endl;
    cout << "• CSV processing: Parsing structured data" << endl;

    return 0;
}