//#include<stdio.h> 
//#include<stdlib.h> 
//
//struct Arbore
//{
//    int cheie;
//    struct Arbore* FiuStang;
//    struct Arbore* FiuDrept;
//    int inaltime;
//};
//
//FILE* fout;
//
//struct Arbore* Tata(struct Arbore* arb, struct Arbore* nod)
//{
//    if (arb != NULL && nod != NULL)
//    {
//        if (arb->cheie < nod->cheie)
//        {
//            if (arb->FiuDrept == nod)
//                return arb;
//
//            return Tata(arb->FiuDrept, nod);
//        }
//
//        if (arb->cheie > nod->cheie)
//        {
//            if (arb->FiuStang == nod)
//                return arb;
//
//            return Tata(arb->FiuStang, nod);
//        }
//    }
//
//    return NULL;
//}
//
//struct Arbore* PrimulFiu(struct Arbore* arb, struct Arbore* nod)
//{
//    if (arb != NULL && nod != NULL)
//    {
//        if (arb->cheie < nod->cheie)
//        {
//            return PrimulFiu(arb->FiuDrept, nod);
//        }
//
//        if (arb->cheie > nod->cheie)
//        {
//            return PrimulFiu(arb->FiuStang, nod);
//        }
//
//        if (arb->cheie == nod->cheie)
//        {
//            if (arb->FiuStang != NULL)
//            {
//                return arb->FiuStang;
//            }
//
//            if (arb->FiuDrept != NULL)
//            {
//                return arb->FiuDrept;
//            }
//        }
//    }
//
//    return NULL;
//}
//
//struct Arbore* FrateDreapta(struct Arbore* arb, struct Arbore* nod)
//{
//    if (arb != NULL && nod != NULL)
//    {
//        if (arb->cheie < nod->cheie)
//        {
//            return FrateDreapta(arb->FiuDrept, nod);
//        }
//
//        if (arb->cheie > nod->cheie)
//        {
//            if (arb->FiuStang == nod)
//                return arb->FiuDrept;
//
//            return FrateDreapta(arb->FiuStang, nod);
//        }
//    }
//
//    return NULL;
//}
//
//int cheie(struct Arbore* arb, struct Arbore* nod)
//{
//    if (arb != NULL && nod != NULL)
//    {
//        return nod->cheie;
//    }
//
//    return 0;
//}
//
//struct Arbore* Radacina(struct Arbore* arb)
//{
//    if (arb != NULL)
//    {
//        return arb;
//    }
//
//    return NULL;
//}
//
//int Maxim(int a, int b)
//{
//    return (a > b) ? a : b;
//}
//
//int inaltime(struct Arbore* N)
//{
//    if (N == NULL)
//        return 0;
//    return N->inaltime;
//}
//
//struct Arbore* Initializare(int cheie)
//{
//    struct Arbore* arb = (struct Arbore*)malloc(sizeof(struct Arbore));
//
//    arb->cheie = cheie;
//    arb->FiuStang = NULL;
//    arb->FiuDrept = NULL;
//    arb->inaltime = 1;
//
//    return(arb);
//}
// 
//struct Arbore* RotatieDreapta(struct Arbore* y)
//{
//    struct Arbore* x = y->FiuStang;
//    struct Arbore* aux1 = x->FiuDrept;
//
//    x->FiuDrept = y;
//    y->FiuStang = aux1;
// 
//    y->inaltime = Maxim(inaltime(y->FiuStang), inaltime(y->FiuDrept)) + 1;
//    x->inaltime = Maxim(inaltime(x->FiuStang), inaltime(x->FiuDrept)) + 1;
//
//    return x;
//}
//
//struct Arbore* RotatieStanga(struct Arbore* x)
//{
//    struct Arbore* y = x->FiuDrept;
//    struct Arbore* aux1 = y->FiuStang;
// 
//    y->FiuStang = x;
//    x->FiuDrept = aux1;
//
//    x->inaltime = Maxim(inaltime(x->FiuStang), inaltime(x->FiuDrept)) + 1;
//    y->inaltime = Maxim(inaltime(y->FiuStang), inaltime(y->FiuDrept)) + 1;
//
//    return y;
//}
//
//int Balansare(struct Arbore* N)
//{
//    if (N == NULL)
//        return 0;
//    return inaltime(N->FiuStang) - inaltime(N->FiuDrept);
//}
//
//struct Arbore* Inserareie(struct Arbore* Arbore, int cheie)
//{
//    if (Arbore == NULL)
//        return(Initializare(cheie));
//
//    if (cheie < Arbore->cheie)
//        Arbore->FiuStang = Inserareie(Arbore->FiuStang, cheie);
//
//    else if (cheie > Arbore->cheie)
//        Arbore->FiuDrept = Inserareie(Arbore->FiuDrept, cheie);
//
//    else 
//        return Arbore;
//
//    Arbore->inaltime = 1 + Maxim(inaltime(Arbore->FiuStang),
//        inaltime(Arbore->FiuDrept));
//
//    int balanta = Balansare(Arbore);
//
//    if (balanta > 1 && cheie < Arbore->FiuStang->cheie)
//        return RotatieDreapta(Arbore);
//
//    if (balanta < -1 && cheie > Arbore->FiuDrept->cheie)
//        return RotatieStanga(Arbore);
//
//    if (balanta > 1 && cheie > Arbore->FiuStang->cheie)
//    {
//        Arbore->FiuStang = RotatieStanga(Arbore->FiuStang);
//        return RotatieDreapta(Arbore);
//    }
// 
//    if (balanta < -1 && cheie < Arbore->FiuDrept->cheie)
//    {
//        Arbore->FiuDrept = RotatieDreapta(Arbore->FiuDrept);
//        return RotatieStanga(Arbore);
//    }
//
//    return Arbore;
//}
//
//void Inordine(struct Arbore* arb)
//{
//    if (arb != NULL)
//    {
//        Inordine(arb->FiuStang);
//
//        fprintf(fout, "%d ", arb->cheie);
//
//        Inordine(arb->FiuDrept);
//    }
//}
//
//void Preordine(struct Arbore* arb)
//{
//    if (arb != NULL)
//    {
//        fprintf(fout, "%d ", arb->cheie);
//
//        Preordine(arb->FiuStang);
//        Preordine(arb->FiuDrept);
//    }
//}
//
//void Postordine(struct Arbore* arb)
//{
//    if (arb != NULL)
//    {
//        Postordine(arb->FiuStang);
//        Postordine(arb->FiuDrept);
//
//        fprintf(fout, "%d ", arb->cheie);
//    }
//}
//
//void cuprindere(struct Arbore* arb)
//{
//    while (arb != NULL)
//    {
//        print("%d ", arb->cheie);
//
//        arb = arb->FiuStang;
//
//    }
//}
//
//struct Arbore* Suprimare(struct Arbore* arb, struct Arbore* nod)
//{
//    struct Arbore* aux = Tata(arb, nod);
//
//    int balanta = 0;
//
//    if (nod->FiuDrept == NULL && nod->FiuStang == NULL)
//    {
//        free(nod);
//    }
//
//    else if (nod->FiuDrept == NULL)
//    {
//        if (nod->FiuStang->FiuDrept == NULL && nod->FiuStang->FiuStang == NULL)
//        {
//            nod = nod->FiuStang;
//            free(nod->FiuStang);
//        }
//    }
//
//    else if (nod->FiuStang == NULL)
//    {
//        if (nod->FiuDrept->FiuDrept == NULL && nod->FiuDrept->FiuStang == NULL)
//        {
//            nod = nod->FiuDrept;
//            free(nod->FiuDrept);
//        }
//    }
//
//    aux = Tata(arb, aux);
//
//    balanta = Balansare(aux);
//
//    if (balanta < -1)
//        return RotatieStanga(aux);
//
//    if (balanta > 1)
//    {
//        aux->FiuStang = RotatieStanga(aux->FiuStang);
//        return RotatieDreapta(aux);
//    }
//
//    if (balanta < -1)
//    {
//        aux->FiuDrept = RotatieDreapta(aux->FiuDrept);
//        return RotatieStanga(aux);
//    }
//
//    return aux;
//}
//
//int main(int argc, char* argv[])
//{
//    int k = 0;
//    int auxiliar = 0;
//
//    struct Arbore* arb = NULL;
//    struct Arbore* aux = NULL;
//
//    FILE* fin;
//
//    if ((fin = fopen("INPUT.DAT", "rb")) == NULL)
//    {
//        perror("fopen");
//        exit(-1);
//    }
//
//    if ((fout = fopen("AVL.DAT", "w")) == NULL)
//    {
//        perror("fopen");
//        exit(-1);
//    }
//
//    while (!feof(fin))
//    {
//        if (fread(&auxiliar, sizeof(unsigned long), 1, fin) == 1)
//        {
//            arb = Inserareie(arb, auxiliar);
//            printf("%d ", auxiliar);
//        }
//    }
//
//    arb = Suprimare(arb, arb->FiuStang->FiuDrept);
//
//    Inordine(arb);
//
//    return 0;
//}