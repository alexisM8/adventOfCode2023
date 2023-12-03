#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>

/*
The engine schematic (your puzzle input) consists of a visual 
    representation of the engine. There are lots of numbers and 
    symbols you don't really understand, but apparently any number 
    adjacent to a symbol, even diagonally, is a "part number" and 
    should be included in your sum. (Periods (.) do not count as a symbol.)

Here is an example engine schematic:

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

In this schematic, two numbers are not part numbers because they are not
    adjacent to a symbol: 114 (top right) and 58 (middle right). 
    Every other number is adjacent to a symbol and so is a part number; 
    their sum is 4361
*/

static constexpr char file_path[] = "puzzle_input/DayThree/DayThree.txt";

std::vector<std::string> splitString(const std::string& str, char delimiter);
std::ostream& operator <<(std::ostream& o, const std::vector<std::string>& vec);
bool checkNeighbors(const std::vector<std::string>& vec, int row, int col, int length, const std::string special_chars);

int main(){
    std::ifstream input(file_path);
    std::string special_chars{"*-$@+=&/#%"};
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
            if(isdigit(tokens[row][col])){
                length++;
            }else{
                if(length > 0 && checkNeighbors(tokens, row, col-length, length, special_chars)){
                    summation += std::stoi(tokens[row].substr(col-length, length));
                }
                length = 0;
            }
        }
        //!!!!! this cost me about 45 mins....
        // Check neighbors before moving to the next row if length is still greater than 0
        if (length > 0) {
            if (checkNeighbors(tokens, row, tokens[row].size() - length, length, special_chars)) {
                summation += std::stoi(tokens[row].substr(tokens[row].size() - length, length));
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

bool checkNeighbors(const std::vector<std::string>& vec, int row, int col, int length, const std::string special_chars){
    /*
                 col
                  ↓                   
              . . . . . .
        row → . . 4 5 6 .
              . * . . . .
    */
    bool result = false;
    int startRow = std::max(row - 1, 0);  
    int endRow = std::min(row + 1, static_cast<int>(vec.size() - 1));
    int startCol = std::max(col - 1, 0);
    int endCol = std::min(col + length, static_cast<int>(vec[row].size() - 1));

    for(int i = startRow; i <= endRow; ++i){
        for(int j = startCol; j <= endCol; ++j){
                if(special_chars.find(vec[i][j]) != std::string::npos){
                    result = true;
                    break;
                }

        }
        if(result) break;
    }
    return result;
}