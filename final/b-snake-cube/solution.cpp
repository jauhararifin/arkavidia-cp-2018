#include <bits/stdc++.h>
using namespace std;

int dx[6], dy[6], dz[6];
int m[3][3][3], mx[27], my[27], mz[27];
int t[27][6];

int n, a[30];

// (i << 35) ^ (coord << 30) ^ (dir << 27) ^ mask
inline long long make_state(int i, int c, int d, int mask) {
    return ((long long)i << 35LL) ^ ((long long)c << 30LL) ^ ((long long)d << 27LL) ^ (long long)mask;
}

inline int get_i(long long state) {
    return (int)(state >> 35L);
}

inline int get_c(long long state) {
    return (int)((state >> 30LL) & ((1LL << 5) - 1));
}

inline int get_d(long long state) {
    return (int)((state >> 27LL) & ((1LL << 3) - 1));
}

inline int get_mask(long long state) {
    return (int)(state & ((1LL << 27) - 1));
}

int main() {
    // precomputes
    // dirs
    dx[0] = 0; dy[0] = 0; dz[0] = 1;
    dx[1] = 0; dy[1] = 0; dz[1] = -1;
    dx[2] = 0; dy[2] = 1; dz[2] = 0;
    dx[3] = 0; dy[3] = -1; dz[3] = 0;
    dx[4] = 1; dy[4] = 0; dz[4] = 0;
    dx[5] = -1; dy[5] = 0; dz[5] = 0;
    // coords
    int counter = 0;
    memset(m, -1, sizeof(m));
    for (int x = 0; x < 3; ++x) {
        for (int y = 0; y < 3; ++y) {
            for (int z = 0; z < 3; ++z) {
                m[x][y][z] = counter;
                mx[counter] = x;
                my[counter] = y;
                mz[counter] = z;
                counter++;
            }
        }
    }
    // neighbors
    for (int i = 0; i < 27; ++i) {
        for (int d = 0; d < 6; ++d) {
            int x = mx[i] + dx[d];
            int y = my[i] + dy[d];
            int z = mz[i] + dz[d];
            if (x < 0 || y < 0 || z < 0 || x > 2 || y > 2 || z > 2) {
                t[i][d] = -1;
            } else {
                t[i][d] = m[x][y][z];
            }
        }
    }
    

    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }

    // perform bfs (?)
    queue<long long> q; // q
    set<long long> visited;
    map<long long, long long> prev;
    // due to symmetry, starting points are restricted to the following:
    // (0, 0, 0), (1, 0, 0), (1, 1, 0), (1, 1, 1)
    int starting_points[] = {m[0][0][0], m[1][0][0], m[1][1][0], m[1][1][1]};
    for (int i = 0; i < 4; ++i) {
        long long s = make_state(0, starting_points[i], 0, 0);
        visited.insert(s);
        q.push(s);
    }
    while (!q.empty()) {
        long long state = q.front();
        q.pop();
        int i = get_i(state);
        int c = get_c(state);
        int dir = get_d(state);
        // if it is the first segment, any direction will do
        if (i == 0) {
            dir = -1;
        }
        int mask = get_mask(state);

        // for all directions, fill the cube with current segment
        for (int d = 0; d < 6; ++d) {
            if (d == dir) continue;
            int newmask = mask;
            int newc = c;
            // for the first segment, fill the first block
            if (i == 0) {
                assert(newmask == 0);
                newmask ^= 1 << newc;
            }
            bool found = true;
            for (int j = 1; j < a[i]; ++j) {
                newc = t[newc][d];
                if (newc == -1 || (newmask & (1 << newc))) {
                    found = false;
                    break;
                }
                newmask ^= 1 << newc;
            }
            if (!found) {
                continue;
            }
            if (newmask == (1 << 27) - 1) {
                puts("YES");
                // printf("STATE SIZE: %lu\n", visited.size());
                // backtracking, construct solution
                vector<int> dirs(n);
                dirs[n - 1] = d;
                long long current_state = state;
                for (int ii = n - 1; ii > 0; ii--) {
                    assert(ii == get_i(current_state));
                    int dd = get_d(current_state);
                    dirs[ii - 1] = dd;
                    current_state = prev[current_state];
                }
                // for (int ii = 0; ii < n; ++ii) {
                //     printf("DIR %2d: (%2d, %2d, %2d)\n", ii + 1, dx[dirs[ii]], dy[dirs[ii]], dz[dirs[ii]]);
                // }
                return 0;
            }
            long long newstate = make_state(i + 1, newc, d, newmask);
            if (visited.find(newstate) == visited.end()) {
                visited.insert(newstate);
                prev[newstate] = state;
                q.push(newstate);
                unsigned long size = visited.size();
            }
        }
    }
    puts("NO");
    // printf("STATE SIZE: %lu\n", visited.size());
}