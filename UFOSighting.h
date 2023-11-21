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
        string city, date_Time, desc, shape, length;
        pair<double, double> latLong;
        Sighting(double _latitude, double _longitude, string& _city, string& _dateTime, string& _desc, string& _length):
                latLong(_latitude, _longitude), city(_city), date_Time(_dateTime), desc(_desc), length(_length){}
    };
    vector<string> cityDates;
public:
    vector<string> v;						//vector of city-date keys for fast traversal
    /**
        Example data insertion
        in parseFile() ->
        for each sighting in the file
            city column = city
            dateTime column = Date1-Time1
            vector<pair<string, string>> key1 = {{"City1", "Date1-Time1"}};

            Sighting sighting1(40.7128, -74.0060, "City1", "Date1-Time1", "Description1", "Length1");
            m[key1] = sighting1;
     */
     //keys: city, dates/time, values: Sighting structs
    unordered_map<vector<pair<string, string>>, Sighting(double _latitude, double _longitude, string& _city, string& _dateTime, string& _desc, string& _length)> m;

    void parseFile(string& filePath);				//read CSV; construct sightings; fill map+vec
    vector<string> getCityDates();		//	return city date
    string getData(const string& data, const string& key);		// general getter function for map lookup
};

void UFOSighting::setLatitude(const string& key, double latitude) {
    m[key].latLong.first = latitude;
}

void UFOSighting::setLongitude(const string& key, double longitude) {
    m[key].latLong.second = longitude;
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

// change to all
pair<long double, long double> UFOSighting::getLatLong(const string& key)
{
    return m[key].latLong;
}
string UFOSighting::getData(const string& data, const string& key)
{
    if(data == "dateTime")
        return m[key].date_Time;
    if(data == "desc")
        return m[key].des;
    if(data == "shape")
        return m[key].shape;
    if(data == "length")
        return m[key].length;
    if(data == "city")
        return m[key].city;
    if(data == "latLong")
        return m[key].latLong;
}

vector<string> UFOSighting::getCityDates(){
    return cityDates;
}

void UFOSighting::parseFile(string& filePath)
{
    /*
     * deserialize?
     * readfile?
     *
     * add to cityDates vector
     */
}


#endif //P3_UFOSIGHTING_H
