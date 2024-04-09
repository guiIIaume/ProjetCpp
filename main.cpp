#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <map>
#include <sstream>
#include <list>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
using namespace std;

typedef tuple<int, int, int> Triplet;
typedef vector<vector<Triplet>> Matrice;
typedef vector<pair<int, int>> Listepts;


Matrice initMat(int nb_lignes, int nb_colonnes){
    Matrice M;
    for(int i = 0;i<nb_lignes;i++){
        Triplet act{0,0,0};
        std::vector<Triplet> v(nb_colonnes,act);
        M.push_back(v);
    }
    return M;
}


void afficherMat(Matrice M){
    for(unsigned int i = 0;i<M.size();i++){
        for(unsigned int j = 0;j<M[i].size();j++){
            Triplet act = M[i][j];
            int a = get<0>(act);
            int b = get<1>(act);
            int c = get<2>(act);
            std::cout<<"("<<a<<","<<b<<","<<c<<") ";
        }
        std::cout<<"\n";
    }
}

int maxMat(std::vector<std::vector<int>> M){
    int maximum = 0;
    for(unsigned int i = 0;i<M.size();i++){
        int maxact = *max_element(M[i].begin(),M[i].end());
        if(maxact > maximum){
            maximum = maxact;
        }
    }
    return maximum;
}

Matrice lireppm(std::string lienppm){
    std::ifstream f(lienppm);
    Matrice M;
    if (!f.is_open()){
        std::cout << "Impossible d'ouvrir le fichier en lecture !" << std::endl;
    }
    else{
        std::string ligne1, ligne2,ligne3,ligne4,ligne5,ligne6 ;
        int dim1,dim2;
        std::getline(f,ligne1);
        std::getline(f,ligne2);
        f >> dim1;
        f >> dim2;
        const int d1 = dim1;
        const int d2 = dim2;
        std::getline(f,ligne3);
        std::getline(f,ligne4);
        std::getline(f,ligne5);
        std::getline(f,ligne6);
        M = initMat(d1,d2);
        for(int i = 0; i < d1 * d2;i++){
            std::string valR,valG,valB;
            std::getline(f,valR);
            std::getline(f,valG);
            std::getline(f,valB);
            int valeurR = std::stoi(valR);
            int valeurG = std::stoi(valG);
            int valeurB = std::stoi(valB);
            Triplet act{valeurR,valeurG,valeurB};
            int ligne = i / d1;
            int colonne = i%d1;
            M[ligne][colonne] = act;
        }
        f.close();
    }
    return M;
}

void afficherdroite(Matrice& matrice, Listepts& points) {
    for (auto& point : points) {
        unsigned int x = point.first;
        unsigned int y = point.second;
        
        if (x < 0 || x >= matrice.size() || y < 0 || y >= matrice[0].size()) {
            cout << "Point hors de la matrice : (" << x << ", " << y << ")" << endl;
        } else {
            matrice[x][y] = make_tuple(255, 255, 255);
            ;
        }
    }
}

void ecriveur(Matrice a){
  int d1 = a.size();
  int d2 = a[0].size();
  string const nomFichier("Projet/Image.ppm");
    std::ofstream monFlux(nomFichier.c_str());
    if(monFlux){
      
        monFlux << "P3" << std::endl;
        monFlux << "#resolution" << std::endl;
        monFlux << d1 << " " << d2 << std::endl;
        monFlux << "#avec 255 comme valeur max" << std::endl;
        monFlux << "255" << std::endl;
        monFlux << "#debut de l'image" << std::endl;
        for (int i = 0; i < d1; ++i){
          for (int j = 0; j < d2; ++j){
            Triplet act = a[i][j];
            monFlux << get<0>(act) << std::endl;
            monFlux << get<1>(act) << std::endl;
            monFlux << get<2>(act) << std::endl;
        }}
    }
    else
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
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

int main(){
    Matrice  M;
    M = initMat(7,5);
    afficherMat(M);
    Matrice image;
    image = lireppm("Projet/m1projetcpp2.ppm");
    afficherMat(image);
    Matrice image2;
    image2 = lireppm("Projet/imgSimple.ppm");
    afficherMat(image2);
    Matrice matrice = {{{1, 2, 3}, {4, 5, 6}}, {{7, 8, 9}, {10, 11, 12}}};
    afficherMat(matrice);
    Listepts points = {{0, 0}, {1, 1}};
    afficherdroite(matrice, points);
    afficherMat(matrice);
    ecriveur(image);
    Matrice image3;
    image3 = lireppm("Projet/Image.ppm");
    afficherMat(image3);
    Listepts L;
    L = NonBlancs(image);
    affiche_Liste(L);
    std::cout<<L.size()<<std::endl;
    return 0;
}