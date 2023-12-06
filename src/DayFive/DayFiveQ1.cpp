#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <limits>
#include <ranges>

static constexpr char file_path[] = "puzzle_input/DayFive/DayFive.txt";

struct MapData{
    long long dst;
    long long src;
    long long rng;
};

std::vector<std::string> customSplit(const std::string& str);
std::vector<std::string> splitString(const std::string& str, char delimiter);
std::string convert_category(const std::string& input, std::string& map);

int main() {
    std::ifstream input(file_path);
    double smallest = std::numeric_limits<double>::infinity();

    if (input.fail()) {
        std::cerr << "Error: could not open file " << file_path << "\n";
        exit(1);
    }

    std::stringstream ss;
    ss << input.rdbuf();
    std::string file_contents{ ss.str() };

    auto tokens = customSplit(file_contents);

    std::stringstream seeds(splitString(tokens[0], ':')[1]);
    std::string stos_map(splitString(tokens[1], ':')[1]);
    std::string stof_map(splitString(tokens[2], ':')[1]);
    std::string ftow_map(splitString(tokens[3], ':')[1]);
    std::string wtol_map(splitString(tokens[4], ':')[1]);
    std::string ltot_map(splitString(tokens[5], ':')[1]);
    std::string ttoh_map(splitString(tokens[6], ':')[1]);
    std::string htol_map(splitString(tokens[7], ':')[1]);

    std::cout << std::fixed;

    long long seed;
    std::string next;
    while (seeds >> seed) {
            std::cout << "seed: " << seed;
            next = convert_category(std::to_string(seed), stos_map);
            std::cout << ", soil:  " << next;
            next = convert_category(next, stof_map);
            std::cout << ", fertilizer:  " << next;
            next = convert_category(next, ftow_map);
            std::cout << ", water:  " << next;
            next = convert_category(next, wtol_map);
            std::cout << ", light:  " << next;
            next = convert_category(next, ltot_map);
            std::cout << ", temperature:  " << next;
            next = convert_category(next, ttoh_map);
            std::cout << ", humidity:  " << next;
            next = convert_category(next, htol_map);
            std::cout << ", location:  " << next << "\n";
            long long num = std::stoll(next);
            if (num < smallest) {
                smallest = num;
            }
    }

    std::cout << "lowest location: " << smallest << "\n";
}

std::string convert_category(const std::string& input, std::string& map) {
    long long num = std::stoll(input);
    std::stringstream ss(map);

    std::vector<MapData> mapData; // Define a struct to store map data

    // Parse map data into a vector of structs
    std::string line;
    while (std::getline(ss, line)) {
        if (line.empty())
            continue; // Skip empty lines
        
        MapData data{};
        auto splitdata = splitString(line, ' ');

        data.dst = std::stoll(splitdata[0]);
        data.src = std::stoll(splitdata[1]);
        data.rng = std::stoll(splitdata[2]);

        mapData.push_back(data);
    }
    
    for (const auto& data : mapData) {
        if (num >= data.src && num < data.src + data.rng) {
            return std::to_string(data.dst + (num - data.src));
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