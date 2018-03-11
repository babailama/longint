#include<bits/stdc++.h>
using namespace std;

const int DIGIT_AFTER_COMA = 8;

struct myLongInt{
    bool is_negative;
    vector<int> numbers;
    vector<int> fraction;
};

void print (myLongInt number)
{
    if (number.is_negative) {
        cout<<'-';
    }
    for(unsigned int i=0; i<number.numbers.size(); i++){
        cout<<number.numbers[i];
    }
    if(number.fraction.size() > 0 ) {
            cout<<'.';
        for(int i=0; i<number.fraction.size(); i++){
            cout<<number.fraction[i];
        }
    }
    cout<<' ';
}

void println (myLongInt number)
{
    print(number);
    cout<<'\n';
}

myLongInt string2mylongint(string number)
{
    myLongInt res;
    int pos=0;
    if(number[0]=='-') {
        pos=1;
        res.is_negative=true;
    }
    else {
        res.is_negative=false;
    }
    for(int i=pos; i<number.length(); i++){
        res.numbers.push_back(number[i]-'0');
    }
    return res;
}

myLongInt integer2mylongint(int number) {
    myLongInt result;
    if (number < 0) {
        result.is_negative = true;
        number = (-1) * number;
    } else {
        result.is_negative = false;
    }
    if (number == 0) {
        result.numbers.push_back(0);
    }

    vector<int> temp;
    while (number) {
        int x = number % 10;
        number /= 10;
        temp.push_back(x);
    }
    for (int i = temp.size() - 1; i >= 0; --i) {
        result.numbers.push_back(temp[i]);
    }
    return result;
}

// return true when rhs > lhs
// return false when rhs <= lhs
bool cmp(myLongInt lhs, myLongInt rhs) {
    if (lhs.is_negative && !rhs.is_negative) {
        return true;
    }

    if (!lhs.is_negative && rhs.is_negative) {
        return false;
    }

    if (lhs.numbers.size() < rhs.numbers.size()) {
        return true;
    }

    if (lhs.numbers.size() > rhs.numbers.size()) {
        return false;
    }

    for (int i = 0; i < lhs.numbers.size(); ++i) {
        if (lhs.numbers[i] < rhs.numbers[i]) {
            if (lhs.is_negative) {
                return false;
            }
            return true;
        } else if (lhs.numbers[i] > rhs.numbers[i]) {
            if (lhs.is_negative) {
                return true;
            }
            return false;
        }
    }

    return false;
}

// return -1 when lhs < rhs
// return 0 when lhs == rhs
// return 1 when lhs > rhs
int compare(myLongInt lhs, myLongInt rhs) {
    if (cmp(lhs, rhs)) {
        return -1;
    } else if (cmp(rhs, lhs)) {
        return 1;
    } else {
        return 0;
    }
}

// add leading zeroes
vector<int> add_lead_zeroes(int n, vector<int> v)
{
    vector<int> res;
    res=v;
    for(int i=0; i<n; i++){
        res.insert(res.begin(), 0);
    }
    return res;
}

vector<int> reverse_numbers(vector<int> v)
{
    vector<int> res;
    for(int i=v.size()-1; i>=0; i--){
        res.push_back(v[i]);
    }
    return res;
}

bool is_zero(myLongInt number) {
    if (number.numbers.size() == 1 && number.numbers[0] == 0) {
        return true;
    }
    return false;
}

myLongInt abs(myLongInt number)
{
    myLongInt res;
    res.numbers = number.numbers;
    res.is_negative = false;
    return res;
}

myLongInt my_minus(myLongInt a, myLongInt b);

myLongInt my_plus(myLongInt a, myLongInt b)
{
    myLongInt res;
    if(a.is_negative && !b.is_negative) {
        res=my_minus(b, abs(a));
        return res;
    }
    else if(!a.is_negative && b.is_negative){
        res=my_minus(a, abs(b));
        return res;
    }
    int diff=a.numbers.size()-b.numbers.size();
    vector<int> v1, v2;
    v1=a.numbers;
    v2=b.numbers;
    if(diff>0) {
        v2=add_lead_zeroes(diff, v2);
    }
    if(diff<0) {
        v1=add_lead_zeroes(diff*(-1), v1);
    }
    int rest=0;
    for(int i=v1.size()-1; i>=0; i--){
        int temp =v1[i]+v2[i]+rest;
        if(temp>9) {
            rest=1;
            res.numbers.push_back(temp%10);
        }
        else{
            rest=0;
            res.numbers.push_back(temp);
        }
    }
    if (rest > 0) {
        res.numbers.push_back(rest);
    }
    res.numbers=reverse_numbers(res.numbers);
    if(a.is_negative) {
        res.is_negative=true;
    }
    else{
        res.is_negative=false;
    }
    return res;
}

myLongInt my_minus(myLongInt a, myLongInt b)
{
    myLongInt res;
    if (a.is_negative && !b.is_negative){
        b.is_negative=true;
        res=my_plus(a, b);
        return res;
    }
    else if (!a.is_negative && b.is_negative){
        b.is_negative=false;
        res=my_plus(a, b);
        return res;
    }
    vector<int> v1, v2;
    v1=a.numbers;
    v2=b.numbers;
    // if flag==0 a=b;
    // if flag==1 a>b;
    // if flag==2 a<b;
    int flag=0;
    int diff=a.numbers.size()-b.numbers.size();
    if (diff>0) {
        flag=1;
        v2=add_lead_zeroes(diff, v2);
    }
    else if (diff<0) {
        flag=2;
        v1=add_lead_zeroes(diff*(-1), v1);
    }
    else {
        for(int i=0; i<v1.size(); i++) {
            if (v1[i]>v2[i]) {
                flag=1;
                break;
            }
            else if (v1[i]<v2[i]) {
                flag=2;
                break;
            }
        }
   }
    if (flag==0) {
        res.numbers.push_back(0);
        res.is_negative=false;
        return res;
    }
    vector<int> temp;
    if (flag==1) {
        for(int i=v1.size()-1; i>=0; i--){
            if(v1[i]<v2[i]) {
                v1[i-1]--;
                v1[i]+=10;
            }
            temp.push_back(v1[i]-v2[i]);
        }
    }
    else if (flag==2) {
        for(int i=v1.size()-1; i>=0; i--){
            if(v1[i]>v2[i]) {
                v2[i-1]--;
                v2[i]+=10;
            }
            temp.push_back(v2[i]-v1[i]);
        }
    }
    bool can_copy=false;
    for (int i=temp.size()-1; i>=0; i--){
        if (temp[i]>0) {
            can_copy=true;
        }
        if (can_copy) {
            res.numbers.push_back(temp[i]);
        }
    }
    if (a.is_negative && b.is_negative) {
        if(flag ==2) {
            res.is_negative=false;
        }
        else{
            res.is_negative=true;
        }
    }
    if (!a.is_negative && !b.is_negative){
        if (flag==1){
            res.is_negative=false;
        }
        else {
            res.is_negative=true;
        }
    }
    return res;
}

myLongInt my_multiplication(myLongInt a, myLongInt b)
{
/*
from https://en.wikipedia.org/wiki/Multiplication_algorithm#Example

multiply(a[1..p], b[1..q], base)   // Operands containing rightmost digits at index 1
  product = [1..p+q]               //Allocate space for result
  for b_i = 1 to q                 // for all digits in b
    carry = 0
    for a_i = 1 to p               //for all digits in a
      product[a_i + b_i - 1] += carry + a[a_i] * b[b_i]
      carry = product[a_i + b_i - 1] / base
      product[a_i + b_i - 1] = product[a_i + b_i - 1] mod base
    product[b_i + p] += carry      // last digit comes from final carry
  return product
*/
    vector<int> res(a.numbers.size()+b.numbers.size(),0);
    vector<int> va = reverse_numbers(a.numbers);
    vector<int> vb = reverse_numbers(b.numbers);
    for(int bi=0; bi<vb.size(); bi++){
        int carry=0;
        for(int ai=0; ai<va.size(); ai++){
            res[ai+bi]+=carry+va[ai]*vb[bi];
            carry=res[ai+bi]/10;
            res[ai+bi]%=10;
        }
        res[bi+va.size()]+=carry;
    }
    myLongInt result;
    while (res.size() > 1 && res.back() == 0) {
        res.pop_back();
    }
    result.numbers=reverse_numbers(res);
    result.is_negative=a.is_negative^b.is_negative;
    return result;
}

myLongInt my_division(myLongInt a, myLongInt b)
{
    if (is_zero(b)) {
        throw std::invalid_argument( "divide by zero" );
    }
    myLongInt result;
    bool flag = cmp(abs(a), abs(b));
    if (is_zero(a)) {
        result.numbers.push_back(0);
        result.is_negative=false;
        return result;
    }
    result.is_negative=a.is_negative^b.is_negative;

    vector<int> res(a.numbers.size(),0);
    myLongInt current_value;
    current_value = string2mylongint("0");
    if (!flag){
        for (int i = 0; i < a.numbers.size(); ++i) {
            current_value = my_multiplication(current_value, string2mylongint("10"));
            int index = current_value.numbers.size() - 1;
            int value = a.numbers[i];
            current_value.numbers[index] = value;

            int x = 0;
            int left_index = 0;
            int right_index = 10;

            while (left_index <= right_index) {
                int middle = (left_index + right_index) >> 1;
                myLongInt mli_middle = integer2mylongint(middle);
                myLongInt cur = my_multiplication(abs(b), mli_middle);

                if (compare(abs(cur), abs(current_value)) <= 0) {
                    x = middle;
                    left_index = middle + 1;
                } else {
                    right_index = middle - 1;
                }
            }

            res[i] = x;
            current_value = my_minus(current_value, my_multiplication(abs(b), integer2mylongint(x)));
        }
        res = reverse_numbers(res);
        while (res.size() > 0 && res.back() == 0) {
            res.pop_back();
        }
        res = reverse_numbers(res);
        result.numbers=res;
    } else {
        current_value.numbers = a.numbers;
        result.numbers.push_back(0);
    }
    vector<int> fraction(DIGIT_AFTER_COMA, 0);
    if (!is_zero(current_value)) {
        for (int i=0; i < DIGIT_AFTER_COMA; i++) {
            current_value = my_multiplication(current_value, string2mylongint("10"));
            int index = current_value.numbers.size() - 1;
            int value = 0;
            current_value.numbers[index] = value;

            int x = 0;
            int left_index = 0;
            int right_index = 10;

            while (left_index <= right_index) {
                int middle = (left_index + right_index) >> 1;
                myLongInt mli_middle = integer2mylongint(middle);
                myLongInt cur = my_multiplication(abs(b), mli_middle);

                if (compare(abs(cur), abs(current_value)) <= 0) {
                    x = middle;
                    left_index = middle + 1;
                } else {
                    right_index = middle - 1;
                }
            }

            fraction[i] = x;
            current_value = my_minus(current_value, my_multiplication(abs(b), integer2mylongint(x)));
        }
        fraction.resize(DIGIT_AFTER_COMA);
        while (fraction.size() > 1 && fraction.back() == 0) {
            fraction.pop_back();
        }
        result.fraction = fraction;
    }
    return result;
}
int main()
{
    string n1;
    string n2;
    string op;
    myLongInt li1;
    myLongInt li2;
    cout << "oprand 1: ";
    cin>>n1;
    cout << "oprand 2: ";
    cin>>n2;
    cout << "operator (only + - * /): ";
    cin>>op;
    li1 = string2mylongint(n1);
    li2 = string2mylongint(n2);
    myLongInt res;
    if (op == "+") {
        res = my_plus(li1, li2);
        println(res);
    }
    if (op == "-") {
        res = my_minus(li1, li2);
        println(res);
    }
    if (op == "*") {
        res = my_multiplication(li1, li2);
        println(res);
    }
    if (op == "/") {
        res = my_division(li1, li2);
        println(res);
    }
    return 0;
}
