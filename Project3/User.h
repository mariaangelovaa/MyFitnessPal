#ifndef USER_H
#define USER_H

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

class User {
public:
    std::string username;
    std::string password;
    std::string gender;
    int age;
    float height;
    float weight;
    std::string activity_level;
    std::string goal;
    std::string account_type;

    // Конструктор за потребителски данни
    User(std::string uname, std::string pass, std::string gen, int ag, float h, float w, std::string activity, std::string g, std::string account)
        : username(uname), password(pass), gender(gen), age(ag), height(h), weight(w), activity_level(activity), goal(g), account_type(account) {}

    // Функция за регистрация на нов потребител
    static bool registerUser(const std::string& filename, const User& newUser) {
        std::ifstream infile(filename);
        std::string line;
        while (std::getline(infile, line)) {
            std::stringstream ss(line);
            std::string storedUsername;
            ss >> storedUsername;
            if (storedUsername == newUser.username) {
                std::cout << "Username already exists! Please choose a different one.\n";
                return false; // Потребителското име вече съществува
            }
        }

        std::ofstream outfile(filename, std::ios::app);
        if (outfile.is_open()) {
            outfile << newUser.username << " "
                << newUser.password << " "
                << newUser.gender << " "
                << newUser.age << " "
                << newUser.height << " "
                << newUser.weight << " "
                << newUser.activity_level << " "
                << newUser.goal << " "
                << newUser.account_type << "\n";
            std::cout << "Registration successful!\n";
            return true;
        }
        return false;
    }

    // Функция за логване на потребител
    static bool loginUser(const std::string& filename, const std::string& uname, const std::string& pass) {
        std::ifstream infile(filename);
        std::string line;
        while (std::getline(infile, line)) {
            std::stringstream ss(line);
            std::string storedUsername, storedPassword;
            ss >> storedUsername >> storedPassword;
            if (storedUsername == uname && storedPassword == pass) {
                return true; // Успешно логване
            }
        }
        return false; // Невалидно потребителско име или парола
    }
};

#endif // USER_H
