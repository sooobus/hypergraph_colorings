#pragma once

#include <vector>
#include <numeric>

using namespace std;

vector<bool> bitwiseor(vector<vector<bool>> &vectors) {
	vector<bool> res(vectors.size(), 0);
	for (size_t j = 0; j < vectors[0].size(); j++) {
		for (size_t i = 0; i < vectors.size(); i++) {
			if (vectors[i][j] == 1) {
				res[i] = 1;
				break;
			}
		}
	}
	return res;
}

vector<bool> twobitwiseor(vector<bool> &vector1, vector<bool> &vector2) {
	vector<bool> res(vector1.size(), 0);
	for (size_t i = 0; i < vector1.size(); i++) {
		res[i] = vector1[i] || vector2[i];
	}
	return res;
}


size_t difference(vector<bool> &one, vector<bool> &another) {
	size_t counter = 0;
	for (size_t i = 0; i < one.size(); i++) {
		if (one[i] == false && another[i] == true) {
			counter++;
		}
	}
	return counter;
}

size_t sum(vector<bool> &v) {
	return std::accumulate(v.begin(), v.end(), 0);
}

vector<size_t> get_greedy_set(const vector<vector<bool>> &vectors) {
	size_t initial = 0;
	size_t len = vectors[0].size();
    vector<bool> used(vectors.size(), 0);
	vector<size_t> chosen;
	chosen.push_back(initial);
	auto current = vectors[initial];
    cout << sum(current) << " ? " << len << endl;
	while (sum(current) < len) {
		size_t dif = 0;
	    auto maxit = 0;
	    size_t max_dif = 0;
        for (size_t i = 0; i < vectors.size(); i++){
            if(!used[i]){
                auto th = vectors[i];
			    dif = difference(current, th);
                //cout << "dif: " << dif << endl;
			    if (dif > max_dif) {
				    max_dif = dif;
				    maxit = i;
			    }
            }
		}
        cout << "maxit: " << maxit << endl;
        auto mix = vectors[maxit];
		chosen.push_back(maxit);
        used[maxit] = true;
		current = twobitwiseor(current, mix);
		cout << "sum: " << sum(current) << "set size: " << chosen.size() << "last dif: " << max_dif << endl;
	}
	return chosen;
}

vector<size_t> get_randomized_set(const vector<vector<bool>> &vectors, double p) {
	size_t initial = 0;
	size_t len = vectors[0].size();
    vector<bool> used(vectors.size(), 0);
	vector<size_t> chosen;
	chosen.push_back(initial);
	auto current = vectors[initial];
    cout << sum(current) << " ? " << len << endl;
	while (sum(current) < len) {
		size_t dif = 0;
	    auto maxit = 0;
	    size_t max_dif = 0;
        for (size_t i = 0; i < vectors.size(); i++){
            if(!used[i]){
                auto th = vectors[i];
			    dif = difference(current, th);
                //cout << "dif: " << dif << endl;
			    if (dif > max_dif) {
				    max_dif = dif;
				    maxit = i;
			    }
            }
		}
        cout << "maxit: " << maxit << endl;
        double random = ((double) rand()) / RAND_MAX;
        cout << random << endl;
        if(random < p){
            try{
                cout << "Go improvize!" << endl;
                auto ri = rand() % vectors.size();
                cout << "index: " << ri;
                while(used[ri]) ri = rand() % len;
                maxit = ri;
            }
            catch(...){

            }
        }
        auto mix = vectors[maxit];
		chosen.push_back(maxit);
        used[maxit] = true;
		current = twobitwiseor(current, mix);
		cout << "sum: " << sum(current) << "set size: " << chosen.size() << "last dif: " << max_dif << endl;
	}
	return chosen;
}
