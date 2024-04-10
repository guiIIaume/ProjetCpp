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
typedef vector<vector<Triplet>> Matrice; // Le format de nos images
typedef vector<pair<int, int>> Listepts;


Matrice initMat(int nb_lignes, int nb_colonnes){ // Crée une matrice de avec nb_lignes lignes et nb_colonnes colonnes, remplie de (0,0,0).
    Matrice M; 
    for(int i = 0;i<nb_lignes;i++){
        Triplet act{0,0,0};
        std::vector<Triplet> v(nb_colonnes,act);
        M.push_back(v);
    }
    return M;
}


void afficherMat(Matrice M){ // Affiche sur c++ une matrice
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

Matrice lireppm(std::string lienppm){ // Transforme un fichier ppm en une matrice c++
    std::ifstream f(lienppm); // On ouvre le fichier en lecture
    Matrice M;
    if (!f.is_open()){
        std::cout << "Impossible d'ouvrir le fichier en lecture !" << std::endl;
    }
    else{
        std::string ligne1, ligne2,ligne3,ligne4,ligne5,ligne6 ; // Les 6 premières lignes du fichiers ne sont pas des valeurs numériques
        int dim1,dim2;
        std::getline(f,ligne1); // Les deux premières lignes ne sont pas nécessaires à la créationd de la matrice
        std::getline(f,ligne2);
        f >> dim1; // On récupère le nombre de lignes de l'image
        f >> dim2; // On récupère le nombre de colonnes de l'image
        const int d1 = dim1;
        const int d2 = dim2;
        std::getline(f,ligne3); // Les quatre lignes suivantes ne sont donc plus nécessaires
        std::getline(f,ligne4);
        std::getline(f,ligne5);
        std::getline(f,ligne6);
        M = initMat(d1,d2); // On initialise une matrice avec d1 lignes et d2 colonnes
        for(int i = 0; i < d1 * d2;i++){
            std::string valR,valG,valB; // On récupère nos valeurs de Rouge, Vert et Bleu qui sont d'abord des chaînes de caractère
            std::getline(f,valR);
            std::getline(f,valG);
            std::getline(f,valB);
            int valeurR = std::stoi(valR); // On transforme ces chaînes de caractère en entier
            int valeurG = std::stoi(valG);
            int valeurB = std::stoi(valB);
            Triplet act{valeurR,valeurG,valeurB}; // Il s'agit du prochain pixel à ajouter à notre matrice
            int ligne = i / d1; // Le numéro de ligne sur lequel on est actuellement
            int colonne = i%d1; // Le numéro de colonne sur lequel on est actuellement
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

void ecriveur(Matrice a,std::string nom){
  int d1 = a.size();
  int d2 = a[0].size();
  string const nomFichier(nom);
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

Listepts NonBlancs(Matrice M){ // Renvoie la liste des coordonnées de tous les pixels qui ne sont pas blancs donc (255,255,255)
    Listepts RES;
    for(unsigned int i = 0; i <M.size();i++){
        for(unsigned int j = 0; j < M[i].size();j++){ // On parcourt les différents coefficients de la matrice
            Triplet act = M[i][j];
            int a = get<0>(act);
            int b = get<1>(act);
            int c = get<2>(act);
            if(a != 255 || b != 255 || c != 255){ // Et on vérifie s'ils sont blancs ou pas
                std::pair<int,int> coord; 
                coord.first = i;
                coord.second = j;
                RES.push_back(coord); // Si ce n'est pas le cas, on l'ajoute à notre liste resultat
            }
        }
    }
    return RES;
}

void affiche_Liste(Listepts L){ // Affiche une liste de points
    for(unsigned int i = 0;i < L.size();i++){
        std::pair<int,int> coord = L[i];
        int x = coord.first;
        int y = coord.second;
        std::cout<<"("<<x<<","<<y<<") ";
    }
}

Matrice changer_en_noir(Matrice M, Listepts L){ // Modifie en noir tous les points d'une image dont les coordonnées ont été renseignées dans une liste
    Matrice RES = M;
    for(unsigned int i = 0; i < L.size();i++){
        Triplet change{0,0,0};
        RES[L[i].first][L[i].second] = change;
    }
    return RES;
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
    Listepts L;
    L = NonBlancs(image);
    affiche_Liste(L);
    Matrice image4 = changer_en_noir(image,L);
    afficherMat(image4);
    ecriveur(image4,"Projet/ImageNoirBlanc.ppm");
    return 0;
}