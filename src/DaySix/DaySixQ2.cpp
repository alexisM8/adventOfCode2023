#include <iostream>
#include <sstream>
#include <fstream>
#include <ranges>

static constexpr char file_path[] = "puzzle_input/DaySix/DaySixP2Comb.txt";

std::vector<std::string> splitString(const std::string& str, char delimiter);


int main(){
    std::ifstream input(file_path);

    if (input.fail()) {
        std::cerr << "Error: could not open file " << file_path << "\n";
        exit(1);
    }

    std::stringstream ss;
    ss << input.rdbuf();
    std::string file_contents{ ss.str() };

    auto data = splitString(file_contents, '\n');

    std::stringstream t(data[0]);
    std::stringstream d(data[1]);

    long long time = 0;
    long long distance = 0;
    long long wayToBeat = 0;
    long long total = 1;

    t >> time;
    d >> distance;

    for(long long interval : std::views::iota(0, time+1)){
        long long remaining = time - interval;
        long long distravled = interval * remaining;
        if(distravled > distance){
            wayToBeat++;
        }
        std::cout << "time-" << time << ", held for : " << interval << ", distravled: " << distravled << "\n";
    }
    std::cout << "Time: " << time << ", ways to beat: " << wayToBeat << "\n"; 

    std::cout << "Total ways to beat all: " << total << "\n";
    return 0;
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