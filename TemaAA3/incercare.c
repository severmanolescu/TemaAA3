#include<stdio.h> 
#include<stdlib.h> 

struct Arbore
{
    int cheie; // Variabila pentru cheia nodului
    int inaltime; // Variabila pentru inaltimea la care se afla nodul

    struct Arbore* FiuStang; // Pointer catre fiul stang al nodului
    struct Arbore* FiuDrept; // Pointer catre fiul drept al nodului

    //daad
};

// Lista simplu inlantuita pentru stergerea in preordine a nodurilor din lista
struct Lista
{
    int cheie;

    struct Lista* urm;
};

struct Lista* list;

FILE* fout; // Fisierul de output

int k1; // Variabile folosite pentru a determina nuamrul de adaugari in lista efectuate
int k;

int Maxim(int a, int b) // Functie de returnare a maximului pentru determianrea inaltimii unui nod in functie de fii sai
{
    return (a > b) ? a : b;
}

int inaltime(struct Arbore* arb) // Functie care returneaza inaltimea unui nod
{
    if (arb == NULL) // Daca nodul nu exista se returneaza 0
    {
        return 0;
    }

    return arb->inaltime;
}

struct Arbore* Initializare(int cheie)
{
    struct Arbore* nod; // Pointer folosti pentru adaugarea noul nod in arbore

    if ((nod = (struct Arbore*)malloc(sizeof(struct Arbore))) == NULL) // Alocarea memoriei pentru noul nod adaugat
    {
        perror("malloc"); // Afisare mesaj de eroare in cazul in care nu s-a putut efectua alocarea memoriei
        exit(-1); // Iesire din program
    }

    nod->cheie = cheie; // Initializam variabilele noului nod
    nod->FiuStang = NULL;
    nod->FiuDrept = NULL;
    nod->inaltime = 1;

    return nod;
}
 
struct Arbore* RotireStanga(struct Arbore* nod)
{
    // Exemplu:
    // Inainte de rotire:           Dupa rotire:
    //         nod                      aux
    //            \                    /   \
    //            aux                nod    x
    //           /   \                 \
    //         aux1   x                 aux1

    struct Arbore* aux = nod->FiuDrept;
    struct Arbore* aux1 = aux->FiuStang;

    aux->FiuStang = nod; // Schimbarea pozitiilor nodurilor
    nod->FiuDrept = aux1;

    nod->inaltime = Maxim(inaltime(nod->FiuStang), inaltime(nod->FiuDrept)) + 1; // Reinitailizarea inaltimilor nodurilor rotite
    aux->inaltime = Maxim(inaltime(aux->FiuStang), inaltime(aux->FiuDrept)) + 1;

    return aux;
}

struct Arbore* RotireDreapta(struct Arbore* nod)
{
    // Exemplu:
    // Inainte de rotire:           Dupa rotire:
    //         nod                      aux
    //        /                        /   \
    //       aux                      x     nod
    //      /   \                          /
    //    aux1   x                      aux1


    struct Arbore* aux = nod->FiuStang;
    struct Arbore* aux1 = aux->FiuDrept;

    aux->FiuDrept = nod; // Schimbarea pozitiilor nodurilor
    nod->FiuStang = aux1;

    nod->inaltime = Maxim(inaltime(nod->FiuStang), inaltime(nod->FiuDrept)) + 1; // Reinitailizarea inaltimilor nodurilor rotite
    aux->inaltime = Maxim(inaltime(aux->FiuStang), inaltime(aux->FiuDrept)) + 1;

    return aux;
}

int Balansare(struct Arbore* arb)
{
    if (arb == NULL) // Daca nodul nu exista
        return 0;   // vom returna 0

    return inaltime(arb->FiuStang) - inaltime(arb->FiuDrept); // In caz contrat returnam diferenta dintre inaltimea
}                                                            // fiului stang si inaltimea fiului drept

struct Arbore* Inserare(struct Arbore* nod, int cheie)
{
    if (nod == NULL) // Daca arborele nu exista, se insereaza nodul fara echilibrare
        return Initializare(cheie);

    if (cheie < nod->cheie)                              // Ne ducem pe ramara stanga daca cheia este
        nod->FiuStang = Inserare(nod->FiuStang, cheie); // mai mica decat nodul curent
                                                       
    else if (cheie > nod->cheie)                         // Ne ducem pe ramara dreapta daca cheia este
        nod->FiuDrept = Inserare(nod->FiuDrept, cheie); // mai mare decat nodul curent

    else  // Daca cheia exista deja in arbore, returnam arborele fara inserare
        return nod;

    nod->inaltime = 1 + Maxim(inaltime(nod->FiuStang), inaltime(nod->FiuDrept)); // Reinializam inaltimea radacinii

    int balanta = Balansare(nod); // Verificam balanta arborelui dupa adaugarea nodului

    if (balanta > 1 && cheie < nod->FiuStang->cheie)  // Daca inaltimea fiului stang este mai mare decat inaltimea
    {                                                // fiului drept + 1 si daca cheia adaugata este mai mica decat
        return RotireDreapta(nod);                  // chiea fiului stang al radacinii facem echilibrare spre dreapta
    }

    if (balanta < -1 && cheie > nod->FiuDrept->cheie)  // Daca inaltimea fiului stang este mai mica decat inaltimea
    {                                                 // fiului drept + 1 si daca cheia adaugata este mai mare decat
        return RotireStanga(nod);                    // chiea fiului drept al radacinii facem echilibrare spre dreapta
    }

    if (balanta > 1 && cheie > nod->FiuStang->cheie)  // Daca inaltimea fiului stang este mai mare decat inaltimea
    {                                                // fiului drept + 1 si daca cheia adaugata este mai mare decat
        nod->FiuStang = RotireStanga(nod->FiuStang);// chiea fiului stang al radacinii facem echilibrare fiului stang la stanga
        return RotireDreapta(nod);                 // si rotire la dreapta la tot arborele
    }

    if (balanta < -1 && cheie < nod->FiuDrept->cheie)  // Daca inaltimea fiului stang este mai mica decat inaltimea
    {                                                 // fiului drept + 1 si daca cheia adaugata este mai mica decat
        nod->FiuDrept = RotireDreapta(nod->FiuDrept);// chiea fiului drept al radacinii facem echilibrare fiului drept la dreapta
        return RotireStanga(nod);                   // si rotire la stanga la tot arborele
    }

    return nod; // Returnam arborele
}

struct Arbore* ValoareMaxima(struct Arbore* nod) // Functie care returneaza nodul cu care se va face schimbarea la suprimare
{
    struct Arbore* aux = nod;

    while (aux->FiuDrept != NULL)
        aux = aux->FiuDrept;

    return aux;
}

struct Arbore* Tata(struct Arbore* arb, struct Arbore* nod) // Functie care retuneaza tatal unui nod 
{
    if (arb != NULL && nod != NULL) // Daca arborele si nodul exista
    {
        if (arb->cheie < nod->cheie) // Daca cheia noduluic autat este mai mare decat nodul curent
        {                           // ne indreptam catre fiul drept 
            if (arb->FiuDrept == nod) // Verificam daca am ajuns la tatal nodului
            {
                return arb; // Returnam tatal nodului
            }

            return Tata(arb->FiuDrept, nod); // Daca inca nu suntem la tatal nodului apelam functai recursiva pentru a continua
        }

        if (arb->cheie > nod->cheie) // Daca cheia noduluic autat este mai mic decat nodul curent
        {                           // ne indreptam catre fiul stang
            if (arb->FiuStang == nod) // Verificam daca am ajuns la tatal nodului
            {
                return arb; // Returnam tatal nodului
            }

            return Tata(arb->FiuStang, nod); // Daca inca nu suntem la tatal nodului apelam functai recursiva pentru a continu
        }
    }

    return NULL; // Returnam NULL daca nodul nu are un Tata, adica acesta este chiar radacina
}

struct Arbore* PrimulFiu(struct Arbore* arb, struct Arbore* nod)
{
    if (arb != NULL && nod != NULL) // Verificam daca arborele si nodul exista
    {
        if (arb->cheie < nod->cheie) // Daca cheia nodului parite este mai mare decat cheia nodului curent
        {                           // ne inredptam catre fiul drept al nodului
            return PrimulFiu(arb->FiuDrept, nod); // Apelam functia recursiva
        }

        if (arb->cheie > nod->cheie) // Daca cheia nodului parite este mai mare decat cheia nodului curent
        {                           // ne inredptam catre fiul drept al nodului
            return PrimulFiu(arb->FiuStang, nod);; // Apelam functia recursiva
        }

        if (arb->cheie == nod->cheie) // Daca am gasit nodul cautat
        {
            if (arb->FiuStang != NULL) // Daca fiul stang exista
            {
                return arb->FiuStang; // Retuneaza fiul stang
            }

            if (arb->FiuDrept != NULL) // Daca fiul stang nu exista, dar exista fiul drept
            {
                return arb->FiuDrept; // Returnam fiul drept
            }
        }
    }

    return NULL; // Returnam NULL daca nodul este o frunza
}

struct Arbore* FrateDreapta(struct Arbore* arb, struct Arbore* nod) // Funtie pentru returnarea nodului frate de dreapta
{
    if (arb != NULL && nod != NULL) // Verificam daca arborele si nodul exista
    {
        if (arb->cheie < nod->cheie) // Daca cheia nodului cautat este mai mare decat cheia actuala
        {
            return FrateDreapta(arb->FiuDrept, nod); // Ne indreptam catre ramura dreapta 
        }

        if (arb->cheie > nod->cheie) // Daca cheia cautata este mai mica decat cheia actuala
        {
            if (arb->FiuStang == nod) // Verificam daca fiu stang nu este cumva nodul cautat
            {
                return arb->FiuDrept; // In caz afirmativ returnam fiul drept
            }

            return FrateDreapta(arb->FiuStang, nod); // In ca contrar reapelam functia recursiva catre ramura stanga
        }
    }

    return NULL; // Returnam NULL daca nodul nu are un frate de drapta
}

int Cheie(struct Arbore* arb, struct Arbore* nod) // Functia care returneaza cheia unui nod
{
    if (arb != NULL && nod != NULL) // Verificam daca arborele si nodul exista
    {
        return nod->cheie; // In caz afirmativ returnam cheia acestuia
    }

    return 0; // In caz negativ returnam valoarea 0
}

struct Arbore* Radacina(struct Arbore* arb) // Functia care returneaza radacina
{
    if (arb != NULL) // Daca arborele exista
    {
        return arb; // Returnam radacina
    }

    return NULL; // In caz contrat returnam NULL
}

void Preordine(struct Arbore* arb) // Afisarea in preordine
{
    if (arb != NULL) // Daca nodul exista
    {
        fprintf(fout, "%d ", arb->cheie); // Afisam in fisier cheia nodului curent

        Preordine(arb->FiuStang); // Apelam functia recursiva catre ramura stanga

        Preordine(arb->FiuDrept); // Apelam functia recursiva catre ramura dreapta
    }
}

void Inordine(struct Arbore* arb) // Afisarea in inordine
{
    if (arb != NULL) // Daca nodul exista
    {
        Inordine(arb->FiuStang); // Apelam functia recursiva catre ramura stanga

        fprintf(fout, "%d ", arb->cheie);  // Afisam in fisier cheia nodului curent

        Inordine(arb->FiuDrept); // Apelam functia recursiva catre ramura dreapta
    }
}

void Postordine(struct Arbore* arb) // Afisarea in postordine
{
    if (arb != NULL) // Daca nodul exista
    {
        Postordine(arb->FiuStang); // Apelam functia recursiva catre ramura stanga

        Postordine(arb->FiuDrept); // Apelam functia recursiva catre ramura dreapta

        fprintf(fout, "%d ", arb->cheie);  // Afisam in fisier cheia nodului curent
    }
}

void Cuprindere(struct Arbore* arb, int linie) // Afisarea prin cuprindere la un nivel dat
{
    int i = 0; // Variabila folosita pentru parcurgerea la stanga
    int j = 0; // Variabila folosita pentru parcurgarea la stanga al fiului drept de la fiecare nod corespunzator variabilei i
    int k = 0; // Variabila folosita pentru parcurgerea la dreapta de la fiecare nod corespunzator variabilei j

    struct Arbore* aux = arb; // Initializam variabile ajutatoare
    struct Arbore* aux1 = arb;
    struct Arbore* aux2 = arb;

    if (linie == 1) // Daca linia care doreste sa fie afisata este prima, afisam doar radacina
    {
        printf("%d ", aux->cheie);
    }

    else // Altfel
    {
        linie -= 2; // Scadem din lina care dorim sa o afisam linia radacinii si ultima linie

        while (i < linie && aux != NULL && aux->FiuStang != NULL) // Cat timp exista un fiu stang si linia curenta este mai mica decat
        {                                                        // linia care doreste sa fie afisata
            aux = aux->FiuStang; // Se muta cursorul la acesta
            i++; // Si incrementam randul la care ne aflam
        }

        if (aux->FiuStang != NULL) // Verificam daca nodul are fii
            printf("%d ", aux->FiuStang->cheie); // Si ii afisam in caz afirmativ

        if (aux->FiuDrept != NULL)
            printf("%d ", aux->FiuDrept->cheie);

        while ((aux = Tata(arb, aux)) != NULL) // Mutam cursorul cu o linie mai sus
        {
            j = i; // initializam pe j cu randul la care ne aflam
            i--;

            aux1 = aux->FiuDrept; // aux1 va deveni fiul drept pentru toate nodurile din ramura stanga

            while (j < linie && aux1 != NULL && aux1->FiuStang != NULL) // Cat timp nu am ajuns la ultima linie si inca exista nodul
            {
                aux1 = aux1->FiuStang; // Mutam cursorul catre fiul stang
                j++; // Si incrementam randul la care ne aflam
            }

            if (j == linie && aux1 != NULL) // Daca am ajuns la linia dorita
            {
                if (aux1->FiuStang != NULL) // Verificam daca nodul are fii
                    printf("%d ", aux1->FiuStang->cheie); // Si ii afisam in caz afirmativ

                if (aux1->FiuDrept != NULL)
                    printf("%d ", aux1->FiuDrept->cheie);
            }

            while ((aux1 = Tata(arb, aux1)) != NULL && aux1 != arb) // Urcam catre Tatal nodului curent
            {
                k = j; // salvam in k inaltimea la care ne aflam
                j--;

                aux2 = aux1->FiuDrept; // Vom merge catre ramura dreapta pentru fiecare nod

                while (k < linie && aux2 != NULL && aux2->FiuDrept != NULL) // Cat timp se poate face mutarea catre fiul drept
                {
                    aux2 = aux2->FiuDrept; // Mutam cursorul catre acesta
                    k++; // Incrementam randul la care ne aflam
                }

                if (k == linie && aux2 != NULL) // Daca am ajuns la linia dorita si nodul exista
                {
                    if (aux2->FiuStang != NULL) // Verificam daca nodul are fii
                        printf("%d ", aux2->FiuStang->cheie); // Si ii afisam

                    if (aux2->FiuDrept != NULL)
                        printf("%d ", aux2->FiuDrept->cheie);
                }
            }
        }
    }
}

void AfisareCuprindere(struct Arbore* arb) // Functie folosita pentru afisarea in cuprindere
{
    int index = 0;
    int in = inaltime(arb);

    for (index = 1; index <= in; index++) // Parcurgem fiecare rand din arbore
    {
        Cuprindere(arb, index); // Apelam functia de afisare pentru randul respectiv
        printf("\n");
    }
}

struct Arbore* Suprimare(struct Arbore* arb, int cheie) // Functie de stergere a unui nod din arbore
{
    if (arb == NULL)
        return arb;

    if (cheie < arb->cheie)
        arb->FiuStang = Suprimare(arb->FiuStang, cheie);

    else if (cheie > arb->cheie)
        arb->FiuDrept = Suprimare(arb->FiuDrept, cheie);

    else
    {
        if ((arb->FiuStang == NULL) || (arb->FiuDrept == NULL))
        {
            struct Arbore* aux = arb->FiuStang ? arb->FiuStang : arb->FiuDrept;

            if (aux == NULL)
            {
                aux = arb;
                arb = NULL;
            }
            else
            {
                *arb = *aux;
            }

            free(aux);
        }
        else
        {
            struct Arbore* aux = ValoareMaxima(arb->FiuStang);

            arb->cheie = aux->cheie;

            arb->FiuStang = Suprimare(arb->FiuStang, aux->cheie);
        }
    }

    if (arb == NULL)
        return arb;

    arb->inaltime = 1 + Maxim(inaltime(arb->FiuStang), inaltime(arb->FiuDrept));

    int balanta = Balansare(arb);

    if (balanta > 1 && Balansare(arb->FiuStang) >= 0)
        return RotireDreapta(arb);

    if (balanta > 1 && Balansare(arb->FiuStang) < 0)
    {
        arb->FiuStang = RotireStanga(arb->FiuStang);
        return RotireDreapta(arb);
    }

    if (balanta < -1 && Balansare(arb->FiuDrept) <= 0)
        return RotireStanga(arb);

    if (balanta < -1 && Balansare(arb->FiuDrept) > 0)
    {
        arb->FiuDrept = RotireDreapta(arb->FiuDrept);
        return RotireStanga(arb);
    }

    return arb;
}

void AdaugareLista(int cheie) // Functie pentru generare functie simplu inlantuite cu nodurile arborelui in preordine
{
    struct Lista* q;
    struct Lista* p;

    if ((q = (struct Lista*)malloc(sizeof(struct Lista))) == NULL) // Alocam memorie pentru noul nod care urmeaza sa fie adaugat in lista
    {
        perror("malloc"); // Afisiam mesaj de eroare in caz de esec la alocare
        exit(-1); // Iesire din program
    }

    if (k1 < k) // Cat timp nu am ajuns la numarul maxim de noduri care doresc sa fie adaugate
    {
        k1++; // Incrementam numarul numerelor adaugate in lista

        q->cheie = cheie; // Initializam noul nod
        q->urm = NULL;

        if (list == NULL) // Daca lista nu exista
        {
            list = q; // Returnam nodul nou
        }

        else
        {
            p = list;

            while (p->urm != NULL) // Parcurgem lista pana la final
                p = p->urm;

            p->urm = q; // Adaugam noul nod la final
        }
    }
}

void GenerareLista(struct Arbore* arb) // Functie pentru generare listei simplu inlantuite
{
    if (arb != NULL)
    {
        AdaugareLista(arb->cheie); // Apelarea functiei de adaugare

        GenerareLista(arb->FiuStang); // Apelam fucntia recusrvisa pentru fiul stang

        GenerareLista(arb->FiuDrept); // Apelam fucntia recusrvisa pentru fiul stang
    }
}

int main()
{
    struct Arbore* arb = NULL; // Variabila corespunzatoare arborelui
    struct Arbore* auxiliar;

    struct Lista* q; // Variabila pentru parcurgerea listei

    FILE* fin; // Fisierul de input

    int aux = 0; // variabila auxiliara pentru citiread in fisier

    if ((fin = fopen("INPUT.DAT", "rb")) == NULL) // Verificam daca fisierul de input poate sa fie deschis
    {
        perror("fopen"); // In caz negativ afisam un mesaj de eroare
        exit(-1); // Iesire din program
    }
        
    if ((fout = fopen("AVL.DAT", "w")) == NULL) // Verificam daca fisierul de output poate sa fie deschis
    {
         perror("fopen"); // In caz negativ afisam un mesaj de eroare
         exit(-1); // Iesire din program
    }
        
    while (!feof(fin)) // Cat timp nu am ajuns la finalul fisierului
    {
          if (fread(&aux, sizeof(int), 1, fin) == 1) // Verificam daca am reusit sa citim un numcar din fisier
          {
              arb = Inserare(arb, aux); // Apelam functia de inserare pentru cheia citita
          }
    }

    if ((scanf("%d", &k)) == 0) // Citim variabila k
    {
        perror("scanf"); // Mesaj de eroare daca nu s-a putut efectua citirea
        exit(-1); // Iesire program
    }

    GenerareLista(arb); // General lista simplu inlantuita

    for (q = list; q != NULL; q = q->urm)
    {
        arb = Suprimare(arb, q->cheie); // Stergem fiecare nod din abore in ordinea lor din lista
        printf("\n\n");
        AfisareCuprindere(arb);
    }

    Preordine(arb); // Afisam arborele in preordine
    fprintf(fout, "\n");

    Inordine(arb); // Afisam arborele in inordine
    fprintf(fout, "\n");

    Postordine(arb); // Afisam arborele in postordine

    return 0;
}