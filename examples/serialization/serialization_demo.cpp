#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <variant>
using namespace std;

// ===== SIMPLE JSON-LIKE SERIALIZER =====
class JsonValue;
using JsonObject = map<string, shared_ptr<JsonValue>>;
using JsonArray = vector<shared_ptr<JsonValue>>;

class JsonValue {
public:
    virtual string toString(int indent = 0) const = 0;
    virtual ~JsonValue() = default;
};

class JsonString : public JsonValue {
private:
    string value;

public:
    JsonString(const string& val) : value(val) {}

    string toString(int indent = 0) const override {
        return "\"" + value + "\"";
    }
};

class JsonNumber : public JsonValue {
private:
    double value;

public:
    JsonNumber(double val) : value(val) {}

    string toString(int indent = 0) const override {
        ostringstream oss;
        oss << value;
        return oss.str();
    }
};

class JsonBool : public JsonValue {
private:
    bool value;

public:
    JsonBool(bool val) : value(val) {}

    string toString(int indent = 0) const override {
        return value ? "true" : "false";
    }
};

class JsonNull : public JsonValue {
public:
    string toString(int indent = 0) const override {
        return "null";
    }
};

class JsonArrayValue : public JsonValue {
private:
    JsonArray value;

public:
    JsonArrayValue(const JsonArray& val) : value(val) {}

    void add(shared_ptr<JsonValue> item) {
        value.push_back(item);
    }

    string toString(int indent = 0) const override {
        if (value.empty()) return "[]";

        string result = "[\n";
        string indentStr(indent + 2, ' ');

        for (size_t i = 0; i < value.size(); ++i) {
            result += indentStr + value[i]->toString(indent + 2);
            if (i < value.size() - 1) result += ",";
            result += "\n";
        }

        result += string(indent, ' ') + "]";
        return result;
    }
};

class JsonObjectValue : public JsonValue {
private:
    JsonObject value;

public:
    JsonObjectValue(const JsonObject& val) : value(val) {}

    void add(const string& key, shared_ptr<JsonValue> val) {
        value[key] = val;
    }

    string toString(int indent = 0) const override {
        if (value.empty()) return "{}";

        string result = "{\n";
        string indentStr(indent + 2, ' ');

        auto it = value.begin();
        while (it != value.end()) {
            result += indentStr + "\"" + it->first + "\": " + it->second->toString(indent + 2);
            ++it;
            if (it != value.end()) result += ",";
            result += "\n";
        }

        result += string(indent, ' ') + "}";
        return result;
    }
};

// ===== PERSON CLASS FOR DEMONSTRATION =====
class Person {
private:
    string name;
    int age;
    double height;
    vector<string> hobbies;

public:
    Person(const string& n, int a, double h, const vector<string>& hob)
        : name(n), age(a), height(h), hobbies(hob) {}

    // Serialize to JSON
    shared_ptr<JsonValue> toJson() const {
        auto obj = make_shared<JsonObjectValue>(JsonObject());

        obj->add("name", make_shared<JsonString>(name));
        obj->add("age", make_shared<JsonNumber>(age));
        obj->add("height", make_shared<JsonNumber>(height));

        auto hobbiesArray = make_shared<JsonArrayValue>(JsonArray());
        for (const string& hobby : hobbies) {
            hobbiesArray->add(make_shared<JsonString>(hobby));
        }
        obj->add("hobbies", hobbiesArray);

        return obj;
    }

    // Deserialize from JSON (simplified)
    static Person fromJson(const JsonObject& obj) {
        string name;
        int age = 0;
        double height = 0.0;
        vector<string> hobbies;

        // This is a simplified deserialization - in practice you'd need proper JSON parsing
        if (obj.count("name")) {
            // Simplified - assuming we can extract string values
            name = "John Doe"; // Placeholder
        }

        return Person(name, age, height, hobbies);
    }

    void display() const {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Height: " << height << " cm" << endl;
        cout << "Hobbies: ";
        for (size_t i = 0; i < hobbies.size(); ++i) {
            cout << hobbies[i];
            if (i < hobbies.size() - 1) cout << ", ";
        }
        cout << endl;
    }
};

// ===== BINARY SERIALIZATION =====
class BinarySerializer {
public:
    template<typename T>
    static void serialize(ofstream& out, const T& value) {
        out.write(reinterpret_cast<const char*>(&value), sizeof(T));
    }

    template<typename T>
    static void deserialize(ifstream& in, T& value) {
        in.read(reinterpret_cast<char*>(&value), sizeof(T));
    }

    static void serializeString(ofstream& out, const string& str) {
        size_t size = str.size();
        out.write(reinterpret_cast<const char*>(&size), sizeof(size));
        out.write(str.c_str(), size);
    }

    static void deserializeString(ifstream& in, string& str) {
        size_t size;
        in.read(reinterpret_cast<char*>(&size), sizeof(size));
        str.resize(size);
        in.read(&str[0], size);
    }
};

// ===== XML-LIKE SERIALIZER =====
class XmlSerializer {
public:
    static string serializePerson(const Person& person, const string& name, int age, double height, const vector<string>& hobbies) {
        ostringstream oss;
        oss << "<person>\n";
        oss << "  <name>" << name << "</name>\n";
        oss << "  <age>" << age << "</age>\n";
        oss << "  <height>" << fixed << setprecision(2) << height << "</height>\n";
        oss << "  <hobbies>\n";
        for (const string& hobby : hobbies) {
            oss << "    <hobby>" << hobby << "</hobby>\n";
        }
        oss << "  </hobbies>\n";
        oss << "</person>\n";
        return oss.str();
    }
};

// ===== CSV SERIALIZER =====
class CsvSerializer {
public:
    static string serializeTable(const vector<vector<string>>& table) {
        ostringstream oss;
        for (const auto& row : table) {
            for (size_t i = 0; i < row.size(); ++i) {
                // Simple CSV escaping - quote fields containing commas
                if (row[i].find(',') != string::npos) {
                    oss << "\"" << row[i] << "\"";
                } else {
                    oss << row[i];
                }
                if (i < row.size() - 1) oss << ",";
            }
            oss << "\n";
        }
        return oss.str();
    }
};

void demonstrateJsonSerialization() {
    cout << "=== JSON Serialization ===\n" << endl;

    // Create a person
    Person person("Alice Johnson", 28, 165.5, {"reading", "hiking", "coding"});

    // Serialize to JSON
    auto jsonObj = person.toJson();
    string jsonStr = jsonObj->toString();

    cout << "Person as JSON:" << endl;
    cout << jsonStr << endl;

    // Save to file
    ofstream jsonFile("person.json");
    jsonFile << jsonStr;
    jsonFile.close();
    cout << "Saved to person.json" << endl;
}

void demonstrateBinarySerialization() {
    cout << "\n=== Binary Serialization ===\n" << endl;

    // Data to serialize
    string name = "Bob Smith";
    int age = 35;
    double salary = 75000.50;
    vector<int> scores = {85, 92, 78, 96, 88};

    // Serialize
    ofstream binFile("data.bin", ios::binary);
    BinarySerializer::serializeString(binFile, name);
    BinarySerializer::serialize(binFile, age);
    BinarySerializer::serialize(binFile, salary);

    // Serialize vector size and elements
    size_t vecSize = scores.size();
    BinarySerializer::serialize(binFile, vecSize);
    for (int score : scores) {
        BinarySerializer::serialize(binFile, score);
    }

    binFile.close();
    cout << "Data serialized to data.bin" << endl;

    // Deserialize
    ifstream binRead("data.bin", ios::binary);
    string readName;
    int readAge;
    double readSalary;
    vector<int> readScores;

    BinarySerializer::deserializeString(binRead, readName);
    BinarySerializer::deserialize(binRead, readAge);
    BinarySerializer::deserialize(binRead, readSalary);

    size_t readVecSize;
    BinarySerializer::deserialize(binRead, readVecSize);
    readScores.resize(readVecSize);
    for (size_t i = 0; i < readVecSize; ++i) {
        BinarySerializer::deserialize(binRead, readScores[i]);
    }

    binRead.close();

    cout << "Deserialized data:" << endl;
    cout << "Name: " << readName << endl;
    cout << "Age: " << readAge << endl;
    cout << "Salary: $" << fixed << setprecision(2) << readSalary << endl;
    cout << "Scores: ";
    for (int score : readScores) cout << score << " ";
    cout << endl;
}

void demonstrateXmlSerialization() {
    cout << "\n=== XML Serialization ===\n" << endl;

    vector<string> hobbies = {"painting", "music", "gardening"};
    string xml = XmlSerializer::serializePerson(Person("", 0, 0, {}),
                                                "Charlie Brown", 42, 175.2, hobbies);

    cout << "Person as XML:" << endl;
    cout << xml;

    // Save to file
    ofstream xmlFile("person.xml");
    xmlFile << xml;
    xmlFile.close();
    cout << "Saved to person.xml" << endl;
}

void demonstrateCsvSerialization() {
    cout << "\n=== CSV Serialization ===\n" << endl;

    vector<vector<string>> table = {
        {"Name", "Age", "City", "Occupation"},
        {"Alice", "28", "New York", "Engineer"},
        {"Bob", "35", "San Francisco", "Designer"},
        {"Charlie", "42", "Chicago", "Manager"},
        {"Diana", "31", "Boston", "Developer"}
    };

    string csv = CsvSerializer::serializeTable(table);
    cout << "Data as CSV:" << endl;
    cout << csv;

    // Save to file
    ofstream csvFile("data.csv");
    csvFile << csv;
    csvFile.close();
    cout << "Saved to data.csv" << endl;
}

void demonstrateFileOperations() {
    cout << "\n=== File Operations with Serialization ===\n" << endl;

    // Create multiple objects
    vector<Person> people = {
        Person("Alice", 28, 165.0, {"reading", "coding"}),
        Person("Bob", 35, 180.0, {"gaming", "sports"}),
        Person("Charlie", 42, 175.0, {"cooking", "photography"})
    };

    // Serialize all to JSON array
    auto jsonArray = make_shared<JsonArrayValue>(JsonArray());
    for (const auto& person : people) {
        jsonArray->add(person.toJson());
    }

    string jsonStr = jsonArray->toString();
    cout << "People array as JSON:" << endl;
    cout << jsonStr << endl;

    // Save to file
    ofstream outfile("people.json");
    outfile << jsonStr;
    outfile.close();
    cout << "Saved to people.json" << endl;

    // Read back and display file size
    ifstream infile("people.json");
    infile.seekg(0, ios::end);
    size_t fileSize = infile.tellg();
    infile.close();

    cout << "File size: " << fileSize << " bytes" << endl;
}

int main() {
    cout << "=== C++ Serialization Demo ===\n" << endl;

    demonstrateJsonSerialization();
    demonstrateBinarySerialization();
    demonstrateXmlSerialization();
    demonstrateCsvSerialization();
    demonstrateFileOperations();

    cout << "\n=== Summary ===" << endl;
    cout << "• JSON: Human-readable, flexible, good for APIs" << endl;
    cout << "• Binary: Compact, fast, good for internal storage" << endl;
    cout << "• XML: Structured, self-descriptive, good for configs" << endl;
    cout << "• CSV: Simple tabular data, good for spreadsheets" << endl;
    cout << "• Choose format based on use case and requirements" << endl;

    return 0;
}