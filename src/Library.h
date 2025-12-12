#ifndef LIBRARY_h
#define LIBRARY_h
#include "Book.h"
#include "User.h"


class Library{
    std::vector<Book> books;    //каталог
    std::vector<User> users;    //список пользователей
    std::string dataFile;       //путь к файлу

public:
    Library(const std::string& dataFile = "../data/library_data.txt");
    void addBook(const Book& book);
    void addUser(const User& user);
    void borrowBook(const std::string& userName, const std::string& isbn);
    void returnBook(const std::string& isbn);
    Book* findBookByISBN(const std::string& isbn);
    User* findUserByName(const std::string& name);
    void displayAllBooks();
    void displayAllUsers();
    void saveToFile();           //сохранить состояние библиотеки в файл
    void loadFromFile();         //загрузить состояние из файла

    std::string numberOfUsersForID() const;
};


#endif