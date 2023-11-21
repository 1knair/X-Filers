#ifndef P3_GRAPH_H
#define P3_GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>
#include <utility>
#include <cmath>



using namespace std;

class Graph {
private:
    struct Edge {
        string target_destination;
        long double weight;	//distance
    };

    vector<string> path; 						 //cities in shortest path
    unordered_map<string, vector<Edge>> adjList; //key: city-date; value: vector of Edges to neighbors

    /**
     * Calculates the edge weight (which is the distance) between the two nodes' latitude
     * and longitude using the Haversine formula.
     * Source(https://www.geeksforgeeks.org/program-distance-two-points-earth/)
     * @param start longitude and latitude of the starting node
     * @param end longitude and latitude of the ending node
     * @return double that corresponds to the edge weight
     */
    long double calculateEdgeWeight(pair<long double, long double> start, pair<long double, long double> end);
    void addVertex(string key);					    //add each key to map if it doesn’t already exist
    void addEdge(string end, double weight);	    //if dist<threshold, add Edge to adjList[start]

public:
    void create(vector<string>);					//for each Sighting in v, getCity(), getData()
    double dijkstra(string start, string end);		//add shortest path keys to class member path
    double modifiedBFS(string start, string end);	//add shortest path keys to class member path
    vector<string> getPath(); 						//get cities in shortest path
};


long double Graph::calculateEdgeWeight(pair<long double,long double> start, pair<long double,long double> end) {
    long double edgeWeight = 0; //holds the distance in km of the two points
    //convert longitudes and latitudes to radians
    long double latitude_start = ((M_PI) / 180 ) * start.first;
    long double longitude_start = ((M_PI) / 180 ) * start.second;
    long double latitude_end = ((M_PI) / 180 ) * end.first;
    long double longitude_end = ((M_PI) / 180 ) * end.second;

    //Using the Haversine Formula
    long double dist_long = abs(longitude_end - longitude_start);
    long double dist_lat = abs(latitude_end - latitude_start);

    edgeWeight = 2 * asin(sqrt( pow(sin(dist_lat/2),2) + cos(latitude_start) * cos(latitude_end) * pow(sin(dist_long/2), 2)));

    //convert into kilometers using the earth's radius in km is 6371
    edgeWeight = edgeWeight * 6371;

    return edgeWeight;

}

void addVertex(string key){
    //Check if it is in the graph

}



#endif //P3_GRAPH_H
