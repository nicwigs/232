/*
Project 05 - Steganography
Section 02
Nic Wiggins
10172016
*/
#include <iostream>
using std::cin; using std::cout;using std::endl;
#include <string>
using std:: string; using std:: to_string;
#include <cmath>
using std::pow;
#include <algorithm>
using std::count_if; 

string lower_case(string s){ 
	//returns the lowercased input string 
	for (char &chr : s)
		chr = tolower(chr);
	return s;
}
string dec_to_binary(long dec){
	//converts base 10 to binary 
	string bit_str = "";
	do{
		bit_str = to_string(dec%2) + bit_str;		
		dec /= 2;			
	}while(dec > 0);	
	return bit_str;
}
string to_binary(char c){
	//Returns 5 bit string that is the index of the character argument	
	unsigned long char_num = 0 ;	
	if (isalpha(c)){
		char_num = c - 'a';
	}
	else if (isspace(c)){
		char_num = 27;
	}	
	string bit_str = dec_to_binary(char_num);	
	while (bit_str.size() <5 )
		bit_str = '0' + bit_str;
	return bit_str;
}
int from_binary (string bit_str){
	//convert binary string to base 10
	long dec = 0;
	for (unsigned int i = 0; i < bit_str.size();i++){
		int digit = bit_str[i] - '0';	
		dec += digit*pow(2,bit_str.size() - 1 - i);		
	}
	return dec;
}
bool check_message(string original_text, string secret_message){
	//make sure at least 5x as many letters in original than secret 
	return count_if(original_text.begin(),original_text.end(),isalpha) >= 
	count_if(secret_message.begin(),secret_message.end(),isalpha)*5;
}
string secret_encode(const string &secret_message){
	//Creates bit string for the whole secret message 
	string secret = "";
	for (auto chr : secret_message)	
		secret += to_binary(chr);		
	return secret;
}
string encode(string original_text, string secret_message){
	//Encodes secret message 
	original_text = lower_case(original_text);
	secret_message = lower_case(secret_message);
	
	if (check_message(original_text,secret_message)){
		string secret = secret_encode(secret_message);	
		//loop through bit str of secret_message, secret 
		for (unsigned long secret_indx = 0, orig_indx = 0; secret_indx < secret.size();secret_indx++,orig_indx++){			
			while (!isalpha(original_text[orig_indx])){ //skip over original text index if punct or space
				orig_indx++;
			}		
			if (secret[secret_indx] == '1'){ //Uppercase if secret code is 1 		
				original_text[orig_indx] = toupper(original_text[orig_indx]);				
			}				
		}
	}
	else{
		return "error";
	}
	return original_text;
}
string decode(string to_decode){
	//Finds secret message 
	string bit_str = "";
	for (auto chr : to_decode){
		if (isalnum(chr))
			isupper(chr) ? bit_str += '1' : bit_str += '0';
	}
	char c = 'a';
	string decoded = "";
	for (size_t i = 0; i < bit_str.size()/5;i++){
		long dec = from_binary(bit_str.substr(i*5,5));
		dec == 27 ? c = ' ' : c = 'a' + dec;
		decoded += c; 
	}
	return decoded; 
}
int main(){
	//cout << lower_case("HI MADDIE THOSE COOKIES WERE GOoD") << endl;
	//cout << to_binary(' ') << endl;
	cout << secret_encode("you are ") << endl;
	cout << encode("some say the world will end in fire. Some say in ice.", "you are ") << endl;
	//cout << secret_encode("you are in danger you must flee soonaa") << endl;
	//cout << decode("SOme saY THe WoRld WIlL End in fIre. sOme Say IN iCE. fRom whAT i'VE TaSTed oF Desire i HOlD wiTH thoSe tHat fAVOr FIRE. but iF IT hAd To pERiSH tWIce I tHinK i kNoW enOUGH oF HatE tO sAy THat For deStrUCtION icE is ALSo gREAt aND wOuld suffice") << endl;
	//cout << from_binary("01000") << endl;
	//cout << alpha_cnt("HI Mom") << endl;
	cout << check_message("hi mom","t");
	//cout << encode("MOMPleaseSendMoreMoney", "help");
}