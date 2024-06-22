#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <vector>
#include <string>
#include <iostream>
#include "FoodItem.h"

class Restaurant {
private:
    std::string name;
    std::vector<FoodItem> menu;

public:
    Restaurant(std::string n) : name(n) {}

    std::string getName() const {
        return name;
    }

    void addFoodItem(FoodItem item) {
        menu.push_back(item);
    }

    void displayMenu() const {
        std::cout << "Menu for " << name << ":\n";
        for (size_t i = 0; i < menu.size(); ++i) {
            std::cout << i + 1 << ". " << menu[i].getName() << " - $" << menu[i].getPrice() << "\n"
                << "   Description: " << menu[i].getDescription() << "\n";
        }
    }

    FoodItem getFoodItem(int index) const {
        if (index >= 0 && index < menu.size()) {
            return menu[index];
        }
        else {
            throw std::out_of_range("Invalid menu item index");
        }
    }

    int getMenuSize() const {
        return menu.size();
    }
};

#endif // RESTAURANT_H
