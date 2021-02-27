/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dbLib.cpp
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>
#include <math.h>
#include "dbLib.h"

/* TODO: You can implement methods, functions that support your data structures here.
 * */
using namespace std;


bool compareString(string s, string t) {
	if (s.length() != t.length()) return false;
	else {
		int k = s.length();
		for (int i = 0; i < k; i++)
			if (s[i] != t[i]) return false;
		return true;
	}
}

int stoint(string s) {
	int result=0;
	int i = s.length()-1;
	int base = 1;
	while (i >= 0&&s[i]!='-') {
		result += int(s[i]-'0')*base;
		base *= 10;
		i--;
	}
	if (s[0] == '-') return -1 * result;
	else return result;
}
void loadNumber(string s, int& i,bool e, int& d) {
	string id;
	char c = ',';
	if (e) c = '\0';
	while (s[i] != c) {
		id = id + s[i];
		i++;
	}
	i++;
	d = stoint(id);
}

void loadString(string s, int& i, bool e, string& d) {
	string id;
	bool flag = false;
	char c = ',';
	if (e) c = '\0';
	if (s[i]==34) {
		i++;
		flag = true;
		c = 34;
	}
	while (s[i] != c) {
		id = id + s[i];
		i++;
	}
	i++;
	if (flag) i++;
	d = id;
}

void fastforward(string s, int& i, bool e) {
	bool flag = false;
	char c = ',';
	if (e) c = '\0';
	if (s[i] == 34) {
		i++;
		flag = true;
		c = 34;
	}
	while (s[i] != c) {
		i++;
	}
	i++;
	if (flag) i++;
}

void LoadData(void* &p) {
	TDataset *a= new TDataset;
	ifstream f;
	string s;

	//Load cities;
	f.open("cities.csv", ios::in);
	getline(f, s);
	while (!f.eof()) {
		TCity cities;
		string temp;
		getline(f, temp, ',');
		cities.id = stoint(temp);
		getline(f, cities.name, ',');
		getline(f, s);
		/*int i = 0;
		
		loadNumber(s, i, false, cities.id);
		loadString(s, i, false, cities.name);
		loadString(s, i, false, cities.coords);
		loadNumber(s, i, false, cities.start_year);
		loadString(s, i, false, cities.url_name);
		loadString(s, i, false, cities.country);
		loadString(s, i, false, cities.country_state);
		*/
		L1Item<TCity>* q = new L1Item<TCity>(cities);
		//q->data = city;
		a->city->push_back(q);
	}
	f.close();
	//cout << a->city->at(0).id << '+';

	//Load lines;
	f.open("lines.csv", ios::in);
	getline(f, s);
	while (!f.eof()) {
		TLine line;
		string temp;
		getline(f, temp, ',');
		line.id = stoint(temp);
		getline(f, temp, ',');
		line.city_id = stoint(temp);
		//getline(f, temp, ',');
		getline(f, s);
		
		/*		int i = 0;

		loadNumber(s, i, false, line.id);
		loadNumber(s, i, false, line.city_id);
		loadString(s, i, false, line.name);
		loadString(s, i, false, line.url_name);
		loadString(s, i, false, line.color);
		loadNumber(s, i, false, line.system_id);
		loadNumber(s, i, true , line.transport_mode_id);
*/
		L1Item<TLine>* q = new L1Item<TLine>(line);
		//q->data = city;
		a->line->push_back(q);
	}
	f.close();
	//cout << a->line->at(1343).id << '+';

	//Load station_lines;
	f.open("station_lines.csv", ios::in);
	getline(f, s);
	while (!f.eof()) {
		TStationLines station_lines;
		string temp;
		getline(f, temp, ',');
		station_lines.id = stoint(temp);
		getline(f, temp, ',');
		station_lines.station_id = stoint(temp);
		getline(f, temp, ',');
		station_lines.line_id = stoint(temp);
		getline(f, s);
/*
		int i = 0;
		
		loadNumber(s, i, false, station_lines.id);
		loadNumber(s, i, false, station_lines.station_id);
		loadNumber(s, i, false, station_lines.line_id);
		//loadNumber(s, i, false, station_lines.city_id);
		*/
		L1Item<TStationLines>* q = new L1Item<TStationLines>(station_lines);
		//q->data = city;
		a->station_lines->push_back(q);
	}
	f.close();
	//cout << a->station_lines->at(1).line_id << '+';

		//Load stations;
	f.open("stations.csv", ios::in);
	getline(f, s);
	while (!f.eof()) {
		TStations stations;
		string temp;
		getline(f, temp, ',');
		stations.id = stoint(temp);
		getline(f, temp, ',');
		//cout << temp << endl;
		if (temp[0] == '"' && temp[temp.length() - 1] != '"') {
			string temp1;
			for (int i = 1; i < temp.length(); i++)
				if (i < temp.length())
					stations.name = stations.name + temp[i];
			getline(f, temp1, '"');
			stations.name = stations.name + ',';
			for (int i = 0; i < temp1.length(); i++)
				if (i < temp1.length())
					stations.name = stations.name + temp1[i];
			getline(f, temp1, ',');
		}
		else if (temp[0] == '"')
			for (int i = 1; i < temp.length() - 1; i++)
				stations.name = stations.name + temp[i];
		else stations.name = temp;
		getline(f, stations.geomatry, ',');
		getline(f, temp, ',');
		getline(f, temp, ',');
		getline(f, temp, ',');
		getline(f, temp);
		stations.city_id = stoint(temp);
		/*
		int i = 0;
		
		loadNumber(s, i, false, stations.id);
		loadString(s, i, false, stations.name);
		loadString(s, i, false, stations.geomatry);
		fastforward(s, i, false);
		fastforward(s, i, false);
		fastforward(s, i, false);
		loadNumber(s, i, true , stations.city_id);
		*/
		L1Item<TStations>* q = new L1Item<TStations>(stations);
		//q->data = city;
		a->station->push_back(q);
	}
	f.close();
	//cout << a->station->at(1).name << '+';
/*
	//Load systems;
	f.open("systems.csv", ios::in);
	getline(f, s);
	while (getline(f, s)) {
		TSystems systems;
		int i = 0;

		loadNumber(s, i, false, systems.id);
		loadNumber(s, i, false, systems.city_id);
		loadString(s, i, true , systems.name);
		
		L1Item<TSystems>* q = new L1Item<TSystems>(systems);
		//q->data = city;
		a->systems->push_back(q);
	}
	f.close();
	//cout << a->systems->at(0).id << '+';
	*/
		//Load systems;
	/*
	f.open("track_lines.csv", ios::in);
	getline(f, s);
	while (!f.eof()) {
		TTrackLines track_lines;
		string temp;
		getline(f, temp, ',');
		track_lines.id = stoint(temp);
		getline(f, temp, ',');
		track_lines.section_id = stoint(temp);
		getline(f, temp, ',');
		track_lines.line_id = stoint(temp);
		getline(f, s);
		int i = 0;
		loadNumber(s, i, false, track_lines.id);
		loadNumber(s, i, false, track_lines.section_id);
		loadNumber(s, i, false, track_lines.line_id);
		fastforward(s, i, false);
		fastforward(s, i, false);
		loadNumber(s, i, true , track_lines.city_id);

		L1Item<TTrackLines>* q = new L1Item<TTrackLines>(track_lines);
		//q->data = city;
		a->track_lines->push_back(q);

	}
	f.close();
	//cout << a->track_lines->at(3).id << '+';
	*/
	//Load tracks;
	f.open("tracks.csv", ios::in);
	getline(f, s);
	while (!f.eof()) {
		TTrack tracks;
		string temp;
		getline(f, temp , ',');
		tracks.id = stoint(temp);
		getline(f, tracks.geomatry, ')');
		getline(f, s);
	
		/*fastforward(s, i, false);
		fastforward(s, i, false);
		fastforward(s, i, false);
		fastforward(s, i, false);
		loadNumber(s, i, true , tracks.city_id);
		*/
		L1Item<TTrack>* q = new L1Item<TTrack>(tracks);
		//q->data = city;
		a->track->push_back(q);
	}
	f.close();
	//cout << a->track->at(1).id << '+';
	a->city->removeLast();
	a->line->removeLast();
	a->station->removeLast();
	a->station_lines->removeLast();
	a->track->removeLast();
	a->track_lines->removeLast();
	//cout << a->line->at(a->line->getSize()-1).id << endl;
	p = a;
}
void ReleaseData(void*& p) {
	/*TDataset* a = new TDataset;
	a = (TDataset*)p;

	delete a->city;
	a->city = NULL;

	delete a->line;
	a->line = NULL;

	delete a->station;
	a->station = NULL;

	delete a->station_lines;
	a->station_lines = NULL;

	delete a->track;
	a->track = NULL;

	delete a->track_lines;
	a->track_lines = NULL;

	delete a;
	a = NULL;
	*/
	free(p);
}