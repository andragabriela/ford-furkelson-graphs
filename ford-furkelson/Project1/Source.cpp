#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <limits.h>
#include <algorithm>
#include <queue>

using namespace std;
using std::vector;
using std::map;

#define NIL 9999999
vector<int>varfuri;
vector<vector<int>>vecini;
vector<int>parinte;


std::ifstream fin("in.txt");

bool bfs(map<pair<int, int>, int> Rgraf, int s, int t) {
	vector<bool>visited(t + 1, false);
	queue<int> coada;
	coada.push(s);
	visited[s] = true;
	parinte[s] = -1;

	while (!coada.empty()) {
		int u = coada.front();
		coada.pop();
		for (const auto v : vecini[u]) {
			auto pereche = make_pair(u, v);
			if (visited[v] == false && Rgraf[pereche] > 0) {
				coada.push(v);
				parinte[v] = u;
				visited[v] = true;
			}
		}
	}

	return (visited[t] == true);
}

int ford_fulkerson(map<pair<int, int>, int> Rgraf, int s, int t) {
	int u, v;

	int max_flow = 0;

	while (bfs(Rgraf, s, t)) {
		int path_flow = INT_MAX;
		for (v = t; v != s; v = parinte[v]) {
			u = parinte[v];
			auto pereche = make_pair(u, v);
			path_flow = min(path_flow, Rgraf[pereche]);

		}

		for (v = t; v != s; v = parinte[v]) {
			u = parinte[v];
			auto pereche1 = make_pair(u, v);
			auto pereche2 = make_pair(v, u);
			Rgraf[pereche1] -= path_flow;
			Rgraf[pereche2] += path_flow;
		}
		max_flow += path_flow;
	}

	return max_flow;

}

int main() {


	int V, E, x, y, w;
	fin >> V >> E;
	for (int i = 0; i < V; i++) {
		varfuri.push_back(i);
		vector<int>a;
		vecini.push_back(a);
		parinte.push_back(NIL);
	}
	map<pair<int, int>, int> Rgraf;
	for (int i = 0; i < E; i++) {
		fin >> x >> y >> w;
		pair<int, int>muchie1 = make_pair(x, y);
		auto pondere1 = make_pair(muchie1, w);
		pair<int, int>muchie2 = make_pair(y, x);
		auto pondere2 = make_pair(muchie2, 0);
		Rgraf.insert(pondere1);
		Rgraf.insert(pondere2);
		vecini.at(x).push_back(y);
		vecini.at(y).push_back(x);
	}


	cout << ford_fulkerson(Rgraf, 0, V - 1);

	fin.close();
	return 0;
}