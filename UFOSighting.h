//
// Created by Brianna Yanqui on 11/20/23.
//

#ifndef P3_UFOSIGHTING_H
#define P3_UFOSIGHTING_H


class UFOSighting {
    struct Sighting{
        string city, time, desc, shape, length
        pair<double> lat, long;
        UFOSighting(double lat, double long, string )
    };

    vector<string> v							//vector of city-date keys for fast traversal
    u_map<sighting> m						//keys: city-dates, values: Sighting structs

    void parseFile(string filePath)				//read CSV; construct sightings; fill map+vec
    vector<string> getCityDates()			//	get vector of city-date keys
    string getData(string key)					// general getter function for map lookup
    string getCity(string key)

};


#endif //P3_UFOSIGHTING_H
