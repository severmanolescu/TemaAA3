//#include <stdio.h>
//#include <stdlib.h>
//
//#define uint unsigned int
//
//
//typedef struct Arbore
//{
//	int cheie;
//	struct Arbore* FiuStang;
//	struct Arbore* FiuDrept;
//	uint inaltime;
//};
//
//int maximim(int a, int b)
//{
//	return (a > b) ? a : b;
//}
//
//int inaltime(struct Arbore* n)
//{
//	if (n != NULL)
//		return n->inaltime;
//
//	return 0;
//}
//
//struct Arbore* newArbore(int cheie)
//{
//	struct Arbore* arb = (struct Arbore*)malloc(sizeof(struct Arbore));
//
//	arb->cheie = cheie;
//	arb->FiuDrept = NULL;
//	arb->FiuStang = NULL;
//	arb->inaltime = 1;
//}
//
//struct Arbore* RotireDreapta(struct Arbore* nod)
//{
//	struct Arbore* auxiliar = nod->FiuStang;
//	struct Arbore* auxiliar1 = nod->FiuDrept;
//
//	auxiliar->FiuDrept = nod;
//	nod->FiuStang = auxiliar1;
//
//	nod->inaltime = maximim(inaltime(nod->FiuStang), inaltime(nod->FiuDrept)) + 1;
//	auxiliar->inaltime = maximim(inaltime(auxiliar->FiuStang), inaltime(auxiliar->FiuDrept)) + 1;
//
//	return auxiliar;
//}
//
//struct Arbore* RotireStanga(struct Arbore* nod)
//{
//	struct Arbore* auxiliar = nod->FiuDrept;
//	struct Arbore* auxiliar1 = nod->FiuStang;
//
//	auxiliar->FiuStang = nod;
//	nod->FiuDrept = auxiliar1;
//
//	nod->inaltime = maximim(inaltime(nod->FiuStang), inaltime(nod->FiuDrept)) + 1;
//	auxiliar->inaltime = maximim(inaltime(auxiliar->FiuStang), inaltime(auxiliar->FiuDrept)) + 1;
//
//	return auxiliar;
//}
//
//int Balansare(struct Arbore* arb)
//{
//    if (arb == NULL)
//        return 0;
//    return inaltime(arb->FiuStang) - inaltime(arb->FiuDrept);
//}
//
//struct Arbore* inserare(struct Arbore* arb, int cheie)
//{
//    if (arb == NULL)
//        return(newArbore(cheie));
//
//    if (cheie < arb->cheie)
//        arb->FiuStang = inserare(arb->FiuStang, cheie);
//
//    else if (cheie > arb->cheie)
//        arb->FiuDrept = inserare(arb->FiuDrept, cheie);
//
//    else
//        return arb;
//
//    arb->inaltime = 1 + maximim(inaltime(arb->FiuStang), (arb->FiuDrept));
//
//    int balance = Balansare(arb);
// 
//    if (balance > 1 && cheie < arb->FiuStang->cheie)
//        return RotireDreapta(arb);
//
//    if (balance < -1 && cheie > arb->FiuDrept->cheie)
//        return RotireStanga(arb);
//
//    if (balance > 1 && cheie > arb->FiuStang->cheie)
//    {
//        arb->FiuStang = RotireStanga(arb->FiuStang);
//        return RotireDreapta(arb);
//    }
//
//    if (balance < -1 && cheie < arb->FiuDrept->cheie)
//    {
//        arb->FiuDrept = RotireDreapta(arb->FiuDrept);
//        return RotireStanga(arb);
//    }
//
//    return arb;
//}
//
//void preOrder(struct Arbore* arb)
//{
//    if (arb != NULL)
//    {
//        printf("%d ", arb->cheie);
//        preOrder(arb->FiuStang);
//        preOrder(arb->FiuDrept);
//    }
//}
//
//
//void inOrder(struct Arbore* arb)
//{
//    if (arb != NULL)
//    {
//        inOrder(arb->FiuStang);
//        printf("%d ", arb->cheie);
//        inOrder(arb->FiuDrept);
//    }
//}
//
//int main()
//{
//    struct Arbore* arb = NULL;
//
//    arb = inserare(arb, 10);
//    arb = inserare(arb, 20);
//    arb = inserare(arb, 30);
//    arb = inserare(arb, 40);
//    arb = inserare(arb, 50);
//    arb = inserare(arb, 25);
//
//    printf("%d %d %d %d\n", arb->cheie, arb->FiuStang->cheie, arb->FiuStang->FiuStang->cheie, arb->FiuStang->FiuDrept->FiuDrept->cheie);
//
//    preOrder(arb);
//    printf("\n");
//    inOrder(arb);
//
//    return 0;
//}