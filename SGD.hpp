#pragma once

#include "vec.hpp"
#include <random>
#include <utility>
#include <iostream>
using namespace std;

namespace SGD {
    mt19937 rnd(time(NULL));
    const int EXPERIMENT_COUNT = 100000, TARGET_SPACE = 200;
    const long double eta = 0.01;

    struct RESULT {
        vector<long double> w;
        vector<long double> E_in_v, E_out_v;
        long double E_in, E_out;
        RESULT() {}
        RESULT(vector<long double> _w, vector<long double> _E_in_v, vector<long double> _E_out_v, long double _E_in, long double _E_out) : w(_w), E_in_v(_E_in_v), E_out_v(_E_out_v), E_in(_E_in), E_out(_E_out) {}
    };

    vector<long double> calc_gradient(vector<long double> &w, vector<long double> &x, long double y) {
        return x * (-2 * ((w * x) - y));
    }

    RESULT make_experiment(int N, int D, vector<long double> *x, vector<long double> &y, int n, vector<int> &selected_id) {
        auto calc_E = [&](vector<long double> &w) -> pair<long double, long double> {
            int id = 0;
            long double E_in = 0, E_out = 0;
            for (int i = 0; i < N; i++) {
                long double z = (w * x[i] - y[i]) * (w * x[i] - y[i]);
                if (id < n && selected_id[i] == id) {
                    E_in += z;
                    id++;
                } else {
                    E_out += z;
                }
            }
            return make_pair(E_in / n, E_out / (N - n));
        };
        vector<long double> w(D, 0.0);
        uniform_int_distribution<int> uid(0, n - 1);
        vector<long double> v_E_in, v_E_out;
        for (int cnt = 1; cnt <= EXPERIMENT_COUNT; cnt++) {
            int id = selected_id[uid(rnd)];
            vector<long double> gradient = calc_gradient(w, x[id], y[id]);
            w += gradient * eta;
            if (cnt % TARGET_SPACE == 0) {
                auto [E_in, E_out] = calc_E(w);
                v_E_in.push_back(E_in);
                v_E_out.push_back(E_out);
            }
        }
        return RESULT(w, v_E_in, v_E_out, v_E_in.back(), v_E_out.back());
    }
}