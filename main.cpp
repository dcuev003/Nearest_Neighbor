#include <iostream> 
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <iomanip>
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

int nearestNeighbor(int out, vector<Instance> train, vector<int> fnum){
		
	double min = DBL_MAX;
	double dist = 0.0;
	int clsf; //classification
	
	for(int i = 0; i < train.size(); i++){
		if(i != out){
			for(int j = 0; j < fnum.size(); j++){
				dist += pow((train.at(i).features.at(fnum.at(j)) - train.at(out).features.at(fnum.at(j))),2); 
			}
			if(dist < min){
				min = dist;
				clsf = train.at(i).id;
			}
		}
		dist = 0.0;
			
	}
	return clsf;
}

double leaveOneOut(vector<Instance> train, vector<int> fnumber){
	double correct = 0.0;
	int sz = train.size();
	double accuracy;
	
	for(int i = 0; i < sz; i++){
		if(nearestNeighbor(i,train, fnumber) == train.at(i).id){
			correct = correct + 1.000;
		}
	}
	accuracy = (correct/static_cast<double>(sz))*100.000;

	cout << "Using feature(s) {"; 
	for(int i = 0; i < fnumber.size(); i++){
		cout << fnumber.at(i)+1;
		if(i != fnumber.size()-1){
			cout << ",";
		}
	}
	cout << "} accuracy is " << setprecision(4) << accuracy << "%" << endl;

	return accuracy;
		
}

void forwardSelection(vector<Instance> instances){
	vector<int> feat;
	vector<int> bestFeat;
	vector<int> trueFeat;
	int siz = instances.at(0).features.size();
	double max = 0;
	double temp;
	int best;
	double curMax = 0;
		
	cout << "Beginning search." << endl << endl;
	for(int i = 0; i < siz; i++){
		curMax = 0.0;
		for(int j = 0; j < siz; j++){
			if((count(bestFeat.begin(), bestFeat.end(),j)) == 0){
				feat.push_back(j);
				temp = leaveOneOut(instances,feat);
				if(temp > curMax){
					curMax = temp;
					best = j;
				}
				feat.pop_back();
			}
		}
		bestFeat.push_back(best);
		if(curMax > max){
			max = curMax;
			trueFeat = bestFeat;
		}
		else{
			cout << "(Warning, Accuracy has decreased! Continue searching in case of local maxima)" << endl;
		}
		feat.clear();
		feat = bestFeat;
		cout << "Feature set {";
		for(int k = 0; k < bestFeat.size(); k++){
			cout << bestFeat.at(k) + 1;
			if(k != bestFeat.size()-1){
				cout << ",";
			}
		}
		cout << "} was best, accuracy is " << curMax << "%" << endl << endl;	
	}
	cout << "Finished Search!! The best feature subset is {";
	for(int l = 0; l < trueFeat.size(); l++){
        	cout << trueFeat.at(l) + 1;
        	if(l != trueFeat.size()-1){
                	cout << ",";
                }
        }
	cout << "}, which has an accuracy of " << max << "%." << endl;
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
	cout << "Please wait while I normalize the data.. ";

	train = normalize(train);

	cout << "Done!" << endl << endl;
	cout << endl;
	cout << "Type the number of the algorithm you want to run." << endl;
	cout << "1) Forward selection" << endl << "2) Backward Elimination" << endl << endl;


	cin >> choice;
	cout << endl;
	forwardSelection(train);	
	
	return 1;
}
