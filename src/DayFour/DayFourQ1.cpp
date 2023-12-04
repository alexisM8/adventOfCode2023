#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <set>


/*
you have to figure out which of the numbers you have appear in 
    the list of winning numbers. The first match makes the card 
    worth one point and each match after the first doubles the 
    point value of that card.

For example:

41 48 83 86 17 | 83 86  6 31 17  9 48 53
13 32 20 16 61 | 61 30 68 82 17 32 24 19
 1 21 53 59 44 | 69 82 63 72 16 21 14  1
41 92 73 84 69 | 59 84 76 51 58  5 54 83
87 83 26 28 32 | 88 30 70 12 93 22 82 36
31 18 13 56 72 | 74 77 10 23 35 67 36 11

In the above example, card 1 has five winning numbers 
    (41, 48, 83, 86, and 17) and eight numbers you have 
    (83, 86, 6, 31, 17, 9, 48, and 53). Of the numbers you have, 
    four of them (48, 83, 17, and 86) are winning numbers! 
    That means card 1 is worth 8 points (1 for the first match, 
    then doubled three times for each of the three matches after the first).

Card 2 has two winning numbers (32 and 61), so it is worth 2 points.
Card 3 has two winning numbers (1 and 21), so it is worth 2 points.
Card 4 has one winning number (84), so it is worth 1 point.
Card 5 has no winning numbers, so it is worth no points.
Card 6 has no winning numbers, so it is worth no points.
So, in this example, the Elf's pile of scratchcards is worth 13 points.

Take a seat in the large pile of colorful cards. 
    How many points are they worth in total?
*/

static constexpr char file_path[] = "puzzle_input/DayFour/DayFourStripped.txt";

std::vector<std::string> splitString(const std::string& str, char delimiter);
std::set<int> toset(const std::string& winningnumbers);
std::optional<int> stringToInt(const std::string& str);
std::ostream& operator <<(std::ostream& o, const std::set<int>& set);

int main() {
    std::ifstream input(file_path);
    int summation = 0;
    
    if(input.fail()){
        std::cerr << "Error: could not open file " << file_path << "\n";
        exit(1);
    }

    std::stringstream ss;
    ss << input.rdbuf();
    std::string file_contents{ ss.str() };

    auto tokens = splitString(file_contents, '\n');
    for(const auto& token : tokens){
        int count = 0;
        auto values = splitString(token, '|');
        auto winningnumbers = toset(values[0]);
        auto nums = splitString(values[1], ' ');
        for(const auto& num : nums){
            auto converted = stringToInt(num);
            if(converted.has_value() && winningnumbers.contains(converted.value())){
                count++;
            }
        }
        std::cout << winningnumbers << " count " << count << "\n";
        if(count > 0){
            summation += std::pow(2, count-1);
        }
    }
    std::cout << "summation: " << summation << "\n";

}

std::vector<std::string> splitString(const std::string& str, char delimiter){
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

std::set<int> toset(const std::string& winningnumbers){
    auto numbers = splitString(winningnumbers, ' ');
    std::set<int> ret;
    for(const auto& num : numbers){
        auto number = stringToInt(num);
        if(number.has_value()){
            ret.insert(number.value());
        }

    }
    return ret;
}

std::optional<int> stringToInt(const std::string& str) {
    try {
        size_t pos = 0;
        int value = std::stoi(str, &pos);
        if (pos < str.size()) {
            // If there are non-numeric characters after the valid integer, it's invalid
            std::cerr << "Non-numeric characters in string: " << str << "\n";
            return std::nullopt; // Indicates failure
        }
        return value;
    } catch(const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << "\n";
        return std::nullopt; // Indicates failure
    } catch(const std::out_of_range& e) {
        std::cerr << "Out of range: " << e.what() << "\n";
        return std::nullopt; // Indicates failure
    }
}

std::ostream& operator <<(std::ostream& o, const std::set<int>& set){
    o << "[";
    for(const auto& value: set){
        o << value << ", ";
    }
    o << "]";
    return o;
}