#include <queue>
#include <iostream>
#include "Graph.hpp"

Graph::Graph(Robot initial, Board board) {
    std::queue<Robot> toEvaluate;

    toEvaluate.push(initial);

    while (!toEvaluate.empty()) {
        Robot robot = toEvaluate.front();
        toEvaluate.pop();

        if (graph.find(robot) == graph.end()) {
            std::vector<std::pair<Robot::Move, Robot>> arcs;
            static std::vector<Robot::Move> movements = {
                Robot::Move::FORWARD_1,
                Robot::Move::FORWARD_2,
                Robot::Move::FORWARD_3,
                Robot::Move::BACKWARD_1,
                Robot::Move::TURN_LEFT,
                Robot::Move::TURN_RIGHT,
                Robot::Move::U_TURN
            };
            for (Robot::Move movement: movements) {
                Robot copy = robot;  //TODO: or is it ? <Vsauce music starts>
                board.play(copy, movement);
                if (copy.status != Robot::Status::DEAD) {
                    arcs.push_back(std::pair<Robot::Move, Robot>(movement, copy));
                    toEvaluate.push(copy);
                }
            }
            graph[robot] = arcs;
        }
    }
}

// ostream of the graph of the board
std::ostream& operator << (std::ostream& out, const Graph& graph) {
    for(std::pair<Robot, std::vector<std::pair<Robot::Move, Robot>>> e: graph.graph) {
        out << e.first << ":\n";
        for(std::pair<Robot::Move, Robot> p: e.second) {
            out << "\t" << p.first << ": " << p.second << "\n";
        }
    }
    return out;
}
