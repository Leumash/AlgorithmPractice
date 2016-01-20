#include <iostream>
#include <cstdlib>

// From www.cplusplus.com, the function signature is:
// char *  itoa ( int value, char * str, int base );

// Maximum value of an int for 32-bit is 2147483647
// Minimum value of an int for 32-bit is -2147483648
// So there's 11 characters, but you need the '\0'

using namespace std;

char* itoa(int value, char* str);
char itoc(int value);

int main()
{
    char buffer[12];
    cout << itoa(0, buffer) << endl;
    cout << itoa(-0, buffer) << endl;
    cout << itoa(1, buffer) << endl;
    cout << itoa(-1, buffer) << endl;
    cout << itoa(2147483647, buffer) << endl;
    cout << itoa(-2147483648, buffer) << endl;
    cout << itoa(74004, buffer) << endl;
    cout << itoa(-10734, buffer) << endl;
}

char itoc(int value)
{
    return value + '0';
}

char* itoa(int value, char* str)
{
    // Assume that str is sufficiently large enough
    // Assume int is 32-bit integer

    if (value == 0)     // Special Case
    {
        str[0] = '0';
        str[1] = '\0';
        return str;
    }

    if (value == -2147483648)   // Special Case
    {
        str[0] = '-';
        str[1] = '2';
        str[2] = '1';
        str[3] = '4';
        str[4] = '7';
        str[5] = '4';
        str[6] = '8';
        str[7] = '3';
        str[8] = '6';
        str[9] = '4';
        str[10] = '8';
        str[11] = '\0';
        return str;
    }

    bool isNegative = value < 0;
    int fillArrayPos = 0 + (isNegative ? 1 : 0);
    bool startedFilling = false;

    if (isNegative)
    {
        value *= -1;
    }

    for (int placeValue = 1000000000; placeValue > 0; placeValue /= 10)
    {
        if ( value / placeValue > 0)
        {
            startedFilling = true;
        }

        if (startedFilling)
        {
            str[fillArrayPos] = itoc(value / placeValue);
            value %= placeValue;
            ++fillArrayPos;
        }
    }

    if (isNegative)
    {
        str[0] = '-';
    }

    str[fillArrayPos] = '\0';

    return str;
}

