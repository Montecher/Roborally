#include <iostream>
#include "board.hpp"
#include "Graph.hpp"
#include "MoveTree.h"

using namespace std;
using namespace RR;
int main(int argc, char** argv) {
    Board board(argv[1]);
    Robot robot;
    robot.location.line = 1;
    robot.location.column = 0;
    robot.status = Robot::Status::EAST;

    Graph graph = Graph(robot, board);
    cout << graph;  // test the ostream

    Location dest = {4, 3};
    auto path = graph.path(robot, dest);
    if(path.empty()) {
        cout << "No path found" << endl;
    } else {
        cout << "Path of length " << path.size() << " found" << endl;
        cout << "(" << dest.line << ", " << dest.column << ")";
        for(auto e: path) {
            cout << " <- " << e.first << ", " << e.second;
        }
        cout << endl;
    }

    vector<Robot::Move> hand;
    hand.push_back(Robot::Move::TURN_RIGHT);
    hand.push_back(Robot::Move::U_TURN);
    hand.push_back(Robot::Move::FORWARD_1);
    hand.push_back(Robot::Move::FORWARD_1);
    hand.push_back(Robot::Move::FORWARD_3);
    hand.push_back(Robot::Move::BACKWARD_1);
    hand.push_back(Robot::Move::TURN_RIGHT);
    hand.push_back(Robot::Move::TURN_LEFT);
    hand.push_back(Robot::Move::FORWARD_2);

    cout << "| ";
    for (auto card: hand) {
        cout << card << " | ";
    }
    cout << endl;

    MoveTree moves(robot, hand, board, 5);
    vector<Robot::Move> test = moves.cardsUsed(dest);
//    cout << robot << endl;

    cout << "| ";
    for (auto card: test) {
        cout << card << " | ";
    }
    cout << endl;

    return 0;
}
