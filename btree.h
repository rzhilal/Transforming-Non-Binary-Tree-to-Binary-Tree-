/*
Nama pemrogram : Rizq Hilal Rifaasya dan Zahratul Mardiyah
Program : Binary tree, pengoperasian pada tree, insert, dan konversian binary ke AVL binary tree
*/
#ifndef btree_H
#define btree_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Info(P) (P)->info
#define Left(P) (P)->left
#define Height(P) (P)->height
#define bRoot(P) (P).broot
#define Right(P) (P)->right
#define COUNT 15

/*** Struktur Data ***/
typedef int bType;
typedef struct TbTreeNode *bAddr;

typedef struct TbTreeNode{
	bAddr right; //anak kanan
	bType info; //nilai elemen
	bAddr left; //anak kiri
	int height;
}bTreeNode;

struct bTree{
	bAddr broot;
};

/* ---------------- Konstruktor ---------------- */
void bCreate(bTree *X);
//Membuat binary tree kosong

bAddr bCNode(bType X);
//Alokasi untuk membuat node baru

/* ---------------- Destruktor ---------------- */
void bDNode(bAddr *Node);

bAddr deleteNode(bAddr *root, bType X);

//Menghapus node tertentu
/* ---------------- Mutator ---------------- */
bAddr rightRotate(bAddr *y);
//Rotasi ke kanan ketika tree tidak balance
bAddr leftRotate(bAddr *y);
//Rotasi ke kiri ketika tree tidak balance

/* ---------------- Asesor ---------------- */
bAddr bSearch(bAddr bRoot, bType Value);
//Modul mereturn node yang di cari dengan nilai valuenya

void printPostorder(bAddr broot);
//Traverse tree dengan cara preorder

void printPreorder(bAddr broot);
//Traverse tree dengan cara inorder

void printInorder(bAddr broot);
//Traverse tree dengan postorder

int getBalance(bAddr p);
//Mengembalikan nilai dari keseimbangan node

void printBTree(bAddr root , int space);
//Print binary tree cara horizontal

int height_count(bAddr N);

/* ---------------- Operasi-operasi Tree ---------------- */
void bInsLeft(bAddr *parent, bType value, bAddr *node);

void bInsRight(bAddr *parent, bType value, bAddr *node);

bAddr insertNode(bAddr *Root, bType X);

void toAVL(bAddr root_non, bAddr *root_avl);

/* ---------------- Operasi Lainnya ---------------- */
int max(int a, int b);
//mencari nilai terbesar antara param a dan b

void printBT(bAddr root);
//Pembanggilan prosedur print

#endif
