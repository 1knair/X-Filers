#ifndef P3_GRAPH_H
#define P3_GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>
#include <utility>
#include <cmath>
#include "UFOSightings.h"
#define X_PI 3.14159265358979323846

using namespace std;

class Graph {
private:
    struct Edge {
        string to;
        long double weight;	//distance
    };

    vector<string> path; 						 
    unordered_map<string, vector<Edge>> adjList;
    float threshold = 600; //km
    /**
     * Calculates the edge weight (which is the distance) between the two nodes' latitude
     * and longitude using the Haversine formula.
     * Source(https://www.geeksforgeeks.org/program-distance-two-points-earth/)
     * @param start longitude and latitude of the starting node
     * @param end longitude and latitude of the ending node
     * @return double that corresponds to the edge weight
     */
    long double calculateEdgeWeight(pair<long double, long double> start, pair<long double, long double> end);
    void addVertex(string key);					    
    void addEdge(string from, string to, long double weight);	       

public:
    void create(UFOSightings& sightings);
    double dijkstra(string start, string end);
    double modifiedBFS(string start, string end);
    vector<string> getPath();
};

<<<<<<< Updated upstream
//O(number of sightings)
void Graph::addVertex(string key){
=======
void Graph::addVertex(string city) {
>>>>>>> Stashed changes
    //Check if it is in the graph
    //calculateEdgeWeight();
   if (adjList.find(city) == adjList.end()) { //For duplicate
       adjList[city] = {};
    }
}
<<<<<<< Updated upstream
//O(
void Graph::addEdge(string start, string end){
=======

void Graph::addEdge(string from, string to, long double weight) {
>>>>>>> Stashed changes
    Edge newEdge;
    newEdge.weight = weight;
    newEdge.to = to;
    // Add the new edge to the start city's list of edges
    adjList[from].push_back(newEdge);
    
    cout << "Added edge from " << from << " to " << to << '\n' << weight << endl;
}

void Graph::create(UFOSightings& sightings) {
    vector<pair<string, string>> v = sightings.v;
    for (const auto& fromKey: v) //Go through every city
    {
        addVertex(sightings.m[fromKey].city);
        for (const auto& toKey : v) {
            string from = fromKey.first;
            string to = toKey.first;
            long double weight = calculateEdgeWeight(sightings.getLatLong(fromKey), sightings.getLatLong(toKey));
            if (from != to && weight < threshold) {           /*sightings.getData("city", fromKey)*/
                addEdge(from, to, weight);
            }
        }
    }

    


}
long double Graph::calculateEdgeWeight(pair<long double, long double> start, pair<long double, long double> end) {
    long double edgeWeight = 0; //holds the distance in km of the two points
    //convert longitudes and latitudes to radians
    
    long double latitude_start = ((X_PI) / 180) * start.first;
    long double longitude_start = ((X_PI) / 180) * start.second;
    long double latitude_end = ((X_PI) / 180) * end.first;
    long double longitude_end = ((X_PI) / 180) * end.second;

    //Using the Haversine Formula
    long double dist_long = abs(longitude_end - longitude_start);
    long double dist_lat = abs(latitude_end - latitude_start);

    edgeWeight = 2 * asin(sqrt(pow(sin(dist_lat / 2), 2) + cos(latitude_start) * cos(latitude_end) * pow(sin(dist_long / 2), 2)));

    //convert into kilometers using the earth's radius in km is 6371
    edgeWeight = edgeWeight * 6371;

    return edgeWeight;

}

#endif //P3_GRAPH_H
