#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <map>

using namespace std;

struct Book {
    string title;
    string author;
    string ISBN;
    bool isAvailable;

    Book(string t, string a, string i) : title(t), author(a), ISBN(i), isAvailable(true) {}
};

struct Borrower {
    string name;
    map<string, time_t> borrowedBooks; // ISBN -> due date
};

vector<Book> books;
vector<Borrower> borrowers;
const int finePerDay = 1; // Assume a fine of 1 unit per day for simplicity

void addBook() {
    string title, author, ISBN;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);
    cout << "Enter book ISBN: ";
    getline(cin, ISBN);
    books.push_back(Book(title, author, ISBN));
    cout << "Book added successfully." << endl;
}

void searchBook() {
    int choice;
    string query;
    cout << "Search by: 1. Title 2. Author 3. ISBN\nEnter choice: ";
    cin >> choice;
    cout << "Enter query: ";
    cin.ignore();
    getline(cin, query);

    for (const auto& book : books) {
        if ((choice == 1 && book.title.find(query) != string::npos) ||
            (choice == 2 && book.author.find(query) != string::npos) ||
            (choice == 3 && book.ISBN.find(query) != string::npos)) {
            cout << "Title: " << book.title << ", Author: " << book.author 
                 << ", ISBN: " << book.ISBN << ", Available: " 
                 << (book.isAvailable ? "Yes" : "No") << endl;
        }
    }
}

void checkoutBook() {
    string borrowerName, ISBN;
    cout << "Enter borrower's name: ";
    cin.ignore();
    getline(cin, borrowerName);
    cout << "Enter book ISBN: ";
    getline(cin, ISBN);

    for (auto& book : books) {
        if (book.ISBN == ISBN && book.isAvailable) {
            book.isAvailable = false;
            time_t now = time(0);
            time_t dueDate = now + 14 * 24 * 60 * 60; // 2 weeks from now

            for (auto& borrower : borrowers) {
                if (borrower.name == borrowerName) {
                    borrower.borrowedBooks[ISBN] = dueDate;
                    cout << "Book checked out successfully. Due date: " << ctime(&dueDate);
                    return;
                }
            }

            Borrower newBorrower;
            newBorrower.name = borrowerName;
            newBorrower.borrowedBooks[ISBN] = dueDate;
            borrowers.push_back(newBorrower);
            cout << "Book checked out successfully. Due date: " << ctime(&dueDate);
            return;
        }
    }

    cout << "Book is not available or ISBN not found." << endl;
}

void returnBook() {
    string borrowerName, ISBN;
    cout << "Enter borrower's name: ";
    cin.ignore();
    getline(cin, borrowerName);
    cout << "Enter book ISBN: ";
    getline(cin, ISBN);

    for (auto& borrower : borrowers) {
        if (borrower.name == borrowerName) {
            auto it = borrower.borrowedBooks.find(ISBN);
            if (it != borrower.borrowedBooks.end()) {
                time_t now = time(0);
                if (now > it->second) {
                    int overdueDays = (now - it->second) / (24 * 60 * 60);
                    int fine = overdueDays * finePerDay;
                    cout << "Book is overdue. Fine: " << fine << " units." << endl;
                } else {
                    cout << "Book returned on time. No fine." << endl;
                }

                borrower.borrowedBooks.erase(it);

                for (auto& book : books) {
                    if (book.ISBN == ISBN) {
                        book.isAvailable = true;
                        break;
                    }
                }

                return;
            }
        }
    }

    cout << "Borrower or ISBN not found." << endl;
}

void userInterface() {
    int choice;
    do {
        cout << "\nLibrary Management System" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Search Book" << endl;
        cout << "3. Checkout Book" << endl;
        cout << "4. Return Book" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                searchBook();
                break;
            case 3:
                checkoutBook();
                break;
            case 4:
                returnBook();
                break;
            case 5:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);
}

int main() {
    userInterface();
    return 0;
}


//OUTPUT
/*
Library Management System
1. Add Book
2. Search Book
3. Checkout Book
4. Return Book
5. Exit
Enter your choice: 1
Enter book title: Mookajjiya Kanasugalu
Enter book author: K Shivarama Karanta
Enter book ISBN: 23MK03
Book added successfully.

Library Management System
1. Add Book
2. Search Book
3. Checkout Book
4. Return Book
5. Exit
Enter your choice: 1
Enter book title: Nenapina Doniyalli
Enter book author: Kuvempu
Enter book ISBN: 14ND95
Book added successfully.

Library Management System
1. Add Book
2. Search Book
3. Checkout Book
4. Return Book
5. Exit
Enter your choice: 2
Search by: 1. Title 2. Author 3. ISBN
Enter choice: 3
Enter query: 14ND95
Title: Nenapina Doniyalli, Author: Kuvempu, ISBN: 14ND95, Available: Yes

Library Management System
1. Add Book
2. Search Book
3. Checkout Book
4. Return Book
5. Exit
Enter your choice: 3
Enter borrower's name: Deepa S R
Enter book ISBN: 23MK03
Book checked out successfully. Due date: Wed Aug 28 10:02:38 2024

Library Management System
1. Add Book
2. Search Book
3. Checkout Book
4. Return Book
5. Exit
Enter your choice: 4
Enter borrower's name: Sharath
Enter book ISBN: 14ND95
Borrower or ISBN not found.

Library Management System
1. Add Book
2. Search Book
3. Checkout Book
4. Return Book
5. Exit
Enter your choice: 4
Enter borrower's name: Deepa S R
Enter book ISBN: 23MK03
Book returned on time. No fine.

Library Management System
1. Add Book
2. Search Book
3. Checkout Book
4. Return Book
5. Exit
Enter your choice: 5
Exiting...
  */
