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
    float kgToLose;
    float kgToGain;
    std::string account_type;

    // Default constructor
    User();

    // Constructor with parameters
    User(std::string uname, std::string pass, std::string gen, int ag, float h, float w, std::string activity, std::string g, float kgL, float kgG, std::string account);

    // Function for user registration
    static bool registerUser(const std::string& filename, const User& newUser);

    // Function for user login
    static bool loginUser(const std::string& filename, const std::string& uname, const std::string& pass);

    // Function to get user from file
    static User getUserFromFile(const std::string& filename, const std::string& uname);

    // Method to update user's physical info
    static bool updateUserPhysicalInfo(const std::string& filename, const std::string& uname);
};

#endif // USER_H
