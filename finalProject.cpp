#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Définition de la structure du livre
typedef struct Livre {
    char titre[100];
    char auteur[100];
    int anneePublication;
    int prix;
    struct Livre *suivant;
} Livre;

// Définition de la structure de la bibliothèque
typedef struct {
    Livre *tete;
    int nbLivres;
} Bibliotheque;

// Définition de la structure de la pile
typedef struct {
    Livre *sommet;
} Pile;

// Définition de la structure de la file
typedef struct {
    Livre *avant;
    Livre *arriere;
} File;

// Fonction pour créer un nouveau livre
Livre* creerLivre(char* titre, char* auteur, int anneePublication,int prix) {
    Livre* nouveauLivre = (Livre*) malloc(sizeof(Livre));
    strcpy(nouveauLivre->titre, titre);
    strcpy(nouveauLivre->auteur, auteur);
    nouveauLivre->prix=prix;
    nouveauLivre->anneePublication = anneePublication;
    nouveauLivre->suivant = NULL;
    return nouveauLivre;
}

// Fonction pour ajouter un livre à la bibliothèque
void ajouterLivre(Bibliotheque* biblio, Livre* livre) {
    livre->suivant = biblio->tete;
    biblio->tete = livre;
    biblio->nbLivres++;
}

// Fonction pour afficher les livres de la bibliothèque
void afficherBibliotheque(Bibliotheque* biblio) {
    Livre* courant = biblio->tete;
    while (courant != NULL) {
        printf("Titre: %s, Auteur: %s, Année de Publication: %d , Prix : %d \n", courant->titre, courant->auteur, courant->anneePublication , courant->prix);
        courant = courant->suivant;
    }
}

// Fonction pour initialiser la pile
void initPile(Pile* pile) {
    pile->sommet = NULL;
}

// Fonction pour empiler un livre (emprunt)
void empiler(Pile* pile, Livre* livre) {
    livre->suivant = pile->sommet;
    pile->sommet = livre;
}

// Fonction pour dépiler un livre (retourner)
Livre* depiler(Pile* pile) {
    if (pile->sommet == NULL) {
        printf("La pile est vide\n");
        return NULL;
    }
    Livre* livre = pile->sommet;
    pile->sommet = pile->sommet->suivant;
    return livre;
}

// Fonction pour initialiser la file
void initFile(File* file) {
    file->avant = NULL;
    file->arriere = NULL;
}

// Fonction pour enfiler un livre (retourner)
void enfiler(File* file, Livre* livre) {
    livre->suivant = NULL;
    if (file->arriere == NULL) {
        file->avant = livre;
        file->arriere = livre;
    } else {
        file->arriere->suivant = livre;
        file->arriere = livre;
    }
}

// Fonction pour défiler un livre (prendre)
Livre* defiler(File* file) {
    if (file->avant == NULL) {
        printf("La file est vide\n");
        return NULL;
    }
    Livre* livre = file->avant;
    file->avant = file->avant->suivant;
    if (file->avant == NULL) {
        file->arriere = NULL;
    }
    return livre;
}

// Fonction pour afficher le menu
void afficherMenu() {
    printf("\n--- Menu de la Bibliothèque ---\n");
    printf("1. Ajouter un livre\n");
    printf("2. Afficher les livres\n");
    printf("3. Emprunter un livre (empiler)\n");
    printf("4. Retourner un livre (depiler)\n");
    printf("5. pour afficher les livres d'un auteur donne\n");
    printf("6. pour compter le nombre des livres\n");
    printf("7. Quitter\n");
    printf("Choisissez une option: ");
}

int main() {
    Bibliotheque biblio = {.tete = NULL, .nbLivres = 0};
    Pile pile;
    File file;
    int choix,i,prix;
    char titre[100], auteur[100],a[100];
    int annee;
    Livre* livre;

    initPile(&pile);
    initFile(&file);

    while (1) {
        afficherMenu();
        scanf("%d", &choix);
        getchar();  // Consommer le caractère de nouvelle ligne après l'entrée

        switch (choix) {
            case 1:
                printf("Entrez le titre du livre: ");
                fgets(titre, 100, stdin);
                titre[strcspn(titre, "\n")] = '\0';  // Enlever le caractère de nouvelle ligne
                printf("Entrez l'auteur du livre: ");
                fgets(auteur, 100, stdin);
                auteur[strcspn(auteur, "\n")] = '\0';
                printf("Entrez l'année de publication: ");
                scanf("%d", &annee);
                printf("saisir le prix :");
                scanf("%d",&prix);
                livre = creerLivre(titre, auteur, annee,prix);
                ajouterLivre(&biblio, livre);
                printf("Livre ajouté avec succès\n");
                break;

            case 2:
                afficherBibliotheque(&biblio);
                break;

            case 3:
                if (biblio.tete == NULL) {
                    printf("Aucun livre disponible pour emprunter\n");
                } else {
                    livre = biblio.tete;
                    biblio.tete = biblio.tete->suivant;
                    biblio.nbLivres--;
                    empiler(&pile, livre);
                    printf("Livre emprunte avec succes\n");
                }
                break;

            case 4:
                livre = depiler(&pile);
                if (livre != NULL) {
                    enfiler(&file, livre);
                    printf("Livre retourne avec succes\n");
                }
                break;

          
                
            case 5: 
            printf("Saisir le nom de l'auteur : ");
                scanf(" %[^\n]", a); 
                printf("-------------------------------\n");
                for (i = 0; i < biblio.nbLivres; i++) {
                    if (strcmp(livre[i].auteur, a) == 0) {
                        printf("%s \t %.2f \n", livre[i].titre, livre[i].prix);
                    }
                }
                break;
                
            case 6: 
            printf("Le nombre de livres de la bibliotheque est : %d\n", biblio.nbLivres );
                printf("---------------------------\n");
                break;
            case 7:
                printf("Quitter le programme\n");
                // Libérer la mémoire allouée aux livres
                while (biblio.tete != NULL) {
                    livre = biblio.tete;
                    biblio.tete = biblio.tete->suivant;
                    free(livre);
                }
                while (pile.sommet != NULL) {
                    livre = pile.sommet;
                    pile.sommet = pile.sommet->suivant;
                    free(livre);
                }
                while (file.avant != NULL) {
                    livre = file.avant;
                    file.avant = file.avant->suivant;
                    free(livre);
                }
                exit(0);

            default:
                printf("Option invalide\n");
        }
    }

    return 0;
}
 
