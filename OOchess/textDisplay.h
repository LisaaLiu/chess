#ifndef TXTDISPLAY_H
#define TXTDISPLAY_H

#include "display.h"

class TextDisplay : public GameDisplay {
  public:
    TextDisplay(Game* game);
    void notify() override;
};

#endif
