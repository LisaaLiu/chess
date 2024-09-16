/*
 *  game.cpp
 *  ChessProject
 *
 */
#include "game.h"
#include "queen.h"
#include "bishop.h"
#include "knight.h"
#include "rook.h"
#include "pawn.h"
#include "king.h"
#include "square.h"
#include "chessConst.h"
#include "humanPlayer.h" 
#include "levelOneComputer.h"
#include "levelTwoComputer.h"
#include "levelThreeComputer.h"



    
Game::Game(int width,int height){
    state.board = new Board(width, height);
    state.currentMove = nullptr;
    state.setupDone = false;
    state.gameStart = false;
    state.defaultSetting = true;
    state.currentPlayerColor = "white";
    state.whiteCheckmate = false;
    state.blackCheckmate = false;
    state.staleMate = false;
    state.whiteKingInCheck = false;
    state.blackKingInCheck = false;
    state.blackScore = 0;
    state.whiteScore = 0;
    state.whiteResign  = false;
    state.blackResign  = false;
    whitePieces = new  (set<Piece*>);
    blackPieces = new (set<Piece*>);
    playerWhite = nullptr;
    playerBlack = nullptr;

}


Game::~Game()
{
    // Delete pieces
    for (set<Piece*>::iterator itr = whitePieces->begin();
         itr != whitePieces->end(); ++itr)
    {
        if (*itr)
            delete *itr;
    }
    whitePieces->clear();
    if (whitePieces)
        delete whitePieces;
    
    for (set<Piece*>::iterator itr = blackPieces->begin();
         itr != blackPieces->end(); ++itr)
    {
        if (*itr)
         delete *itr;
    }
    blackPieces->clear();
    if (blackPieces)
        delete blackPieces;
   
    
    // Delete players
    if (playerWhite)
        delete playerWhite;
    if (playerBlack)
        delete playerBlack;
    if (state.board)
        delete state.board;
}

void Game::removePiece(int X, int Y) {
    Piece* aPiece;
    
    aPiece = state.board->squareAt(X,Y)->occupiedBy();
    if (aPiece) {
        
        if (aPiece->isWhite()) {
            whitePieces->erase(aPiece);
        } else {
            blackPieces->erase(aPiece);
        }
        delete aPiece;
    }

    state.board->squareAt(X,Y)->setOccupier(nullptr);
    
}
// Delete pieces
void Game::cleanupCurrentGame(){
   // cout << "clean up whitePieces" << endl;
    for (set<Piece*>::iterator itr = whitePieces->begin();
         itr != whitePieces->end(); ++itr)
    {
        if (*itr) {
            (*itr)->location()->setOccupier(nullptr);
            delete *itr;
        }
    }
    whitePieces->clear();
   
  //  cout << "clean up black pieces" << endl;
    for (set<Piece*>::iterator itr = blackPieces->begin();
         itr != blackPieces->end(); ++itr)
    {
        if (*itr) {
            (*itr)->location()->setOccupier(nullptr);
            delete *itr;
        }
    }
    blackPieces->clear();
   
  if (playerWhite) {
    delete (playerWhite);
  }
  if (playerBlack){
    delete (playerBlack);
  }

    playerWhite = nullptr;
    playerBlack = nullptr;
    state.currentPlayerColor = "white";
    state.whiteCheckmate = false;
    state.blackCheckmate = false;
    state.staleMate = false;
    state.whiteKingInCheck = false;
    state.blackKingInCheck = false;
    state.whiteResign = false;
    state.blackResign = false;

}

void Game::updateState() {
    whiteKinginCheck();
    blackKinginCheck();
    setWhiteCheckmate();
    if (state.whiteCheckmate) {
        state.whiteScore = state.whiteScore + 1;
    }
    
    setBlackCheckmate();
    if (state.blackCheckmate) {
        state.blackScore = state.blackScore + 1;
    }
    setStaleMate();
    if (state.staleMate) {
        state.whiteScore = state.whiteScore + 0.5;
        state.blackScore = state.blackScore + 0.5;
    }
    if (state.blackResign) {
        state.whiteScore = state.whiteScore +1;
    }
    if (state.whiteResign) {
        state.blackScore = state.blackScore + 1;
    }

}
void Game::putPiece(int X, int Y, char type)
{
    Piece* aPiece;
    King* aKing;
    Pawn* aPawn;
    Rook* aRook;
    Square* aSquare;
    // if a piece is already on that square, delete the 
    // one that is there, and replace with the new one
    if (state.board->squareAt(X,Y)->occupied()) {
       removePiece(X,Y);
    }
    // put the new piece in 
    switch (type) {
            case 'K':
                aKing = new King(true);
                aSquare = state.board->squareAt(X, Y);
                aSquare->setOccupier(aKing);
                aKing->setLocation(aSquare);
                aKing->setBoard(state.board);
                if (!state.defaultSetting) {
                    aKing->setMoved();
                }
                whitePieces->insert(aKing);
                whiteKing = aKing;
               
                break;
            case 'k':
                aKing = new King(false);
                aSquare = state.board->squareAt(X, Y);
                aSquare->setOccupier(aKing);
                aKing->setLocation(aSquare);
                aKing->setBoard(state.board);
                if (!state.defaultSetting) {
                    aKing->setMoved();
                }
                blackPieces->insert(aKing);
                blackKing = aKing;
                
                break;
            case 'Q':
                aPiece = new Queen(true);
                aSquare = state.board->squareAt(X, Y);
                aSquare->setOccupier(aPiece);
                aPiece->setLocation(aSquare);
                aPiece->setBoard(state.board);
                whitePieces->insert(aPiece);  
                break;

            case 'q':
                aPiece = new Queen(false);
                aSquare = state.board->squareAt(X, Y);
                aSquare->setOccupier(aPiece);
                aPiece->setLocation(aSquare);
                aPiece->setBoard(state.board);
                blackPieces->insert(aPiece);
                break;
                
            case 'B':
                aPiece = new Bishop(true);
                aSquare = state.board->squareAt(X, Y);
                aSquare->setOccupier(aPiece);
                aPiece->setLocation(aSquare);
                aPiece->setBoard(state.board);
                whitePieces->insert(aPiece);
                break;

            case 'b':
                aPiece = new Bishop(false);
                aSquare = state.board->squareAt(X, Y);
                aSquare->setOccupier(aPiece);
                aPiece->setLocation(aSquare);
                aPiece->setBoard(state.board);
                blackPieces->insert(aPiece);
                break;
         
            case 'R':
                aRook = new Rook(true);
                aSquare = state.board->squareAt(X, Y);
                aSquare->setOccupier(aRook);
                aRook->setLocation(aSquare);
                aRook->setBoard(state.board);
                if (!state.defaultSetting) {
                    aRook->setMoved();
                }
                whitePieces->insert(aRook);
                break;
                
            case 'r' :
                aRook = new Rook(false);
                aSquare = state.board->squareAt(X,Y);
                aSquare->setOccupier(aRook);
                aRook->setLocation(aSquare);
                aRook->setBoard(state.board);
                if (!state.defaultSetting) {
                    aRook->setMoved();
                }
                blackPieces->insert(aRook);
                break;

            case 'P' :
                aPawn = new Pawn(true);
                aSquare = state.board->squareAt(X,Y);
                aSquare->setOccupier(aPawn);
                aPawn->setLocation(aSquare);
                aPawn->setBoard(state.board);
                if (!state.defaultSetting) {
                    aPawn->setMoved();
                }
                whitePieces->insert(aPawn);
                
                break;

            case 'p':
                aPawn = new Pawn(false);
                aSquare = state.board->squareAt(X, Y);
                aSquare->setOccupier(aPawn);
                aPawn->setLocation(aSquare);
                aPawn->setBoard(state.board);
                if (!state.defaultSetting) {
                    aPawn->setMoved();
                }
                blackPieces->insert(aPawn);
                break;
                
            case 'N':
                aPiece = new Knight(true);
                aSquare = state.board->squareAt(X, Y);
                aSquare->setOccupier(aPiece);
                aPiece->setLocation(aSquare);
                aPiece->setBoard(state.board);
                whitePieces->insert(aPiece); 
                break;

            case 'n':
                aPiece = new Knight(false);
                aSquare = state.board->squareAt(X, Y);
                aSquare->setOccupier(aPiece);
                aPiece->setLocation(aSquare);
                aPiece->setBoard(state.board);
                blackPieces->insert(aPiece);
                break;
               
                
        }
}
/* king in check*/ 
/* game has not started and no players yet*/
/* in the setup mode*/
bool Game::whiteKinginCheck()
{
    bool check = false;
    state.whiteKingInCheck = false;
    if (whiteKing) {
    // for each piece in the opponent's set of pieces
        for (set<Piece*>::iterator itr = blackPieces->begin(); 
            itr != blackPieces->end(); ++itr)
        {
        // if a piece that is still located on the board
        // can move to my king's square 
            if (*itr) {
                if (((Piece*)*itr)->location() && 
                    ((Piece*)*itr)->canMoveTo(*(whiteKing->location())))
                {
                    // I am in check
                    check = true;
                    state.whiteKingInCheck = true;
                }
            }
        }
    }
    
    return check;
}
bool Game::blackKinginCheck()
{
    bool check = false;
    state.blackKingInCheck = false;
    if (blackKing) {
    // for each piece in the opponent's set of pieces
        for (set<Piece*>::iterator itr = whitePieces->begin(); 
            itr != whitePieces->end(); ++itr)
        {
      
        // if a piece that is still located on the board
        // can move to my king's square 
            if (*itr) {
                if (((Piece*)*itr)->location() && 
                    ((Piece*)*itr)->canMoveTo(*(blackKing->location())))
                {
                    // I am in check
                    check = true;
                    state.blackKingInCheck = true;
                }
            }
        }
    }
    
    return check;
}
void Game::setBlackCheckmate(){
    state.blackCheckmate = false;
    if (!(whiteKinginCheck())) {
        return;
    }
    if (whiteKing) {
        for (int i = 0; i < state.board->height; i++)
          {
            for (int j = 0; j < state.board->width; j++)
            {  
              if (whiteKing->validMove(*playerWhite, *(state.board->squareAt(j,i)),' ')){
                return;   
              }
            }
          }
        state.blackCheckmate = true;
        return;
    }
}

void Game::setWhiteCheckmate(){
    state.whiteCheckmate = false;
    if (!(blackKinginCheck())) {
        return;
    }
    if (blackKing) {
        for (int i = 0; i < state.board->height; i++)
          {
            for (int j = 0; j < state.board->width; j++)
            {  
              
              if (blackKing->validMove(*playerBlack, *(state.board->squareAt(j,i)),' ')){
                return;
                   
              }
            }
          }
        state.whiteCheckmate = true;
        return;
    }
}

void Game::setStaleMate() 
{
    state.staleMate = false;
    bool hasWhiteMove = false;
    bool hasBlackMove = false;
   
    for (set<Piece*>::iterator itr = whitePieces->begin(); itr != whitePieces->end(); ++itr)
    {
        if (*itr) {
            
          for (int i = 0; i < state.board->height; i++)
          {
            for (int j = 0; j < state.board->width; j++)
            {  
              
              if ((Piece*)(*itr)->validMove(*playerWhite, *(state.board->squareAt(j,i)),' ')){
                   hasWhiteMove = true;
                   break;
              }
            }
            if (hasWhiteMove) {
                break;
            }
          }
        
        }
        if (hasWhiteMove){
            break;
        }
    }
    for (set<Piece*>::iterator itr = blackPieces->begin(); itr != blackPieces->end(); ++itr)
    {
        if (*itr) {
            
        //    cout << "from Square "<< fromSquare << endl;

          for (int i = 0; i < state.board->height; i++)
          {
            for (int j = 0; j < state.board->width; j++)
            {  
              
              if ((Piece*)(*itr)->validMove(*playerBlack, *(state.board->squareAt(j,i)),' ')){
                   hasBlackMove = true;
                   break;
              }
            }
            if (hasBlackMove) {
                break;
            }
          }
        
        }
        if (hasBlackMove){
            break;
        }
    }

    if (state.currentPlayerColor=="white"&&!hasWhiteMove && !(whiteKinginCheck())) {
        state.staleMate = true;
        return;
    }
    if (state.currentPlayerColor=="black"&&!hasBlackMove && !(blackKinginCheck())) {
        state.staleMate = true;
        return;
    }
}
bool Game::validSetup() {
    
    int wKingCount = 0;
    int bKingCount = 0;
    Piece* wKing = nullptr;
    Piece* bKing = nullptr;


    for (set<Piece*>::iterator itr = whitePieces->begin();
         itr != whitePieces->end(); ++itr)
    {
        if (*itr){
            // count the king
            if ((*itr)->value() ==0 ) {
                wKingCount++;
                wKing = *itr;
            }
            // if pawn and is on the first and last row
            if ((*itr)->value() ==1 ){
                if ((*itr)->location()) {
                   if ((*itr)->location()->getY() == Y_MIN-1 ||(*itr)->location()->getY()==Y_MAX-1) {

                    return false;
                   }
                }
            }
        }
    }

    for (set<Piece*>::iterator itr = blackPieces->begin();
         itr != blackPieces->end(); ++itr)
    {
        if (*itr){
            if ((*itr)->value() == 0) {
                bKingCount++;
                bKing = (*itr);
            }
            // if pawn and is on the first and last row
            if ((*itr)->value() ==1 ){
                if ((*itr)->location()) {
                   if ((*itr)->location()->getY() == Y_MIN-1 ||(*itr)->location()->getY()==Y_MAX-1) {

                    return false;
                   }
                }
            }
        }
    }
    if ((wKingCount != 1)|| (bKingCount != 1)) {
        return false;
    }
    // set the current king
    whiteKing = dynamic_cast<King *> (wKing);
    blackKing = dynamic_cast<King *> (bKing);


    if (whiteKinginCheck() || blackKinginCheck()) {
        return false;
    }
    

    return true;

}

void Game::initializePieces()
{
    
    
    // Create each piece
    // Set their locations
    // Put them in their respective collections
    putPiece(3,0,'Q');
    putPiece(3,7,'q');
    putPiece(2,0,'B');
    putPiece(2,7,'b');
    putPiece(5,0,'B');
    putPiece(5,7,'b');
    putPiece(1,0,'N');
    putPiece(1,7,'n');
    putPiece(6,0,'N');
    putPiece(6,7,'n');
    putPiece(0,0,'R');
    putPiece(0,7,'r');
    putPiece(7,0,'R');
    putPiece(7,7,'r');
   
    
    for (int i = 0; i < 8; i++)
    {
        putPiece(i,1,'P');
        putPiece(i,6,'p');
    }
    
    // create the white king
    putPiece(4,7,'k');

    
    // create the black king
    putPiece(4,0,'K');
    
   
}
void Game::setWhitePlayerConfig(Player * aPlayer){
    aPlayer->setBoard(state.board);     
    aPlayer->setKing(whiteKing);
    aPlayer->setmyPieces(whitePieces); 
}
void Game::setBlackPlayerConfig(Player * aPlayer){
    aPlayer->setBoard(state.board);     
    aPlayer->setKing(blackKing);
    aPlayer->setmyPieces(blackPieces); 
}
void Game::createPlayers(int whitePlayer, int blackPlayer)
{
    LevelOneComputer *alevelOneWhite;
    LevelOneComputer *alevelOneBlack;
    LevelTwoComputer *alevelTwoWhite;
    LevelTwoComputer *alevelTwoBlack;
    LevelThreeComputer * alevelThreeWhite;
    LevelThreeComputer * alevelThreeBlack;

    // create White player and hand them their pieces
    switch(whitePlayer) {
    case 0:
        playerWhite = new HumanPlayer("white", true,0);
        setWhitePlayerConfig(playerWhite);
        // code block
         break;
    case 1:
        playerWhite = new LevelOneComputer("white", true,1);
        setWhitePlayerConfig(playerWhite);
        break;
    case 2:
        alevelOneWhite = new LevelOneComputer("white",true,1);
        setWhitePlayerConfig(alevelOneWhite);
        alevelTwoWhite = new LevelTwoComputer("white",true,2,alevelOneWhite);
        setWhitePlayerConfig(alevelTwoWhite);
        playerWhite = alevelTwoWhite;
        setWhitePlayerConfig(playerWhite);
        break;
    case 3:
        alevelOneWhite = new LevelOneComputer("white",true,1);
        setWhitePlayerConfig(alevelOneWhite);
        alevelTwoWhite = new LevelTwoComputer("white",true,2,alevelOneWhite);
        setWhitePlayerConfig(alevelTwoWhite);
        alevelThreeWhite = new LevelThreeComputer("white",true,3,alevelTwoWhite);
        setWhitePlayerConfig(alevelThreeWhite);
        playerWhite = alevelThreeWhite;
        setWhitePlayerConfig(playerWhite);
        break;
  
    }  

    switch(blackPlayer) {
    case 0:
        playerBlack = new HumanPlayer("black", false,0);
        setBlackPlayerConfig(playerBlack);
        // code block
         break;
    case 1:
        playerBlack = new LevelOneComputer("black", false,1);
        setBlackPlayerConfig(playerBlack);
        break;
    case 2:
        alevelOneBlack = new LevelOneComputer("black",false,1);
        setBlackPlayerConfig(alevelOneBlack);
        alevelTwoBlack = new LevelTwoComputer("black",false,2,alevelOneBlack);
        setBlackPlayerConfig(alevelTwoBlack);
        playerBlack = alevelTwoBlack;
        setBlackPlayerConfig(playerBlack);
        break;
    case 3:
        alevelOneBlack = new LevelOneComputer("black",false,1);
        setBlackPlayerConfig(alevelOneBlack);
        alevelTwoBlack = new LevelTwoComputer("black",false,2,alevelOneBlack);
        setBlackPlayerConfig(alevelTwoBlack);
        alevelThreeBlack = new LevelThreeComputer("black",false,3,alevelTwoBlack);
        setBlackPlayerConfig(alevelThreeBlack);
        playerBlack = alevelThreeBlack;
        setBlackPlayerConfig(playerBlack);
        break;
  
    }            
    // set opponent
    playerBlack->setOpponent(playerWhite);
    playerWhite->setOpponent(playerBlack);

    switch(whitePlayer) {
    
    case 2:
        alevelOneWhite->setOpponent(playerBlack);
        break;
    case 3:
        alevelOneWhite->setOpponent(playerBlack);
        alevelTwoWhite->setOpponent(playerBlack);
        break;
  
    }  
    switch(blackPlayer) {
    
    case 2:
        alevelOneBlack->setOpponent(playerWhite);
        break;
    case 3:
        alevelOneBlack->setOpponent(playerWhite);
        alevelTwoBlack->setOpponent(playerWhite);
        break;
  
    }  
   
}


void Game::setCurrentPlayer(string color) {
    if (color == "black") {
        currentPlayer = playerBlack;
    }
    if (color == "white") {
        currentPlayer = playerWhite;
    }
}


Player* Game::getNextPlayer(Player* player)

{
    if (player->isWhite())
        return playerBlack;
    else
        return playerWhite;
    
}

GameState Game::getState() {
    return state;
}
