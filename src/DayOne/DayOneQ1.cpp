#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

    /*
    puzzle one:
        given a string of characters with at least 1 digit return the 
        sum of the first and last digit
            ex:
            1abc2
            pqr3stu8vwx
            a1b2c3d4e5f
            treb7uchet

            In this example, the calibration values of these four 
            lines are 12, 38, 15, and 77. Adding these together produces 142.
    */

int main(){
    //load contents of file
    std::ifstream infile("puzzle_input/DayOneQ1.txt");
    std::string input{};
    long long summation = 0;

    if (infile.fail()){
        std::cerr << "Error: Could not open puzzle_input/DayOneQ1.txt\n";
        exit(1);
    }

    //loop threw each line
    while (infile >> input){
        std::stringstream ss;
        
        //extract digits
        for(auto c : input){
            if(isdigit(c)){
                ss << c;
            }
        }
        std::string strnum{ss.str()};
        int num = std::stoi(strnum);
        //if number is > 2 in length make number from first and last
        if( strnum.length() >= 2){
            num = std::stoi(std::string(1, strnum[0]) + std::string(1, strnum[strnum.length()-1]));
        }else{
        //1 digit double it
            num = std::stoi(strnum+strnum);
        }

        //add to running total
        summation += num;
        ss.clear();
        
    }
    std::cout << "sum:"  << summation << "\n";
    return 0;
}