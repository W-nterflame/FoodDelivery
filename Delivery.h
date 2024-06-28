#ifndef DELIVERY_H
#define DELIVERY_H

#include <string>

using namespace std;

class Delivery {
private:
    string address;
    string deliveryOption;
    double deliveryPrice;

public:
    Delivery(const string& addr, const string& option, double price)
        : address(addr), deliveryOption(option), deliveryPrice(price) {}

    string getAddress() const {
        return address;
    }

    void setAddress(const string& addr) {
        address = addr;
    }

    string getDeliveryOption() const {
        return deliveryOption;
    }

    void setDeliveryOption(const string& option) {
        deliveryOption = option;
    }

    double getDeliveryPrice() const {
        return deliveryPrice;
    }

    void setDeliveryPrice(double price) {
        deliveryPrice = price;
    }
};

#endif // DELIVERY_H
