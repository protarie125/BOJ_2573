#include <algorithm>
#include <bit>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using ll = long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;
using pii = pair<int, int>;
using vii = vector<pii>;
using pll = pair<ll, ll>;
using vll = vector<pll>;
using vs = vector<string>;

int N, M;
vvi bd;
int ct;
vvb visit;
vvi nbd;

const auto dx = vi{ -1,1,0,0 };
const auto dy = vi{ 0,0,-1,1 };

void dfs(int r, int c) {
	nbd = vvi(bd);

	auto st = stack<pii>{};
	st.push({ r,c });

	visit[r][c] = true;

	while (!st.empty()) {
		const auto [y, x] = st.top();
		st.pop();

		for (auto d = 0; d < 4; ++d) {
			const auto& nx = x + dx[d];
			const auto& ny = y + dy[d];

			if (nx < 0 || M <= nx ||
				ny < 0 || N <= ny) {
				continue;
			}

			if (visit[ny][nx]) {
				continue;
			}

			if (0 == bd[ny][nx]) {
				--nbd[y][x];
				if (nbd[y][x] < 0) {
					nbd[y][x] = 0;
				}
				continue;
			}

			st.push({ ny, nx });
			visit[ny][nx] = true;
		}
	}

	bd = vvi(nbd);
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	cin >> N >> M;

	bd = vvi(N, vi(M));
	for (auto&& r : bd) {
		for (auto&& x : r) {
			cin >> x;
		}
	}

	auto t = 0;
	while (true) {
		/*for (const auto& r : bd) {
			for (const auto& x : r) {
				cout << x;
			}
			cout << endl;
		}
		cout << endl;*/

		ct = 0;
		visit = vvb(N, vb(M, false));
		for (auto r = 0; r < N; ++r) {
			for (auto c = 0; c < M; ++c) {
				if (0 == bd[r][c] || visit[r][c]) {
					continue;
				}

				dfs(r, c);
				++ct;
			}
		}

		if (2 <= ct) {
			cout << t;
			return 0;
		}

		if (0 == ct) {
			cout << 0;
			return 0;
		}

		++t;
	}

	return 0;
}