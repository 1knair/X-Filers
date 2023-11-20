//
// Created by Brianna Yanqui on 11/20/23.
//
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;
#ifndef P3_UFOSIGHTING_H
#define P3_UFOSIGHTING_H


class UFOSighting{
private:
    struct Sighting{
        string city, time, desc, shape, length;
        double lat;
        double longitude;
        Sighting(double _latitude, double _longitude, string& _city, string& _time, string& _desc, string& _length):
                lat(_latitude), longitude(_longitude), city(_city), time(_time), desc(_desc), length(_length){}
    };

public:
    vector<string> v;						//vector of city-date keys for fast traversal
    unordered_map<vector<string>, Sighting(double lat, double long, std::string)> m;	//keys: city-dates, values: Sighting structs

    void parseFile(string& filePath);				//read CSV; construct sightings; fill map+vec
    vector<string> getCityDates();		//	get vector of city-date keys
    string getData(string& key);					// general getter function for map lookup
    string getCity(string& key);

};

string UFOSighting::getData(string& key) {
    return string();
}

string UFOSighting::getCity(string& key) {
    return string();
}

vector<string> UFOSighting::getCityDates() {
    return vector<string>();
}

void UFOSighting::parseFile(string& filePath) {

}


#endif //P3_UFOSIGHTING_H
