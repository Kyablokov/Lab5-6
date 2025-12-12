#include "Book.h"
#include <iostream>
#include <stdexcept>

Book::Book(const std::string& title, const std::string& author, int year,const  std::string& isbn)
    : title(title), author(author), year(year), isbn(isbn), isAvailable(true), borrowedBy("")
{
    if (title.empty()){
        throw std::invalid_argument("Title can't be empty.");
    }
    if (author.empty()){
        throw std::invalid_argument("Author can't be empty.");
    }
    if (year > 2025 || year < 1450){
        throw std::invalid_argument("Wrong year. Year must be between 1450 and 2025.");
    }
    if (isbn.empty()){
        throw std::invalid_argument("Isbn can't be empty.");
    }
}

Book::Book(const std::string& title,const  std::string& author, int year,const  std::string& isbn, bool isAvailable, const std::string borrowedBy)
    : title(title), author(author), year(year), isbn(isbn), isAvailable(isAvailable), borrowedBy(borrowedBy)
{
    if (title.empty()){
        throw std::invalid_argument("Title can't be empty.");
    }
    if (author.empty()){
        throw std::invalid_argument("Author can't be empty.");
    }
    if (year > 2025 || year < 1450){
        throw std::invalid_argument("Wrong year. Year must be between 1450 and 2025.");
    }
    if (isbn.empty()){
        throw std::invalid_argument("Isbn can't be empty.");
    }
}

std::string Book::getTitle() const {return title;}

std::string Book::getAuthor() const {return author;}

int Book::getYear() const {return year;}

std::string Book::getIsbn() const {return isbn;}

bool Book::getIsAvailable() const {return isAvailable;}

std::string Book::getBorrowedBy() const {return borrowedBy;}



void Book::borrowBook(const std::string& userName) {
    if (!isAvailable){
        throw std::runtime_error("Book is already borrowed.");

    }
    isAvailable = false;
    borrowedBy = userName;
    std::cout << "Now " << userName << " has '" << title << "'" << std::endl;
    

}

void Book::returnBook(){
    isAvailable = true;
    std::cout << "Book '" << title << "' was returned by " << borrowedBy << std::endl;
    borrowedBy = "";
}

void Book::displayInfo() const{
    std::cout << std::endl << "BOOK" << std::endl;
    std::cout << "Title: " << title << std::endl;
    std::cout << "Автор: " << author << std::endl;
    std::cout << "Year: " << year << std::endl;
    std::cout << "ISBN: " << isbn << std::endl;
    if (isAvailable){
        std::cout << "Is available" << std::endl;
    }
    else{
        std::cout << "Is not available " << std::endl;
        std::cout << "Now is borrowed by " << borrowedBy << std::endl;
    }

}