/*
proj10 - Dynamic Memory & MSet 
11302016
Section 002
Nic Wiggins
God is Good!
*/
#include<iostream>
using std::cout; using std::endl;
using std::ostream; using std::cin; using std::boolalpha;
#include<algorithm>
using std::copy; using std::transform; using std::find_if;
#include<utility>
using std::swap;
#include<string>
using std::string;
#include<vector>
using std::vector;
#include<iterator>
using std::istream_iterator; using std::back_inserter;
#include<sstream>
using std::ostringstream;

template<typename T>
struct SetElement {
public:
	T element;
	int cnt;
	SetElement() = default;
	SetElement(T val) : element(val), cnt(1) {};
};
template<typename T>
ostream &operator<<(ostream& out, const SetElement<T>& p) {
	out << p.element << ":" << p.cnt;
	return out;
}
template <typename T>
class MSet {
private:
	SetElement<T>* ary_;
	size_t size_;
	size_t capacity_;
	void grow();

public:
	MSet(size_t s = 2);
	MSet(T val);
	MSet(vector<T>&);
	MSet(MSet&);
	MSet operator=(MSet);
	~MSet() { delete[] ary_; };
	size_t size() { return size_; };
	size_t capacity() { return capacity_; };
	SetElement<T>* find(T);
	void insert(T);
	size_t count(T val);
	bool erase(T);

	friend ostream& operator<<(ostream& out, MSet<T>& m) {
		out << "Size:" << m.size_ << ", Capacity:" << m.capacity_ << endl;
		if (m.size_ == 0) out << "Empty";
		ostringstream oss;
		for (size_t i = 0; i < m.size_; i++)
			oss << m.ary_[i] << ", ";
		string output = oss.str();
		output = output.substr(0, output.length() - 2); //remove last " ,"
		out << output;
		return out;
	};
};
template <typename T>
MSet<T>::MSet(size_t s) {
	ary_ = new SetElement<T>[s]();
	capacity_ = s;
	size_ = 0;
}
template <typename T>
MSet<T>::MSet(T val) {
	ary_ = new SetElement<T>[2]();
	ary_[0].element = val;
	ary_[0].cnt = 1;
	capacity_ = 2;
	size_ = 1;
}
template <typename T>
MSet<T>::MSet(vector<T>& v) {
	capacity_ = 2;
	size_ = v.size();
	while (size_ > capacity_) //more efficient than calling grow()
		capacity_ *= 2;
	ary_ = new SetElement<T>[capacity_]();
	transform(v.begin(), v.end(), ary_,
		[](T val) {return SetElement<T>(val); });
}
template <typename T>
MSet<T>::MSet(MSet& m) { 						//copy
	capacity_ = m.capacity_;
	size_ = m.size_;
	ary_ = new SetElement<T>[capacity_]();
	copy(m.ary_, m.ary_ + m.size_, ary_);
}
template <typename T>
MSet<T> MSet<T>::operator=(MSet<T> m) {
	swap(size_, m.size_);
	swap(capacity_, m.capacity);
	swap(ary_, m.ary_);
	return *this;
}
template <typename T>
void MSet<T>::grow() {
	capacity_ *= 2;
	SetElement<T>* new_ary = new SetElement<T>[capacity_]();
	copy(ary_, ary_ + size_, new_ary);
	swap(ary_, new_ary);
	delete[] new_ary;
}
template <typename T>
SetElement<T>* MSet<T>::find(T val) {
	SetElement<T> * itr = find_if(ary_, ary_ + size_,
		[val](SetElement<T> s) {return s.element == val; });
	if (itr == ary_ + size_) itr = nullptr; //find_if returns last (ary_ + size_) if not found
	return itr;
}
template <typename T>
void MSet<T>::insert(T val) {
	SetElement<T>* itr = find(val);
	if (itr != nullptr) itr->cnt++; //value in MSet
	else {
		if (size_ == capacity_) grow();
		ary_[size_] = SetElement<T>(val);
		size_++;
	}
}
template <typename T>
size_t MSet<T>::count(T val) {
	SetElement<T>* ptr = find(val);
	if (ptr != nullptr) return ptr->cnt;
	else return 0;
}
template <typename T>
bool MSet<T>::erase(T val) {
	SetElement<T> * ptr = find(val);
	if (ptr != nullptr) {
		if (ptr->cnt > 1) ptr->cnt--;
		else {
			copy(ptr + 1, ptr + (size_ - (ptr - ary_)), ptr); //ptr arithmatic to find length of copy
			size_--;
		}
		return true;
	}
	return false;
}

// DO NOT CHANGE ANYTHING BELOW. TESTING!
int main(){
  int test;
  long l1, l2, l3;

  cin >> test;
  cout << boolalpha;

  switch (test){

    // basic constructors, .size() and .capacity()
  case 1 : {
    MSet<long> m_l;    
    cout << m_l.size() <<":"<< m_l.capacity()<<endl;    
    cin >> l1;
    MSet<long> m_l_oneval(l1);
    cout << m_l_oneval.size() <<":"<< m_l_oneval.capacity()<<endl;
    break;
  }

    // find
  case 2 : {
    cin >> l1 >> l2;
    MSet<long> m_l(l1);    
    auto p = m_l.find(l1);
    if (p != nullptr)
      cout << *p << endl;
    else
      cout << "Val:"<<l1<<" not found "<<endl;
    
    p = m_l.find(l2);
    if (p != nullptr)
      cout << *p << endl;
    else
      cout << "Val:"<<l2<<" not found "<<endl;
    break;
  }

    // insert and operator<<
  case 3 : {
    MSet<long> m_l;
    cin >> l1 >> l2 >> l3;
    cout << m_l << endl;
    m_l.insert(l1);
    cout << m_l << endl;
    m_l.insert(l2);
    m_l.insert(l3);
    m_l.insert(l2);
    cout << m_l << endl;
    break;
  }

    // copy
  case 4 : {
    MSet<long> m_l;
    cin >> l1 >> l2 >> l3;
    m_l.insert(l1);
    m_l.insert(l2);
    MSet<long> m_copy(m_l);
    m_copy.insert(l3);  
    cout << m_l << endl;
    cout << m_copy << endl;
    break;
  }

    // assign
  case 5 : {
    MSet<long> m_l;
    cin >> l1 >> l2 >> l3;
    m_l.insert(l1);
    m_l.insert(l2);   
    MSet<long> m_assign= m_l;
    m_assign.insert(l3);
    cout << m_l << endl;
    cout << m_assign << endl;
    break;
  }

    // erase
  case 6 : {
    cin >> l1 >> l2 >> l3;
    MSet<long> m_l;
    m_l.insert(l1);
    m_l.insert(l2);
    m_l.insert(l3);
    m_l.insert(l2);
    cout << m_l << endl;
    cout << m_l.erase(l2) << endl;
    cout << m_l << endl;
    cout << m_l.erase(l2) << endl;
    cout << m_l << endl;
    cout << m_l.erase(l2) << endl;
    cout << m_l << endl;
    break;
  }
    
    // string, vector constructor, count
  case 7 : {
    vector<string>v_s;
    copy(istream_iterator<string>(cin),
	 istream_iterator<string>(),
	 back_inserter(v_s)
	 );
    MSet<string>m_s(v_s);
    m_s.insert(v_s[0]);
    cout << m_s.count(v_s[0]) << endl;
    cout << m_s.count("xyzzy") << endl;
    cout << m_s << endl;
    break;
  }
  }
}
