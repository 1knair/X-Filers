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

class Graph {
//private:
public:
    struct Edge {
        string to;
        long double weight;	//distancesance

        Edge(string _to, long double _weight) : to(_to), weight(_weight) {}
    };

    unordered_map<string, tuple<vector<Edge>, long double, bool>> adjList;
    int numVertices = 0;

    float threshold = 600; //km
    /**
     * Calculates the edge weight (which is the distancesance) between the two nodes' latitude
     * and longitude using the Haversine formula.
     * Source(https://www.geeksforgeeks.org/program-distancesance-two-points-earth/)
     * @param start longitude and latitude of the starting node
     * @param end longitude and latitude of the ending node
     * @return double that corresponds to the edge weight
     */
    long double calculateEdgeWeight(pair<long double, long double> start, pair<long double, long double> end);
    void addVertex(string key);					    
    void addEdge(string from, string to, long double weight);	       

public:
    void create(UFOSightings& sightings);

    /**
     * Source(https://www.geeksforgeeks.org/printing-paths-dijkstras-shortest-path-algorithm/)
     * @param start
     * @param end
     * @return
     */
    double dijkstra(string start, string end);
    vector<string> modifiedBFS(string start, string end);
};

//O(number of sightings)
void Graph::addVertex(string city){
    //Check if it is in the graph
    //calculateEdgeWeight();
   if (adjList.find(city) == adjList.end()) { //For duplicate
       get<1>(adjList[city]) = { std::numeric_limits<long double>::max() };
       numVertices++;
    }
}

//O(
void Graph::addEdge(string from, string to, long double weight){
    Edge newEdge = Edge(to, weight);
    // Add the new edge to the start city's list of edges
    get<0>(adjList[from]).push_back(newEdge);
    
    //cout << "Added edge from " << from << " to " << to << '\n' << weight << endl;
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
    long double edgeWeight = 0; //holds the distancesance in km of the two points
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
//key : vector<Edge>, distance, bool
double Graph::dijkstra(string start, string end) {
    priority_queue<pair<long double, string>, vector<pair<long double, string>>, greater<pair<long double, string>>> pq;
    pq.push(make_pair(0.0, start));
    get<1>(adjList[start]) = 0.0;

    while (!pq.empty()) {
        pair<long double, string> curr = pq.top();
        string u = curr.second;
        pq.pop();

        for (const Edge& edge : get<0>(adjList[u])) {
            string to = edge.to;
            long double distance = edge.weight;

            if (get<1>(adjList[u]) + distance < get<1>(adjList[to])) {
                get<1>(adjList[to]) = get<1>(adjList[u]) + distance;
                pq.push(make_pair(get<1>(adjList[to]), to));
            }
        }
    }

    return get<1>(adjList[end]);
}

vector<string> Graph::modifiedBFS(string start, string end){
    //START HERE!!! CURRENTLY PRINTING EMPTY STRINGS
    //int minedges(int [][]edges, int u, int v, int n)
    vector<pair<string,bool>> visited(adjList.size(),make_pair("",false));
    //vector<pair<string,int>> distance(adjList.size(),make_pair("",0));
    vector<string> distance(adjList.size(),"");

    int index = 1; //counter to fill the distance array with pairs
    queue<string> q; //to keep track of the current visited nodes
    q.push(start);
    visited[0] = make_pair(start, true);
    distance[0] = start;

   while(!q.empty()) {
       string curr = q.front();
       q.pop();

       for (const Edge& edge : get<0>(adjList[curr])){
           //check if the edge is in the visited vector
           auto it = find_if(visited.begin(), visited.end(), [&edge](const pair<string,bool>& p){
               return p.first == edge.to;
           });

           if (it == visited.end()) { //if the edge is NOT found
               //update the distance this holds the BFS order when we traverse the graph
               //distance[index].first = edge.to;
               //distance[index].second = distance[index].second + 1; //add one to the distance
               distance[index] = edge.to;
               //update that the visited vector to include that this edge has been visited
               visited[index+1].first = edge.to;
               visited[index+1].second = true;
               q.push(visited[index+1].first );
               index++;
           }
       }
   }
   return distance;
}





#endif //P3_GRAPH_H
//313.204