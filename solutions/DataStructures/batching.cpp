#include <bits/stdc++.h>
using namespace std;

int n, q;
vector<int> arr;
vector<long long> prefix;

/** Build the prefix array for arr */
void build() {
	prefix[0] = 0;
	for (int i = 1; i <= n; i++) { prefix[i] = prefix[i - 1] + arr[i - 1]; }
}

int main() {
	cin >> n >> q;
	arr.resize(n);
	for (int i = 0; i < n; i++) { cin >> arr[i]; }
	prefix.assign(n + 1, 0);
	build();

	vector<pair<int, int>> updates;
	for (int i = 0; i < q; i++) {
		int type, a, b;
		cin >> type >> a >> b;
		if (type == 1) {
			a--;
			updates.push_back({a, b - arr[a]});
			arr[a] = b;
		} else {
			long long ans = prefix[b] - prefix[a - 1];
			a--, b--;
			for (const auto &[idx, val] : updates) {
				if (a <= idx && idx <= b) { ans += val; }
			}
			cout << ans << "\n";
		}

		// rebuild the prefix array once the buffer gets to sqrt(n)
		if (updates.size() * updates.size() >= n) {
			updates.clear();
			build();
		}
	}
}