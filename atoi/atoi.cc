#include <iostream>
#include <cstdlib>
#include <cctype>

// Function Signature
// For invalid input, return 0
int atoi (const char * str);

using namespace std;

bool IsValid(const char * str);
int main()
{
    // Valid Input
    cout << atoi("0") << endl;
    cout << atoi("-0") << endl;
    cout << atoi("-1") << endl;
    cout << atoi("1") << endl;
    cout << atoi("1402") << endl;
    cout << atoi("-235") << endl;
    cout << atoi("2147483647") << endl;
    cout << atoi("-2147483648") << endl;

    // Invalid Input
    cout << atoi("-2147483649") << endl;
    cout << atoi("abc") << endl;
    cout << atoi(" 0") << endl;
}

bool IsNegative(const char a)
{
    if (a == '-')
    {
        return true;
    }

    return false;
}

bool IsValid(const char * str)
{
    // TODO: Out of Range?


    // Check if empty string
    if(str[0] == '\0')
    {
        return false;
    }

    bool isNegative = IsNegative(str[0]);

    int pos = isNegative ? 1 : 0;

    while (str[pos] != '\0')
    {
        if (!isdigit(str[pos]))
        {
            return false;
        }
        
        ++pos;
    }

    return true;
}

int atoi (const char * str)
{
    // Validate Input
    // Is all digits
    if (!IsValid(str))
    {
        return 0;
    }

    bool isNegative = IsNegative(str[0]);
    int end = isNegative ? 1 : 0;
    int pos = 0;

    while (str[pos] != '\0')
    {
        ++pos;
    }

    int sum = 0;
    int multiplier = 1;

    while (pos != end)
    {
        sum += (str[pos-1] - '0') * multiplier;
        multiplier *= 10;
        --pos;
    }

    if (isNegative)
    {
        sum *= -1;
    }

    return sum;
}

