/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dbLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#ifndef DSA191_A1_DBLIB_H
#define DSA191_A1_DBLIB_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>
#include <math.h>

#include "dsaLib.h"

/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */

struct TCity {
    // The structure to store city information
	int id;
	string name;
	string coords;
	/*int start_year;
	string url_name;
	string country;
	string country_state;
	*/

};

struct TLine {
    // The structure to store line information
	int id;
	int city_id;
	string name;
	/*string color;
	string url_name;
	int system_id;
	int transport_mode_id;
	*/
};

struct TStationLines {
	// The structure to store line information
	int id;
	int station_id;
	int line_id;
	int city_id;
};

struct TStations {
	// The structure to store line information
	int id;
	string name;
	string geomatry;
	/*int buildstart;
	int opening;
	int closure;*/
	int city_id;
};
/*
struct TSystems {
	// The structure to store line information
	int id;
	int city_id;
	string name;
};
*/

struct TTrack {
    // The structure to store track information
	int id;
	string geomatry;
	int buildstart;
	int opening;
	/*int closure;
	int length;*/
	int city_id;
};

struct TTrackLines {
	// The structure to store track information
	int id;
	int section_id;
	int line_id;
	int city_id;
};


class TDataset {
    // This class can be a container that help you manage your tables
public:
	L1List<TCity>* city=new L1List<TCity>;
	L1List<TLine>* line = new L1List<TLine>;
	L1List<TStationLines>* station_lines = new L1List<TStationLines>;
	L1List<TStations>* station = new L1List<TStations>;
	//L1List<TSystems>* systems = new L1List<TSystems>;
	L1List<TTrack>* track = new L1List<TTrack>;
	L1List<TTrackLines>* track_lines = new L1List<TTrackLines>;
};

// Please add more or modify as needed
bool compareString(string s, string t);
int findCityID(L1List<TCity>* city, string s);
int stoint(string s);
void loadNumber(string s, int& i, bool e, int& d);
void loadString(string s, int& i, bool e, string& d);
void fastforward(string s, int& i, bool e);

void LoadData(void* &p);
void ReleaseData(void* &p);

#endif //DSA191_A1_DBLIB_H
