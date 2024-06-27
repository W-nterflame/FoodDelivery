#ifndef ORDER_H
#define ORDER_H

#include <vector>
#include <iostream>
#include "FoodItem.h"
#include "Delivery.h"

class Order {
private:
    std::vector<FoodItem> items;
    std::vector<int> quantities;
    Delivery delivery;
    bool hasUtensils;
    double tipAmount;

public:
    Order() : delivery("", "", 0.0), hasUtensils(false), tipAmount(0.0) {} // Initialize with default values

    void addItem(const FoodItem& item, int quantity) {
        items.push_back(item);
        quantities.push_back(quantity);
    }

    bool getHasUtensils() const {
        return hasUtensils;
    }

    double getTipAmount() const {
        return tipAmount;
    }

    const std::vector<FoodItem>& getItems() const {
        return items;
    }

    const std::vector<int>& getQuantities() const {
        return quantities;
    }

    void addFoodUtensils(bool addUtensils) {
        hasUtensils = addUtensils;
    }

    void addDeliveryTip(double amount) {
        tipAmount = amount;
    }

    double calculateTotal() const {
        double subtotal = 0.0;
        for (size_t i = 0; i < items.size(); ++i) {
            subtotal += items[i].getPrice() * quantities[i];
        }
        double total = subtotal + delivery.getDeliveryPrice();
        if (hasUtensils) {
            total += 0.5; // Add $0.5 for food utensils
        }
        total += tipAmount; // Add tip amount
        return total;
    }

    void displayOrderSummary() const {
        std::cout << "Order Summary:\n";
        for (size_t i = 0; i < items.size(); ++i) {
            std::cout << items[i].getName() << " x" << quantities[i] << " - $" << items[i].getPrice() * quantities[i] << "\n";
            if (!items[i].getSpecialInstructions().empty()) {
                std::cout << "  Special instructions: " << items[i].getSpecialInstructions() << "\n";
            }
        }
        std::cout << "Delivery: " << delivery.getDeliveryOption() << " - $" << delivery.getDeliveryPrice() << "\n";
        if (hasUtensils) {
            std::cout << "Food Utensils: Yes - $0.5\n";
        }
        else {
            std::cout << "Food Utensils: No\n";
        }
        std::cout << "Tip: $" << tipAmount << "\n";
        std::cout << "Total: $" << calculateTotal() << "\n";
    }

    void setDelivery(const Delivery& deliveryDetails) {
        delivery = deliveryDetails;
    }

    const Delivery& getDelivery() const {
        return delivery;
    }

    void displayOrderMenu(const Restaurant& selectedRestaurant) {
        int itemChoice;
        int quantity;
        char addMore;
        do {
            std::cout << "\nEnter the number of the food item to order: ";
            std::cin >> itemChoice;
            if (itemChoice < 1 || itemChoice > selectedRestaurant.getMenuSize()) {
                std::cout << "Invalid choice. Please try again.\n";
                continue;
            }

            FoodItem selectedItem = selectedRestaurant.getFoodItem(itemChoice - 1);

            std::cout << "Enter quantity: ";
            std::cin >> quantity;

            std::string specialInstructions;
            std::cout << "Enter any special instructions (or press Enter to skip): ";
            std::cin.ignore(); // To clear the newline left by previous input
            std::getline(std::cin, specialInstructions);
            selectedItem.setSpecialInstructions(specialInstructions);

            addItem(selectedItem, quantity);

            std::cout << "Add more items? (y/n): ";
            std::cin >> addMore;
        } while (addMore == 'y' || addMore == 'Y');

        displayOrderSummary();
    }

    void displayUtensilOption() {
        char addUtensilsChoice;
        std::cout << "Do you want to add food utensils? (y/n): ";
        std::cin >> addUtensilsChoice;
        if (addUtensilsChoice == 'y' || addUtensilsChoice == 'Y') {
            addFoodUtensils(true);
        }
        else {
            addFoodUtensils(false);
        }
    }

    void displayTipOption() {
        int tipChoice;
        std::cout << "Select delivery tip:\n";
        std::cout << "1. None\n";
        std::cout << "2. $1\n";
        std::cout << "3. $2\n";
        std::cin >> tipChoice;

        switch (tipChoice) {
        case 1:
            addDeliveryTip(0.0); // No tip
            break;
        case 2:
            addDeliveryTip(1.0); // $1 tip
            break;
        case 3:
            addDeliveryTip(2.0); // $2 tip
            break;
        default:
            std::cout << "Invalid tip choice. No tip will be added.\n";
            addDeliveryTip(0.0); // Default to no tip
            break;
        }
    }
};

#endif // ORDER_H
