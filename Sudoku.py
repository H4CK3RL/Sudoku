#
#Henri LASSERRE
#Jeu de sudoku
#

from tkinter import *
import numpy as np
import random as rd

fenetre = Tk()
fenetre.title("Sudoku")
fenetre.resizable(False, False)

def drawGrid(win,s):
    """
    Cette fonction permet d'afficher une grille dans la fenetre win.
    """
    size = 40 #px
    init = 100 #px
    grid = Canvas(win,width = init*2+9*size,height = init*2+9*size)
    lignes = []
    
    for k in range(10):
        lignes.append(grid.create_line(init+k*size,init,init+k*size,init+9*size,width=2*((k%3)==0)+1))
        lignes.append(grid.create_line(init,init+k*size,init+9*size,init+k*size,width=2*((k%3)==0)+1))
    
    grid.pack()

    labels = [[Label(win,text=int(s[i][j])) for j in range(9)]for i in range(9)]
    
    for i in range(9):
        for j in range(9):
            labels[i][j].place(x=init+13+j*size,y=init+13+i*size)
    fenetre.mainloop()

def getCarre(grid,i,j):
    """
    Cette fonction permet de récupérer le carré auquel appartient la case (i,j)
    """
    return(grid[i-i%3:i-i%3+3,j-j%3:j-j%3+3])

def getLigne(grid,i):
    """
    Cette fonction permet de récupérer la ligne i
    """
    return(grid[i])

def getColonne(grid,j):
    """
    Cette fonction permet de récupérer la colonne j
    """
    return(grid[:,j])

def Existe(i,grille):
    """
    Cette fonction détermine si la valeur i est présente dans le tableau grille
    """
    for k in grille:
        if k == i:
            return(True)
    return(False)


def afficher(grille):
    """
    Cette fonction permet d'afficher la grille de sudoku dans la console
    """
    for i in range(9):
        print("_______________________________________________________\n" if i%3==0 and i!=0 else "",end="")
        print("[",end='')
        for j in range(9):
            print("|  " if j%3==0 and j!=0 else "",end='')
            print(int(grille[i,j]) if len(str(grille[i,j]))==4 else " "+str(int(grille[i,j])),end='   ')
        print("]")
    print("\n")


def valeurs_possibles(grid,i,j,interdit):
    """
    Cette fonction permet de déterminer les valeurs possibles pour la case (i,j)
    """
    possible = []
    
    ligne=getLigne(grid,i)
    colonne=getColonne(grid,j)
    carr = getCarre(grid,i,j).ravel()
    for k in range(1,10):
        if not(Existe(k,ligne) or Existe(k,colonne) or Existe(k,carr) or Existe(k,interdit)):
            possible.append(k)
    if possible == []:
        return(None)
    return(possible)

def choixPossibles(grid,interdit):
    """
    Cette fonction permet de déterminer tous les choix possibles pour toutes les cases
    """
    mini = 9#pour trouver lequel a le moins de choix
    possibilites = [[[]for i in range(9)]for k in range(9)]
    ordre = None
    for i in range(9):
        for j in range(9):
            if grid[i,j] == 0:
                val_pos = valeurs_possibles(grid,i,j,interdit[i][j])
                try:
                    l = len(val_pos)
                except TypeError:
                    return(0,0)
                if l<mini:#on conserve la case qui a le moins de possibilites
                    ordre = (i,j)
                    mini=l
                possibilites[i][j] = val_pos
            else:
                possibilites[i][j] = [grid[i,j]]
    return(possibilites,ordre)

def retourArriere(grid,arbitraire,interdit):
    try:
        i,j,choix = arbitraire.pop()
        interdit[i][j].append(choix)
        grid[i,j] = 0
    except IndexError:
        print("remise a zero")
        grid = beginSudoku()
        interdit = [[[] for i in range(9)]for j in range(9)]
    return(grid, interdit)

def beginSudoku():
    """
    Fonction qui détermine au hasard les 16 premiers numeros du sudoku
    """
    grid = np.zeros((9,9))
    i=0
    j=0
    while 9*i+j < 16:
        ligne=getLigne(grid,i)
        colonne=getColonne(grid,j)
        carr = getCarre(grid,i,j)
        grid[i,j] = nvNb(ligne,colonne,carr)
        i += 1 if j>=8 else 0
        j += 1
        j %= 9
    return(grid)

def newSudoku():
    
    #Génération aléatoire des 16 premiers
    grid=beginSudoku()
    
    #Détermination des autres
    arbitraire = []
    interdit = [[[]for i in range(9)]for k in range(9)]
    possibilites, premier = choixPossibles(grid,interdit)
    afficher(grid)
    compteur = 0
    while len(arbitraire) < 65:
        try:
            i,j = premier
            choix = possibilites[i][j][0]
            grid[premier] = choix
            arbitraire.append((i,j,choix))
            possibilites,premier = choixPossibles(grid,interdit)
        except TypeError:
            #si aucun nombre n'est possible
            grid, interdit = retourArriere(grid,arbitraire,interdit)
            possibilites, premier = choixPossibles(grid,interdit)
        compteur += 1
    return(grid)

def nvNb(l,co,ca):
    dejaEssaye = []
    nb = rd.randint(1,9)
    while Existe(nb,l) or Existe(nb,co) or Existe(nb,ca.ravel()):
        dejaEssaye.append(nb)
        if len(dejaEssaye) == 9:
            return(-1)
        while(Existe(nb,dejaEssaye)):
            nb = rd.randint(1,9)
    return(nb)

sudoku = newSudoku()
drawGrid(fenetre,sudoku)
