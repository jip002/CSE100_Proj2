#include "ActorGraph.hpp"

#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>

using namespace std;

// ActorGraph::ActorGraph() {}

/* Build the actor graph from dataset file.
 * Each line of the dataset file must be formatted as:
 * ActorName <tab> MovieName <tab> Year
 * Two actors are connected by an undirected edge if they have worked in a movie
 * before.
 */
bool ActorGraph::buildGraph(istream& is) {
    bool readHeader = false;
    // an actor* list to avoid creating redundant actor node
    // vector<Actor*> actor_list;
    while (is) {
        string s;
        if (!getline(is, s)) break;

        // skip the header of the file
        if (!readHeader) {
            readHeader = true;
            continue;
        }

        // read each line of the dataset to get the movie actor relation
        istringstream ss(s);
        vector<string> record;
        while (ss) {
            string str;
            if (!getline(ss, str, '\t')) break;
            record.push_back(str);
        }

        // if format is wrong, skip current line
        if (record.size() != 3) {
            continue;
        }

        // extract the information
        string actor(record[0]);
        string title(record[1]);
        int year = stoi(record[2]);

        string movieTitle = title + "#@" + to_string(year);

        Actor* actorObj;
        // check if the actor's node is already createdf
        if (actor_list.empty() == true) {
            actorObj = new Actor(actor);
            actor_list.push_back(actorObj);
            // cout << "added actor : " << actor << endl;
        } else {
            int size = actor_list.size();
            bool actor_exists = false;
            for (int i = 0; i < actor_list.size(); i++) {
                if (actor_list[i]->name ==
                    actor) {  // oh the actor already exists in the list
                    actorObj = actor_list[i];
                    actor_exists = true;
                    break;
                }
            }
            if (actor_exists == false) {
                actorObj = new Actor(actor);     // create new node
                actor_list.push_back(actorObj);  // add to the list
                // cout << "added actor : " << actor << endl;
            }
        }
        // add the actor node to the movie's vector
        movieToActors[movieTitle].push_back(actorObj);
        nameToActors[actor] = actorObj;
    }
    // if failed to read the file, clear the graph and return
    if (!is.eof()) {
        // TODO: delete the graph
        // ActorGraph::~ActorGraph();
        return false;
    }
    for (unordered_map<string, vector<Actor*>>::iterator it =
             movieToActors.begin();
         it != movieToActors.end(); ++it) {
        // let each actor in the same movie link to each other
        string title = it->first;
        vector<Actor*> actors = it->second;
        for (int i = 0; i < actors.size(); i++) {  // actors[i]
            for (int j = 0; j < actors.size(); j++) {
                if (i != j) {  // avoid actor A points to himself
                    pair<Actor*, string> outgoingPair(actors[j], title);
                    actors[i]->outgoing.push_back(outgoingPair);
                }
            }
        }
    }
    return true;
}

/* TODO */
void ActorGraph::BFS(const string& fromActor, const string& toActor,
                     string& shortestPath) {
    Actor* curr;
    if (nameToActors[fromActor] == 0 || nameToActors[toActor] == 0) return;
    if (fromActor.compare(toActor) == 0) return;  // When 2 actors are the same

    curr = nameToActors[fromActor];   // O(1)
    queue<pair<string, Actor*>> que;  // queue
    Actor* linked_Actor;  // temp object for each linked actor of curr (d, w)
    string path = "(" + curr->name + ")";
    pair<string, Actor*> currNode;
    currNode.first = path;
    currNode.second = curr;
    que.push(currNode);  // add (0,start) to queue
    while (!que.empty()) {
        currNode = que.front();
        if (currNode.second->name == toActor) {  // found the toActor node;
            shortestPath = currNode.first;
            break;
        }
        que.pop();  // pop curr from the queue
        if (currNode.second->isVisited == false) {
            currNode.second->isVisited = true;
            for (int i = 0; i < currNode.second->outgoing.size(); i++) {
                linked_Actor = currNode.second->outgoing[i].first;
                path = currNode.first;
                if (linked_Actor->isVisited == false) {
                    string title = currNode.second->outgoing[i].second;
                    path = path + "--[" + title + "]-->(" + linked_Actor->name +
                           ")";  // path = path + "--[title]-->(actor)"
                    pair<string, Actor*> newNode;
                    newNode.first = path;
                    newNode.second = linked_Actor;
                    que.push(newNode);  // add (d,w) to queue
                }                       // end of small if statement
            }                           // end of for loop
        }                               // end of the big if statement
    }                                   // end of while loop
    cout << "the path is: " << shortestPath << endl;
    // setting isVisited to false for all the actor nodes
    // for the next bfs call
    for (int i = 0; i < actor_list.size(); i++) {
        actor_list[i]->isVisited = false;
    }
}  // end of the method

/* TODO */
ActorGraph::~ActorGraph() {
    for (int i = 0; i < actor_list.size(); i++) {
        delete actor_list[i];
    }
}
