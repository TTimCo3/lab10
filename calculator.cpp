#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

bool isDigit(char ele){
    if (ele == '0' || ele == '1' || ele == '2' || ele == '3' || ele == '4' || ele == '5'
    || ele == '6' || ele == '7' || ele == '8' || ele == '9') return true;
    else return false;
}

bool validate(string num){
    bool decimal = false;
    if (!num.empty()){
        if (num[0]!= '+' && num[0] != '-' && !isDigit(num[0])) return false;
        else{
            for (int i = 1; i<num.length(); i++){
                if (!isDigit(num[i])){
                    if(num[i] == '.' && decimal == false){
                        decimal = true;
                        if ((num.length()-1) == i) return false;
                        else{
                            if (!isDigit(num[i+1])) return false;
                        }
                    }
                    else return false;
                }
                else{
                    if(i==(num.length()-1)) return true;
                }
            }
        }
        return true;
    }
    else return false;
}

string addition(string num1, string num2){
    char op1 = '+', op2 = '+';
    if(num1[0] == '+' || num1[0] == '-') { op1 = num1[0]; num1 = num1.substr(1); }
    if(num2[0] == '+' || num2[0] == '-') { op2 = num2[0]; num2 = num2.substr(1); }
    string int1, frac1, int2, frac2;
    size_t dot1 = num1.find('.');
    if(dot1 != string::npos){ int1 = num1.substr(0,dot1); frac1 = num1.substr(dot1+1); } else int1=num1;
    size_t dot2 = num2.find('.');
    if(dot2 != string::npos){ int2 = num2.substr(0,dot2); frac2 = num2.substr(dot2+1); } else int2=num2;
    while(frac1.length() < frac2.length()) frac1 += '0';
    while(frac2.length() < frac1.length()) frac2 += '0';
    while(int1.length() < int2.length()) int1 = '0' + int1;
    while(int2.length() < int1.length()) int2 = '0' + int2;
    bool num1Greater;
    if(int1 != int2)
        num1Greater = int1 > int2;
    else
        num1Greater = frac1 > frac2;
    reverse(int1.begin(), int1.end());
    reverse(int2.begin(), int2.end());
    string sum = "";
    string fracSum = "";
    bool carry = false;
    for(int i = frac1.length()-1; i >= 0; i--){
        int digit1 = frac1[i] - '0';
        int digit2 = frac2[i] - '0';
        int temp;
        if(op1 == op2){
            temp = digit1 + digit2 + (carry ? 1 : 0);
            carry = temp >= 10;
            temp %= 10;
        } else {
            if(num1Greater) temp = digit1 - digit2 - (carry ? 1 : 0);
            else temp = digit2 - digit1 - (carry ? 1 : 0);
            if(temp < 0){ temp += 10; carry = true; } else carry = false;
        }
        fracSum = char(temp+'0') + fracSum;
    }
    while(!fracSum.empty() && fracSum.back() == '0')
        fracSum.pop_back();
    for(int i = 0; i < int1.length(); i++){
        int digit1 = int1[i] - '0';
        int digit2 = int2[i] - '0';
        int temp;
        if(op1 == op2){
            temp = digit1 + digit2 + (carry ? 1 : 0);
            carry = temp >= 10;
            temp %= 10;
        } 
        else {
            if(num1Greater) temp = digit1 - digit2 - (carry ? 1 : 0);
            else temp = digit2 - digit1 - (carry ? 1 : 0);
            if(temp < 0){ temp += 10; carry = true; } else carry = false;
        }
        sum += char(temp+'0');
    }
    if(carry && op1 == op2) sum += '1';
    reverse(sum.begin(), sum.end());
    while(sum.length() > 1 && sum[0] == '0') sum.erase(0,1);
    while(!fracSum.empty() && fracSum.back() == '0') fracSum.pop_back();
    string finalSum = sum;
    if(!fracSum.empty()) finalSum =  sum + "." + fracSum;
    if(op1 == op2){
        if(op1 == '-') finalSum = '-' + finalSum;
    } else {
        if(finalSum == "0"){
        }
        else if(!num1Greater) finalSum = (op2 == '-') ? '-' + finalSum : finalSum;
        else finalSum = (op1 == '-') ? '-' + finalSum : finalSum;
    }
    return finalSum;
}

void readFile(string& filename){
    string line;
    ifstream myfile (filename);
    if (myfile.is_open()){
        while(getline(myfile, line)){
            if(line.empty()) continue;
            size_t space = line.find(' ');
            string num1 = line.substr(0,space);
            string num2 = line.substr(space+1);
            bool valid1 = validate(num1);
            bool valid2 = validate(num2);
            if (valid1 && valid2){
                string result = addition(num1, num2);
                cout << num1 << " + " << num2 << " = " << result << endl << endl;
                
            }
            else{
                cout << "A number is invalid" << endl << endl;
            }
        }
    }
    else{
        cout << "Unable to open file";
        cout << endl;
        return;
    }
}

int main(){
    cout << "Enter the name of the file: ";
    string name;
    cin>>name;
    cout << endl;
    readFile(name);

    return 0;
}