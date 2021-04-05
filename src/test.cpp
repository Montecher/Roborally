#include <iostream>
#include "board.hpp"
#include "Graph.hpp"
#include "Deck.hpp"
#include "MoveTree.hpp"
#include "app.hpp"

#define attempt(fn) do { \
    int rst = fn(board); \
    if(rst != 0) return rst; \
} while(0)

using namespace std;
using namespace RR;

int testgraph(Board&);
int testpath(Board&);
int testdeal(Board&);
int testrandomhand(Board&);
int testfixedhand(Board&);

int main(int argc, char** argv) {
    if(argc != 2) {
        cerr << "Need one argument: the board file" << endl;
        return 1;
    }

    Board board(argv[1]);

    while(1) {
        int action = 0;
        cout << "What do you want to do?" << endl;
        cout << "0: exit (^D also works)" << endl;
        cout << "1: test graph generation" << endl;
        cout << "2: test path from (x,y,d) to (x,y)" << endl;
        cout << "3: test dealing cards" << endl;
        cout << "4: run webserver" << endl;
        cout << "5: test path with random hand" << endl;
        cout << "6: test path with fixed hand" << endl;
        cout << "> " << flush;
        cin >> action;

        switch(action) {
            case 0:
                cout << "Cya!" << endl;
                return 0;
            case 1:
                attempt(testgraph);
                break;
            case 2:
                attempt(testpath);
                break;
            case 3:
                attempt(testdeal);
                break;
            case 4:
                attempt(app);
                break;
            case 5:
                attempt(testrandomhand);
                break;
            case 6:
                attempt(testfixedhand);
                break;
            default:
                cerr << "Sorry, couldn't quite catch that" << endl;
        }
        cout << endl << endl;
    }
}

Graph mkgraph(Board& board) {
    Robot robot;
    robot.location.line = 1;
    robot.location.column = 0;
    robot.status = Robot::Status::EAST;

    return Graph(robot, board);
}

Location readlocation() {
    int x = 0;
    cout << "x: " << flush;
    cin >> x;
    int y = 0;
    cout << "y: " << flush;
    cin >> y;
    return { x, y };
}

Robot readrobot() {
    Location loc = readlocation();
    while(1) {
        int dir = 0;
        cout << "0: N, 1: S, 2: W, 3: E" << endl;
        cout << "d: " << flush;
        cin >> dir;
        Robot::Status st;
        switch(dir) {
            case 0:
                st = Robot::Status::NORTH;
                return { loc, st };
            case 1:
                st = Robot::Status::SOUTH;
                return { loc, st };
            case 2:
                st = Robot::Status::WEST;
                return { loc, st };
            case 3:
                st = Robot::Status::EAST;
                return { loc, st };
        }
        cerr << "Sorry, couldn't quite catch that" << endl;
    }
}

vector<Robot::Move> deal() {
    Deck<Robot::Move> deck;
    deck.add({
        {Robot::Move::FORWARD_1, 5},
        {Robot::Move::FORWARD_2, 3},
        {Robot::Move::FORWARD_3, 1},
        {Robot::Move::BACKWARD_1, 2},
        {Robot::Move::TURN_LEFT, 2},
        {Robot::Move::TURN_RIGHT, 2},
        {Robot::Move::U_TURN, 2}
    });
    deck.shuffle();
    return deck.deal(9);
}

int testgraph(Board& board) {
    cout << mkgraph(board);
    return 0;
}

int testpath(Board& board) {
    Graph graph = mkgraph(board);

    cout << "Where do you want to start?" << endl;
    Robot start = readrobot();
    cout << "Where do you want to go?" << endl;
    Location dest = readlocation();

    auto path = graph.path(start, dest);
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
    return 0;
}

int testdeal(Board&) {
    auto hand = deal();
    cout << "Dealt hand:";
    for(auto c: hand) cout << " " << c;
    cout << endl;
    return 0;
}

int testrandomhand(Board& board) {
    cout << "Where do you want to go from" << endl;
    Robot robot = readrobot();
    cout << "Where do you want to go to" << endl;
    Location dest = readlocation();

    auto hand = deal();
    MoveTree moves(robot, hand, board, 5);
    vector<Robot::Move> path = moves.cardsUsed(dest);

    if(path.empty()) {
        cout << "No path found" << endl;
    } else {
        cout << "Path of length " << path.size() << " found" << endl;
        cout << "(" << dest.line << ", " << dest.column << ")";
        for(auto e: path) {
            cout << " <- " << e;
        }
        cout << endl;
    }
    return 0;
}

int testfixedhand(Board& board) {
    cout << "Where do you want to go from" << endl;
    Robot robot = readrobot();
    cout << "Where do you want to go to" << endl;
    Location dest = readlocation();

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

    MoveTree moves(robot, hand, board, 5);
    vector<Robot::Move> path = moves.cardsUsed(dest);

    if(path.empty()) {
        cout << "No path found" << endl;
    } else {
        cout << "Path of length " << path.size() << " found" << endl;
        cout << "(" << dest.line << ", " << dest.column << ")";
        for(auto e: path) {
            cout << " <- " << e;
        }
        cout << endl;
    }
    return 0;
}
