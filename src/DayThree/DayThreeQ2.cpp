#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <stack>

/*
The missing part wasn't the only issue - one of the gears in the
    engine is wrong. A gear is any * symbol that is adjacent to 
    exactly two part numbers. Its gear ratio is the result of 
    multiplying those two numbers together.

This time, you need to find the gear ratio of every gear and 
    add them all up so that the engineer can figure out which 
    gear needs to be replaced.

Consider the same engine schematic again:

467..114..
...*......
..35..633.
......#...
617*......
.....+.58.
..592.....
......755.
...$.*....
.664.598..

In this schematic, there are two gears. The first is in the top left; 
    it has part numbers 467 and 35, so its gear ratio is 16345. 
    The second gear is in the lower right; its gear ratio is 451490. 
    (The * adjacent to 617 is not a gear because it is only adjacent 
    to one part number.) Adding up all of the gear ratios produces 467835.

What is the sum of all of the gear ratios in your engine schematic?
*/

static constexpr char file_path[] = "puzzle_input/DayThree/DayThree.txt";

std::vector<std::string> splitString(const std::string& str, char delimiter);
void checkForAdjacentGear(const std::vector<std::string>& vec, int row, int col, long long& gear_summation);

int main() {
    std::ifstream input(file_path);
    long long gear_summation = 0;
    
    if(input.fail()){
        std::cerr << "Error: could not open file " << file_path << "\n";
        exit(1);
    }

    std::stringstream ss;
    ss << input.rdbuf();
    std::string file_contents{ ss.str() };

    auto tokens = splitString(file_contents, '\n');

    for(int row = 0; row < tokens.size(); row++){
        for(int col = 0; col < tokens[row].size(); col++){
            if(tokens[row][col] == '*'){
                checkForAdjacentGear(tokens, row, col, gear_summation);
            }
        }
    }

    std::cout << "Summation of gear ratios: " << gear_summation << "\n";
    return 0;
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

void checkForAdjacentGear(const std::vector<std::string>& vec, int row, int col, long long& gear_summation){
    /*
                   col
                    ↓                   
              4 6 7 . . .
        row → . . . * . .
              . . 3 5 . .
    */
    std::vector<int> adjacent_numbers; // Store adjacent numbers found around '*'
    std::stack<char> stack;
    std::vector<std::vector<bool>> visited(vec.size(), std::vector<bool>(vec[0].size(), false)); // Track visited positions

    for(int i = row - 1; i <= row + 1; ++i){
        for(int j = col - 1; j <= col + 1; ++j){
            if(i >= 0 && i < vec.size() && j >= 0 && j < vec[row].size()){
                if(isdigit(vec[i][j]) && !visited[i][j]){
                    std::string number;
                    int k = j;
                    while(k <= vec[i].size() && isdigit(vec[i][k])){
                        k++;
                    }
                    k--;
                    while(k >= 0 && isdigit(vec[i][k])){
                        stack.push(vec[i][k]);
                        visited[i][k] = true; // Mark position as visited
                        k--;
                    }
                    while(!stack.empty()){
                        number.push_back(stack.top());
                        stack.pop();
                    }
                    std::cout << "number: "  << number << "\n";
                    int num = std::stoi(number);
                    adjacent_numbers.push_back(num);
                    number.clear();
                }
            }
        }
    }

    if(adjacent_numbers.size() == 2){
        std::cout << "num1: " << adjacent_numbers[0] << " num2: " << adjacent_numbers[1] << "\n";
        gear_summation += (long long)adjacent_numbers[0] * adjacent_numbers[1];
    }
}