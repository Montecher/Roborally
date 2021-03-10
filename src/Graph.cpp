#include <queue>
#include <iostream>
#include <unordered_set>
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
                Robot copy = robot;
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

// custom comparator for reverse order of the first element of a pair
template<typename T, typename X>
struct PairFirstCompareReverse {
    bool operator () (const std::pair<T, X>& a, const std::pair<T, X>& b) {
        return a.first>b.first;
    }
};

std::vector<std::pair<Robot::Move, Robot>> Graph::path(const Robot orig, const Robot dest) {
    // C++ types are always fun
    std::unordered_map<Robot, double, RobotHashTool, RobotHashTool> costs;
    std::unordered_map<Robot, std::pair<Robot::Move, Robot>, RobotHashTool, RobotHashTool> pred;
    std::priority_queue<std::pair<double, Robot>, std::vector<std::pair<double, Robot>>, PairFirstCompareReverse<double, Robot>> toEvaluate;
    std::unordered_set<Robot, RobotHashTool, RobotHashTool> seen;

    // initialize algorithm
    for(auto e: graph) costs[e.first] = std::numeric_limits<double>::infinity(); 
    costs[orig] = 0.;
    toEvaluate.push({0., orig});

    // evaluate costs for every single node
    while(!toEvaluate.empty()) {
        Robot r = toEvaluate.top().second;
        toEvaluate.pop();
        if(seen.find(r)!=seen.end()) continue;
        seen.insert(r);
        for(auto s: graph[r]) {
            Robot w = s.second;
            if(costs[w] > costs[r] + 1) {
                costs[w] = costs[r] + 1;
                pred[w] = {s.first, r};
                toEvaluate.push({costs[w], w});
            }
        }
    }

    // couldn't find path to destination node
    if(costs[dest] == std::numeric_limits<double>::infinity()) return {};

    // build path from predecessors
    std::vector<std::pair<Robot::Move, Robot>> moves;
    Robot r = dest;
    while(r != orig) {
        auto m = pred[r];
        moves.push_back(m);
        r = m.second;
    }
    return moves;
}
std::vector<std::pair<Robot::Move, Robot>> Graph::path(const Robot orig, const Location dest) {
    // C++ types are always fun
    std::unordered_map<Robot, double, RobotHashTool, RobotHashTool> costs;
    std::unordered_map<Robot, std::pair<Robot::Move, Robot>, RobotHashTool, RobotHashTool> pred;
    std::priority_queue<std::pair<double, Robot>, std::vector<std::pair<double, Robot>>, PairFirstCompareReverse<double, Robot>> toEvaluate;
    std::unordered_set<Robot, RobotHashTool, RobotHashTool> seen;

    // initialize algorithm
    for(auto e: graph) costs[e.first] = std::numeric_limits<double>::infinity(); 
    costs[orig] = 0.;
    toEvaluate.push({0., orig});

    // evaluate costs for every single node
    while(!toEvaluate.empty()) {
        Robot r = toEvaluate.top().second;
        toEvaluate.pop();
        if(seen.find(r)!=seen.end()) continue;
        seen.insert(r);
        for(auto s: graph[r]) {
            Robot w = s.second;
            if(costs[w] > costs[r] + 1) {
                costs[w] = costs[r] + 1;
                pred[w] = {s.first, r};
                toEvaluate.push({costs[w], w});
            }
        }
    }

    static std::vector<Robot::Status> statuses = {
        Robot::Status::EAST,
        Robot::Status::SOUTH,
        Robot::Status::WEST,
        Robot::Status::NORTH
    };
    Robot bestRobot;
    double bestCost = std::numeric_limits<double>::infinity();
    for(auto status: statuses) {
        Robot robot;
        robot.location = dest;
        robot.status = status;

        // not found for this orientation
        if(costs[robot] < bestCost) {
            bestRobot = robot;
            bestCost = costs[robot];
        }
    }

    // couldn't find path to destination node
    if(bestCost == std::numeric_limits<double>::infinity()) return {};

    // build path from predecessors
    std::vector<std::pair<Robot::Move, Robot>> moves;
    Robot r = bestRobot;
    while(r != orig) {
        auto m = pred[r];
        moves.push_back(m);
        r = m.second;
    }
    return moves;
}
