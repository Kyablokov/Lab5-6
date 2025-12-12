#include "Book.h"
#include "User.h"
#include "Library.h"
#include <iostream>
#include <stdexcept>
#include <limits>

void menu(){
    std::cout << std::endl << "===LIBRARY===" << std::endl;
    std::cout << "1. View all books" << std::endl;
    std::cout << "2. View all users" << std::endl;
    std::cout << "3. Add new book" << std::endl;
    std::cout << "4. Add new user" << std::endl;
    std::cout << "5. Borrow book to user" << std::endl;
    std::cout << "6. Return book" << std::endl;
    std::cout << "7. Find book by ISBN" << std::endl;
    std::cout << "8. View user's profile" << std::endl;
    std::cout << "9. Save data to file" << std::endl;
    std::cout << "10. Exit" << std::endl;
    std::cout << "Your choice: ";
}

std::string input(const std::string& line, bool can_be_empty = false){
    std::string input;
    std::cin.clear();
    while (true){
        std::cout << line;
        std::cin.clear();
        getline(std::cin,input);
        if (!can_be_empty && input.empty()){
            std::cout << "Can't be empty. Try again." << std::endl;
            continue;
        }
        break;
    }
    return input;
}

int intinput(const std::string& line, bool year = false){
    int input;
    std::cin.clear();

    while (true){
        std::cout << line;
        if (!(std::cin >> input)){
            std::cin.clear();
            if(year){
                std::cout << "Must be integer. Try again." << std::endl;
                continue;
            }
            else{
                std::cout << "Must be integer or empty string. Max books now - 3." << std::endl;
                return 3;
                
            }
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (year && (input > 2025 || input < 1450)){                //можно ctime
            std::cout << "Year must be between 1450 and 2025. Try again." << std::endl;
            continue;
        }
        std::cin.clear();
        break;

    }
    std::cin.clear();
    return input;
}


int main(){
    Library library = Library();

    while (true){
        menu();

        int choice;
        if (!(std::cin >> choice)){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Input error. Please, input number between 1 and 10." << std::endl;
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        try{
            switch (choice){
                case 1:
                    std::cout << std::endl;
                    library.displayAllBooks();
                    break;
                case 2:
                    std::cout << std::endl;
                    library.displayAllUsers();
                    break;
                case 3:
                {
                    std::cout << std::endl;
                    std::cout << "ADD NEW BOOK" << std::endl;

                    std::string title = input("Enter title: ");
                    std::string author = input("Enter author: ");
                    int year = intinput("Enter year: ", true);
                    std::string isbn = input("Enter ISBN: ");

                    Book new_book(title,author,year,isbn);
                    library.addBook(new_book);
                    std::cout << "Success" << std::endl;
                    break;
                }
                case 4:
                {
                    std::cout << std::endl;
                    std::cout << "ADD NEW USER" << std::endl;

                    std::string name = input("Enter name: ");
                    while (library.findUserByName(name)){
                        name = input("User with that name already exists. Try another name: ");
                    }
                    std::string userId = "USR_" +  library.numberOfUsersForID();
                    int maxBooksAllowed = intinput("Enter count of max books: ");
                    
                    User new_user(name, userId,maxBooksAllowed);
                    library.addUser(new_user);
                    std::cout << "Success" << std::endl;
                    break;
                }
                case 5:
                {
                    std::cout << std::endl;
                    std::cout << "BORROWING BOOK" << std::endl;

                    std::string name = input("Enter name: ");
                    std::string isbn = input("Enter ISBN: ");

                    library.borrowBook(name,isbn);
                    std::cout << "Success" << std::endl;
                    break;
                }

                case 6:
                {
                    std::cout << std::endl;
                    std::cout << "RETURNING BOOK" << std::endl;

                    std::string isbn = input("Enter ISBN: ");

                    library.returnBook(isbn);
                    std::cout << "Success" << std::endl;
                    break;
                }

                case 7:
                {
                    std::cout << std::endl;
                    std::cout << "FINDING BOOK BY ISBN" <<std::endl;

                    std::string isbn = input("Enter ISBN: ");
                    Book* this_book = library.findBookByISBN(isbn);
                    if (this_book == nullptr){
                        throw std::runtime_error("Book not found.");
                    }
                    else{
                        this_book->displayInfo();
                    }
                    break;
                }

                case 8:
                {
                    std::cout << std::endl;
                    std::cout << "USER'S PROFILE BY NAME" <<std::endl;

                    std::string name = input("Enter name: ");
                    User* this_user = library.findUserByName(name);
                    if (this_user == nullptr){
                        throw std::runtime_error("User not found.");
                    }
                    else{
                        this_user->displayProfile();
                    }
                    break;
                }

                case 9:
                    std::cout << std::endl;
                    library.saveToFile();
                    std::cout << "Success" << std::endl;
                    break;
                
                case 10:
                    std::cout << std::endl;
                    library.saveToFile();
                    std::cout << "Files were saved. Goodbye!" << std::endl;
                    return 0;
                default:
                    std::cout << std::endl;
                    std::cout << "Wrong input. Please, input number between 1 and 10." << std::endl;
                    break;
            }
        } catch (const std::exception& error){
            std::cerr << "Error" << error.what() << std::endl;
        }
    }
    return 0;
}