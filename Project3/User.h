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

    // Default constructor
    User()
        : username(""), password(""), gender(""), age(0), height(0.0f), weight(0.0f), activity_level(""), goal(""), account_type("") {}

    // Constructor with parameters
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

    // Функция за извличане на потребителския обект от файла
    static User getUserFromFile(const std::string& filename, const std::string& uname) {
        std::ifstream infile(filename);
        std::string line;
        while (std::getline(infile, line)) {
            std::stringstream ss(line);
            std::string storedUsername, storedPassword, gender, activityLevel, goal, accountType;
            int age;
            float height, weight;

            ss >> storedUsername >> storedPassword >> gender >> age >> height >> weight >> activityLevel >> goal >> accountType;

            // Ако намерим съвпадение на потребителското име, връщаме обект User
            if (storedUsername == uname) {
                return User(storedUsername, storedPassword, gender, age, height, weight, activityLevel, goal, accountType);
            }
        }
        // Ако не намерим потребителя, връщаме празен обект (или хвърляме изключение, ако е необходимо)
        throw std::runtime_error("User not found");
    }
    // Method to update user's physical info
    static bool updateUserPhysicalInfo(const std::string& filename, const std::string& uname) {
        std::ifstream infile(filename);
        std::vector<std::string> lines;
        std::string line;
        bool userFound = false;

        // Read the file into a vector of lines
        while (std::getline(infile, line)) {
            lines.push_back(line);
        }

        // Search for the user and update the physical info
        for (auto& line : lines) {
            std::stringstream ss(line);
            std::string storedUsername, storedPassword, gender, activityLevel, goal, accountType;
            int age;
            float height, weight;

            ss >> storedUsername >> storedPassword >> gender >> age >> height >> weight >> activityLevel >> goal >> accountType;

            if (storedUsername == uname) {
                userFound = true;
                // Ask user for new information
                std::cout << "Enter new gender (current: " << gender << "): ";
                std::cin >> gender;
                std::cout << "Enter new age (current: " << age << "): ";
                std::cin >> age;
                std::cout << "Enter new height (current: " << height << "): ";
                std::cin >> height;
                std::cout << "Enter new weight (current: " << weight << "): ";
                std::cin >> weight;
                std::cout << "Enter new activity level (current: " << activityLevel << "): ";
                std::cin >> activityLevel;
                std::cout << "Enter new goal (current: " << goal << "): ";
                std::cin >> goal;

                // Update the current line with the new values
                std::stringstream updatedLine;
                updatedLine << storedUsername << " "
                    << storedPassword << " "
                    << gender << " "
                    << age << " "
                    << height << " "
                    << weight << " "
                    << activityLevel << " "
                    << goal << " "
                    << accountType;

                line = updatedLine.str(); // Replace the line with updated details
                break;
            }
        }

        infile.close();

        if (userFound) {
            // Write the updated lines back to the file
            std::ofstream outfile(filename);
            for (const auto& line : lines) {
                outfile << line << "\n";
            }
            outfile.close();
            std::cout << "User information updated successfully.\n";
            return true;
        }
        else {
            std::cout << "User not found.\n";
            return false;
        }
    }
};

#endif // USER_H
