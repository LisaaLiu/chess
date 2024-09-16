#ifndef GRAPHICDISPLAY_H
#define GRAPHICDISPLAY_H

#include "display.h"
#include "window.h"
#include "board.h"
#include <vector>

class GraphicDisplay : public GameDisplay {
    Xwindow w;
    // Store the previous state of the board and previous game message
    // to allow only re-rendering the elements that have changed
    std::vector<std::vector<char>> prevBoardChars;
    std::string prevMessage;
    static std::vector<std::vector<char>> convertBoard(Board*);
  public:
    GraphicDisplay(Game* game);
    void notify() override;
};

#endif
