#include <iostream>
#include <fstream>
#include <map>
#include <sstream>

static constexpr char file_path[] = "puzzle_input/DayEight/DayEightStripped.txt";

std::vector<std::string> splitString(const std::string& str, char delimiter);

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

    {
        std::string node, left, right;
        for(auto& line : data){
            if(line != leftright && line != ""){
                std::stringstream ss(line);
                ss >> node >> left >> right;
                //std:: cout << "node: " << node << ", left: " << left << ", right: " << right << "\n";
                nodes[node] = {left, right};
            }
        }
    }


    bool found = false;
    std::string node = "AAA";
    int count = 0;
    while(!found){
        for(const auto& c : leftright){
            if(c == 'L'){
                node = nodes[node].first;
            }else{
                node = nodes[node].second;
            }
            if(node == "ZZZ"){
                found = true;
                count++;
                break;
            }else{
                count++;
            }
        }
    }

    std::cout << "count to zzz: " << count << "\n";
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