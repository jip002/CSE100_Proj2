#include <gtest/gtest.h>

#include "ActorGraph.hpp"

using namespace std;
using namespace testing;

TEST(ActorGraphTests, TwoActorsOneMovie) {
    string from = "Actor 1";
    string to = "Actor 2";
    string through = "Awesome Movie\t2020";

    stringstream ss;
    ss << "Actor/Actress	Movie	Year" << endl;
    ss << from << "\t" << through << endl;
    ss << to << "\t" << through << endl;

    ActorGraph graph;
    bool isBuilt = graph.buildGraph(ss);
    ASSERT_TRUE(isBuilt);
}

TEST(ActorGraphTests, ThreeActorsTwoMovie) {
    string throughOne = "Awesome Movie\t2020";
    string throughTwo = "Awesome Movie\t2024";

    stringstream ss;
    ss << "Actor/Actress	Movie	Year" << endl;
    ss << "Actor 1"
       << "\t" << throughOne << endl;
    ss << "Actor 2"
       << "\t" << throughOne << endl;
    ss << "Actor 1"
       << "\t" << throughTwo << endl;
    ss << "Actor 3"
       << "\t" << throughTwo << endl;
    ss << "Actor 2"
       << "\t" << throughOne << endl;
    ss << "Actor 3"
       << "\t" << throughOne << endl;

    ActorGraph graph;
    bool isBuilt = graph.buildGraph(ss);
    ASSERT_TRUE(isBuilt);
}

TEST(ActorGraphTests, ThreeActorsTwoMovieBFS) {
    string actor1 = "Actor 1";
    string actor2 = "Actor 2";
    string actor3 = "Actor 3";
    string throughOne = "Awesome Movie\t2020";
    string throughTwo = "Awesome Movie\t2024";

    stringstream ss;
    ss << "Actor/Actress	Movie	Year" << endl;
    ss << actor1 << "\t" << throughOne << endl;
    ss << actor2 << "\t" << throughOne << endl;
    ss << actor1 << "\t" << throughTwo << endl;
    ss << actor3 << "\t" << throughTwo << endl;
    ss << actor2 << "\t" << throughOne << endl;
    ss << actor3 << "\t" << throughOne << endl;

    ActorGraph graph;
    string shortestPath = "";
    graph.buildGraph(ss);

    graph.BFS(actor1, actor2, shortestPath);
    ASSERT_EQ(shortestPath,
              "(" + actor1 + ")--[Awesome Movie#@2020]-->(" + actor2 + ")");
}

TEST(ActorGraphTests, ThreeActorsOneMovieBFS) {
    string actor1 = "Actor 1";
    string actor2 = "Actor 2";
    string actor3 = "Actor 3";
    string through = "Awesome Movie\t2020";

    stringstream ss;
    ss << "Actor/Actress	Movie	Year" << endl;
    ss << actor1 << "\t" << through << endl;
    ss << actor2 << "\t" << through << endl;
    ss << actor2 << "\t" << through << endl;
    ss << actor3 << "\t" << through << endl;
    ss << actor1 << "\t" << through << endl;
    ss << actor3 << "\t" << through << endl;

    ActorGraph graph;
    string shortestPath = "";
    graph.buildGraph(ss);

    graph.BFS(actor1, actor3, shortestPath);

    ASSERT_EQ(shortestPath,
              "(" + actor1 + ")--[Awesome Movie#@2020]-->(" + actor3 + ")");
}

// TODO: add more tests for actor graph
