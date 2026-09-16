#include <iostream>

using namespace std;

bool isValid(long long number);
int sumOfDoubleEvenPlace(long long number);
int getDigit(int number);
int sumOfOddPlace(long long number);
bool prefixMatched(long long number, int d);
int getSize(long long d);
long long getPrefix(long long number, int k);

int main() {
    long long creditCardNumber;
    
    cout << "Enter a credit card number as a long integer: ";
    cin >> creditCardNumber;
    
    if (isValid(creditCardNumber)) {
        cout << creditCardNumber << " is valid" << endl;
    } else {
        cout << creditCardNumber << " is invalid" << endl;
    }
    
    return 0;
}

bool isValid(long long number) {
    int size = getSize(number);
    if (size < 13 || size > 16) {
        return false;
    }
    
    if (!prefixMatched(number, 4) && 
        !prefixMatched(number, 5) && 
        !prefixMatched(number, 37) && 
        !prefixMatched(number, 6)) {
        return false;
    }
    
    int totalSum = sumOfDoubleEvenPlace(number) + sumOfOddPlace(number);
    return (totalSum % 10 == 0);
}

int sumOfDoubleEvenPlace(long long number) {
    int sum = 0;
    number /= 10;
    
    while (number > 0) {
        int digit = number % 10;
        sum += getDigit(digit * 2);
        number /= 100; 
    }
    return sum;
}

int getDigit(int number) {
    if (number < 10) {
        return number;
    }
    return (number / 10) + (number % 10);
}

int sumOfOddPlace(long long number) {
    int sum = 0;
    
    while (number > 0) {
        sum += number % 10;
        number /= 100;
    }
    return sum;
}

bool prefixMatched(long long number, int d) {
    return getPrefix(number, getSize(d)) == d;
}

int getSize(long long d) {
    int count = 0;
    while (d > 0) {
        d /= 10;
        count++;
    }
    return count;
}

long long getPrefix(long long number, int k) {
    int size = getSize(number);
    if (size < k) {
        return number;
    }
    
    int diff = size - k;
    while (diff > 0) {
        number /= 10;
        diff--;
    }
    return number;
}