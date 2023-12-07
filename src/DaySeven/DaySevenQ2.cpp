#include <iostream>
#include <map>
#include <utility>
#include <sstream>
#include <fstream>

static constexpr char file_path[] = "puzzle_input/DaySeven/DaySevenQ2.txt";

static std::map<std::string, int> suits = {
    {"A", 14},
    {"K", 13},
    {"Q", 12},
    {"J", 11},
    {"T", 10},
    {"9", 9},
    {"8", 8},
    {"7", 7},
    {"6", 6},
    {"5", 5},
    {"4", 4},
    {"3", 3},
    {"2", 2},
    {"J", 1},
};

static std::map<std::string, int> winning_hands  = {
    {"5", 7},
    {"14", 6},
    {"23", 5},
    {"113", 4},
    {"122", 3},
    {"1112", 2},
    {"11111", 1}
};

struct Elements{
    std::string hand;
    int type;
    int bid;
};

std::vector<std::string> splitString(const std::string& str, char delimiter);
std::pair<int, int> getHandType(const std::string& hand, int bid);

int main(){

    std::ifstream input(file_path);
    long long summation = 0;

    if (input.fail()) {
        std::cerr << "Error: could not open file " << file_path << "\n";
        exit(1);
    }

    std::stringstream ss;
    ss << input.rdbuf();
    std::string file_contents{ ss.str() };

    auto games = splitString(file_contents, '\n');

    // hand is key, value is pair: first->type, second->bid
    std::map<std::string, std::pair<int, int>> hands;

    std::string cards;
    int bid;
    for(auto &game : games){
        std::stringstream ss(game);
        ss >> cards >> bid;
        hands[game] = getHandType(cards, bid);
    }

    //for(auto& [hand, type_bid] : hands){
    //    std::cout << "hand: " << hand << ", type: " << type_bid.first << ", bid: " << type_bid.second << "\n";
    //}
    std::vector<Elements> sorted_hands{};
    for(auto& [hand, type_bid] : hands){
        sorted_hands.push_back({.hand = hand, .type = type_bid.first, .bid = type_bid.second});
    }
    
    auto pred_type = [](const Elements& obj1, const Elements& obj2){
        if(obj1.type < obj2.type){
            return true;
        }
        return false;
    };

    auto pred_hand = [](const Elements& obj1, const Elements& obj2){
        if(obj1.type < obj2.type){
            return true;
        }else if(obj1.type == obj2.type){
            for(int i = 0; i < obj1.hand.length(); i++){
                if(suits[obj1.hand.substr(i, 1)] < suits[obj2.hand.substr(i, 1)]){
                    return true;
                }else if (suits[obj1.hand.substr(i, 1)] == suits[obj2.hand.substr(i, 1)]){
                    continue;
                }else{
                    return false;
                }
            }
        }
        return false;
    };

    //std::sort(sorted_hands.begin(), sorted_hands.end(), pred_type);
    std::sort(sorted_hands.begin(), sorted_hands.end(), pred_hand);

    int rank = 1;
    for(const auto& e : sorted_hands){
        std::cout << "rank: " << rank << ", hand: " << e.hand << ", type: " << e.type << ", bid: " << e.bid << "\n";
        summation += e.bid * rank;
        rank++;
    }

    std::cout << "total winnings: " << summation << "\n";

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

std::pair<int, int> getHandType(const std::string& hand, int bid) {
    std::map<std::string, int> suitss = {
        {"A", 0},
        {"K", 0},
        {"Q", 0},
        {"J", 0},
        {"T", 0},
        {"9", 0},
        {"8", 0},
        {"7", 0},
        {"6", 0},
        {"5", 0},
        {"4", 0},
        {"3", 0},
        {"2", 0},
        {"J", 0}
    };
    for(int i = 0; i < hand.length(); i++){
        suitss[hand.substr(i, 1)] += 1;
    }
    std::string combo;
    int joker = 0;
    for(auto [key, value] : suitss){
        if(value > 0){
            std::cout << "key: " << key << ", value: " << value <<"\n";
            if(key != "J"){
                combo.append(std::to_string(value));
            } else if(key == "J"){
                joker = value;
            }
        }
    }

    std::sort(combo.begin(), combo.end());
    std::cout << "combo before: " << combo << ", jokers: " << joker;
    

    switch(joker){
        case 1:{
            if(combo == "22"){
                combo = "23";
            }else if(combo == "112"){
                combo = "113";
            }else if(combo == "1111"){
                combo = "1112";
            }else if(combo == "13"){
                combo = "14";
            }else if(combo == "4"){
                combo = "5";
            }
            break;
        }
        case 2:{
            if(combo == "111"){
                combo = "113";
            }else if(combo == "3"){
                combo = "5";
            }else if(combo == "12"){
                combo = "14";
            }
            break;
        }
        case 3:{
            if(combo == "11"){
                combo = "14";
            }else if(combo == "2"){
                combo = 5;
            }
            break;
        }
        case 4:{
            if(combo == "1"){
                combo = 5;
                break;
            }
        }
        case 5:{
            combo = "5";
            break;
        }
        default: break;
    }

    std::cout << ", combo After: " << combo << "\n";

    return std::make_pair(winning_hands[combo], bid);
}
