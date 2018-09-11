/*
Proj07 - UNi & BI GRAMS
10312016
Nic Wiggins
Section 002
*/
#include <iostream>
using std::cout; using std::endl; using std::cin;
#include <string>
using std::string; using std::getline;
#include <algorithm>
using std::transform;
#include <vector>
using std::vector;
#include <sstream>
using std::istringstream; 
using std::ostringstream;
#include <iterator>
using std::istream_iterator;
using std::back_inserter;
#include <map>
using std::map; 
#include <utility>
using std::swap; 

string process_word(string s) {
	//returns lower case s, stripped in front and behind the word 
	transform(s.begin(), s.end(), s.begin(), tolower);

	string alpha = "abcdefghijklmnopqrstuvwxyz";	
	int start = s.find_first_of(alpha);
	int length = s.find_last_of(alpha) - start + 1; 
	s = s.substr(start, length);

	return s;
}
void process_line(string line, vector<string>& v) {
	//splits line into individual words, store in vector
	istringstream iss(line);
	transform(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(v),process_word);
}
void bi_key_check(const map<string, long>& bi, string& first, string& second){
	//if not already in map, swap values. To avoid bigram different order issue
	if (!bi.count(first + " " + second))
		swap(first, second);
}
void read_file(map<string, long>& bi, map<string, long>& uni) {
	//Stores each word(s) from each line into maps
	string line; 

	while(getline(cin, line)) {		
		vector<string> words;
		process_line(line, words);

		for (int i = 0; i < static_cast<int>(words.size()); i++) { //fill uni
			uni[words[i]]++;
		}		
		for (int i = 0; i < static_cast<int>(words.size()) - 1; i++) { //fill bi
			string first = words[i];
			string second = words[i + 1];
			bi_key_check(bi, first, second);
			bi[first + " " + second]++;
		}		
	} 
}
string report_counts(const map<string, long>& bi, const map<string, long>& uni, string word1, string word2) {
	//Collects data on uni and bigrams
	bi_key_check(bi, word1, word2); 
	long bi_cnt = bi.at(word1 + " " + word2);
	long word1_cnt = uni.at(word2); //word2 due to bi_key_check's nature
	long word2_cnt = uni.at(word1);
	long unique_bi = bi.size();
	long unique_uni = uni.size();
	ostringstream oss;
	oss << bi_cnt << " " << word1_cnt - bi_cnt << " " << word2_cnt - bi_cnt 
		<< " " << unique_bi << " " << unique_uni;
	return oss.str();
}
 int main (){
  map<string,long> bigrams;
  map<string, long> unigrams;
  string word1, word2, line;
  cin >> word1 >> word2; // get the two words
  getline(cin,line); // clear the \n at end of first line
  
  read_file(bigrams, unigrams); // read the lines and process

  cout << report_counts(bigrams, unigrams, word1, word2)
       << endl;
}