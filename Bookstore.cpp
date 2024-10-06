#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <fstream>
#include <map>

// Book Class
class Book {
public:
    std::string title;
    std::string author;
    std::string category;
    int quantity;
    double price;

    Book(std::string t, std::string a, std::string c, int q, double p)
        : title(t), author(a), category(c), quantity(q), price(p) {}

    void displayBook() const {
        std::cout << std::setw(20) << title
                  << std::setw(20) << author
                  << std::setw(15) << category
                  << std::setw(10) << quantity
                  << std::setw(10) << price << std::endl;
    }
};

// Customer Class
class Customer {
public:
    std::string name;
    std::map<std::string, int> purchases; // book title and quantity purchased

    Customer(const std::string& n) : name(n) {}

    void addPurchase(const std::string& bookTitle, int quantity) {
        purchases[bookTitle] += quantity;
    }

    void displayPurchases() const {
        std::cout << "Customer: " << name << std::endl;
        for (const auto& p : purchases) {
            std::cout << p.first << " - " << p.second << " copies" << std::endl;
        }
    }
};

// Bookstore Class
class Bookstore {
private:
    std::vector<Book> books;
    std::vector<Customer> customers;

public:
    // Add Book to Inventory
    void addBook(const Book& book) {
        books.push_back(book);
    }

    // Display All Books in Inventory
    void displayBooks() const {
        std::cout << std::setw(20) << "Title" 
                  << std::setw(20) << "Author"
                  << std::setw(15) << "Category"
                  << std::setw(10) << "Quantity" 
                  << std::setw(10) << "Price" << std::endl;
        
        for (const auto& book : books) {
            book.displayBook();
        }
    }

    // Search for Books by Title
    void searchBooksByTitle(const std::string& title) const {
        bool found = false;
        for (const auto& book : books) {
            if (book.title.find(title) != std::string::npos) {
                book.displayBook();
                found = true;
            }
        }
        if (!found) {
            std::cout << "No books found with title: " << title << std::endl;
        }
    }

    // Sell Book to a Customer
    bool sellBook(const std::string& title, int quantity, const std::string& customerName) {
        for (auto& book : books) {
            if (book.title == title && book.quantity >= quantity) {
                book.quantity -= quantity;

                // Find or create a customer
                Customer* customer = findCustomer(customerName);
                if (!customer) {
                    customers.emplace_back(customerName);
                    customer = &customers.back();
                }
                customer->addPurchase(title, quantity);
                return true;
            }
        }
        return false;
    }

    // Restock a Book
    bool restockBook(const std::string& title, int quantity) {
        for (auto& book : books) {
            if (book.title == title) {
                book.quantity += quantity;
                return true;
            }
        }
        return false;
    }

    // Generate Inventory Report (Low Stock)
    void generateLowStockReport(int threshold) const {
        std::cout << "Books with stock below " << threshold << ":\n";
        for (const auto& book : books) {
            if (book.quantity < threshold) {
                book.displayBook();
            }
        }
    }

    // Display Customer Purchases
    void displayCustomerPurchases(const std::string& customerName) const {
        const Customer* customer = findCustomer(customerName);
        if (customer) {
            customer->displayPurchases();
        } else {
            std::cout << "Customer not found.\n";
        }
    }

    // Save Bookstore Data to File
    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        for (const auto& book : books) {
            file << book.title << "," << book.author << "," << book.category
                 << "," << book.quantity << "," << book.price << std::endl;
        }
        file.close();
    }

    // Load Bookstore Data from File
    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        std::string title, author, category;
        int quantity;
        double price;
        while (file >> std::ws && std::getline(file, title, ',') &&
               std::getline(file, author, ',') &&
               std::getline(file, category, ',') &&
               file >> quantity >> price) {
            books.emplace_back(title, author, category, quantity, price);
        }
        file.close();
    }

private:
    // Find Customer by Name
    Customer* findCustomer(const std::string& name) {
        for (auto& customer : customers) {
            if (customer.name == name) {
                return &customer;
            }
        }
        return nullptr;
    }

    const Customer* findCustomer(const std::string& name) const {
        for (const auto& customer : customers) {
            if (customer.name == name) {
                return &customer;
            }
        }
        return nullptr;
    }
};

// Main Program
int main() {
    Bookstore bookstore;

    // Load initial data from a file
    bookstore.loadFromFile("books_data.txt");

    int choice;
    do {
        std::cout << "\nOptions:\n";
        std::cout << "1. Display Books\n";
        std::cout << "2. Search Book by Title\n";
        std::cout << "3. Sell Book\n";
        std::cout << "4. Restock Book\n";
        std::cout << "5. Generate Low Stock Report\n";
        std::cout << "6. Display Customer Purchases\n";
        std::cout << "7. Save and Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                bookstore.displayBooks();
                break;
            case 2: {
                std::string title;
                std::cout << "Enter the title to search: ";
                std::cin.ignore();
                std::getline(std::cin, title);
                bookstore.searchBooksByTitle(title);
                break;
            }
            case 3: {
                std::string title, customerName;
                int quantity;
                std::cout << "Enter the title of the book: ";
                std::cin.ignore();
                std::getline(std::cin, title);
                std::cout << "Enter the quantity to sell: ";
                std::cin >> quantity;
                std::cout << "Enter customer name: ";
                std::cin.ignore();
                std::getline(std::cin, customerName);

                if (bookstore.sellBook(title, quantity, customerName))
                    std::cout << "Sale successful.\n";
                else
                    std::cout << "Book not available or insufficient quantity.\n";
                break;
            }
            case 4: {
                std::string title;
                int quantity;
                std::cout << "Enter the title of the book: ";
                std::cin.ignore();
                std::getline(std::cin, title);
                std::cout << "Enter the quantity to restock: ";
                std::cin >> quantity;

                if (bookstore.restockBook(title, quantity))
                    std::cout << "Restock successful.\n";
                else
                    std::cout << "Book not found.\n";
                break;
            }
            case 5: {
                int threshold;
                std::cout << "Enter the threshold for low stock report: ";
                std::cin >> threshold;
                bookstore.generateLowStockReport(threshold);
                break;
            }
            case 6: {
                std::string customerName;
                std::cout << "Enter customer name: ";
                std::cin.ignore();
                std::getline(std::cin, customerName);
                bookstore.displayCustomerPurchases(customerName);
                break
