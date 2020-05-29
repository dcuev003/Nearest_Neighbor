#include <iostream> 
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include "instance.cpp"
#include <algorithm>
#include <float.h>
using namespace std;

vector<Instance> normalize(vector<Instance> temp){
	double mean = 0.0;
	double sum = 0.0;
	double stdDev = 0.0;
	double var = 0.0;
	double sz = static_cast<double>(temp.size());
	
	vector<Instance> ret = temp;
	for(int i = 0; i < temp.at(0).features.size(); i++){
		for(int j = 0; j < temp.size(); j++){
			sum += temp.at(j).features.at(i); 	
		}
		//cout << endl << "sum: " << sum << endl;
		mean = sum/sz;
		//cout << "mean: " << mean << endl;
		for(int k = 0; k < temp.size(); k++){
			var += pow(temp.at(k).features.at(i) - mean, 2);
		}
		var = var/sz;
		stdDev = sqrt(var);
		//cout <<  "stdDev: " << stdDev << endl;
		for(int f = 0; f < temp.size(); f++){
			ret.at(f).features.at(i) = ((ret.at(f).features.at(i) - mean)/stdDev);
		}
		mean = 0.0;
		sum = 0.0;
		stdDev = 0.0;
		var = 0.0;
	}

	return ret;   
	
}

int nearestNeighbor(vector<double> featureSet, vector<Instance> train){
		
	double min = DBL_MAX;
	double dist = 0;
	int id;
	
	for(int i = 0; i < train.size(); i++){
		for(int j = 0; j < featureSet.size(); j++){
			dist += pow((train.at(i).features.at(j) - featureSet.at(j)),2); 
		}
		if(dist < min){
			min = dist;
			id = train.at(i).id;
		}
		dist = 0;	
	}
	return id;

	return 0;
}

void leaveOneOut(vector<double> fset, vector<Instance> train){
	cout << nearestNeighbor(fset, train);

}

int main(){
	
	cout << "Welcome to Daniel Cueva's Feature Selection Algorithm." << endl;
	cout << "Type in the name of the file to test: ";

	double val;
	vector <double> data;
	vector <Instance> train;

	string fname; //variable for file name
	int choice;
	cin >> fname;

	cout << fname << endl << endl;

	ifstream dat;

	dat.open(fname.c_str());
	
	string line;
	Instance *temp;
	
	while(getline(dat, line)){
		stringstream ss(line);
		
		while(ss >> val){
			data.push_back(val);
		}
		temp = new Instance(data);
		ss.clear();
		data.clear();
		train.push_back(*temp);
		delete temp;
	}
			
	dat.close();
	
	cout << "This dataset has " << train.at(0).features.size() << " features, with " << train.size() << " instances." << endl;
	cout << endl;

	/*cout << "testing nearest neighbor" << endl;
	vector<double> f;
	f.push_back(3.64);
	f.push_back(3.51);
	f.push_back(3.55);
	f.push_back(3.13);

	cout << "the nearest neighbor is: " << nearestNeighbor(f, train) << endl;*/

	cout << "Please wait while I normalize the data.. ";

	train = normalize(train);

	cout << "Done!" << endl << endl;

	for(int i = 0; i < train.size(); i++){
		train.at(i).print();
	}

	cout << endl;
	cout << "Type the number of the algorithm you want to run." << endl;
	cout << "1) Forward selection" << endl << "2) Backward Elimination" << endl << endl;


	cin >> choice;
	cout << "Running nearest neighbor with features, using leaving-one-out evaluation";
	cout << endl;

	
	
	


	return 1;
}
