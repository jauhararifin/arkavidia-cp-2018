#include <bits/stdc++.h>
using namespace std;

int dx[6], dy[6], dz[6];
int n, a[30];
int v[3][3][3];

void dfs(int x, int y, int z, int i, int lastd) {
    if (i == n) {
        puts("Ya");
        exit(0);
    }
    for (int d = 0; d < 6; ++d) {
        if (d == lastd) continue;
        vector<int> ax, ay, az;
        if (i == 0) {
            ax.push_back(x);
            ay.push_back(y);
            az.push_back(z);
        }
        int nx = x, ny = y, nz = z;
        bool valid = true;
        for (int j = 1; j < a[i]; ++j) {
            nx += dx[d];
            ny += dy[d];
            nz += dz[d];
            if (nx < 0 || nx > 2 || ny < 0 || ny > 2 || nz < 0 || nz > 2 || v[nx][ny][nz]) {
                valid = false;
                break;
            }
            ax.push_back(nx);
            ay.push_back(ny);
            az.push_back(nz);
        }
        if (valid) {
            for (int j = 0; j < (int)ax.size(); ++j) {
                v[ax[j]][ay[j]][az[j]] = 1;
            }
            dfs(nx, ny, nz, i + 1, d);
            for (int j = 0; j < (int)ax.size(); ++j) {
                v[ax[j]][ay[j]][az[j]] = 0;
            }
        }
    }
}

int main() {
    // precomputes
    dx[0] = 0; dy[0] = 0; dz[0] = 1;
    dx[1] = 0; dy[1] = 0; dz[1] = -1;
    dx[2] = 0; dy[2] = 1; dz[2] = 0;
    dx[3] = 0; dy[3] = -1; dz[3] = 0;
    dx[4] = 1; dy[4] = 0; dz[4] = 0;
    dx[5] = -1; dy[5] = 0; dz[5] = 0;

    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }

    // unoptimized version:
    // start from all positions
    // easily got TLE
    // for (int x = 0; x < 3; ++x) {
    //     for (int y = 0; y < 3; ++y) {
    //         for (int z = 0; z < 3; ++z) {
    //             dfs(x, y, z, 0, -1);
    //         }
    //     }
    // }

    // optimized version:
    // start only from 4 possible starting points
    // due to symmetry
    dfs(0, 0, 0, 0, -1);
    dfs(1, 0, 0, 0, -1);
    dfs(1, 1, 0, 0, -1);
    dfs(1, 1, 1, 0, -1);

    puts("Tidak");
    return 0;
}