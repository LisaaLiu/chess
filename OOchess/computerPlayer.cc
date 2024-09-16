#include "computerPlayer.h"
#include <random>

// construtor
ComputerPlayer::ComputerPlayer(string name, bool isWhite, int level): Player(name, isWhite, level){
    moves = new (vector<Move*>);
}
// destrucotr
ComputerPlayer::~ComputerPlayer() {
    for (auto am :*moves) {
        delete (am);
    }
    moves->clear();
    //moves->erase(moves->begin(), moves->end());
    delete moves;
}
// get random Item for vector
template <typename T>
T ComputerPlayer::getRandomItem(const std::vector<T> myVector) {
    // Check if the vector is empty
    if (myVector.empty()) {
        throw std::runtime_error("The vector is empty.");
    }

    // Generate a random index between 0 and the size of the vector minus one
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, myVector.size() - 1);
    int randomIndex = dis(gen);

    // Access the element at the random index
    return myVector[randomIndex];
}
// get random Pawn promotion
char ComputerPlayer::getRandomPawnPomotion() {
    
    std::vector<char> pChars = {'Q','R','B','N'};

    try {
        char randomItem = getRandomItem(pChars);
        return randomItem;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
// get random move
Move* ComputerPlayer::getRandomMove() {
   
    try {
        Move* randomItem = getRandomItem(*moves);
        return randomItem;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
// get move
Move* ComputerPlayer::getMove(){return nullptr;}
