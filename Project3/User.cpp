/**
*
* Solution to course project #9
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2024 / 2025
*
* @author Maria Angelova
* @idnumber 4MI0600425
* @compiler VS
*
* file for users
*
*/

#include "User.h"

void initUser(User& user, const std::string& uname, const std::string& pass, const std::string& gen, int ag, float h, float w, const std::string& activity, const std::string& g, float kgL, float kgG, const std::string& account) {
    user.username = uname;
    user.password = pass;
    user.gender = gen;
    user.age = ag;
    user.height = h;
    user.weight = w;
    user.activity_level = activity;
    user.goal = g;
    user.kgToLose = kgL;
    user.kgToGain = kgG;
    user.account_type = account;
}

bool registerUser(const std::string& filename, const User& newUser) {
    std::ifstream infile(filename);
    std::string line;
    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        std::string storedUsername;
        ss >> storedUsername;
        if (storedUsername == newUser.username) {
            std::cout << "Username already exists! Please choose a different one.\n";
            return false; // Username already exists
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
            << newUser.kgToLose << " "
            << newUser.kgToGain << " "
            << newUser.account_type << "\n";
        std::cout << "Registration successful!\n";
        return true;
    }
    return false;
}

bool loginUser(const std::string& filename, const std::string& uname, const std::string& pass) {
    std::ifstream infile(filename);
    std::string line;
    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        std::string storedUsername, storedPassword;
        ss >> storedUsername >> storedPassword;
        if (storedUsername == uname && storedPassword == pass) {
            return true; // Successful login
        }
    }
    return false; // Invalid username or password
}

User getUserFromFile(const std::string& filename, const std::string& uname) {
    std::ifstream infile(filename);
    std::string line;
    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        std::string storedUsername, storedPassword, gender, activityLevel, goal, accountType;
        int age;
        float height, weight, kgToLose, kgToGain;

        ss >> storedUsername >> storedPassword >> gender >> age >> height >> weight >> activityLevel >> goal >> kgToLose >> kgToGain >> accountType;

        // If we find a match for the username, return a User object
        if (storedUsername == uname) {
            User user;
            initUser(user, storedUsername, storedPassword, gender, age, height, weight, activityLevel, goal, kgToLose, kgToGain, accountType);
            return user;
        }
    }
    // If the user is not found, throw an exception
    throw std::runtime_error("User not found");
}

bool updateUserPhysicalInfo(const std::string& filename, const std::string& uname) {
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
        float height, weight, kgToLose, kgToGain;

        ss >> storedUsername >> storedPassword >> gender >> age >> height >> weight >> activityLevel >> goal >> kgToLose >> kgToGain >> accountType;

        if (storedUsername == uname) {
            userFound = true;
            // Ask the user for new information
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

            if (goal == "Lose") {
                std::cout << "How much weight per week do you intend to lose? (in kg): ";
                std::cin >> kgToLose;
                kgToGain = 0; // Ensure kgToGain is 0 if the goal is to lose weight
            }
            else if (goal == "Gain") {
                std::cout << "How much weight per week do you intend to gain? (in kg): ";
                std::cin >> kgToGain;
                kgToLose = 0; // Ensure kgToLose is 0 if the goal is to gain weight
            }
            else {
                // If goal is Maintain, both kgToLose and kgToGain should be 0
                kgToLose = 0;
                kgToGain = 0;
            }

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
                << kgToLose << " "
                << kgToGain << " "
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
