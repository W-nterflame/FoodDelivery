#ifndef ORDERHISTORY_H
#define ORDERHISTORY_H

#include <vector>
#include <fstream>
#include "Order.h"

class OrderHistory {
private:
    std::vector<Order> orders;
    std::string filename; // Filename for storing orders

public:
    OrderHistory(const std::string& file) : filename(file) {}

    void addOrder(const Order& order) {
        orders.push_back(order);
        saveOrderToFile(order);
    }

    void saveOrderToFile(const Order& order) {
        std::ofstream file(filename, std::ios::app); // Append mode
        if (file.is_open()) {
            file << "Order Details\n";
            file << "Delivery Address: " << order.getDelivery().getAddress() << "\n";
            file << "Delivery Option: " << order.getDelivery().getDeliveryOption() << "\n";
            file << "Delivery Price: " << order.getDelivery().getDeliveryPrice() << "\n";
            file << "Items Ordered:\n";
            for (size_t i = 0; i < order.getItems().size(); ++i) {
                file << order.getItems()[i].getName() << ","
                    << order.getQuantities()[i] << ",";
                if (!order.getItems()[i].getSpecialInstructions().empty()) {
                    file << order.getItems()[i].getSpecialInstructions();
                }
                file << "\n";
            }
            file << "Food Utensils: " << (order.getHasUtensils() ? "Yes - $0.5\n" : "No\n");
            file << "Tip: $" << order.getTipAmount() << "\n";
            file << "Total Amount: " << order.calculateTotal() << "\n";
            file << "------------------------------------\n";
            file.close();
        }
        else {
            throw std::runtime_error("Unable to open file for saving orders.");
        }
    }

    const std::vector<Order>& getOrderHistory() const {
        return orders;
    }
};

#endif // ORDERHISTORY_H
