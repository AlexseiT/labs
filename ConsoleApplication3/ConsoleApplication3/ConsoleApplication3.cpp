#include <iostream>
#include <queue>
using namespace std;
int main()
{
	//BFS - очереди
	int n, m;
	ios_base::sync_with_stdio(false);
	cin >> n >> m;
	vector<int> used(123456, 0);
	queue<int> q;
	q.push(n);
	//q.size();
	//q.empty();
	used[n] = 1;
	while (!q.empty()) {
		int tmp = q.front();
		q.pop();
		if (tmp * 2 < 1e4 && !used[tmp * 2]) {
			q.push(tmp * 2);
			used[tmp * 2] = used[tmp] + 1;
		}
		if (!used[tmp - 1] && tmp - 1 > 0) {
			q.push(tmp - 1);
			used[tmp - 1] = used[tmp] + 1;
		}
	}
	cout << used[m] - 1;
}

