#include <iostream>
#include <string>
#include <utility> // За std::pair
#include "User.h"

class CalorieCalculator {
public:
    // Изчисляване на BMR на потребителя (Основен метаболитен разход)
    static float calculateBMR(const User& user) {
        if (user.gender == "male") {
            return 88.362 + (13.397 * user.weight) + (4.799 * user.height) - (5.677 * user.age);
        }
        else {
            return 447.593 + (9.247 * user.weight) + (3.098 * user.height) - (4.330 * user.age);
        }
    }

    // Изчисляване на общия калориен разход на потребителя, като се умножи BMR с коефициент на активност
    static float calculateTotalCalories(const User& user) {
        float bmr = calculateBMR(user);
        float activity_multiplier = 1.2;

        if (user.activity_level == "Light") {
            activity_multiplier = 1.375;
        }
        else if (user.activity_level == "Moderate") {
            activity_multiplier = 1.55;
        }
        else if (user.activity_level == "Active") {
            activity_multiplier = 1.725;
        }
        else if (user.activity_level == "Very Active") {
            activity_multiplier = 1.9;
        }

        return bmr * activity_multiplier;
    }

    // Изчисляване на целевите калории за потребителя в зависимост от целта му (сваляне/поддържане/качване)
    static float calculateTargetCalories(const User& user) {
        float totalCalories = calculateTotalCalories(user);

        if (user.goal == "Lose") {
            return totalCalories - 500; // За сваляне на 0.5 кг седмично
        }
        else if (user.goal == "Gain") {
            return totalCalories + 500; // За качване на 0.5 кг седмично
        }
        else {
            return totalCalories; // За поддържане на тегло
        }
    }

    // Изчисляване на макронутриентите (протеини, мазнини и въглехидрати) за целевите калории
    static std::pair<float, float> calculateMacros(const User& user, float totalCalories) {
        float protein, fat, carbs;

        if (user.goal == "Lose") {
            protein = totalCalories * 0.35 / 4;
            fat = totalCalories * 0.30 / 9;
            carbs = totalCalories * 0.35 / 4;
        }
        else if (user.goal == "Gain") {
            protein = totalCalories * 0.40 / 4;
            fat = totalCalories * 0.25 / 9;
            carbs = totalCalories * 0.35 / 4;
        }
        else {
            protein = totalCalories * 0.25 / 4;
            fat = totalCalories * 0.30 / 9;
            carbs = totalCalories * 0.45 / 4;
        }

        return std::pair<float, float>(protein, fat);
    }
};
