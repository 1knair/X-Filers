#include "iostream"
#include "UFOSightings.h"
#include "Graph.h"
#include <matplot/matplot.h>
#include <utility>
#include <cmath>

using namespace std;
void output(Graph& graph, UFOSightings& sightings, vector<string> path, int algo) {
    ofstream fs("./output.txt");
    if (!fs.is_open()) {
        cout << "Output file not found" << endl;
        return;
    }

    if (algo == 1) {
        cout << "SHORTEST PATH USING BFS" << endl;
        fs << "SHORTEST PATH USING BFS" << endl;
    }
    if (algo == 2) {
        cout << "SHORTEST PATH USING DIJKSTRA'S ALGORITHM" << endl;
        fs << "SHORTEST PATH USING DIJKSTRA'S ALGORITHM" << endl;
    }
    cout << endl;
    fs << endl;
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i];
        fs << path[i];
        if (i < path.size() - 1) {
            cout << " -> ";
            fs << " -> ";
        }
        else {
            cout << endl;
            fs << endl;
            cout << setw(20) << setfill('_') << "" << endl;
            fs << setw(200) << setfill('_') << "" << endl;
        }
    }

    for (auto cityState : path) {
        for (auto cityDate : sightings.v) {
            if (cityState == sightings.getData("city", cityDate) + "-" + sightings.getData("state", cityDate)) {
                cout << sightings.getData("city", cityDate) << ", " << sightings.getData("state", cityDate) << endl << endl;
                fs << sightings.getData("city", cityDate) << ", " << sightings.getData("state", cityDate) << endl << endl;

                cout << "Date and Time: " << sightings.getData("dateTime", cityDate) << endl;
                fs << "Date and Time: " << sightings.getData("dateTime", cityDate) << endl;

                cout << "Description: " << sightings.getData("desc", cityDate) << endl;
                fs << "Description: " << sightings.getData("desc", cityDate) << endl;

                cout << "Length: " << sightings.getData("length", cityDate) << endl;
                fs << "Length: " << sightings.getData("length", cityDate) << endl;

                cout << "Latitude: " << sightings.getData("lat", cityDate) << endl;
                fs << "Latitude: " << sightings.getData("lat", cityDate) << endl;

                cout << "Longitude: " << sightings.getData("long", cityDate) << endl;
                fs << "Longitude: " << sightings.getData("long", cityDate) << endl;

                break;
            }
        }
        cout << setw(20) << setfill('_') << "" << endl;
        fs << setw(200) << setfill('_') << "" << endl;
    }
    fs.close();
}
int main() {

    using namespace matplot;
    Graph graph; //create empty graph
    UFOSightings sightings; //create container for sightings

    //Fill the graph with sightings
    sightings.parseFile("./ufo_sighting_data.csv", 80332);
    graph.create(sightings);

    //Ask user for the starting and ending location and for the type of path
    string start = "";
    string end = "";
    int path_type = 0;

    cout << "Enter the city-state (eg. houston-tx) of the starting UFO sighting" << endl;
    getline(cin, start);
    cout << "Enter the city-state (eg. white plains-ny) of the target/destination UFO sighting" << endl;
    getline(cin, end);
    cout << "Would you like to take the scenic route? Type 1 for yes, 2 for no" << endl;
    cin >> path_type;

    //BFS
    if (path_type == 1)
    {
        vector<string> bfs = graph.modifiedBFS(start, end);
        vector<pair<long double, long double>> coords;
        output(graph, sightings, bfs, path_type);

        for(auto location: bfs)
        {
            size_t pos = location.find('-');
            string city = location.substr(0, pos);
            string state = location.substr(pos + 1);
            pair<string, string> key = make_pair(city, state);

            coords.push_back(sightings.getLatLong(key));
        }

        // Source(https://alandefreitas.github.io/matplotplusplus/plot-types/geography/geoplot/)
        for(unsigned int i = 0; i < coords.size() - 1; i++) {
            if (i == 0 || i == coords.size() - 2)
                geoplot(vector{coords[i].first, coords[i + 1].first}, vector{coords[i].second, coords[i + 1].second},
                        "g-*");

            else
                geoplot(vector{coords[i].first, coords[i + 1].first}, vector{coords[i].second, coords[i + 1].second},
                        "g-*");
            hold(on);

            geolimits(13.8183, 49.4595, -135.207, -44.8848);
            show();

        }
    }

    //Dijsktra
    if (path_type == 2)
    {
        vector<string> djkstr = graph.dijkstra(start, end);
        vector<pair<long double, long double>> coords;

        output(graph, sightings, djkstr, path_type);


        for(auto location: djkstr)
        {
            size_t pos = location.find('-');
            string city = location.substr(0, pos);
            string state = location.substr(pos + 1);
            pair<string, string> key = make_pair(city, state);

            coords.push_back(sightings.getLatLong(key));
        }

        // Source (https://alandefreitas.github.io/matplotplusplus/plot-types/geography/geoplot/)
        for(unsigned int i = 0; i < coords.size() - 1; i++) {
            if (i == 0 || i == coords.size() - 2)
                geoplot(vector{coords[i].first, coords[i + 1].first}, vector{coords[i].second, coords[i + 1].second},
                        "g-*");

            else
                geoplot(vector{coords[i].first, coords[i + 1].first}, vector{coords[i].second, coords[i + 1].second},
                        "g-*");
            hold(on);

            geolimits(13.8183, 49.4595, -135.207, -44.8848);
            show();

        }

    }
}
