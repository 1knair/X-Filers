#include "iostream"
#include "UFOSightings.h"
#include "Graph.h"
#include <utility>
using namespace std;

int main()
{	
	Graph graph;
	UFOSightings sightings;

	sightings.parseFile("./ufo_sighting_data.csv", 80332);
	graph.create(sightings);
	string start = "houston";
	string end = "dallas";
    cout << "hi" << endl;
	//cout << graph.dijkstra(start, end) << endl;
    vector<string> bfs = graph.modifiedBFS(start,end);
    for(auto city : bfs) {
        cout << city << "->";
    }
	//if (graph.adjList.find("houston") != graph.adjList.end()) cout << "Found";
	//cout << graph.calculateEdgeWeight(make_pair(29.7630556, -95.3630556), make_pair(41.523427, -73.646795));
//	cout << graph.calculateEdgeWeight(make_pair(29.7630556, -95.3630556), make_pair(41.523427, -73.646795));
//	for (pair<string, string>& key : sightings.v) {
		/*cout << "City: " << sightings.m[key].city << endl;
		cout << "Date/Time: " << sightings.m[key].date_time << endl;
		cout << "Length: " << sightings.m[key].length << endl;
		cout << "Desc: " << sightings.m[key].desc << endl;
		cout << "Coords: " << sightings.m[key].coords.first << ", " << sightings.m[key].coords.first << endl;*/
	//}
	//go here 4/29/2005 21:00,cary,nc,us,light,90,90 sec,((NUFORC Note:  Missile launch at 2055 hrs (EDT).  PD))  Two small yellow-white lights moving parallel to horizon; fuzzy ring of light,5/11/2005,35.7913889,-78.7813889

}
