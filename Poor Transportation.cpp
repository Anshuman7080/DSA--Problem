#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

const int MAX_NODES = 1002;
vector<int> graph[MAX_NODES];
int capacity[MAX_NODES][MAX_NODES];
int parent[MAX_NODES];
bool visited[MAX_NODES];

bool getAugmentedPath(int source, int sink) {
    fill(visited, visited + MAX_NODES, false);
    visited[source] = true;

    vector<int> stack = {source};
    while (!stack.empty()) {
        int current = stack.back();
        stack.pop_back();

        for (int adj : graph[current]) {
            if (!visited[adj] && capacity[current][adj] > 0) {
                visited[adj] = true;
                parent[adj] = current;
                if (adj == sink) return true;
                stack.push_back(adj);
            }
        }
    }
    return false;
}

int updateAugmentedPath(int sink) {
    int flow = numeric_limits<int>::max();
    for (int node = sink; node != 0; node = parent[node]) {
        int prev = parent[node];
        flow = min(flow, capacity[prev][node]);
    }

    for (int node = sink; node != 0; node = parent[node]) {
        int prev = parent[node];
        capacity[prev][node] -= flow;
        capacity[node][prev] += flow;
    }
    return flow;
}

int maxFlow(int source, int sink) {
    int totalFlow = 0;
    while (getAugmentedPath(source, sink)) {
        totalFlow += updateAugmentedPath(sink);
    }
    return totalFlow;
}

vector<int> maxTrucks(int N, int M, int P, int D, const vector<vector<int>>& permits, const vector<int>& cap, const vector<vector<int>>& reduction) {
    fill(&capacity[0][0], &capacity[0][0] + sizeof(capacity) / sizeof(int), 0);
    for (int i = 1; i <= N; i++) {
        graph[0].push_back(i);
        graph[i].push_back(0);
        capacity[0][i] = 1;
    }

    for (int i = 0; i < P; i++) {
        int u = permits[i][0];
        int v = permits[i][1];
        graph[u].push_back(v + N);
        graph[v + N].push_back(u);
        capacity[u][v + N] = 1;
    }

    for (int i = 1; i <= M; i++) {
        graph[N + i].push_back(N + M + 1);
        graph[N + M + 1].push_back(N + i);
        capacity[N + i][N + M + 1] = cap[i - 1];
    }

    for (int i = 0; i < D; i++) {
        int r = reduction[i][0];
        int c = reduction[i][1];
        capacity[N + r][N + M + 1] -= c;
    }

    int initialMaxFlow = maxFlow(0, N + M + 1);
    vector<int> ans;

    while (D > 0) {
        int r = reduction[D - 1][0];
        int c = reduction[D - 1][1];
        capacity[N + r][N + M + 1] += c;
        initialMaxFlow += maxFlow(0, N + M + 1);
        ans.push_back(initialMaxFlow);
        D--;
    }

    reverse(ans.begin(), ans.end());
    return ans;
}

int main() {
    // Example usage
    int N = 3, M = 3, P = 5, D = 2;
    vector<vector<int>> permits = {{1, 1}, {1, 2}, {2, 1}, {2, 3}, {3, 3}};
    vector<int> cap = {1, 2, 1};
    vector<vector<int>> reduction = {{1, 1}, {2, 1}};

    vector<int> result = maxTrucks(N, M, P, D, permits, cap, reduction);
    for (int flow : result) {
        cout << flow << " ";
    }
    cout << endl;

    return 0;
}
