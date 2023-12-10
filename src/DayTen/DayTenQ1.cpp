#include <iostream> 
#include <queue>
#include <map>

static constexpr char file_path[] = "puzzle_input/DayTen/DayTenSample.txt";

std::map<char, std::string> tile_maps = {
    {'|', "LJF7"},
    {'-', "LJF7"},
    {'L', "-|J7F"},
    {'7', "LFJ-|"},
    {'F', "-|7LJ"}
}

int main(){
    std::cout << "Day Ten AOC Pathfinding\n";
}