#include <cmath>
#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

typedef tuple<int, int, int> Triplet;
typedef vector<vector<Triplet>> Matrice;
typedef vector<pair<int, int>> Listepts;


void afficherdroite(Matrice& matrice, Listepts& points) {
    for (auto& point : points) {
        int x = point.first;
        int y = point.second;
        
        if (x < 0 || x >= matrice.size() || y < 0 || y >= matrice[0].size()) {
            cout << "Point hors de la matrice : (" << x << ", " << y << ")" << endl;
        } else {
            matrice[x][y] = make_tuple(0, 0, 0);
            ;
        }
    }
}

void antipoint(Matrice& matrice){
  for (auto& point : matrice) {
    int x = point.first;
    int y = point.second;
    for (int i = floor(x); i <= ceil(x); i++){
      for (int j = floor(y); j <= ceil(y); j++){
        float percent_x=1-abs(x-i);
        float percent_y=1-abs(x-i);
        float percent = percent_x * percent_y;
        matrice[i][j] = make_tuple(255-floor(percent*255),255-floor(percent*255),255-floor(percent*255));
  }}}}

//def plot_antialiased_point(x: float, y: float):
//    """Plot a single, white-on-black anti-aliased point."""
//    for rounded_x in floor(x) to ceil(x):
//        for rounded_y in floor(y) to ceil(y):
//            percent_x = 1 - abs(x - rounded_x)
//            percent_y = 1 - abs(y - rounded_y)
//            percent = percent_x * percent_y
//            draw_pixel(coordinates=(rounded_x, rounded_y), color=percent (range 0-1))




int main() {
    Matrice matrice = {{{1, 2, 3}, {4, 5, 6}}, {{7, 8, 9}, {10, 11, 12}}};
    Listepts pt= {{0,1},{1,0}};
    afficherdroite(matrice,pt);
    for (const auto& row : matrice) {
        for (const auto& triplet : row) {
            cout << "(" << get<0>(triplet) << ", " << get<1>(triplet) << ", " << get<2>(triplet) << ") ";
        }
        cout << endl;
    }
    
    return 0;
}











