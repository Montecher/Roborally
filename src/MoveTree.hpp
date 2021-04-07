#ifndef ROBORALLY_MOVETREE_H
#define ROBORALLY_MOVETREE_H

#include <vector>
#include "board.hpp"

using namespace RR;
class MoveTree {
private:
    Robot position;
    std::vector<Robot::Move> hand;
    int movesLeft;
    std::vector<std::pair<Robot::Move, MoveTree*>> branches;

public:
    MoveTree(Robot position, std::vector<Robot::Move> hand, Board board, int movesLeft);
    std::vector<Robot::Move> cardsUsed(Location goal);
    ~MoveTree();
};


#endif //ROBORALLY_MOVETREE_H
