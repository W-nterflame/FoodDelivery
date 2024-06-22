#ifndef FOODITEM_H
#define FOODITEM_H

#include <string>
#include <iostream>

class FoodItem {
private:
    std::string name;
    double price;
    std::string description;
    std::string specialInstructions;

public:
    FoodItem(std::string n, double p, std::string d)
        : name(n), price(p), description(d) {}

    std::string getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }

    std::string getDescription() const {
        return description;
    }

    void setSpecialInstructions(std::string instructions) {
        specialInstructions = instructions;
    }

    std::string getSpecialInstructions() const {
        return specialInstructions;
    }

    // Virtual method to display food item details
    virtual void display() const {
        std::cout << "Name: " << name << "\n";
        std::cout << "Price: $" << price << "\n";
        std::cout << "Description: " << description << "\n";
        if (!specialInstructions.empty()) {
            std::cout << "Special Instructions: " << specialInstructions << "\n";
        }
    }
};

class MainCourse : public FoodItem {
private:
    std::string chefSpecialty;

public:
    MainCourse(std::string n, double p, std::string d, std::string specialty)
        : FoodItem(n, p, d), chefSpecialty(specialty) {}

    std::string getChefSpecialty() const {
        return chefSpecialty;
    }

    // Override display() method to include chef specialty
    void display() const override {
        FoodItem::display(); // Call base class display method
        std::cout << "Chef Specialty: " << chefSpecialty << "\n";
    }
};

#endif // FOODITEM_H
