#include "btree.h"

void bCreate(bTree *X)
{
    bRoot(*X) = NULL;
}

bAddr bCNode(bType X)
{
    bAddr newNode;
    newNode = (bAddr)malloc(sizeof(bTreeNode));
    if (newNode != NULL)
    {
        Right(newNode) = NULL;
        Info(newNode) = X;
        Left(newNode) = NULL;
        Height(newNode) = 1;
        return newNode;
    }
    else
    {
        printf("Alokasi gagal");
        return NULL;
    }
}

void bDNode(bAddr *Node)
{
    Right(*Node) = NULL;
    Left(*Node) = NULL;
    free(*Node);
}

void bInsLeft(bAddr *parent, bType value, bAddr *node)
{
    *node = bCNode(value);
    if (*parent != NULL)
    {
        if (Left(*parent) == NULL)
            Left(*parent) = *node;
        else
            printf("Cabang kiri sudah ada");
    }
    else
        printf("Parent tidak ada");
}

void bInsRight(bAddr *parent, bType value, bAddr *node)
{
    *node = bCNode(value);
    if (*parent != NULL)
    {
        if (Right(*parent) == NULL)
            Right(*parent) = *node;
        else
            printf("Cabang kanan sudah ada");
    }
    else
        printf("Parent tidak ada");
}

void printPostorder(bAddr broot)
{
    if (broot == NULL)
        return;

    printPostorder(Left(broot));
    printPostorder(Right(broot));
    printf("%d ", Info(broot));
}

void printPreorder(bAddr broot)
{
    if (broot == NULL)
        return;

    printf("%d ", Info(broot));
    printPreorder(Left(broot));
    printPreorder(Right(broot));
}

void printInorder(bAddr broot)
{
    if (broot == NULL)
        return;

    printInorder(Left(broot));
    printf("%d ", Info(broot));
    printInorder(Right(broot));
}

bAddr bSearch(bAddr bRoot, bType Value)
{
    if (bRoot == NULL)
        return bRoot;
    if (Info(bRoot) == Value)
        return bRoot;

    bAddr temp = bSearch(Left(bRoot), Value);
    if (temp == NULL)
        temp = bSearch(Right(bRoot), Value);
    return temp;
}
// AVL Tree modul

int getBalance(bAddr p)
{
    if (p == NULL)
        return 0;

    return height_count(Left(p)) - height_count(Right(p));
}

int max(int a, int b)
{
    if (a >= b)
        return a;
    else
        return b;
}

bAddr rightRotate(bAddr *y)
{
    bAddr x = Left(*y); // variabel menunjuk anak kiri dari y
    bAddr z = Right(x); // variabel menunjuk anak kanan dari x, yang nantinya akan jadi anak kiri dari y jika ada

    Right(x) = *y;
    Left(*y) = z;

    Height(*y) = max(height_count(Left(*y)), height_count(Right(*y))) + 1;
    Height(x) = max(height_count(Left(x)), height_count(Right(x))) + 1;

    return x;
}

bAddr leftRotate(bAddr *y)
{
    bAddr x = Right(*y); // variabel menunjuk anak kanan dari y
    bAddr z = Left(x);   // variabel menunjuk anak kiri dari x, nantinya akan jadi anak kanan dari y jika ada

    Left(x) = *y;
    Right(*y) = z;

    Height(*y) = max(height_count(Left(*y)), height_count(Right(*y))) + 1;
    Height(x) = max(height_count(Left(x)), height_count(Right(x))) + 1;

    return x;
}

bAddr insertNode(bAddr *Root, bType X)
{
    if (*Root == NULL)
        return *Root = (bCNode(X));

    if (X < Info(*Root))
        Left(*Root) = insertNode(&(Left(*Root)), X);
    else if (X > Info(*Root))
        Right(*Root) = insertNode(&(Right(*Root)), X);
    else
        return *Root;

    Height(*Root) = 1 + max(height_count(Left(*Root)), height_count(Right(*Root))); // update ketinggian tiap-tiap node

    int balance = getBalance(*Root);          // pengecekan keseimbangan tiap node yang di lalui ketika penginsertan
    if (balance > 1 && X < Info(Left(*Root))) // kondisi right rotate
        return rightRotate(&(*Root));

    if (balance < -1 && X > Info(Right(*Root))) // kondisi left rotate
        return leftRotate(&(*Root));

    if (balance > 1 && X > Info(Left(*Root))) // kondisi left-right rotate
    {
        Left(*Root) = leftRotate(&(Left(*Root)));
        return rightRotate(&(*Root));
    }

    if (balance < -1 && X < Info(Right(*Root))) // kondisi ketika right-left rotate
    {
        Right(*Root) = rightRotate(&(Right(*Root)));
        return leftRotate(&(*Root));
    }

    return *Root;
}

bAddr minValueNode(bAddr Root)
{
    bAddr cur = Root;

    while (Left(cur) != NULL) //pencarian nilai terkiri
        cur = Left(cur);

    return cur;
}

bAddr deleteNode(bAddr *root, bType X) 
{
    // pencarian node
    if (*root == NULL)
        return *root;

    if (X < Info(*root))
        Left(*root) = deleteNode(&Left(*root), X);

    else if (X > Info(*root))
        Right(*root) = deleteNode(&Right(*root), X);
    else
    {
        if(Left(*root) == NULL || Right(*root) == NULL) //kondisi salah satu anak atau keduanya null
        {
        	bAddr temp = Left(*root) ? Left(*root) : Right(*root); //jika left ada diisi left, jika tidak diisi kanannya

            if (temp == NULL) //kondisi ketika nodetobedeleted merupakan leaf
            {
                temp = *root;
                *root = NULL;
            }
            else //kondisi ketika memiliki anak satu, root akan digantikan oleh temp
                *root = temp;

            bDNode(&temp);
        }
        else //kondisi mempunyai 2 anak
        {
            bAddr temp = minValueNode(Right(*root)); //dicari nilai terkiri dari cabang kanan

            Info(*root) = Info(temp);

            Right(*root) = deleteNode(&Right(*root), Info(temp));
        }
    }

    if (*root == NULL) //kondisi ketika dalam tree menjadi kosong setelah deletion
        return *root;

    // Update ketinggian dan cek keseimbangan setelah deletion
    Height(*root) = max(height_count(Left(*root)), height_count(Right(*root))) + 1; // update ketinggian tiap-tiap node


    int balance = getBalance(*root);
    if (balance > 1 && getBalance(Left(*root)) >= 0)
        return rightRotate(&(*root));

    if (balance > 1 && getBalance(Left(*root)) < 0) {
        Left(*root) = leftRotate(&Left(*root));
        return rightRotate(&(*root));
    }

    if (balance < -1 && getBalance(Right(*root)) <= 0)
        return leftRotate(&(*root));

    if (balance < -1 && getBalance(Right(*root)) > 0) {
        Right(*root) = rightRotate(&Right(*root));
        return leftRotate(&(*root));
    }

    return *root;
}

void toAVL(bAddr root_non, bAddr *root_avl)
{
    if (root_non == NULL)
        return;
    *root_avl = insertNode(&(*root_avl), Info(root_non));
    toAVL(Left(root_non), &(*root_avl));
    toAVL(Right(root_non), &(*root_avl));
}

int height_count(bAddr N) {
    
	if (N == NULL)
        return 0;
        
    return Height(N);
}

void printBTree(bAddr root , int space)
{
    if(root == NULL)
        return;

    space += COUNT;

    printBTree(Right(root), space);

    printf("\n");

    for(int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", Info(root));

    printBTree(Left(root), space);
}

void printBT(bAddr root)
{
    printBTree(root, 0);
}

