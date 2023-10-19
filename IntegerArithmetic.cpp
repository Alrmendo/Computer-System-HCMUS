#include <iostream>

using namespace std;

const int ARRAY_SIZE = 8;

void output(char bin[]) 
{
    for (int i = 0; i <= ARRAY_SIZE - 1; ++i) 
    {
        cout << bin[i] << " ";
    }
}

void DecToBin(int n, char bin[])
{
    for (int i = ARRAY_SIZE - 1; i >= 0; --i)
    {
        if((n & 1) == 1)
        {
            bin[i] = '1';
        }
        else
        {
            bin[i] = '0';
        }
        n = n >> 1;
    }
}

int BinToDec(char bin[]) 
{
    int decimal = 0;
    int base = 1;

    if (bin[0] == '1')
    {
        // negative binary
        for (int i = ARRAY_SIZE - 1; i >= 0; --i) 
        {
            if (bin[i] == '1') 
            {
                decimal |= base;
            }
            else if (bin[i] != '0') 
            {
                return -1;
            }
            base = base << 1;
        }
        decimal = -((1 << ARRAY_SIZE) - decimal);
    }
    else 
    {
        // positive binary
        for (int i = ARRAY_SIZE - 1; i >= 0; --i) 
        {
            if (bin[i] == '1') 
            {
                decimal |= base;
            }
            else if (bin[i] != '0') 
            {
                return -1;
            }
            base = base << 1;
        }
    }

    cout << decimal;
    return decimal;
}

void addBinary(char bin1[], char bin2[], char result[])
{
    int carry = 0;

    for (int i = ARRAY_SIZE - 1; i >= 0; --i)
    {
        char temp = bin1[i];
        if ((temp ^ bin2[i]) ^ carry)
        {
            result[i] = '1';
        }
        else 
        {
            result[i] = '0';
        }

        if ((temp == '1' && bin2[i] == '1') || ((temp ^ bin2[i]) == 1 && carry == 1))
        {
            carry = 1;
        }
        else
        {
            carry = 0;
        }
    }
}

void notBinary(char bin[])
{
    char one[ARRAY_SIZE] = {'0', '0', '0', '0', '0', '0', '0', '1'};

    for (int i = ARRAY_SIZE - 1; i >= 0; --i)
    {
        if(bin[i] == '0')
        {
            bin[i] = '1';
        }
        else
        {
            bin[i] = '0';
        }
    }
    addBinary(bin, one, bin);
}

void subtractBinary(char bin1[], char bin2[], char result[])
{
    char temp[ARRAY_SIZE];
    for (int i = 0; i <= ARRAY_SIZE - 1; ++i)
    {
        temp[i] = bin2[i];
    }
    notBinary(temp);
    addBinary(bin1, temp, result);
}

void shiftLeft(char A[], char Q[])
{
    char temp = Q[0];
    for (int i = 0; i <= ARRAY_SIZE - 1; ++i)
    {
        if(i == ARRAY_SIZE - 1)
        {
            A[i] = temp;
        }
        else
        {
            A[i] = A[i + 1];
        }
    }

    for (int i = 0; i <= ARRAY_SIZE - 1; ++i)
    {
        if(i == ARRAY_SIZE - 1)
        {
            Q[i] = '0';
        }
        else
        {
            Q[i] = Q[i + 1];
        }
    }
}

void shiftRight(char A[], char Q1[])
{
    char temp = A[ARRAY_SIZE - 1], temp1 = A[0];
    
    for (int i = ARRAY_SIZE - 1; i >= 0; --i)
    {
        if(i == 0)
        {
            A[i] = '0';
        }
        else
        {
            A[i] = A[i - 1];
        }
    }

    for (int i = ARRAY_SIZE; i >= 0; --i)
    {
        if(i == 0)
        {
            Q1[i] = temp;
        }
        else
        {
            Q1[i] = Q1[i - 1];
        }
    }
    A[0] = temp1;
}

void copyArray(char bin[], char copy[])
{
    for(int i = 0; i <= ARRAY_SIZE - 1; ++i)
    {
        copy[i] = bin[i];
    }
}

void multipleBinary(char bin1[], char bin2[], char result[])
{
    char A[ARRAY_SIZE] = {'0', '0', '0', '0', '0', '0', '0', '0'};
    int count = ARRAY_SIZE;
    char Q1[ARRAY_SIZE + 1] = {'0', '0', '0', '0', '0', '0', '0', '0', '0'};
    char M[ARRAY_SIZE] = {'0', '0', '0', '0', '0', '0', '0', '0'};

    copyArray(bin1, Q1);
    copyArray(bin2, M);

    while(count > 0)
    {
        if(Q1[ARRAY_SIZE - 1] == '1' && Q1[ARRAY_SIZE] == '0')
        {
            subtractBinary(A, M, A);
        }
        else if(Q1[ARRAY_SIZE - 1] == '0' && Q1[ARRAY_SIZE] == '1')
        {
            addBinary(A, M, A);
        }
        shiftRight(A, Q1);
        --count;
    }
    copyArray(Q1, result);
}

void divideBinary(char bin1[], char bin2[], char result[])
{
    char A[ARRAY_SIZE] = {'0', '0', '0', '0', '0', '0', '0', '0'};
    int count = ARRAY_SIZE;
    char Q[ARRAY_SIZE] = {'0', '0', '0', '0', '0', '0', '0', '0'};
    char M[ARRAY_SIZE] = {'0', '0', '0', '0', '0', '0', '0', '0'};

    copyArray(bin1, Q);
    copyArray(bin2, M);

    if(Q[0] == '1')
    {
        notBinary(Q);
    }
    if(M[0] == '1')
    {
        notBinary(M);
    }

    while(count > 0)
    {
        shiftLeft(A, Q);
        subtractBinary(A, M, A);
        if(A[0] == '1')
        {
            Q[ARRAY_SIZE - 1] = '0';
            addBinary(A, M, A);
        }
        else
        {
            Q[ARRAY_SIZE - 1] = '1';
        }
        --count;
    }
    if(bin1[0] ^ bin2[0])
    {
        notBinary(Q);
    }
    copyArray(Q, result);
}

void modBinary(char bin1[], char bin2[], char result[])
{
    char A[ARRAY_SIZE] = {'0', '0', '0', '0', '0', '0', '0', '0'};
    int count = ARRAY_SIZE;
    char Q[ARRAY_SIZE] = {'0', '0', '0', '0', '0', '0', '0', '0'};
    char M[ARRAY_SIZE] = {'0', '0', '0', '0', '0', '0', '0', '0'};

    copyArray(bin1, Q);
    copyArray(bin2, M);

    if(Q[0] == '1')
    {
        notBinary(Q);
    }
    if(M[0] == '1')
    {
        notBinary(M);
    }

    while(count > 0)
    {
        shiftLeft(A, Q);
        subtractBinary(A, M, A);
        if(A[0] == '1')
        {
            Q[ARRAY_SIZE - 1] = '0';
            addBinary(A, M, A);
        }
        else
        {
            Q[ARRAY_SIZE - 1] = '1';
        }
        --count;
    }
    if(bin1[0] ^ bin2[0])
    {
        notBinary(A);
    }
    copyArray(A, result);
}

int main ()
{
    char arrA[ARRAY_SIZE], arrB[ARRAY_SIZE];
    char resultAdd[ARRAY_SIZE] = {'0', '0', '0', '0', '0', '0', '0', '0'};
    char resultSub[ARRAY_SIZE] = {'0', '0', '0', '0', '0', '0', '0', '0'};
    char resultMul[ARRAY_SIZE] = {'0', '0', '0', '0', '0', '0', '0', '0'};
    char resultDiv[ARRAY_SIZE] = {'0', '0', '0', '0', '0', '0', '0', '0'};
    char resultMod[ARRAY_SIZE] = {'0', '0', '0', '0', '0', '0', '0', '0'};

    int a, b;

    cout << "\nInput A (Decimal): ";
    cin >> a;

    cout << "\nInput B (Decimal): ";
    cin >> b;

    DecToBin(a, arrA);
    DecToBin(b, arrB);

    cout << "\nA (Binary): ";
    output(arrA);

    cout << "\nB (Binary): ";
    output(arrB);

    cout << "\nA + B (Binary): ";
    addBinary(arrA, arrB, resultAdd);
    output(resultAdd);

    cout << "\nA + B (Decimal): ";
    BinToDec(resultAdd);

    cout << "\nA - B (Binary): ";
    subtractBinary(arrA, arrB, resultSub);
    output(resultSub);

    cout << "\nA - B (Decimal): ";
    BinToDec(resultSub);

    cout << "\nA * B (Binary): ";
    multipleBinary(arrA, arrB, resultMul);
    output(resultMul);

    cout << "\nA * B (Decimal): ";
    BinToDec(resultMul);

    cout << "\nA / B (Binary): ";
    divideBinary(arrA, arrB, resultDiv);
    output(resultDiv);

    cout << "\nA / B (Decimal): ";
    BinToDec(resultDiv);

    cout << "\nA % B (Binary): ";
    modBinary(arrA, arrB, resultMod);
    output(resultMod);

    cout << "\nA % B (Decimal): ";
    BinToDec(resultMod);

    return 0;
}