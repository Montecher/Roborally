#include "MoveTree.h"
#include <queue>
#include <iostream>

MoveTree::MoveTree(Robot position, std::vector<Robot::Move> hand, Board board, int movesLeft) {
    this->position = position;
    this->hand = hand;
    this->movesLeft = movesLeft;

    if (movesLeft > 0) {
        for (long unsigned int i = 0; i < hand.size(); ++i) {
            std::vector<Robot::Move> newHand;
            for (long unsigned int j = 0; j < hand.size(); ++j) {
                if (i != j) {
                    newHand.push_back(hand[j]);
                }
            }

            Robot newPosition = position;
            board.play(newPosition, hand[i]);
            if (newPosition.status != Robot::Status::DEAD) {
                this->branches.push_back({hand[i], new MoveTree(newPosition, newHand, board, movesLeft-1)});
            }
        }
    }
}

std::vector<Robot::Move> MoveTree::cardsUsed(Location goal) {
    std::queue<MoveTree*> toEvaluate;
    std::unordered_map<MoveTree*, std::pair<MoveTree*, Robot::Move>> rewindParent;
    std::vector<Robot::Move> used;

    toEvaluate.push(this);
    do {
        MoveTree* cell = toEvaluate.front();
        toEvaluate.pop();

        if (cell->position.location == goal) {
            do {
                used.push_back(rewindParent[cell].second);
                cell = rewindParent[cell].first;
            } while (cell != this);
            return used;
        }

        for (auto move: cell->branches) {
            rewindParent[move.second] = {cell, move.first};
            toEvaluate.push(move.second);
        }
    } while (!toEvaluate.empty());

    return used;
}
