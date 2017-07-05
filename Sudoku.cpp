#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

//works
void afficher1D(int grid[], int len){
	for(int i=0;i<len;i++){
		cout<<grid[i];
		cout<<", ";
	}
	cout<<endl;
}

//works
void afficher2D(int grid[][9]){
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			cout << grid[i][j] << '\t';
		}
		cout << endl;
	}
	cout<<endl;
}

//works
void afficher3D(int grid[][9][9]){
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			cout <<"[";
			for(int k=0;k<9;k++){
				cout << grid[i][j][k];
			}
			cout<<"]\t";
		}
		cout<<endl;
	}
}

//works
void getCarre(int i,int j, int grid[][9], int carre33[][3]){
    for(int k=0;k<3;k++){
        for(int l=0;l<3;l++){
            carre33[k][l] = grid[i-i%3+k][j-j%3+l];
        }
    }
}

//works
void getLigne(int i, int grid[][9], int ligne[]){
    for(int k=0;k<9;k++){
        ligne[k] = grid[i][k];
    }
}

//works
void getColonne(int j, int grid[][9], int colonne[]){
    for(int k=0;k<9;k++){
        colonne[k] = grid[k][j];
    }
}

//works
bool Existe(int i, int liste[]) {
    for(int k=0; k<9; k++){
		int e = liste[k];
		if(e==i){
		    return true;
		}
    }
    return false;
}

//works
void flat(int carre33[][3], int carre9[]){
	for (int i=0;i<3;i++){
		for(int j=0; j<3;j++){
			carre9[3*i+j] = carre33[i][j];
		}
	}
}

//works
int valeursPossibles(int i, int j, int grid[][9], int ligne[], int colonne[], int carre33[][3], int carre9[], int interdit[], int val_pos[]){
	getLigne(i,grid,ligne);
	getColonne(j,grid, colonne);
	getCarre(i,j,grid,carre33);
	flat(carre33, carre9);
	int indice = 0;//nombre de valeurs possibles
  
	for(int k=1;k<10;k++){
		if(!(Existe(k,ligne) || Existe(k,colonne) || Existe(k,carre9) || Existe(k,interdit))){
			val_pos[indice] = k;
			indice++;
		}
	}
	return indice;
}

//works
void copyArray(int a1[],int a2[], int len){
	for(int k=0;k<len;k++){
		a2[k] = a1[k];
	}
}

//works
void melanger(int l[], int len){
	int temp = 0, r1 = 0, r2 = 0;
	for(int i=0;i<len;i++){
		r1 = rand()%len;
		r2 = rand()%len;
		temp = l[r1];
		l[r1] = l[r2];
		l[r2] = temp;
	}
}

//works
bool choixPossibles(int possibilites[][9][9], int grid[][9], int val_pos[],int ligne[], int colonne[], int carre33[][3], int carre9[], int interdit[][9][9], int premier[]){
	int mini = 9;
	int nb_val_pos=0;
	premier[0] = 10;premier[1] = 10;
	
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(grid[i][j]==0){
				nb_val_pos = valeursPossibles(i,j,grid,ligne,colonne,carre33,carre9,interdit[i][j],val_pos);
				if(nb_val_pos != 0){
					if(nb_val_pos<mini){
						premier[0] = i;premier[1] = j;
						mini = nb_val_pos;
					}
					copyArray(val_pos,possibilites[i][j],9);
					for(int k=0;k<9;k++){
						val_pos[k] = 0;
					}
				}else{
					return false;
				}
			}else{
				possibilites[i][j][0] = grid[i][j];
			}
		}
	}
	return(true);
}

//works
int nvNb(int dejaEssaye[], int ligne[], int colonne[], int carre9[]){
	int nb = rand()%9+1;
	int indice = 0;
	while(Existe(nb,ligne)||Existe(nb,colonne)||Existe(nb,carre9)){
		dejaEssaye[indice] = nb;
		indice ++;
		while(Existe(nb, dejaEssaye)){
			nb = rand()%9+1;
		}
	}
	return nb;
}

//works
void beginSudoku(int grid[][9], int aMelanger[],int ligne[], int colonne[], int carre33[][3], int carre9[], int dejaEssaye[]){
	
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			grid[i][j] = 0;
		}
		dejaEssaye[i] = 0;
	}
	melanger(aMelanger,9);
	copyArray(aMelanger, grid[0],9);
	for(int j=0;j<7;j++){
		getLigne(1,grid,ligne);
		getColonne(j,grid,colonne);
		getCarre(1,j,grid,carre33);
		flat(carre33, carre9);
		grid[1][j] = nvNb(dejaEssaye, ligne, colonne, carre9);
		for(int k=0;k<9;k++){
			dejaEssaye[k] = 0;
		}
	}
}

//works
int retourArriere(int grid[][9], int arbitraire[][3], int interdit[][9][9], int nb_interdits[][9], int last[], int nb_val_arbitraires, int aMelanger[], int ligne[], int colonne[], int carre33[][3], int carre9[], int dejaEssaye[]){
	if(nb_val_arbitraires>-1){
		copyArray(arbitraire[nb_val_arbitraires],last,3);
		int i = last[0], j = last[1];
		interdit[i][j][nb_interdits[i][j]] = last[2];
		nb_interdits[i][j]++;
		grid[i][j] = 0;
		nb_val_arbitraires--;
		return nb_val_arbitraires;
	}else{
		beginSudoku(grid, aMelanger, ligne, colonne, carre33, carre9, dejaEssaye);
		for(int i=0;i<9;i++){
			for(int j=0;j<9;j++){
				nb_interdits[i][j] = 0;
				for(int k=0;k<9;k++){
					interdit[i][j][k]=0;
				}
			}
		}
		return 0;
	}
}

//works
void newSudoku(int grid[][9], int aMelanger[],int ligne[], int colonne[], int carre33[][3], int carre9[], int dejaEssaye[], int arbitraire[][3], int interdit[][9][9], int possibilites[][9][9], int val_pos[], int premier[], int choix_arbitraire[], int nb_interdits[][9], int last[]){
	
	beginSudoku(grid, aMelanger, ligne, colonne, carre33, carre9, dejaEssaye);
	bool possible = choixPossibles(possibilites, grid, val_pos, ligne, colonne, carre33, carre9,  interdit, premier);
	int i,j,choix;
	int nb_val_arbitraires = 0;
	
	while(nb_val_arbitraires<65){
		if(possible){
		//if(possible and !(premier[0]==10 and premier[1]==10)){
			i = premier[0];
			j = premier[1];
			choix = possibilites[i][j][0];
			grid[i][j] = choix;
			choix_arbitraire[0] = i;
			choix_arbitraire[1] = j;
			choix_arbitraire[2] = choix;
			copyArray(choix_arbitraire, arbitraire[nb_val_arbitraires],3);
			possible = choixPossibles(possibilites, grid, val_pos, ligne, colonne, carre33, carre9,  interdit, premier);
			nb_val_arbitraires++;
		}else{
			nb_val_arbitraires = retourArriere(grid, arbitraire, interdit, nb_interdits, last,  nb_val_arbitraires, aMelanger, ligne, colonne, carre33, carre9, dejaEssaye);
			possible = choixPossibles(possibilites, grid, val_pos, ligne, colonne, carre33, carre9,  interdit, premier);
		}
	}
	afficher2D(grid);
}

//works
int main() {
	//choix aleatoire de la graine
	srand(time(NULL));
    
	//liste des tableaux necessaires:
	
    int val_pos[9] = {0};//valeurs possibles (non deja presentes)
    int ligne[9];//stocke la ligne etudiee
    int colonne[9];//stocke la colonne etudiee
    int carre33[3][3];//stocke le carre etudie
    int carre9[9];//stocke le carre sous forme de tableau 1D
    int interdit[9][9][9] = {0};//stocke tous les nombres interdits pour toutes les cases
    int nb_interdits[9][9] = {0};//nombre de valeurs interdites (longeur du tableau)
    int grid[9][9] = {0};//grille du sudoku
    int arbitraire[65][3] = {0};//succession des choix poses
    int premier[2] = {10,10};//coordonnees de la case dans laquelle faire un choix
    int last[3];//dernier choix arbitraire enregistre
    int aMelanger[9] = {1,2,3,4,5,6,7,8,9};//tous les entiers possibles, que l'on va melanger --> aleatoire
    int dejaEssaye[9] = {0};//stocke les nb deja utilises pour la generation des 16 premiers nb
    int possibilites[9][9][9] = {0};//toutes les possibilites pour toutes les cases
    int choix_arbitraire[3];//elements du tableau arbitraire(coordonnees et choix)
	
	
	newSudoku(grid, aMelanger, ligne, colonne, carre33, carre9, dejaEssaye, arbitraire, interdit, possibilites, val_pos, premier, choix_arbitraire, nb_interdits, last);
    return 0;

}