#include <iostream>
#include <limits>
#include <vector>
#include <climits> 
#include <iomanip>
#include <string>

using namespace std;

//-----------------------------------------------------//
const int MAX = 10; // const for the prima algorithm

int a, b, u, v, ne = 1;
int visited[MAX] = { 0 }, mincost = 0, cost[MAX][MAX];

//-----------------------------------------------------//

const int MAXN = 100; // const for the prima-kruscal algorithm

//-----------------------------------------------------//

const unsigned START = 0; // const for Dijkstra's algorithm

//-----------------------------------------------------//

// function executing Dijkstra's algorithm
void Dijkstra(const vector<vector<int>>& B, const unsigned& START, int n) {
    vector<bool> visited(n, false);
    vector<unsigned> distances(n, INT_MAX);
    unsigned minimalWeight, minimalIndex;

    for (int i = 0; i < n; i++)
    {
        visited[i] = false;
        distances[i] = INT_MAX;
    }

    distances[START] = 0;

    do
    {
        minimalIndex = INT_MAX;
        minimalWeight = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (!visited[i] && distances[i] < minimalWeight)
            {
                minimalIndex = i;
                minimalWeight = distances[i];
            }
        }

        if (minimalIndex != INT_MAX)
        {
            for (int i = 0; i < n; i++)
            {
                if (B[minimalIndex][i])
                {
                    unsigned temp = minimalWeight + B[minimalIndex][i];

                    if (temp < distances[i])
                        distances[i] = temp;
                }
            }

            visited[minimalIndex] = true;
        }
    } while (minimalIndex < INT_MAX);

    for (int i = 0; i < n; i++)
    {
        if (distances[i] != INT_MAX)
        {
            cout << "Weight: " << START << " ~> " << i + 1 << " = " << setw(6) << left << distances[i] << "\t";

            int end = i;
            unsigned weight = distances[end];
            string way = to_string(end) + " >~ ";

            while (end != START)
            {
                for (int j = 0; j < n; j++)
                {
                    if (B[j][end])
                    {
                        int temp = weight - B[j][end];

                        if (temp == distances[j])
                        {
                            end = j;
                            weight = temp;
                            way += to_string(j) + " >~ ";
                        }
                    }
                }
            }

            cout << "Path: ";

            for (int j = way.length() - 5; j >= 0; j--)
                cout << way[j];

            cout << endl;
        }
        else
            cout << "Weight: " << START << " ~ " << i + 1 << " = " << "Path not accessible" << endl;
    }
}

//-----------------------------------------------------//


// function executing the Prim-Kruskal algorithm
void primKruskal(int n, vector<vector<int>>& A) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (A[i][j] == 0 && i != j) {
                A[i][j] = INT_MAX;
            }
        }
    }

    vector<int> colors(n);
    for (int i = 0; i < n; i++) {
        colors[i] = i;
    }

    int treeLength = 0;
    vector<int> res1, res2;

    for (int k = 0; k < n - 1; k++) {
        int minew = INT_MAX;
        int minI = -1, minJ = -1;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; ++j) {
                if (colors[i] != colors[j] && A[i][j] < minew) {
                    minew = A[i][j];
                    minI = i;
                    minJ = j;
                }
            }
        }

        if (minI != -1 && minJ != -1) {
            res1.push_back(minI);
            res2.push_back(minJ);
            int oldColor = colors[minJ];
            int newColor = colors[minI];
            for (int m = 0; m < n; m++) {
                if (colors[m] == oldColor) {
                    colors[m] = newColor;
                }
            }

            treeLength += minew;
        }
    }

    cout << "Edges in the minimum spanning tree:" << endl;
    for (size_t i = 0; i < res1.size(); ++i) {
        cout << "(" << res1[i] + 1 << ", " << res2[i] + 1 << ")" << endl;
    }
    cout << "Length of the tree: " << treeLength << endl;
}

//-----------------------------------------------------//


//function executing the prima algorithm
void prim(int n) {
    cout << "Enter the distance matrix (if there is no edge, enter 0):\n";

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> cost[i][j];
            if (cost[i][j] == 0)
                cost[i][j] = 999;
        }
    }

    visited[1] = 1;
    cout << "\n";

    while (ne < n) {
        int min = 999;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (cost[i][j] < min) {
                    if (visited[i] == 1 && visited[j] == 0) {
                        min = cost[i][j];
                        u = i;
                        v = j;
                    }
                }
            }
        }

        visited[v] = 1;
        ne++;
        mincost += min;

        cout << "Edge " << u << " - " << v << " minimal and added to spanning tree with weight " << min << endl;

        cost[u][v] = cost[v][u] = 999;
    }

    cout << "\nMinimum cost: " << mincost;
}

//-----------------------------------------------------//

// menu item function
void print_menu() {
    cout << "Select algorithm:\n";
    cout << "1. Prim's algorithm\n";
    cout << "2. Prima-Kruskal algorithm\n";
    cout << "3. Dijkstra's algorithm.\n";
    cout << "4. Exit\n";
}

//-----------------------------------------------------//

// function to check the correctness of input when selecting menu items
int get_variant(int count) {
    int variant;

    cout << ">";
    while (!(cin >> variant) || variant < 1 || variant > count) {
        cout << "Invalid input. Try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return variant;
}

//-----------------------------------------------------//

int main() {
    setlocale(LC_ALL, "ru");
    int variant;

    do {
        print_menu();

        variant = get_variant(4);

        switch (variant) {
        case 1: { // call prim funcktion
            int n;
            cout << "Enter the number of vertices: ";
            cin >> n;
            prim(n);
            break;
        }

        case 2: { // call primKruskal function
            int n;
            cout << "Enter the number of vertices: ";
            cin >> n;

            vector<vector<int>> A(n, vector<int>(n));

            cout << "Enter the distance matrix (if there is no edge, enter 0):\n";
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    cout << "Enter edge (" << i + 1 << ", " << j + 1 << ") - "; cin >> A[i][j];
                }
            }
            primKruskal(n, A);
            cout << "-----------------------------------------" << endl;

            break;
        }

        case 4: { // exit of the programm
            cout << "Exit\n";
            break;
        }

        case 3: { // call Dijkstra function

            int n;

            cout << "Enter the number of vertices: ";
            cin >> n;

            vector<vector<int>> B(n, vector<int>(n));

            cout << "Enter the distance matrix (if there is no edge, enter 0):\n";
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    cout << "Enter edge (" << i + 1 << ", " << j + 1 << ") - ";
                    cin >> B[i][j];
                }
            }

            Dijkstra(B, START, n);
        }

        }
        if (variant != 5) {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }

    } while (variant != 4);

    return 0;
}


