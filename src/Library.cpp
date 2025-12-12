#include "Library.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
Library::Library(const std::string& dataFile)
    : dataFile(dataFile)
{
    try{
        loadFromFile();
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << std::endl;
        std::cerr << "Creating new empty library." << std::endl;
    }
}

void Library::addBook(const Book& book){
    books.push_back(book);
}

void Library::addUser(const User& user){
    if (findUserByName(user.getName()) != nullptr){
        throw std::runtime_error("User already exists.");
    }
    users.push_back(user);
}

void Library::borrowBook(const std::string& userName, const std::string& isbn){
    Book* book = findBookByISBN(isbn);
    if (book == nullptr){
        throw std::runtime_error("Book not found.");
    }
    User* user = findUserByName(userName);
    if (user == nullptr){
        throw std::runtime_error("User not found.");
    }
    if (!(user->canBorrowMore())){
        throw std::runtime_error("User already has max amount of books.");
    }
    book->borrowBook(userName);
    user->addBook(isbn);
}
void Library::returnBook(const std::string& isbn){
    Book* book = findBookByISBN(isbn);
    if (book == nullptr){
        throw std::runtime_error("Book not found.");
    }
    std::string name = book->getBorrowedBy();
    if (name.empty()){
        throw std::runtime_error("Book is in library.");
    }
    User* user = findUserByName(name);
    if (user == nullptr){
        throw std::runtime_error("User not found.");
    }
    book->returnBook();
    user->removeBook(isbn);
}

Book* Library::findBookByISBN(const std::string& isbn){
    for (auto& book : books){
        if(book.getIsbn() == isbn){
            return &book;
        }
    }
    return nullptr;
}

User* Library::findUserByName(const std::string& name){
    for (auto& user : users){
        if(user.getName() == name){
            return &user;
        }
    }
    return nullptr;
}


void Library::displayAllBooks(){
    std::cout << "---BOOKS---" << std::endl;
    if (books.empty()){
        throw std::runtime_error(" No books.");
    }
    for (auto& book : books){
        book.displayInfo();
    }
}

void Library::displayAllUsers(){
    std::cout << "---USERS---" << std::endl;
    if (users.empty()){
        throw std::runtime_error(" No users.");
    }
    for (auto& user : users){
        user.displayProfile();
    }
}

void Library::saveToFile(){
    std::ofstream fileInput(dataFile);
    if (!fileInput){
        throw std::runtime_error("Can't open file.");
    }
    for (auto& book : books){
        fileInput << "BOOK" << std::endl;
        fileInput << "Title : " << book.getTitle() << std::endl;;
        fileInput << "Author : " << book.getAuthor() << std::endl;;
        fileInput << "Year : " << book.getYear() << std::endl;;
        fileInput << "ISBN : " << book.getIsbn() << std::endl;;
        fileInput << "Available: " << (book.getIsAvailable() ? "yes" : "no") << std::endl;
        fileInput << "BorrowedBy: " << book.getBorrowedBy() << std::endl;
        fileInput << std::endl;
    }

    fileInput << "---USERS---" << std::endl;

    for (auto& user : users){
        fileInput << "Name: " << user.getName() << std::endl;
        fileInput << "UserID: " << user.getUserId() << std::endl;
        fileInput << "Name: " << user.getName() << std::endl;
        std::vector<std::string> realborrowedbooks = user.getborrowedBooks();
        
        std::string string_with_books = "";
        if (!realborrowedbooks.empty()) {
            string_with_books = realborrowedbooks[0];
            for (size_t index = 1; index < realborrowedbooks.size(); index++) {
                string_with_books += "|" + realborrowedbooks[index];
            }
        }
        fileInput << "BorrowedBooks: " << string_with_books << std::endl;
        fileInput << "MaxBooks: " << user.getmaxBooksAllowed() << std::endl;
        fileInput<< std::endl;
    }
    fileInput.close();
}

void Library::loadFromFile(){
    std::ifstream fileOutput(dataFile);
    if (!fileOutput){
        std::cout << "File not found. New library was created." << std::endl;
        std::ofstream newfileOutput(dataFile);
        if (newfileOutput){
            newfileOutput.close();
        }
        return;
    }

    books.clear();
    users.clear();
    
    std::string current_line;
    
    while (std::getline(fileOutput,current_line)){
        if (current_line.empty()){
            continue;
        }
        if (current_line == "BOOK"){

            std::getline(fileOutput,current_line);
            std::string title = current_line.substr(7);

            std::getline(fileOutput,current_line);
            std::string author = current_line.substr(8);

            std::getline(fileOutput,current_line);
            int year = std::stoi(current_line.substr(6));

            std::getline(fileOutput,current_line);
            std::string isbn = current_line.substr(6);

            std::getline(fileOutput,current_line);
            bool available = (current_line.substr(11) == "yes");

            std::getline(fileOutput,current_line);
            std::string borrowedby = current_line.substr(12);
            Book new_book(title,author,year, isbn, available,borrowedby);
            if (!available){
                new_book.borrowBook(borrowedby);
            }
            books.push_back(new_book);
        }
        else if (current_line == "USER"){

            std::getline(fileOutput,current_line);
            std::string name = current_line.substr(6);
            
            std::getline(fileOutput,current_line);
            std::string userId = current_line.substr(8);

            std::getline(fileOutput,current_line);
            std::vector<std::string> borrowedbooks = {};
            current_line.erase(0,15);
            while (size_t end_index = current_line.find("|")){
                if (end_index == std::string::npos){
                    break;
                }
                borrowedbooks.push_back(current_line.substr(0, end_index));
                current_line.erase(0,end_index + 1);
            }
            if (!current_line.empty()){
                borrowedbooks.push_back(current_line);
            }

            std::getline(fileOutput,current_line);
            int maxBooks = std::stoi(current_line.substr(10));
            User new_user(name,userId,borrowedbooks,maxBooks);
            for (auto booksisbn : borrowedbooks){
                findBookByISBN(booksisbn)->borrowBook(name);
            }
            users.push_back(new_user);
        }
    }
    fileOutput.close();
}

std::string Library::numberOfUsersForID() const {return std::to_string(users.size() + 1);}
