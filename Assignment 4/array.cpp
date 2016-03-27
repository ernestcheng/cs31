#include <iostream>
#include <string>
#include <cassert>

using namespace std;

int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos);
int countRuns(const string a[], int n);
int flip(string a[], int n);
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int split(string a[], int n, string splitter);

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main()
{
    string h[7] = { "bernie", "hillary", "donald", "jeb", "", "carly", "ben" };
    assert(lookup(h, 7, "carly") == 5);
    assert(lookup(h, 7, "donald") == 2);
    assert(lookup(h, 2, "donald") == -1);
    assert(lookup(h, 0, "bernie") == -1);
    assert(lookup(h, -2, "bernie") == -1);
    assert(positionOfMax(h, 7) == 3);
    assert(positionOfMax(h, 0) == -1);
    
    string g[4] = { "bernie", "hillary", "jeb", "carly" };
    assert(differ(h, 4, g, 4) == 2);
    assert(appendToAll(g, 4, "?") == 4 && g[0] == "bernie?" && g[3] == "carly?");
    assert(appendToAll(g, 0, "?") == 0 && g[0] == "bernie?" && g[3] == "carly?");
    assert(rotateLeft(g, 4, 1) == 1 && g[1] == "jeb?" && g[3] == "hillary?");
    assert(rotateLeft(g, 3, 0) == 0 && g[0] == "jeb?" && g[3] == "hillary?" && g[2] == "bernie?");
    assert(rotateLeft(g, 0, 0) == -1 && g[0] == "jeb?" && g[3] == "hillary?" && g[2] == "bernie?");
    
    string e[4] = { "donald", "jeb", "", "carly" };
    assert(subsequence(h, 7, e, 4) == 2);
    assert(subsequence(h, 5, e, 4) == -1);
    assert(subsequence(h, 7, e, 1) == 2);
    assert(subsequence(h, 7, e, 0) == 0);
    assert(subsequence(h, 0, e, 0) == -1);
    assert(subsequence(e, 4, h, 7) == -1);
    assert(differ(h, 4, e, 4) == 0);
    assert(differ(h, 7, e, 0) == 0);
    assert(differ(h, 0, e, 0) == 0);
    
    string d[5] = { "hillary", "hillary", "hillary", "ben", "ben" };
    assert(countRuns(d, 5) == 2);
    
    string y[8] = { "bernie", "bernie", "bernie", "donald", "donald", "jeb", "carly", "carly" };
    assert(countRuns(y, 8) == 4);
    assert(countRuns(y, 0) == 0);
    assert(flip(y, 6) == 6 && y[0] == "jeb" && y[2] == "donald" && y[7] == "carly");
    
    string f[3] = { "jeb", "donald", "marco" };
    assert(lookupAny(h, 7, f, 3) == 2);
    assert(lookupAny(h, 7, f, 0) == -1);
    assert(lookupAny(h, 0, f, 3) == -1);
    assert(lookupAny(h, 0, f, 0) == -1);
    assert(flip(f, 3) == 3 && f[0] == "marco" && f[2] == "jeb");
    assert(flip(f, 0) == 0 && f[0] == "marco" && f[2] == "jeb");
    
    assert(split(h, 7, "carly") == 3);
    
    string z1[7] = { "bernie", "hillary", "george", "barack", "lincoln", "marco", "donald" };
    assert(split(z1, 5, "hillary") == 3 && z1[3] == "hillary" && z1[5] == "marco");
    string z2[7] = { "bernie", "hillary", "george", "barack", "lincoln", "marco", "donald" };
    assert(split(z2, 7, "zed") == 7 && z2[3] == "george" && z2[5] == "lincoln");
    assert(split(z2, 7, "aaa") == 0 && z2[3] == "george" && z2[5] == "lincoln");
    string z3[7] = { "bernie", "hillary", "george", "barack", "lincoln", "marco", "donald" };
    assert(split(z3, 0, "hillary") == 0 && z3[1] == "hillary" && z3[6] == "donald");
    
    
    cout << "All tests succeeded." << endl;
}

int appendToAll(string a[], int n, string value)
{
    if (n < 0)
        return -1;
    for (int i = 0; i < n; i++) // Loop through strings in array.
        a[i] += value; // Append string for each string.
    return n;
}

int lookup(const string a[], int n, string target)
{
    if (n < 0)
        return -1;
    for (int i = 0; i < n; i++) // Loop through strings in array.
        if (a[i] == target) // Check whether string matches target string.
            return i; // Return position of string which matches.
    return -1;
}

int positionOfMax(const string a[], int n)
{
    if (n <= 0)
        return -1;
    string currentLargest = a[0]; // Define current largest string.
    int currentLargestPosition = 0; // Define position of current largest string.
    for (int i = 1; i < n; i++) // Loop through strings in array.
        if (a[i] > currentLargest)
        {
            currentLargest = a[i]; // If string is larger than current largest, change the string.
            currentLargestPosition = i; // If string is larger than current largest, change the position.
        }
    return currentLargestPosition;
}

int rotateLeft(string a[], int n, int pos)
{
    if (n < 0 || pos < 0 || pos >= n)
        return -1;
    string posString = a[pos];
    for (int i = pos; i < (n - 1); i++) // Loop through strings in array.
        a[i] = a[i+1]; // Copy the next string in the array to current.
    a[n-1] = posString; // Replace final string with string at original position.
    return pos;
}

int countRuns(const string a[], int n)
{
    if (n < 0)
        return -1;
    if (n == 0)
        return 0;
    string currentString = a[0]; // Define current string.
    int items = 1; // Default to 1 item.
    for (int i = 1; i < n; i++)
        if (a[i] != currentString)
        {
            currentString = a[i]; // If string is different from current string, change to new string.
            items++; // Add 1 to number of items.
        }
    return items;
}

int flip(string a[], int n)
{
    if (n < 0)
        return -1;
    for (int i = 0; i < (n / 2); i++) // Loop through first half of the array.
    {
        string store = a[i];
        a[i] = a[(n - (i+1))];
        a[(n - (i+1))] = store; // Swap the two strings.
    }
    return n;
}

int differ(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0)
        return -1;
    int length = 0;
    if (n1 <= n2)
        length = n1;
    else
        length = n2; // Determine which array is shorter.
    for (int i = 0; i < length; i++) // Loop through strings in both the arrays until shorter array ends.
        if (a1[i] != a2[i])
            return i; // Return position when two strings did not match.
    return length; // Return length of shorter array otherwise.
}

int subsequence(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 <= 0 || n2 < 0 || n2 > n1)
        return -1;
    for (int i = 0; i < (n1 - (n2 - 1)); i++) // Loop through larger array.
    {
        bool match = true; // Default match to true.
        for (int k = 0; k < n2; k++) // Loop through smaller array.
            if (a1[i+k] != a2[k]) // If any string in smaller array does not match string in larger array.
            {
                match = false; // Change match to false then break.
                break;
            }
        if (match)
            return i; // If all strings match between smaller and larger array, match is true.
    }
    return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0)
        return -1;
    for (int i = 0; i < n1; i++) // Loop through array 1.
        for (int k = 0; k < n2; k++) // Loop through array 2.
            if (a1[i] == a2[k]) // If string in array 1 matches string in array 2, return position.
                return i;
    return -1;
}

int split(string a[], int n, string splitter)
{
    if (n < 0)
        return -1;
    for (int i = 0; i < (n-1); i++) // Bubble sort to sort in ascending order.
    {
        string store = "";
        for (int k = 0; k < (n-i-1); k++)
            if (a[k] > a[k+1]) // Switch neighbours if current is larger then next.
            {
                store = a[k];
                a[k] = a[k+1];
                a[k+1] = store;
            }
    }
    for (int i = 0; i < n; i++) // Loop through array, return i when string is larger or equal to splitter.
    {
        if (a[i] >= splitter)
            return i;
    }
    return n;
}