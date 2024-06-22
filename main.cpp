#include <iostream>
#include <vector>
#include <stdexcept> // For std::runtime_error
#include "User.h"
#include "Restaurant.h"
#include "FoodItem.h"
#include "Order.h"
#include "OrderHistory.h"
#include "Delivery.h"
#include "Payment.h"

const std::string ORDER_HISTORY_FILE = "order_history.csv";
const double DIRECT_DELIVERY_PRICE = 5.0;
const double STANDARD_DELIVERY_PRICE = 3.0;
const double SAVER_DELIVERY_PRICE = 0.0;

void displayMainMenu(OrderHistory& orderHistory);
void login();
void newFoodOrder(OrderHistory& orderHistory);
void reorder(OrderHistory& orderHistory);   

std::vector<Restaurant> initializeRestaurants();

int main() {
    try {
        login();
        OrderHistory orderHistory(ORDER_HISTORY_FILE);
        displayMainMenu(orderHistory);
    }
    catch (const std::exception& e) {
        std::cerr << "Error occurred: " << e.what() << std::endl;
    }
    return 0;
}

std::vector<Restaurant> initializeRestaurants() {
    std::vector<Restaurant> restaurants;

    Restaurant r1("Italian Bistro");
    r1.addFoodItem(FoodItem("Spaghetti Carbonara", 12.99, "Classic Italian pasta dish with creamy sauce."));
    r1.addFoodItem(MainCourse("Filet Mignon", 24.99, "Tender filet mignon steak grilled to perfection.", "Steakhouse Special"));
    restaurants.push_back(r1);

    Restaurant r2("Sushi House");
    r2.addFoodItem(FoodItem("California Roll", 8.99, "Crab, avocado, and cucumber roll."));
    r2.addFoodItem(FoodItem("Spicy Tuna Roll", 9.99, "Tuna, spicy mayo, and cucumber roll."));
    restaurants.push_back(r2);

    return restaurants;
}

void login() {
    User users[5] = {
        User("user1", "pass1"),
        User("user2", "pass2"),
        User("user3", "pass3"),
        User("user4", "pass4"),
        User("user5", "pass5")
    };

    std::string username, password;
    bool authenticated = false;

    while (!authenticated) {
        std::cout << "Enter username: ";
        std::cin >> username;
        std::cout << "Enter password: ";
        std::cin >> password;

        for (const auto& user : users) {
            if (user.authenticate(username, password)) {
                std::cout << "Login successful!" << std::endl;
                authenticated = true;
                break;
            }
        }

        if (!authenticated) {
            std::cout << "Invalid username or password. Please try again." << std::endl;
        }
    }
}

void displayMainMenu(OrderHistory& orderHistory) {
    int choice;
    do {
        std::cout << "\nMain Menu\n";
        std::cout << "1. New Food Order\n";
        std::cout << "2. Reorder\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            newFoodOrder(orderHistory);
            break;
        case 2:
            reorder(orderHistory);
            break;
        case 3:
            std::cout << "Exiting the program." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 3);
}

void newFoodOrder(OrderHistory& orderHistory) {
    std::vector<Restaurant> restaurants = initializeRestaurants();

    std::cout << "\nSelect a restaurant:\n";
    for (size_t i = 0; i < restaurants.size(); ++i) {
        std::cout << i + 1 << ". " << restaurants[i].getName() << "\n";
    }

    int restaurantChoice;
    std::cin >> restaurantChoice;
    if (restaurantChoice < 1 || restaurantChoice > restaurants.size()) {
        std::cout << "Invalid choice. Returning to main menu.\n";
        return;
    }

    Restaurant selectedRestaurant = restaurants[restaurantChoice - 1];
    selectedRestaurant.displayMenu();

    Order order;
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

        order.addItem(selectedItem, quantity);

        std::cout << "Add more items? (y/n): ";
        std::cin >> addMore;
    } while (addMore == 'y' || addMore == 'Y');

    order.displayOrderSummary();

    // Add food utensils option
    char addUtensilsChoice;
    std::cout << "Do you want to add food utensils? (y/n): ";
    std::cin >> addUtensilsChoice;
    if (addUtensilsChoice == 'y' || addUtensilsChoice == 'Y') {
        order.addFoodUtensils(true);
    }
    else {
        order.addFoodUtensils(false);
    }

    // Add delivery tip option
    int tipChoice;
    std::cout << "Select delivery tip:\n";
    std::cout << "1. None\n";
    std::cout << "2. $1\n";
    std::cout << "3. $2\n";
    std::cin >> tipChoice;

    switch (tipChoice) {
    case 1:
        order.addDeliveryTip(0.0); // No tip
        break;
    case 2:
        order.addDeliveryTip(1.0); // $1 tip
        break;
    case 3:
        order.addDeliveryTip(2.0); // $2 tip
        break;
    default:
        std::cout << "Invalid tip choice. No tip will be added.\n";
        order.addDeliveryTip(0.0); // Default to no tip
        break;
    }

    order.displayOrderSummary(); // Display order summary again with utensils and tip

    std::string address, deliveryOption;
    double deliveryPrice = 0.0;

    std::cout << "\nEnter delivery address: ";
    std::cin.ignore(); // To clear the newline left by previous input
    std::getline(std::cin, address);

    std::cout << "Select delivery option:\n";
    std::cout << "1. Direct (<30 mins)\n";
    std::cout << "2. Standard (45 mins)\n";
    std::cout << "3. Saver (60 mins)\n";
    int deliveryChoice;
    std::cin >> deliveryChoice;

    switch (deliveryChoice) {
    case 1:
        deliveryOption = "Direct (<30 mins)";
        deliveryPrice = DIRECT_DELIVERY_PRICE;
        break;
    case 2:
        deliveryOption = "Standard (45 mins)";
        deliveryPrice = STANDARD_DELIVERY_PRICE;
        break;
    case 3:
        deliveryOption = "Saver (60 mins)";
        deliveryPrice = SAVER_DELIVERY_PRICE;
        break;
    default:
        std::cout << "Invalid choice. Returning to main menu.\n";
        return;
    }

    Delivery delivery(address, deliveryOption, deliveryPrice);
    order.setDelivery(delivery);

    order.displayOrderSummary(); // Display final order summary

    std::cout << "\nSelect payment method:\n";
    std::cout << "1. Cash on Delivery\n";
    std::cout << "2. E-Wallet\n";
    std::cout << "3. Credit Card\n";

    int paymentChoice;
    std::cin >> paymentChoice;

    std::string paymentMethod;
    switch (paymentChoice) {
    case 1:
        paymentMethod = "Cash";
        break;
    case 2:
        paymentMethod = "E-Wallet";
        break;
    case 3:
        paymentMethod = "Credit Card";
        break;
    default:
        std::cout << "Invalid choice. Returning to main menu.\n";
        return;
    }

    double totalAmount = order.calculateTotal();
    Payment payment(paymentMethod, totalAmount);

    if (paymentMethod == "Credit Card") {
        std::string cardNumber, expiryDate, cvv;
        std::cout << "Enter card number: ";
        std::cin.ignore(); // To clear the newline left by previous input
        std::getline(std::cin, cardNumber);
        std::cout << "Enter expiry date (MM/YY): ";
        std::getline(std::cin, expiryDate);
        std::cout << "Enter CVV: ";
        std::getline(std::cin, cvv);
        payment.setCardDetails(cardNumber, expiryDate, cvv);
    }

    if (payment.processPayment()) {
        orderHistory.addOrder(order);
        std::cout << "\nPayment successful. Your order is on its way!\n";
    }
    else {
        std::cout << "\nPayment failed. Please try again.\n";
    }
}


void reorder(OrderHistory& orderHistory) {
    if (orderHistory.getOrderHistory().empty()) {
        std::cout << "No previous orders found.\n";
        return;
    }

    std::cout << "\nPrevious Orders:\n";
    const std::vector<Order>& history = orderHistory.getOrderHistory();
    for (size_t i = 0; i < history.size(); ++i) {
        std::cout << i + 1 << ". Order " << i + 1 << " - Total: $" << history[i].calculateTotal() << "\n";
    }

    int orderChoice;
    std::cout << "\nEnter the number of the order to reorder: ";
    std::cin >> orderChoice;

    if (orderChoice < 1 || orderChoice > history.size()) {
        std::cout << "Invalid choice. Returning to main menu.\n";
        return;
    }

    Order reorder = history[orderChoice - 1];
    reorder.displayOrderSummary();

    std::string address, deliveryOption;
    double deliveryPrice = 0.0;

    std::cout << "\nEnter delivery address: ";
    std::cin.ignore(); // To clear the newline left by previous input
    std::getline(std::cin, address);

    std::cout << "Select delivery option:\n";
    std::cout << "1. Direct (<30 mins)\n";
    std::cout << "2. Standard (45 mins)\n";
    std::cout << "3. Saver (60 mins)\n";
    int deliveryChoice;
    std::cin >> deliveryChoice;

    switch (deliveryChoice) {
    case 1:
        deliveryOption = "Direct (<30 mins)";
        deliveryPrice = DIRECT_DELIVERY_PRICE;
        break;
    case 2:
        deliveryOption = "Standard (45 mins)";
        deliveryPrice = STANDARD_DELIVERY_PRICE;
        break;
    case 3:
        deliveryOption = "Saver (60 mins)";
        deliveryPrice = SAVER_DELIVERY_PRICE;
        break;
    default:
        std::cout << "Invalid choice. Returning to main menu.\n";
        return;
    }

    Delivery delivery(address, deliveryOption, deliveryPrice);
    reorder.setDelivery(delivery);

    reorder.displayOrderSummary(); // Display order summary again with delivery details

    std::cout << "\nSelect payment method:\n";
    std::cout << "1. Cash on Delivery\n";
    std::cout << "2. E-Wallet\n";
    std::cout << "3. Credit Card\n";

    int paymentChoice;
    std::cin >> paymentChoice;

    std::string paymentMethod;
    switch (paymentChoice) {
    case 1:
        paymentMethod = "Cash";
        break;
    case 2:
        paymentMethod = "E-Wallet";
        break;
    case 3:
        paymentMethod = "Credit Card";
        break;
    default:
        std::cout << "Invalid choice. Returning to main menu.\n";
        return;
    }

    double totalAmount = reorder.calculateTotal();
    totalAmount += deliveryPrice; // Add delivery cost to total amount
    Payment payment(paymentMethod, totalAmount);

    if (paymentMethod == "Credit Card") {
        std::string cardNumber, expiryDate, cvv;
        std::cout << "Enter card number: ";
        std::cin.ignore(); // To clear the newline left by previous input
        std::getline(std::cin, cardNumber);
        std::cout << "Enter expiry date (MM/YY): ";
        std::getline(std::cin, expiryDate);
        std::cout << "Enter CVV: ";
        std::getline(std::cin, cvv);
        payment.setCardDetails(cardNumber, expiryDate, cvv);
    }

    if (payment.processPayment()) {
        orderHistory.addOrder(reorder);
        std::cout << "\nPayment successful. Your order is on its way!\n";
    }
    else {
        std::cout << "\nPayment failed. Please try again.\n";
    }
}
