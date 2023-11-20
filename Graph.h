#ifndef P3_GRAPH_H
#define P3_GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

using namespace std;

class Graph {
private:
    struct Edge {
        string end;     //this target destination
        double weight;	//distance
    };

    vector<string> path; 						 //cities in shortest path
    unordered_map<string, vector<Edge>> adjList; //key: city-date; value: vector of Edges to neighbors

    double euclideanDist(double latitude, double longitude);      //calculates the edge weight given the long and lat
    void addVertex(string city);					    //add each key to map if it doesn’t already exist
    void addEdge(string end, double weight);			//if dist<threshold, add Edge to adjList[start]

public:
    void create(vector<string>);					//for each Sighting in v, getCity(), getData()
    double dijkstra(string start, string end);		//add shortest path keys to class member path
    double modifiedBFS(string start, string end);	//add shortest path keys to class member path
    vector<string> getPath(); 						//get cities in shortest path
};


#endif //P3_GRAPH_H
