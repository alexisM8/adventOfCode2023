#include <iostream>
#include <sstream>
#include <fstream>
#include <ranges>

static constexpr char file_path[] = "puzzle_input/DayNine/DayNine.txt";

template <typename T>
std::vector<T> splitString(const std::string& str, char delimiter);
template <typename T>
std::ostream& operator<<(std::ostream& o, const std::vector<T>& vec);
std::vector<int> getVecDiff(const std::vector<int>& vec);
bool checkAllZeros(const std::vector<int>& vec);
std::vector<std::string> splitStringStr(const std::string& str, char delimiter);

int main(){
    std::ifstream input(file_path);
    int summation = 0;
    bool done = false;

    if (input.fail()) {
        std::cerr << "Error: could not open file " << file_path << "\n";
        exit(1);
    }

    std::stringstream ss;
    ss << input.rdbuf();
    std::string file_contents{ ss.str() };

    auto data = splitStringStr(file_contents, '\n');

    std::vector<std::vector<int>> calc{};

    for(const auto& line : data){
        auto nums = splitString<int>(line, ' ');
        auto diffs = nums;
        calc.push_back(diffs);
        while(!done){
            diffs = getVecDiff(diffs);
            if(!checkAllZeros(diffs)){
                calc.push_back(diffs);
            }else{
                done = true;
                break;
            }
        }
        int history = 0;
        for(int i = calc.size()-1; i >= 0; i--){
            history = calc[i].front() - history;
        }
        summation += history;
        calc.clear();
        done = false;
    }
    std::cout << "summation: " << summation << "\n";

}

template <typename T>
std::vector<T> splitString(const std::string& str, char delimiter) {
    std::vector<T> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        std::stringstream converter(token);
        T converted;
        if (converter >> converted) {
            tokens.push_back(converted);
        }
    }
    return tokens;
}

std::vector<std::string> splitStringStr(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

template <typename T>
std::ostream& operator<<(std::ostream& o, const std::vector<T>& vec) {
    o << "[";
    if (!vec.empty()) {
        auto last = vec.end() - 1;
        for (auto it = vec.begin(); it != last; ++it) {
            o << *it << ", ";
        }
        o << *last;
    }
    o << "]\n";
    return o;
}

bool checkAllZeros(const std::vector<int>& vec){
    int ret = true;
    for(const auto& e : vec){
        if(e != 0){
            ret = false;
            break;
        }
    }
    return ret;
}

std::vector<int> getVecDiff(const std::vector<int>& vec){
    std::vector<int> ans{};
    for(int i = 0; i < vec.size() - 1; i++){
        int j = i +1;
        int diff = vec[j] - vec[i];
        ans.push_back(diff);
    }
    return ans;
}