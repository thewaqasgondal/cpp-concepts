#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <functional>
#include <unordered_map>
#include <mutex>
using namespace std;

// ===== SINGLETON PATTERN =====
class Logger {
private:
    static Logger* instance;
    static mutex mtx;
    string log_file;

    Logger() : log_file("application.log") {
        cout << "Logger instance created" << endl;
    }

public:
    static Logger* getInstance() {
        lock_guard<mutex> lock(mtx);
        if (instance == nullptr) {
            instance = new Logger();
        }
        return instance;
    }

    void log(const string& message) {
        cout << "[LOG] " << message << endl;
    }

    // Prevent copying
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
};

Logger* Logger::instance = nullptr;
mutex Logger::mtx;

// ===== FACTORY PATTERN =====
class Shape {
public:
    virtual void draw() const = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape {
public:
    void draw() const override {
        cout << "Drawing a Circle" << endl;
    }
};

class Rectangle : public Shape {
public:
    void draw() const override {
        cout << "Drawing a Rectangle" << endl;
    }
};

class Triangle : public Shape {
public:
    void draw() const override {
        cout << "Drawing a Triangle" << endl;
    }
};

class ShapeFactory {
public:
    static unique_ptr<Shape> createShape(const string& type) {
        if (type == "circle") {
            return make_unique<Circle>();
        } else if (type == "rectangle") {
            return make_unique<Rectangle>();
        } else if (type == "triangle") {
            return make_unique<Triangle>();
        }
        return nullptr;
    }
};

// ===== OBSERVER PATTERN =====
class Observer {
public:
    virtual void update(const string& message) = 0;
    virtual ~Observer() = default;
};

class Subject {
private:
    vector<Observer*> observers;

public:
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) {
        observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notifyObservers(const string& message) {
        for (Observer* observer : observers) {
            observer->update(message);
        }
    }
};

class NewsAgency : public Subject {
public:
    void publishNews(const string& news) {
        cout << "News Agency: Publishing - " << news << endl;
        notifyObservers(news);
    }
};

class NewsSubscriber : public Observer {
private:
    string name;

public:
    NewsSubscriber(const string& n) : name(n) {}

    void update(const string& message) override {
        cout << name << " received news: " << message << endl;
    }
};

// ===== STRATEGY PATTERN =====
class SortingStrategy {
public:
    virtual void sort(vector<int>& data) = 0;
    virtual ~SortingStrategy() = default;
};

class BubbleSort : public SortingStrategy {
public:
    void sort(vector<int>& data) override {
        cout << "Using Bubble Sort" << endl;
        // Simplified bubble sort implementation
        for (size_t i = 0; i < data.size() - 1; ++i) {
            for (size_t j = 0; j < data.size() - i - 1; ++j) {
                if (data[j] > data[j + 1]) {
                    swap(data[j], data[j + 1]);
                }
            }
        }
    }
};

class QuickSort : public SortingStrategy {
public:
    void sort(vector<int>& data) override {
        cout << "Using Quick Sort" << endl;
        // Simplified quick sort implementation
        if (data.size() <= 1) return;

        int pivot = data[data.size() / 2];
        vector<int> left, right;

        for (size_t i = 0; i < data.size(); ++i) {
            if (i != data.size() / 2) {
                if (data[i] < pivot) left.push_back(data[i]);
                else right.push_back(data[i]);
            }
        }

        left.push_back(pivot);
        left.insert(left.end(), right.begin(), right.end());
        data = left;
    }
};

class Sorter {
private:
    unique_ptr<SortingStrategy> strategy;

public:
    void setStrategy(unique_ptr<SortingStrategy> strat) {
        strategy = move(strat);
    }

    void sort(vector<int>& data) {
        if (strategy) {
            strategy->sort(data);
        }
    }
};

// ===== DECORATOR PATTERN =====
class Coffee {
public:
    virtual string getDescription() const = 0;
    virtual double getCost() const = 0;
    virtual ~Coffee() = default;
};

class SimpleCoffee : public Coffee {
public:
    string getDescription() const override {
        return "Simple Coffee";
    }

    double getCost() const override {
        return 2.0;
    }
};

class CoffeeDecorator : public Coffee {
protected:
    unique_ptr<Coffee> coffee;

public:
    CoffeeDecorator(unique_ptr<Coffee> c) : coffee(move(c)) {}
};

class MilkDecorator : public CoffeeDecorator {
public:
    MilkDecorator(unique_ptr<Coffee> c) : CoffeeDecorator(move(c)) {}

    string getDescription() const override {
        return coffee->getDescription() + " + Milk";
    }

    double getCost() const override {
        return coffee->getCost() + 0.5;
    }
};

class SugarDecorator : public CoffeeDecorator {
public:
    SugarDecorator(unique_ptr<Coffee> c) : CoffeeDecorator(move(c)) {}

    string getDescription() const override {
        return coffee->getDescription() + " + Sugar";
    }

    double getCost() const override {
        return coffee->getCost() + 0.2;
    }
};

class WhippedCreamDecorator : public CoffeeDecorator {
public:
    WhippedCreamDecorator(unique_ptr<Coffee> c) : CoffeeDecorator(move(c)) {}

    string getDescription() const override {
        return coffee->getDescription() + " + Whipped Cream";
    }

    double getCost() const override {
        return coffee->getCost() + 0.7;
    }
};

// ===== COMMAND PATTERN =====
class Command {
public:
    virtual void execute() = 0;
    virtual ~Command() = default;
};

class Light {
public:
    void turnOn() { cout << "Light is ON" << endl; }
    void turnOff() { cout << "Light is OFF" << endl; }
};

class LightOnCommand : public Command {
private:
    Light& light;

public:
    LightOnCommand(Light& l) : light(l) {}

    void execute() override {
        light.turnOn();
    }
};

class LightOffCommand : public Command {
private:
    Light& light;

public:
    LightOffCommand(Light& l) : light(l) {}

    void execute() override {
        light.turnOff();
    }
};

class RemoteControl {
private:
    vector<unique_ptr<Command>> commands;

public:
    void addCommand(unique_ptr<Command> cmd) {
        commands.push_back(move(cmd));
    }

    void pressButton(int slot) {
        if (slot >= 0 && slot < commands.size()) {
            commands[slot]->execute();
        }
    }
};

// ===== ADAPTER PATTERN =====
class OldSystem {
public:
    void oldMethod() {
        cout << "Old system method called" << endl;
    }
};

class NewSystem {
public:
    virtual void newMethod() = 0;
    virtual ~NewSystem() = default;
};

class Adapter : public NewSystem {
private:
    OldSystem old_system;

public:
    void newMethod() override {
        cout << "Adapter: Converting new method call to old system" << endl;
        old_system.oldMethod();
    }
};

void demonstrateSingleton() {
    cout << "=== Singleton Pattern ===\n" << endl;

    Logger* logger1 = Logger::getInstance();
    Logger* logger2 = Logger::getInstance();

    cout << "Same instance: " << (logger1 == logger2 ? "Yes" : "No") << endl;

    logger1->log("Application started");
    logger2->log("User logged in");
}

void demonstrateFactory() {
    cout << "\n=== Factory Pattern ===\n" << endl;

    auto circle = ShapeFactory::createShape("circle");
    auto rectangle = ShapeFactory::createShape("rectangle");
    auto triangle = ShapeFactory::createShape("triangle");

    if (circle) circle->draw();
    if (rectangle) rectangle->draw();
    if (triangle) triangle->draw();
}

void demonstrateObserver() {
    cout << "\n=== Observer Pattern ===\n" << endl;

    NewsAgency agency;
    NewsSubscriber subscriber1("Alice");
    NewsSubscriber subscriber2("Bob");
    NewsSubscriber subscriber3("Charlie");

    agency.addObserver(&subscriber1);
    agency.addObserver(&subscriber2);
    agency.addObserver(&subscriber3);

    agency.publishNews("Breaking: C++ 23 Released!");
    agency.publishNews("Update: Design Patterns are Essential!");

    agency.removeObserver(&subscriber2);
    agency.publishNews("Final: Stay tuned for more updates!");
}

void demonstrateStrategy() {
    cout << "\n=== Strategy Pattern ===\n" << endl;

    Sorter sorter;
    vector<int> data = {3, 1, 4, 1, 5, 9, 2, 6};

    cout << "Original data: ";
    for (int n : data) cout << n << " ";
    cout << endl;

    // Use bubble sort
    sorter.setStrategy(make_unique<BubbleSort>());
    vector<int> bubble_data = data;
    sorter.sort(bubble_data);
    cout << "After bubble sort: ";
    for (int n : bubble_data) cout << n << " ";
    cout << endl;

    // Use quick sort
    sorter.setStrategy(make_unique<QuickSort>());
    vector<int> quick_data = data;
    sorter.sort(quick_data);
    cout << "After quick sort: ";
    for (int n : quick_data) cout << n << " ";
    cout << endl;
}

void demonstrateDecorator() {
    cout << "\n=== Decorator Pattern ===\n" << endl;

    // Start with simple coffee
    unique_ptr<Coffee> coffee = make_unique<SimpleCoffee>();
    cout << coffee->getDescription() << " costs $" << coffee->getCost() << endl;

    // Add milk
    coffee = make_unique<MilkDecorator>(move(coffee));
    cout << coffee->getDescription() << " costs $" << coffee->getCost() << endl;

    // Add sugar
    coffee = make_unique<SugarDecorator>(move(coffee));
    cout << coffee->getDescription() << " costs $" << coffee->getCost() << endl;

    // Add whipped cream
    coffee = make_unique<WhippedCreamDecorator>(move(coffee));
    cout << coffee->getDescription() << " costs $" << coffee->getCost() << endl;
}

void demonstrateCommand() {
    cout << "\n=== Command Pattern ===\n" << endl;

    Light livingRoomLight;
    RemoteControl remote;

    remote.addCommand(make_unique<LightOnCommand>(livingRoomLight));
    remote.addCommand(make_unique<LightOffCommand>(livingRoomLight));

    cout << "Pressing button 0 (Turn On):" << endl;
    remote.pressButton(0);

    cout << "Pressing button 1 (Turn Off):" << endl;
    remote.pressButton(1);
}

void demonstrateAdapter() {
    cout << "\n=== Adapter Pattern ===\n" << endl;

    NewSystem* system = new Adapter();
    system->newMethod();
    delete system;
}

int main() {
    cout << "=== Design Patterns in C++ Demo ===\n" << endl;

    demonstrateSingleton();
    demonstrateFactory();
    demonstrateObserver();
    demonstrateStrategy();
    demonstrateDecorator();
    demonstrateCommand();
    demonstrateAdapter();

    cout << "\n=== Summary ===" << endl;
    cout << "• Singleton: Ensures single instance of a class" << endl;
    cout << "• Factory: Creates objects without specifying exact classes" << endl;
    cout << "• Observer: Notifies multiple objects of state changes" << endl;
    cout << "• Strategy: Encapsulates algorithms for interchangeable use" << endl;
    cout << "• Decorator: Adds functionality to objects dynamically" << endl;
    cout << "• Command: Encapsulates requests as objects" << endl;
    cout << "• Adapter: Allows incompatible interfaces to work together" << endl;

    return 0;
}