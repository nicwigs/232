/*
Proj08 - Bot
11072016
Nic Wiggins
Section 002
God is good!
*/
#include <iostream>
using std::cin; using std::cout; using std::endl; using std::ostream;
using std::boolalpha;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <stdexcept>
using std::out_of_range;
#include <map>
using std::map;
#include <utility>
using std::pair;
using std::make_pair;

class Grid {
	private:
		vector<vector<long>> g_;
		long x_;
		long y_;
		long dim_;
	public:
		Grid() = default;
		Grid(size_t, size_t, size_t);
		friend class Bot;
};
class Bot {
	private:
		long x_;
		long y_;
		char face_;
		long cmd_index_;
		string cmd_;
		Grid g_;
	public:
		Bot() = default;
		Bot(size_t, size_t, char, string, Grid&);
		void shift(int);
		void turn(int);
		void execute_command();
		bool at_goal();
		friend ostream& operator<<(ostream&, Bot&);
};

Grid::Grid(size_t dim, size_t x, size_t y) {
	x_ = x;
	y_ = y;
	dim_ = dim;
	vector<long> v(dim_, 0);
	for (int i = 0; i < static_cast<int>(dim); i++) {
		g_.push_back(v);
	}
	g_[x][y] = 1;
}

Bot::Bot(size_t x, size_t y, char face, string commands, Grid& g)
	:x_(x), y_(y), face_(face), cmd_(commands), g_(g), cmd_index_(0) {};

ostream& operator<<(ostream& out, Bot& b) {
	out << "(" << b.x_ << "," << b.y_ << ")" << " facing:" << b.face_;
	return out;
}

void wrapping(int & new_pos, string s) { // wraps string
	if (new_pos < 0) new_pos = s.size() - 1;
	else if (new_pos >= static_cast<int>(s.size())) new_pos = 0;
}

void Bot::turn(int new_dir) {
	//new_dir == 1 = rotate right, new_dir == -1 = rotate_left

	string directions = "nesw";
	int pos = directions.find(face_);
	int new_pos = pos + new_dir;

	try {
		face_ = directions.at(new_pos);
	}
	catch (const std::out_of_range& orr) { // change value if out of range
		wrapping(new_pos, directions);
		face_ = directions[new_pos];
	}
}

bool hit_wall(long x, long y, long dim) {
	if (x > dim-1 || x < 0 || y > dim-1 || y < 0) return true;
	return false;
}
void Bot::shift(int direction) {
	//direction == 1 = forward, direction == -1 = backward

	//for each direction, says which way can move on grid
	map<char, pair<long, long>> route = { { 'n',make_pair(0,1) },{ 'e',make_pair(1,0) },
	{ 's',make_pair(0,-1) } ,{ 'w',make_pair(-1,0) } };

	long dx = direction * route.at(face_).first;
	long dy = direction * route.at(face_).second;

	if (!hit_wall(x_ + dx, y_ + dy, g_.dim_)) {
		x_ += dx;
		y_ += dy;
	}
}
bool Bot::at_goal() {
	if (x_ == g_.x_ && y_ == g_.y_) return true;
	return false;
}
void Bot::execute_command() {
	if (cmd_[cmd_index_] == 'r') turn(1);
	else if (cmd_[cmd_index_] == 'l') turn(-1);
	else if (cmd_[cmd_index_] == 'f') shift(1);
	else if (cmd_[cmd_index_] == 'b') shift(-1);
	
	cmd_index_ + 1 == static_cast<int>(cmd_.size()) ? cmd_index_ = 0 : cmd_index_++;
}

int main(){
  cout << boolalpha;
  size_t dim, goal_x, goal_y;
  cin >> dim >> goal_x >> goal_y;

  size_t bot_x, bot_y;
  char bot_dir;
  string command_str;
  cin >> bot_x >> bot_y >> bot_dir >> command_str;

  long limit;
  cin >> limit;
  
  Grid g(dim, goal_x, goal_y);
  Bot b(bot_x, bot_y, bot_dir, command_str ,g);
  int cnt=0;

  while(!b.at_goal() && cnt < limit){
    //cout << b << endl;
    b.execute_command();
    ++cnt;
  }
  cout << b << endl;
  cout << b.at_goal();
}