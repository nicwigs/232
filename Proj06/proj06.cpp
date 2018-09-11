/* 
Project 06 - Game of life 
10242016 
Section 002 
Nic Wiggins 
*/ 

#include <iostream> 
using std::cout; using std::endl; using std::cin; 
#include <vector> 
using std::vector; 
#include <string> 
using std::string; using std::getline; 
#include <algorithm> 
using std::for_each; 
using std::count; 
#include <utility> 
using std::pair; 
using std::make_pair; 


void print(vector<string> & v) { 
    //View for Debugging  
    for_each(v.begin(), v.end(),  
        [](const string & s) { 
        cout << s << endl; 
    }); 
} 
void wrapping(const vector<string>& v, long& row, long& col) { 
    //corrects row and col if out of bounds of grid for wrap feature 
    if (row < 0) row = v.size() - 1; 
    else if (row >= static_cast<int>(v.size())) row = 0; 
    if (col < 0) col = v.at(row).size() - 1; 
    else if (col >= static_cast<int>(v.at(row).size())) col = 0; 
} 
int on_check(const vector<string>& v,  long& row,  long& col) { 
    //Reutrns 1 if cell is on, 0 if cell is off 
    int is_on = 0; 
    return  v[row][col] == '#' ? is_on = 1 : is_on = 0; 
} 
int check_neighbors(const vector<string> & v, const long& row, const long& col) { 
    //Returns number of 'on' neighbor cells 
    //vector of pairs <row,col> of neighbor cells relative to any given cell starting upper left corner moving clockwise.  
    vector<pair<int, int>> neighbors{{-1,-1},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1}}; 
    int on_cnt = 0; 

    for (auto cell : neighbors) { 
        long row_neighbor = cell.first + row; 
        long col_neighbor = cell.second + col; 
        wrapping(v, row_neighbor, col_neighbor); 
        on_cnt += on_check(v,row_neighbor,col_neighbor); 
    } 
    return on_cnt; 
} 
pair <string, string> rules() { 
    /*Grabs rule specifications and splits to each rule part 
    Reutrns pair of rules, born rules and survive rules */ 
    string rules; 
    getline(cin, rules); 
    int slash_pos = rules.find('/');     

    string born = rules.substr(1, slash_pos - 1); 
    string survive = rules.substr(slash_pos + 2); 

    return make_pair(born, survive);  
} 
vector<string> new_grid(vector<string> grid1, string born, string survive) { 
    //Creates new grid from rules specfied and current grid 
    vector<string> grid2 = grid1; 
    for (long row = 0; row < static_cast<int>(grid1.size()); row++) { 
        for (long col = 0; col < static_cast<int>(grid1[row].size()); col++) { 
            char on_cnt = check_neighbors(grid1, row, col) + 48; //number of on neighbors to char for later count comparrison         
            if (grid1[row][col] == '#') {                             //cell in current grid is on, to survive...             
                int satisfy = count(survive.begin(), survive.end(), on_cnt); //rules are strings, search for matching chars 
                satisfy ? grid2[row][col] = '#' : grid2[row][col] = '.'; 
            } 
            else {                                                     //cell in current grid is off, to be born... 
                int satisfy = count(born.begin(), born.end(), on_cnt); 
                satisfy ? grid2[row][col] = '#' : grid2[row][col] = '.'; 
            } 
        } 
    } 
    return grid2; 
} 
vector<string> grid_init(long row_cnt) { 
    //Creates first grid 
    string row; 
    vector<string> grid1; 
    for (long i = 0; i < row_cnt; i++) { 
        getline(cin, row); 
        grid1.push_back(row); 
    } 
    return grid1; 
} 
int final_count(vector<string> grid1) { 
    //Returns number of 'on' cells in grid 
    long on_cnt = 0; 
    for (auto row : grid1) { 
        on_cnt += count(row.begin(), row.end(), '#'); 
    } 
    return on_cnt; 
} 
void run_iterations(long iterations, vector<string> & grid1, pair<string,string> & rule_pair) { 
    //Runs through number of specified times by user  
    for (int i = 0; i < iterations; i++) { 
        grid1 = new_grid(grid1, rule_pair.first, rule_pair.second); 
        //print(grid1); 
    } 
} 
int main(){ 
    pair <string, string> rule_pair = rules(); 

    long iterations; 
    cin >> iterations; 

    long row_cnt = 0, col_cnt = 0; 
    string junk; //grabs the left over '/n' from cin/getline() combination   
    cin >> row_cnt >> col_cnt; 
    getline(cin, junk); 

    vector<string> grid1 = grid_init(row_cnt); 

    //print(grid1); 
    run_iterations(iterations, grid1, rule_pair); 

    cout << final_count(grid1) << endl; 
} 
