#include "User.h"
#include <iostream>
#include <stdexcept>

User::User(const std::string& name, const std::string& userId , int maxBooksAllowed)
    : name(name), userId(userId), maxBooksAllowed(maxBooksAllowed), borrowedBooks{}
{
    if (name.empty()){
        throw std::invalid_argument("Name can't be empty.");
    }
    if (userId.empty()){
        throw std::invalid_argument("User Id can't be empty.");
    }
}

User::User(const std::string& name, const std::string& userId, const std::vector<std::string>& borrowedBooks,int maxBooksAllowed)
    :name(name), userId(userId), maxBooksAllowed(maxBooksAllowed), borrowedBooks(borrowedBooks)
{
    if (name.empty()){
        throw std::invalid_argument("Name can't be empty.");
    }
    if (userId.empty()){
        throw std::invalid_argument("User Id can't be empty.");
    }
}

std::string User::getName() const {return name;}
std::string User::getUserId() const {return userId;}
std::vector<std::string> User::getborrowedBooks() const {return borrowedBooks;}
int User::getmaxBooksAllowed() const {return maxBooksAllowed;}

bool User::canBorrowMore() {
    if (maxBooksAllowed > borrowedBooks.size()){
        return true;
    }
    else{
        return false;
    }
}

void User::addBook(const std::string& isbn){
    if (!canBorrowMore()){
        throw std::runtime_error("User already has max amount of books.");
    }
    else{
        borrowedBooks.push_back(isbn);
    }
}

void User::removeBook(const std::string& isbn){
    auto index = find(borrowedBooks.begin(), borrowedBooks.end(), isbn);
    if (index == borrowedBooks.end()){
        throw std::runtime_error("User doesn't have this book");
    }
    borrowedBooks.erase(index);
}

void User::displayProfile() const{
    std::cout << std::endl << "USER" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "User ID: " << userId << std::endl;
    std::cout << "Borrowed books: ";
    if (borrowedBooks.empty()) {
        std::cout << "none";
    } else {
        std::cout << borrowedBooks[0];
        for (size_t i = 1; i < borrowedBooks.size(); i++){
            std::cout << "|" << borrowedBooks[i];
        }
    }
    std::cout<< std::endl;
    std::cout << "Max books: " << maxBooksAllowed << std::endl;
}