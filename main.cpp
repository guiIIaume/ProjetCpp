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


std::vector<std::vector<int>> initMat(int nb_lignes,int nb_colonnes){
    std::vector<std::vector<int>> M;
    for(int i = 0; i< nb_lignes;i++){
        std::vector<int> v(nb_colonnes,0);
        M.push_back(v);
    }
    return M;
}

void afficherMat(std::vector<std::vector<int>> M){
    for(unsigned int i = 0;i<M.size();i++){
        for(unsigned int j = 0;j<M[i].size();j++){
            std::cout<<M[i][j]<<" ";
        }
        std::cout<<"\n";
    }
}


std::vector<std::vector<int>> lireppm(std::string lienppm){
    std::ifstream f(lienppm);
    std::vector<std::vector<int>> M;
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
        std::cout<<dim1<<" "<< dim2<<std::endl;
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
            double moy = (valeurR+valeurG+valeurB) /3;
            int coulfinale;
            if(moy < 128){
                coulfinale = 0;
            }
            else{
                coulfinale = 255;
            }
            int ligne = i / d1;
            int colonne = i%d1;
            M[ligne][colonne] = coulfinale;
        }
        f.close();
    }
    return M;
}

int main(){
    std::vector<std::vector<int>> M;
    M = initMat(7,5);
    afficherMat(M);
    std::vector<std::vector<int>> image;
    image = lireppm("Projet/m1projetcpp2.ppm");
    afficherMat(image);
    std::vector<std::vector<int>> image2;
    image2 = lireppm("Projet/imgSimple.ppm");
    afficherMat(image2);
    return 0;
}