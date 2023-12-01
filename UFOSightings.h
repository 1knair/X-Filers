//
// Created by Brianna Yanqui on 11/20/23.
//
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <utility>
#include <fstream>
#include <sstream>
using namespace std;

#ifndef P3_UFOSIGHTING_H
#define P3_UFOSIGHTING_H



//CITY-DATES = KEYS
class UFOSightings{
private:

public:
    struct Sighting {
        string state, city, date_time, desc, shape, length;
        pair<long double, long double> coords;
        Sighting() : state(""), city(""), date_time(""), desc(""), shape(""), length(""), coords({ 0.0, 0.0 }) {}

        Sighting(string & _state, string& _city, string& _dateTime, string& _desc, string& _length, pair<long double, long double> _coords)
                : state(_state), city(_city), date_time(_dateTime), desc(_desc), length(_length), coords(_coords) {}

    };

    struct HashPairString {
        size_t operator()(const pair<string, string>& p) const {
            size_t h1 = hash<string>{}(p.first);
            size_t h2 = hash<string>{}(p.second);
            return h1 ^ (h2 << 1); //xor
        }
    };

    vector<pair<string, string>> v; //vector of keys for fast traversal this is the city state
    unordered_map<pair<string, string>, Sighting, HashPairString> m; //map of keys

    //read CSV; construct sightings; fill map+vec
    void parseFile(string filePath, int n); //does n lines

    //Getters
    vector<pair<string, string>> getCityDates();
    string getData(const string field, const pair<string, string>& key);
    pair<long double, long double> getLatLong(pair<string, string> key);

};


string UFOSightings::getData(const string field, const pair<string, string>& key)
{
    if(field == "dateTime")
        return m[key].date_time;
    if(field == "desc")
        return m[key].desc;
    if(field == "shape")
        return m[key].shape;
    if(field == "length")
        return m[key].length;
    if(field == "city")
        return (m[key].city + m[key].state);
    if(field == "state")
        return m[key].state;
    if (field == "latitude")
        return to_string(m[key].coords.first);
    if (field == "longitude")
        return to_string(m[key].coords.second); //Or long double getCoords()
    else
        return "-1";
}

// O(1)
pair<long double, long double> UFOSightings::getLatLong(pair<string, string> key)
{
    return m[key].coords;
}
/*
void UFOSighting::setLatitude(const string& key, double latitude) {
    m[key].coords.first = latitude;
}

void UFOSighting::setLongitude(const string& key, double longitude) {
    m[key].coords.second = longitude;
}

void UFOSighting::setCity(const string& key, const string& city) {
    m[key].city = city;
}

void UFOSighting::setTime(const string& key, const string& time) {
    m[key].time = time;
}

void UFOSighting::setDescription(const string& key, const string& desc) {
    m[key].desc = desc;
}

void UFOSighting::setDescription(const string& key, const string& desc) {
    m[key].desc = desc;
}

void UFOSighting::setLength(const string& key, const string& length) {
    m[key].length = length;
}
*/

vector<pair<string, string>> UFOSightings::getCityDates()
{
    return v;
}

void UFOSightings::parseFile(string filePath, int n)
{
    ifstream fs;

    fs.open(filePath);
    if (!fs.is_open()) {
        cout << "CAN'T OPEN";
        return;
    }

    string line;
    int count = -1; //

    while (getline(fs, line, '\r')) { //wow \r is crazy
        count++;
        if (count == 0)
            continue;
        stringstream ss(line);
        string field;
        string fields[11];
        for (int i = 0; i < 11; i++) {
            if (i < 10)
                getline(ss, field, ',');
            else //Last field in line
                getline(ss, field, ' ');
            fields[i] = field;
            //cout << field << "|"; //
        }
        //Date_time,city,state/proxvince,country,UFO_shape,length_of_encounter_seconds,described_duration_of_encounter,description,date_documented,latitude,longitude
        string date_time = fields[0];
        string city = fields[1];
        string state = fields[2];
        string desc = fields[7];
        string length = fields[5];
        long double lati = stold(fields[9]);
        long double longi = stold(fields[10]);

        pair<long double, long double> coords = { lati, longi };
        pair<string, string> key = { city, state };
        v.push_back(key);
        m[key] = Sighting(state, city, date_time, desc, length, coords);
        if (count == n)
            break;
    }
}


#endif //P3_UFOSIGHTING_H
