//
// Created by Brianna Yanqui on 11/20/23.
//

#ifndef P3_GRAPH_H
#define P3_GRAPH_H


class Graph {
    struct Edge
            string end							destination
    double weight						distance

            vector<string> path 						cities in shortest path
            u_map<string, vector<Edge>> adjList			key: city-date; value: vector of Edges to neighbors

    double euclideanDist(pair<double>)
    addVertex(string city)					add each key to map if it doesn’t already exist
    addEdge(string end, weight)					if dist<threshold, add Edge to adjList[start]

            void create(vector<string>)					for each Sighting in v, getCity(), getData()
    double dijkstra(string start string end)		add shortest path keys to class member path
    double modifiedBFS(string start, string end)	add shortest path keys to class member path
    getPath()								get cities in shortest path
};


#endif //P3_GRAPH_H
