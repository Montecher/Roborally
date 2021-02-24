#ifndef ROBORALLY_GRAPH_HPP
#define ROBORALLY_GRAPH_HPP


#include <unordered_map>
#include <vector>
#include "board.hpp"

using namespace RR;  // ffs this namespace....

struct RobotHashTool {
    std::size_t operator()(Robot const& r) const noexcept {
        return (size_t) r.location.line + 61*r.location.column + 17*(int)r.status;
    }
    bool operator()(Robot const& a, Robot const& b) const noexcept {
        return a.location.line == b.location.line && a.location.column == b.location.column && a.status == b.status;
    }
};


class Graph {
private:
    std::unordered_map<Robot, std::vector<std::pair<Robot::Move, Robot>>, RobotHashTool, RobotHashTool> graph;

public:
    Graph(Robot initial, Board board);
};

#endif //ROBORALLY_GRAPH_HPP
