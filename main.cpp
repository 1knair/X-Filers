#include "iostream"
#include "UFOSightings.h"
#include "Graph.h"
using namespace std;

int main()
{	
	Graph graph;
	UFOSightings sightings;

	sightings.parseFile("./ufo_sighting_data.csv", 50);
	graph.create(sightings);


	for (pair<string, string>& key : sightings.v) {
		/*cout << "City: " << sightings.m[key].city << endl;
		cout << "Date/Time: " << sightings.m[key].date_time << endl;
		cout << "Length: " << sightings.m[key].length << endl;
		cout << "Desc: " << sightings.m[key].desc << endl;
		cout << "Coords: " << sightings.m[key].coords.first << ", " << sightings.m[key].coords.first << endl;*/
	}
	//go here 4/29/2005 21:00,cary,nc,us,light,90,90 sec,((NUFORC Note:  Missile launch at 2055 hrs (EDT).  PD))  Two small yellow-white lights moving parallel to horizon; fuzzy ring of light,5/11/2005,35.7913889,-78.7813889

}
