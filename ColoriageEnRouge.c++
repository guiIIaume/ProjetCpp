#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

typedef tuple<int, int, int> Triplet;
typedef vector<vector<Triplet>> Matrice;
typedef vector<pair<int, int>> Listepts;

void modifierEnRouge(Matrice& matrice, Listepts& points) {
    for (auto& point : points) {
        int x = point.first;
        int y = point.second;
        
        if (x < 0 || x >= matrice.size() || y < 0 || y >= matrice[0].size()) {
            cout << "Point hors de la matrice : (" << x << ", " << y << ")" << endl;
        } else {
            matrice[x][y] = make_tuple(255, 0, 0);
            ;
        }
    }
}

int main() {
    Matrice matrice = {{{1, 2, 3}, {4, 5, 6}}, {{7, 8, 9}, {10, 11, 12}}};
    Listepts points = {{0, 0}, {1, 1}};
    
    modifierEnRouge(matrice, points);
    
    for (const auto& row : matrice) {
        for (const auto& triplet : row) {
            cout << "(" << get<0>(triplet) << ", " << get<1>(triplet) << ", " << get<2>(triplet) << ") ";
        }
        cout << endl;
    }
    
    return 0;
}
