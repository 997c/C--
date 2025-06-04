#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

// Define screen dimensions
const int SCREEN_WIDTH = 22;
const int SCREEN_HEIGHT = 22;

// Define the Tetris grid
std::vector<std::vector<int>> grid(SCREEN_HEIGHT, std::vector<int>(SCREEN_WIDTH, 0));

// Define the shapes of the Tetris pieces
enum PieceType {
    I,
    O,
    T,
    L,
    J,
    S,
    Z
};

// Define the colors for each piece type
enum PieceColor {
    BLACK = 0,
    CYAN,
    YELLOW,
    PURPLE,
    ORANGE,
    BLUE,
    GREEN,
    RED
};

// Structure to represent a Tetris piece
struct Piece {
    PieceType type;
    PieceColor color;
    int rotation;
    int x;
    int y;
    std::vector<std::vector<int>> shape;
};

// Function to generate a random Tetris piece
Piece generatePiece() {
    Piece piece;
    piece.rotation = 0;
    piece.x = SCREEN_WIDTH / 2 - 2;
    piece.y = 0;

    int pieceType = rand() % 7;
    switch (pieceType) {
        case I:
            piece.type = I;
            piece.color = CYAN;
            piece.shape = {{0,0,0,0},
                           {1,1,1,1},
                           {0,0,0,0},
                           {0,0,0,0}};
            break;
        case O:
            piece.type = O;
            piece.color = YELLOW;
            piece.shape = {{1,1},
                           {1,1}};
            break;
        case T:
            piece.type = T;
            piece.color = PURPLE;
            piece.shape = {{0,1,0},
                           {1,1,1},
                           {0,0,0}};
            break;
        case L:
            piece.type = L;
            piece.color = ORANGE;
            piece.shape = {{0,0,1},
                           {1,1,1},
                           {0,0,0}};
            break;
        case J:
            piece.type = J;
            piece.color = BLUE;
            piece.shape = {{1,0,0},
                           {1,1,1},
                           {0,0,0}};
            break;
        case S:
            piece.type = S;
            piece.color = GREEN;
            piece.shape = {{0,1,1},
                           {1,1,0},
                           {0,0,0}};
            break;
        case Z:
            piece.type = Z;
            piece.color = RED;
            piece.shape = {{1,1,0},
                           {0,1,1},
                           {0,0,0}};
            break;
    }
    return piece;
}

// Function to rotate a Tetris piece
void rotatePiece(Piece& piece) {
    int n = piece.shape.size();
    std::vector<std::vector<int>> rotatedShape(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            rotatedShape[j][n - 1 - i] = piece.shape[i][j];
        }
    }
    piece.shape = rotatedShape;
}

// Function to check if a piece can move to a new position
bool canMove(const Piece& piece, int newX, int newY) {
    for (int i = 0; i < piece.shape.size(); ++i) {
        for (int j = 0; j < piece.shape[0].size(); ++j) {
            if (piece.shape[i][j] == 1) {
                int gridX = newX + j;
                int gridY = newY + i;

                if (gridX < 0 || gridX >= SCREEN_WIDTH || gridY < 0 || gridY >= SCREEN_HEIGHT) {
                    return false;
                }

                if (grid[gridY][gridX] != 0) {
                    return false;
                }
            }
        }
    }
    return true;
}

// Function to merge a piece into the grid
void mergePiece(const Piece& piece) {
    for (int i = 0; i < piece.shape.size(); ++i) {
        for (int j = 0; j < piece.shape[0].size(); ++j) {
            if (piece.shape[i][j] == 1) {
                grid[piece.y + i][piece.x + j] = piece.color;
            }
        }
    }
}

// Function to clear completed lines
void clearLines() {
    for (int i = 0; i < SCREEN_HEIGHT; ++i) {
        bool lineFilled = true;
        for (int j = 0; j < SCREEN_WIDTH; ++j) {
            if (grid[i][j] == 0) {
                lineFilled = false;
                break;
            }
        }
        if (lineFilled) {
            // Move all lines above down one row
            for (int k = i; k > 0; --k) {
                grid[k] = grid[k - 1];
            }
            // Clear the top line
            grid[0] = std::vector<int>(SCREEN_WIDTH, 0);
        }
    }
}

// Function to print the grid to the console
void printGrid() {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

    for (int i = 0; i < SCREEN_HEIGHT; ++i) {
        for (int j = 0; j < SCREEN_WIDTH; ++j) {
            int cell = grid[i][j];
            
#ifdef _WIN32
            SetConsoleTextAttribute(hConsole, cell);
#endif
            
            std::cout << (cell == 0 ? " " : "#");
        }
        std::cout << std::endl;
    }
}

// Function to implement a delay
void delay(int milliseconds) {
#ifdef _WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif
}

int main() {
    srand(time(0));

    Piece currentPiece = generatePiece();
    int dropInterval = 500; // Milliseconds

    while (true) {
        // Move the piece down
        if (canMove(currentPiece, currentPiece.x, currentPiece.y + 1)) {
            currentPiece.y++;
        } else {
            // Merge the piece into the grid
            mergePiece(currentPiece);

            // Clear any completed lines
            clearLines();

            // Generate a new piece
            currentPiece = generatePiece();

            // Check for game over
            if (!canMove(currentPiece, currentPiece.x, currentPiece.y)) {
                std::cout << "Game Over!" << std::endl;
                break;
            }
        }

        // Print the grid
        printGrid();

        // Delay
        delay(dropInterval);

        // Clear the console (platform-dependent)
        system("cls||clear");
    }

    return 0;
}