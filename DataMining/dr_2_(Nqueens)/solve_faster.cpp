#include <iostream>
#include <queue>
#include <vector>
#include <bits/stdc++.h>
#include <sys/time.h>
// nQueens[n]
// queensPerRow [n]
// queensPerD1 [2n-1]
// queensPerD2 [2n-1]
// solve(N)
// {
//     // Putting the queen on the row with min conflicts
//     queens[] = init(N)
//         iter = 0 while (iter++ <= k * N)
//     {
//         // Randomly if two or more!
//         col = getColWithQueenWithMaxConf()
//             // Randomly if two or more!
//             row = getRowWithMinConflict(col)
//             // index=col & value=row
//             queens[col] = row
//     }
//     if (hasConflicts())
//     {
//         // Restart
//         solve(N)
//     }
// }
time_t start, end;
int *nQueens, *queensPerRow, *queensPerD1, *queensPerD2;
int n, k = 2, previousCol = -1;
const int FOUND_SOLUTION = -10;
bool hasConflicts;

void init()
{
    nQueens = new int[n];

    queensPerRow = new int[n];
    for (size_t i = 0; i < n; i++)
    {
        queensPerRow[i] = 0;
    }

    queensPerD1 = new int[2 * n - 1];
    for (size_t i = 0; i < 2 * n - 1; i++)
    {
        queensPerD1[i] = 0;
    }

    queensPerD2 = new int[2 * n - 1];
    for (size_t i = 0; i < 2 * n - 1; i++)
    {
        queensPerD2[i] = 0;
    }

    // putting queens on random row , each of them is on different col
    for (size_t i = 0; i < n; i++)
    {
        nQueens[i] = (rand() % n);
        queensPerRow[nQueens[i]] += 1;
        // \d1: x1 - y1 = x2 - y2
        queensPerD1[(i - nQueens[i]) + (n - 1)] += 1;
        // /d2: x1 + y1 = x2 + y2
        queensPerD2[(i + nQueens[i])] += 1;
    }
    hasConflicts = true;
}
int getColWithQueenWithMaxConf(const int &previousCol)
{

    std::vector<int> cols;
    int max_conf = INT_MIN;
    for (size_t i = 0; i < n; i++)
    {
        if (i == previousCol)
        {
            continue;
        }
        int conf = 0;
        conf += queensPerRow[nQueens[i]] + queensPerD1[(i - nQueens[i]) + (n - 1)] + queensPerD2[(i + nQueens[i])] - 3;
        if (conf == max_conf)
        {
            cols.push_back(i);
        }
        else if (conf > max_conf)
        {
            max_conf = conf;
            cols.clear();
            cols.push_back(i);
        }
    }

    if (max_conf == 0)
    {
        return FOUND_SOLUTION;
    }
    // choose random col
    int random = (rand() % cols.size());

    return cols[random];
}

int getRowWithMinConflict(const int &col)
{

    std::vector<int> rows;
    int min_conf = INT_MAX;
    // row iterating by the  col
    for (size_t row = 0; row < n; row++)
    {
        // the queen is there at the moment
        if (nQueens[col] == row)
        {
            continue;
        }
        int conf = 0;
        conf += queensPerRow[row] + queensPerD1[(col - row) + (n - 1)] + queensPerD2[(col + row)];
        if (conf == min_conf)
        {
            rows.push_back(row);
        }
        else if (conf < min_conf)
        {
            min_conf = conf;
            rows.clear();
            rows.push_back(row);
        }
    }

    // choose random row
    int random = (rand() % rows.size());

    return rows[random];
}

void solve()
{

    while (true)
    {
        // Putting the queen on the row with min conflicts
        init();
        int iter = 0;
        while (iter++ <= k * n)
        {
            // Randomly if two or more!
            int col = getColWithQueenWithMaxConf(previousCol);
            if (col == FOUND_SOLUTION)
            {
                hasConflicts = false;
                break;
            }
            // Randomly if two or more!
            int row = getRowWithMinConflict(col);

            // moving the current max conflict queen
            queensPerRow[nQueens[col]] -= 1;
            queensPerD1[(col - nQueens[col]) + (n - 1)] -= 1;
            queensPerD2[(col + nQueens[col])] -= 1;

            // index=col & value=row
            nQueens[col] = row;

            // moving the current max conflict queen
            queensPerRow[nQueens[col]] += 1;
            queensPerD1[(col - nQueens[col]) + (n - 1)] += 1;
            queensPerD2[(col + nQueens[col])] += 1;

            previousCol = col;
        }
        if (hasConflicts)
        {
            // Restart
            delete nQueens, queensPerRow, queensPerD1, queensPerD2;
            continue;
        }
        else
        {
            break;
        }
    }
}
void print()
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            if (nQueens[j] == i)
            {
                if (j == n - 1)
                {
                    std::cout << '*';
                }
                else
                {
                    std::cout << "* ";
                }
            }
            else
            {
                if (j == n - 1)
                {
                    std::cout << '_';
                }
                else
                {
                    std::cout << "_ ";
                }
            }
        }
        std::cout << '\n';
    }
}
int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    srand(time(0));
    std::cin >> n;
    time(&start);
    if (n == 1)
    {
        std::cout << "*\n";
        return 0;
    }
    else if (n == 2 || n == 3)
    {
        std::cout << "\n";
        return 0;
    }
    else
    {
        solve();
        time(&end);
    }

    double time_taken = double(end - start);
    std::cout << "Time taken by program is : " << std::fixed << std::setprecision(2) << time_taken << " sec " << std::endl;

    //print();
    delete nQueens, queensPerRow, queensPerD1, queensPerD2;
}