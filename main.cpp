#include "iostream"
#include "UFOSightings.h"
#include "Graph.h"
#include <utility>
using namespace std;

int main()
{	
	Graph graph; //create empty graph
    cout << "Graph container created successfully" << endl;
	UFOSightings sightings; //create container for sightings
    cout << "Sighting container created successfully" << endl;

    //Fill the graph with sightings
	sightings.parseFile("./ufo_sighting_data.csv", 80332);
    cout << "Parse file and sighting objects created successfully" << endl;
    graph.create(sightings);
    cout << "Graph created successfully" << endl;

    //This will be the user input from starting ufo sighting and target(end) ufo sighting
    string start = "houston-tx";
    string end = "white plains-ny";

    cout << ""<< endl;

    //Finding the shortest path using dijsktra. Shortest path from source node to target node considering edge weights
    vector<string> djkstr = graph.dijkstra(start,end);
    for(auto city : djkstr) {
        cout << city << "->";
    }

    cout << endl << "--------------------------------------" << endl;
    //Finding the shortest path using breadth first search. Shortest path from source node to target node
    vector<string> bfs = graph.modifiedBFS(start,end);
    for(auto city : bfs) {
        cout << city << "->";
    }
    //testing the graph and sighitings object
	//if (graph.adjList.find("houston") != graph.adjList.end()) cout << "Found";
	//cout << graph.calculateEdgeWeight(make_pair(29.7630556, -95.3630556), make_pair(41.523427, -73.646795));
    // cout << graph.calculateEdgeWeight(make_pair(29.7630556, -95.3630556), make_pair(41.523427, -73.646795));
    // for (pair<string, string>& key : sightings.v) {
		/*cout << "City: " << sightings.m[key].city << endl;
		cout << "Date/Time: " << sightings.m[key].date_time << endl;
		cout << "Length: " << sightings.m[key].length << endl;
		cout << "Desc: " << sightings.m[key].desc << endl;
		cout << "Coords: " << sightings.m[key].coords.first << ", " << sightings.m[key].coords.first << endl;*/
	//}
    //Vsit this UFO sighting
	//go here 4/29/2005 21:00,cary,nc,us,light,90,90 sec,((NUFORC Note:  Missile launch at 2055 hrs (EDT).  PD))  Two small yellow-white lights moving parallel to horizon; fuzzy ring of light,5/11/2005,35.7913889,-78.7813889

}
