#include<vector>
#include<iostream>
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

//transforme une matrice en un fichier texte ou ppm avec les informations dedant
void ecriveur(std::vector<std::vector<int>> a){
  int d1 = a.size();
  int d2 = a[0].size();
  string const nomFichier("PpmEcrit.txt");
    std::ofstream monFlux(nomFichier.c_str());
    if(monFlux){
        monFlux << "P3" << std::endl;
        monFlux << "#resolution" << std::endl;
        monFlux << d1 << "  " << d2 << std::endl;
        monFlux << "#avec 255 comme valeur max" << std::endl;
        monFlux << "255" << std::endl;
        monFlux << "#debut de l'image" << std::endl;
        for (int i = 0; i < d1; ++i){
          for (int j = 0; j < d2; ++j){
            monFlux << a[i][j] << std::endl;
        }}
    }
    else
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
    }
}
  
int main(){
    std::vector<std::vector<int>> k={{1,2,3},{4,5,6},{7,8,9}};
    ecriveur(k);
    return 0;
}














