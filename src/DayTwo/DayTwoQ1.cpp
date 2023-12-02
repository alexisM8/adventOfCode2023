#include <iostream>
#include <fstream>
#include <sstream>
#include <ostream>

/*
Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green
In game 1, three sets of cubes are revealed from the bag 
(and then put back again). The first set is 3 blue cubes 
and 4 red cubes; the second set is 1 red cube, 2 green cubes, 
and 6 blue cubes; the third set is only 2 green cubes.

The Elf would first like to know which games would have been possible 
if the bag contained only 12 red cubes, 13 green cubes, and 14 blue cubes?

In the example above, games 1, 2, and 5 would have been possible if the 
bag had been loaded with that configuration. However, 
game 3 would have been impossible because at one point the Elf 
showed you 20 red cubes at once; similarly, game 4 would also have 
been impossible because the Elf showed you 15 blue cubes at once. 
If you add up the IDs of the games that would have been possible, 
you get 8.

Determine which games would have been possible if the bag had been 
loaded with only 12 red cubes, 13 green cubes, and 14 blue cubes. 
What is the sum of the IDs of those games?
*/

constexpr int RED = 12;
constexpr int GREEN = 13;
constexpr int BLUE = 14;

std::vector<std::string> splitString(const std::string& str, char delimiter);
std::ostream& operator <<(std::ostream& o, const std::vector<std::string>&);
bool checkValid(int count, const std::string& color);

int main(){
    std::ifstream infile("puzzle_input/DayTwo/DayTwo.txt");
    std::string line{};
    int id = 0;
    int summation = 0;

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

                valid = checkValid(count, color);
                std::cout << "Count: " << count << ", Color: " << color << ", Valid: " << valid << std::endl;
                if(!valid) break;
            }
            if(!valid) break;
        }
        if(valid){
            summation += id;
        }
        
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

bool checkValid(int count, const std::string& color){
    if(color == "red"){
        return count <= RED;
    }else if(color == "green"){
        return count <= GREEN;
    }else{
        return count <= BLUE;
    }
}