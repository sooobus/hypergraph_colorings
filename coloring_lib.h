#include <vector>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

vector<int> next_cnk(vector<int> a, int n, bool* done) {
	auto ans = a;
	ans.push_back(n + 1);
	for (int i = (int)ans.size() - 1; i > 0; i--) {
		if (ans[i] - ans[i - 1] > 1) {
			ans[i - 1]++;
			int tail = ans[i - 1] + 1;
			for (size_t j = i; j < ans.size(); j++) {
				ans[j] = tail;
				tail++;
			}
			return ans;
		}
	}
	*done = false;
	return ans;
}

vector<vector<bool>> * generate_all_subsets(int n, int k) {
    vector<vector<int>> ans;
    vector<int> first;
    for(int i = 1; i <= k; i++){
        first.push_back(i);
    }
    bool done = true;
    while(done){
        ans.push_back(first);
        first = next_cnk(first, n, &done);
        first.pop_back();
    }
    
    auto masks = new vector<vector<bool>>(ans.size(), vector<bool>(n, 0));
    for(int i = ans.size() - 1; i >= 0; i--){
        for(int j = 0; j < k; j++){
            (*masks)[ans.size() - i - 1][ans[i][j] - 1] = true;
        }
    }

    return masks;
}

vector<vector<bool>>* get_all_binary_masks(int k) {
	auto masks = new vector<vector<bool>>;
	masks->reserve(pow(2, k));
	for (int i = 0; i < pow(2, k); i++) {
		vector<bool> mask(k, 0);
		int number = i;
		for(int j = k - 1; j >= 0; j--) {
			mask[j] = number % 2;
			//cout << number % 2 << " ";
			number /= 2;
		}
		masks->push_back(mask);
		//cout << endl;
	}
	return masks;
}

bool is_not_b(vector<bool>& edge, vector<bool>& color, size_t k) {
	size_t cnt_red = 0, cnt_blue = 0;
	for (size_t i = 0; i < edge.size(); i++) {
		if (edge[i]) {
			if (color[i]) {
				cnt_red++;
			}
			else {
				cnt_blue++;
			}
		}
	}
	return cnt_red < k || cnt_blue < k;
}


vector<vector<bool>>* generate_edge_color_matrix(size_t n, size_t k, size_t v){ //n -- uniform, k -- bound, v -- #vertexes
    auto edges = generate_all_subsets(v, n);
    cout << "made_edges" << endl;
    auto colorings = get_all_binary_masks(v);
    cout << "made_colorings" << endl;
    auto matrix = new vector<vector<bool>>(edges->size(), vector<bool>(colorings->size(), 0));

    for(size_t i = 0; i < (*edges).size(); i++){
        if (i % 100 == 0) cout << i << endl;
        for(size_t j = 0; j < (*colorings).size(); j++){
            (*matrix)[i][j] = is_not_b((*edges)[i], (*colorings)[j], k);
        }
    }

    return matrix;
}

bool check_matrix(vector<vector<bool>>& matrix){
    auto d1 = matrix.size();
    auto d2 = matrix[0].size();
    for(size_t j = 0; j < d2; j++){
        size_t cnt = 0;
        for(size_t i = 0; i < d1; i++)
            cnt += matrix[i][j];
        if(cnt == 0)
            return false;
    }
    return true;
}

bool check_answer(vector<size_t>& ans, vector<vector<bool>> matrix){
    for(size_t j = 0; j < matrix[0].size(); j++){
        bool flag = false;
        for(size_t i = 0; i < ans.size(); i++){
            if(matrix[ans[i]][j]){
                flag = true;

                //cout << ans[i] << endl;

                break;
            }
        }
        if(!flag)
            return false;
    }
    return true;
}


