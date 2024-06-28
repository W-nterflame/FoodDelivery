#include <iostream>
#include <vector>
#include <stdexcept>
#include <limits>
#include "User.h"
#include "Restaurant.h"
#include "FoodItem.h"
#include "Order.h"
#include "OrderHistory.h"
#include "Delivery.h"
#include "Payment.h"
#include "Driver.h"

using namespace std;

const string ORDER_HISTORY_FILE = "order_history.csv";
const double DIRECT_DELIVERY_PRICE = 5.0;
const double STANDARD_DELIVERY_PRICE = 3.0;
const double SAVER_DELIVERY_PRICE = 1.0;

void displayMainMenu(OrderHistory& orderHistory);
void login();
void newFoodOrder(OrderHistory& orderHistory);
void reorder(OrderHistory& orderHistory);
void assignAndShowDriver();

vector<Restaurant> initializeRestaurants();
vector<Driver> initializeDrivers();

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

    Restaurant r3("Northern Delights");
    r3.addFoodItem(FoodItem("Khao Soi", 10.99, "Spicy yellow curry noodle soup with egg noodles, chicken, and crispy fried noodles."));
    r3.addFoodItem(FoodItem("Sai Oua", 8.99, "Northern Thai sausage with lemongrass, galangal, kaffir lime leaves, and spices."));
    r3.addFoodItem(FoodItem("Nam Prik Ong", 7.50, "Spicy tomato chili dip with vegetables and crispy pork rinds."));
    r3.addFoodItem(FoodItem("Khanom Jeen Nam Ngiao", 8.50, "Northern fermented rice noodles with various curries and toppings."));
    r3.addFoodItem(FoodItem("Mango Sticky Rice", 6.50, "Sweet sticky rice with fresh mango slices and creamy coconut milk."));
    r3.addFoodItem(FoodItem("Chiang Mai Iced Tea", 4.50, "Sweet and refreshing iced tea with condensed milk and tamarind syrup."));
    restaurants.push_back(r3);

    Restaurant r4("Penang Delights");
    r4.addFoodItem(FoodItem("Satay", 12.99, "Marinated skewered chicken or beef grilled to perfection, served with peanut sauce and cucumber relish."));
    r4.addFoodItem(FoodItem("Laksa", 9.99, "Spicy and creamy noodle soup with your choice of protein (chicken, seafood, or vegetarian) and various herbs."));
    r4.addFoodItem(FoodItem("Nasi Lemak", 8.99, "Fragrant coconut rice served with fried anchovies, peanuts, cucumber, sambal (chili paste), and your choice of protein (chicken rendang, fried fish, or egg)."));
    r4.addFoodItem(FoodItem("Char Kway Teow", 8.50, "Stir-fried flat rice noodles with egg, vegetables, seafood (optional), and a savory sauce."));
    r4.addFoodItem(FoodItem("Roti Canai", 5.50, "Crispy flatbread served with rich lentil curry or dhal."));
    r4.addFoodItem(FoodItem("Cendol", 4.50, "Shaved ice dessert with green jelly noodles, coconut milk, and palm sugar syrup."));
    restaurants.push_back(r4);

    Restaurant r5("Ayutthaya Flavours");
    r5.addFoodItem(FoodItem("Pad Thai", 8.99, "Stir-fried rice noodles with egg, vegetables, and your choice of protein (chicken, shrimp, or tofu)."));
    r5.addFoodItem(FoodItem("Khao Pad Sapparot", 9.99, "Pineapple fried rice with shrimp, egg, vegetables, and pineapple chunks."));
    r5.addFoodItem(FoodItem("Tom Yum Goong", 8.99, "Fragrant and sour soup with shrimp, lemongrass, kaffir lime leaves, and mushrooms."));
    r5.addFoodItem(FoodItem("Gaeng Phet", 10.99, "Red curry with your choice of protein (chicken, beef, or vegetables) and bamboo shoots."));
    r5.addFoodItem(FoodItem("Boat Noodles", 3.50, "Small bowls of rice noodles in a rich and flavorful broth with various toppings."));
    r5.addFoodItem(FoodItem("Thai Iced Tea", 3.50, "Sweet and refreshing iced tea with condensed milk."));
    restaurants.push_back(r5);

    Restaurant r6("Warung Sari Rasa");
    r6.addFoodItem(FoodItem("Nasi Goreng Jawa", 8.99, "Fried rice with Javanese spices, vegetables, and your choice of protein (chicken, shrimp, or tempe)."));
    r6.addFoodItem(FoodItem("Gado-Gado", 9.99, "Steamed vegetables with peanut sauce and a fried egg."));
    r6.addFoodItem(FoodItem("Rawon", 10.99, "Beef stew in a rich black broth with kluwek (tropical nut) and herbs."));
    r6.addFoodItem(FoodItem("Soto Ayam", 8.50, "Clear chicken soup with noodles, vegetables, and hard-boiled egg."));
    r6.addFoodItem(FoodItem("Tempe Mendoan", 5.50, "Crispy fried tempeh (fermented soybean cake) with a savory batter."));
    r6.addFoodItem(FoodItem("Kolak Pisang", 4.50, "Sweet dessert soup with bananas, coconut milk, and palm sugar."));
    restaurants.push_back(r6);

    return restaurants;
}

vector<Driver> initializeDrivers() {
    vector<Driver> drivers;
    drivers.push_back(Driver("Somchai Suksawat", "Motorbike - Yamaha FZ", "TH-1234"));
    drivers.push_back(Driver("Wan Ahmad", "Motorbike - Honda Wave", "MY-5678"));
    drivers.push_back(Driver("Naree Ploysuwan", "Motorbike - Suzuki GSX", "TH-8765"));
    drivers.push_back(Driver("Arif Rahman", "Motorbike - Yamaha YZF", "MY-4321"));
    drivers.push_back(Driver("Sirinun Khun", "Motorbike - Kawasaki Ninja", "TH-9988"));
    drivers.push_back(Driver("Kanya Sri", "Motorbike - Yamaha FZ", "TH-3344"));
    drivers.push_back(Driver("Tariq Aziz", "Motorbike - Honda CBR", "MY-5566"));
    return drivers;
}

void login() {
    User users[] = {
        User("sirinun_khun", "khunsirinun2566"),  
        User("thana_suk", "sukthana789"),  
        User("naree_chai", "chainaree456"),  
        User("somchai_phuket", "phuketsomchai2566"), 
        User("winni", "winni1323"), 
        User("wan_ahmad", "ahmadwan123"), 
        User("arif_rahman", "rahmanarif789"), 
        User("lee_wen", "wenlee456"), 
        User("huang_li", "lihuang123"), 
        User("zhang_wei", "weizhang789") 
    };

    string username, password;
    bool authenticated = false;

    while (!authenticated) {
        cout << "-----------------------------------\n";
        cout << "           Welcome to             \n";
        cout << "          Food Delivery            \n";
        cout << "-----------------------------------\n";
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        for (const auto& user : users) {
            if (user.authenticate(username, password)) {
                cout << "\n-----------------------------------\n";
                cout << " Login successful! Welcome, " << username << "!\n";
                cout << "-----------------------------------\n\n";
                authenticated = true;
                break;
            }
        }

        if (!authenticated) {
            cout << "\nInvalid username or password. Please try again.\n\n";
        }
    }
}

void displayMainMenu(OrderHistory& orderHistory) {
    int choice;
    do {
        try {
            cout << "==============================\n";
            cout << "          Main Menu           \n";
            cout << "==============================\n";
            cout << "1. New Food Order\n";
            cout << "2. Reorder\n";
            cout << "3. Exit\n";
            cout << "==============================\n";
            cout << "Enter your choice: ";

            cin >> choice;

            if (cin.fail()) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore incorrect input
                throw invalid_argument("Invalid input. Please enter a valid number.");
            }

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
                throw out_of_range("Invalid choice. Please try again.");
            }
        }
        catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    } while (choice != 3);
}

void newFoodOrder(OrderHistory& orderHistory) {
    try {
        vector<Restaurant> restaurants = initializeRestaurants();
        cout << "-----------------------------------\n";
        cout << "Select a restaurant:\n";
        cout << "-----------------------------------\n";
        for (size_t i = 0; i < restaurants.size(); ++i) {
            cout << i + 1 << ". " << restaurants[i].getName() << "\n";
        }

        int restaurantChoice;
        cout << "Enter the number of the restaurant: ";
        cin >> restaurantChoice;

        if (cin.fail() || restaurantChoice < 1 || restaurantChoice > restaurants.size()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore incorrect input
            throw invalid_argument("Invalid choice. Please select a valid restaurant number.");
        }

        Restaurant selectedRestaurant = restaurants[restaurantChoice - 1];
        Order order;
        order.displayOrderMenu(selectedRestaurant);

        char addDelivery;
        cout << "Add delivery? (y/n): ";
        cin >> addDelivery;
        if (addDelivery == 'y' || addDelivery == 'Y') {
            int deliveryOption;
            cout << "Select delivery option:\n";
            cout << "1. Direct Delivery - $" << DIRECT_DELIVERY_PRICE << endl;
            cout << "2. Standard Delivery - $" << STANDARD_DELIVERY_PRICE << endl;
            cout << "3. Saver Delivery - $" << SAVER_DELIVERY_PRICE << endl;
            cin >> deliveryOption;

            if (cin.fail() || deliveryOption < 1 || deliveryOption > 3) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore incorrect input
                throw invalid_argument("Invalid delivery option. Please select a valid delivery option.");
            }

            // Get delivery address
            string deliveryAddress;
            cout << "Enter delivery address: ";
            cin.ignore(); // Ignore newline left in the buffer
            getline(cin, deliveryAddress);

            switch (deliveryOption) {
            case 1:
                order.setDelivery(Delivery(deliveryAddress, "Direct Delivery", DIRECT_DELIVERY_PRICE));
                break;
            case 2:
                order.setDelivery(Delivery(deliveryAddress, "Standard Delivery", STANDARD_DELIVERY_PRICE));
                break;
            case 3:
                order.setDelivery(Delivery(deliveryAddress, "Saver Delivery", SAVER_DELIVERY_PRICE));
                break;
            default:
                throw invalid_argument("Invalid delivery option.");
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
            cout << "-------------------------\n";
            assignAndShowDriver();
        }
        else {
            cout << "Order cancelled.\n";
        }
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

void reorder(OrderHistory& orderHistory) {
    try {
        const vector<Order>& pastOrders = orderHistory.getOrders();
        if (pastOrders.empty()) {
            throw runtime_error("No past orders found.");
        }

        cout << "Select a past order to reorder:\n";
        cout << "-------------------------\n";
        for (size_t i = 0; i < pastOrders.size(); ++i) {
            cout << "Order " << i + 1 << ":\n";
            pastOrders[i].displayOrderSummary();
            cout << "-------------------------\n";
        }

        int reorderChoice;
        cout << "Enter the number of the order to reorder: ";
        cin >> reorderChoice;

        if (cin.fail() || reorderChoice < 1 || reorderChoice > static_cast<int>(pastOrders.size())) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore incorrect input
            throw invalid_argument("Invalid choice. Please select a valid order number.");
        }

        Order reordered = pastOrders[reorderChoice - 1];
        reordered.displayOrderSummary();

        char confirmOrder;
        cout << "Confirm reorder? (y/n): ";
        cin >> confirmOrder;
        if (confirmOrder == 'y' || confirmOrder == 'Y') {
            orderHistory.addOrder(reordered);
            cout << "Reorder confirmed!\n";
            cout << "-------------------------\n";
            assignAndShowDriver();
        }
        else {
            cout << "Reorder cancelled.\n";
        }

    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

void assignAndShowDriver() {
    vector<Driver> drivers = initializeDrivers();
    if (drivers.empty()) {
        cerr << "No drivers available.\n";
        return;
    }

    int randomIndex = rand() % drivers.size();
    Driver assignedDriver = drivers[randomIndex];

    cout << "Driver Details:\n";
    cout << "Name: " << assignedDriver.getName() << "\n";
    cout << "Vehicle: " << assignedDriver.getVehicle() << "\n";
    cout << "License Plate: " << assignedDriver.getLicensePlate() << "\n";
}

