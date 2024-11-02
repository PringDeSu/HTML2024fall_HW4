#pragma once

#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

long double operator*(vector<long double> &v, vector<long double> &w) {
    int n = v.size();
    long double ans = 0;
    for (int i = 0; i < n; i++) ans += v[i] * w[i];
    return ans;
}

vector<long double> operator*(vector<long double> a, long double k) {
    for (int i = 0; i < a.size(); i++) a[i] *= k;
    return a;
}

vector<long double> &operator+=(vector<long double> &a, vector<long double> b) {
    assert(a.size() == b.size());
    for (int i = 0; i < a.size(); i++) a[i] += b[i];
    return a;
}

vector<long double> &operator-=(vector<long double> &a, vector<long double> b) {
    assert(a.size() == b.size());
    for (int i = 0; i < a.size(); i++) a[i] -= b[i];
    return a;
}

struct MATRIX {
    int n, m;
    vector<vector<long double>> v;
    MATRIX() {}
    MATRIX(int _n, int _m) : n(_n), m(_m), v(n, vector<long double>(m, 0.0)) {}

    vector<long double> &operator[](int id) {
        return v[id];
    }
    void transpose() {
        vector<vector<long double>> w(m, vector<long double>(n));
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) w[j][i] = v[i][j];
        swap(v, w);
        swap(n, m);
    }
    MATRIX operator*(MATRIX &A) {
        // this matrix is assumed to be transposed
        assert(m == A.m);
        MATRIX S(n, A.n);
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) S[i][j] = operator[](i) * A[j];
        return S;
    }
    vector<long double> operator*(vector<long double> a) {
        assert(m == a.size());
        vector<long double> ans(n);
        for (int i = 0; i < n; i++) ans[i] = operator[](i) * a;
        return ans;
    }
    void invert() {
        MATRIX Y(n, n);
        for (int i = 0; i < n; i++) Y[i][i] = 1.0;
        for (int i = 0; i < n; i++) {
            Y[i] = Y[i] * (1.0 / v[i][i]);
            v[i] = v[i] * (1.0 / v[i][i]);
            for (int j = i + 1; j < n; j++) {
                Y[j] -= Y[i] * v[j][i];
                v[j] -= v[i] * v[j][i];
            }
        }
        for (int i = n - 1; i >= 0; i--) {
            for (int j = 0; j < i; j++) {
                Y[j] -= Y[i] * v[j][i];
                v[j] -= v[i] * v[j][i];
            }
        }
        swap(Y.v, v);
    }
};
