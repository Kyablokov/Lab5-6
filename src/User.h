#ifndef USER_h
#define USER_h
#include <string>
#include <vector>

class User{
    std::string name;                          //фамилия
    std::string userId;                        //уникальный ID (вида "USR_001")
    std::vector<std::string> borrowedBooks;    //список ISBN выданных книг
    int maxBooksAllowed;                       // максимум книг, которые можно взять (по умолчанию 3)
public:
    User(const std::string& name, const std::string& userId, int maxBooksAllowed);
    User(const std::string& name, const std::string& userId, const std::vector<std::string>& borrowedBooks,int maxBooksAllowed);
    
    std::string getName() const;
    std::string getUserId()const;
    std::vector<std::string> getborrowedBooks() const;
    int getmaxBooksAllowed() const;

    bool canBorrowMore();
    void addBook(const std::string& isbn);     //добавить книгу в список взятых
    void removeBook(const std::string& isbn);  //убрать книгу из списка
    void displayProfile() const;


};


#endif