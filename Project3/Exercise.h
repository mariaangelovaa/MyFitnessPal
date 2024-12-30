#ifndef EXERCISE_H
#define EXERCISE_H

#include <string>
#include <fstream>  // �� ������� ������
#include <sstream>  // �� ���������� �� stringstream
#include <iostream>

class Exercise {
public:
    std::string name;
    float caloriesBurned; // �������, ����� �� �������� ��� ����������

    Exercise(const std::string& name, float caloriesBurned) : name(name), caloriesBurned(caloriesBurned) {}

    // ��������� �� ������������ � ����
    static void addExercise(const std::string& username, const Exercise& exercise, const std::string& filename) {
        std::ofstream outfile(filename, std::ios::app);
        if (outfile.is_open()) {
            outfile << username << " " << exercise.name << " " << exercise.caloriesBurned << "\n";
        }
    }

    // ��������� �� ������ ���������� �� ���� � ����������� �� ������ �������� �������
    static float getTotalCaloriesBurned(const std::string& username, const std::string& filename) {
        std::ifstream infile(filename);
        std::string line;
        float totalCaloriesBurned = 0;

        while (std::getline(infile, line)) {
            std::stringstream ss(line);
            std::string storedUsername, name;
            float caloriesBurned;

            ss >> storedUsername >> name >> caloriesBurned;

            if (storedUsername == username) {
                totalCaloriesBurned += caloriesBurned;
            }
        }

        return totalCaloriesBurned;
    }
};

#endif // EXERCISE_H
