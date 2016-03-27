#include "grid.h"
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cctype>
using namespace std;

// Declaring function prototypes.

bool isRouteWellFormed(string route);
bool isValid(int r, int c);
int navigateSegment(int r, int c, char dir, int maxSteps);
int navigateRoute(int sr, int sc, int er, int ec, string route, int& nsteps);

// Main routine for function testing.

int main()
{
    setSize(3,4);
    setWall(1,4);
    setWall(2,2);
    setWall(3,2);
    
    assert(isRouteWellFormed("n2e1")); // When route is valid.
    assert(isRouteWellFormed("N2eE01n0e2e1")); // When route is valid.
    assert(isRouteWellFormed("")); // When route is empty but valid.
    assert(isRouteWellFormed("W42")); // When route is valid.
    assert(!isRouteWellFormed("e1x")); // When invalid alpha character is present.
    assert(!isRouteWellFormed("w2+n3")); // When invalid character is present.
    assert(!isRouteWellFormed("!")); // When invalid character is present.
    assert(!isRouteWellFormed("N144")); // When there are more than 2 consecutive digits.
    assert(!isRouteWellFormed("3sn")); // When the route begins with a digit.
    
    assert(navigateSegment(3, 1, 'N', 2) == 2); // When segment is correctly navigable.
    assert(navigateSegment(1, 3, 'S', 5) == 2); // When number of steps is above maximum.
    assert(navigateSegment(3, 4, 'N', 5) == 1); // When number of steps is above maximum.
    assert(navigateSegment(1, 1, 'E', 5) == 2); // When number of steps is above maximum.
    assert(navigateSegment(1, 1, 'e', 5) == 2); // When number of steps is above maximum.
    assert(navigateSegment(1, 1, 'e', 0) == 0); // When number of steps is above maximum.
    assert(navigateSegment(2, 2, 'N', 5) == -1); // When (r,c) is not a valid empty grid position.
    assert(navigateSegment(-2, 2, 'N', 5) == -1); // When (r,c) is not a valid empty grid position.
    assert(navigateSegment(3, 1, 'N', -5) == -1); // When maxSteps is a negative value.
    assert(navigateSegment(3, 1, 'A', 5) == -1); // When char dir is not a direction value (N, E, S, W).
    
    int len;
    len = -999;
    assert(navigateRoute(3,1, 3,4, "e1x", len) == 2  &&  len == -999); // When route is syntactically incorrect.
    len = -999;
    assert(navigateRoute(10,1, 3,4, "n2e1", len) == 2  &&  len == -999); // When sr is larger than number of rows.
    len = -999;
    assert(navigateRoute(2,2, 3,4, "n2e1", len) == 2  &&  len == -999); // When (sr,sc) is wall.
    len = -999;
    assert(navigateRoute(-2,2, 3,4, "n2e1", len) == 2  &&  len == -999); // When sr is negative.
    len = -999;
    assert(navigateRoute(3,1, 3,4, "N2eE01n0s2e1", len) == 0  &&  len == 7); // When navigation is successful and endpoint is reached.
    len = -999;
    assert(navigateRoute(3,1, 3,4, "N01N01E01E01n0sse01", len) == 0  &&  len == 7); // When navigation is successful and endpoint is reached.
    len = -999;
    assert(navigateRoute(3,1, 3,1, "", len) == 0  &&  len == 0); // When navigation is successful and endpoint is reached.
    len = -999;
    assert(navigateRoute(3,1, 3,4, "N2", len) == 1  &&  len == 2); // When navigation is successful and endpoint is not reached.
    len = -999;
    assert(navigateRoute(3,1, 3,4, "N2E1", len) == 1  &&  len == 3); // When navigation is successful and endpoint is not reached.
    len = -999;
    assert(navigateRoute(3,1, 3,4, "N2es2", len) == 3  &&  len == 3); // When navigation is unsuccessful (runs into a wall).
    len = -999;
    assert(navigateRoute(3,1, 3,4, "N3e2s2", len) == 3  &&  len == 2); // When navigation is unsuccessful (runs off the grid).
    
    cout << "All tests succeeded." << endl;
}

// Function to check the validity of route.

bool isRouteWellFormed(string route)
{
    if (route == "")
        return true;
    
    // Tests whether first character is a direction value.

    switch(tolower(route[0]))
    {
        case 'n':
        case 'e':
        case 's':
        case 'w': break;
        default: return false;
    }
    
    // Tests whether the following characters are valid (e.g. numbers or direction value).
    
    for (int k = 1; k != route.size(); k++)
    {
        
        // Returning false if not digit and not a directional value.
        
        if (!isdigit(route[k]))
            switch(tolower(route[k]))
            {
                case 'n':
                case 'e':
                case 's':
                case 'w': break;
                default: return false;
            }
        
        // Returning false if more than two consecutive digits, true if two or less consecutive digits.
        
        else if (isdigit(route[k]))
            if (k+2 <= route.size() && isdigit(route[k+1]) && isdigit(route[k+2]))
                return false;
    }
    return true;
}

// Function to check whether start and end positions are valid empty grid positions.

bool isValid(int r, int c)
{
    int nColumns = getCols();
    int nRows = getRows();
    return (r <= nRows &&
            r > 0 &&
            c <= nColumns &&
            c > 0 &&
            !isWall(r,c));
}

// Function to check whether the number of steps in the route exceeds the maximum in one direction.

int navigateSegment(int r, int c, char dir, int maxSteps)
{
    int nColumns = getCols();
    int nRows = getRows();
    int max = 0;
    dir = toupper(dir);
    
    if (!isValid(r,c) || maxSteps < 0)
        return -1;
        
    // Calculate max number of steps in a certain direction until grid is ended or it meets a wall.
    
    if (dir == 'N')
        for (int k = r-1; k > 0 && !isWall(k, c); k--)
            max++;
    else if (dir == 'S')
        for (int k = r+1; k <= nRows && !isWall(k, c); k++)
            max++;
    else if (dir == 'W')
        for (int k = c-1; k > 0 && !isWall(r, k); k--)
            max++;
    else if (dir == 'E')
        for (int k = c+1; k <= nColumns && !isWall(r, k); k++)
            max++;
    else
        return -1;
    
    // Modify max steps if it is larger than max, else do nothing.
    
    if (maxSteps > max)
        maxSteps = max;
    
    return maxSteps;
}

// Function to check whether the grid is navigable by the robot with a given route.

int navigateRoute(int sr, int sc, int er, int ec, string route, int& nsteps)
{
    
    // Returning 2 if route is not well formed or start / end is invalid.
    
    if (!isRouteWellFormed(route) || !isValid(sr,sc) || !isValid(er, ec))
        return 2;
    
    else
    {
        nsteps = 0;
        int currentRow = sr;
        int currentCol = sc;
        
        // Loop to cycle through route.
        
        for (int k = 0; k != route.size(); k++)
        {
            if (isalpha(route[k]))
            {
                int maxSteps = 0;
                int navSteps = 0;
                char currentDir = route[k];
                
                // If direction is followed by no digits, steps is 1.
                
                if (isalpha(route[k+1]))
                    maxSteps = 1;
                else
                {
                    
                    // If the number of steps after the direction is two digits.
                    
                    if (k+2 <= route.size() && isdigit(route[k+2]))
                    {
                        maxSteps = (route[k+1] - '0') * 10 + (route[k+2] - '0');
                    }
                    
                    // If the number of steps after the direciton is one digit.
                    
                    else
                        maxSteps = route[k+1] - '0';
                }
                
                // Adding steps and checking whether robot runs into a wall or off the grid.
                
                navSteps = navigateSegment(currentRow, currentCol, currentDir, maxSteps);
                nsteps += navSteps;
                if (maxSteps > navSteps)
                    return 3;
                
                // Applying direction and navigable steps to current row and column.
                
                else
                    switch(tolower(currentDir))
                    {
                        case 'n': currentRow -= navSteps; break;
                        case 'e': currentCol += navSteps; break;
                        case 's': currentRow += navSteps; break;
                        case 'w': currentCol -= navSteps; break;
                        default: break;
                    }
            }
        }
        
        // Checking whether end point is reached.
        
        if (currentRow == er && currentCol == ec)
            return 0;
        else
            return 1;
    }
}