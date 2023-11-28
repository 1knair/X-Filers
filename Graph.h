#ifndef P3_GRAPH_H
#define P3_GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>
#include <utility>
#include <cmath>
#include <queue>
#include <tuple>
#include <algorithm>
#include "UFOSightings.h"
#define X_PI 3.14159265358979323846
#include <limits>


using namespace std;

struct Edge{
    string to; //city-state adjacent/neighbor node
    long double weight;	//distances from sighting to neighboring sighting
    pair<long double, long double> latLong; //latitude and longitude coordinates for testing

    //parametrized constructor
    Edge(string _to, long double _weight, pair<long double, long double> _latLong) : to(_to), weight(_weight), latLong(_latLong) {}
};

class Graph {
//private:
public:


    //key is the city-state from node, value is a tuple
    //first is the to nodes along with edge weights
    //next is to keep track of cumulative distances for the dijkstra algorithm
    //bool for keeping track if it has been visited
    //MARIA REMOVE BOOLEAN AND LONG DOUBLE FOR DISTANCE?
    unordered_map<string, tuple<vector<Edge>, long double, bool>> adjList;
    int numVertices = 0; //MARIA DO WE EVER USE THIS
    float threshold = 500; //distance in km to make an edge between two sightings

    /**
     * Calculates the edge weight (which is the distance) between the two nodes' latitude
     * and longitude using the Haversine formula.
     * Source(https://www.geeksforgeeks.org/program-distancesance-two-points-earth/)
     * @param start longitude and latitude of the starting node
     * @param end longitude and latitude of the ending node
     * @return double that corresponds to the edge weight
     */
    long double calculateEdgeWeight(pair<long double, long double> start, pair<long double, long double> end);

    /**
     * Adds the key to the graph where the key represents
     * the location of the UFO sighting.
     * @param key is a string that represents city-state
     */
    void addVertex(const string& key);

    /**
     * Adds an edge between two UFO sightings if the weight
     * is below the threshold. This means that the graph
     * could be disconnected.
     * @param from is the from city-state
     * @param to is the to city-state
     * @param weight is the distance between the from node and to node
     * @param latLong is the latitude and longitude of from
     */
    void addEdge(const string& from, const string& to, long double weight, pair<long double, long double> latLong);

    /**
     * Creates the graph which consists of sightings as vertices
     * and the edges being the distance in km between the nodes
     * @param sightings contains the sighting objects read from a csv file
     */
    void create(UFOSightings& sightings);

    /**
     * Finds the shortest paths using the Dijkstra algorithm.
     * Note that it calculates paths to all nodes, but we only return
     * th path from the source node to target node. This takes into account
     * the edge weights.
     * Source(https://www.geeksforgeeks.org/printing-paths-dijkstras-shortest-path-algorithm/)
     * @param start the source node
     * @param end the target node
     * @return vector of strings of city-state to get from start to end
     */
    vector<string> dijkstra(const string& start, const string& end);

    /**
     * Finds the shortest path using breadth first search. Note that
     * it calcultes the paths to all node, but we only return the path
     * from the source node to the target node
     * This does not take edge weights into account. Instead,
     * it keeps track of the number of edges.
     * Source(Discussion Slides on Algorithms)
     * @param start the source node
     * @param end the target node
     * @return vector of strings of city-state to get from start to end
     */
    vector<string> modifiedBFS(string start, string end);
};

//O(number of sightings)
void Graph::addVertex(const string& city){
    //Check if sighting is already in the graph because there are multiple sightings in same location
    if (adjList.find(city) == adjList.end()) {
        //initialize the cumulative distance of the sighting to the largest number
        //this is because we will use it in the dijkstra algorithm
        get<1>(adjList[city]) = { std::numeric_limits<long double>::max() };
        numVertices++; //add to the total number of vertices
    }
}

//O(number of sightings less than threshold)
void Graph::addEdge(const string& from, const string& to, long double weight, pair<long double, long double> latLong){
    Edge newEdge = Edge(to, weight, latLong);
    // Add the new edge to the start city's list of edges
    get<0>(adjList[from]).push_back(newEdge);

}

void Graph::create(UFOSightings& sightings) {
    vector<pair<string, string>> v = sightings.v;

    for (unsigned int i  = 0 ;  i < v.size(); i ++){
        auto currentSighting = v[i];
        //cout << v[i].first << endl;
        auto destSighting = v[i+1];
        string currentCity = sightings.m[currentSighting].city + '-' + sightings.m[currentSighting].state ;
        //   cout << currentCity << endl;
        addVertex(currentCity);

        string otherCity = sightings.m[destSighting].city + '-' + sightings.m[destSighting].state;

        if (currentCity != otherCity)
        {
            long double weight = calculateEdgeWeight(sightings.getLatLong(currentSighting), sightings.getLatLong(destSighting));

            if (weight < threshold)
                addEdge(currentCity, otherCity, weight, sightings.getLatLong(destSighting));

        }
    }
}



long double Graph::calculateEdgeWeight(pair<long double, long double> start, pair<long double, long double> end) {
    long double edgeWeight = 0.0; //holds the distance in km of the two points

    //convert longitudes and latitudes to radians
    long double latitude_start = ((X_PI) / 180) * start.first;
    long double longitude_start = ((X_PI) / 180) * start.second;
    long double latitude_end = ((X_PI) / 180) * end.first;
    long double longitude_end = ((X_PI) / 180) * end.second;

    //Using the Haversine Formula
    long double distances_long = abs(longitude_end - longitude_start);
    long double distances_lat = abs(latitude_end - latitude_start);
    edgeWeight = 2 * asin(sqrt(pow(sin(distances_lat / 2), 2) + cos(latitude_start) * cos(latitude_end) * pow(sin(distances_long / 2), 2)));

    //convert into kilometers using the earth's radius in km is 6371
    edgeWeight = edgeWeight * 6371;

    return edgeWeight;
}

//Note that key : vector<Edge>, distance, bool
vector<string> Graph::dijkstra(const string& start, const string& end)
{
    //vector<string> path;
    priority_queue<pair<long double, string>, vector<pair<long double, string>>, greater<>> pq;

    //initialize contents of the queue and cumulative distance
    pq.emplace(0.0, start);
    get<1>(adjList[start]) = 0.0; //distance to itself which would be the start node

    unordered_map<string, string> previous; //keeps track of the visited nodes

    while (!pq.empty())
    {
        pair<long double, string> curr = pq.top();
        string from = curr.second; //city-state of the from node
        long double currDistance = curr.first; //from to distance

        pq.pop();

        for (const Edge& edge : get<0>(adjList[from])) {
            string to = edge.to;  //city-state of the neighboring node of from
            long double distance = edge.weight;

            if (currDistance + distance < get<1>(adjList[to])) {
                get<1>(adjList[to]) = currDistance + distance; //update the cumulative distance
                pq.emplace(get<1>(adjList[to]), to);
                previous[to] = from; //add to the list of visited nodes
            }
        }
    }

    if (previous.find(end) != previous.end()) {  //if the end node is in the dijsktra shortest path
        string current = end; //set the current node to the ending node
        vector<string> shortestPath; //holds path from starting node to the ending node

        //starting from the target end node we are going backwards to find path back to source
        while (current != start) { //while we have not reached the source node
            shortestPath.push_back(current);
            current = previous[current];
       }
        shortestPath.push_back(start); //add the source node

        //since we were traversing the dijsktra shortest path from the end to the start
        //we need to reverse it so that it goes from source to target.
        reverse(shortestPath.begin(), shortestPath.end());

        return shortestPath;
    }
    else{   //this means that the source node has no path to target node
        return {"You can't drive to this UFO sighting :("};
    }
}

vector<string> Graph::modifiedBFS(string start, string end){
    vector<pair<string,bool>> visited;
    vector<string> path;

    queue<string> q; //to keep track of the current visited nodes
    q.push(start);
    visited.push_back(make_pair(start,true));
    path.push_back(start);

   while(!q.empty()) {
       string curr = q.front();
       q.pop();

       for (const Edge& edge : get<0>(adjList[curr])){
           //check if the edge is in the visited vector
           auto it = find_if(visited.begin(), visited.end(), [&edge](const pair<string,bool>& p){
               return p.first == edge.to;
           });

           if (it == visited.end()) { //if the edge is NOT found
               path.push_back(edge.to);
               //update that the visited vector to include that this edge has been visited
               visited.push_back(make_pair(edge.to,true));
               q.push(edge.to);

               if(edge.to == end){
                   return path;
               }
           }
       }
   }
   return {"You can't drive to this UFO sighting :("};
}





#endif //P3_GRAPH_H
