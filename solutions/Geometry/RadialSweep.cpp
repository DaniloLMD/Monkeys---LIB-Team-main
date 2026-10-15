#include <bits/stdc++.h>

using namespace std;

const double eps = 1e-10;

struct Point {
	int x, y, color;
} points[2001];

int M, N;
double pi;

int ComputeMin(int a1, int b1, int a2, int b2) {
	return min(b1 + a2, a1 + b2);
}

int cnt[2];
vector<pair<double, int>> vp;

int Solve(int idx) {
	vp.clear();
	for (int i = 0; i < M + N; ++i) {
		if (i == idx) continue;
		const int dx = points[i].x - points[idx].x, dy = points[i].y - points[idx].y;
		assert(dx != 0 || dy != 0);
		const double u = atan2(dy, dx);
		vp.push_back({u, i});
		vp.push_back({u + 2.0 * pi, i});
	}
	
	sort(vp.begin(), vp.end());

	int ans = M + N, color_idx = points[idx].color;

	memset(cnt, 0, sizeof(cnt));
	for (int i = 0, j = 0; i < M + N - 1; ++i) {
		while (j < int(vp.size()) && vp[j].first - vp[i].first <= pi - eps) {
			++cnt[points[vp[j].second].color];
			++j;
		}
		
		// idx inside, vp[i].second inside.
		++cnt[color_idx];		
		ans = min(ans, ComputeMin(cnt[0], cnt[1], M - cnt[0], N - cnt[1]));
		
		// idx inside, vp[i].second outside.
		--cnt[points[vp[i].second].color];
		ans = min(ans, ComputeMin(cnt[0], cnt[1], M - cnt[0], N - cnt[1]));
		
		// idx outside, vp[i].second outside.
		--cnt[color_idx];		
		ans = min(ans, ComputeMin(cnt[0], cnt[1], M - cnt[0], N - cnt[1]));

		// idx outside, vp[i].second inside.
		++cnt[points[vp[i].second].color];
		ans = min(ans, ComputeMin(cnt[0], cnt[1], M - cnt[0], N - cnt[1]));

		// Move vp[i].second outside.
		--cnt[points[vp[i].second].color];
	}
	
	return ans;
}

int main() {
	pi = 2.0 * acos(0.0);
	int T;
	scanf("%d", &T);
	assert(1 <= T && T <= 100);
	while (T--) {
        scanf("%d %d", &M, &N);
    	
    	for (int i = 0; i < M; ++i) {
    		scanf("%d %d", &points[i].x, &points[i].y);
    	
    		points[i].color = 0;
    	}
    	
    	for (int i = M; i < M + N; ++i) {
    		scanf("%d %d", &points[i].x, &points[i].y);
    	
    		points[i].color = 1;
    	}

		int ans = M + N;
		for (int idx = 0; idx < M + N; ++idx) ans = min(ans, Solve(idx));
		
		printf("%d\n", ans);
	}
	return 0;
}