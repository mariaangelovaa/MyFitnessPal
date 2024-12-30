#ifndef MEAL_H
#define MEAL_H

#include <string>
#include <fstream>  // �� ������� ������
#include <sstream>  // �� stringstream
#include <iostream>

class Meal {
public:
    std::string name;
    float calories; // ������� �� ���� �������

    Meal(const std::string& name, float calories) : name(name), calories(calories) {}

    // ��������� �� ��������� � ����
    static void addMeal(const std::string& username, const Meal& meal, const std::string& filename) {
        std::ofstream outfile(filename, std::ios::app);
        if (outfile.is_open()) {
            outfile << username << " " << meal.name << " " << meal.calories << "\n";
        }
    }

    // ��������� �� ������ �������� �� ���� � ����������� �� ����� �������� �����
    static float getTotalCalories(const std::string& username, const std::string& filename) {
        std::ifstream infile(filename);
        std::string line;
        float totalCalories = 0;

        while (std::getline(infile, line)) {
            std::stringstream ss(line);
            std::string storedUsername, name;
            float calories;

            ss >> storedUsername >> name >> calories;

            if (storedUsername == username) {
                totalCalories += calories;
            }
        }

        return totalCalories;
    }
};

#endif // MEAL_H
