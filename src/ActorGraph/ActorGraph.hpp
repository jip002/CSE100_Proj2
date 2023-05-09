#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP

#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

class Actor {
  public:
    string name;  // actor name
    bool isVisited;
    vector<pair<Actor*, string>> outgoing;
    // constructor
    Actor(string name) : name(name), isVisited(false) {}
};

class ActorGraph {
  public:
    // TODO: add data structures used in actor graph
    unordered_map<string, vector<Actor*>> movieToActors;
    unordered_map<string, Actor*> nameToActors;
    vector<Actor*> actor_list;

    /* TODO */
    ActorGraph() {
        movieToActors = unordered_map<string, vector<Actor*>>();
        nameToActors = unordered_map<string, Actor*>();
    };

    /* TODO */
    bool buildGraph(istream& is);

    /* TODO */
    void BFS(const string& fromActor, const string& toActor,
             string& shortestPath);

    /* TODO */
    ~ActorGraph();
};

#endif  // ACTORGRAPH_HPP
