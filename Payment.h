#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>
#include <iostream>

using namespace std;

class Payment {
private:
    string method;
    double amount;
    string cardNumber;
    string expiryDate;
    string cvv;

public:
    Payment(const string& method, double amount)
        : method(method), amount(amount) {}

    void setCardDetails(const string& cardNumber, const string& expiryDate, const string& cvv) {
        this->cardNumber = cardNumber;
        this->expiryDate = expiryDate;
        this->cvv = cvv;
    }

    bool processPayment() const {
        if (method == "Credit Card") {
            if (cardNumber.empty() || expiryDate.empty() || cvv.empty()) {
                cout << "Incomplete card details. Payment failed.\n";
                return false;
            }
            // Simulate payment processing for demonstration
            cout << "Processing credit card payment...\n";
            cout << "Payment of $" << amount << " was successful.\n";
            return true;
        }
        else if (method == "Cash") {
            cout << "Cash payment to be collected on delivery.\n";
            return true;
        }
        else if (method == "E-Wallet") {
            cout << "Processing e-wallet payment...\n";
            cout << "Payment of $" << amount << " was successful.\n";
            return true;
        }
        else {
            cout << "Unsupported payment method. Payment failed.\n";
            return false;
        }
    }
};

#endif // PAYMENT_H
