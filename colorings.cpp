#include <iostream>
#include "coloring_lib.h"
#include "greedy.h"

int main(){
    int n, k, v;
    double p;
    cin >> n >> k >> v >> p;
    auto mx = generate_edge_color_matrix(n, k, v);
    vector<vector<bool>> matrix = *mx;
    auto d1 = matrix.size(), d2 = matrix[0].size();
    //for(size_t i = 0; i < d1; i++){
    //    for(size_t j = 0; j < d2; j++){
    //        cout << matrix[i][j];
    //    }
    //    cout << endl;
    //}
    if(check_matrix(matrix)){
        auto ans = get_randomized_set(matrix, p);
        cout << ans.size() << endl;
        for(size_t i = 0; i < ans.size(); i++)
                cout << ans[i] << endl;
    }
    else
        cout << "Can't get set" << endl;
}
