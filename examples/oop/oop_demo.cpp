#include <iostream>
#include <string>
using namespace std;

// Base class for inheritance and polymorphism
class Animal {
protected:
    string name;

public:
    Animal(string n) : name(n) {}
    virtual ~Animal() {}

    virtual void sound() {
        cout << "Some generic animal sound" << endl;
    }

    void eat() {
        cout << name << " is eating" << endl;
    }

    string getName() const {
        return name;
    }
};

// Derived class - Inheritance
class Dog : public Animal {
private:
    string breed;

public:
    Dog(string n, string b) : Animal(n), breed(b) {}

    // Override virtual function - Polymorphism
    void sound() override {
        cout << name << " (a " << breed << ") says: Woof! Woof!" << endl;
    }

    void fetch() {
        cout << name << " is fetching the ball" << endl;
    }
};

// Another derived class
class Cat : public Animal {
public:
    Cat(string n) : Animal(n) {}

    void sound() override {
        cout << name << " says: Meow!" << endl;
    }

    void scratch() {
        cout << name << " is scratching" << endl;
    }
};

// Encapsulation example - Bank Account
class BankAccount {
private:
    string accountNumber;
    double balance;
    static int accountCount;  // Static member

public:
    // Constructor
    BankAccount(string accNum, double initialBalance = 0.0)
        : accountNumber(accNum), balance(initialBalance) {
        accountCount++;
    }

    // Destructor
    ~BankAccount() {
        accountCount--;
    }

    // Getter methods
    string getAccountNumber() const {
        return accountNumber;
    }

    double getBalance() const {
        return balance;
    }

    // Setter methods with validation
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited $" << amount << ". New balance: $" << balance << endl;
        } else {
            cout << "Invalid deposit amount" << endl;
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrew $" << amount << ". New balance: $" << balance << endl;
        } else {
            cout << "Invalid withdrawal amount or insufficient funds" << endl;
        }
    }

    // Static method
    static int getAccountCount() {
        return accountCount;
    }
};

// Initialize static member
int BankAccount::accountCount = 0;

// Person class with composition
class Person {
private:
    string name;
    int age;
    BankAccount* account;  // Composition

public:
    Person(string n, int a, string accNum)
        : name(n), age(a), account(new BankAccount(accNum, 1000.0)) {}

    ~Person() {
        delete account;
    }

    void displayInfo() {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Account Balance: $" << account->getBalance() << endl;
    }

    BankAccount* getAccount() {
        return account;
    }
};

int main() {
    cout << "=== Object-Oriented Programming Demo ===\n" << endl;

    // Basic class usage
    cout << "1. Basic Class Usage:" << endl;
    Person person("Alice", 30, "ACC001");
    person.displayInfo();

    // Inheritance and Polymorphism
    cout << "\n2. Inheritance and Polymorphism:" << endl;
    Dog dog("Buddy", "Golden Retriever");
    Cat cat("Whiskers");

    // Polymorphism - same interface, different behavior
    Animal* animals[] = {&dog, &cat};

    for (Animal* animal : animals) {
        animal->sound();
        animal->eat();
        cout << endl;
    }

    // Specific methods
    dog.fetch();
    cat.scratch();

    // Encapsulation - Bank Account
    cout << "\n3. Encapsulation - Bank Account:" << endl;
    BankAccount account("ACC002", 500.0);

    cout << "Initial balance: $" << account.getBalance() << endl;

    account.deposit(200.0);
    account.withdraw(100.0);
    account.withdraw(1000.0);  // Should fail

    // Static members
    cout << "\n4. Static Members:" << endl;
    cout << "Total accounts created: " << BankAccount::getAccountCount() << endl;

    BankAccount account2("ACC003", 300.0);
    cout << "Total accounts after creating another: " << BankAccount::getAccountCount() << endl;

    // Composition
    cout << "\n5. Composition:" << endl;
    person.getAccount()->deposit(500.0);
    cout << "Alice's new balance: $" << person.getAccount()->getBalance() << endl;

    return 0;
}