/*
Nicholas Wiggins
Date: 09192016
Section: 002
Project: 002
---Uses two different formulas for calculating pi via a summation,
-----values are outputed once consecutive values for same method are 
-----within the user's inputed epsilon.
*/

#include <iostream>
using std::cin; using std::cout; using std::endl;
#include <cmath>
using std::pow; using std::abs;
#include <iomanip>
using std::fixed; using std::setprecision;
///////////////////////////////////////////////////////////////////////
double gl_series(long iteration, double previous){ 
    /* 
    Gregory-Leibniz Series
    parameters: current iteration value and previous value of pi
    outputs: updated pi
    To save time this function simply builds off of the previous
    calculated value of pi, adding the next term to the series. 
    */ 
    
    double pi = 0.0;
    
    //adding new term to old term, via formula
    pi =4*(pow(-1,iteration)/(2*iteration + 1))+previous; 
    return pi;    
}
///////////////////////////////////////////////////////////////////////
double n_series(long iteration, double previous){ 
    /* 
    Nilakantha Series
    Parameters: current iteration value and previous value of pi
    outputs: updated pi
    To save time this function simply builds off of the previous
    calculated value of pi, adding the next term to the series. 
    */
    
    double pi = 0.0;
    
    //adding new term to old term,via formula
    pi =4*(pow(-1,iteration)/
    ((2*iteration+2)*(2*iteration+3)*(2*iteration+4)))+previous; 
    return pi;
}
///////////////////////////////////////////////////////////////////////
int iterate(double pi_current, bool gl_method, double epsilon){
    /* 
    Parameters: current pi value, true (1) for Gregory-Leibniz Series,
    0 for Nilakantha Series, and inputed epsilon
    Outputs: 0
    Iterates through desired formula and finds pi to specific epsilon
    Prints pi and number of iterations to reach desired epsilon 
    */

    double pi_previous = 0.0;
    long iterate = 1;
    
    do{
        pi_previous = pi_current; //make previous pi equal to current
        //check which method we are using, and update current pi
        if(gl_method) 
            pi_current = gl_series(iterate,pi_previous);
        else
            pi_current = n_series(iterate,pi_previous);
        iterate++;                     //increase iteration
    //check if met the ultimate goal
    }while(abs(pi_current - pi_previous) > epsilon); 
    
    //Once done, output pi to 12 decimals and number of iterations 
    cout << fixed << setprecision(12) << pi_current << " " 
    << iterate << endl;
    return 0;
}
int main(){
    double epsilon = 0.0;
    cin >> epsilon;
    double gl_pi_current = 0.0;
    double n_pi_current = 0.0; 

    if (epsilon == 0.0){ //if enter 0, output desired values
        cout << fixed << setprecision(12) << 0.0  << " " << 0 << endl; 
        cout << fixed << setprecision(12) << 0.0  << " " << 0 << endl; 
    }
    else{ //normal case
        //initalize when n = 0 in gl formula, need this start for while loop 
        gl_pi_current = 4; 
        iterate(gl_pi_current, 1, epsilon);
        
        //initalize when n = 0 in n formula, need this start for while loop 
        n_pi_current = 3.0 + 4.0*(1/24.0); 
        iterate(n_pi_current,0,epsilon);
    }
    return 0;
}        