#include <vector>
#include <queue>
#include <set>
#include <iostream>
using namespace std;

class TreeNode {
    friend class Tree;
    private:
        int value;
        vector<TreeNode*> children;
    public:
        TreeNode(int val) { value = val; }
};

class Tree {
    private:
        TreeNode* root;
    public:
        Tree() { root = nullptr; }
        void insert(int val, int parent) {
            TreeNode* newNode = new TreeNode(val);
        }

};

class Graph {
    private:
        set<int>* adjList;
        int* parents;
        enum NodeColor { WHITE, GRAY, BLACK };
        NodeColor* colors;
        int size;
    public:
        Graph(set<pair<int, int>> pairs, int n) {
            adjList = new set<int>[n];
            for (pair<int,int> pair: pairs) {
                adjList[pair.first].insert(pair.second);
                adjList[pair.second].insert(pair.first);
            }
            parents = new int[n];
            colors = new NodeColor[n];
            size = n;
        }
        ~Graph() {
            delete [] adjList;
            delete [] parents;
            delete [] colors;
        }
        void bfs(int origin) {
            queue<int> discovered;
            discovered.push(origin);
            parents[origin] = -1;
            while (!discovered.empty()) {
                int vertex = discovered.front();
                discovered.pop();
                colors[vertex] = GRAY;
                for (int elem: adjList[vertex]) {
                    if (colors[elem] == WHITE) {
                        parents[elem] = vertex;
                        colors[elem] = GRAY;
                        discovered.push(elem);
                    }
                }
                colors[vertex] = BLACK;
            }
            for (int i = 1; i < size; i++) {
                cout << "parents[" << i << "]: " << parents[i] << endl;
            }
            for (int i = 1; i < size; i++) {
                cout << "colors[" << i << "]: " << colors[i] << endl;
            }
        }
        void print() {
            for (int i = 1; i < size; i++) {
                cout << "adjList[" << i << "] = ";
                for (int elem: adjList[i]) {
                    cout << elem << " ";
                }
                cout << endl;
            }
        }
        bool isEulerian() {
            bool result = true;
            int i = 0;
            while (result and i < size) {
                if (adjList[i].size() % 2 != 0)
                    result = false;
                i++;
            }
            return result;
        }
};



int main() {
    int n, u, v;
    cin >> n;
    set<pair<int,int>> pairs;
    while (cin >> u >> v) {
        pairs.insert(pair(u,v));
    }
    Graph g(pairs, n+1);
    g.bfs(1);
    g.print();
    if (g.isEulerian())
        cout << "Sim\n";
    else
        cout << "Não\n";
}


