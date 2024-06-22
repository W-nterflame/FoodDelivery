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
};

#endif // ORDER_H
