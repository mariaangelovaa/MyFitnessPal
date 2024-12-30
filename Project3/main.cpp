#include <iostream>
#include <string>
#include "User.h"
#include "Exercise.h"
#include "Meal.h"

//void showMainMenu() {
//    std::cout << "Welcome to the Calorie Tracker!\n";
//    std::cout << "1. Register\n";
//    std::cout << "2. Login\n";
//    std::cout << "3. Exit\n";
//    std::cout << "Please select an option: ";
//}

void handleRegister(const std::string& filename) {
    std::string username, password, gender, activity, goal, accountType;
    int age;
    float height, weight;

    std::cout << "Enter username: ";
    std::cin >> username;

    std::cout << "Enter password: ";
    std::cin >> password;

    std::cout << "Enter gender (M/F): ";
    std::cin >> gender;

    std::cout << "Enter age: ";
    std::cin >> age;

    std::cout << "Enter height (cm): ";
    std::cin >> height;

    std::cout << "Enter weight (kg): ";
    std::cin >> weight;

    std::cout << "Enter activity level (Sedentary/Light/Moderate/Active/Very Active): ";
    std::cin >> activity;

    std::cout << "Enter goal (Lose/Maintain/Gain): ";
    std::cin >> goal;

    std::cout << "Select account type (Standard/Premium): ";
    std::cin >> accountType;

    User newUser(username, password, gender, age, height, weight, activity, goal, accountType);
    if (User::registerUser(filename, newUser)) {
        // Успешна регистрация
    }
}

void handleLogin(const std::string& filename) {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;

    std::cout << "Enter password: ";
    std::cin >> password;

    if (User::loginUser(filename, username, password)) {
        std::cout << "Login successful!\n";
        // Може да продължиш с функционалността за добавяне на хранения, тренировки и т.н.
    }
    else {
        std::cout << "Invalid username or password.\n";
    }
}

void showMainMenu() {
    std::cout << "\nWelcome to the Calorie Tracker!\n";
    std::cout << "1. View Daily Report\n";
    std::cout << "2. Add Meal\n";
    std::cout << "3. Add Exercise\n";
    std::cout << "4. View Progress\n";
    std::cout << "5. Logout\n";
    std::cout << "Please select an option: ";
}

void viewDailyReport(const std::string& username) {
    // Прочитане на дневен отчет: калории от хранения и тренировки
    float totalCalories = Meal::getTotalCalories(username, "meals.txt");
    float totalCaloriesBurned = Exercise::getTotalCaloriesBurned(username, "exercises.txt");

    std::cout << "\nDaily Report for " << username << ":\n";
    std::cout << "Total Calories Consumed: " << totalCalories << " kcal\n";
    std::cout << "Total Calories Burned: " << totalCaloriesBurned << " kcal\n";
    std::cout << "Net Calories: " << (totalCalories - totalCaloriesBurned) << " kcal\n";
}

void addMeal(const std::string& username) {
    std::string name;
    float calories;

    std::cout << "Enter meal name: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    std::cout << "Enter calories: ";
    std::cin >> calories;

    Meal meal(name, calories);
    Meal::addMeal(username, meal, "meals.txt");
    std::cout << "Meal added successfully!\n";
}

void addExercise(const std::string& username) {
    std::string name;
    float caloriesBurned;

    std::cout << "Enter exercise name: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    std::cout << "Enter calories burned: ";
    std::cin >> caloriesBurned;

    Exercise exercise(name, caloriesBurned);
    Exercise::addExercise(username, exercise, "exercises.txt");
    std::cout << "Exercise added successfully!\n";
}

void viewProgress(const std::string& username) {
    // Показване на прогрес към целта
    // За целта можем да използваме нещо като дневен лимит на калории и да го сравним с текущите стойности.
    std::cout << "Progress feature coming soon...\n";
}

int main() {
    std::string username = "user123";  // Пример за потребител (след логване)

    int choice;
    while (true) {
        showMainMenu();
        std::cin >> choice;

        switch (choice) {
        case 1:
            viewDailyReport(username);
            break;
        case 2:
            addMeal(username);
            break;
        case 3:
            addExercise(username);
            break;
        case 4:
            viewProgress(username);
            break;
        case 5:
            std::cout << "Logged out successfully.\n";
            return 0;
        default:
            std::cout << "Invalid option. Please try again.\n";
        }
    }

    return 0;
}
