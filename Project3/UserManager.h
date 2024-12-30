#include <fstream>
#include <iostream>
#include "User.h"

class UserManager {
public:
    static bool registerUser(const std::string& username, const std::string& password, const User& user) {
        std::ofstream file(username + ".txt");
        if (file.is_open()) {
            file << user.username << "\n";
            file << user.password << "\n";
            file << user.gender << "\n";
            file << user.age << "\n";
            file << user.height << "\n";
            file << user.weight << "\n";
            file << user.activity_level << "\n";
            file << user.goal << "\n";
            file << user.account_type << "\n";
            file.close();
            return true;
        }
        return false;
    }

    static bool loginUser(const std::string& username, const std::string& password, User& user) {
        std::ifstream file(username + ".txt");
        if (file.is_open()) {
            std::string storedUsername, storedPassword;
            file >> storedUsername >> storedPassword;
            if (storedUsername == username && storedPassword == password) {
                file >> user.gender >> user.age >> user.height >> user.weight >> user.activity_level >> user.goal >> user.account_type;
                file.close();
                return true;
            }
        }
        return false;
    }

    static void logoutUser() {
        std::cout << "Logged out successfully!\n";
    }
};
