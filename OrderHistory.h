#ifndef ORDER_HISTORY_H
#define ORDER_HISTORY_H

#include <fstream>
#include <stdexcept>
#include "Order.h"

using namespace std;

class OrderHistory {
private:
    vector<Order> orders;
    string filename; // Filename for storing orders

public:
    OrderHistory(const string& file) : filename(file) {}

    void addOrder(const Order& order) {
        orders.push_back(order);
        try {
            saveOrderToFile(order);
        }
        catch (const exception& e) {
            cerr << "Error occurred while saving order: " << e.what() << endl;
        }
    }

    void saveOrderToFile(const Order& order) {
        ofstream file(filename, ios::app); // Append mode
        if (file.is_open()) {
            file << "Order Details\n";
            file << "Delivery Option: " << order.getDelivery().getDeliveryOption() << "\n";
            file << "Delivery Address: " << order.getDelivery().getAddress() << "\n";
            file << "Delivery Price: $" << order.getDelivery().getDeliveryPrice() << "\n";
            file << "Items Ordered:\n";
            for (size_t i = 0; i < order.getItems().size(); ++i) {
                file << order.getItems()[i].getName() << ","
                    << order.getQuantities()[i] << ",";
                if (!order.getItems()[i].getSpecialInstructions().empty()) {
                    file << "Special Instructions: " << order.getItems()[i].getSpecialInstructions();
                }
                file << "\n";
            }
            file << "Food Utensils: " << (order.getHasUtensils() ? "Yes - $0.5\n" : "No\n");
            file << "Tip: $" << order.getTipAmount() << "\n";
            file << "Total Amount: $" << order.calculateTotal() << "\n";
            file << "------------------------------------\n";
            file.close();
        }
        else {
            throw runtime_error("Unable to open file for saving orders.");
        }
    }

    const vector<Order>& getOrders() const {
        return orders;
    }
};

#endif // ORDER_HISTORY_H
