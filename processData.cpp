/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : processData.cpp
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : Implementation of main features in the assignment
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */
#include "dbLib.h"
#include "processData.h"

/* TODO: You can implement methods, functions that support your data structures here.
 * */
using namespace std;
int* r = NULL;
void Initialization() {
    // If you use global variables, please initialize them explicitly in this function.
}

void Finalization() {
    // Release your data before exiting
	//free(r);
}

int findStationMaxID(L1List<TStations>* station) {
	L1Item<TStations>* b = station->head();
	if (b == NULL) return -1;
	int max = b->data.id;
	while (b) {
		if (b->data.id>max) {
			//cout << b->data.name << endl;
			max = b->data.id;
		}
		b = b->pNext;
	}
	return max;
}

int findStationID(L1List<TStations>* staion, string s) {
	L1Item<TStations>* b = staion->head();
	while (b) {
		if (compareString(b->data.name, s)) {
			//cout << b->data.name << endl;
			return b->data.id;
		}
		b = b->pNext;
	}
	return -1;
}

int findCityID(L1List<TCity>* city, string s) {
	L1Item<TCity>* b = city->head();
	while (b) {
		if (compareString(b->data.name,s)) {
			//cout << b->data.name << endl;
			return b->data.id;
		}
		b = b->pNext;
	}
	return -1;
}
int countLine(L1List<TLine>* line, int city_id) {
	L1Item<TLine>* b = line->head();
	int count = 0;
	while (b) {
		if (b->data.city_id==city_id) {
			//cout << b->data.name.length() << endl;
			count++;
		}
		b = b->pNext;
	}
	return count;
}
int countStation(L1List<TStations>* station, int city_id) {
	L1Item<TStations>* b = station->head();
	int count = 0;
	while (b) {
		if (b->data.city_id == city_id) {
			//cout << b->data.name.length() << endl;
			count++;
		}
		b = b->pNext;
	}
	return count;
}

int countSLine(L1List<TStationLines>* station_line, int line_id) {
	L1Item<TStationLines>* b = station_line->head();
	int count = 0;
	while (b) {
		if (b->data.line_id == line_id) {
			//cout << b->data.name.length() << endl;
			count++;
		}
		b = b->pNext;
	}
	return count;
}


void ProcessRequest(const char* pRequest, void* pData, void* &pOutput, int &N) {
    // TODO: Implement this function for processing a request
    // NOTE: You can add other functions to support this main process.
    //       pData is a pointer to a data structure that manages the dataset
    //       pOutput is a pointer reference. It is set to nullptr and student must allocate data for it in order to save the required output
    //       N is the size of output, must be a non-negative number
	
	//cout << a->line->at(0).id << '+';
	
	if (pRequest == NULL) {
		N = 1;
		r = new int[N];
		*r = -1;
		pOutput = r;
		return;
	}

	TDataset* a = new TDataset;
	a = (TDataset*)pData;
	//cout << a->city->at(0).name;-
	//a->station->remove(4);


	if (pRequest[0] == 'I' && pRequest[1] == 'S' && pRequest[2] == 'L') {
		N = 1;
		r = new int[N];
		if (a->station_lines == NULL || a->station_lines->head() == NULL) {
			*r = -1;
			pOutput = r;
			return;
		}
		string station_id = "";
		string line_id = "";
		string pos = "";
		int count = 4;

		while (pRequest[count] != ' ') {
			station_id = station_id + pRequest[count];
			count++;
		}
		count = count + 1;
		while (pRequest[count] != ' ') {
			line_id = line_id + pRequest[count];
			count++;
		}
		count = count + 1;
		while (count!=strlen(pRequest)) {
			pos = pos + pRequest[count];
			count++;
		}
		//ISL <17000> <1> <2>
		int sid = stoint(station_id);
		int lid = stoint(line_id);
		int post = stoint(pos);

		count = 0;
		int position = 0;
		L1Item<TStationLines>* c = new L1Item<TStationLines>;
		c->data.station_id = sid;
		c->data.line_id = lid;
		L1Item<TStationLines>* b = a->station_lines->head();
		while (b) {
			if (b->data.line_id == lid) {
				if (count == post) {
					a->station_lines->insert(position, c);
					*r = 0;
					pOutput = r;
					return;
				}
				count++;
			}
			b = b->pNext;
			position++;
		}
		*r = -1;
		pOutput = r;
	}

	else if (pRequest[0] == 'R' && pRequest[1] == 'S' && pRequest[2] == 'L') {
		N = 1;
		r = new int[N];
		if (a->station_lines == NULL || a->station_lines->head() == NULL) {
			*r = -1;
			pOutput = r;
			//cout << '?';
			return;
		}
		string station_id = "";
		string line_id = "";
		int count = 4;

		while (pRequest[count] != ' ') {
			station_id = station_id + pRequest[count];
			count++;
		}
		count = count + 1;
		while (count!=strlen(pRequest)) {
			line_id = line_id + pRequest[count];
			count++;
		}
		int sid = stoint(station_id);
		int lid = stoint(line_id);
		//cout << sid << endl << lid << endl;
		int pos = 0;
		L1Item<TStationLines>* b = a->station_lines->head();
		while (b) {
			if (b->data.station_id == sid && b->data.line_id == lid) {
				a->station_lines->remove(pos);
				*r = 0;
				pOutput = r;
				return;
			}
			pos++;
			b = b->pNext;
		}

		*r = -1;
		pOutput = r;
	}

	else if (pRequest[0] == 'S' && pRequest[1] == 'L' && pRequest[2] == 'P') {
		N = 1;
		r = new int[N];
		if (a->station == NULL || a->station->head() == NULL || a->track == NULL || a->track->head() == NULL) {
			*r = -1;
			pOutput = r;
			return;
		}
		string station_id = "";
		string track_id = "";

		int count = 4;

		while (pRequest[count] != ' ') {
			station_id = station_id + pRequest[count];
			count++;
		}
		count = count + 1;
		while (count != strlen(pRequest)) {
			track_id = track_id + pRequest[count];
			count++;
		}
		int sid = stoint(station_id);
		int tid = stoint(track_id);

		int index = 0;
		L1Item<TStations>* b = a->station->head();
		L1Item<TTrack>* c = a->track->head();

		while (b) {
			if (b->data.id == sid) break;
			b = b->pNext;
		}
		while (c) {
			if (c->data.id == tid) break;
			c = c->pNext;
		}

		string point = "";

		count = 6;
		while (b->data.geomatry[count] != ')') {
			point = point + b->data.geomatry[count];
			count++;
		}

		count = 12;
		while (c->data.geomatry[count] != ')') {
			string temp;
			while (c->data.geomatry[count] != ',' && c->data.geomatry[count] != ')') {
				temp = temp + c->data.geomatry[count];
				count++;
			}
			if (compareString(temp, point)) {
				*r = index;
				pOutput = r;
				return;
			}
			count++;
			index++;
		}
		*r = -1;
		pOutput = r;
	}

	else if (pRequest[0] == 'C' && pRequest[1] == 'L' && strlen(pRequest) == 2){
		N = 1;
		r = new int[N];
		*r=a->line->getSize();
		//cout << r << endl;
		pOutput = r;
		return;
		
	}
	else if (pRequest[0] == 'C' && pRequest[1] == 'L' && strlen(pRequest) > 2) {
		N = 1;
		r = new int[N];
		string city_name;
		for (int i=3;i<strlen(pRequest);i++) city_name= city_name+pRequest[i];
		int city_id = findCityID(a->city, city_name);
		if (city_id != -1) *r = countLine(a->line, city_id);
		else *r = -1;
		//cout << city_id<<city_name<<endl;
		pOutput = r;
	}
	else if (pRequest[0] == 'L' && pRequest[1] == 'S' && pRequest[2] == 'C') {
		string city_name;
		for (int i = 4; i < strlen(pRequest); i++) city_name = city_name + pRequest[i];
		int city_id = findCityID(a->city, city_name);
		N = countStation(a->station, city_id);
		r = new int[N];

		L1Item<TStations>* b = a->station->head();
		int count = 0;
		while (b) {
			if (b->data.city_id == city_id) {
				r[count] = b->data.id;
				count++;
			}
			b = b->pNext;
		}
		pOutput = r;

		//for (int i = 0; i < N; i++) cout << ' ' << r[i];
		//cout << endl;
	}
	else if (pRequest[0] == 'L' && pRequest[1] == 'L' && pRequest[2] == 'C') {
		string city_name;
		for (int i = 4; i < strlen(pRequest); i++) city_name = city_name + pRequest[i];
		int city_id = findCityID(a->city, city_name);
		N = countLine(a->line, city_id);
		r = new int[N];

		L1Item<TLine>* b = a->line->head();
		int count = 0;
		while (b) {
			if (b->data.city_id == city_id) {
				r[count] = b->data.id;
				//cout << r[count] << ' ';
				count++;
			}
			b = b->pNext;
		}
		//cout << endl;
		pOutput = r;
	}
	else if (pRequest[0] == 'L' && pRequest[1] == 'S' && pRequest[2] == 'L') {
		string line_id;
		for (int i = 4; i < strlen(pRequest); i++) line_id = line_id + pRequest[i];
		int lid = stoint(line_id);
		N = countSLine(a->station_lines, lid);
		r = new int[N];

		L1Item<TStationLines>* b = a->station_lines->head();
		int count = 0;
		while (b) {
			if (b->data.line_id == lid) {
				r[count] = b->data.station_id;
				//cout << r[count] << ' ';
				count++;
			}
			b = b->pNext;
		}
		//cout << endl;
		pOutput = r;
	}
	else if (pRequest[0] == 'F' && pRequest[1] == 'C') {
		string city_name;
		for (int i = 3; i < strlen(pRequest); i++) city_name = city_name + pRequest[i];
		N = 1;
		r = new int[N];
		*r = findCityID(a->city, city_name);
		pOutput = r;
	}
	else if (pRequest[0] == 'F' && pRequest[1] == 'S') {
		string station_name;
		for (int i = 3; i < strlen(pRequest); i++) station_name = station_name + pRequest[i];
		N = 1;
		r = new int[N];
		*r = findStationID(a->station, station_name);
		pOutput = r;
	}
	else if (pRequest[0] == 'I' && pRequest[1] == 'S') {
		string csv_description;
		for (int i = 3; i < strlen(pRequest); i++) csv_description = csv_description + pRequest[i];
		N = 1;
		r = new int[N];
		int station_ID = findStationMaxID(a->station)+1;

		L1Item<TStations>* b = new L1Item<TStations>;
		b->data.id = station_ID;
		int j = 0;
		string temp;
		loadString(csv_description, j, false, temp);
		if (temp[0] == '"' && temp[temp.length() - 1] != '"') {
			for (int k = 1; k < temp.length(); k++)
				b->data.name = b->data.name + temp[k];
			b->data.name = b->data.name + ',';
			while (csv_description[j] != '"') {
				b->data.name = b->data.name + csv_description[j];
				j++;
			}
			j = j + 2;
		}
		else if (temp[0] == '"') {
			for (int i = 1; i < temp.length() - 1; i++)
				b->data.name = b->data.name + temp[i];
		}
		else b->data.name = temp;
		loadString(csv_description, j, false, b->data.geomatry);
		fastforward(csv_description, j, false);
		fastforward(csv_description, j, false);
		fastforward(csv_description, j, false);
		loadNumber(csv_description, j, true, b->data.city_id);
		a->station->push_back(b);

		*r = station_ID;
		pOutput = r;
	}

	else if (pRequest[0] == 'R' && pRequest[1] == 'S') {
		string station_id;
		for (int i = 3; i < strlen(pRequest); i++) station_id = station_id + pRequest[i];
		int id = stoint(station_id);
		N = 1;
		r = new int[N];
		int count = 0;
		bool flag = false;

		L1Item<TStations>* b=a->station->head();
		while (b) {
			if (b->data.id == id) {
				flag = true;
				break;
			}
			b = b->pNext;
			count++;
		}
		if (!flag) {
			*r = -1;
			pOutput = r;
			return;
		}
		a->station->remove(count);

		count = 0;
		L1Item<TStationLines>* c = a->station_lines->head();
		while (c) {
			if (c->data.station_id == id) {
				flag = true;
				break;
			}
			c = c->pNext;
			count++;
		}
		if (!flag) {
			*r = -1;
			pOutput = r;
			return;
		}
		a->station_lines->remove(count);

		*r = 0;
		pOutput = r;
	}
	else if (pRequest[0] == 'U' && pRequest[1] == 'S') {
	N = 1;
	r = new int[N];
		if (a->station == NULL || a->station->head() == NULL) {
			*r = -1;
			pOutput = r;
			return;
		}
		string station_id;
		string csv_description;
		int count = 3;
		while (pRequest[count] != ' ') {
			station_id = station_id + pRequest[count];
			count++;
		}
		count = count + 1;
		while (count != strlen(pRequest)) {
			csv_description = csv_description + pRequest[count];
			count++;
		}
		int id = stoint(station_id);

		L1Item<TStations>* b = a->station->head();
		while (b) {
			if (b->data.id == id) {
				int i = 0;
				loadNumber(csv_description, i, false, b->data.id);
				loadString(csv_description, i, false, b->data.name);
				loadString(csv_description, i, false, b->data.geomatry);
				fastforward(csv_description, i, false);
				fastforward(csv_description, i, false);
				fastforward(csv_description, i, false);
				loadNumber(csv_description, i, true, b->data.city_id);
				*r = 0;
				pOutput = r;
				return;
			}
			b = b->pNext;
		}
		*r = -1;
		pOutput = r;
	}
	
	
	
}

