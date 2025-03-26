#include <iostream>
#include <cmath>
using namespace std;

const double VAT_RATE = 0.05;
const double DELIVERY_COST_PER_KM = 0.5;

// Function to display the menu
void displayMenu(const string menuNames[], const double menuPrices[], int size)
{
    cout << "Menu: " << endl;
    for (int i = 0; i < size; ++i)
    {
        cout << i + 1 << ". " << menuNames[i] << " - AED " << menuPrices[i] << endl;
    }
}

// Function to add items to the cart
void addToCart(const string menuNames[], const double menuPrices[], int cartItems[], int& cartSize, int menuSize)
{
    displayMenu(menuNames, menuPrices, menuSize);

    int choice;
    int quantity;

    do {
        cout << "Enter the item number to add to your cart (0 to checkout): ";
        cin >> choice;
        // Check if the input is not a number
        if (cin.fail()) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(256, '\n');
            continue;
        }

        if (choice == 0)
        {
            break;
        }

        if (choice >= 1 && choice <= menuSize)
        {
            cout << "Enter the quantity: ";
            cin >> quantity;
            // Check if the input is not a positive number
            if (cin.fail() || quantity <= 0) {
                cout << "Invalid input. Please enter a positive number for quantity." << endl;
                cin.clear();
                cin.ignore(256, '\n');
                continue;
            }

            // Store the selected item index and quantity in the cart
            cartItems[cartSize++] = choice - 1;  // Store the index of the selected item
            cartItems[cartSize++] = quantity;    // Store the quantity
        }
        else {
            cout << "Invalid choice. Please select a valid item." << endl;
        }

    } while (true);
}

// Function to calculate the total cost
double calculateTotalCost(const string menuNames[], const double menuPrices[], const int cartItems[], int cartSize, double deliveryDistance)
{
    double subtotal = 0;

    // Calculate the subtotal of items in the cart
    for (int i = 0; i < cartSize; i += 2)
    {
        int itemIndex = cartItems[i];
        int quantity = cartItems[i + 1];
        subtotal += menuPrices[itemIndex] * quantity;
    }

    // Calculate delivery cost
    double deliveryCost = DELIVERY_COST_PER_KM * deliveryDistance;
    // Calculate total cost before VAT
    double totalBeforeVAT = subtotal + deliveryCost;
    // Calculate VAT
    double vat = totalBeforeVAT * VAT_RATE;
    // Calculate the final total cost
    double total = totalBeforeVAT + vat;

    return total;
}

int main()
{
    const int NUM_RESTAURANTS = 5;
    const int MAX_MENU_SIZE = 5;

    // Define menus for different restaurants.
    string restaurantNames[NUM_RESTAURANTS] = { "Subway", "Papa Johns", "M14 Cafe", "Starbucks", "Dunkin" };

    string menuNames[NUM_RESTAURANTS][MAX_MENU_SIZE] =
    {
        {"Oven Roasted Chicken Sandwich", "Turkey Breast 6 Inch Meal", "Hash Browns", "Potato Crispers", "Orange Juice"},
        {"Butter Chicken", "Cheddar Makhani", "Cheddar Cheese Sticks", "Potato Wedges", "KKD Fruit Juice"},
        {"Gourmet Beef Slider", "Chicken Quinoa Salad", "Cheese Chicken Mushroom Pizza", "Avocado Quinoa Salad", "Strawberry Matcha Latte Cold"},
        {"Matcha Latte", "Cappuccino", "Spanish Latte", "Burnt Basque Cheesecake", "Original Chocolate Cake"},
        {"Half Dozen Donuts", "Box Of 3 Donuts", "Iced Latte", "Chocolate �clair", "Matcha Green Tea"}
    };

    double menuPrices[NUM_RESTAURANTS][MAX_MENU_SIZE] =
    {
        {23.0, 36.0, 10.0, 10.0, 13.0},
        {30.0, 36.0, 24.0, 12.0, 9.0},
        {37.0, 40.0, 45.0, 35.0, 30.0},
        {23.0, 20.0, 26.0, 23.0, 25.0},
        {35.0, 19.0, 17.0, 5.0, 12.0}
    };

    int restaurantChoice;

    do {
        cout << "Select a restaurant:" << endl;
        for (int i = 0; i < NUM_RESTAURANTS; ++i)
        {
            cout << i + 1 << ". " << restaurantNames[i] << endl;
        }

        cout << "Enter your choice: ";
        cin >> restaurantChoice;
        // Check if the input is not a number or out of range
        if (cin.fail() || restaurantChoice < 1 || restaurantChoice > NUM_RESTAURANTS)
        {
            cout << "Invalid restaurant choice. Please enter a number between 1 and " << NUM_RESTAURANTS << "." << endl;
            cin.clear();
            cin.ignore(256, '\n');
        }
        else {
            break;
        }

    } while (true);

    int cartItems[2 * MAX_MENU_SIZE];
    int cartSize = 0;

    // Ask the user to add items to their cart
    addToCart(menuNames[restaurantChoice - 1], menuPrices[restaurantChoice - 1], cartItems, cartSize, MAX_MENU_SIZE);

    double deliveryDistance;

    do {
        cout << "Enter the delivery distance (in kilometers): ";
        cin >> deliveryDistance;
        // Check if the input is not a positive number
        if (cin.fail() || deliveryDistance <= 0)
        {
            cout << "Invalid input. Please enter a positive number for delivery distance." << endl;
            cin.clear();
            cin.ignore(256, '\n');
        }
        else {
            break;
        }

    } while (true);

    // Calculate the total cost
    double totalCost = calculateTotalCost(menuNames[restaurantChoice - 1], menuPrices[restaurantChoice - 1], cartItems, cartSize, deliveryDistance);

    // Display the invoice
    cout << "Your Bill:" << endl;
    for (int i = 0; i < cartSize; i += 2)
    {
        int itemIndex = cartItems[i];
        int quantity = cartItems[i + 1];
        cout << menuNames[restaurantChoice - 1][itemIndex] << " - AED "
            << menuPrices[restaurantChoice - 1][itemIndex] << " x " << quantity
            << " = AED " << menuPrices[restaurantChoice - 1][itemIndex] * quantity << endl;
    }

    cout << "Delivery fees - " << deliveryDistance << " x AED " << DELIVERY_COST_PER_KM
        << " = AED " << deliveryDistance * DELIVERY_COST_PER_KM << endl;

    cout << "Total without VAT - AED " << totalCost / (1 + VAT_RATE) << endl;
    cout << "VAT (" << VAT_RATE * 100 << "%) - AED "
        << totalCost / (1 + VAT_RATE) * VAT_RATE << endl;

    cout << "Total - AED " << totalCost << endl;

    return 0;
}