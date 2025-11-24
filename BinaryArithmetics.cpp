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

//this function modifies the number's size to the right number of bit so successfully operate 2's complement
/*1.  it takes the second number, it's size, and the size it will be changed to
2. added_zero = calculates how many '0' needed to gain the certain length
3. add the zerros to the left of num2
4. having '1' to the same length as num2, to later easily use in 2's complement*/
pair<string, string> fix_bit(string num2, int num_size, int new_size)
{
    int added_zero = new_size - num_size;
    num2 = string(added_zero, '0') + num2;
    string add_1 = string(new_size - 1, '0') + '1';

    return make_pair(num2, add_1);
}

//fix the size for both bit
pair<string, string> equal_size(string equalBit_n1, string equalBit_n2)
{
    int size;
    //assigning size to the max size
    if (equalBit_n1.size() > equalBit_n2.size())
    {
        size = equalBit_n1.size();
        //now fix the size by additing 0 to the left
        while (equalBit_n2.size() < size)
        {
            equalBit_n2 = '0' + equalBit_n2;
        }
    }
    else
    {
        size = equalBit_n2.size();
        //now fix the size by additing 0 to the left
        while (equalBit_n1.size() < size)
        {
            equalBit_n1 = '0' + equalBit_n1;
        }
    }
    return make_pair(equalBit_n1, equalBit_n2);
}

//this function gets the final sum and pass it to main function when called
pair<string, string> get_final_sum(string num1, string num2)
{
    int A, B, C_in = 0;  //fo r the eftmost digits, the intial carry is 0
    vector<int> list_sum;


    string equalBit_n1, equalBit_n2;
    tie(equalBit_n1, equalBit_n2) = equal_size(num1, num2);
    //s is to store the sums inside the list_sum vector
    for (int i = (equalBit_n1.size() - 1); i >= 0; i--)
    {
        A = equalBit_n1[i] - '0';    // subtract '0' to get convert string to integer
        B = equalBit_n2[i] - '0';

        int s = get_bitwise_sum(A, B, C_in);
        list_sum.push_back(s); //storing the sums inside a list.  NOTE: the bits are stored reversedly 

        C_in = get_carry(A, B, C_in);   //to passe "carry bit" and add them with the digits in the next place
    }
    string C_out = to_string(C_in);
    //cout << "\nThe carry is: " << C_out << endl;
    //this loop the sum in one variable from the vector
    string sum = "";
    for (int i : list_sum)
    {
        sum = to_string(i) + sum;  //this reverse the sum again, ultimately writes it correctly
    }
    return make_pair(sum, C_out);
}

//this function modifies the number's size to the right number of bit so successfully operate 2's complement
/*1.  it takes the second number, it's size, and the size it will be changed to
2. added_zero = calculates how many '0' needed to gain the certain length
3. add the zerros to the left of num2
4. having '1' to the same length as num2, to later easily use in 2's complement*/
string two_s_complement(string num2)
{
    int num_size = num2.size();
    int new_size;
    string fixed_num2, Add_1;
    if (num_size < 2)
    {
        new_size = 2;
        tie(fixed_num2, Add_1) = fix_bit(num2, num_size, new_size);
    }
    else if (num_size < 4) {
        new_size = 4;
        tie(fixed_num2, Add_1) = fix_bit(num2, num_size, new_size);
    }
    else if (num_size < 8) {
        new_size = 8;
        tie(fixed_num2, Add_1) = fix_bit(num2, num_size, new_size);
    }
    else if (num_size < 16) {
        new_size = 16;
        tie(fixed_num2, Add_1) = fix_bit(num2, num_size, new_size);
    }
    else if (num_size < 32) {
        new_size = 32;
        tie(fixed_num2, Add_1) = fix_bit(num2, num_size, new_size);
    }
    else if (num_size < 64) {
        new_size = 64;
        tie(fixed_num2, Add_1) = fix_bit(num2, num_size, new_size);
    }
    else if (num_size < 128) {
        new_size = 128;
        tie(fixed_num2, Add_1) = fix_bit(num2, num_size, new_size);
    }

    //getting 1's complement by interchanging the position of 0 and 1
    string complement_1 = "";
    for (char i : fixed_num2)
    {
        if (i == '0')
            complement_1 += '1';
        else complement_1 += '0';
    }
    //calculate 2's complement now by adding 1 (Add_1) with complement_1
    string complement_2, carry;
    tie(complement_2, carry) = get_final_sum(complement_1, Add_1);   //the function returns the "sum" in "string"
    //though carry isn't needed here, the functions returns 2 variables.
    return complement_2;
}

//calculate the subtraction
string get_subtraction(string num1, string num2)
{
    string Nbit_num1, Nbit_num2;
    

    Nbit_num2 = two_s_complement(num2);
    tie(Nbit_num1, Nbit_num2) = equal_size(num1, Nbit_num2);   //also fixing numer1's bit number to make summation easier.
    //this function takes 1.the number, 2.it's size, 3. the size it will changed to
    string result, carry;
    tie(result, carry) = get_final_sum(Nbit_num1, Nbit_num2);

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
            tie(product, temp_carry) = get_final_sum(product, num1);
            product = temp_carry + product;  //get_final_sum function gets the sum and carry separetely, so here we need to add it befor the product to avoid miscalculation
        }
        num1 = num1 + '0';
    }
    return product;

}

///power function
string power(string num1, string num2)
{
    string result = "1";

    int num2_dec = 0;
    for (char bit : num2)
    {
        num2_dec = num2_dec * 2 + (bit - '0');  // polynomial evaluation
    }
    for (int i = 1; i <= num2_dec; i++)
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
        and append the next bit from dividend to the remain"
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
        //first bit  1 means negative (subtraction not possible)
        if (subRemainder.at(0) == '0')
        {
            result += '1';
            if ((i + 1) < n1.size())
                remainder = subRemainder + n1.at(i + 1);
            else
                remainder = subRemainder;
        }
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
            //int Sub = stoi(sSub); 

            cout << "The subtraction is = " << Sub << endl;
            break;
        }
        else if (operation == '*')
        {
            string product = multiply(num1, num2);
            cout << "The product is = " << product << endl;
            break;
        }
        else if (operation == '^')
        {
            string result = power(num1, num2);
            cout << num1 << " to the " << num2 << "th power = " << result << endl;
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
            cout << num1 << " " << operation << " " << num2 << " = " << divisionResult << endl;
            break;
        }
        else
        {
            cout << "\nPlease select an operation";
            cin >> operation;
        }
    }
}