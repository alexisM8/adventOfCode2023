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
std::vector<std::pair<int, int>> BFS(const std::vector<std::string>& grid, int start_row, int start_col, std::queue<std::pair<std::pair<int, int>, char>>& que);
bool isLeft(std::pair<int, int> a, std::pair<int, int> b, std::pair<int, int> c);
bool isInsidePolygon(const std::vector<std::pair<int, int>>& polygon, std::pair<int, int> point);


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

    std::queue<node> que;
    std::vector<std::pair<int, int>> points = BFS(tiles, row, col, que);

    int count = 0;
    for(auto& p : points){
        std::cout << "(" << p.first << ", " << p.second << ")\n";
        count += isInsidePolygon(points, p);
    }
    
    std::cout << "enclosed points: " << count << "\n";

    int ans = count*-1 + (points.size()/2) + 1;

    std::cout << "area: " << ans << "\n";
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
    if(row - 1 >= 0 && row - 1 < tiles.size()){
        if(col >= 0 && col < tiles[row - 1].size()){
            return {{row - 1, col}, tiles[row - 1][col]};
        }
    }
    return invalid;
}

node getDownStairsNeighbors(int row, int col, const std::vector<std::string>& tiles){
    node invalid = {{-1, -1}, '.'};
    if(row + 1 >= 0 && row + 1 < tiles.size()){
        if(col >= 0 && col < tiles[row + 1].size()){
            return {{row + 1, col}, tiles[row + 1][col]};
        }
    }
    return invalid;
}

node getLeftStairsNeighbors(int row, int col, const std::vector<std::string>& tiles){
    node invalid = {{-1, -1}, '.'};
    if(row >= 0 && row < tiles.size()){
        if(col - 1 >= 0 && col - 1 < tiles[row].size()){
            return {{row, col - 1}, tiles[row][col - 1]};
        }
    }
    return invalid;
}

node getRightStairsNeighbors(int row, int col, const std::vector<std::string>& tiles){
    node invalid = {{-1, -1}, '.'};
    if(row >= 0 && row < tiles.size()){
        if(col + 1 >= 0 && col + 1 < tiles[row].size()){
            return {{row, col + 1}, tiles[row][col + 1]};
        }
    }
    return invalid;
}

std::vector<std::pair<int, int>> BFS(const std::vector<std::string>& grid, int start_row, int start_col, std::queue<std::pair<std::pair<int, int>, char>>& que){
    node nodestart = {{start_row, start_col}, 'S'};

    std::vector<std::pair<int, int>> points;
    std::set<node> visited;
    long count = 0;

    que.push(nodestart);
    while (!que.empty()) {
        node n = que.front();
        que.pop();

        visited.insert(n);

        node up = getUpStairsNeighbors(n.first.first, n.first.second, grid);
        node down = getDownStairsNeighbors(n.first.first, n.first.second, grid);
        node left = getLeftStairsNeighbors(n.first.first, n.first.second, grid);
        node right = getRightStairsNeighbors(n.first.first, n.first.second, grid);

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
                if(!visited.contains(down) and (down.second == 'L' || down.second == 'J' || down.second == '|')){
                    que.push(down);
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
    }
    
    for(const auto& elem : visited){
        points.push_back({elem.first.first, elem.first.second});
    }

    return points;
}

bool isLeft(std::pair<int, int> a, std::pair<int, int> b, std::pair<int, int> c) {
    return ((b.first - a.first) * (c.second - a.second) - (c.first - a.first) * (b.second - a.second)) > 0;
}

bool isInsidePolygon(const std::vector<std::pair<int, int>>& polygon, std::pair<int, int> point) {
    int numIntersections = 0;
    int n = polygon.size();

    std::pair<int, int> extremePoint = {INT_MAX, point.second};

    for (int i = 0; i < n; ++i) {
        int next = (i + 1) % n;

        if (isLeft(polygon[i], polygon[next], point) != isLeft(polygon[i], polygon[next], extremePoint) &&
            std::min(polygon[i].first, polygon[next].first) < point.first &&
            std::max(polygon[i].second, polygon[next].second) >= point.second &&
            std::min(polygon[i].second, polygon[next].second) <= point.second) {
            numIntersections++;
        }
    }

    return (numIntersections % 2 == 1);
}