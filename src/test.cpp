#include <iostream>
#include "board.hpp"
#include "Graph.hpp"

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

    return 0;
}