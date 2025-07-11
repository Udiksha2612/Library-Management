#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

class User {
public:
    int id;
    string name;

    User(int i, string n) : id(i), name(n) {}
};

class Book {
private:
    string id;
    string title;
    string author;
    bool isIssued;
    int issuedToUserId;

public:
    Book(string i, string t, string a, bool issued = false, int userId = -1)
        : id(i), title(t), author(a), isIssued(issued), issuedToUserId(userId) {}

    string getid() const { return id; }
    bool getissuedstatus() const { return isIssued; }
    int getIssuedToUserId() const { return issuedToUserId; }

    void issuebook(int userId) {
        isIssued = true;
        issuedToUserId = userId;
    }

    void returnbook() {
        isIssued = false;
        issuedToUserId = -1;
    }

    void displaybook() const {
        cout << left << setw(10) << id << setw(30) << title << setw(20) << author;
        cout << (isIssued ? "Issued to User ID: " + to_string(issuedToUserId) : "Available") << endl;
    }
};

class Library {
private:
    vector<Book> books;
    vector<User> users;

    void saveToFile() {
        ofstream outFile("library_data.txt");
        for (const auto& book : books) {
            outFile << book.getid() << ","
                    << book.getissuedstatus() << ","
                    << book.getIssuedToUserId() << endl;
        }
        outFile.close();
    }

    void loadFromFile() {
        ifstream inFile("library_data.txt");
        string id;
        bool issuedStatus;
        int userId;

        while (inFile >> id >> issuedStatus >> userId) {
            books.emplace_back(id, "Unknown", "Unknown", issuedStatus, userId);
        }
        inFile.close();
    }

public:
    Library() { loadFromFile(); }
    ~Library() { saveToFile(); }

    void addUser(int id, string name) {
        users.push_back(User(id, name));
        cout << "👤 User registered.\n";
    }

    void addbook() {
        string id, title, author;
        cout << "Enter book ID: ";
        cin >> id;
        cout << "Enter book title: ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter author name: ";
        getline(cin, author);
        books.emplace_back(id, title, author);
        cout << "Book added successfully!\n";
    }

    void searchbook() {
        string searchid;
        cout << "Enter book ID to search: ";
        cin >> searchid;
        for (auto& book : books) {
            if (book.getid() == searchid) {
                cout << "Book Found:\n";
                book.displaybook();
                return;
            }
        }
        cout << "Book not found!\n";
    }

    void deletebook() {
        string deleteid;
        cout << "Enter book ID to delete: ";
        cin >> deleteid;
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->getid() == deleteid) {
                books.erase(it);
                cout << "Book deleted successfully!\n";
                return;
            }
        }
        cout << "Book not found!\n";
    }

    void issuebook() {
        string issueid;
        int userId;
        cout << "Enter book ID to issue: ";
        cin >> issueid;
        cout << "Enter user ID: ";
        cin >> userId;

        for (auto& book : books) {
            if (book.getid() == issueid) {
                if (!book.getissuedstatus()) {
                    book.issuebook(userId);
                    cout << "Book issued successfully!\n";
                } else {
                    cout << "Book is already issued!\n";
                }
                return;
            }
        }
        cout << "Book not found!\n";
    }

    void returnbook() {
        string returnid;
        cout << "Enter book ID to return: ";
        cin >> returnid;
        for (auto& book : books) {
            if (book.getid() == returnid) {
                if (book.getissuedstatus()) {
                    book.returnbook();
                    cout << "Book returned successfully!\n";
                } else {
                    cout << "Book is not issued!\n";
                }
                return;
            }
        }
        cout << "Book not found!\n";
    }

    void displaybooks() {
        cout << left << setw(10) << "ID" << setw(30) << "Title" << setw(20) << "Author" << "Status" << endl;
        for (const auto& book : books) {
            book.displaybook();
        }
    }

    void generateReport() {
        cout << "\n📊 Issued Book Report:\n";
        for (const auto& book : books) {
            if (book.getissuedstatus()) {
                cout << "Book ID: " << book.getid()
                     << " issued to User ID: " << book.getIssuedToUserId() << endl;
            }
        }
    }
};

// PART 2: Main menu and main function

// Make sure to include the correct header where Library class is defined if separate

int menu() {
    Library lib;
    int choice;
    while (true) {
        cout << "\n1. Add Book\n2. Search Book\n3. Delete Book\n4. Display All Books\n"
             << "5. Issue Book\n6. Return Book\n7. Register User\n8. Generate Report\n0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: lib.addbook(); break;
            case 2: lib.searchbook(); break;
            case 3: lib.deletebook(); break;
            case 4: lib.displaybooks(); break;
            case 5: lib.issuebook(); break;
            case 6: lib.returnbook(); break;
            case 7: {
                int id;
                string name;
                cout << "Enter User ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Name: ";
                getline(cin, name);
                lib.addUser(id, name);
                break;
            }
            case 8: lib.generateReport(); break;
            case 0: return 0;
            default: cout << "Invalid choice.\n";
        }
    }
}

int main() {
    menu();
    return 0;
}