#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <vector>
#include <string>
#include <iostream>
#include "FoodItem.h"

using namespace std;

class Restaurant {
private:
    string name;
    vector<FoodItem> menu;

public:
    Restaurant(string n) : name(n) {}

    string getName() const {
        return name;
    }

    void addFoodItem(const FoodItem& item) {
        menu.push_back(item);
    }

    void displayMenu() const {
        cout << "Menu for " << name << ":\n";
        for (size_t i = 0; i < menu.size(); ++i) {
            cout << i + 1 << ". " << menu[i].getName() << " - $" << menu[i].getPrice() << "\n"
                << "   Description: " << menu[i].getDescription() << "\n";
        }
    }

    const FoodItem& getFoodItem(int index) const {
        if (index >= 0 && index < static_cast<int>(menu.size())) {
            return menu[index];
        }
        else {
            throw out_of_range("Invalid menu item index");
        }
    }

    int getMenuSize() const {
        return static_cast<int>(menu.size());
    }
};

#endif // RESTAURANT_H
