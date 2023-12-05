#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <limits>

static constexpr char file_path[] = "puzzle_input/DayFive/DayFiveSample.txt";

std::vector<std::string> customSplit(const std::string& str);
std::vector<std::string> splitString(const std::string& str, char delimiter);
std::string convert_category(int input, const std::vector<std::string>& maps);

int main() {
    std::ifstream input(file_path);
    int smallest = std::numeric_limits<int>::max();

    if (input.fail()) {
        std::cerr << "Error: could not open file " << file_path << "\n";
        exit(1);
    }

    std::stringstream ss;
    ss << input.rdbuf();
    std::string file_contents{ ss.str() };

    auto tokens = customSplit(file_contents);

    std::vector<std::string> maps;
    for (size_t i = 1; i < tokens.size(); ++i) {
        std::string map = splitString(tokens[i], ':')[1];
        maps.push_back(map);
    }

    std::cout << "made it past all splitting\n";

    std::vector<int> seeds;
    std::stringstream seed_stream(splitString(tokens[0], ':')[1]);
    int seed;
    while (seed_stream >> seed) {
        seeds.push_back(seed);
    }

    for (const auto& seed : seeds) {
        int location = std::stoi(convert_category(seed, maps));
        //std::cout << "seed: " << seed << " location: " << "\n";
        if (location < smallest) {
            smallest = location;
        }
    }

    std::cout << "lowest location: " << smallest << "\n";
}

std::string convert_category(int input, const std::vector<std::string>& maps) {
    int num = input;

    for (const auto& map : maps) {
        std::vector<std::string> mapData = splitString(map, '\n');
        std::cout  << map << "\n";
        
        for (const auto& line : mapData) {
            if(line != ""){
                std::vector<std::string> tokens = splitString(line, ' ');
                //std::cout << tokens.size() << " sdfm\n";
                int start = std::stoi(tokens[0]);
                int end = std::stoi(tokens[1]);
                int range = std::stoi(tokens[2]);


                if (num >= start && num < start + range) {
                    int distance = num - start;
                    return std::to_string(end + distance);
                }
            }
        }
    }
    return std::to_string(num); // If not mapped, return the input number itself
}

std::vector<std::string> splitString(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

std::vector<std::string> customSplit(const std::string& str) {
    std::vector<std::string> tokens;
    size_t startPos = 0;

    while (startPos < str.length()) {
        size_t endPos = str.find("\n\n", startPos);
        if (endPos == std::string::npos) {
            endPos = str.length();
        }

        tokens.push_back(str.substr(startPos, endPos - startPos));
        startPos = endPos + 2; // Skip the two '\n' characters
    }

    return tokens;
}