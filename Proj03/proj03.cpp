#include <iostream>
using std::cout;using std::cin; using std::endl;using std::boolalpha;
#include <cmath>
using std::sqrt;

long sum_divisors(long num){
//Parameter: long num. Returns the sum of all the divsors of num. 
	long sum;
	num == 1 ? sum = 0 : sum =1+num; //initalize sum to 1 + the value
	for(int i = 2; i <= sqrt(num); i++){ //max possible factor is sqrt
		if (not (num % i)){ //if i is a factor of num
			sum += num / i + i; //+ divisor and answer to sum
		} //end if
	}//end for
	return sum;
}// end sum_divisors
bool is_k_perfect(int k, long num){
//Paremters: k-what type of perfect, num - see if this number is k-perfect
//returns true if num is k-perfect 
	return num * k == sum_divisors(num); //condition for k-perfect
}//end is_k_perfect
void check_range(int k,int first,int last){
//Parameters: first- inclusive beginning of range
// last - inclusive last number in range
//k - of the k-perfect numbers
//prints all numbers in range that are k perfect 
	for (long i = first; i <= last; i++){ //range
		if(is_k_perfect(k,i)){ //k func for all values in range
			cout << i << " "; //output on one line
		} //end if
	} //end for
} // end check_range 
int main(){
	cout << boolalpha;
	long first, last, num, k;
	cin >> num;
	cout << sum_divisors(num) << endl;
	cin >> k;
	cout << is_k_perfect(k,num) << endl;
	cin >> first >> last;
	check_range(k,first,last);
	cout << endl;
}
