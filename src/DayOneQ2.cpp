#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

    /*
    puzzle two:
        given a string of characters with at least 1 digit return the 
        num of the first and last digit, except accept spelling like two
            ex:
            1abc2
            pqr3stu8vwx
            a1b2c3d4e5f
            treb7uchet

            In this example, the calibration values of these four 
            lines are 12, 38, 15, and 77. Adding these together produces 142.
    */

int tryFindDigitSpelling(const std::string &str, int offset);
int tryFindDigitSpellingRev(const std::string &str, int offset);

int main(){
    //load contents of file
    std::ifstream infile("puzzle_input/DayOne.txt");
    std::string input{};
    long long summation = 0;
    int linenumber = 1;

    if (infile.fail()){
        std::cerr << "Error: Could not open puzzle_input/DayOneQ1.txt\n";
        exit(1);
    }

    //loop threw each line
    while (infile >> input){
        bool digit1 = false;
        bool digit2 = false;
        std::string firstdigit{};
        std::string seconddigit{};
        for( int i = 0; i < input.length(); i++){
            if(!digit1){
                if(isdigit(input[i])){
                    digit1 = true;
                    firstdigit = input[i];
                    //std::cout << "first digit: " << firstdigit << "\n";
                    break;
                }else{
                    int num = tryFindDigitSpelling(input, i);
                    if(num > 0){
                        digit1 = true;
                        firstdigit = std::to_string(num);
                        //std::cout << "first digit: " << firstdigit << "\n";
                        break;
                    }
                }
            }
        }
        for(int i = input.length()-1; i >= 0; i--){
            
            if(!digit2){
                if(isdigit(char(input[i]))){
                    digit2 = true;
                    seconddigit = input[i];
                    //std::cout << "second digit: " << seconddigit << "\n";
                    break;
                }else{
                    int num = tryFindDigitSpellingRev(input, i);
                    if(num > 0){
                        digit2 = true;
                        seconddigit = std::to_string(num);
                        //std::cout << "second digit: " << seconddigit << "\n";
                        break;
                    }
                }   
            }
        }
        std::cout << "line: " << linenumber <<  "  number: " << firstdigit << seconddigit << "\n";
        int num = std::stoi(firstdigit+seconddigit);
        //add to running total
        summation += num;
        linenumber++;
    }
    std::cout << "sum:"  << summation << "\n";
    return 0;
}

int tryFindDigitSpelling(const std::string &str, int offset) {
    if (str[offset] == 'o' && str.substr(offset, 3) == "one") {
        return 1;
    } else if (str[offset] == 't') {
        if (str.substr(offset, 3) == "two") {
            return 2;
        } else if (str.substr(offset, 5) == "three") {
            return 3;
        }
    } else if (str[offset] == 'f') {
        if (str.substr(offset, 4) == "four") {
            return 4;
        } else if (str.substr(offset, 4) == "five") {
            return 5;
        }
    } else if (str[offset] == 's') {
        if (str.substr(offset, 3) == "six") {
            return 6;
        } else if (str.substr(offset, 5) == "seven") {
            return 7;
        }
    } else if (str[offset] == 'e' && str.substr(offset, 5) == "eight") {
        return 8;
    } else if (str[offset] == 'n' && str.substr(offset, 4) == "nine") {
        return 9;
    }
    return -1;
}

int tryFindDigitSpellingRev(const std::string &str, int offset) {
    if (offset >= 2 && str.substr(offset - 2, 3) == "one") {
        return 1;
    } else if (offset >= 3 && str.substr(offset - 2, 3) == "two") {
        return 2;
    } else if (offset >= 4 && str.substr(offset - 4, 5) == "three") {
        return 3;
    } else if (offset >= 3 && str.substr(offset - 3, 4) == "four") {
        return 4;
    } else if (offset >= 3 && str.substr(offset - 3, 4) == "five") {
        return 5;
    } else if (offset >= 2 && str.substr(offset - 2, 3) == "six") {
        return 6;
    } else if (offset >= 4 && str.substr(offset - 4, 5) == "seven") {
        return 7;
    } else if (offset >= 4 && str.substr(offset - 4, 5) == "eight") {
        return 8;
    } else if (offset >= 3 && str.substr(offset - 3, 4) == "nine") {
        return 9;
    } else {
        return -1;
    }
}