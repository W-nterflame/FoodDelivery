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

public:
    Order() : delivery("", "", 0.0) {} // Initialize delivery with default values

    void addItem(const FoodItem& item, int quantity) {
        items.push_back(item);
        quantities.push_back(quantity);
    }

    const std::vector<FoodItem>& getItems() const {
        return items;
    }

    const std::vector<int>& getQuantities() const {
        return quantities;
    }

    double calculateTotal() const {
        double subtotal = 0.0;
        for (size_t i = 0; i < items.size(); ++i) {
            subtotal += items[i].getPrice() * quantities[i];
        }
        return subtotal + delivery.getDeliveryPrice(); // Include delivery price in total
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
