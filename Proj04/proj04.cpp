/*
Project 04
Section 002
10022016
wiggin63
196 Algorithm - Checking if a number is a palindrome, and if not applying the 196 algorithm to see
    if the the number is a Lychrel number (cant be made a palindrome) or not.
*/
#include <iostream>
using std:: cin; using std:: cout; using std::endl; using std::boolalpha;
#include <string>
using std::to_string; using std::stol; using std::string;
#include <algorithm>
using std::reverse;

long rev_num(long n){
	/*reverses the order of the digits of n, returns that reversed number*/ 
	
	string str = to_string(n);		//convert number to string
	reverse(str.begin(),str.end()); //reverse num 
	return stol(str); 				//return string as long
}
bool is_palindrome(long n){
	/*returns true if the number is a palindrome, false otherwise
	calls rev_num*/ 
	
	return n == rev_num(n); 
}
bool check_args(long limit, long &first, long &second){
	/*if the first is greater than second, the 2 numbers should be swapped
	if any of limit, first or second is less than one, return false, else return true*/
	
	if (first > second){     //first needs to be smaller than second
		long temp = first;  //change if not...
		first = second;
		second = temp; 
	}
	return (limit >= 1) && (first >= 1) && (second >= 1); 
}
bool check_lychrel(long n, long limit){
	/*apply the 196 algorithm for limit itertions or until the number becomes a palindrome
	returns true if the number of iterations exceeds the limit, false otherwise
	calls is_palindrome and rev_num */
	
	long count = 1;  								//dont run if already a palindrome 
	while(not(is_palindrome(n)) && count <= limit){ //if its not a palindrome and in limit
		n = n + rev_num(n); 						//add reversal to int
		count++;            						//keep track of how many iterations 
	}
	return not(is_palindrome(n));
}
long check_range(long start, long end, long limit, long &natural_cnt, long &pal_cnt){
	/*checks each number in the range from start to finish (inclusive) to classify each num
	returns the count of Lychrel numbers found in the range
	natural_cnt = the number of natural palindromes
	pal_cnt is set to the number of non-natural palindromic numbers found by 
	applicatin of check_lychrel within the limit
	calls check_lychrel, is_palindrome */
	
	for(int i = start; i<= end;i++){     //over given range
		if(is_palindrome(i)){       	 //if already a palindrome
			natural_cnt++;				 //then its a natural palindrome
		}
		else if (not(check_lychrel(i,limit))){ //if not a natural, try algorithm
			pal_cnt++; 						   //if becomes one, add to pal_count.
		}					
	}				
	return (end-start + 1) - (natural_cnt + pal_cnt);	//return number of lychrel numbers 
}
int main() {
    cout << boolalpha;
    long num, limit;
    long start, end;
    long natural_cnt=0, pal_cnt=0, lychrel_cnt = 0;
        
    cin >> num;
    cout << rev_num(num)<<endl;
    cin >> num;
    cout << is_palindrome(num)<<endl;
    cin >> num >> limit;
    cout << check_lychrel(num,limit)<< endl;
    cin >> start >> end >> limit;
    if (check_args(limit, start, end)){    
      lychrel_cnt = check_range(start, end, limit, natural_cnt, pal_cnt);
      cout << lychrel_cnt << " " << natural_cnt << " " << pal_cnt << endl;
    }
    else cout << "error" << endl;
}