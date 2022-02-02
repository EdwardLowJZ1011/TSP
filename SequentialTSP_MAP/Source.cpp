#include<iostream>
#include<fstream>
#include<string>
#include <algorithm> 
#include<vector>
using namespace std;

struct point {
	float x;
	float y;
	char name[20];
	char signal;
	int index;
};

float dist(point p, point p1) {
	return sqrt((p.x - p1.x)*(p.x - p1.x) + (p.y - p1.y)*(p.y - p1.y));
}

void swap(point *xp, point *yp) {
	point temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void sortingSignal(point p[], int n) {

	bool swapped;

	for (int i = 0; i < n - 1; i++) {
		swapped = false;
		for (int j = 1; j < n - i - 1; j++) {
			if (p[j].signal > p[j + 1].signal) {
				swap(&p[j], &p[j + 1]);
				swapped = true;
			}
		}
		if (swapped == false)
			break;
	}
}

void dijkstra(point P[], vector<string> &o, int init, int t, int c, int control){

	float min = FLT_MAX;

	if (control == 1 || control == 2){
		for (int i = init; i < t; i++){
			min = FLT_MAX;
			for (int j = i + 1; j < c; j++){
				if (dist(P[i], P[j]) < min){
					min = dist(P[i], P[j]);
					P[i].index = j;
					if (P[i].index != i + 1){
						swap(&P[i + 1], &P[P[i].index]);
					}
				}
			}
			o.push_back(P[i].name);
		}
	}
	else{
		o.push_back(P[t].name);
		o.push_back(P[0].name);
	}

}

int main(void) {

	vector<string> output;
	ifstream in;
	int number_of_input = 0;
	point* a = NULL;
	in.open("tsp.map");


	in >> number_of_input;
	a = new point[number_of_input];
	int i = 0;
	while (!in.eof()) {
		in >> a[i].name >> a[i].x >> a[i].y;
		i++;
	}

	in.clear();
	in.close();

	int count = 0;

	a[0].signal = 'G';
	for (int i = 1; i < number_of_input; i++) {
		if (a[i].name[0] == 'R'){
			a[i].signal = 'R';
			count++;
		}
		else
			a[i].signal = 'B';
	}


	sortingSignal(a, number_of_input);


	
	dijkstra(a, output, 0, number_of_input - count - 1, number_of_input - count, 1);
	dijkstra(a, output, number_of_input - count - 1, number_of_input - 1, number_of_input, 2);
	dijkstra(a, output, NULL, number_of_input - 1, NULL, 3);


	ofstream out;
	out.open("solution.txt");

	for (size_t i = 0; i < output.size(); i++)
		out << output[i] << '\n';

	out.close();
	output.clear();

	return 0;

}