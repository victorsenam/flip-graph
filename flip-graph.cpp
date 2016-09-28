#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 60;

struct edge {
    int a, b;

    bool operator < (const edge & ot) const {
        if (a != ot.a) return a < ot.a;
        return b < ot.b;
    }

    bool operator == (const edge & ot) const {
        if (a != ot.a) return 0;
        if (b != ot.b) return 0;
        return 1;
    }
};

map<vector<edge>, int> mp;
int n, qt;
bool adj[N][N];

void printit (vector<edge> v) {
    if (mp.find(v) == mp.end()) {
        debug("x:");
    } else {
        debug("%d:", mp[v]);
    }
    for (int i = 0; i < v.size(); i++)
        debug(" (%d,%d)", v[i].a, v[i].b);
}

bool is_invalid (edge x) {
    if (x.a > x.b) return 1;
    if (x.b == x.a) return 1;
    if (x.b == (x.a + 1)%n) return 1;
    if ((x.b + 1)%n == x.a) return 1;
    return 0;
}

bool cross (edge x, edge y) {
    if (x == y) return 1;
    if (y < x) swap(x, y);

    x.b -= x.a;
    y.b -= x.a;
    y.a -= x.a;

    if (y.a == x.b || y.b == x.b) return 0;
    if (y.a == 0 || y.b == 0) return 0;
    return ((y.a < x.b) != (y.b < x.b));
}

vector<edge> sorted_insert (vector<edge> v, edge x) {
    vector<edge> nw;
    if (is_invalid(x)) return vector<edge>();
    for (int i = 0; i < v.size(); i++) {
        if (cross(v[i], x)) return vector<edge>();
        nw.push_back(v[i]);
    }

    nw.push_back(x);
    for (int m = nw.size() - 1; m > 0 && nw[m] < nw[m-1]; m--) swap(nw[m], nw[m-1]);
    return nw;
}
int build (vector<edge> v) {
    if (v.size() < n-3) {
        return -1;
    } else {
        if (mp.find(v) != mp.end()) return mp[v];
        int idx = mp[v] = qt++;

        for (int i = 0; i < n-3; i++) {
            vector<edge> next;
            edge x;
            for (int j = 0; j < n-3; j++) {
                if (i != j)
                    next.push_back(v[j]);
            }
            for (x.a = 0; x.a < n; x.a++) {
                for (x.b = x.a+2; x.b < n; x.b++) {
                    vector<edge> lala = sorted_insert(next, x);
                    int to = build(lala);
                    if (to >= 0) {
                        adj[to][idx] = adj[idx][to] = 1;
                    }
                }
            }
        }
        return idx;
    }
}

int main () {
    scanf("%d", &n);

    vector<edge> v;
    edge x;
    x.a = 0;

    for (x.b = 2; x.b < n-1; x.b++) {
        v.push_back(x);
    }
    build(v);

    for (int i = 0; i < qt; i++)
        adj[i][i] = 0;

    for (int i = 0; i < qt; i++, putchar('\n'))
        for (int j = 0; j < qt; j++)
            printf("%d,", adj[i][j]);
}
