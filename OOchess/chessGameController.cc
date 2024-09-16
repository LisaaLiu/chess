// chess Game Controller class to manage the  chess game
#include "chessGameController.h"
#include "textDisplay.h"
#include "graphicDisplay.h"
#include "iostream"
#include "chessConst.h"
#include "game.h"
#include "computerPlayer.h"



GameController::GameController(int width, int height) : game(width, height) {}

 // check if valid coordinate

bool GameController::validCoord(string coord) {

   if (coord.length() != 2 ||
          tolower(coord.at(0)) < X_MIN ||
          tolower(coord.at(0)) > X_MAX ||
          tolower(coord.at(1)) < Y_MIN ||
          tolower(coord.at(1)) > Y_MAX 
    )
    {
        return false;
    } 
    return true;
}
// check if valid piece charactor
bool GameController::validPiece(string pieceS) {
   char pieceC;
   if (pieceS.length() != 1)
        return false;
   pieceC = pieceS[0];
   if (pieceC == 'K' || pieceC =='k' ||
        pieceC == 'Q' || pieceC =='q' ||
        pieceC == 'R' || pieceC =='r' ||
        pieceC == 'P' || pieceC =='p' ||
        pieceC == 'B' || pieceC =='b' ||
        pieceC == 'N' || pieceC =='n' 
    )
    {
        return true;
    } 
    return false;
}

// check if valid move location
bool GameController::validMoveLocation(string fromSquare, string toSquare) {

 if(validCoord(fromSquare) &&
     validCoord(toSquare) &&
          (game.state.board->squareAt(tolower(fromSquare.at(0)) - X_MIN, 
                                      tolower(fromSquare.at(1)) - Y_MIN)->occupied())
    )
{    
    return true;
}
   
    return false;
}
// change the string to lower case
std::string GameController::toLowercase(const std::string& str) {
    std::string result = str;
    for (char& c : result) {
        c = std::tolower(c);
    }
    return result;
}
// game set up 
void GameController::setupGame()
{
   
    string cmdLine;
    string command;
    string parameter;
    int pos;

    cout << R"(
Entered setup mode! Valid commands:
    + <piece type> <location>       adds a piece. Example: + K e1
    - <location>                    removes a piece
    = [white | black]               sets white/black's turn next
    done                            exits setup mode

)";
    while (getline(cin, cmdLine) ){
        if (cmdLine.empty()) {
            continue;
        }
        
        pos = cmdLine.find(' ');
        command = cmdLine.substr(0,pos);
        parameter = cmdLine.erase(0,pos+1);
        
        command = toLowercase(command);
        if (command=="done" ) {
            
            if  (game.validSetup()) {
                cout << "Setup complete!" <<endl;
                game.state.setupDone = true;
                break;  
            } else {
                cout << "Invalid setup" << endl;
            }
        
        } else 
        
        if ( command == "+"){
                string pieceString;
                string coords;
                
                pos = parameter.find(' ');
                pieceString = parameter.substr(0,pos);
                
                coords = parameter.erase(0,pos+1);
                
                if (validPiece(pieceString) && validCoord(coords)) {
                    char piece;
                    int X = tolower(coords.at(0)) - X_MIN;
                    int Y = tolower(coords.at(1)) - Y_MIN;
                    piece = pieceString[0];
                    game.putPiece(X,Y, piece);
                    game.notify();
                } else 
                {
                    std::cout<<"invalid input!"<<endl;
                }
        } 
        else 
        if (command == "=")  {
            string colour;
            pos = parameter.find(' ');
            colour = parameter.substr(0,pos);
            colour = toLowercase(colour);
            if (colour == "black" || colour == "white") {
                game.state.currentPlayerColor = colour;
            } else {
                cout << "Invalid color!" << endl;
            }
        }
        else 
        if (command == "-") {
            string coords;
            coords =parameter;
            if (validCoord(coords)){
                int X = tolower(coords.at(0)) - X_MIN;
                int Y = tolower(coords.at(1)) - Y_MIN;
                game.removePiece(X,Y);
                game.notify();
            } else {
                cout << "Invalid coordinate!"<< endl;
            }
        }
        else {
                cout << R"(
Invalid command! Please try:
    + <piece type> <location>       adds a piece.       Example: + K e1
    - <location>                    removes a piece.    Example: - e1
    = [white | black]               sets white/black's turn next
    done                            exits setup mode

)";
            cin.clear();
        }
                           
    }
}
// get the level of computer
int GameController::getLevel(string l){ 
    if  (l=="computer1")
            return 1;
    if  (l=="computer2")
            return 2;
    if  (l=="computer3" )
            return 3;
    if ((l=="human"))
        return 0;
    return -1;
}

  
// handle human input move
void GameController:: handleHumanMove(string parameter){
    std::string fromSquare="";
    std::string toSquare = "";
    size_t pos;
    char pChar = ' ';
    pos = parameter.find(' ');
    if ( pos == std::string::npos) {
        std::cout << "Invalid move ... Try again. " << endl;
        return;
    }
    // get the fromSquare
    fromSquare = parameter.substr(0,pos);
    parameter = parameter.erase(0,pos+1);
    
    // get the toSquare
    pos = parameter.find(' ');
    if ( pos == std::string::npos) {
        toSquare = parameter;
    } else {
        // get the pomotion char
        
        toSquare = parameter.substr(0, pos);
        
        parameter = parameter.erase(0, pos+1);
        if (parameter.size()==1){
            pChar = parameter[0];
            cout << pChar << endl;
        }
        else 
        {
            std::cout << "Invalid move... Try again" << endl;
            return;
        }
    }
   
    if (!validMoveLocation(fromSquare, toSquare)){
        std::cout << "Invalid move... Try again." << endl;
    } else {
        
        Move *aMove= new Move(fromSquare, toSquare, pChar);
        if (!game.currentPlayer->makeMove(aMove))
        {
            std::cout << "Invalid move... Try again." << endl;
        } else {
            game.currentPlayer = game.getNextPlayer(game.currentPlayer); 
            std::cout << "current Player: "<< game.currentPlayer->getName() << endl;
            }
        game.state.currentMove = aMove;
    }
}

void GameController::startGame(string parameter)  {
    string wPlayer;
    string bPlayer;
    int pos;
    pos = parameter.find(' ');
    wPlayer = parameter.substr(0,pos);
    bPlayer = parameter.erase(0,pos+1);
    int wl = getLevel(wPlayer);
    int bl = getLevel(bPlayer);
    if (wl == -1 || bl == -1){
        cout << "Invalid player"<< endl;
    } else {
        cout << "Let the game begin!" << endl;
        cout << "Valid commands:" << endl;
        if (wl + bl == 0) {
            // both are human
            cout << "   move <from> <to>    (example: move e2 e4)" << endl;
        } else if (wl + bl >= 2) {
            // both are computers
            cout << "   move" << endl;
        } else {
            // one is human, one is computer
            cout << "   move <from> <to>    for human. Example: move e2 e4" << endl;
            cout << "   move                for computer." << endl;
        }
        cout << "   resign" << endl;

        game.state.gameStart = true;
       
        game.createPlayers(wl, bl);
        if (game.state.currentPlayerColor == "white"){
            game.currentPlayer = game.playerWhite;
        } else {
            game.currentPlayer = game.playerBlack;
        }
        cout << "Current Player: "<< game.state.currentPlayerColor << endl;
        game.notify();
       
    }
}
// set the game to default state
void GameController::setToDefaultState() {
             
    game.cleanupCurrentGame();
    
    game.state.defaultSetting = true;
    game.initializePieces();
    
    game.state.gameStart = false;
    game.state.currentMove = nullptr; 
}
// play the game
void GameController::play() {
  
    string command;
    string current;
    string destination;
    
    string setup;
    string cmdLine;
    string parameter;
    int pos;
  
    game.state.gameStart = false;
   
    game.initializePieces();
  
    TextDisplay *textDisplay = new TextDisplay(&game);
    GraphicDisplay *graphicDisplay = new GraphicDisplay(&game);
    game.attach(textDisplay);
    game.attach(graphicDisplay);
    game.notify();

    cout << R"(
Valid commands:
    setup
    game human human
    game human computer[1-3]
    game computer[1-3] computer[1-3]
)" << endl;
    while (getline(cin, cmdLine) ){
        if (cmdLine.empty()) {
            continue;
        }
        
        pos = cmdLine.find(' ');
        command = cmdLine.substr(0,pos);
        parameter = cmdLine.erase(0,pos+1);
        
    
        if  (command=="setup") {
       
                game.state.gameStart = false;
                game.state.defaultSetting = false;
                game.cleanupCurrentGame();
                game.state.currentMove = nullptr;
                game.notify();
                game.currentPlayer = game.playerWhite;
               
                setupGame();
              
        } else 
        if (command == "game") {
            if (game.validSetup()) {
                startGame( parameter);
            }
            else {
                cout << "not valid setup to start the game" << endl;
            }
               
        } else 
        if (command=="move" ) {
            if (game.state.gameStart) {
                if ((game.currentPlayer->getLevel() ==0)) {
                    handleHumanMove(parameter) ; 
                } else {

                     Move *aMove= game.currentPlayer->getMove();
                     if (aMove)
                     {
                       
                        game.currentPlayer->makeMove(aMove);
            
                        game.currentPlayer = game.getNextPlayer(game.currentPlayer); 
                        std::cout << "Current player: "<< game.currentPlayer->getName() << endl;
                        
                     } else {
                        game.state.staleMate = true;
                        cout << "No more valid moves!" << endl;
    
                     }
                     game.state.currentMove = aMove;
                    
                }
                
                game.updateState();
                game.notify();
                game.state.currentMove = nullptr;
                
                if (game.state.blackCheckmate||game.state.whiteCheckmate||game.state.staleMate) {
                    setToDefaultState();                   
                }
            } else {
                cout << "Game has not started"<< endl;
                cin.clear();
            }  
            
        } else 
         if (command == "resign") {
            if (game.state.gameStart){
                if (game.currentPlayer->isWhite())
                {
                    game.state.whiteResign = true;
                }
                else{
                    game.state.blackResign = true;
                }
                game.updateState();
                game.state.currentMove = nullptr;
                game.notify();
                setToDefaultState();                
            } else {
                cout << "Game has not started yet"<< endl;
                cin.clear();
            }
         }
         else 
        {
            cout << "Invalid command" << endl;
            cin.clear();
        }
        
    } 
    // display final score
    cout << "Final Score:" << endl;
    cout << "White score: " << game.state.whiteScore << endl;
    cout << "Black score: " << game.state.blackScore << endl;
    // clean up 
    delete textDisplay;
    delete graphicDisplay;
    
}
