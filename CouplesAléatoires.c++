//A tester!
//pour diminuer la complexité

#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <tuple>
#include <cstdlib>
#include <cmath>
using namespace std;

typedef tuple<int, int, int> Triplet;
typedef vector<vector<Triplet>> Matrice;
typedef vector<pair<int, int>> Listepts;
typedef pair<int,int> Point;

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

void afficherdroite2(Matrice& matrice,float m,float b){
  unsigned int d2 = matrice.size();
  unsigned int d1 = matrice[0].size();
  for (int j = 0; j < 10000; ++j){
    if (m*j+b<d1 && j < d2){
      Listepts mono {{floor(m*j+b),j}};
      afficherdroite(matrice,mono);
    }else{
      break;
    }
  }
}



Listepts NonBlancs(Matrice M){
    Listepts RES;
    for(unsigned int i = 0; i <M.size();i++){
        for(unsigned int j = 0; j < M[i].size();j++){
            Triplet act = M[i][j];
            int a = get<0>(act);
            int b = get<1>(act);
            int c = get<2>(act);
            if(a != 255 || b != 255 || c != 255){
                std::pair<int,int> coord;
                coord.first = i;
                coord.second = j;
                RES.push_back(coord);
            }
        }
    }
    return RES;
}

void affiche_Liste(Listepts L){
    for(unsigned int i = 0;i < L.size();i++){
        std::pair<int,int> coord = L[i];
        int x = coord.first;
        int y = coord.second;
        std::cout<<"("<<x<<","<<y<<") ";
    }
}

void print_map(std::string_view comment, const std::map<pair<float,float>, int>& m){
    std::cout << comment;
    for (const auto& [key, value] : m)
        std::cout << '[' << key.first <<"  ;  "<< key.second << "] = " << value << "; ";
}

Matrice CouplesAleatoires(Matrice matrice, nombredecouples = 10000, seuil = 1000){
    std::map<std::pair<float, float>, int> nblignes; // Pour stocker le nombre d'occurrences de chaque couple (m,p)
        
    //creation des 1000 droites
    for(int i = 0; i < nombredecouples; i++) {
      Point p1;
      unsigned int k = rand() % NonBlancs(matrice).size();
      p1.first = NonBlancs(matrice)[k].second;
      p1.second = NonBlancs(matrice)[k].first;
      Point p2;
      unsigned int k2 = rand() % NonBlancs(matrice).size();
      p2.first = NonBlancs(matrice)[k2].second;
      p2.second = NonBlancs(matrice)[k2].first;
      if (p2.first != p1.first){
        float m = (float) (p2.second - p1.second) / (p2.first - p1.first);
        float p = p1.second - m * p1.first;
        nblignes[{m, p}]=nblignes[{m, p}]+1;
      }
    }
  
    //affichage ssi nbligne(droite) >= 5
    for(auto& pair : nblignes) {
        if(pair.second >= seuil) {
            afficherdroite2(matrice,pair.first.first,pair.first.second);
            std::cout << "Droite : y = " << pair.first.first << "x + " << pair.first.second << std::endl;
      }
    }
    print_map("map=   ",nblignes);
    cout<<endl;
    return matrice;
}




int main() {
    Matrice matrice = {{{0,255,0}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}}, {{255,0,255}, {255,0,255}, {255,0,255}, {0,255,0}, {255,0,255}},{{255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}},{{255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}},{{255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}}};
    
    
    std::map<std::pair<float, float>, int> nblignes; // Pour stocker le nombre d'occurrences de chaque couple (m,p)
        
    //creation des 1000 droites 

    for(int i = 0; i < nombredecouples; i++) {
      Point p1;
      unsigned int k = rand() % NonBlancs(matrice).size();
      p1.first = NonBlancs(matrice)[k].second;
      p1.second = NonBlancs(matrice)[k].first;
      Point p2;
      unsigned int k2 = rand() % NonBlancs(matrice).size();
      p2.first = NonBlancs(matrice)[k2].second;
      p2.second = NonBlancs(matrice)[k2].first;
      if (p2.first != p1.first){
        float m = (float) (p2.second - p1.second) / (p2.first - p1.first);
        float p = p1.second - m * p1.first;
        nblignes[{m, p}]=nblignes[{m, p}]+1;
      }
    }
    //affichage ssi nbligne(droite) >= 5
    for(auto& pair : nblignes) {
        if(pair.second >= seuil) {
            afficherdroite2(matrice,pair.first.first,pair.first.second);
            std::cout << "Droite : y = " << pair.first.first << "x + " << pair.first.second << std::endl;
      }
    }
    print_map("map=   ",nblignes);
    cout<<endl;
    for (const auto& row : matrice) { //affichage matrice
      for (const auto& triplet : row) {
          cout << "(" << get<0>(triplet) << ", " << get<1>(triplet) << ", " << get<2>(triplet) << ") ";
      }
      cout << endl;
    }
    return 0;
}
