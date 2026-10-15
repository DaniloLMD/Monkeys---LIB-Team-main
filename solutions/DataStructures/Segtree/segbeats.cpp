#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 200001;  // 1-based
const ll llINF=1e18;
#define lef(x) (x<<1)
#define rig(x) (lef(x) | 1)
int N;
ll A[MAXN];

struct Node {
	ll sum;  // Sum tag
	ll max1;  // Max value
	ll max2;  // Second Max value
	ll maxc;  // Max value count
	ll min1;  // Min value
	ll min2;  // Second Min value
	ll minc;  // Min value count
	ll lazy;  // Lazy tag
} T[MAXN * 4];

void merge(int t) {
	// sum
	T[t].sum = T[lef(t)].sum + T[rig(t)].sum;

	// max
	if (T[lef(t)].max1 == T[rig(t)].max1) {
		T[t].max1 = T[lef(t)].max1;
		T[t].max2 = max(T[lef(t)].max2, T[rig(t)].max2);
		T[t].maxc = T[lef(t)].maxc + T[rig(t)].maxc;
	} else {
		if (T[lef(t)].max1 > T[rig(t)].max1) {
			T[t].max1 = T[lef(t)].max1;
			T[t].max2 = max(T[lef(t)].max2, T[rig(t)].max1);
			T[t].maxc = T[lef(t)].maxc;
		} else {
			T[t].max1 = T[rig(t)].max1;
			T[t].max2 = max(T[lef(t)].max1, T[rig(t)].max2);
			T[t].maxc = T[rig(t)].maxc;
		}
	}

	// min
	if (T[lef(t)].min1 == T[rig(t)].min1) {
		T[t].min1 = T[lef(t)].min1;
		T[t].min2 = min(T[lef(t)].min2, T[rig(t)].min2);
		T[t].minc = T[lef(t)].minc + T[rig(t)].minc;
	} else {
		if (T[lef(t)].min1 < T[rig(t)].min1) {
			T[t].min1 = T[lef(t)].min1;
			T[t].min2 = min(T[lef(t)].min2, T[rig(t)].min1);
			T[t].minc = T[lef(t)].minc;
		} else {
			T[t].min1 = T[rig(t)].min1;
			T[t].min2 = min(T[lef(t)].min1, T[rig(t)].min2);
			T[t].minc = T[rig(t)].minc;
		}
	}
}

void push_add(int t, int tl, int tr, ll v) {
	if (v == 0) {
		return;
	}
	T[t].sum += (tr - tl + 1) *v;
	T[t].max1 += v;
	if (T[t].max2 != -llINF) {
		T[t].max2 += v;
	}
	T[t].min1 += v;
	if (T[t].min2 != llINF) {
		T[t].min2 += v;
	}
	T[t].lazy += v;
}

// corresponds to a chmin update
void push_max(int t, ll v, bool l) {
	if (v >= T[t].max1) {
		return;
	}
	T[t].sum -= T[t].max1 * T[t].maxc;
	T[t].max1 = v;
	T[t].sum += T[t].max1 * T[t].maxc;
	if (l) {
		T[t].min1 = T[t].max1;
	} else {
		if (v <= T[t].min1) {
			T[t].min1 = v;
		} else if (v < T[t].min2) {
			T[t].min2 = v;
		}
	}
}

// corresponds to a chmax update
void push_min(int t, ll v, bool l) {
	if (v <= T[t].min1) {
		return;
	}
	T[t].sum -= T[t].min1 * T[t].minc;
	T[t].min1 = v;
	T[t].sum += T[t].min1 * T[t].minc;
	if (l) {
		T[t].max1 = T[t].min1;
	} else {
		if (v >= T[t].max1) {
			T[t].max1 = v;
		} else if (v > T[t].max2) {
			T[t].max2 = v;
		}
	}
}

void pushdown(int t, int tl, int tr) {
	if (tl == tr)
		return;
	// sum
	int tm = (tl + tr) >> 1;
	push_add(lef(t), tl, tm, T[t].lazy);
	push_add(rig(t), tm + 1, tr, T[t].lazy);
	T[t].lazy = 0;

	// max
	push_max(lef(t), T[t].max1, tl == tm);
	push_max(rig(t), T[t].max1, tm + 1 == tr);

	// min
	push_min(lef(t), T[t].min1, tl == tm);
	push_min(rig(t), T[t].min1, tm + 1 == tr);
}

void build(int t=1, int tl=0, int tr=N-1) {
	T[t].lazy = 0;
	if (tl == tr) {
		T[t].sum = T[t].max1 = T[t].min1 = A[tl];
		T[t].maxc = T[t].minc = 1;
		T[t].max2 = -llINF;
		T[t].min2 = llINF;
		return;
	}

	int tm = (tl + tr) >> 1;
	build(lef(t), tl, tm);
	build(rig(t), tm + 1, tr);
	merge(t);
}

void update_add(int l, int r, ll v, int t=1, int tl=0, int tr=N-1) {
	if (r < tl || tr < l) {
		return;
	}
	if (l <= tl && tr <= r) {
		push_add(t, tl, tr, v);
		return;
	}
	pushdown(t, tl, tr);

	int tm = (tl + tr) >> 1;
	update_add(l, r, v, lef(t), tl, tm);
	update_add(l, r, v, rig(t), tm + 1, tr);
	merge(t);
}

void update_chmin(int l, int r, ll v, int t=1, int tl=0, int tr=N-1) {
	if (r < tl || tr < l || v >= T[t].max1) {
		return;
	}
	if (l <= tl && tr <= r && v > T[t].max2) {
		push_max(t, v, tl == tr);
		return;
	}
	pushdown(t, tl, tr);

	int tm = (tl + tr) >> 1;
	update_chmin(l, r, v, lef(t), tl, tm);
	update_chmin(l, r, v, rig(t), tm + 1, tr);
	merge(t);
}

void update_chmax(int l, int r, ll v, int t=1, int tl=0, int tr=N-1) {
	if (r < tl || tr < l || v <= T[t].min1) {
		return;
	}
	if (l <= tl && tr <= r && v < T[t].min2) {
		push_min(t, v, tl == tr);
		return;
	}
	pushdown(t, tl, tr);

	int tm = (tl + tr) >> 1;
	update_chmax(l, r, v, lef(t), tl, tm);
	update_chmax(l, r, v, rig(t), tm + 1, tr);
	merge(t);
}

ll query_sum(int l, int r, int t=1, int tl=0, int tr=N-1) {
	if (r < tl || tr < l) {
		return 0;
	}
	if (l <= tl && tr <= r) {
		return T[t].sum;
	}
	pushdown(t, tl, tr);

	int tm = (tl + tr) >> 1;
	return query_sum(l, r, lef(t), tl, tm) + query_sum(l, r, rig(t), tm + 1, tr);
}

int main() {
	int Q;

	cin >> N >> Q;
	for (int i = 0; i < N; i++) {
		cin >> A[i];
	}
	build();
	for (int q = 0; q < Q; q++) {
		int t; cin >> t;
		if (t == 0) {
			int l, r;
			ll x;
			cin >> l >> r >> x;
			update_chmin(l, r - 1, x);
		} else if (t == 1) {
			int l, r;
			ll x;
			cin >> l >> r >> x;
			update_chmax(l, r - 1, x);
		} else if (t == 2) {
			int l, r;
			ll x;
			cin >> l >> r >> x;
			update_add(l, r - 1, x);
		} else if (t == 3) {
			int l, r;
			cin >> l >> r;
			cout << query_sum(l, r - 1) << '\n';
		}
	}
}