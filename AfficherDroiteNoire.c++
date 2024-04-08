#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <tuple>
using namespace std;

typedef tuple<int, int, int> Triplet;
typedef vector<vector<Triplet>> Matrice;
typedef vector<pair<int, int>> Listepts;

//pour afficher un ensemble de points (attention même si c'est un point unique il faut le mettre au type "Listepts")
void afficherdroite(Matrice& matrice, Listepts& points) {
  for (auto& point : points) {
    int x = point.first;
    int y = point.second;

    if (x < 0 || x >= matrice.size() || y < 0 || y >= matrice[0].size()) {
        cout << "Point hors de la matrice : (" << x << ", " << y << ")" << endl;
    } else {
        matrice[x][y] = make_tuple(255, 255, 255);
        ;
    }
  }
}

//pour afficher une droite y=mx+b
void afficherdroite2(Matrice& matrice,float m,float b){
  unsigned int d2 = matrice.size();
  unsigned int d1 = matrice[0].size();
  for (int j = 0; j < 100; ++j){
    if (m*j+b<d1 && j < d2){
      Listepts mono {{floor(m*j+b),j}};
      afficherdroite(matrice,mono);
    }else{
      break;
    }
  }
}


int main() {
    Matrice matrice = {{{1,2,3}, {4,5,6}, {7,8,9}, {10,11,12}, {13,14,15}}, {{16,17,18}, {19,20,21}, {22,23,24}, {25,26,27}, {28,29,30}}, {{31,32,33}, {34,35,36}, {37,38,39}, {40,41,42}, {43,44,45}}, {{46,47,48}, {49,50,51}, {52,53,54}, {55,56,57}, {58,59,60}}, {{61,62,63}, {64,65,66}, {67,68,69}, {70,71,72}, {73,74,75}}};
    Listepts points = {{0, 0}, {1, 1}};
//    afficherdroite(matrice, points);
    afficherdroite2(matrice,2,0);
  
    for (const auto& row : matrice) {
      for (const auto& triplet : row) {
          cout << "(" << get<0>(triplet) << ", " << get<1>(triplet) << ", " << get<2>(triplet) << ") ";
      }
      cout << endl;
    }
    
    return 0;
}
