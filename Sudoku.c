#include <iostream>

#include <random>

using namespace std;
int main() {

    cout<<"Hello world";

    return 0;

}


void getCarre(int grid[][9],int carre[][3],int i,int j){

    for(int k=0;k<3;k++){

        for(int l=0;l<3;l++){

            carre[k][l] = grid[i-i%3+k][j-j%3+l];

        }

    }

}



void getLigne(int grid[][9], int ligne[], int i){

    for(int k=0;k<9;k++){

        ligne[k] = grid[i][k];

    }

}



void getColonne(int grid[][9], int colonne[], int j){

    for(int k=0;k<9;k++){

        colonne[j] = grid[k][j];

    }

}



bool Existe(int i, int grid[], int len) {

    for(int k=0; k<len; k++){

        if(k==i){

            return true;

        }

    }

    return false;

}


void valeursPossibles(int grid[][9], int val_pos[], )