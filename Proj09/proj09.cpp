/*
Project 09 - Polynomial Solving
11212016
Section 002
Nic Wiggins
God is Good!
*/
#include <iostream>
using std::cin; using std::cout; using std::endl;
#include <string>
using std::string; using std::stod; 
#include <deque>
using std::deque;
#include <map>
using std::map;
#include <vector>
using std::vector;
#include <sstream>
using std::istringstream; using std::ostringstream;
using std::ostream;
#include <iterator>
using std::istream_iterator;
using std::front_inserter;
#include <algorithm>
using std::transform;
using std::replace;
#include<cmath>
#include<limits>

class Polynomial {
private:
	deque<double> coef_;
	map<double,double> table_;
	double sample_;
	double x0_;
	double x1_;
public:
	Polynomial() = default;
	Polynomial(string s, long samp = 10, double x0 = 0.0, double x1 = 1.0) :
		sample_(samp), x0_(x0), x1_(x1) {process_string(s); set_table(samp, x0, x1);};

	Polynomial(deque<double>& co, long samp = 10, double x0 = 0.0, double x1 = 1.0) :
		sample_(samp), x0_(x0), x1_(x1), coef_(co) {set_table(samp, x0, x1);};

	void set_table(size_t samples, double x0, double x1);
	void process_string(string s, char delim = ' ');
	double eval(double);
	double full_eval(double val);
	friend ostream& operator<<(ostream&, const Polynomial& p);
	friend Polynomial operator+(const Polynomial& p1,const Polynomial& p2);
};
void Polynomial::process_string(string s, char delim) {
	replace(s.begin(), s.end(), delim, ' ');
	istringstream iss(s);
	transform(istream_iterator<string>(iss), istream_iterator<string>(), front_inserter(coef_), 
		[](string co) { return stod(co); });
}
double Polynomial::full_eval(double x) {
	double y = 0;
	for (unsigned int power = 0; power < coef_.size(); power++)
		y += coef_[power] * pow(x, power);
	return y;
}
void Polynomial::set_table(size_t samples, double x0, double x1) {
	table_.clear();
	const double step_sz =  (x1 - x0) / (samples - 1); 

	//max is x1+step since step_sz is not exact, ie. final step = 10.000000000000011

	for (double samp = x0; samp <= x1+step_sz; samp += step_sz)
		table_[samp] = full_eval(samp);
	x0_ = x0;
	x1_ = x1;
}
double Polynomial::eval(double val) {
	double y = 0;
	map<double,double>::iterator point = table_.lower_bound(val);
	
	if (val >= x0_ && val <= x1_) {

		//+/- since step is NOT precise ie 10.000000000000011 is a key

		if (point->first < val + 0.00000001 && point->first > val - 0.00000001) //in Table
			y = point->second;
		else                                                            //linear interp
			y = point->second + (val - point->first)
			*((point--)->second - point->second) /
			((point--)->first - point->first);
	}
	else														    	//calculate
		y = full_eval(val);
	return y;
}

Polynomial operator+(const Polynomial& p1, const Polynomial& p2) {
	deque<double> sum;

	if (p1.coef_.size() > p2.coef_.size()) {
		sum = p1.coef_;
		for (unsigned int i = 0; i < p2.coef_.size(); i++)
			sum.at(i) += p2.coef_.at(i);
	}
	else {
		sum = p2.coef_;
		for (unsigned int i = 0; i < p1.coef_.size(); i++)
			sum.at(i) += p1.coef_.at(i);
	}
	return Polynomial(sum);
}
ostream& operator<<(ostream& out, const Polynomial& p) {
	ostringstream oss;
	string output;
	string sign;
	
	for (int i = p.coef_.size()-1; i >= 0; i--) {						//reverse order
		if (p.coef_.at(i) > 0) sign = " + ";							//sign
		else sign = " - ";

		if (p.coef_.at(i)) {											//coef not 0
			if (!i) oss << sign << abs(p.coef_.at(i));					//0 power
			else if (i == 1) oss << sign << abs(p.coef_.at(i)) << "x";	
			else oss << sign << abs(p.coef_.at(i)) << "x**" << i;		
		}
	}
	output = oss.str().substr(3);										//remove inital sign
	out << output; 
	return out;
}
int main(){ 
  size_t samples; 
  double x0, x1, test_val; 
  string poly; 

  cin >> samples >> x0 >> x1 >> test_val; 
  cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');  
  getline(cin, poly); 
  Polynomial p1(poly, samples, x0, x1); 
  // cout << p1.dump_table() << endl; 
  cout << p1 << endl; 
  cout << p1.eval(test_val) << endl; 
  cout << p1.full_eval(test_val) << endl; 
  cout << p1.eval(x1) << endl; 
  cout << p1.eval(x1 + 1) << endl; 

  getline(cin, poly); 
  Polynomial p2(poly, samples, x0, x1); 
  Polynomial p = p1 + p2; 
  p.set_table(samples, x0, x1); 
  // cout << p.dump_table() << endl; 
  cout << p << endl;   
  cout << p.eval(test_val) << endl; 
  cout << p.full_eval(test_val) << endl; 
  cout << p.eval(x0) << endl; 
  cout << p.eval(x0 - 1) << endl; 
}