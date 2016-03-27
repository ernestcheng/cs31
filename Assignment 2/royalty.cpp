#include <iostream>
#include <string>
using namespace std;

int main()
{
    // Define all variables.
    
    int units_sent(0);
    string title("");
    double base_price(0);
    string premium_item("");
    double royalties(0);
    
    // Define cout settings.
    
    cout.precision(2);
    cout.setf(ios::fixed);
    
    // Query for units sent input.
    
    cout << "Units sent: ";
    cin >> units_sent;
    cin.ignore(10000, '\n');
    
    // Query for title.
    
    cout << "Title: ";
    getline(cin,title);
    
    // Query for base price.
    
    cout << "Base price: ";
    cin >> base_price;
    cin.ignore(10000, '\n');
    
    // Query for premium item.
    
    cout << "Premium item? (y/n): ";
    getline(cin,premium_item);
    
    // Define variable royalties.
    
    cout << "---" << endl;
    
    // Error Messages
    
    if (units_sent < 0)
    {
        cout << "The number of units sent must be nonnegative." << endl;
        return 1;
    }
    
    else if (title == "")
    {
        cout << "You must enter a title." << endl;
        return 1;
    }
    
    else if (base_price < 0)
    {
        cout << "The base price must be nonnegative." << endl;
        return 1;
    }
    
    else if (premium_item != "y" && premium_item != "n")
    {
        cout << "You must enter y or n." << endl;
        return 1;
    }
    
    // Calculation if units sent is no more than 400.
    
    if (units_sent <= 400)
    {
        royalties = (base_price * 0.09) * units_sent;
    }
    
    // Calculation if units sent is more than 400 but less than 1200.
    
    else if (units_sent > 400 && units_sent <= 1200)
    {
        if (premium_item == "n")
        {
            royalties = (base_price * 0.09) * 400 + (base_price * 0.13) * (units_sent - 400);
        }
        
        else
        {
            royalties = (base_price * 0.09) * 400 + (base_price * 0.16) * (units_sent - 400);
        }
    }
    
    // Calculation if units sent is more than 1200.
    
    else
    {
        if (premium_item == "n")
        {
            royalties = (base_price * 0.09) * 400 + (base_price * 0.13) * 800 + (base_price * 0.14) * (units_sent - 1200);
        }
        
        else
        {
            royalties = (base_price * 0.09) * 400 + (base_price * 0.16) * 800 + (base_price * 0.14) * (units_sent - 1200);
        }
    }
    
    // Print final statement.
    
    cout << title << " earned $" << royalties << " in royalties." << endl;
}