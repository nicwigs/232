/* 
proj11 - DisJoint Sets 
12072016 
Section 002 
Nic Wiggins 
God is Good! 
*/ 
#include<iostream> 
using std::cout; using std::endl; using std::cin; 
using std::ostream; 
#include<vector> 
using std::vector; 
#include<string> 
using std::string; 
#include<sstream> 
using std::ostringstream; 
#include<algorithm> 
using std::copy; 
#include <utility> 
using std::swap; 

template<typename T> 
class DJSet; 
template <typename T> 
struct Element { 
public: 
    T data_; 
    Element* next_; 

    Element() = default; 
    Element(T d) : data_(d), next_(nullptr) {}; 
    friend ostream& operator<<(ostream& out, Element e) { 
        out << e.data_; 
        return out; 
    }; 
    friend class DJSet<T>; 
}; 

template<typename T> 
class DJSet { 
private: 
    vector<Element<T>* > v_; 
public: 
    DJSet() = default; 
    DJSet(T); 
    DJSet(vector<T>); 
    DJSet(const DJSet&); 
    DJSet& operator=(DJSet); 
    ~DJSet(); 
    Element<T>* member(T); 
    Element<T>* add(T); 
    Element<T>* join(T, T); 

    friend ostream& operator<<(ostream& out, DJSet<T> ds) { 
        for (int i = 0; i < ds.v_.size(); i++) {  
            Element<T>* ptr = ds.v_[i]; 
            while (ptr != nullptr) { 
                out << *ptr << "-> "; 
                ptr = ptr->next_; 
            } 
            if (i < ds.v_.size() - 1) out << endl; 
        } 
        if (ds.v_.size() == 0) out << "empty"; 
        return out; 
    }; 
}; 
template<typename T> 
DJSet<T>::DJSet(const DJSet& d) { 
    Element<T>* new_head; 
    Element<T>* new_tail; 
    Element<T>* ptr; 
    Element<T>* new_element; 
    for (Element<T>* head : d.v_) { 
        new_head = new Element<T>(head->data_); 
        new_tail = new_head; 
        ptr = head->next_; 
        while (ptr != nullptr) { 
            new_element = new Element<T>(ptr->data_); 
            new_tail->next_ = new_element; 
            ptr = ptr->next_; 
            new_tail = new_element; 
        } 
        v_.push_back(new_head); 
    } 
} 
template<typename T> 
DJSet<T>::~DJSet() { 
    Element<T>* head; 
    Element<T>* del; 
    for (Element<T>* start : v_) { 
        head = start; 
        del = head; 
        while (head != nullptr) { 
            head = head->next_; 
            delete del; 
            del = head; 
        } 
    } 
} 
template<typename T> 
DJSet<T>::DJSet(vector<T> v) { 
    Element<T>* ptr; 
    for (T val : v) ptr = add(val); 
} 
template<typename T> 
DJSet<T>::DJSet(T val) { 
    Element<T>* head = new Element<T>(val); 
    v_.push_back(head); 
} 
template<typename T> 
DJSet<T>& DJSet<T>::operator=(DJSet d) { 
    swap(v_, d.v_); 
    return *this; 
} 
template<typename T> 
Element<T>* DJSet<T>::member(T val) { 
    Element<T>* ptr; 
    for (Element<T>* start : v_) { 
        ptr = start; 
        while (ptr != nullptr) { 
            if (ptr->data_ == val) return start; 
            else ptr = ptr->next_; 
        } 
    } 
    return nullptr; 
} 
template<typename T> 
Element<T>* DJSet<T>::add(T val) { 
    if (member(val) == nullptr) {                                //if not already in 
        Element<T>* ptr = new Element<T>(val); 
        v_.push_back(ptr); 
        return ptr; 
    } 
    return nullptr; 
} 
template<typename T> 
Element<T>* DJSet<T>::join(T val1, T val2) { 
    Element<T>* ptr1 = member(val1); 
    Element<T>* ptr2 = member(val2); 
    if (ptr1 != nullptr && ptr2 != nullptr) {                    //both found 
        Element<T>* tail2 = ptr2; 
        while (tail2->next_ != nullptr) tail2 = tail2->next_;   //find tail 
        tail2->next_ = ptr1;                                    //join! 
        v_.erase(find(v_.begin(), v_.end(), ptr1)); 
        return ptr2; 
    } 
    return nullptr; 
} 

// Don't change main!!!! 
int main (){ 
  int case_num; 
  cin >> case_num; 
  string name; 
  switch (case_num){ 
     
    // basic constructors 
  case 1: { 
    cin >> name; 
    Element<string> e(name); 
    cout << e << endl; 
    DJSet<string> djs_empty; 
    cout << djs_empty << endl; 
    break; 
  } 

    // single T constructor 
  case 2: { 
    cin >> name; 
    DJSet<string> djs_one(name); 
    cout << djs_one << endl; 
    break; 
  } 

    // vector T constructor.  
  case 3: { 
    vector<string> v_s; 
    while (cin >> name) 
      v_s.push_back(name); 
    DJSet<string> djs_3(v_s); 
    cout << djs_3 << endl; 
    break; 
  } 

    // member 
  case 4:{ 
    vector<string> v_s; 
    Element<string>* ptr; 
    while (cin >> name) 
      v_s.push_back(name); 
    DJSet<string> djs(v_s); 
    ptr = djs.member(v_s[0]); 
    cout << "Name:" << v_s[0]  
     <<( (ptr == nullptr) ? " not-member" : " member") 
     << endl; 
    ptr = djs.member("xyzzy"); 
    cout << "Name:" << "xyzzy" 
     <<( (ptr == nullptr) ? " not-member" : " member") 
     << endl; 
    break; 
  } 

    // add 
  case 5: { 
    DJSet<string> djs_add; 
    Element<string>* ptr; 
    while (cin >> name){ 
      ptr = djs_add.add(name); 
      cout << "Name:" << name  
       <<( (ptr == nullptr) ? " not-added" : " added") 
       << endl; 
    } 
    cout << djs_add << endl; 
      cout << "Add returns:" 
       <<( (ptr == nullptr) ? " nullptr" : name) 
       << endl; 
    break; 
  } 
     
    // copy constructor 
  case 6: { 
    cin >> name; 
    DJSet<string> djs(name); 
    DJSet<string> djs_copy(djs); 
    cin >> name; 
    djs_copy.add(name); 
    cin >> name; 
    djs.add(name); 
    cout << djs << endl; 
    cout << endl; 
    cout << djs_copy << endl; 
    break; 
  } 

    // operator = 
  case 7: { 
    DJSet<string> djs_rhs; 
    DJSet<string> djs_lhs; 
    cin >> name; 
    djs_rhs.add(name); 
    cin >> name; 
    djs_rhs.add(name); 
     
    cin >> name; 
    djs_lhs.add(name); 
    cin >> name; 
    djs_lhs.add(name); 

    djs_lhs = djs_rhs; 
    cout << djs_lhs << endl; 
    cout << endl; 
    cout << djs_rhs << endl;   
    break; 
  } 

    // join 
  case 8:{ 
    DJSet<string> djs; 
    Element<string>* ptr; 
     
    while(cin >> name) 
      djs.add(name); 
    djs.join("Francis", "Fiona"); 
    cout << djs << endl; 
    cout << endl; 
    djs.join("Francis", "Fred"); 
    cout << djs << endl; 
    cout << endl; 
    djs.join("Faith", "Frieda"); 
    ptr = djs.join("Faith", "Fiona"); 
    cout << djs << endl; 
    cout << endl; 
    cout << "Faith and Fiona " 
     <<( (ptr == nullptr) ? " not-joined" : " joined") 
     << endl; 
    cout << *ptr << endl; 
    ptr = djs.join("xyzzy", "Ford"); 
    cout << djs << endl; 
    cout << "xyzzy and Ford"  
     <<( (ptr == nullptr) ? " not-joined" : " joined") 
     << endl; 
    break; 
  } 
  } 
} 