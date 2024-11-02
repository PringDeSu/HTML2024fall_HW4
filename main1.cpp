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

const int D = 13;
const int INPUT_SIZE = 8192;
vector<long double> x[INPUT_SIZE];
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

int main(int argc, char *argv[]) {
    ofstream output(argv[1]);
    for (int i = 0; i < INPUT_SIZE; i++) {
        x[i].resize(D);
        string s;
        getline(cin, s);
        convert_string_to_vec(s, x[i], y[i]);
    }
    int EXPERIMENT_COUNT = 1126, N = 64;
    vector<long double> v_E_in, v_E_out;
    long double E_in_lin = 0, E_out_lin = 0;
    for (int i = 1; i <= EXPERIMENT_COUNT; i++) {
        vector<int> selected_id = RND::GET(INPUT_SIZE, N);
        auto [res_lin, _] = LINEAR_REGRESSION::make_experiment(INPUT_SIZE, D, x, y, N, selected_id);
        auto res_sgd = SGD::make_experiment(INPUT_SIZE, D, x, y, N, selected_id);
        if (i == 1) {
            v_E_in = res_sgd.E_in_v;
            v_E_out = res_sgd.E_out_v;
        } else {
            v_E_in += res_sgd.E_in_v;
            v_E_out += res_sgd.E_out_v;
        }
        E_in_lin += res_lin.E_in;
        E_out_lin += res_lin.E_out;
        #ifdef PRINT
        cout << "EXPERIMENT #" << i << ": " << '\n';
        cout << res_lin.E_in << ' ' << res_lin.E_out << '\n';
        cout << res_sgd.E_in << ' ' << res_sgd.E_out << '\n';
        #endif
    }
    output << E_in_lin / EXPERIMENT_COUNT << '\n' << E_out_lin / EXPERIMENT_COUNT << '\n';
    for (auto &i : v_E_in) output << i / EXPERIMENT_COUNT << '\n';
    for (auto &i : v_E_out) output << i / EXPERIMENT_COUNT << '\n';
    return 0;
}