#ifndef Book_h
#define Book_h
#include <string>

class Book {
    std::string title;              //название книги
    std::string author;             //автор
    std::string isbn;               //уникальный ISBN
    std::string borrowedBy;         //фамилия пользователя, взявшего книгу

    int year;                       //год издания

    bool isAvailable;               //доступна ли книга для выдачи

public:
    Book(const std::string& title,const  std::string& author, int year,const  std::string& isbn);
    Book(const std::string& title,const  std::string& author, int year,const  std::string& isbn, bool isAvailable, const std::string borrowedBy);

    std::string getTitle() const;
    std::string getAuthor() const;
    int getYear() const;
    std::string getIsbn() const;
    bool getIsAvailable() const;
    std::string getBorrowedBy() const;

    void borrowBook(const std::string& userName);
    void returnBook();
    void displayInfo() const;

};

#endif