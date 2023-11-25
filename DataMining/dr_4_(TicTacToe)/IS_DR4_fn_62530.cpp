#include <iostream>

char emptyChar = '_';
char computerChar;
char playerChar;
int maxUtility = 10;
int minUtility = -10;
bool isPlayerTurn;

int maximizer(int alpha, int beta, int depth);
int minimizer(int alpha, int beta, int depth);

char gameBoard[3][3] =
    {
        {'_', '_', '_'},
        {'_', '_', '_'},
        {'_', '_', '_'}};

int calcUtility(int depth)
{
    // check if somebody wins by row
    for (int row = 0; row < 3; row++)
    {
        if (gameBoard[row][0] == gameBoard[row][1] && gameBoard[row][1] == gameBoard[row][2])
        {
            // player is minimizer
            if (gameBoard[row][0] == playerChar)
            {
                return minUtility + depth;
            }
            // computer is maximizer
            else if (gameBoard[row][0] == computerChar)
            {
                return maxUtility - depth;
            }
        }
    }

    // check if somebody wins by col
    for (int col = 0; col < 3; col++)
    {
        if (gameBoard[0][col] == gameBoard[1][col] && gameBoard[1][col] == gameBoard[2][col])
        {
            // player is minimizer
            if (gameBoard[0][col] == playerChar)
            {
                return minUtility + depth;
            }
            // computer is maximizer
            else if (gameBoard[0][col] == computerChar)
            {
                return maxUtility - depth;
            }
        }
    }

    // check if somebody wins by main diagonal
    if (gameBoard[0][0] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][2])
    {
        // player is minimizer
        if (gameBoard[0][0] == playerChar)
        {
            return minUtility + depth;
        }
        // computer is maximizer
        else if (gameBoard[0][0] == computerChar)
        {
            return maxUtility - depth;
        }
    }

    // check if somebody wins by secondary diagonal
    if (gameBoard[0][2] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][0])
    {
        // player is minimizer
        if (gameBoard[0][2] == playerChar)
        {
            return minUtility + depth;
        }
        // computer is maximizer
        else if (gameBoard[0][2] == computerChar)
        {
            return maxUtility - depth;
        }
    }
    // if nobody wins
    return 0;
}

void print()
{

    std::cout << "-------------\n";

    for (int i = 0; i < 3; i++)
    {
        std::cout << "| ";
        for (int j = 0; j < 3; j++)
        {
            std::cout << gameBoard[i][j];
            std::cout << " | ";
        }
        std::cout << '\n';
        std::cout << "-------------";
        std::cout << '\n';
    }
}

bool areThereMovesLeft()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (gameBoard[i][j] == emptyChar)
            {
                return true;
            }
        }
    }
    return false;
}

int maximizer(int alpha, int beta, int depth)
{
    int utility = calcUtility(depth);

    // check if someone is winning
    if (utility != 0)
    {
        return utility;
    }

    // there are no moves left , so the game is tied
    if (!areThereMovesLeft())
    {
        return 0;
    }

    // initialing value of  v for the maximizer is the smallest possible number
    int v = INT_MIN;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (gameBoard[i][j] == emptyChar)
            {
                gameBoard[i][j] = computerChar;

                // find the best v with recursion for the maximizer
                v = std::max(v, minimizer(alpha, beta, depth + 1));

                // undo the change to find all other possible moves
                gameBoard[i][j] = emptyChar;

                if (v >= beta)
                {
                    return v;
                }
                alpha = std::max(alpha, v);
            }
        }
    }
    return v;
}

int minimizer(int alpha, int beta, int depth)
{
    int utility = calcUtility(depth);

    // check if someone is winning
    if (utility != 0)
    {
        return utility;
    }

    // there are no moves left , so the game is tied
    if (!areThereMovesLeft())
    {
        return 0;
    }

    // initialing value of  v for the minimizer is the maximum possible number
    int v = INT_MAX;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (gameBoard[i][j] == emptyChar)
            {
                gameBoard[i][j] = playerChar;

                // find the best v with recursion for the minimizer
                v = std::min(v, maximizer(alpha, beta, depth + 1));

                // undo the change to find all other possible moves
                gameBoard[i][j] = emptyChar;

                if (v <= alpha)
                {
                    return v;
                }
                beta = std::min(beta, v);
            }
        }
    }
    return v;
}

std::pair<int, int> nextMoveForComputer()
{
    int bestValue = INT_MIN;
    std::pair<int, int> nextMove(-1, -1);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (gameBoard[i][j] == emptyChar)
            {
                gameBoard[i][j] = computerChar;

                int curValue = minimizer(INT_MIN, INT_MAX, 0);

                // undo
                gameBoard[i][j] = emptyChar;

                if (curValue > bestValue)
                {
                    nextMove.first = i;
                    nextMove.second = j;
                    bestValue = curValue;
                }
            }
        }
    }
    return nextMove;
}

bool isThereWinner()
{
    if (calcUtility(0) != 0)
    {
        return true;
    }
    return false;
}

bool makeMove(int i, int j, bool isPlayerTurn)
{
    if (gameBoard[i][j] == emptyChar)
    {
        if (isPlayerTurn)
        {
            gameBoard[i][j] = playerChar;
        }
        else
        {
            gameBoard[i][j] = computerChar;
        }

        std::cout << "===\n";

        print();

        if (isThereWinner())
        {
            if (isPlayerTurn)
            {
                std::cout << "Congratulations! Player has won!\n";
            }
            else
            {
                std::cout << "Unfortunately the computer has won!\n";
            }
        }
        else if (!areThereMovesLeft())
        {
            std::cout << "Game has finished tie!\n";
        }

        return true;
    }

    std::cout << "\nIt's not an empty cell ! Try another !\n\n";
    return false;
}

int main()
{
    print();

    char k;

    std::cout << "Who do u want to start the game first ? [P/C] : ";
    std::cin >> k;

    if (k == 'P' || k == 'p')
    {
        isPlayerTurn = true;
        computerChar = 'O';
        playerChar = 'X';
    }
    else if (k == 'C' || k == 'c')
    {
        isPlayerTurn = false;
        computerChar = 'X';
        playerChar = 'O';
    }

    while (areThereMovesLeft() && !isThereWinner())
    {
        int row, col;
        if (isPlayerTurn)
        {
            do
            {
                std::cout << "row: ";
                std::cin >> row;
                std::cout << "col: ";
                std::cin >> col;
            } while (!makeMove(row - 1, col - 1, isPlayerTurn));
            isPlayerTurn = !isPlayerTurn;
            continue;
        }
        std::pair<int, int> nextMove = nextMoveForComputer();
        makeMove(nextMove.first, nextMove.second, isPlayerTurn);
        isPlayerTurn = !isPlayerTurn;
    }

    return 0;
}