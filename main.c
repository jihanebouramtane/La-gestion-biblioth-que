#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>
#include <time.h>
// Structure pour stocker les informations de l'utilisateur
typedef struct {
    char username[50];
    char password[50];
} UserInfo;

struct livre
{
    int code_livre;
    char titre_livre[50];
    int nbre_pages;
    char auteur[50];
    char disponible;
};
struct etudiant
{
    int cin;
    char nom_etudiant[50];
    char prenom_etudiant[50];
    int date_naissance_e[3];

};
struct emprunt
{   int dhe[5];
    int cin_emprunt;
    int code_livre_emprunt;
    int dhr[5];
};
struct livre tlivre[100];
struct etudiant tetudiant[100];
struct emprunt temprunt[100];
void gotoxy(int x,int y)
{
    HANDLE hConsoleOutput;
    COORD dwCursorPosition;
    dwCursorPosition.X = x;
    dwCursorPosition.Y = y;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);
}
void setColor(int textColor, int bgColor) {
    int color = textColor + (bgColor * 16);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
// Fonction pour v rifier les informations d'authentification de l'admin
int authenticateAdmin() {
    char adminNames[3][20] = {"malak", "jihane", "aissam"};
    char adminPassword[20] = "admin";

    char enteredName[20];
    char enteredPassword[20];
    system("cls");
    setColor(9,15);
    gotoxy(35, 0);
    printf("************************************************");
    gotoxy(35, 1);
    printf("*                                              *");
    setColor(14,5);
    gotoxy(35, 2);
    printf("*              Bibliotheque ENSAH              *");
    setColor(9,15);
    gotoxy(35, 3);
    printf("*                                              *");
    gotoxy(35, 4);
    printf("*                                              *");
    gotoxy(35, 5);
    printf("*                Connecter (Login)             *");
    gotoxy(35, 6);
    printf("*                                              *");
    gotoxy(35, 7);
    printf("* Entrez votre nom admin : |____________|      *");
    gotoxy(35,8);
    printf("* Entrez votre mot de passe : |____________|   *");
    gotoxy(35,9);
    printf("*                                              *");
    gotoxy(35,10);
    printf("************************************************");
    gotoxy(63,7);
    scanf("%s", enteredName);

    // V rifie le nom d'admin
    int isAdmin = 0;
    for (int i = 0; i < 3; ++i) {
        if (strcmp(enteredName, adminNames[i]) == 0) {
            isAdmin = 1;
            break;
        }
    }

    if (!isAdmin) {
        printf("Vous n' tes pas un admin.\n");
        return 0; // Retourne 0 pour indiquer que l'authentification a  chou
    }

    // Si le nom est correct, demande le mot de passe
    gotoxy(66, 8);
    scanf("%s", enteredPassword);

    // V rifie le mot de passe
    if (strcmp(enteredPassword, adminPassword) != 0) {
        printf("Mot de passe incorrect.\n");
        return 0; // Retourne 0 pour indiquer que l'authentification a  chou
    }
   setColor(15,0);
    return 1; // Retourne 1 pour indiquer que l'authentification a r ussi
}

// Nouvelle fonction pour l'interface de login et de cr ation de compte
int menu_login_signup() {
    int choice;
    do {
        system("cls");
        setColor(9,15);
        gotoxy(35, 0);
        printf("************************************************");
        gotoxy(35, 1);
        printf("*                                              *");
        setColor(14,5);
        gotoxy(35, 2);
        printf("*             Bibliotheque ENSAH               *");
        setColor(9,15);
        gotoxy(35, 3);
        printf("*                                              *");
        gotoxy(35, 4);
        printf("*                                              *");
        gotoxy(35, 5);
        printf("*                                              *");
        gotoxy(35, 6);
        printf("*        1- Cree un Compte (Sign up)           *");
        gotoxy(35, 7);
        printf("*        2- Connecter (Login)                  *");
        gotoxy(35, 8);
        printf("*        3- Quitter                            *");
        gotoxy(35, 9);
        printf("*                                   Choix : |_|*");
        gotoxy(35, 10);
        printf("************************************************");
        gotoxy(80, 9);
        scanf("%d", &choice);
    } while (choice < 1 || choice > 3);
    setColor(15,0);

    return choice;
}
void signup() {
    UserInfo user;
    FILE *userFile;

    system("cls");
    setColor(9,15);
    gotoxy(35, 1);
    printf("************************************************");
    gotoxy(35, 2);
    printf("*                                              *");
    setColor(15,9);
    gotoxy(35, 3);
    printf("*            Bibliotheque ENSAH                *");
    setColor(9,15);
    gotoxy(35, 4);
    printf("*                                              *");
    gotoxy(35, 5);
    printf("*                                              *");
    gotoxy(35, 6);
    printf("*            Cree un Compte (Sign up)          *");
    gotoxy(35, 7);
    printf("*                                              *");
    gotoxy(35, 8);
    printf("* Entrez votre nom d'utilisateur :|___________|*");
    gotoxy(35, 9);
    printf("* Entrez votre mot de passe :|___________|     *");
    gotoxy(35, 10);
    printf("*                                              *");
    gotoxy(35, 11);
    printf("************************************************");
     gotoxy(70, 8);
    scanf("%s", user.username);
     gotoxy(65, 9);
    scanf("%s", user.password);
    // Enregistrez les informations de l'utilisateur dans le fichier
    userFile = fopen("c:/PROJECT/users.txt", "a"); // Ouverture en mode ajout
    if (userFile == NULL) {
        printf("Erreur lors de l'ouverture du fichier des utilisateurs.\n");
        exit(1);
    }

    fprintf(userFile, "%s %s\n", user.username, user.password);

    fclose(userFile);

    printf("Compte cree avec succes !\n");
    setColor(15,0);
}



// Fonction pour v rifier si le compte existe
int doesUserExist(char *username, char *password) {
    FILE *userFile;
    char storedUsername[50];
    char storedPassword[50];

    userFile = fopen("c:/PROJECT/users.txt", "r");
    if (userFile == NULL) {
        printf("Erreur lors de l'ouverture du fichier des utilisateurs.\n");
        exit(1);
    }

    // Lisez le fichier utilisateur et v rifiez si les informations correspondent
    while (fscanf(userFile, "%s %s", storedUsername, storedPassword) != EOF) {
        if (strcmp(username, storedUsername) == 0 && strcmp(password, storedPassword) == 0) {
            fclose(userFile);
            return 1; // Le compte existe
        }
    }

    fclose(userFile);
    return 0; // Le compte n'existe pas
}
int login() {
    UserInfo user;
    char enteredUsername[50];
    char enteredPassword[50];

     system("cls");
     setColor(9,15);
    gotoxy(35, 1);
    printf("************************************************");
    gotoxy(35, 2);
    printf("*                                              *");
    setColor(15,9);
    gotoxy(35, 3);
    printf("*             Bibliotheque ENSAH               *");
    setColor(9,15);
    gotoxy(35, 4);
    printf("*                                              *");
    gotoxy(35, 5);
    printf("*                                              *");
    gotoxy(35, 6);
    printf("*                Connecter (Login)             *");
    gotoxy(35, 7);
    printf("*                                              *");
    gotoxy(35, 8);
    printf("* Entrez votre nom d'utilisateur :|___________|*");
    gotoxy(35, 9);
    printf("* Entrez votre mot de passe :|___________|     *");
    gotoxy(35, 10);
    printf("*                                              *");
    gotoxy(35, 11);
    printf("************************************************");
    gotoxy(70, 8); // Position du curseur pour le nom d'utilisateur
    scanf("%s", enteredUsername);
    gotoxy(65, 9);
    scanf("%s", enteredPassword);
    setColor(15,0);
    // V rifiez si le compte existe en appelant la fonction doesUserExist
    if (doesUserExist(enteredUsername, enteredPassword)) {
        printf("Connexion reussie !\n");
        return 1; // Connexion r ussie
    } else {
        printf("Nom d'utilisateur ou mot de passe incorrect.\n");
        return 0; // Connexion  chou e
    }
}




void extract_date(int date[])
{
    time_t x;
    time(&x);
    struct tm y=*(localtime(&x));
    date[1]=y.tm_mon+1;
    date[0]=y.tm_mday;
    date[2]=y.tm_year+1900;
}
void extract_time(int heure[])
{
    time_t x;
    time(&x);
    struct tm y=*(localtime(&x));
    heure[1]=y.tm_min;
    heure[0]=y.tm_hour;
}



struct livre tlivre[100]; // Supposons que vous avez une structure pour stocker les informations sur les livres.

int extract_info_Flivre() {
    FILE *Flivre;
    int n = 0;
    Flivre = fopen("c:/PROJECT/Flivre.txt", "a+"); // Mode "a+" ou "r+" pour permettre la lecture et l' criture
    if (Flivre == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return -1;
    }

    rewind(Flivre);

    while (fscanf(Flivre, "%d %s %d %c", &tlivre[n].code_livre, tlivre[n].titre_livre, &tlivre[n].nbre_pages, &tlivre[n].disponible) == 4) {
        n++;
    }

    fclose(Flivre);

    return n;
}

int extract_info_Fetudiant()
{
    FILE *Fetudiant;
    int p=0;
    Fetudiant=fopen("c:/PROJECT/Fetudiant.txt","a+");
    rewind(Fetudiant);
    do{
        fscanf(Fetudiant,"%d %s %s %d %d %d %d\n",&tetudiant[p].cin,tetudiant[p].nom_etudiant,tetudiant[p].prenom_etudiant,&tetudiant[p].date_naissance_e[0],&tetudiant[p].date_naissance_e[1],&tetudiant[p].date_naissance_e[2]);
        p+=1;
      }while(feof(Fetudiant)==0);
    fclose(Fetudiant);
   if ((p==1)&&(tetudiant[0].date_naissance_e[0]==0)&&(tetudiant[0].date_naissance_e[1]==0)&&(tetudiant[0].date_naissance_e[2]==0))
        return 0;
    else
        return p;
}
int extract_info_Fempruntretour()
{
    FILE *Fempruntretour;
    int q=0;
    Fempruntretour=fopen("c:/PROJECT/Fempruntretour.txt","a+");
    rewind(Fempruntretour);
    do{
        fscanf(Fempruntretour,"%d %d %d %d %d %d %d %d %d %d %d %d\n",&temprunt[q].dhe[0],&temprunt[q].dhe[1],&temprunt[q].dhe[2],&temprunt[q].dhe[3],&temprunt[q].dhe[4],&temprunt[q].cin_emprunt,&temprunt[q].code_livre_emprunt,&temprunt[q].dhr[0],&temprunt[q].dhr[1],&temprunt[q].dhr[2],&temprunt[q].dhr[3],&temprunt[q].dhr[4]);
        q+=1;
      }while(feof(Fempruntretour)==0);
    fclose(Fempruntretour);
   if ((q==1)&&(temprunt[q].dhe[4]==0)&&(temprunt[q].dhe[3]==0)&&(temprunt[q].dhe[2]==0))
        return 0;
    else
        return q;
}
int recherche_max(int tab[],int n)
{
    int i,max=tab[0];
    for (i=1;i<n;i++)
    if (tab[i]>max)
       max=tab[i];
    return max;
}
int recherche_min(int tab[],int n)
{
    int i,min=tab[0];
    for (i=1;i<n;i++)
    if (tab[i]<min)
       min=tab[i];
    return min;
}

void affichage_livre(int n)
{
    int i;
    gotoxy(32,12);
    printf("______________________________________________________");
    gotoxy(32,13);
    printf("| Code Livre | Titre Livre | Nbre Pages | disponible |");
    gotoxy(32,14);
    printf("______________________________________________________");
    for(i=0;i<n;i++)
    {
        gotoxy(32,15+i);
        printf("| %d",tlivre[i].code_livre);
        gotoxy(45,15+i);
        printf("| %s",tlivre[i].titre_livre);
        gotoxy(59,15+i);
        printf("| %d",tlivre[i].nbre_pages);
        gotoxy(72,15+i);
        printf("| %c",tlivre[i].disponible);
        gotoxy(85,15+i);
        printf("|");
    }
    gotoxy(32,15+n);
    printf("______________________________________________________");
}
void affichage_etudiant(int p)
{
    int i;
    gotoxy(29,12);
    printf("_____________________________________________________________");
    gotoxy(29,13);
    printf("|   CIN   | Nom etudiant | Prenom etudiant | Date naissance | ");
    gotoxy(29,14);
    printf("_____________________________________________________________");
    for(i=0;i<p;i++)
    {
        gotoxy(29,15+i);
        printf("| %d",tetudiant[i].cin);
        gotoxy(39,15+i);
        printf("| %s",tetudiant[i].nom_etudiant);
        gotoxy(54,15+i);
        printf("| %s",tetudiant[i].prenom_etudiant);
        gotoxy(72,15+i);
        printf("| %d/%d/%d",tetudiant[i].date_naissance_e[0],tetudiant[i].date_naissance_e[1],tetudiant[i].date_naissance_e[2]);
        gotoxy(89,15+i);
        printf("|");
    }
    gotoxy(29,15+p);
    printf("_____________________________________________________________");
}
void affichage_emprunt_retour(int q)
{
    int i;
    gotoxy(30,12);
    printf("___________________________________________________________");
    gotoxy(30,13);
    printf("|  Date Emprunt  |   CIN   | Code Livre |   Date Retour   |");
    gotoxy(30,14);
    printf("___________________________________________________________");
    for(i=0;i<q;i++)
    {
        gotoxy(30,15+i);
        printf("| %d:%d %d/%d/%d",temprunt[i].dhe[0],temprunt[i].dhe[1],temprunt[i].dhe[2],temprunt[i].dhe[3],temprunt[i].dhe[4]);
        gotoxy(47,15+i);
        printf("| %d",temprunt[i].cin_emprunt);
        gotoxy(57,15+i);
        printf("| %d",temprunt[i].code_livre_emprunt);
        gotoxy(70,15+i);
        printf("| %d:%d %d/%d/%d",temprunt[i].dhr[0],temprunt[i].dhr[1],temprunt[i].dhr[2],temprunt[i].dhr[3],temprunt[i].dhr[4]);
        gotoxy(88,15+i);
        printf("|");
    }
    gotoxy(30,15+q);
    printf("___________________________________________________________");
}

int test_integer(char test[])
{
    int i,b=0;
    for(i=0;i<strlen(test);i++)
        if (!isdigit(test[i]))
           b=1;
    return b;
}
int test_float(char test[])
{
    int i,j=0,b=0,c=0;
    for(i=0;i<strlen(test);i++)
    {
        if (!isdigit(test[i])&&(test[i]!='.'))
           b=1;
        else if (test[i]=='.')
           j+=1;
    }
    if ((j>1)||(b==1))
        c=1;
    return c;
}
int test_alpaha(char test[])
{
    int i,b=0;
    for(i=0;i<strlen(test);i++)
        if (!isalpha(test[i]))
           b=1;
    return b;
}

int verif_livre(int n, int code_livre)
{
    int i,b=-1;
    for(i=0;i<n;i++)
    {
        if (tlivre[i].code_livre==code_livre)
            b=i;
    }
    return b;
}
int verif_etudiant(int p, int cin)
{
    int i,b=-1;
    for(i=0;i<p;i++)
    {
        if (tetudiant[i].cin==cin)
            b=i;
    }
    return b;
}
int verif_emprunt(int q,int code_livre)
{
    int i,b=-1;
    for(i=0;i<q;i++)
    {
        if (temprunt[i].code_livre_emprunt==code_livre)
            b=i;
    }
    return b;
}

void interface_nouveau_livre()
{
    system("cls");
    setColor(0,15);
    gotoxy(35,0);
    printf("************************************************");
    gotoxy(35,1);
    printf("*         Creation d'un nouveau livre          *");
    gotoxy(35,2);
    printf("*                                              *");
    gotoxy(35,3);
    printf("*                                              *");
    gotoxy(35,4);
    printf("* Code Livre    : |__________|                 *");
    gotoxy(35,5);
    printf("* Titre Livre   : |__________|                 *");
    gotoxy(35,6);
    printf("* Nbre Pages    : |__________|                 *");
    gotoxy(35,7);
    printf("* Disponible O/N : |_|                         *");
    gotoxy(35,8);
    printf("*                                              *");
    gotoxy(35,9);
    printf("*                                              *");
    gotoxy(35,10);
    printf("*                                              *");
    gotoxy(35,11);
    printf("*                                              *");
    gotoxy(35,12);
    printf("* Voulez-vous ajouter un autre livre O/N : |_| *");
    gotoxy(35,13);
    printf("************************************************");
    setColor(15,0);
}
void interface_ajout_etudiant()
{
    system("cls");
    setColor(0,15);
    gotoxy(35,0);
    printf("************************************************");
    gotoxy(35,1);
    printf("*             Ajout d'un etudiant              *");
    gotoxy(35,2);
    printf("*                                              *");
    gotoxy(35,3);
    printf("*                                              *");
    gotoxy(35,4);
    printf("* CIN            : |__________|                *");
    gotoxy(35,5);
    printf("* Nom etudiant   : |__________|                *");
    gotoxy(35,6);
    printf("* Prenom etudiant: |__________|                *");
    gotoxy(35,7);
    printf("* Date naissance : |__/__/____|                *");
    gotoxy(35,8);
    printf("*                                              *");
    gotoxy(35,9);
    printf("*                                              *");
    gotoxy(35,10);
    printf("*Voulez-vous ajouter un autre etudiant O/N: |_|*");
    gotoxy(35,11);
    printf("************************************************");
     setColor(15,0);
}

int saisie_code_livre()
{
    char test[50];
    do{
        interface_nouveau_livre();
        gotoxy(54,4);
        scanf("%s",test);
      }while((test_integer(test)==1)||(strlen(test)>10));
    return atoi(test);
}
int saisie_cin()
{
    char test[50];
    do{
        interface_ajout_etudiant();
        gotoxy(55,4);
        scanf("%s",test);
      }while((test_integer(test)==1)||(strlen(test)>8));
    return atoi(test);
}


void saisie_nom_etudiant(char test[],int cin)
{
    do{
        interface_ajout_etudiant();
        gotoxy(55,4);
        printf("%d",cin);
        gotoxy(55,5);
        scanf("%s",test);
      }while((test_alpaha(test)==1)||(strlen(test)>10));
}
void saisie_prenom_etudian(char test[],int cin,char nom_etudiant[])
{
    do{
        interface_ajout_etudiant();
        gotoxy(55,4);
        printf("%d",cin);
        gotoxy(55,5);
        printf("%s",nom_etudiant);
        gotoxy(55,6);
        scanf("%s",test);
      }while((test_alpaha(test)==1)||(strlen(test)>10));
}
void saisie_titre_livre(char test[],int code_livre)
{
    do{
        interface_nouveau_livre();
        gotoxy(54,4);
        printf("%d",code_livre);
        gotoxy(54,5);
        scanf("%s",test);
      }while((test_alpaha(test)==1)||(strlen(test)>10));
}
int saisie_nbre_pages(int code_livre,char titre_livre[])
{
    char test[50];
    do{
        interface_nouveau_livre();
        gotoxy(54,4);
        printf("%d",code_livre);
        gotoxy(54,5);
        printf("%s",titre_livre);
        gotoxy(54,6);
        scanf("%s",test);
      }while((test_integer(test)==1)||(strlen(test)>10));
    return atoi(test);
}


int saisie_annee_etudiant(int cin,char nom_etudiant[],char prenom_etudiant[])
{
    char test[50];
    int annee,date[3];
    extract_date(date);
    do{
        do{
            interface_ajout_etudiant();
            gotoxy(55,4);
            printf("%d",cin);
            gotoxy(55,5);
            printf("%s",nom_etudiant);
            gotoxy(55,6);
            printf("%s",prenom_etudiant);
            gotoxy(61,7);
            scanf("%s",test);
          }while(test_integer(test)==1);
        annee=atoi(test);
      }while((annee>date[2])||(annee<1));
    return annee;
}

int saisie_mois_etudiant(int cin,char nom_etudiant[],char prenom_etudiant[],int annee)
{
    char test[50];
    int mois,date[3];
    extract_date(date);
    do{
        do{
            interface_ajout_etudiant();
            gotoxy(55,4);
            printf("%d",cin);
            gotoxy(55,5);
            printf("%s",nom_etudiant);
            gotoxy(55,6);
            printf("%s",prenom_etudiant);
            gotoxy(61,7);
            printf("%d",annee);
            gotoxy(58,7);
            scanf("%s",test);
          }while((test_integer(test)==1)||(strlen(test)>2));
        mois=atoi(test);
      }while((mois<1)||(mois>12)||((date[2]==annee)&&(date[1]<mois)));
    return mois;
}
int verif_jour(int annee,int mois,int jour)
{
    int b=0;
    if (((mois==1)||(mois==3)||(mois==5)||(mois==7)||(mois==8)||(mois==10)||(mois==12))&&(jour<=31))
        b=1;
    else if (((mois==4)||(mois==6)||(mois==9)||(mois==11))&&(jour<=30))
            b=1;
    else if ((mois==2)&&(((annee-1500)%4)==0)&&(jour<=29))
            b=1;
    else if ((mois==2)&&(jour<=28))
            b=1;
    return b;
}

int saisie_jour_etudiant(int cin,char nom_etudiant[],char prenom_etudiant[],int annee,int mois)
{
    char test[50];
    int jour,date[3];
    extract_date(date);
    do{
        do{
            interface_ajout_etudiant();
            gotoxy(55,4);
            printf("%d",cin);
            gotoxy(55,5);
            printf("%s",nom_etudiant);
            gotoxy(55,6);
            printf("%s",prenom_etudiant);
            gotoxy(61,7);
            printf("%d",annee);
            gotoxy(58,7);
            printf("%d",mois);
            gotoxy(55,7);
            scanf("%s",test);
          }while(test_integer(test)==1);
        jour=atoi(test);
      }while((jour<1)||(verif_jour(annee,mois,jour)==0)||((date[2]==annee)&&(date[1]==mois)&(date[0]<jour)));
    return jour;
}


void saisie_date_naissance_e(int cin,char nom_etudiant[],char prenom_etudiant[],int date_naissance_e[])
{
    date_naissance_e[2]=saisie_annee_etudiant(cin,nom_etudiant,prenom_etudiant);
    date_naissance_e[1]=saisie_mois_etudiant(cin,nom_etudiant,prenom_etudiant,date_naissance_e[2]);
    date_naissance_e[0]=saisie_jour_etudiant(cin,nom_etudiant,prenom_etudiant,date_naissance_e[2],date_naissance_e[1]);
}

int creation_nouveau_livre(int n)
{
    FILE *Flivre;
    char b='N';
    int code_livre;
    do{
        code_livre=saisie_code_livre();
        if (verif_livre(n,code_livre)==-1)
        {
            tlivre[n].code_livre=code_livre;
            saisie_titre_livre(tlivre[n].titre_livre,code_livre);
            tlivre[n].nbre_pages=saisie_nbre_pages(code_livre,tlivre[n].titre_livre);
            gotoxy(55,11);
            printf("%c",'O');
            tlivre[n].disponible='O';
            do{
                interface_nouveau_livre();
                gotoxy(54,4);
                printf("%d",code_livre);
                gotoxy(54,5);
                printf("%s",tlivre[n].titre_livre);
                gotoxy(54,6);
                printf("%d",tlivre[n].nbre_pages);
                gotoxy(55,7);
                printf("%c",'O');
                gotoxy(79,12);
                fflush(stdin);
                scanf("%c",&b);
              }while((toupper(b)!='O')&&(toupper(b)!='N'));
            Flivre=fopen("c:/PROJECT/Flivre.txt","a");
            fprintf(Flivre,"%d %s %d %c\n",code_livre,tlivre[n].titre_livre,tlivre[n].nbre_pages,tlivre[n].disponible);
            fclose(Flivre);
            n+=1;
        }
        else
        {
            do{
                interface_nouveau_livre();
                gotoxy(54,4);
                printf("%d",code_livre);
                gotoxy(46,13);
                printf("\"ce code livre est utilise\"");
                gotoxy(79,14);
                fflush(stdin);
                scanf("%c",&b);
              }while((toupper(b)!='O')&&(toupper(b)!='N'));
        }
      }while(toupper(b)=='O');
    return n;
}
int ajout_nouvel_etudiant(int p)
{
    FILE *Fetudiant;
    char b='N';
    int cin;
    do{
        cin=saisie_cin();
        if (verif_etudiant(p,cin)==-1)
        {
            tetudiant[p].cin=cin;
            saisie_nom_etudiant(tetudiant[p].nom_etudiant,cin);
            saisie_prenom_etudian(tetudiant[p].prenom_etudiant,cin,tetudiant[p].nom_etudiant);
            saisie_date_naissance_e(cin,tetudiant[p].nom_etudiant,tetudiant[p].prenom_etudiant,tetudiant[p].date_naissance_e);
            do{
                interface_ajout_etudiant();
                gotoxy(55,4);
                printf("%d",cin);
                gotoxy(55,5);
                printf("%s",tetudiant[p].nom_etudiant);
                gotoxy(55,6);
                printf("%s",tetudiant[p].prenom_etudiant);
                gotoxy(61,7);
                printf("%d",tetudiant[p].date_naissance_e[2]);
                gotoxy(58,7);
                printf("%d",tetudiant[p].date_naissance_e[1]);
                gotoxy(55,7);
                printf("%d",tetudiant[p].date_naissance_e[0]);
                gotoxy(80,10);
                fflush(stdin);
                scanf("%c",&b);
              }while((toupper(b)!='O')&&(toupper(b)!='N'));
            Fetudiant=fopen("c:/PROJECT/Fetudiant.txt","a");
            fprintf(Fetudiant,"%d %s %s %d %d %d \n",cin,tetudiant[p].nom_etudiant,tetudiant[p].prenom_etudiant,tetudiant[p].date_naissance_e[0],tetudiant[p].date_naissance_e[1],tetudiant[p].date_naissance_e[2]);
            fclose(Fetudiant);
            p+=1;
        }
        else
        {
            do{
                interface_ajout_etudiant();
                gotoxy(55,4);
                printf("%d",cin);
                gotoxy(46,10);
                printf("\"ce code etudiant est utilise\"");
                gotoxy(80,11);
                fflush(stdin);
                scanf("%c",&b);
              }while((toupper(b)!='O')&&(toupper(b)!='N'));
        }
      }while(toupper(b)=='O');
    return p;
}

void interface_code_livre_modifier()
{
    system("cls");
    setColor(0,15);
    gotoxy(35,0);
    printf("************************************************");
    gotoxy(35,1);
    printf("*    Saisissez le code du livre a modifier     *");
    gotoxy(35,2);
    printf("*                                              *");
    gotoxy(35,3);
    printf("*                                              *");
    gotoxy(35,4);
    printf("* Code Livre    : |__________|                 *");
    gotoxy(35,5);
    printf("*                                              *");
    gotoxy(35,6);
    printf("*                                              *");
    gotoxy(35,7);
    printf("*        Appuez sur Entree pour valider        *");
    gotoxy(35,8);
    printf("************************************************");
    setColor(15,0);
}
void interface_cin_modifier()
{
    system("cls");
    setColor(0,15);
    gotoxy(35,0);
    printf("************************************************");
    gotoxy(35,1);
    printf("*  Saisissez le CIN de l'etudiant a modifier   *");
    gotoxy(35,2);
    printf("*                                              *");
    gotoxy(35,3);
    printf("*                                              *");
    gotoxy(35,4);
    printf("*        CIN    : |__________|                 *");
    gotoxy(35,5);
    printf("*                                              *");
    gotoxy(35,6);
    printf("*                                              *");
    gotoxy(35,7);
    printf("*        Appuez sur Entree pour valider        *");
    gotoxy(35,8);
    printf("************************************************");
    setColor(15,0);
}

int saisie_code_livre_m()
{
    char test[50];
    do{
        interface_code_livre_modifier();
        gotoxy(54,4);
        scanf("%s",test);
      }while((test_integer(test)==1)||(strlen(test)>10));
    return atoi(test);
}
int saisie_cin_m()
{
    char test[50];
    do{
        interface_cin_modifier();
        gotoxy(54,4);
        scanf("%s",test);
      }while((test_integer(test)==1)||(strlen(test)>10));
    return atoi(test);
}

void interface_modification_livre(int code_livre_m)
{
    system("cls");
    setColor(0,15);
    gotoxy(35,0);
    printf("************************************************");
    gotoxy(35,1);
    printf("*        modification du livre  %d              ",code_livre_m);
    gotoxy(82,1);
    printf("*");
    gotoxy(35,2);
    printf("*                                              *");
    gotoxy(35,3);
    printf("*                                              *");
    gotoxy(35,4);
    printf("* Titre Livre   : |__________|                 *");
    gotoxy(35,5);
    printf("* Nbre Pages    : |__________|                 *");
    gotoxy(35,6);
    printf("*                                              *");
    gotoxy(35,7);
    printf("*                                              *");
    gotoxy(35,8);
    printf("*Voulez-vous confirmer la modification O/N :|_|*");
    gotoxy(35,9);
    printf("************************************************");
    setColor(15,0);
}
void interface_modification_etudiant(int cin)
{
    system("cls");
    setColor(0,15);
    gotoxy(35,0);
    printf("************************************************");
    gotoxy(35,1);
    printf("*      modification de l'etudiant %d           ",cin);
    gotoxy(82,1);
    printf("*");
    gotoxy(35,2);
    printf("*                                              *");
    gotoxy(35,3);
    printf("*                                              *");
    gotoxy(35,4);
    printf("* Nom etudiant   : |__________|                *");
    gotoxy(35,5);
    printf("* Prenom etudiant: |__________|                *");
    gotoxy(35,6);
    printf("* Date naissance : |__/__/____|                *");
    gotoxy(35,7);
    printf("*                                              *");
    gotoxy(35,8);
    printf("*                                              *");
    gotoxy(35,9);
    printf("*                                              *");
    gotoxy(35,10);
    printf("*Voulez-vous confirmer la modification O/N :|_|*");
    gotoxy(35,11);
    printf("************************************************");
    setColor(15,0);
}


void saisie_nom_etudiant_m(char test[],int cin)
{
    system("cls");
    do{
        interface_modification_etudiant(cin);
        gotoxy(55,4);
        scanf("%s",test);
      }while((test_alpaha(test)==1)||(strlen(test)>10));
}
void saisie_prenom_etudiant_m(char test[],int cin,char nom_etudiant_m[])
{
    system("cls");
    do{
        interface_modification_etudiant(cin);
        gotoxy(55,4);
        printf("%s",nom_etudiant_m);
        gotoxy(55,5);
        scanf("%s",test);
      }while((test_alpaha(test)==1)||(strlen(test)>10));
}
void saisie_titre_livre_m(char test[],int code_livre_m)
{
    system("cls");
    do{
        interface_modification_livre(code_livre_m);
        gotoxy(54,4);
        scanf("%s",test);
      }while((test_alpaha(test)==1)||(strlen(test)>10));
}
int saisie_nbre_pages_m(int code_livre_m,char titre_livre_m[])
{
    char test[50];
    do{
        interface_modification_livre(code_livre_m);
        gotoxy(54,4);
        printf("%s",titre_livre_m);
        gotoxy(54,5);
        scanf("%s",test);
      }while((test_integer(test)==1)||(strlen(test)>10));
    return atoi(test);
}


int saisie_annee_etudiant_m(int cin,char nom_etudiant_m[],char prenom_etudiant_m[])
{
    char test[50];
    int annee,date[3];
    extract_date(date);
    do{
        do{
            interface_modification_etudiant(cin);
            gotoxy(55,4);
            printf("%s",nom_etudiant_m);
            gotoxy(55,5);
            printf("%s",prenom_etudiant_m);
            gotoxy(61,6);
            scanf("%s",test);
          }while(test_integer(test)==1);
        annee=atoi(test);
      }while((annee>date[2])||(annee<1));
    return annee;
}

int saisie_mois_etudiant_m(int cin,char nom_etudiant_m[],char prenom_etudiant_m[],int annee_m)
{
    char test[50];
    int mois,date[3];
    extract_date(date);
    do{
        do{
            interface_modification_etudiant(cin);
            gotoxy(55,4);
            printf("%s",nom_etudiant_m);
            gotoxy(55,5);
            printf("%s",prenom_etudiant_m);
            gotoxy(61,6);
            printf("%d",annee_m);
            gotoxy(58,6);
            scanf("%s",test);
          }while((test_integer(test)==1)||(strlen(test)>2));
        mois=atoi(test);
      }while((mois<1)||(mois>12)||((date[2]==annee_m)&&(date[1]<mois)));
    return mois;
}

int saisie_jour_etudiant_m(int cin,char nom_etudiant_m[],char prenom_etudiant_m[],int annee_m,int mois_m)
{
    char test[50];
    int jour,date[3];
    extract_date(date);
    do{
        do{
            interface_modification_etudiant(cin);
            gotoxy(55,4);
            printf("%s",nom_etudiant_m);
            gotoxy(55,5);
            printf("%s",prenom_etudiant_m);
            gotoxy(61,6);
            printf("%d",annee_m);
            gotoxy(58,6);
            printf("%d",mois_m);
            gotoxy(55,6);
            scanf("%s",test);
          }while(test_integer(test)==1);
        jour=atoi(test);
      }while((jour<1)||(verif_jour(annee_m,mois_m,jour)==0)||((date[2]==annee_m)&&(date[1]==mois_m)&(date[0]<jour)));
    return jour;
}


void saisie_date_naissance_e_m(int cin,char nom_etudiant_m[],char prenom_etudiant_m[],int date_naissance_e_m[])
{
    date_naissance_e_m[2]=saisie_annee_etudiant_m(cin,nom_etudiant_m,prenom_etudiant_m);
    date_naissance_e_m[1]=saisie_mois_etudiant_m(cin,nom_etudiant_m,prenom_etudiant_m,date_naissance_e_m[2]);
    date_naissance_e_m[0]=saisie_jour_etudiant_m(cin,nom_etudiant_m,prenom_etudiant_m,date_naissance_e_m[2],date_naissance_e_m[1]);
}

void modification_livre(int n)
{
    FILE *Flivre;
    int code_livre_m,i,d,nbre_pages_m,date_achat_m[3];
    char titre_livre_m[10],b,c;
    do{
        d=0;
        code_livre_m=saisie_code_livre_m();
        i=verif_livre(n,code_livre_m);
        if (i!=-1)
        {
            saisie_titre_livre_m(titre_livre_m,code_livre_m);
            nbre_pages_m=saisie_nbre_pages_m(code_livre_m,titre_livre_m);
            do{
                gotoxy(80,8);
                fflush(stdin);
                scanf("%c",&b);
              }while((toupper(b)!='O')&&(toupper(b)!='N'));
            if (toupper(b)=='O')
            {
                strcpy(tlivre[i].titre_livre,titre_livre_m);
                tlivre[i].nbre_pages=nbre_pages_m;

            }
        }
        else
        {
            do{
                interface_code_livre_modifier();
                gotoxy(54,4);
                printf("%d",code_livre_m);
                gotoxy(47,5);
                printf("\"code livre invalide\"");
                gotoxy(37,6);
                printf("voulez-vous modifier un livre O/N : |_|");
                gotoxy(76,6);
                fflush(stdin);
                scanf("%c",&c);
              }while((toupper(c)!='O')&&(toupper(c)!='N'));
              if (toupper(c)=='O')
                 d=1;
        }
      }while(d==1);
      Flivre=fopen("c:/PROJECT/Flivre.txt","w");
      for(i=0;i<n;i++)
      fprintf(Flivre,"%d %s %d %c\n",tlivre[i].code_livre,tlivre[i].titre_livre,tlivre[i].nbre_pages,tlivre[i].disponible);
      fclose(Flivre);
}
void modification_etudiant(int p)
{
    FILE *Fetudiant;
    int cin_m,i,d,date_naissance_e_m[3],code_classe_m;
    char nom_etudiant_m[10],b,c,prenom_etudiant_m[10];
    do{
        d=0;
        cin_m=saisie_cin_m();
        i=verif_etudiant(p,cin_m);
        if (i!=-1)
        {
            saisie_nom_etudiant_m(nom_etudiant_m,cin_m);
            saisie_prenom_etudiant_m(prenom_etudiant_m,cin_m,nom_etudiant_m);
            saisie_date_naissance_e_m(cin_m,nom_etudiant_m,prenom_etudiant_m,date_naissance_e_m);
            do{
                gotoxy(80,10);
                fflush(stdin);
                scanf("%c",&b);
              }while((toupper(b)!='O')&&(toupper(b)!='N'));
            if (toupper(b)=='O')
            {
                strcpy(tetudiant[i].nom_etudiant,nom_etudiant_m);
                strcpy(tetudiant[i].prenom_etudiant,prenom_etudiant_m);
                tetudiant[i].date_naissance_e[2]=date_naissance_e_m[2];
                tetudiant[i].date_naissance_e[1]=date_naissance_e_m[1];
                tetudiant[i].date_naissance_e[0]=date_naissance_e_m[0];
            }
        }
        else
        {
            do{
                interface_cin_modifier();
                gotoxy(54,4);
                printf("%d",cin_m);
                gotoxy(50,5);
                printf("\"CIN invalide\"");
                gotoxy(37,6);
                printf("voulez-vous modifier un etudiant O/N : |_|");
                gotoxy(77,6);
                fflush(stdin);
                scanf("%c",&c);
              }while((toupper(c)!='O')&&(toupper(c)!='N'));
              if (toupper(c)=='O')
                 d=1;
        }
      }while(d==1);
      Fetudiant=fopen("c:/PROJECT/Fetudiant.txt","w");
      for(i=0;i<p;i++)
      fprintf(Fetudiant,"%d %s %s %d %d %d\n",tetudiant[i].cin,tetudiant[i].nom_etudiant,tetudiant[i].prenom_etudiant,tetudiant[i].date_naissance_e[0],tetudiant[i].date_naissance_e[1],tetudiant[i].date_naissance_e[2]);
      fclose(Fetudiant);
}

void interface_suppression_livre()
{
    system("cls");
    setColor(0,15);
    gotoxy(35,0);
    printf("************************************************");
    gotoxy(35,1);
    printf("*    Saisissez le code du livre a supprimer    *");
    gotoxy(35,2);
    printf("*                                              *");
    gotoxy(35,3);
    printf("*                                              *");
    gotoxy(35,4);
    printf("* Code Livre    : |__________|                 *");
    gotoxy(35,5);
    printf("*                                              *");
    gotoxy(35,6);
    printf("*                                              *");
    gotoxy(35,7);
    printf("*        Appuez sur Entree pour valider        *");
    gotoxy(35,8);
    printf("*                la suppression                *");
    gotoxy(35,9);
    printf("************************************************");
    setColor(15,0);
}
void interface_suppression_etudiant()
{
    system("cls");
    setColor(0,15);
    gotoxy(35,0);
    printf("************************************************");
    gotoxy(35,1);
    printf("*  Saisissez le CIN de l'etudiant a supprimer  *");
    gotoxy(35,2);
    printf("*                                              *");
    gotoxy(35,3);
    printf("*                                              *");
    gotoxy(35,4);
    printf("*        CIN    : |__________|                 *");
    gotoxy(35,5);
    printf("*                                              *");
    gotoxy(35,6);
    printf("*                                              *");
    gotoxy(35,7);
    printf("*        Appuez sur Entree pour valider        *");
    gotoxy(35,8);
    printf("*                la suppression                *");
    gotoxy(35,9);
    printf("************************************************");
    setColor(15,0);
}

int saisie_code_livre_supp()
{
    char test[50];
    do{
        interface_suppression_livre();
        gotoxy(54,4);
        scanf("%s",test);
      }while((test_integer(test)==1)||(strlen(test)>10));
    return atoi(test);
}
int saisie_cin_supp()
{
    char test[50];
    do{
        interface_suppression_etudiant();
        gotoxy(54,4);
        scanf("%s",test);
      }while((test_integer(test)==1)||(strlen(test)>10));
    return atoi(test);
}

int suppression_livre(int n)
{
   FILE *Flivre;
   int code_livre_sup,i,j,d;
    char c;
    do{
        d=0;
        code_livre_sup=saisie_code_livre_supp();
        i=verif_livre(n,code_livre_sup);
        if (i!=-1)
        {
            for(j=i;j<(n-1);j++)
            {
                tlivre[j].code_livre=tlivre[j+1].code_livre;
                strcpy(tlivre[j].titre_livre,tlivre[j+1].titre_livre);
                tlivre[j].nbre_pages=tlivre[j+1].nbre_pages;
                tlivre[j].disponible=tlivre[j+1].disponible;
            }
        }
        else
        {
            do{
                interface_suppression_livre();
                gotoxy(54,4);
                printf("%d",code_livre_sup);
                gotoxy(47,5);
                printf("\"code livre invalide\"");
                gotoxy(37,6);
                printf("voulez-vous supprimer un livre O/N : |_|");
                gotoxy(75,6);
                fflush(stdin);
                scanf("%c",&c);
              }while((toupper(c)!='O')&&(toupper(c)!='N'));
                if (toupper(c)=='O')
                    d=1;
        }
      }while (d==1);
      Flivre=fopen("c:/PROJECT/Flivre.txt","w");
      for(i=0;i<n-1;i++)
      fprintf(Flivre,"%d %s %d %c\n",tlivre[i].code_livre,tlivre[i].titre_livre,tlivre[i].nbre_pages,tlivre[i].disponible);
      fclose(Flivre);
      return (n-1);
}
int suppression_etudiant(int p)
{
    FILE *Fetudiant;
    int cin,i,j,d;
    char c;
    do{
        d=0;
        cin=saisie_cin_supp();
        i=verif_etudiant(p,cin);
        if (i!=-1)
        {
            for(j=i;j<(p-1);j++)
            {
                tetudiant[j].cin=tetudiant[j+1].cin;
                strcpy(tetudiant[j].nom_etudiant,tetudiant[j+1].nom_etudiant);
                strcpy(tetudiant[j].prenom_etudiant,tetudiant[j+1].prenom_etudiant);
                tetudiant[j].date_naissance_e[2]=tetudiant[j+1].date_naissance_e[2];
                tetudiant[j].date_naissance_e[1]=tetudiant[j+1].date_naissance_e[1];
                tetudiant[j].date_naissance_e[0]=tetudiant[j+1].date_naissance_e[0];

            }
        }
        else
        {
            do{
                interface_suppression_etudiant();
                gotoxy(54,4);
                printf("%d",cin);
                gotoxy(47,5);
                printf("\"code auteur invalide\"");
                gotoxy(37,6);
                printf("voulez-vous supprimer un etudiant O/N : |_|");
                gotoxy(78,6);
                fflush(stdin);
                scanf("%c",&c);
              }while((toupper(c)!='O')&&(toupper(c)!='N'));
                if (toupper(c)=='O')
                    d=1;
        }
      }while (d==1);
      Fetudiant=fopen("c:/PROJECT/Fetudiant.txt","w");
      for(i=0;i<p-1;i++)
      fprintf(Fetudiant,"%d %s %s %d %d %d\n",tetudiant[i].cin,tetudiant[i].nom_etudiant,tetudiant[i].prenom_etudiant,tetudiant[i].date_naissance_e[0],tetudiant[i].date_naissance_e[1],tetudiant[i].date_naissance_e[2]);
      fclose(Fetudiant);
      return (p-1);
}

int menu_gestion_livre(int n)
{
    int a;
    do{
        do{
            system("cls");
            setColor(9,15);
            gotoxy(35,0);
            printf("************************************************");
            gotoxy(35,1);
            printf("*                                              *");
            setColor(15,9);
            gotoxy(35,2);
            printf("*            Gestion des Livres                *");
            setColor(9,15);
            gotoxy(35,3);
            printf("*                                              *");
            gotoxy(35,4);
            printf("*                                              *");
            gotoxy(35,5);
            printf("*        1-Creation d un nouveau livre         *");
            gotoxy(35,6);
            printf("*        2-Modification d'un livre existant    *");
            gotoxy(35,7);
            printf("*        3-Suppression d'un livre existant     *");
            gotoxy(35,8);
            printf("*        4-Quitter                             *");
            gotoxy(35,9);
            printf("*                                              *");
            gotoxy(35,10);
            printf("*                                   Choix : |_|*");
            gotoxy(35,11);
            printf("************************************************");
            setColor(15,0);
            affichage_livre(n);
            setColor(9,15);
            gotoxy(80,10);
            scanf("%d",&a);
          }while((a<1)||(a>4));
          setColor(15,0);
        switch(a)
        {
        case 1:
            n=creation_nouveau_livre(n);
            break;
        case 2:
            modification_livre(n);
            break;
        case 3:
            n=suppression_livre(n);
            break;
        case 4:
            break;
        }
      }while (a!=4);
    return n;
}
int menu_gestion_etudiants(int p)
{
    int a;
    do{
        do{
            system("cls");
            setColor(15,9);
            gotoxy(35,0);
            printf("************************************************");
            gotoxy(35,1);
            printf("*                                              *");
            setColor(9,15);
            gotoxy(35,2);
            printf("*            Gestion des etudiants             *");
            setColor(15,9);
            gotoxy(35,3);
            printf("*                                              *");
            gotoxy(35,4);
            printf("*                                              *");
            gotoxy(35,5);
            printf("*       1-Ajout d'un nouvel etudiant           *");
            gotoxy(35,6);
            printf("*       2-Modification d'un etudiant existant  *");
            gotoxy(35,7);
            printf("*       3-Suppression d'un etudiant  existant  *");
            gotoxy(35,8);
            printf("*       4-Quitter                              *");
            gotoxy(35,9);
            printf("*                                              *");
            gotoxy(35,10);
            printf("*                                   Choix : |_|*");
            gotoxy(35,11);
            printf("************************************************");
            setColor(15,0);
            affichage_etudiant(p);
             setColor(15,9);
            gotoxy(80,10);
            scanf("%d",&a);
          }while((a<1)||(a>4));
          setColor(15,0);
        switch(a)
        {
        case 1:
            p=ajout_nouvel_etudiant(p);
            break;
        case 2:
            modification_etudiant(p);
            break;
        case 3:
            p=suppression_etudiant(p);
            break;
        case 4:
            break;
        }
      }while (a!=4);
    return p;
}
void interface_emprunt_livre(int date[],int heure[])
{
    extract_date(date);
    extract_time(heure);
    system("cls");
    setColor(0,15);
    gotoxy(35,0);
    printf("************************************************");
    gotoxy(35,1);
    printf("*               Emprunt de Livre               *");
    gotoxy(35,2);
    printf("*                                              *");
    gotoxy(35,3);
    printf("*                                              *");
    if (heure[0]<10)
    {
        gotoxy(35,4);
        printf("* Date Emprunt  : |0%d",heure[0]);
    }
    else
    {
        gotoxy(35,4);
        printf("* Date Emprunt  : |%d",heure[0]);
    }
    if (heure[1]<10)
    {
        gotoxy(56,4);
        printf(":0%d",heure[1]);
    }
    else
    {
        gotoxy(56,4);
        printf(":%d",heure[1]);
    }
    if (date[0]<10)
    {
        gotoxy(59,4);
        printf("| |0%d",date[0]);
    }
    else
    {
        gotoxy(59,4);
        printf("| |%d",date[0]);
    }
    if (date[1]<10)
    {
        gotoxy(64,4);
        printf("/0%d",date[1]);
    }
    else
    {
        gotoxy(64,4);
        printf("/%d",date[1]);
    }
    gotoxy(67,4);
    printf("/%d",date[2]);
    gotoxy(72,4);
    printf("|         *");
    gotoxy(35,5);
    printf("*     CIN       : |__________|                 *");
    gotoxy(35,6);
    printf("* Code Livre    : |__________|                 *");
    gotoxy(35,7);
    printf("*                                              *");
    gotoxy(35,8);
    printf("*                                              *");
    gotoxy(35,9);
    printf("*Voulez-vous emprunter un autre livre O/N : |_|*");
    gotoxy(35,10);
    printf("************************************************");
    setColor(15,0);
}
int saisie_cin_emprunt(int p)
{
    char test[50];
    int heure[2],date[3];
    int cin;
    do{
        do{
            interface_emprunt_livre(date,heure);
            gotoxy(54,5);
            scanf("%s",test);
          }while((test_integer(test)==1)||(strlen(test)>8));
          cin=atoi(test);
      }while(verif_etudiant(p,cin)==-1);
    return cin;
}
int saisie_code_livre_emprunt(int n,int cin,int date[],int heure[])
{
    char test[50];
    int code_livre;
    do{
        do{
            interface_emprunt_livre(date,heure);
            gotoxy(54,5);
            printf("%d",cin);
            gotoxy(54,6);
            scanf("%s",test);
          }while((test_integer(test)==1)||(strlen(test)>8));
          code_livre=atoi(test);
      }while(verif_livre(n,code_livre)==-1);
    return code_livre;
}
int emprunt_livre(int q,int n,int p)
{
    FILE *Fempruntretour,*Flivre;
    char b='N';
    int cin,code_livre,i,date[3],heure[2];
    do{
        cin=saisie_cin_emprunt(p);
        code_livre=saisie_code_livre_emprunt(n,cin,date,heure);
        i=verif_livre(n,code_livre);
        if (tlivre[i].disponible=='O')
        {
            temprunt[q].dhe[0]=heure[0];
            temprunt[q].dhe[1]=heure[1];
            temprunt[q].dhe[2]=date[0];
            temprunt[q].dhe[3]=date[1];
            temprunt[q].dhe[4]=date[2];
            temprunt[q].cin_emprunt=cin;
            temprunt[q].code_livre_emprunt=code_livre;
            tlivre[i].disponible='N';
            do{
                interface_emprunt_livre(date,heure);
                gotoxy(54,5);
                printf("%d",cin);
                gotoxy(54,6);
                printf("%d",code_livre);
                gotoxy(80,9);
                fflush(stdin);
                scanf("%c",&b);
              }while((toupper(b)!='O')&&(toupper(b)!='N'));
            Fempruntretour=fopen("c:/PROJECT/Fempruntretour.txt","a");
            fprintf(Fempruntretour,"%d %d %d %d %d %d %d %d %d %d %d %d\n",temprunt[q].dhe[0],temprunt[q].dhe[1],temprunt[q].dhe[2],temprunt[q].dhe[3],temprunt[q].dhe[4],temprunt[q].cin_emprunt,temprunt[q].code_livre_emprunt,0,0,0,0,0);
            fclose(Fempruntretour);
            q+=1;
        }
        else
        {
            do{
                interface_emprunt_livre(date,heure);
                gotoxy(54,5);
                printf("%d",cin);
                gotoxy(54,6);
                printf("%d",code_livre);
                gotoxy(40,8);
                printf("\"ce livre n'est pas disponible\"");
                gotoxy(80,9);
                fflush(stdin);
                scanf("%c",&b);
              }while((toupper(b)!='O')&&(toupper(b)!='N'));
        }
        Flivre=fopen("c:/PROJECT/Flivre.txt","w");
        for(i=0;i<n;i++)
        fprintf(Flivre,"%d %s %d %c\n",tlivre[i].code_livre,tlivre[i].titre_livre,tlivre[i].nbre_pages,tlivre[i].disponible);
        fclose(Flivre);
      }while(toupper(b)=='O');
      printf("%d",q);
      getch();
    return q;
}
void interface_retour_livre(int code_livre,int cin,int date_r[],int heure_r[],int i)
{
    extract_date(date_r);
    extract_time(heure_r);
    system("cls");
    setColor(0,15);
    gotoxy(35,0);
    printf("************************************************");
    gotoxy(35,1);
    printf("*               retour du Livre %d              ",code_livre);
    gotoxy(82,1);
    printf("*");
    gotoxy(35,2);
    printf("*                                              *");
    gotoxy(35,3);
    printf("*                                              *");
   if (temprunt[i].dhe[0]<10)
    {
        gotoxy(35,4);
        printf("* Date Emprunt  : |0%d",temprunt[i].dhe[0]);
    }
    else
    {
        gotoxy(35,4);
        printf("* Date Emprunt  : |%d",temprunt[i].dhe[0]);
    }
    if (temprunt[i].dhe[1]<10)
    {
        gotoxy(56,4);
        printf(":0%d",temprunt[i].dhe[1]);
    }
    else
    {
        gotoxy(56,4);
        printf(":%d",temprunt[i].dhe[1]);
    }
    if (temprunt[i].dhe[2]<10)
    {
        gotoxy(59,4);
        printf("| |0%d",temprunt[i].dhe[2]);
    }
    else
    {
        gotoxy(59,4);
        printf("| |%d",temprunt[i].dhe[2]);
    }
    if (temprunt[i].dhe[3]<10)
    {
        gotoxy(64,4);
        printf("/0%d",temprunt[i].dhe[3]);
    }
    else
    {
        gotoxy(64,4);
        printf("/%d",temprunt[i].dhe[3]);
    }
    gotoxy(67,4);
    printf("/%d",temprunt[i].dhe[4]);
    gotoxy(72,4);
    printf("|         *");
    gotoxy(35,5);
    printf("*     CIN       : |________|                   *");
    gotoxy(54,5);
    printf("%d",cin);
    if (heure_r[0]<10)
    {
        gotoxy(35,6);
        printf("* Date Emprunt  : |0%d",heure_r[0]);
    }
    else
    {
        gotoxy(35,6);
        printf("* Date Emprunt  : |%d",heure_r[0]);
    }
    if (heure_r[1]<10)
    {
        gotoxy(56,6);
        printf(":0%d",heure_r[1]);
    }
    else
    {
        gotoxy(56,6);
        printf(":%d",heure_r[1]);
    }
    if (date_r[0]<10)
    {
        gotoxy(59,6);
        printf("| |0%d",date_r[0]);
    }
    else
    {
        gotoxy(59,6);
        printf("| |%d",date_r[0]);
    }
    if (date_r[1]<10)
    {
        gotoxy(64,6);
        printf("/0%d",date_r[1]);
    }
    else
    {
        gotoxy(64,6);
        printf("/%d",date_r[1]);
    }
    gotoxy(67,6);
    printf("/%d",date_r[2]);
    gotoxy(72,6);
    printf("|         *");
    gotoxy(35,7);
    printf("*                                              *");
    gotoxy(35,8);
    printf("*                                              *");
    gotoxy(35,9);
    printf("*Voulez-vous confirmer le retour livre O/N :|_|*");
    gotoxy(35,10);
    printf("************************************************");
    setColor(15,0);
}
void interface_code_retour_livre()
{
    system("cls");
    setColor(0,15);
    gotoxy(35,0);
    printf("************************************************");
    gotoxy(35,1);
    printf("*    Saisissez le code du livre a rtourner     *");
    gotoxy(35,2);
    printf("*                                              *");
    gotoxy(35,3);
    printf("*                                              *");
    gotoxy(35,4);
    printf("* Code Livre    : |__________|                 *");
    gotoxy(35,5);
    printf("*                                              *");
    gotoxy(35,6);
    printf("*                                              *");
    gotoxy(35,7);
    printf("*        Appuez sur Entree pour valider        *");
    gotoxy(35,8);
    printf("************************************************");
     setColor(15,0);
}
int saisie_code_livre_r()
{
    char test[50];
    do{
        interface_code_retour_livre();
        gotoxy(54,4);
        scanf("%s",test);
      }while((test_integer(test)==1)||(strlen(test)>10));
    return atoi(test);
}
void retour_livre(int n,int q)
{
    FILE *Flivre,*Fempruntretour;
    int code_livre,i,j,k,date_r[3],heure_r[2];
    char b,c;
    do{
        c='N';
        code_livre=saisie_code_livre_r();
        i=verif_livre(n,code_livre);
        j=verif_emprunt(q,code_livre);
        if ((i!=-1)&&(tlivre[i].disponible=='N'))
        {
            do{
                interface_retour_livre(code_livre,temprunt[j].cin_emprunt,date_r,heure_r,i);
                gotoxy(80,9);
                fflush(stdin);
                scanf("%c",&b);
              }while((toupper(b)!='O')&&(toupper(b)!='N'));
            if (toupper(b)=='O')
            {
                tlivre[i].disponible='O';
                temprunt[j].dhr[0]=heure_r[0];
                temprunt[j].dhr[1]=heure_r[1];
                temprunt[j].dhr[2]=date_r[0];
                temprunt[j].dhr[3]=date_r[1];
                temprunt[j].dhr[4]=date_r[2];
                Fempruntretour=fopen("c:/PROJECT/Fempruntretour.txt","w");
                for(k=0;k<q;k++)
                fprintf(Fempruntretour,"%d %d %d %d %d %d %d %d %d %d %d %d\n",temprunt[k].dhe[0],temprunt[k].dhe[1],temprunt[k].dhe[2],temprunt[k].dhe[3],temprunt[k].dhe[4],temprunt[k].cin_emprunt,temprunt[k].code_livre_emprunt,temprunt[k].dhr[0],temprunt[k].dhr[1],temprunt[k].dhr[2],temprunt[k].dhr[3],temprunt[k].dhr[4]);
                fclose(Fempruntretour);
                Flivre=fopen("c:/PROJECT/Flivre.txt","w");
                for(k=0;k<n;k++)
                fprintf(Flivre,"%d %s %d %c\n",tlivre[k].code_livre,tlivre[k].titre_livre,tlivre[k].nbre_pages,tlivre[k].disponible);
                fclose(Flivre);
            }
        }
        else
        {
            do{
                interface_code_retour_livre();
                gotoxy(54,4);
                printf("%d",code_livre);
                gotoxy(47,5);
                printf("\"code Livre invalide\"");
                gotoxy(38,6);
                printf("voulez-vous retourner un livre O/N : |_|");
                gotoxy(76,6);
                fflush(stdin);
                scanf("%c",&c);
              }while((toupper(c)!='O')&&(toupper(c)!='N'));
        }
      }while (toupper(c)=='O');
}
void livre_non_rtournes(int q)
{
    int i,j=0;
    system("cls");
    setColor(4,0);
    gotoxy(35,0);
    printf("**********Livre Non Retournes************");
    gotoxy(35,1);
    printf("_________________________________________");
    gotoxy(35,2);
    printf("|  Date Emprunt  |   CIN   | Code Livre |");
    gotoxy(35,3);
    printf("_________________________________________");
    for(i=0;i<q;i++)
    {
        if((temprunt[i].dhr[4]==0)&&(temprunt[i].dhr[3]==0)&&(temprunt[i].dhr[2]==0))
            {
                gotoxy(35,4+j);
                printf("| %d:%d %d/%d/%d",temprunt[i].dhe[0],temprunt[i].dhe[1],temprunt[i].dhe[2],temprunt[i].dhe[3],temprunt[i].dhe[4]);
                gotoxy(52,4+j);
                printf("| %d",temprunt[i].cin_emprunt);
                gotoxy(62,4+j);
                printf("| %d",temprunt[i].code_livre_emprunt);
                gotoxy(75,4+j);
                printf("|");
                j+=1;
            }
    }
    gotoxy(35,4+j);
    printf("_________________________________________");
    getch();
}
int menu_gestion_E_R(int q,int n,int p)
{
    int a;
    do{
        do{
            system("cls");
            setColor(9,15);
            gotoxy(35,0);
            printf("************************************************");
            gotoxy(35,1);
            printf("*                                              *");
            setColor(15,9);
            gotoxy(35,2);
            printf("*         Emprunt/Retour des livre             *");
             setColor(9,15);
            gotoxy(35,3);
            printf("*                                              *");
            gotoxy(35,4);
            printf("*                                              *");
            gotoxy(35,5);
            printf("*        1-Emprunt des Livres                  *");
            gotoxy(35,6);
            printf("*        2-Retour des Livres                   *");
            gotoxy(35,7);
            printf("*        3-Livres non retournes                *");
            gotoxy(35,8);
            printf("*        4-Quitter                             *");
            gotoxy(35,9);
            printf("*                                              *");
            gotoxy(35,10);
            printf("*                                   Choix : |_|*");
            gotoxy(35,11);
            printf("************************************************");
            setColor(15,0);
            affichage_emprunt_retour(q);
            setColor(9,15);
            gotoxy(80,10);
            scanf("%d",&a);
          }while((a<1)||(a>4));
          setColor(15,0);
        switch(a)
        {
        case 1:
            q=emprunt_livre(q,n,p);
            break;
        case 2:
            retour_livre(n,q);
            break;
        case 3:
            livre_non_rtournes(q);
            break;
        }
      }while (a!=4);
    return n;
}
void trace_histogramme(int n,int T[],int TA[])
{
    int max,min,i,j,l=0;
    max=recherche_max(T,n);
    min=recherche_min(T,n);
    system("cls");
    gotoxy(50,max+16);
    printf("%c",192);
    for(i=0;i<n*6+2;i++)
    {
        gotoxy(51+i,max+16);
        printf("%c",196);
    }
    gotoxy(52+n*6,max+16);
    printf("%c",'>');
    for(i=15;i<max+16;i++)
    {
        gotoxy(50,i);
        printf("%c",179);
    }
    gotoxy(50,max-min+15);
    printf("%c",197);
    gotoxy(47,max-min+15);
    printf("%s","min");
    gotoxy(50,15);
    printf("%c",197);
    gotoxy(47,15);
    printf("%s","max");
    gotoxy(50,14);
    printf("%c",'^');
    for(i=0;i<n*6;i+=6)
       {
            gotoxy(55+i,max+16);
            printf("%c",197);
            gotoxy(55+i,max+17);
            printf("%d",TA[l]);
            for(j=0;j<T[l];j++)
               {
                  gotoxy(54+i,max-j+15);
                  printf("%c%c%c",219,219,219);
               }
            l+=1;
       }
    getch();
}
void histogramme_livre_plus_emprunt(int n,int q)
{
    int i,j,T[100],TA[100];
    for(i=0;i<n;i++)
        TA[i]=tlivre[i].code_livre;
    for(i=0;i<n;i++)
        T[i]=0;
    for(i=0;i<n;i++)
    for(j=0;j<q;j++)
    if(temprunt[j].code_livre_emprunt==TA[i])
    T[i]+=1;
    trace_histogramme(n,T,TA);
}
void histogramme_etudiant_motive(int p,int q)
{
    int i,j,T[100],TA[100];
    for(i=0;i<p;i++)
        TA[i]=tetudiant[i].cin;
    for(i=0;i<p;i++)
        T[i]=0;
    for(i=0;i<p;i++)
    for(j=0;j<q;j++)
    if(temprunt[j].cin_emprunt==TA[i])
    T[i]+=1;
    trace_histogramme(p,T,TA);
}

void menu_statistiques(int n,int p,int q)
{
    int a;
    do{
        do{
            system("cls");
            setColor(9,15);
            gotoxy(35,0);
            printf("************************************************");
            gotoxy(35,1);
            printf("*                                              *");
            setColor(15,9);
            gotoxy(35,2);
            printf("*               Statistiques                   *");
            setColor(9,15);
            gotoxy(35,3);
            printf("*                                              *");
            gotoxy(35,4);
            printf("*                                              *");
            gotoxy(35,5);
            printf("*1-Histogramme des livre les plus empruntes    *");
            gotoxy(35,6);
            printf("*2-Histogramme des etudiants motives           *");
            gotoxy(35,7);
            printf("*3-Quitter                                     *");
            gotoxy(35,8);
            printf("*                                              *");
            gotoxy(35,9);
            printf("*                                   Choix : |_|*");
            gotoxy(35,10);
            printf("************************************************");
            gotoxy(80,9);
            scanf("%d",&a);
          }while((a<1)||(a>4));
          setColor(15,0);
        switch(a)
        {
        case 1:
            histogramme_livre_plus_emprunt(n,q);
            break;
        case 2:
            histogramme_etudiant_motive(p,q);
            break;
        }
      }while (a!=3);
}

// Fonction pour l'interface initiale (choix du r le)
int chooseRole() {
    int userRole;

    system("cls");
    setColor(15,9);
    gotoxy(35, 0);
    printf("************************************************");
    gotoxy(35, 1);
    printf("*                                              *");
     setColor(9,15);
    gotoxy(35, 2);
    printf("*               BIBLIOTHEQUE ENSAH             *");
     setColor(15,9);
    gotoxy(35, 3);
    printf("*                                              *");
    gotoxy(35, 4);
    printf("*                                              *");
    gotoxy(35, 5);
    printf("*                                              *");
    gotoxy(35, 6);
    printf("*        1- Administrateur                     *");
    gotoxy(35, 7);
    printf("*        2- Etudiant                           *");
    gotoxy(35, 8);
    printf("*        3- Quitter                            *");
    gotoxy(35, 9);
    printf("*                                   Choix : |_| ");
    gotoxy(35, 10);
    printf("************************************************");
    gotoxy(80, 9);
    printf("");
    scanf("%d", &userRole);
    setColor(15,0);
    return userRole;
}


// Modification de la fonction menu_principal
void menu_principal(int n, int p, int q) {
    int choice =0;
    int loggedIn = 0; // Variable pour suivre l' tat de connexion
    int isAdmin = 0;  // Variable pour suivre si l'utilisateur est admin

    // Afficher l'interface initiale (choix du r le)
    int userRole = chooseRole();

    switch (userRole) {
        case 1:
            isAdmin = authenticateAdmin();
            if(isAdmin){
                do{
                    system("cls");
                    setColor(9,15);
            gotoxy(35, 0);
            printf("************************************************");
            gotoxy(35, 1);
            printf("*                                              *");
            gotoxy(35, 2);
            printf("*     Application Gestion de bibliotheque      *");
            gotoxy(35, 3);
            printf("*                    ENSAH                     *");
            gotoxy(35, 4);
            printf("*                                              *");
            gotoxy(35, 5);
            printf("*                                              *");
            gotoxy(35, 6);
            printf("*        1- Gestion des livres                 *");
            gotoxy(35, 7);
            printf("*        2- Gestion des Etudiants              *");
            gotoxy(35, 8);
            printf("*        3- gestion des Emprunts/Retours       *");
            gotoxy(35, 9);
            printf("*        4- Statistiques                       *");
            gotoxy(35, 10);
            printf("*        5- Quitter                            *");
            gotoxy(35, 11);
            printf("*                                              *");
            gotoxy(35, 12);
            printf("*                                   Choix : |_|*");
            gotoxy(35, 13);
            printf("************************************************");
            gotoxy(80, 12);
            printf("");
            scanf("%d", &choice);
              setColor(15,0);
            switch (choice) {
                case 1:
                    n = menu_gestion_livre(n);
                    break;
                case 2:
                    p = menu_gestion_etudiants(p);
                    break;
                case 3:
                    q = menu_gestion_E_R(q, n, p);
                    break;
                case 4:
                    menu_statistiques(n, p, q);
                    break;
                }
            }while (choice != 5);
        }
            break;
        case 2:
            do {
        // Si l'utilisateur n'est pas connect , afficher l'interface de login/signup
        if (!loggedIn) {
            choice = menu_login_signup();  // Affiche l'interface de login/signup

            switch (choice) {
                case 1:
                    signup();  // Appelle la fonction de cr ation de compte
                    break;
                case 2:
                    loggedIn = login();  // Appelle la fonction de login
                    break;
                case 3:
                    exit(0);  // Quitte l'application
                    break;
            }
        } else {
            system("cls");
            setColor(9,15);
            gotoxy(35, 0);
            printf("************************************************");
            gotoxy(35, 1);
            printf("*                                              *");
            setColor(15,9);
            gotoxy(35, 2);
            printf("*     Application Gestion de bibliotheque      *");
            gotoxy(35, 3);
            printf("*                     ENSAH                    *");
            setColor(9,15);
            gotoxy(35, 4);
            printf("*                                              *");
            gotoxy(35, 5);
            printf("*        1- ajoutez vous pour emprunt          *");
            gotoxy(35, 6);
            printf("*        2- gestion des Emprunts/Retours       *");
            gotoxy(35, 7);
            printf("*        3- Statistiques                       *");
            gotoxy(35, 8);
            printf("*        4- Quitter                            *");
            gotoxy(35, 9);
            printf("*                                              *");
            gotoxy(35, 10);
            printf("*                                   Choix : |_|*");
            gotoxy(35, 11);
            printf("************************************************");
            setColor(15,0);
            affichage_livre(n);
            setColor(9,15);
            gotoxy(80, 10);
            printf(" ");
            scanf("%d", &choice);
            setColor(15,0);
            switch (choice) {

               case 1:
                    p = ajout_nouvel_etudiant(p);
                    break;
                case 2:
                    q = menu_gestion_E_R(q, n, p);
                    break;
                case 3:
                    menu_statistiques(n, p, q);
                    break;
            }
        }
    } while (choice != 4);
            break;
        case 3:
            exit(0);  // Quitte l'application
            break;
        default:
            printf("Choix non valide.\n");
            exit(1);
            break;
    }
}

int main() {
    int n = 0, p = 0, q = 0;
    n = extract_info_Flivre();
    p = extract_info_Fetudiant();
    q = extract_info_Fempruntretour();
    menu_principal(n, p, q);
    return 0;
}

