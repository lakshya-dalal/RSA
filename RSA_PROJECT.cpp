#include<bits/stdc++.h>
using namespace std;
#define unsigned long long int int;

//Converts decimal to Bearcatii (base27)
void toBearcatii(int num, string &text) {
    int unitsDigit, num_ = num;
    int i = 0, length;
    while (num_ > 0) {
        num_ /= 27;
        i++;
    }
    length = i;
    for (int i = length - 1; i >= 0; i--) {
        unitsDigit = num % 27;
        if (unitsDigit == 0)
            text[i] = (char) 32;
        else {
            unitsDigit += 64;
            text[i] = (char) unitsDigit;
        }
        num /= 27;
    }

    for (int i = 0; i < length; i ++)
        cout << text[i];
}

//Computes gcd using euler's extended gcd method
int extGCD(int a, int b, int &s, int &t) {

    if (b == 0) {
        s = 1;
        t = 0;
        return a;
    }
    int s_, t_, result;
    result = extGCD(b, a % b, s_, t_);
    t = s_ - (a / b) * t_;
    s = t_;

    return result;
}

//Computes (a * b) mod c
int modularMul(int a, int b, int c)
{
    int res = 0;
    a = a % c;
    while (b > 0)
    {
        if (b % 2 == 1)
            res = (res + a) % c;
        a = (a * 2) % c;
        b /= 2;
    }
    return res % c;
}

//Does modular exponentiation
int modulo(int a, int b, int n) {
    int x = 1, y = a;
    while (b > 0) {
        if (b % 2 == 1) {
            x = (x * y) % n; // multiplying with base
        }
        y = (y * y) % n; // squaring the base
        b /= 2;
    }
    return x % n;
}

bool isprime(int n) {
    int q = sqrt(n);
    for (int i = 2; i <= q; i++)
    {
        if (n % i == 0) {return false;}
    }

    return true;
}

int main() {

    int p, q, n, phi, e, d, decimal = 0, encryptednum, decrptednum, temp;
    string M, C, P;
    int messageLength, flag;

    //Generating primes p and q randomly
    do {
        p = rand() % 1000000; // restricting random number to 999999 to prevent memory overflow
    } while (!isprime(p));

    do {
        q = rand() % 1000000;
    } while (!isprime(q));

    //Computing phi and n
    n = p * q;
    phi = (p - 1) * (q - 1);

    //Getting the encryption key
    do {
        cout << "Enter the encryption key, e: ";
        cin >> e;
    } while (extGCD(e, phi, d, temp) != 1 || e == 1);

    //Adjusting d if it is negative
    if (d < 0)
        d += phi;

    cout << "p: " << p << " || q: " << q << " || n: " << n << " || phi: " << phi << " || private key, d: " << d << endl;
    //Reading the message
    flag = 1;
    cout << "Enter the message (only a-z/A-Z/<space>, lower case will be converted to upper): ";
    cin.get();
    getline(cin, M);

    messageLength = M.length();

    //Checking for validity
    for (int i = 0; i < messageLength; i++) {
        if (((int)M[i] < 32) || ( ((int)M[i] > 32) && (((int)M[i] < 65)) ) || ( ((int)M[i] > 90) && (((int)M[i] < 97)) ) || (((int)M[i] > 122)))
            flag = 0;
        else
            flag = 1;
    }

    //Converting text to upper
    for (int i = 0; i < messageLength; i++)
        M[i] = toupper(M[i]);

    if (flag == 0) {
        cout << "Invalid input. Try a-z|A-Z|<space>\nExiting program...";
        exit(1);
    }

    //Text to decimal
    for (int i = messageLength - 1, j = 0; i >= 0; i--, j++) {
        if (M[i] == ' ')
            continue;
        decimal = decimal + ((int)(M[i]) - 64) * pow(27, j);
    }

    cout << "Message in decimal: " << decimal << endl;
    if (decimal > n) {
        cout << "Message in decimal exceeds n, message too long to encrypt. Exiting program..." << endl;
        exit(1);
    }
    else if (decimal == 0) {
        cout << "Message in decimal too large for unsigned long long int, enter a smaller text." << endl;
        exit(1);
    }

    encryptednum = modulo(decimal, e, n);
    cout << "Encrypted number (" << decimal << "^" << e << " mod " << n << "): " << encryptednum << endl;
    cout << "Encrypted text, C: ";
    toBearcatii(encryptednum, C);
    cout << endl;
    decrptednum = modulo(encryptednum, d, n);
    if (decrptednum != decimal) {
        cout << "Memory overflowed, encryption failed! Exiting program..." << endl;
        exit(1);
    }
    cout << "Decrypted number (" << encryptednum << "^" << d << " mod " << n << "): " << decrptednum << endl;
    cout << "Decrypted text, P: ";
    toBearcatii(decrptednum, P);
    cout << endl;
    cout << "Message, M: " << M << endl;

    return 0;
}

/*SAMPLE OUTPUT:
Enter the encryption key, e: 2001
p: 14771 || q: 25667 || n: 379127257 || phi: 379086820 || private key, d: 96429381
Enter the message (only a-z/A-Z/<space>, lower case will be converted to upper): DTU
Message in decimal: 3477
Encrypted number (3477^2001 mod 379127257): 200136838
Encrypted text, C: MYP CM
Decrypted number (200136838^96429381 mod 379127257): 3477
Decrypted text, P: DTU
Message, M: DTU

--------------------------------
Process exited after 10.13 seconds with return value 0
Press any key to continue . . .
*/