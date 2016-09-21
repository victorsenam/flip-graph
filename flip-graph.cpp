#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef int64_t ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 50;

typedef pair<int, int> pii;
int n, qt;
int mat[N][N];
map<vector<pii>, int> mp;

bool conf (pii x, pii y) {
    if (x.first == y.first && x.second == y.second) return 1;
    x.second = (x.second - x.first + n)%n;
    y.second = (y.second - x.first + n)%n;
    y.first = (y.first - x.first + n)%n;
    if (y.first > y.second) swap(y.first, y.second);

    return ((y.first < x.second)^(y.second <= x.second));
}

bool conf (vector<pii> & u, pii x) {
    for (int i = 0; i < u.size(); i++)
        if (conf(u[i], x)) return 1;
    return 0;
}

int dfs (vector<pii> & v) {
    if (mp.find(v) != mp.end())
        return mp[v];
    int id = mp[v] = qt++;

    for (int k = 0; k < v.size(); k++) { 
        vector<pii> u;
        for (int i = 0; i < v.size(); i++)
            if (i != k)
                u.push_back(v[i]);

        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) {
                if ((i+1)%n == j || (j+1)%n == i) continue;
                if (conf(u, pii(i, j))) continue;
                vector<pii> nw = u;
                nw.push_back(pii(i, j));
                sort(nw.begin(), nw.end());
                int nid = dfs(nw);
                if (id != nid)
                    mat[nid][id] = mat[id][nid] = 1;
            }
        }
    }
    
    return id;
}

int main () {
    scanf("%d", &n);
    
    vector<pii> v;
    for (int i = 2; i < n-1; i++)
        v.push_back(pii(0, i));

    dfs(v);

    for (int i = 0; i < qt; i++, putchar('\n')) {
        for (int j = 0; j < qt; j++) {
            printf("%d%c", !!mat[i][j], ", "[j==qt-1]);
        }
    }
}
