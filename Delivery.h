#ifndef DELIVERY_H
#define DELIVERY_H

#include <string>

class Delivery {
private:
    std::string address;
    std::string deliveryOption;
    double deliveryPrice;

public:
    Delivery(const std::string& addr, const std::string& option, double price)
        : address(addr), deliveryOption(option), deliveryPrice(price) {}

    std::string getAddress() const {
        return address;
    }

    void setAddress(const std::string& addr) {
        address = addr;
    }

    std::string getDeliveryOption() const {
        return deliveryOption;
    }

    void setDeliveryOption(const std::string& option) {
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
