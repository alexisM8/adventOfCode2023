#include <iostream>
#include <sstream>
#include <fstream>
#include <ranges>

static constexpr char file_path[] = "puzzle_input/DaySix/DaySixStripped.txt";

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

    std::stringstream times(data[0]);
    std::stringstream distances(data[1]);

    int time = 0;
    int distance = 0;
    int wayToBeat = 0;
    int total = 1;

    while(times >> time && distances >> distance){
        for(int interval : std::views::iota(0, time+1)){
            int remaining = time - interval;
            int distravled = interval * remaining;
            if(distravled > distance){
                wayToBeat++;
            }
            std::cout << "time-" << time << ", held for : " << interval << ", distravled: " << distravled << "\n";
        }
        std::cout << "Time: " << time << ", ways to beat: " << wayToBeat << "\n"; 
        total *= wayToBeat;
        wayToBeat = 0;
    }

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