#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

struct User {
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
};

void initUser(User& user, const std::string& uname, const std::string& pass, const std::string& gen, 
    int ag, float h, float w, const std::string& activity, const std::string& g, float kgL, float kgG, const std::string& account);

bool registerUser(const std::string& filename, const User& newUser);

bool loginUser(const std::string& filename, const std::string& uname, const std::string& pass);

User getUserFromFile(const std::string& filename, const std::string& uname);

bool updateUserPhysicalInfo(const std::string& filename, const std::string& uname);
