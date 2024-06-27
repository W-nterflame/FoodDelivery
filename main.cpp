#include <iostream>
#include <vector>
#include <stdexcept> 
#include "User.h"
#include "Restaurant.h"
#include "FoodItem.h"
#include "Order.h"
#include "OrderHistory.h"
#include "Delivery.h"
#include "Payment.h"

using namespace std;

const string ORDER_HISTORY_FILE = "order_history.csv";
const double DIRECT_DELIVERY_PRICE = 5.0;
const double STANDARD_DELIVERY_PRICE = 3.0;
const double SAVER_DELIVERY_PRICE = 0.0;

void displayMainMenu(OrderHistory& orderHistory);
void login();
void newFoodOrder(OrderHistory& orderHistory);
void reorder(OrderHistory& orderHistory);

vector<Restaurant> initializeRestaurants();

int main() {
    try {
        login();
        OrderHistory orderHistory(ORDER_HISTORY_FILE);
        displayMainMenu(orderHistory);
    }
    catch (const exception& e) {
        cerr << "Error occurred: " << e.what() << endl;
    }
    return 0;
}

vector<Restaurant> initializeRestaurants() {
    vector<Restaurant> restaurants;

    Restaurant r1("Italian Bistro");
    r1.addFoodItem(FoodItem("Bruschetta", 8.99, "Freshly toasted bread topped with chopped tomatoes, garlic, olive oil, and herbs."));
    r1.addFoodItem(FoodItem("Penne Arrabbiata", 13.50, "Spicy penne pasta with tomato sauce, garlic, and chili flakes."));
    r1.addFoodItem(FoodItem("Chicken Piccata", 19.99, "Tender chicken breast sauteed in a lemon butter sauce with capers."));
    r1.addFoodItem(FoodItem("Shrimp Scampi", 21.99, "Plump shrimp sauteed in garlic, white wine, butter, and lemon juice."));
    r1.addFoodItem(FoodItem("Tiramisu", 7.50, "Classic Italian layered dessert with ladyfingers, coffee, mascarpone cheese, and cocoa powder."));
    restaurants.push_back(r1);

    Restaurant r2("Sushi House");
    r2.addFoodItem(FoodItem("Edamame", 5.99, "Steamed soybeans in their pods."));
    r2.addFoodItem(FoodItem("Salmon Nigiri", 6.50, "Fresh salmon slice on vinegared rice."));
    r2.addFoodItem(FoodItem("Philadelphia Roll", 8.99, "Smoked salmon, cream cheese, and cucumber roll."));
    r2.addFoodItem(FoodItem("Tuna Roll", 8.99, "Fresh purified tuna, rolled with onigiri style sauce."));
    r2.addFoodItem(FoodItem("Green Tea", 2.50, "Refreshing hot or cold green tea."));
    restaurants.push_back(r2);

    Restaurant r3("Aroi Delights");
    r3.addFoodItem(FoodItem("Fresh Spring Rolls", 5.99, "Rice paper rolls with shrimp, pork, vegetables, and peanut dipping sauce."));
    r3.addFoodItem(FoodItem("Ayutthaya Boat Noodle", 2.99, "Classic bowl of mild spicy sour boat noodle."));
    r3.addFoodItem(FoodItem("Pad Thai", 7.99, "Stir-fried rice noodles with egg, vegetables, and your choice of protein."));
    r3.addFoodItem(FoodItem("Tom Yum Goong", 8.99, "Fragrant and sour soup with shrimp, lemongrass, kaffir lime leaves, and mushrooms."));
    r3.addFoodItem(FoodItem("Tom Kha Gai", 8.50, "Creamy coconut soup with chicken, galangal, lemongrass, and kaffir lime leaves."));
    r3.addFoodItem(FoodItem("Thai Iced Tea", 3.50, "Sweet and refreshing iced tea with condensed milk."));
    restaurants.push_back(r3);

    return restaurants;
}

void login() {
    string username;
    string password;
    cout << "Login Menu:\n";
    cout << "Enter your username: ";
    cin >> username;

    cout << "Enter your password: ";
    cin >> password;

    cout << "Login successful.\n";
}

void displayMainMenu(OrderHistory& orderHistory) {
    int choice;
    do {
        cout << "Main Menu\n";
        cout << "1. New Food Order\n";
        cout << "2. Reorder\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            newFoodOrder(orderHistory);
            break;
        case 2:
            reorder(orderHistory);
            break;
        case 3:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 3);
}

void newFoodOrder(OrderHistory& orderHistory) {
    vector<Restaurant> restaurants = initializeRestaurants();
    cout << "Select a restaurant:\n";
    for (size_t i = 0; i < restaurants.size(); ++i) {
        cout << i + 1 << ". " << restaurants[i].getName() << "\n";
    }

    int restaurantChoice;
    cout << "Enter the number of the restaurant: ";
    cin >> restaurantChoice;

    if (restaurantChoice < 1 || restaurantChoice > restaurants.size()) {
        cout << "Invalid choice. Returning to main menu.\n";
        return;
    }

    Restaurant selectedRestaurant = restaurants[restaurantChoice - 1];

    cout << "Menu for " << selectedRestaurant.getName() << ":\n";
    selectedRestaurant.displayMenu();

    Order order;
    order.displayOrderMenu(selectedRestaurant);

    char addDelivery;
    cout << "Add delivery? (y/n): ";
    cin >> addDelivery;
    if (addDelivery == 'y' || addDelivery == 'Y') {
        int deliveryOption;
        cout << "Select delivery option:\n";
        cout << "1. Direct Delivery - $" << DIRECT_DELIVERY_PRICE << "\n";
        cout << "2. Standard Delivery - $" << STANDARD_DELIVERY_PRICE << "\n";
        cout << "3. Saver Delivery - Free\n";
        cin >> deliveryOption;

        switch (deliveryOption) {
        case 1:
            order.setDelivery(Delivery("Direct Delivery", "Fastest delivery option", DIRECT_DELIVERY_PRICE));
            break;
        case 2:
            order.setDelivery(Delivery("Standard Delivery", "Regular delivery time", STANDARD_DELIVERY_PRICE));
            break;
        case 3:
            order.setDelivery(Delivery("Saver Delivery", "Longer delivery time", SAVER_DELIVERY_PRICE));
            break;
        default:
            cout << "Invalid delivery option. No delivery will be added.\n";
            break;
        }
    }

    order.displayUtensilOption();
    order.displayTipOption();

    order.displayOrderSummary();

    char confirmOrder;
    cout << "Confirm order? (y/n): ";
    cin >> confirmOrder;
    if (confirmOrder == 'y' || confirmOrder == 'Y') {
        orderHistory.addOrder(order);
        cout << "Order confirmed!\n";
    }
    else {
        cout << "Order cancelled.\n";
    }
}

void reorder(OrderHistory& orderHistory) {
    const vector<Order>& pastOrders = orderHistory.getOrders();
    if (pastOrders.empty()) {
        cout << "No past orders found.\n";
        return;
    }

    cout << "Select a past order to reorder:\n";
    for (size_t i = 0; i < pastOrders.size(); ++i) {
        cout << "Order " << i + 1 << ":\n";
        pastOrders[i].displayOrderSummary();
        cout << "-------------------------\n";
    }

    int reorderChoice;
    while (true) {
        cout << "Enter the number of the order to reorder: ";
        cin >> reorderChoice;

        if (cin.fail()) {
            cerr << "Invalid input. Please enter a valid integer.\n";
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            continue; // Retry loop
        }

        if (reorderChoice < 1 || reorderChoice > static_cast<int>(pastOrders.size())) {
            cerr << "Invalid choice. Please select a number within the valid range.\n";
            continue; // Retry loop
        }

        break; // Valid input
    }

    Order reordered = pastOrders[reorderChoice - 1];
    reordered.displayOrderSummary();

    char confirmOrder;
    cout << "Confirm reorder? (y/n): ";
    cin >> confirmOrder;
    if (confirmOrder == 'y' || confirmOrder == 'Y') {
        try {
            orderHistory.addOrder(reordered);
            cout << "Reorder confirmed!\n";
        }
        catch (const exception& e) {
            cerr << "Error adding order to history: " << e.what() << "\n";
        }
    }
    else {
        cout << "Reorder cancelled.\n";
    }
}
