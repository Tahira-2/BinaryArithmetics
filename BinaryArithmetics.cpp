#include <iostream>
#include <vector>
#include <string>
#include <tuple>
using namespace std;
/* Nme: n-bit Binary Adder-Subtractor
       :it can add or subtract two binary digits using addition only.

OPERATIONS: sum = A XOR B XOR C_in
                = sum1 XOR C_in (sum1 = A XOR B)
        carry (C_out) = A.B OR C_in.sum1
 variables:
    A = first binary
    B = second binary
    c_in = input carry bit (first one is 0, then it changes inside the function)

  steps: it reads the input as string since string is easier to handle and split.
    for addition:
    1.add the right most digits
    2.store the sum inside a vector called "list_sum" and pass the carry to the next full_adder (or next two digits)
    3.this continues to the left-most digits.
    4.at last, print the final sun & carry-bit

    for subtraction:
    1.to perform 2's complement, change the size of num2 by adding least number of necessary zeros to the left.
    2.take the negative of num2 using 2's complement, and the add with num1 to get (num1-num2)
*/

//this function creates XOR gate:  (A OR B) AND NOT (A AND B)
bool get_xor(bool A, bool B) {
    bool xor_gate;

    xor_gate = (A || B) && !(A && B);

    return xor_gate;
}

// this function returns bit by bit summation 
bool get_bitwise_sum(bool A, bool B, bool C_in) {
    bool sum1, sum_final;

    sum1 = get_xor(A, B);
    sum_final = get_xor(sum1, C_in);

    return sum_final;
}

// this function returns the carry digit
bool get_carry(bool A, bool B, bool C_in) {
    bool sum1, carry;

    sum1 = get_xor(A, B);
    carry = (A && B) || (C_in && sum1);

    return carry;
}

//this function modifies the number's size
/*1.  it takes a number, and the size it will be changed to
2. addNumzeros = calculates how many '0' needed to gain the certain length
3. add the zerros to the left of the number
*/
void fixNumBit(string& number, int size)
{
    int numBits;
    int addNumZeros = size - number.size();

    for (int i = 0; i < addNumZeros; i++)
    {
        number = "0" + number;
    }
}

//this function gets the final sum and pass it to main function when called
pair<string, string> get_final_sum(string num1, string num2)
{
    int A, B, C_in = 0;  //for the right most digits, the initial carryIn is 0
    //store the bit-wise sum inside a vector
    vector<int> list_sum;

    //determine new size
    int newSize;
    if (num1.size() > num2.size())
        newSize = num1.size();
    else
        newSize = num2.size();
    //fix the number of bits in the numbers for easier calculation
    fixNumBit(num1, newSize);
    fixNumBit(num1, newSize);
  
    //s is to store the sums inside the list_sum vector
    //start from right most digits
    for (int i = (newSize-1); i >= 0; i--)
    {
        // subtract '0' to get integer value
        A = num1[i] - '0';
        B = num2[i] - '0';

        int s = get_bitwise_sum(A, B, C_in);
        //storing the sums inside a list.
        list_sum.push_back(s);   //NOTE: the sums are stored reversedly 
        C_in = get_carry(A, B, C_in);   //pass this "carry bit" to the next F/A with the digits
    }
    string C_out = to_string(C_in);
    //this loop put the sum back as a string from the vector
    string sum = "";
    for (int i : list_sum)
    {
        //this reverse the sum again, ultimately writes it correctly
        sum = to_string(i) + sum;  
    }
    return make_pair(sum, C_out);
}

//it gets the 2's complement of a number
string two_s_complement(string num)
{
    //getting 1's complement by interchanging the position of 0 and 1
    string complement_1 = "";
    for (char i : num)
    {
        if (i == '0')
            complement_1 += '1';
        else complement_1 += '0';
    }

    //get the needed size for "1" to get 2's complement
    string oneToAdd = "1";
    fixNumBit(oneToAdd, num.size());
    
    //get 2's complement by adding 1 to the complement_1
    string complement_2, carryBit;
    tie(complement_2, carryBit) = get_final_sum(complement_1, oneToAdd);   //the function returns the "sum" in "string"
    
    //ignore the carryBit
    return complement_2;
}

//calculate the subtraction
string get_subtraction(string num1, string num2)
{
    int currentSize;
    if (num1.size() > num2.size())
        currentSize = num1.size();
    else
        currentSize = num2.size();
    
    //determine the needed size
    int new_size;

    if (currentSize < 2)
        new_size = 2;
    else if (currentSize < 4)
        new_size = 4;        
    else if (currentSize < 8)
        new_size = 8;
    else if (currentSize < 16)
        new_size = 16;
    else if (currentSize < 32)
        new_size = 32;
    else if (currentSize < 64)
        new_size = 64;
    else if (currentSize < 128)
        new_size = 128;

    //fix the size of the numbers
    fixNumBit(num1, new_size);
    fixNumBit(num2, new_size);
            
    //get 2's complement of the second number "num2"
    string negativeNum2 = two_s_complement(num2);

    //Add first number to the negative second number
    //num1 + 2's complement of num2
    string result, carryBit;
    tie(result, carryBit) = get_final_sum(num1, negativeNum2);

    return result;
}

//multipllication
string multiply(string num1, string num2)
{
    string temp_carry;
    string product = "0"; //initialize the product as 0
    //1.loop through the second number
    //2.multiply num1 by each bit in num2 from right to left,
    //3.add the results in product
    //4.add '0' add the right of num1 after every bit in num2 to change it's positional value by 2(base)
    for (int i = num2.size() - 1; i >= 0; i--)
    {
        if (num2[i] == '1')
        {
            //get_final_sum function gets the sum and carry separetely
            tie(product, temp_carry) = get_final_sum(product, num1);
            //now add the carry befor the product for correct answer
            product = temp_carry + product;
        }
        num1 = num1 + '0';
    }
    return product;

}

///power function
string power(string num1, string num2)
{
    string result = "1";

    int num2_deg = 0;
    for (char bit : num2)
    {
        num2_deg = num2_deg * 2 + (bit - '0');  // polynomial evaluation
    }
    for (int i = 1; i <= num2_deg; i++)
    {
        result = multiply(result, num1);
    }
    return result;
}

//Division & remainder
/*
* It follows the shift-and-subtract logic. 
* Steps: 1. Treat the input strings like streams of bits. 
2.Start by initializing remainder with just the first bit of the dividend.
3.Loop through the dividend, bit by bit. 
4.In each iteration treat the remainder as minuend and try subtracting num2 from it.
5.Check the sign bit (the first character) of the result (called subRemainder here).
    If it’s '0' (Positive): It means the divisor 'fits.' So, append '1' to quotient string (result)
        and update the remainder to this new result.
    If it’s '1' (Negative): It means the divisor was bigger. So append '0' quotient string (result)
        and append the next bit from dividend to the remainder"
6.Finnaly, return the result based on the operation user choose 
*/
string divide(string n1, string n2, char operation)
{
    string result = "", subRemainder;
    string remainder = string(1, n1.at(0));
    //loop through each digit of the first number
    for (int i = 0; i < n1.size(); i++)
    {
        subRemainder = get_subtraction(remainder, n2);
  
        //first bit 0 means positive (subtraction possible)
        if (subRemainder.at(0) == '0')
        {
            result += '1';
            if ((i + 1) < n1.size())
                remainder = subRemainder + n1.at(i + 1);
            else
                remainder = subRemainder;
        }
        //first bit  1 means negative (subtraction not possible)
        else
        {
            result += '0';
            if ((i + 1) < n1.size())
                remainder += n1.at(i + 1);
            else
                remainder = remainder;
        }
    }
    //return the desired answer
    if (operation == '/')
        return result;
    else if (operation == '%')
        return remainder;
}

// this is the main function that will print the sum and carry of three binary digit, in short it will work as an actual full adder
int main()
{
    string num1, num2;
    cout << "Enter two binary numbers separated by space: ";
    cin >> num1 >> num2;
    //input validation
    for (char i : num1)
    {
        if (i != '0' and i != '1')
        {
            cout << "Invalid Input: Please enter binary numbers only\Try again" << endl;
            cout << "Try again" << endl;
            return -1;
        }
    }
    for (char i : num2)
    {
        if (i != '0' and i != '1')
        {
            cout << "Invalid Input: Please enter binary numbers only" << endl;
            cout << "Try again" << endl;
            return -2;
        }
    }

    char operation;
    cout << "Enter operation (+, -, *, ^, /, %): ";
    cin >> operation;

    while (true)     //loop to ask the user for valid operation until they provide one
    {
        if (operation == '+')
        {
            string Sum, carry;
            tie(Sum, carry) = get_final_sum(num1, num2);  //function returs the sum in string
            //int Sum = stoi(sSum);

            cout << "The carry is = " << carry << endl;           //NOTE: this carry is empty for some reason, fix it
            cout << "The sum is = " << Sum << endl;
            break;
        }
        else if (operation == '-')
        {
            string Sub = get_subtraction(num1, num2);     //function returns the result in string
            
            //print as integer to ignore the leading zeros
            cout << "The subtraction is = " << stoi(Sub) << endl;
            break;
        }
        else if (operation == '*')
        {
            string product = multiply(num1, num2);
            cout << "The product is = " << stoi(product) << endl;
            break;
        }
        else if (operation == '^')
        {
            string result = power(num1, num2);
            cout << num1 << " to the " << num2 << "th power = " << stoi(result) << endl;
            break;
        }
        else if (operation == '/' || operation == '%')
        {
            if (stoi(num2) == 0)
            {
                cout << "division by zero(0) is mathemetically illegal." << endl;
                cout << "Enter a valid expression or number to procceed." << endl;
                return -1;
            }
            string divisionResult = divide(num1, num2, operation);
            cout << num1 << " " << operation << " " << num2 << " = " << stoi(divisionResult) << endl;
            break;
        }
        else
        {
            cout << "\nPlease select an operation";
            cin >> operation;
        }
    }
}
