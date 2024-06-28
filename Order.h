#ifndef ORDER_H
#define ORDER_H

#include <vector>
#include <iostream>
#include "FoodItem.h"
#include "Delivery.h"

using namespace std;

class Order {
private:
    vector<FoodItem> items;
    vector<int> quantities;
    Delivery delivery;
    bool hasUtensils;
    double tipAmount;

public:
    Order() : delivery("", "", 0.0), hasUtensils(false), tipAmount(0.0) {}

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

    const vector<FoodItem>& getItems() const {
        return items;
    }

    const vector<int>& getQuantities() const {
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
        cout << "Order Summary:\n";
        for (size_t i = 0; i < items.size(); ++i) {
            cout << items[i].getName() << " x" << quantities[i] << " - $" << items[i].getPrice() * quantities[i] << "\n";
            if (!items[i].getSpecialInstructions().empty()) {
                cout << "  Special instructions: " << items[i].getSpecialInstructions() << "\n";
            }
        }
        cout << "Delivery: " << delivery.getDeliveryOption() << " - $" << delivery.getDeliveryPrice() << "\n";
        if (hasUtensils) {
            cout << "Food Utensils: Yes - $0.5\n";
        }
        else {
            cout << "Food Utensils: No\n";
        }
        cout << "Tip: $" << tipAmount << "\n";
        cout << "Total: $" << calculateTotal() << "\n";
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
            // Display restaurant menu
            cout << "\nRestaurant Menu: " << selectedRestaurant.getName() << "\n";
            for (int i = 0; i < selectedRestaurant.getMenuSize(); ++i) {
                FoodItem item = selectedRestaurant.getFoodItem(i);
                cout << i + 1 << ". " << item.getName() << " - $" << item.getPrice() << "\n";
                cout << "   Description: " << item.getDescription() << "\n";
            }

            // Prompt for item choice
            cout << "\nEnter the number of the food item to order: ";
            cin >> itemChoice;
            if (itemChoice < 1 || itemChoice > selectedRestaurant.getMenuSize()) {
                cout << "Invalid choice. Please try again.\n";
                continue;
            }

            // Retrieve selected item details
            FoodItem selectedItem = selectedRestaurant.getFoodItem(itemChoice - 1);

            // Prompt for quantity
            cout << "Enter quantity: ";
            cin >> quantity;

            // Clear newline from buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // Prompt for special instructions
            string specialInstructions;
            cout << "Enter any special instructions (or press Enter to skip): ";
            getline(cin, specialInstructions);
            selectedItem.setSpecialInstructions(specialInstructions);

            // Add item to order
            addItem(selectedItem, quantity);

            // Prompt to add more items
            cout << "Add more items? (y/n): ";
            cin >> addMore;
            cin.ignore(); // Clear newline from buffer

        } while (addMore == 'y' || addMore == 'Y');

        // Display order summary after finalizing items
        displayOrderSummary();
    }


    void displayUtensilOption() {
        char addUtensilsChoice;
        cout << "Do you want to add food utensils? (y/n): ";
        cin >> addUtensilsChoice;
        if (addUtensilsChoice == 'y' || addUtensilsChoice == 'Y') {
            addFoodUtensils(true);
        }
        else {
            addFoodUtensils(false);
        }
    }

    void displayTipOption() {
        int tipChoice;
        cout << "Select delivery tip:\n";
        cout << "1. None\n";
        cout << "2. $1\n";
        cout << "3. $2\n";
        cin >> tipChoice;

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
            cout << "Invalid tip choice. No tip will be added.\n";
            addDeliveryTip(0.0); // Default to no tip
            break;
        }
    }
};

#endif // ORDER_H
