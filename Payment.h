#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>
#include <iostream>

class Payment {
private:
    std::string method;
    double amount;
    std::string cardNumber;
    std::string expiryDate;
    std::string cvv;

public:
    Payment(const std::string& method, double amount)
        : method(method), amount(amount) {}

    void setCardDetails(const std::string& cardNumber, const std::string& expiryDate, const std::string& cvv) {
        this->cardNumber = cardNumber;
        this->expiryDate = expiryDate;
        this->cvv = cvv;
    }

    bool processPayment() const {
        if (method == "Credit Card") {
            if (cardNumber.empty() || expiryDate.empty() || cvv.empty()) {
                std::cout << "Incomplete card details. Payment failed.\n";
                return false;
            }
            // Simulate payment processing for demonstration
            std::cout << "Processing credit card payment...\n";
            std::cout << "Payment of $" << amount << " was successful.\n";
            return true;
        }
        else if (method == "Cash") {
            std::cout << "Cash payment to be collected on delivery.\n";
            return true;
        }
        else if (method == "E-Wallet") {
            std::cout << "Processing e-wallet payment...\n";
            std::cout << "Payment of $" << amount << " was successful.\n";
            return true;
        }
        else {
            std::cout << "Unsupported payment method. Payment failed.\n";
            return false;
        }
    }
};

#endif // PAYMENT_H
