#include "display.h"

using namespace std;

GameDisplay::GameDisplay(Game* game) : game(game) {}

void GameDisplay::notify() {}

string GameDisplay::getMessage(const GameState& state) {
    if (state.whiteCheckmate) {
        return "Checkmate! White wins!";
    }
    if (state.blackCheckmate) {
        return "Checkmate! Black wins!";
    }
    if (state.staleMate) {
        return "Stalemate!";
    }   
    if (state.whiteResign) {
        return "Black wins!";
    }
    if (state.blackResign) {
        return "White wins!";
    }
    // These conditions will also be true during a checkmate
    // During checkmate, these messages will not be shown
    if (state.whiteKingInCheck) {
        return "White is in check.";  
    }
    if (state.blackKingInCheck) { 
        return "Black is in check.";
    }
    return "";
}

GameDisplay::~GameDisplay() {
    game->detach(this);
}
