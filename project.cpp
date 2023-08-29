#include <iostream>
#include <algorithm>
#include <cmath>
#include <climits>
#include <vector>
#include <string>
#include <exception>
#include <memory>
using namespace std;

/*
Problem Statement:

Design an E-commerce Inventory Management System for an online store that offers a diverse range of products, including electronics,
furniture, and clothing. The goal is to create a robust system that allows customers to view product categories, select products, and
place orders. The system should handle product stock availability, manage customer orders, and process payments securely through a
payment gateway.
The code covers several key functionalities such as:

1.Creating different types of products (Electronics, Furniture, Clothing) with specific attributes.
2.Managing stock availability for products.
3.Allowing customers to place orders, specifying the quantity of products they want to purchase.
4.Processing payments using a payment gateway
5.Displaying order details and calculating the total bill for the customer.
6.Cancelling order


The Factory Design Pattern is used in the above code to create instances of different product categories (Electronics, Furniture, and
Clothing) based on user input.
The ProductFactory class serves as the factory and abstracts the creation of specific product objects.

In the code, the ProductFactory class provides a static method createProduct(string category) that takes a product category as input.
Based on the provided category, the factory method creates an instance of the corresponding product category (Electronics, Furniture, or
Clothing). The factory method handles the instantiation and initialization of the product objects, shielding the client code from the
internal details.

*/

class PaymentProcessingException : public exception
{
public:
    const char *what()
    {
        return "Payment processing failed.";
    }
};

class ProductNotFoundException : public exception
{
public:
    const char *what()
    {
        return "Product not found in the inventory.";
    }
};

class ProductCreationException : public exception
{
public:
    const char *what()
    {
        return "Failed to create the product. Invalid or missing input.";
    }
};

class InvalidCategoryException : public exception
{
public:
    const char *what()
    {
        return "Invalid Category,the given category of products do not exist.";
    }
};

class InvalidElectronicsException : public exception
{
public:
    const char *what()
    {
        return "Invalid Electronics: The requested item was not found.";
    }
};

class InvalidFurnitureException : public exception
{
public:
    const char *what() const noexcept override
    {
        return "Invalid furniture: The requested item was not found.";
    }
};

class InvalidClothingException : public exception
{
public:
    const char *what() const noexcept override
    {
        return "Invalid clothing: The requested item was not found.";
    }
};

class NegativeQuantityException : public exception
{
public:
    const char *what()
    {
        return "Invalid quantity: Quantity cannot be negative.";
    }
};

class InvalidOrderIDException : public exception
{
public:
    const char *what()
    {
        return "Invalid Order ID. The provided Order ID does not exist.";
    }
};

class Product // abstract class
{
public:
    int product_id;
    string product_name;
    double price;
    int quantity;

    Product()
    {
        product_id = 0;
        price = 0.0;
        quantity = 0;
        this->product_name = "";
    }
    Product(int pid, string pname, double price)
    {
        this->product_id = pid;
        this->product_name = pname;
        this->price = price;
        this->quantity = 1000;
    }

    virtual void displayDetails() = 0;

    bool isOutOfStock()
    {
        return quantity == 0;
    }
    void increaseStock(int quantityToAdd)
    {
        quantity += quantityToAdd;
    }
    double getPrice()
    {
        return price;
    }
    ~Product()
    {
        cout << "Destructor called for product : " << product_name;
    }
};

class Electronics : public Product // abstract class
{
public:
    string brand;

    Electronics() : Product()
    {
        this->brand = "";
    }

    Electronics(int pid, string pname, double price, string brand)
        : Product(pid, pname, price)
    {
        this->brand = brand;
    }

    virtual void displayDetails() = 0;
};

class Furniture : public Product // abstract class
{
public:
    string material;
    Furniture() : Product()
    {
        this->material = "";
    }

    Furniture(int pid, string pname, double price, string material)
        : Product(pid, pname, price)
    {
        this->material = material;
    }

    virtual void displayDetails() = 0;
};

class Clothing : public Product // abstract class
{
public:
    string size;
    string color;
    Clothing() : Product()
    {
        this->size = "";
        this->color = "";
    }

    Clothing(int pid, string pname, double price, string size, string color)
        : Product(pid, pname, price)
    {
        this->size = size;
        this->color = color;
    }

    virtual void displayDetails() = 0;
};

class Laptop : public Electronics
{
public:
    string processor;
    int ram;

    Laptop() : Electronics()
    {
        ram = 0;
        processor = "";
    }
    Laptop(int pid, string pname, double price, string brand, string processor, int ram)
        : Electronics(pid, pname, price, brand)
    {
        this->processor = processor;
        this->ram = ram;
    }
    void displayDetails()
    {
        cout << "Product ID: " << product_id << endl;
        cout << "Name: " << product_name << endl;
        cout << "Price: " << price << endl;
        cout << "Processor: " << processor << endl;
        cout << "RAM: " << ram << "GB" << endl;
    }
};

class Mobile : public Electronics
{
public:
    int storage;
    int ram;
    Mobile() : Electronics()
    {
        storage = 0;
        ram = 0;
    }
    Mobile(int pid, string pname, double price, string brand, int storage, int ram)
        : Electronics(pid, pname, price, brand)
    {
        this->storage = storage;
        this->ram = ram;
    }
    void displayDetails()
    {
        cout << "Product ID: " << product_id << endl;
        cout << "Name: " << product_name << endl;
        cout << "Price: " << price << endl;
        cout << "RAM: " << ram << "GB" << endl;
        cout << "Storage capacity: " << storage << "GB" << endl;
    }
};

class Chair : public Furniture
{
public:
    string color;
    string chair_type;

    Chair() : Furniture()
    {
        this->color = "";
        this->chair_type = "";
    }

    Chair(int pid, string pname, double price, string material, string color, string chair_type)
        : Furniture(pid, pname, price, material)
    {
        this->color = color;
        this->chair_type = chair_type;
    }
    void displayDetails()
    {
        cout << "Product ID: " << product_id << endl;
        cout << "Name: " << product_name << endl;
        cout << "Price: " << price << endl;
        cout << "Chair Type: " << chair_type << endl;
        cout << "Chair color : " << color << endl;
    }
};

class Table : public Furniture
{
public:
    int capacity;

    Table() : Furniture()
    {
        capacity = 0;
    }

    Table(int pid, string pname, double price, string material, int capacity)
        : Furniture(pid, pname, price, material)
    {
        this->capacity = capacity;
    }
    void displayDetails()
    {
        cout << "Product ID: " << product_id << endl;
        cout << "Name: " << product_name << endl;
        cout << "Price: " << price << endl;
        cout << "Table capacity : " << endl;
    }
};

class Shirt : public Clothing
{
public:
    string fabric;
    Shirt() : Clothing()
    {
        this->fabric = "";
    }

    Shirt(int pid, string pname, double price, string size, string color, string fabric)
        : Clothing(pid, pname, price, size, color)
    {
        this->fabric = fabric;
    }

    void displayDetails()
    {
        cout << "Product ID: " << product_id << endl;
        cout << "Name: " << product_name << endl;
        cout << "Price: " << price << endl;
        cout << "Fabric: " << fabric << endl;
        cout << "Color of shirt : " << color << endl;
    }
};

class Jeans : public Clothing
{
public:
    string denim_style;

    Jeans() : Clothing()
    {
        denim_style = "";
    }

    Jeans(int pid, string pname, double price, string size, string color, string denim_style)
        : Clothing(pid, pname, price, size, color)
    {
        this->denim_style = denim_style;
    }

    void displayDetails()
    {
        cout << "Product ID: " << product_id << endl;
        cout << "Name: " << product_name << endl;
        cout << "Price: " << price << endl;
        cout << "Denim Style: " << denim_style << endl;
    }
};

// Factory class for creating products
class ProductFactory
{
public:
    static unique_ptr<Product> createProduct(string category)
    {
        try
        {
            if (category == "Electronics")
            {
                return createElectronicsProduct();
            }
            else if (category == "Furniture")
            {
                return createFurnitureProduct();
            }
            else if (category == "Clothing")
            {
                return createClothingProduct();
            }
            else
            {
                throw InvalidCategoryException();
            }
        }
        catch (InvalidCategoryException &ice)
        {
            cout << ice.what();
        }
        return NULL;
    }

private:

    static unique_ptr<Electronics> createElectronicsProduct()
    {
        char productType;
        cout << "Enter the type of electronics (L for Laptop, M for Mobile): ";
        cin >> productType;

        int productId;
        string productName;
        double price;
        string brand;
        int ram;
        int storage;

        cout << "Enter product ID: ";
        cin >> productId;
        cout << "Enter product name: ";
        cin >> productName;
        cout << "Enter price: ";
        cin >> price;
        cout << "Enter brand: ";
        cin >> brand;
        cout << "Enter RAM : ";
        cin >> ram;


        try
        {
            if (productType == 'L' || productType == 'l')
            {
                return make_unique<Laptop>(productId, productName, price, brand, "Intel", ram);
            }
            else if (productType == 'M' || productType == 'm')
            {
                cout << "Enter storage (for mobiles): ";
                cin >> storage;
                return make_unique<Mobile>(productId, productName, price, brand, storage, ram);
            }
            else
            {
                throw InvalidElectronicsException();
            }
        }
        catch (InvalidElectronicsException &iee)
        {
            cout << iee.what();
        }
        return NULL;

    }

    static unique_ptr<Furniture> createFurnitureProduct()
    {
        char productType;
        cout << "Enter the type of furniture (C for Chair, T for Table): ";
        cin >> productType;

        int productId;
        string productName;
        double price;

        string material;
        int capacity;
        string chairColor;
        string chairType;

        cout << "Enter product ID: ";
        cin >> productId;
        cout << "Enter product name: ";
        cin >> productName;
        cout << "Enter price: ";
        cin >> price;
        cout << "Enter material: ";
        cin >> material;

        try
        {
            if (productType == 'C' || productType == 'c')
            {
                cout << "Enter the chair type: ";
                cin >> chairType;
                cout << "Enter the color of chair : ";
                cin >> chairColor;
                return make_unique<Chair>(productId, productName, price, material, chairColor, chairType);
            }
            else if (productType == 'T' || productType == 't')
            {
                cout << "Enter capacity (for tables): ";
                cin >> capacity;
                return make_unique<Table>(productId, productName, price, material, capacity);
            }
            else
            {
                throw InvalidFurnitureException();
            }
        }
        catch (InvalidFurnitureException &ife)
        {
            cout << ife.what() << endl;
        }
        return NULL;
    }


    static unique_ptr<Clothing> createClothingProduct()
    {
        char productType;
        cout << "Enter the type of clothing (S for Shirt, J for Jeans): ";
        cin >> productType;

        int productId;
        string productName;
        double price;

        string size;
        string color;
        string denim_style;
        string fabric;

        cout << "Enter product ID: ";
        cin >> productId;
        cout << "Enter product name: ";
        cin >> productName;
        cout << "Enter price: ";
        cin >> price;
        cout << "Enter size (for clothing): ";
        cin >> size;
        cout << "Enter color (for clothing): ";
        cin >> color;
        try
        {
            if (productType == 'S' || productType == 's')
            {
                cout << "Enter the fabric of shirt:" << endl;
                cin >> fabric;
                return make_unique<Shirt>(productId, productName, price, size, color, fabric);
            }
            else if (productType == 'J' || productType == 'j')
            {
                cout << "Enter the denim style : ";
                cin >> denim_style;
                return make_unique<Jeans>(productId, productName, price, size, color, denim_style);
            }
            else
            {
                throw InvalidClothingException();
            }
        }
        catch (InvalidClothingException &ice)
        {
            cout << ice.what() << endl;
        }
        return NULL;
    }
};
class Order
{
public:
    int orderId;
    bool isPaid;
    bool isCancelled = false;   // Initialize to false by default
    vector<Product *> products; // Order has products

    Order()
    {
        orderId = 0;
        isPaid = false;
    }
    Order(int orderId, bool isPaid)
    {
        this->orderId = orderId;
        this->isPaid = isPaid;
    }

    void addProduct(Product *product)
    {
        products.push_back(product);
    }
};
class PaymentGateway
{
public:
    bool processPayment()
    {
        cout << "Payment processed successfully!" << endl;
        return true;
    }
};

class Customer
{
public:
    string name;
    int custid;
    string contactNumber;
    string address;
    string emailAddress;
    vector<Order> orders; // customer has Orders

    Customer()
    {
        this->custid = 0;
        this->contactNumber = "";
        this->address = "";
        this->emailAddress = "";
    }
    Customer(string name, int cid, string contact, string address, string email)
    {
        this->name = name;
        this->custid = cid;
        this->contactNumber = contact;
        this->address = address;
        this->emailAddress = email;
    }

    void print()
    {
        cout << "Customer name: " << name << endl;
        cout << "Contact number: " << contactNumber << endl;
        cout << "Address: " << address << endl;
        cout << "Email address: " << emailAddress << endl;
    }

    // Method to place an order
    void placeOrder(vector<Product *> &products, PaymentGateway *paymentGateway);

    void cancelOrder(int orderId)
    {
        for (auto it = orders.begin(); it != orders.end(); it++)
        {
            if (it->orderId == orderId)
            {
                
                // Erase the cancelled order from the customer's orders vector
                orders.erase(it);

                cout << "Order with ID " << orderId << " has been cancelled." << endl;
                return;
            }
        }

        // If the loop finishes without finding the order, throw InvalidOrderIDException
        throw InvalidOrderIDException();
    }
};

void Customer::placeOrder(vector<Product *> &products, PaymentGateway *paymentGateway)
{
    // Create a new order
    static int nextOrderId = 1;
    Order newOrder(nextOrderId++, false);

    // Add all the products present in the vector to the Order of customer
    for (auto product : products)
    {
        newOrder.addProduct(product);
    }


    // Display order details
    cout << "Order Details:" << endl;
    cout << "Order ID: " << newOrder.orderId << endl;
    cout << "Customer Name: " << name << endl;
    cout << "Products: ";
    for (auto product : newOrder.products)
    {
        cout << product->product_name << ", ";
    }
    cout << endl;


    // Process the payment using the payment gateway
    double totalAmount = 0.0;
    for (auto product : newOrder.products)
    {
        totalAmount += product->quantity * product->price;
    }


    if (paymentGateway->processPayment())
    {
        newOrder.isPaid = true;
        orders.push_back(newOrder); // Add the order to the customer's order history
        cout << "Amount to be paid : " << totalAmount << endl;
        cout << "Order successfully placed  !" << endl;
    }
    else
    {
        cout << "Payment failed. Order not placed." << endl;
    }
}

int main()
{
    // Create a PaymentGateway object
    PaymentGateway paymentGateway;

    // Create a customer object
    Customer customer("John Doe", 12345, "9880854465", "123 Main St", "john.doe@gmail.com");

    double totalBill = 0.0;
    char choice;
    try
    {
        int quantity;
        do
        {
            // Ask the user for their choice
            cout << "Select an option:\n";
            cout << "1. Place an order\n";
            cout << "2. Cancel an order\n";
            cout << "3. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == '1')
            {
                char categoryChoice;
                cout << "Select a category (E for Electronics, F for Furniture, C for Clothing): ";
                cin >> categoryChoice;

                // Place an order based on the user's choice
                vector<Product *> products;
                if (categoryChoice == 'E' || categoryChoice == 'e')
                {
                    // Electronics category
                    products.push_back(ProductFactory::createProduct("Electronics").release());
                }
                else if (categoryChoice == 'F' || categoryChoice == 'f')
                {
                    // Furniture category
                    products.push_back(ProductFactory::createProduct("Furniture").release());
                }
                else if (categoryChoice == 'C' || categoryChoice == 'c')
                {
                    // Clothing category
                    products.push_back(ProductFactory::createProduct("Clothing").release());
                }
                else
                {
                    throw ProductNotFoundException();
                }


                // Place the order for the products
                cout << "Enter the quantity for this order: ";
                cin >> quantity;
                if (quantity < 0)
                {
                    throw NegativeQuantityException();
                }
                for (const auto &product : products)
                {
                    product->quantity = quantity; // Set the product quantity to the user input
                }

                try
                {
                    customer.placeOrder(products, &paymentGateway);
                }
                catch (PaymentProcessingException &ex)
                {
                    cout << ex.what() << endl;
                    continue;
                }
                catch (NegativeQuantityException &nqe)
                {
                    cout << nqe.what() << endl;
                }
                catch (exception &ex)
                {
                    cout << "An error occurred: " << ex.what() << endl;
                    continue; // Continue to the next iteration of the loop
                }

                cout << "Order placed successfully!" << endl;
            }
            else if (choice == '2')
            {
                int orderIdToCancel;
                cout << "Enter the Order ID to cancel: ";
                cin >> orderIdToCancel;
                try
                {
                    customer.cancelOrder(orderIdToCancel);
                }
                catch (InvalidOrderIDException &ioe)
                {
                    cout << ioe.what();
                }
            }
            
            else if (choice == '3')
            {
                cout << "Exiting..." << endl;
                break;
            }
            else
            {
                cout << "Invalid choice. Please try again." << endl;
            }

            // Ask the user if they want to place/cancel another order or exit
            cout << "\nDo you want to continue? (Y/N): " << endl;
            cin >> choice;
            cout << endl;

        } while (choice == 'Y' || choice == 'y');
    }
    catch (ProductNotFoundException &pnfe)
    {
        cout << pnfe.what() << endl;
    }

    // Print the final bill
    cout << "=========================================" << endl;
    cout << "           INVOICE - Total Bill          " << endl;
    cout << "=========================================" << endl;
    cout << "Customer Name: " << customer.name << endl;
    cout << "Customer ID: " << customer.custid << endl;
    cout << "Contact Number: " << customer.contactNumber << endl;
    cout << "Address: " << customer.address << endl;
    cout << "Email Address: " << customer.emailAddress << endl;
    cout << "-----------------------------------------" << endl;
    cout << "Order Details:" << endl;

    for (const auto &order : customer.orders)
    {
        if (order.isCancelled == false)
        {
            cout << "Order ID: " << order.orderId << endl;
            cout << "Products: " << endl;
            double subtotal = 0.0;
            for (const auto &product : order.products)
            {
                cout << "- " << product->product_name;
                cout << " x " << product->quantity << " (Price per item: Rs" << product->getPrice() << ")" << endl;
                subtotal += product->getPrice() * product->quantity;
            }
            cout << "Subtotal for this order: Rs. " << subtotal << endl << endl;
            cout << "-----------------------------------------" << endl;

            // Add the subtotal of non-cancelled and in-stock orders to the total bill
            totalBill += subtotal;
        }
    }

    cout << "\nTotal Amount to be Paid: Rs. " << totalBill << endl;
    cout << "=========================================" << endl;

    return 0;
}
