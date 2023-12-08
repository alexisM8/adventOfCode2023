#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <ranges>
#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>


static constexpr char file_path[] = "puzzle_input/DayEight/DayEightQ2Stripped.txt";

std::vector<std::string> splitString(const std::string& str, char delimiter);
void getNextPositions(std::vector<std::string>& nodes, char dir, std::map<std::string, std::pair<std::string, std::string>>& map);
bool checkAllZs(const std::vector<std::string>& nodes);

int main(){
    std::ifstream input(file_path);

    if(input.fail()){
        std::cout << "[Error] could not open file: " << file_path << "\n";
        exit(1);
    }

    std::stringstream ss;
    ss << input.rdbuf();
    std::string file_contents{ ss.str() };

    auto data = splitString(file_contents, '\n');
    
    std::string leftright = data[0]; 

    // node is 3 letter code, value is pair: first->left_node_code, second->right_node_code
    std::map<std::string, std::pair<std::string, std::string>> nodes;
    std::vector<std::string> starting_nodes;

    {
        std::string node, left, right;
        for(auto& line : data){
            if(line != leftright && line != ""){
                std::stringstream ss(line);
                ss >> node >> left >> right;
                if(node.back() == 'A'){
                    starting_nodes.push_back(node);
                }
                //std:: cout << "node: " << node << ", left: " << left << ", right: " << right << "\n";
                nodes[node] = {left, right};
            }
        }
    }
    std::vector<std::int64_t> end_counts(starting_nodes.size(), 0);
    std::int64_t count = 0;
    while(!checkAllZs(starting_nodes)){
        for(const auto& c : leftright){
            count++;
            
            for(int i = 0; i < starting_nodes.size(); i++){
                if(end_counts[i] > 0){
                    continue;
                }

                std::string& cur = starting_nodes[i];
                if(c == 'L'){
                    cur = nodes[cur].first;
                }else{
                    cur = nodes[cur].second;
                }

                if(cur.back() == 'Z'){
                    end_counts[i] = count;
                }
            }
        }
    }

    if (!end_counts.empty()) {
        auto lcm_result = std::accumulate(
            std::next(end_counts.begin()), end_counts.end(),
            end_counts[0],
            [](long long acc, long long val) { return std::lcm(acc, val); }
        );

        std::cout << "LCM: " << lcm_result << std::endl;
    }
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

void getNextPositions(std::vector<std::string>& nodes, char dir, std::map<std::string, std::pair<std::string, std::string>>& map){
    for(auto& n : nodes){
        if(dir == 'L'){
            n = map[n].first;
        }else{
            n = map[n].second;
        }
    }
}

bool checkAllZs(const std::vector<std::string>& nodes){
    bool ret = true;
    for(const auto& n : nodes){
        if(n.back() != 'Z'){
            ret = false;
        }
    }
    return ret;
}