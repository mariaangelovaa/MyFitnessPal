#include <string>

class Workout {
public:
    std::string name;
    float calories_burned;

    // Constructor
    Workout(std::string n, float c) : name(n), calories_burned(c) {}
};
