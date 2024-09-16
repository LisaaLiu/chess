#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include "observer.h"
#include "game.h"

class GameDisplay: public Observer {
	protected:
		Game* game;
		static std::string getMessage(const GameState&);
	public:
		GameDisplay(Game*);
		
		virtual void notify();
		virtual ~GameDisplay(); 
};

#endif
