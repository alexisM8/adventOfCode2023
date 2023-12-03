#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>

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

static constexpr char file_path[] = "puzzle_input/DayThree/DayThreeSample.txt";

std::vector<std::string> splitString(const std::string& str, char delimiter);
std::ostream& operator <<(std::ostream& o, const std::vector<std::string>& vec);
int checkGearRatios(const std::vector<std::string>& vec, int row, int col);
int checkLeft(const std::vector<std::string>& vec, int row, int col);
int checkRight(const std::vector<std::string>& vec, int row, int col);
int checkTop(const std::vector<std::string>& vec, int row, int col);
int checkBottom(const std::vector<std::string>& vec, int row, int col);

int main(){
    std::ifstream input(file_path);
    int summation = 0;
    
    if(input.fail()){
        std::cerr << "Error: could not open file" << file_path << "\n";
        exit(1);
    }

    std::stringstream ss;
    ss << input.rdbuf();
    std::string file_contents{ ss.str() };

    auto tokens = splitString(file_contents, '\n');

    for(int row = 0; row < tokens.size(); row++){
        int length = 0;
        for(int col = 0; col < tokens[row].size(); col++){
            if (tokens[row][col] == '*') {
                int gearRatio = checkGearRatios(tokens, row, col);
                summation += gearRatio;
            }
        }
    }
    std::cout << "summation: " << summation << "\n";
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

std::ostream& operator <<(std::ostream& o, const std::vector<std::string>& vec){
    for(auto &token : vec){
        o << token << "\n";
    }
    return o;
}

int checkRight(const std::vector<std::string>& vec, int row, int col){
    if(vec[row][col] == '*'){
        int length = 0;
        int tempcol = col+1;
        while(tempcol < vec[row].size() && isdigit(vec[row][tempcol])){
            length++;
            tempcol++;
        }
        if(length > 0){
            return std::stoi(vec[row].substr(col+1, length));
        }else{
            return -1;
        }
    }else{
        return -1;
    }
}

int checkLeft(const std::vector<std::string>& vec, int row, int col){
    if (vec[row][col] == '*') {
        int length = 0;
        int tempcol = col - 1;
        while (tempcol >= 0 && isdigit(vec[row][tempcol])) {
            length++;
            tempcol--;
        }
        if (length > 0) {
            return std::stoi(vec[row].substr(col - length, length));
        } else {
            return -1;
        }
    } else {
        return -1;
    }
}

int checkTop(const std::vector<std::string>& vec, int row, int col) {
    if (vec[row][col] == '*') {
        int leftNum = checkLeft(vec, row-1, col);
        int rightNum = checkRight(vec, row-1, col);
        if (leftNum != -1 && rightNum != -1) {
            return leftNum * rightNum;
        }
    } else {
        return -1;
    }
}

int checkBottom(const std::vector<std::string>& vec, int row, int col) {
    if (vec[row][col] == '*') {
        int leftNum = checkLeft(vec, row+1, col);
        int rightNum = checkRight(vec, row+1, col);
        if (leftNum != -1 && rightNum != -1) {
            return leftNum * rightNum;
        }
    } else {
        return -1;
    }
}

int checkGearRatios(const std::vector<std::string>& vec, int row, int col){
    int leftNum = checkLeft(vec, row, col);
    int rightNum = checkRight(vec, row, col);
    int topNum = checkTop(vec, row, col);
    int bottomNum = checkBottom(vec, row, col);

    if (leftNum != -1 && rightNum != -1) {
        return leftNum * rightNum;
    } else if (topNum != -1 && bottomNum != -1) {
        return topNum + bottomNum;
    } else {
        return 0; // No valid gear ratio found
    }
}