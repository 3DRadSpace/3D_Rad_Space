#include "LevenshteinDistance.hpp"

int Engine3DRadSpace::Algorithms::DamerauLevenshteinDistance(const std::string& a, const std::string& b)
{
    //if a is null, distance is length of b
    if(a.length() == 0) return int(b.length());
    //the reverse also applies.
    if(b.length() == 0) return int(a.length());

    int n = int(a.length() + 1);
    int m = int(b.length() + 1);

    //Allocate a two dimensional array of the size [a.length() + 1][b.length() + 1].
    int** d = new int* [n];
    if (d == nullptr) throw std::bad_alloc();

    for (int i = 0; i < n; i++)
    {
        d[i] = new int[m];
        if (d[i] == nullptr) throw std::bad_alloc();

        memset(d[i], 0, sizeof(int) * m);
    }

    //Fill the matrix margins.
    for (int i = 0; i <= a.length(); i++)
    {
        d[i][0] = i;
    }
    for (int j = 0; j <= b.length(); j++)
    {
        d[0][j] = j;
    }

    //String distance calculation
    int cost = 0;
    for (int i = 1; i <= a.length(); i++)
    {
        for (int j = 1; j <= b.length(); j++)
        {
            if (a[i-1] == b[j-1]) cost = 0;
            else
            {
                cost = 1;
            }
            d[i][j] = std::min({ d[i - 1][j] + 1 , d[i][j - 1] + 1, d[i - 1][j - 1] + cost });

            if (i > 1 && j > 1 && a[i] == b[j - 1] && a[i - 1] == b[j])
            {
                d[i][j] = std::min(d[i][j], d[i - 2][j - 2] + 1);
            }
        }
    }
    //Create a copy of the result.
    int r = d[n - 1][m - 1];

    //Deallocate the matrix
    for (int i = 0; i < a.length(); i++) delete[] d[i];
    delete[] d;

    return r;
}
