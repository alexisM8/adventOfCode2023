#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <set>
#include <map>

/*
you win copies of the scratchcards below the winning card equal 
    to the number of matches. So, if card 10 were to have 5 
    matching numbers, you would win one copy each of cards 
    11, 12, 13, 14, and 15.

Copies of scratchcards are scored like normal scratchcards 
    and have the same card number as the card they copied. 
    So, if you win a copy of card 10 and it has 5 matching numbers, 
    it would then win a copy of the same cards that the original 
    card 10 won: cards 11, 12, 13, 14, and 15. This process repeats 
    until none of the copies cause you to win any more cards. 
    (Cards will never make you copy a card past the end of the table.)

This time, the above example goes differently:

Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53
Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19
Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1
Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83
Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36
Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11

Card 1 has four matching numbers, so you win one copy each of the 
    next four cards: cards 2, 3, 4, and 5.

Your original card 2 has two matching numbers, 
    so you win one copy each of cards 3 and 4.

Your copy of card 2 also wins one copy each of cards 3 and 4.

Your four instances of card 3 (one original and three copies) 
    have two matching numbers, so you win four copies each of cards 
    4 and 5.

Your eight instances of card 4 (one original and seven copies) 
    have one matching number, so you win eight copies of card 5.

Your fourteen instances of card 5 (one original and thirteen copies) 
    have no matching numbers and win no more cards.

Your one instance of card 6 (one original) has no matching numbers 
    and wins no more cards.

Once all of the originals and copies have been processed, 
    you end up with 1 instance of card 1, 2 instances of 
    card 2, 4 instances of card 3, 8 instances of card 4, 14 
    instances of card 5, and 1 instance of card 6. 
    In total, this example pile of scratchcards causes you to 
    ultimately have 30 scratchcards!

Process all of the original and copied scratchcards 
    until no more scratchcards are won. Including the 
    original set of scratchcards, how many total scratchcards 
    do you end up with?
*/

static constexpr char file_path[] = "puzzle_input/DayFour/DayFourStripped.txt";

std::vector<std::string> splitString(const std::string& str, char delimiter);
std::set<int> toset(const std::string& winningnumbers);
std::optional<int> stringToInt(const std::string& str);
std::ostream& operator <<(std::ostream& o, const std::set<int>& set);
void fillmap(std::map<int, int>& map);

int main() {
    std::ifstream input(file_path);
    std::map<int, int> cards;
    fillmap(cards);
    int summation = 0;
    
    if(input.fail()){
        std::cerr << "Error: could not open file " << file_path << "\n";
        exit(1);
    }

    std::stringstream ss;
    ss << input.rdbuf();
    std::string file_contents{ ss.str() };

    auto tokens = splitString(file_contents, '\n');
    
    for(auto &[card, copies]: cards){
        std::cout << "orig card: " << card << " coupies " << copies << "\n";
        for(int i = 0; i < copies; i++){
            int count = 0;
            auto values = splitString(tokens[card-1], '|');
            auto winningnumbers = toset(values[0]);
            auto nums = splitString(values[1], ' ');
            for(const auto& num : nums){
                auto converted = stringToInt(num);
                if(converted.has_value() && winningnumbers.contains(converted.value())){
                    count++;
                }
            }
            if (count > 0) {
                int lastCard = std::min(card + count, static_cast<int>(cards.size()));
                for (int j = card + 1; j <= lastCard; j++) {
                    if (cards.find(j) == cards.end()) {
                        cards[j] = 1; 
                    } else {
                        cards[j] += 1; 
                    }
                    std::cout << "card " << j << " now has " << cards[j] << " copies\n";
                }
            }
        }
    }
    for(const auto& [card, copies]: cards){
        summation += copies;
    }
    std::cout << "summation: " << summation << "\n";
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

std::set<int> toset(const std::string& winningnumbers){
    auto numbers = splitString(winningnumbers, ' ');
    std::set<int> ret;
    for(const auto& num : numbers){
        auto number = stringToInt(num);
        if(number.has_value()){
            ret.insert(number.value());
        }

    }
    return ret;
}

std::optional<int> stringToInt(const std::string& str) {
    try {
        size_t pos = 0;
        int value = std::stoi(str, &pos);
        if (pos < str.size()) {
            // If there are non-numeric characters after the valid integer, it's invalid
            std::cerr << "Non-numeric characters in string: " << str << "\n";
            return std::nullopt; 
        }
        return value;
    } catch(const std::invalid_argument& e) {
        //std::cerr << "Invalid argument: " << e.what() << "\n";
        return std::nullopt; 
    } catch(const std::out_of_range& e) {
        std::cerr << "Out of range: " << e.what() << "\n";
        return std::nullopt;
    }
}

std::ostream& operator <<(std::ostream& o, const std::set<int>& set){
    o << "[";
    for(const auto& value: set){
        o << value << ", ";
    }
    o << "]";
    return o;
}

void fillmap(std::map<int, int>& map){
    for(int i = 1; i <= 199; i++){
        map[i] = 1;
    }
}