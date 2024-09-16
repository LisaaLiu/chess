#include "graphicDisplay.h"
#include "window.h"

#define SQUARE_SIZE 50 // pixels

GraphicDisplay::GraphicDisplay(Game* game): GameDisplay{game} {
    vector<string> title{
        " ______  __   _  ______  ______  ______  ",
        "|   ___||  |_| ||   ___||   ___||   ___| ",
        "|   |__ |   _  ||   ___| `-.`-.  `-.`-.  ",
        "|______||__| |_||______||______||______| ",
    };
    int lineNo = 0;
    for (auto line : title) {
        w.drawString(180, lineNo * 13 + 25, line);
        lineNo++;
    }

    // draw a nice backdrop for the chess board
    w.fillRectangle(90, 90, 420, 420, Xwindow::Blue);

    // draw the column labels
    for (int x = 0; x < game->state.board->width; x++) {
        int labelX = 100 + SQUARE_SIZE*x + SQUARE_SIZE / 2;
        int labelY = 100 + SQUARE_SIZE*game->state.board->width + SQUARE_SIZE / 2;
        string label = string(1, 'a' + x);
        w.drawString(labelX, labelY, label);
    }

    // draw the row labels
    for (int y = 0; y < game->state.board->height; y++) {
        int squareY = 100 + SQUARE_SIZE*(game->state.board->height - y - 1);
        w.drawString(75, squareY + SQUARE_SIZE / 2, to_string(y + 1));
    }
};

// converts a Board into a 2D array of characters representing the pieces
// this is useful for the GraphicDisplay to figure out which pieces have moved,
// so it won't need to redraw the entire board after each move
vector<vector<char>> GraphicDisplay::convertBoard(Board* board) {
    vector<vector<char>> converted;
    for (int x = 0; x < board->width; x++) {
        vector<char> column;

        for (int y = 0; y < board->height; y++) {
            auto square = board->squareAt(x, y);
            if (square->occupied()) {
                column.push_back(square->occupiedBy()->getDisplayChar());
            } else {
                column.push_back('\0');
            }
        }
        converted.push_back(column);
    }
    return converted;
}

// draw the board
void GraphicDisplay::notify() {
    GameState state = game->getState();
    vector<vector<char>> currBoardChars = convertBoard(state.board);
    // display black at top, white at bottom
    for (int y = 0; y < state.board->height; y++) {
        int squareY = 100 + SQUARE_SIZE*(state.board->height - y - 1);
        for (int x = 0; x < state.board->width; x++) {
            // if the piece hasn't changed then don't redraw
            if (prevBoardChars.size() && prevBoardChars[x][y] == currBoardChars[x][y]) {
                continue;
            }

            // draw the square
            bool isDarkSquare = (x % 2 == 0 && y % 2 == 0) || ( x % 2 !=0 && y % 2 != 0);
            Xwindow::colour squareColour = isDarkSquare ? Xwindow::Black : Xwindow::White;
            int squareX = 100 + SQUARE_SIZE*x;
            w.fillRectangle(squareX, squareY, SQUARE_SIZE, SQUARE_SIZE, squareColour);

            char pieceChar = currBoardChars[x][y];
            // draw the piece
            if (pieceChar) {
                int pieceX = squareX + SQUARE_SIZE / 2;
                int pieceY = squareY + SQUARE_SIZE / 2;
                // should be the opposite of the square's colour for high contrast
                Xwindow::colour pieceDisplayColour = isDarkSquare ? Xwindow::White : Xwindow::Black;
                w.drawString(pieceX, pieceY, string(1, pieceChar), pieceDisplayColour);
            }
        }
    }

    
    string message = getMessage(state);
    if (message != prevMessage) {
        // paint a white rectangle over the old message
        w.fillRectangle(100, 550, 400, 100, Xwindow::White);
        w.drawString(250, 575, message);
    }

    prevBoardChars = convertBoard(state.board);
    prevMessage = message;
}
