// COMPLETE TETRIS GAME - VISUAL STUDIO COMMUNITY
// Just paste this entire code into your .cpp file and press Ctrl+F5 to run!
// No other files needed - everything is included here

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <thread>
#include <chrono>
#include <algorithm>

#pragma warning(disable : 4996)  // Disable Visual Studio warnings

using namespace std;

// Game Configuration
const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 20;
const int PREVIEW_SIZE = 4;

// Tetromino piece types
enum TetrominoType {
    I_PIECE, O_PIECE, T_PIECE, S_PIECE, Z_PIECE, J_PIECE, L_PIECE, PIECE_COUNT
};

// Colors for each piece type (Windows console colors)
const int PIECE_COLORS[PIECE_COUNT] = {
    11,  // I - Cyan
    14,  // O - Yellow  
    13,  // T - Magenta
    10,  // S - Green
    12,  // Z - Red
    9,   // J - Blue
    6    // L - Brown/Orange
};

// All tetromino shapes with their 4 rotations
// Each piece is stored as a 4x4 grid, with 4 rotations
const vector<vector<vector<int>>> PIECES = {
    // I-Piece (Cyan) - Long piece
    {
        {0,0,0,0, 1,1,1,1, 0,0,0,0, 0,0,0,0},
        {0,0,1,0, 0,0,1,0, 0,0,1,0, 0,0,1,0},
        {0,0,0,0, 0,0,0,0, 1,1,1,1, 0,0,0,0},
        {0,1,0,0, 0,1,0,0, 0,1,0,0, 0,1,0,0}
    },
    // O-Piece (Yellow) - Square piece
    {
        {0,0,0,0, 0,1,1,0, 0,1,1,0, 0,0,0,0},
        {0,0,0,0, 0,1,1,0, 0,1,1,0, 0,0,0,0},
        {0,0,0,0, 0,1,1,0, 0,1,1,0, 0,0,0,0},
        {0,0,0,0, 0,1,1,0, 0,1,1,0, 0,0,0,0}
    },
    // T-Piece (Magenta) - T shape
    {
        {0,0,0,0, 0,1,0,0, 1,1,1,0, 0,0,0,0},
        {0,0,0,0, 0,1,0,0, 0,1,1,0, 0,1,0,0},
        {0,0,0,0, 0,0,0,0, 1,1,1,0, 0,1,0,0},
        {0,0,0,0, 0,1,0,0, 1,1,0,0, 0,1,0,0}
    },
    // S-Piece (Green) - S shape
    {
        {0,0,0,0, 0,1,1,0, 1,1,0,0, 0,0,0,0},
        {0,0,0,0, 0,1,0,0, 0,1,1,0, 0,0,1,0},
        {0,0,0,0, 0,0,0,0, 0,1,1,0, 1,1,0,0},
        {0,0,0,0, 1,0,0,0, 1,1,0,0, 0,1,0,0}
    },
    // Z-Piece (Red) - Z shape
    {
        {0,0,0,0, 1,1,0,0, 0,1,1,0, 0,0,0,0},
        {0,0,0,0, 0,0,1,0, 0,1,1,0, 0,1,0,0},
        {0,0,0,0, 0,0,0,0, 1,1,0,0, 0,1,1,0},
        {0,0,0,0, 0,1,0,0, 1,1,0,0, 1,0,0,0}
    },
    // J-Piece (Blue) - J shape
    {
        {0,0,0,0, 1,0,0,0, 1,1,1,0, 0,0,0,0},
        {0,0,0,0, 0,1,1,0, 0,1,0,0, 0,1,0,0},
        {0,0,0,0, 0,0,0,0, 1,1,1,0, 0,0,1,0},
        {0,0,0,0, 0,1,0,0, 0,1,0,0, 1,1,0,0}
    },
    // L-Piece (Orange) - L shape
    {
        {0,0,0,0, 0,0,1,0, 1,1,1,0, 0,0,0,0},
        {0,0,0,0, 0,1,0,0, 0,1,0,0, 0,1,1,0},
        {0,0,0,0, 0,0,0,0, 1,1,1,0, 1,0,0,0},
        {0,0,0,0, 1,1,0,0, 0,1,0,0, 0,1,0,0}
    }
};

// Main Tetris Game Class
class Tetris {
private:
    vector<vector<int>> board;      // Game board
    int currentPiece;                // Current falling piece type
    int currentRotation;             // Current rotation (0-3)
    int currentX, currentY;          // Position of current piece
    int nextPiece;                   // Next piece to spawn
    int score;                       // Player score
    int level;                       // Current level
    int linesCleared;                // Total lines cleared
    bool gameOver;                   // Game over flag
    int dropTimer;                   // Timer for auto-drop
    int dropSpeed;                   // Speed of auto-drop
    int ghostY;                      // Y position of ghost piece

public:
    // Constructor - Initialize game
    Tetris() {
        board = vector<vector<int>>(BOARD_HEIGHT, vector<int>(BOARD_WIDTH, 0));
        srand(static_cast<unsigned int>(time(nullptr)));
        nextPiece = rand() % PIECE_COUNT;
        spawnNewPiece();
        score = 0;
        level = 1;
        linesCleared = 0;
        gameOver = false;
        dropTimer = 0;
        dropSpeed = 20;
        ghostY = 0;
    }

    // Spawn a new piece at the top
    void spawnNewPiece() {
        currentPiece = nextPiece;
        nextPiece = rand() % PIECE_COUNT;
        currentRotation = 0;
        currentX = BOARD_WIDTH / 2 - 2;
        currentY = 0;
        updateGhostPosition();

        // Check if new piece can spawn
        if (!isValidPosition(currentPiece, currentRotation, currentX, currentY)) {
            gameOver = true;
        }
    }

    // Check if a piece position is valid
    bool isValidPosition(int piece, int rotation, int x, int y) {
        for (int py = 0; py < 4; py++) {
            for (int px = 0; px < 4; px++) {
                int index = py * 4 + px;
                if (PIECES[piece][rotation][index] != 0) {
                    int boardX = x + px;
                    int boardY = y + py;

                    // Check boundaries
                    if (boardX < 0 || boardX >= BOARD_WIDTH ||
                        boardY < 0 || boardY >= BOARD_HEIGHT) {
                        return false;
                    }

                    // Check collision with placed pieces
                    if (board[boardY][boardX] != 0) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    // Update ghost piece position
    void updateGhostPosition() {
        ghostY = currentY;
        while (isValidPosition(currentPiece, currentRotation, currentX, ghostY + 1)) {
            ghostY++;
        }
    }

    // Lock current piece in place
    void lockPiece() {
        for (int py = 0; py < 4; py++) {
            for (int px = 0; px < 4; px++) {
                int index = py * 4 + px;
                if (PIECES[currentPiece][currentRotation][index] != 0) {
                    board[currentY + py][currentX + px] = currentPiece + 1;
                }
            }
        }
    }

    // Clear completed lines
    void clearLines() {
        int linesThisRound = 0;

        for (int y = BOARD_HEIGHT - 1; y >= 0; y--) {
            bool fullLine = true;
            for (int x = 0; x < BOARD_WIDTH; x++) {
                if (board[y][x] == 0) {
                    fullLine = false;
                    break;
                }
            }

            if (fullLine) {
                // Move all lines above down
                for (int moveY = y; moveY > 0; moveY--) {
                    for (int x = 0; x < BOARD_WIDTH; x++) {
                        board[moveY][x] = board[moveY - 1][x];
                    }
                }
                // Clear top line
                for (int x = 0; x < BOARD_WIDTH; x++) {
                    board[0][x] = 0;
                }
                y++; // Check same line again
                linesThisRound++;
            }
        }

        // Update score and level
        if (linesThisRound > 0) {
            linesCleared += linesThisRound;
            // Scoring: 1 line=100, 2 lines=300, 3 lines=500, 4 lines=800
            int points[] = { 0, 100, 300, 500, 800 };
            score += points[min(4, linesThisRound)] * level;

            // Level up every 10 lines
            if (linesCleared >= level * 10) {
                level++;
                dropSpeed = max(1, 20 - level * 2);
            }
        }
    }

    // Move piece left
    void moveLeft() {
        if (isValidPosition(currentPiece, currentRotation, currentX - 1, currentY)) {
            currentX--;
            updateGhostPosition();
        }
    }

    // Move piece right
    void moveRight() {
        if (isValidPosition(currentPiece, currentRotation, currentX + 1, currentY)) {
            currentX++;
            updateGhostPosition();
        }
    }

    // Move piece down (soft drop)
    void moveDown() {
        if (isValidPosition(currentPiece, currentRotation, currentX, currentY + 1)) {
            currentY++;
            score += 1;
        }
        else {
            lockPiece();
            clearLines();
            spawnNewPiece();
        }
    }

    // Drop piece instantly (hard drop)
    void hardDrop() {
        int dropDistance = 0;
        while (isValidPosition(currentPiece, currentRotation, currentX, currentY + 1)) {
            currentY++;
            dropDistance++;
        }
        score += dropDistance * 2;
        lockPiece();
        clearLines();
        spawnNewPiece();
    }

    // Rotate piece clockwise
    void rotate() {
        int newRotation = (currentRotation + 1) % 4;

        // Try normal rotation
        if (isValidPosition(currentPiece, newRotation, currentX, currentY)) {
            currentRotation = newRotation;
            updateGhostPosition();
            return;
        }

        // Try wall kicks (moving piece if rotation doesn't fit)
        int kicks[] = { -1, 1, -2, 2 };
        for (int kick : kicks) {
            if (isValidPosition(currentPiece, newRotation, currentX + kick, currentY)) {
                currentRotation = newRotation;
                currentX += kick;
                updateGhostPosition();
                return;
            }
        }
    }

    // Set console cursor position
    void gotoxy(int x, int y) {
        COORD coord;
        coord.X = static_cast<SHORT>(x);
        coord.Y = static_cast<SHORT>(y);
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    // Set console text color
    void setColor(int color) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

    // Draw the entire game
    void draw() {
        gotoxy(0, 0);  // Move cursor to top instead of clearing screen

        // Draw title
        setColor(15);
        cout << "          ===== TETRIS GAME =====          " << endl << endl;

        // Draw main game board
        for (int y = 0; y < BOARD_HEIGHT; y++) {
            cout << "          ||";  // Left border

            for (int x = 0; x < BOARD_WIDTH; x++) {
                bool drawnCell = false;

                // Check if current piece is here
                for (int py = 0; py < 4; py++) {
                    for (int px = 0; px < 4; px++) {
                        int index = py * 4 + px;
                        if (PIECES[currentPiece][currentRotation][index] != 0) {
                            if (currentX + px == x && currentY + py == y) {
                                setColor(PIECE_COLORS[currentPiece]);
                                cout << "[]";
                                setColor(15);
                                drawnCell = true;
                                break;
                            }
                        }
                    }
                    if (drawnCell) break;
                }

                // If not current piece, check for placed pieces or ghost
                if (!drawnCell) {
                    if (board[y][x] == 0) {
                        // Check for ghost piece
                        bool isGhost = false;
                        for (int py = 0; py < 4; py++) {
                            for (int px = 0; px < 4; px++) {
                                int index = py * 4 + px;
                                if (PIECES[currentPiece][currentRotation][index] != 0) {
                                    if (currentX + px == x && ghostY + py == y && ghostY != currentY) {
                                        setColor(8);  // Dark gray for ghost
                                        cout << "::";
                                        setColor(15);
                                        isGhost = true;
                                        break;
                                    }
                                }
                            }
                            if (isGhost) break;
                        }
                        if (!isGhost) {
                            cout << "  ";  // Empty space
                        }
                    }
                    else {
                        setColor(PIECE_COLORS[board[y][x] - 1]);
                        cout << "[]";
                        setColor(15);
                    }
                }
            }

            cout << "||";  // Right border

            // Draw info panel on the right
            if (y == 2) cout << "    NEXT PIECE:";
            if (y >= 3 && y <= 6) {
                cout << "    ";
                for (int px = 0; px < 4; px++) {
                    int index = (y - 3) * 4 + px;
                    if (PIECES[nextPiece][0][index] != 0) {
                        setColor(PIECE_COLORS[nextPiece]);
                        cout << "[]";
                        setColor(15);
                    }
                    else {
                        cout << "  ";
                    }
                }
            }
            if (y == 8)  cout << "    SCORE: " << score << "    ";
            if (y == 9)  cout << "    LEVEL: " << level << "    ";
            if (y == 10) cout << "    LINES: " << linesCleared << "    ";
            if (y == 12) cout << "    CONTROLS:";
            if (y == 13) cout << "    [A][D] - Move L/R";
            if (y == 14) cout << "    [S] - Soft Drop";
            if (y == 15) cout << "    [W] - Rotate";
            if (y == 16) cout << "    [Space] - Hard Drop";
            if (y == 17) cout << "    [P] - Pause";
            if (y == 18) cout << "    [Q] - Quit";

            cout << "   " << endl;  // Extra spaces to clear line
        }

        // Draw bottom border
        cout << "          ==";
        for (int x = 0; x < BOARD_WIDTH; x++) {
            cout << "==";
        }
        cout << "==          " << endl;
    }

    // Update game state (auto-drop)
    void update() {
        dropTimer++;
        if (dropTimer >= dropSpeed) {
            moveDown();
            dropTimer = 0;
        }
    }

    // Handle keyboard input
    void handleInput() {
        if (_kbhit()) {
            char key = static_cast<char>(_getch());

            // Convert to lowercase for WASD
            if (key >= 'A' && key <= 'Z') {
                key = key + 32;
            }

            switch (key) {
            case 'a':  // Move left
                moveLeft();
                break;
            case 'd':  // Move right
                moveRight();
                break;
            case 's':  // Soft drop
                moveDown();
                break;
            case 'w':  // Rotate
                rotate();
                break;
            case ' ':  // Hard drop (spacebar)
                hardDrop();
                break;
            case 'p':  // Pause
                gotoxy(15, 12);
                cout << "PAUSED - Press P to continue";
                while (_getch() != 'p' && _getch() != 'P');
                break;
            case 'q':  // Quit
                gameOver = true;
                break;
            }
        }
    }

    // Check if game is over
    bool isGameOver() const {
        return gameOver;
    }

    // Get final score
    int getScore() const {
        return score;
    }

    // Get current level
    int getLevel() const {
        return level;
    }
};

// Main function - Entry point
int main() {
    // Setup console
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = false;  // Hide cursor
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    // Set console title
    SetConsoleTitleA("TETRIS - Classic Block Game");

    // Set console size (optional, but recommended)
    system("mode con: cols=60 lines=25");

    // Welcome screen
    system("cls");
    cout << "\n\n\n";
    cout << "          ========================\n";
    cout << "               T E T R I S\n";
    cout << "          ========================\n\n";
    cout << "          Classic Block Puzzle Game\n\n";
    cout << "            CONTROLS:\n";
    cout << "            A/D - Move Left/Right\n";
    cout << "            W   - Rotate\n";
    cout << "            S   - Soft Drop\n";
    cout << "            Space - Hard Drop\n";
    cout << "            P   - Pause\n";
    cout << "            Q   - Quit\n\n";
    cout << "          Press any key to start...\n\n";
    cout << "                                                             MADE BY JUBIN VERMA \n";
    _getch();

    // Create and run game
    system("cls");
    Tetris game;

    // Game loop
    while (!game.isGameOver()) {
        game.draw();
        game.handleInput();
        game.update();

        // Frame rate control (20 FPS)
        this_thread::sleep_for(chrono::milliseconds(50));
    }

    // Game over screen
    system("cls");
    cout << "\n\n\n";
    cout << "          ========================\n";
    cout << "              GAME OVER!\n";
    cout << "          ========================\n\n";
    cout << "            Final Score: " << game.getScore() << "\n";
    cout << "            Level Reached: " << game.getLevel() << "\n\n";

    // Simple high score tracking
    cout << "            Great job!\n\n";
    if (game.getScore() > 10000) {
        cout << "            AMAZING SCORE!\n\n";
    }
    else if (game.getScore() > 5000) {
        cout << "            Excellent playing!\n\n";
    }
    else if (game.getScore() > 1000) {
        cout << "            Good effort!\n\n";
    }

    cout << "          Press any key to exit...\n";
    _getch();

    return 0;
}