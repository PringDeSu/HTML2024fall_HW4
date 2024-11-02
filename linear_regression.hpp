#pragma once

#include "vec.hpp"
#include <algorithm>
#include <random>

namespace LINEAR_REGRESSION {
    struct RESULT {
        vector<long double> w;
        long double E_in, E_out;
        RESULT() {}
        RESULT(vector<long double> _w, long double _E_in, long double _E_out) : w(_w), E_in(_E_in), E_out(_E_out) {}
    };

    pair<RESULT, bool> make_experiment(int N, int D, vector<long double> *x, vector<long double> &y, int n, vector<int> &selected_id) {
        MATRIX X(n, D);
        vector<long double> Y(n);
        for (int i = 0; i < n; i++) {
            X[i] = x[selected_id[i]];
            Y[i] = y[selected_id[i]];
        }
        X.transpose();
        MATRIX XTX = X * X;
        {
            MATRIX Y = XTX;
            MATRIX Z = Y;
            Z.invert();
            Z.transpose();
            MATRIX A = Z * Y;
            long double eps = 1e-8;
            for (int i = 0; i < D; i++) {
                for (int j = 0; j < D; j++) {
                    long double x = A[i][j];
                    long double sim = min(abs(x - 1.0), abs(x));
                    if (sim > eps) {
                        return make_pair(RESULT(), false);
                    }
                }
            }
        }
        XTX.invert();
        XTX.transpose();
        vector<long double> w = XTX * (X * Y);
        long double E_in = 0, E_out = 0;
        int id = 0;
        for (int i = 0; i < N; i++) {
            long double dif = w * x[i] - y[i];
            if (id < n && i == selected_id[id]) {
                E_in += dif * dif;
                id++;
            } else {
                E_out += dif * dif;
            }
        }
        E_in /= n;
        E_out /= (N - n);
        return make_pair(RESULT(w, E_in, E_out), true);
    }
};