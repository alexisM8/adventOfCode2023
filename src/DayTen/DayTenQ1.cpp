#include <iostream> 
#include <queue>
#include <map>
#include <fstream>
#include <sstream>
#include <set>
#include <utility>

static constexpr char file_path[] = "puzzle_input/DayTen/DayTen.txt";
using node = std::pair<std::pair<int, int>, char>;

std::vector<std::string> splitStringStr(const std::string& str, char delimiter);
node getUpStairsNeighbors(int row, int column, const std::vector<std::string>& tiles);
node getDownStairsNeighbors(int row, int column, const std::vector<std::string>& tiles);
node getLeftStairsNeighbors(int row, int column, const std::vector<std::string>& tiles);
node getRightStairsNeighbors(int row, int column, const std::vector<std::string>& tiles);
long BFS(const std::vector<std::string>& grid, int start_row, int start_col, std::queue<std::pair<std::pair<int, int>, char>>& que);
void printNode(const node& n);

int main(){
    std::ifstream input_file(file_path);

    if(input_file.fail()){
        std::cout << "[Error]: could not open file: " << file_path << "\n";
        exit(1);
    }

    std::stringstream ss;
    ss << input_file.rdbuf();
    std::string file_contents{ ss.str() };

    auto tiles = splitStringStr(file_contents, '\n');

    int row = 20; //20
    int col = 103; //103
    char value = tiles[row][col];

    std::cout << "row : " << row << " col: " << " char: " << value << "\n";

    std::queue<node> que;
    long length = BFS(tiles, row, col, que);

    std::cout << "BFS returned: " << length <<  " should be: " << 6907 << "\n";

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

node getUpStairsNeighbors(int row, int col, const std::vector<std::string>& tiles){
    node invalid = {{-1, -1}, '.'};
    if(row - 1 >= 0 and row - 1 < tiles.size()){
        if(col >= 0 && col < tiles[row].size()){
            return {{row-1, col}, tiles[row - 1][col]};
        }else{
            return invalid;
        }
    }else{
        return invalid;
    }
    return invalid;
}

node getDownStairsNeighbors(int row, int col, const std::vector<std::string>& tiles){
    node invalid = {{-1, -1}, '.'};
    if(row + 1>= 0 and row + 1 < tiles.size()){
        if(col >= 0 && col < tiles[row].size()){
            return {{row+1, col}, tiles[row + 1][col]};
        }else{
            return invalid;
        }
    }else{
        return invalid;
    }
    return invalid;
}

node getLeftStairsNeighbors(int row, int col, const std::vector<std::string>& tiles){
    node invalid = {{-1, -1}, '.'};
    if(row >= 0 and row < tiles.size()){
        if(col - 1 >= 0 && col < tiles[row].size() - 1){
            return {{row, col-1}, tiles[row][col - 1]};
        }else{
            return invalid;
        }
    }else{
        return invalid;
    }
    return invalid;
}

node getRightStairsNeighbors(int row, int col, const std::vector<std::string>& tiles){
    node invalid = {{-1, -1}, '.'};
    if(row >= 0 and row < tiles.size()){
        if(col + 1 >= 0 && col < tiles[row].size() + 1){
            return {{row, col+1}, tiles[row][col + 1]};
        }else{
            return invalid;
        }
    }else{
        return invalid;
    }
    return invalid;
}

long BFS(const std::vector<std::string>& grid, int start_row, int start_col, std::queue<std::pair<std::pair<int, int>, char>>& que){
    node nodestart = {{start_row, start_col}, 'S'};

    std::set<node> visited;
    long count = 0;

    que.push(nodestart);
    while(!que.empty()){
        std::cout << "set size: " << visited.size() <<  " queue size: " << que.size() << "\n";

        node n = que.front();
        que.pop();

        if(count == 0 and n.second == 'S'){

        }else if(count > 0 and n.second == 'S'){
            //break;
        }

        visited.insert(n);

        std::cout << "current ";
        printNode(n);

        node up = getUpStairsNeighbors(n.first.first, n.first.second, grid);
        node down  = getDownStairsNeighbors(n.first.first, n.first.second, grid);
        node left = getLeftStairsNeighbors(n.first.first, n.first.second, grid);
        node right = getRightStairsNeighbors(n.first.first, n.first.second, grid);

        std::cout << "up node: ";
        printNode(up);

        std::cout << "down node: ";
        printNode(down);

        std::cout << "left node: ";
        printNode(left);

        std::cout << "right node: ";
        printNode(right);
        

        switch(n.second){
            case '|':{
                if(!visited.contains(up) and (up.second == 'F' || up.second == '7' || up.second == '|')){
                    que.push(up);
                    count++;
                }
                if(!visited.contains(down) and (down.second == 'L' || down.second == 'J' || down.second == '|')){
                    que.push(down);
                    count++;
                }
                break;
            }
            case '-':{
                if(!visited.contains(left) and (left.second == 'L' || left.second == 'F' || left.second == '-')){
                    que.push(left);
                    count++;
                }
                if(!visited.contains(right) and (right.second == 'J' || right.second == '7' || right.second == '-')){
                    que.push(right);
                    count++;
                }
                break;
            }
            case 'F':{
                if(!visited.contains(down) and (down.second == '|' || down.second == 'J' || down.second == 'L')){
                    que.push(down);
                    count++;
                }
                if(!visited.contains(right) and (right.second == '-' || right.second == '7' || right.second == 'J')){
                    que.push(right);
                    count++;
                }
                break;
            }
            case 'J':{
                if(!visited.contains(up) and (up.second == '|' || up.second == '7' || up.second == 'F')){
                    que.push(up);
                    count++;
                }
                if(!visited.contains(left) and (left.second == '-' || left.second == 'L' || left.second == 'F')){
                    que.push(left);
                    count++;
                }
                break;
            }
            case 'L':{
                if(!visited.contains(up) and (up.second == '|' || up.second == '7' || up.second == 'F')){
                    que.push(up);
                    count++;
                }
                if(!visited.contains(right) and (right.second == '-' || right.second == 'J' || right.second == '7')){
                    que.push(right);
                    count++;
                }
                break;
            }
            case '7':{
                if(!visited.contains(left) and (left.second == '-' || left.second == 'F' || left.second == 'L')){
                    que.push(left);
                    count++;
                }
                break;
            }
            case 'S':{
                if(!visited.contains(up) and (up.second == 'F' || up.second == '7' || up.second == 'J' || up.second == '|')){
                    que.push(up);
                    count++;
                }
                if(!visited.contains(right) and (right.second == '-' || right.second == 'J' || right.second == '7')){
                    que.push(right);
                    count++;
                }
                if(!visited.contains(down) and (down.second == '|' || down.second == 'L' || down.second == 'J')){
                    que.push(down);
                    count++;
                }
                if(!visited.contains(left) and (left.second == '-' || left.second == 'F' || left.second == 'F' || left.second == 'L')){
                    que.push(left);
                    count++;
                }
                break;
            }
            default: break;
        }
        std::cout << "\n";
    }
    return count+2;
}

void printNode(const node& n){
    std::cout << "Node: " << "(" << n.first.first << ", " << n.first.second << ")" << ": " << n.second << "\n";
}