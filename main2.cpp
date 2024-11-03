#include "io.hpp"
#include "linear_regression.hpp"
#include "SGD.hpp"

#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>
#include <iterator>
#include <cassert>
using namespace std;

const int D1 = 13, D2 = 37;
const int INPUT_SIZE = 8192;
vector<long double> x[INPUT_SIZE], z[INPUT_SIZE];
vector<long double> y(INPUT_SIZE);

namespace RND {
    mt19937 rnd(time(nullptr));
    vector<int> vid;

    void INIT(int n) {
        for (int i = 0; i < n; i++) vid.push_back(i);
    }

    vector<int> GET(int N, int n) {
        if (vid.empty()) INIT(N);
        vector<int> res;
        sample(vid.begin(), vid.end(), back_inserter(res), n, rnd);
        return res;
    }
}

vector<long double> NONLINEAR_TRANSFER(vector<long double> x) {
    vector<long double> ans;
    ans.push_back(1.0);
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 12; j++) {
            ans.push_back(1.0);
            for (int k = 0; k < i; k++) ans.back() *= x[j];
        }
    }
    return ans;
}

int main(int argc, char *argv[]) {
    ofstream output_in(argv[1]), output_out(argv[2]);
    for (int i = 0; i < INPUT_SIZE; i++) {
        x[i].resize(D1);
        string s;
        getline(cin, s);
        convert_string_to_vec(s, x[i], y[i]);
        z[i] = NONLINEAR_TRANSFER(x[i]);
    }
    int EXPERIMENT_COUNT = 1126, N = 64;
    vector<long double> v_E_in, v_E_out;
    long double E_in_lin = 0, E_out_lin = 0;
    for (int i = 1; i <= EXPERIMENT_COUNT; i++) {
        vector<int> selected_id = RND::GET(INPUT_SIZE, N);
        auto [res_z, inv] = LINEAR_REGRESSION::make_experiment(INPUT_SIZE, D2, z, y, N, selected_id);
        if (!inv) {
            i--;
            continue;
        }
        auto [res_x, _] = LINEAR_REGRESSION::make_experiment(INPUT_SIZE, D1, x, y, N, selected_id);
        output_in << res_x.E_in - res_z.E_in << '\n';
        output_out << res_x.E_out - res_z.E_out << '\n';
        #ifdef PRINT
        cout << "EXPERIMENT #" << i << ": " << endl;
        cout << res_x.E_in << ' ' << res_x.E_out << endl;
        cout << res_z.E_in << ' ' << res_z.E_out << endl;
        #endif
    }
    return 0;
}