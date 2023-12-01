#include "iostream"
#include "UFOSightings.h"
#include "Graph.h"
#include <utility>
#include <cmath>

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

    //Ask user for the starting and ending location and for the type of path
    string start = "";
    string end = "";
    int path_type = 0;

    cout << "Enter the city-state (eg. houston-tx) of the starting UFO sighting" << endl;
    getline(cin,start);
    cout << "Enter the city-state (eg. white plains-ny) of the target/destination UFO sighting" << endl;
    getline(cin,end);
    cout << "Would you like to take the scenic route? Type 1 for yes, 2 for no" << endl;
    cin >> path_type;

    if (path_type == 1) {//BFS
        //Finding the shortest path using breadth first search. Shortest path from source node to target node
        vector<string> bfs = graph.modifiedBFS(start,end);
        vector<vector<long double>> coords;
        for(auto sighting : bfs) {
            cout << sighting << "->";
        }

        //attempt to path from start to end using geoplot
//        for(auto location : bfs) {
//            //sighting is formatted as city-state
//            size_t pos = location.find('-');
//            string city = location.substr(0, pos);
//            string state = location.substr(pos + 1);
//            //make a pair where the first is the city and then state
//            pair<string,string> key = make_pair(city,state);
//            vector<long double> coord {};
//            //stores lat long of one sighting
//            coord.push_back(sightings.getLatLong(key).first);
//            coord.push_back(sightings.getLatLong(key).second);
//            //store the coord vector into another vector that holds the lat long vectors of size 2
//            coords.push_back(coord);
//        }
//
//        //Display path on map
//        //Source(https://alandefreitas.github.io/matplotplusplus/plot-types/geography/geoplot/)
//        //{{lat1,long1},{lat2,long2},...}
//        for(unsigned int i = 0; i < coords.size(); i++) {
//            vector<long double> initial = coords[i];
//            vector<long double> next = coords[i+1];
//            //geoplot(vector{initial[1], next[1]}, vector{initial[2], next[2]}, "g-*" );
//            //store vector into a json file
//            //read json file as python script
//            //use matplotlib in python
//            //run the python file separately
//            //just use command line to run all of the code
//        }
    }

    if (path_type == 2) {//Dijsktra
        //Finding the shortest path using dijsktra. Shortest path from source node to target node considering edge weights
        vector<string> djkstr = graph.dijkstra(start,end);
        for(auto sighting : djkstr) {
            cout << sighting << "->";
        }
    }


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
