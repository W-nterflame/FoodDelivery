#ifndef FOODITEM_H
#define FOODITEM_H

#include <string>
#include <iostream>

using namespace std;

class FoodItem {
private:
    string name;
    double price;
    string description;
    string specialInstructions;

public:
    FoodItem(string n, double p, string d)
        : name(n), price(p), description(d) {}

    string getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }

    string getDescription() const {
        return description;
    }

    void setSpecialInstructions(string instructions) {
        specialInstructions = instructions;
    }

    string getSpecialInstructions() const {
        return specialInstructions;
    }

    virtual void display() const {
        cout << "Name: " << name << "\n";
        cout << "Price: $" << price << "\n";
        cout << "Description: " << description << "\n";
        if (!specialInstructions.empty()) {
            cout << "Special Instructions: " << specialInstructions << "\n";
        }
    }
};

#endif // FOODITEM_H
