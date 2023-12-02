#include <iostream>
#include <fstream>
#include <sstream>
#include <ostream>

/*
Again consider the example games from earlier:

Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green

In game 1, the game could have been played with as few as 4 red, 2 green, and 6 blue cubes. 
If any color had even one fewer cube, the game would have been impossible.

Game 2 could have been played with a minimum of 1 red, 3 green, and 4 blue cubes.

Game 3 must have been played with at least 20 red, 13 green, and 6 blue cubes.

Game 4 required at least 14 red, 3 green, and 15 blue cubes.

Game 5 needed no fewer than 6 red, 3 green, and 2 blue cubes in the bag.

The power of a set of cubes is equal to the numbers of red, green, and blue cubes multiplied together.
The power of the minimum set of cubes in game 1 is 48. In games 2-5 
it was 12, 1560, 630, and 36, respectively. 
Adding up these five powers produces the sum 2286.

For each game, find the minimum set of cubes that must have been present. 
What is the sum of the power of these sets?
*/

std::vector<std::string> splitString(const std::string& str, char delimiter);
std::ostream& operator <<(std::ostream& o, const std::vector<std::string>&);
bool checkValid(int count, const std::string& color);

int main(){
    std::ifstream infile("puzzle_input/DayTwo/DayTwo.txt");
    std::string line{};
    int id = 0;
    int summation = 0;
    int max_red = -1;
    int max_green = -1;
    int max_blue = -1;

    if(infile.fail()){
        std::cerr << "Could not open file: puzzle_input/DayTwo/DayTwo.txt\n";
        exit(1);
    }

    while(std::getline(infile, line)){
        size_t colonPos = line.find(":");

        if (colonPos != std::string::npos) {
            size_t length = colonPos - 5;
            id = std::stoi(line.substr(5, length));
        }

        auto tokens = splitString(line.substr(colonPos+2), ';');
        bool valid = true;
        for(auto& token : tokens){
            auto subtokens = splitString(token, ',');
            for(auto& subtoken : subtokens){
                std::istringstream ss(subtoken);
                int count;
                std::string color;
                ss >> count >> color;
                if(color == "red"){
                    max_red = (count > max_red) ? count : max_red;
                }
                if(color == "green"){
                    max_green = (count > max_green) ? count : max_green;
                }
                if(color == "blue"){
                    max_blue = (count > max_blue) ? count : max_blue;
                }
            }
        }
        summation += max_red * max_blue * max_green;
        max_red = max_green = max_blue = -1;
    }
    std::cout << "summation: "  << summation << "\n";
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