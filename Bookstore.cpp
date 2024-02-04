#include <iostream>
#include <vector>
#include <iomanip>

class Book {
public:
    std::string title;
    std::string author;
    int quantity;
    double price;

    Book(std::string t, std::string a, int q, double p)
        : title(t), author(a), quantity(q), price(p) {}
};

class Bookstore {
private:
    std::vector<Book> books;

public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void displayBooks() const {
        std::cout << std::setw(20) << "Title" << std::setw(20) << "Author"
                  << std::setw(10) << "Quantity" << std::setw(10) << "Price" << std::endl;

        for (const auto& book : books) {
            std::cout << std::setw(20) << book.title
                      << std::setw(20) << book.author
                      << std::setw(10) << book.quantity
                      << std::setw(10) << book.price << std::endl;
        }
    }

    bool sellBook(const std::string& title, int quantity) {
        for (auto& book : books) {
            if (book.title == title && book.quantity >= quantity) {
                book.quantity -= quantity;
                return true;
            }
        }
        return false;
    }

    bool restockBook(const std::string& title, int quantity) {
        for (auto& book : books) {
            if (book.title == title) {
                book.quantity += quantity;
                return true;
            }
        }
        return false;
    }
};

int main() {
    Bookstore bookstore;

    // Add some initial books to the bookstore
    bookstore.addBook(Book("The Catcher in the Rye", "J.D. Salinger", 50, 10.99));
    bookstore.addBook(Book("To Kill a Mockingbird", "Harper Lee", 30, 12.99));
    bookstore.addBook(Book("1984", "George Orwell", 40, 9.99));

    int choice;
    do {
        std::cout << "\nOptions:\n";
        std::cout << "1. Display Books\n";
        std::cout << "2. Sell Book\n";
        std::cout << "3. Restock Book\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                bookstore.displayBooks();
                break;
            case 2: {
                std::string title;
                int quantity;
                std::cout << "Enter the title of the book: ";
                std::cin.ignore();
                std::getline(std::cin, title);
                std::cout << "Enter the quantity to sell: ";
                std::cin >> quantity;

                if (bookstore.sellBook(title, quantity))
                    std::cout << "Sale successful.\n";
                else
                    std::cout << "Book not available or insufficient quantity.\n";
                break;
            }
            case 3: {
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
            case 4:
                std::cout << "Exiting program.\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 4);

    return 0;
}
