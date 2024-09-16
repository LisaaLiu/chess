#include "textDisplay.h"
#include "display.h"
#include <algorithm>

TextDisplay::TextDisplay(Game* game): GameDisplay{game} {};

void TextDisplay::notify() {
    GameState state = game->getState();

    cout << endl;
    // display black at top, white at bottom
    for (int y = state.board->height - 1; y >= 0; y--) {
        cout << y + 1 << ' ';
        for (int x = 0; x < state.board->width; x++) {
            Square* currentSquare = state.board->squareAt(x, y);
            if (currentSquare->occupied()) {
                cout << currentSquare->occupiedBy()->getDisplayChar();
            } else {
                bool isDarkSquare = (x % 2 == 0 && y % 2 == 0) || ( x % 2 !=0 && y % 2 != 0);
                char squareChar = isDarkSquare ? '_' : ' ';
                cout << squareChar;
            }
        }
        cout << endl;
    }
    cout << "  abcdefgh" << endl << endl;

    string message = getMessage(state);
    cout << message << endl;
}
