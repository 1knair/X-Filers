#include <iostream>
#include <UFOSightings.h>
#include <Graph.h>
using namespace std;

int main() {
    UFOSightings() sightings;
	sightings.parseFile("ufo_sighting_data.csv");
	Graph graph;
    string start, target; //Keys
	
    graph.create(sightings.getCityDates());
    
    //UI stuff for input selection
    cin >> start; //Get start key
    cin >> target; //Get end key
    //If we want to input weight, do it here, pass to graph

	startCity = getCity(start)
    targetCity = getCity(target); //Get city data from keys

    //UI stuff for algo selection
    Graph.dijkstra(startCity, targetCity);
    Graph.modifiedBFS(startCity, targetCity);

    //UI stuff to display string
    for (const string& city : graph.getPath()) {
        cout << city << " ";
    }

    return 0;

}
