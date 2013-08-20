/*
This is a solution to the numbers to words challenge on Codersumo (http://codersumo.com/challenges/4)
input <- integer up to 1E+15
output -> text representation of integer

example: 
input: 123456
output: one-hundred-twenty-three-thousand-four-hundred-fifty-six

CTRL+C to quit
*/

#include <iostream>
#include <stdlib.h>

#define VALID(x) ( x > 47 && x < 58)
#define CONVERT(x) ( x - 48 )
#define MAXNUMLENGTH 15

using namespace std;

bool ValidString(string);               // forward declaration

int main() {
    int intNum = 0;
    string str;
    short thousandPlace, unitPlace, digit;
    bool printThousands;
    string lessThan20[] = {
        "","one","two","three",
        "four","five","six",
        "seven","eight","nine",
        "ten","eleven","twelve",
        "thirteen","fourteen",
        "fifteen","sixteen","seventeen",
        "eighteen","nineteen"
        }; 
    string lessThan100[] = {            
            "","","twenty","thirty","fourty","fifty","sixty","seventy","eighty","ninety"
        };                              
        string thousands[] = {
            "", "-thousand","-million","-billion","-trillion"
        };       
        
    while( getline(cin, str) ) {
        // check validity of input
        if (!ValidString(str)){
            cout << "Invalid number. Try again. CTRL+C to quit.\n";
            continue;
        }
        int len = str.length();
        for(intNum=0; intNum < len; ++intNum){
            thousandPlace = (len-intNum-1)/3;                                   // locate the thousands place
            unitPlace=(len-intNum)%3;                                           // locate the location of digit in reference to nearest comma
            digit = CONVERT(str[intNum]);                                       // integer representation of digit being evaluated 
            if (digit > 0 && intNum > 0) { cout <<"-"; }                        // if number being evaluated isn't 0 or the first number, output "-"
            switch (unitPlace)                                                  // review the unitPlace
            {
             case 2:                                                            // evaluating ,_ X _,
                if(digit > 1) {                                                 // digit is not part of a teen
                    cout << *(lessThan100 + digit); 
                    printThousands = true; 
                    break;
                } else {                                                        // digit is part of a teen
                    digit = digit * 10 + CONVERT(str[intNum+1]);
                    ++intNum;                                                   // let it fall through
                    }
            case 1:                                                             // evaluating ,_ _ X,
                cout <<  *(lessThan20 + digit);
                if(printThousands || digit > 0) cout <<  *(thousands + thousandPlace);
                break; 
            case 0:                                                             // evaluating ,X _ _,
                cout <<  *(lessThan20 + digit); 
                printThousands = false;
                if(digit> 0) { 
                    cout << "-hundred"; 
                    printThousands = true; }
                break;
            default:
                break;
            }
        } cout << "\n";
    }
    return 0;
}

bool ValidString(string str){
    // returns whether a converted string consists of an acceptable number
    for(std::string::size_type i = 0; i < str.size(); ++i) { 
            if (!VALID(str[i]) || i > MAXNUMLENGTH) { 
                return false;}
        }
    return true;
}
