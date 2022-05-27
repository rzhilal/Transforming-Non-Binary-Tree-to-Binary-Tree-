#include "nbtree.h"
#include "btree.h"

void nbCreate(nbTree *x)
{//Membuat tree kosong (X.root=NULL)
	Root(*x) = NULL;
}

nbAddr nbCNode(nbType X)
{//Alokasi untuk membuat node baru
	nbAddr newNode;
	newNode = (nbAddr) malloc(sizeof(nbTreeNode));
	if (newNode != NULL) // Ketika alokasi berhasil
	{
		FS(newNode)=NULL;
		Info(newNode)=X;
		NB(newNode)=NULL;
		Parent(newNode)=NULL;
	}
	return newNode;
}

void nbDNode(nbAddr *Node)
{
	FS(*Node)=NULL;
	NB(*Node)=NULL;
	Parent(*Node)=NULL;
	free(*Node);
}

void nbInsert(nbTree *tRoot, nbAddr parent, nbType X){
	nbAddr newNode, temp;
	newNode=nbCNode(X);
	if (newNode !=NULL){ //Jika pengalokasian node baru berhasil
		
		if (Root(*tRoot) == NULL) //JIka belum terdapat root
			Root(*tRoot)=newNode;
		else
		{
			if(parent!=NULL) //Node di insert menjadi anak terakhir, jika parent tidak memiliki FS maka node akan menjadi FS
			{
				temp=parent;
				if (FS(temp) != NULL){
					temp=FS(temp);
					while(NB(temp)!=NULL)
						temp=NB(temp);
					NB(temp)=newNode;
				}else
					FS(temp) = newNode;
				Parent(newNode) = parent;
			}
			else
			{
				printf("Parent tidak ada\n");
				system("pause");
			}
		}
	}
	else
	{
		printf("Alokasi gagal");
	}
}

nbAddr nbSearch(nbAddr root, nbType src){
	nbAddr nSrc;
	if (root!=NULL)
	{
		if (Info(root)==src)
			return root;
		else{
			nSrc=nbSearch(FS(root),src);
			if (nSrc==NULL)
				return nbSearch(NB(root),src);
			else
				return nSrc;
		}
	}
	return NULL; // mereturn NULL jika tree kosong
}

void nbUpgrade(nbAddr *root)
{
	nbAddr temp;
	temp= NB(*root);
	if (FS(*root)==NULL) //jika first son null
		FS(*root)=temp;
	while(temp!=NULL) // jika next brothernya tidak null
	{
		Parent(temp)= *root;
		temp=NB(temp);
	}
}

void nbDelete(nbAddr *pDel, nbTree *pTree)
{
	nbAddr pCur;
	pCur=*pDel;
	
	if(Root(*pTree) == NULL) //kondisi ketika root kosong
	{
		printf("Tree Kosong");
		return;
	}
	if (pCur==Root(*pTree) && FS(pCur)==NULL) //kondisi ketika root memiliki 1 elemen
	{
		Root(*pTree)=NULL;
		nbDNode(&pCur);
		return;
	}
	
	//kondisi node merupakan leaf dan jika merupakan first son maka next brothernya menjadi first son
	if(FS(pCur) == NULL)
	{
		if(FS(Parent(pCur)) == pCur) //kondisi ketika node merupakan anak pertama dari parent
		{
			if(NB(pCur) != NULL) //ketika first son memiliki sibling
				FS(Parent(pCur)) = NB(pCur);
			else
				FS(Parent(pCur)) = NULL;
			nbDNode(&(*pDel));
		}else //kondisi ketika node bukan merupakan anak pertama
		{
			pCur = FS(Parent(pCur)); //pCur ditunjuk ke anak pertama 
			while(NB(pCur) != *pDel) //pencarian node sebelum pDel
				pCur = NB(pCur);
			if(NB(*pDel) == NULL) //kondisi ketika pDel merupakan last son
			{
				NB(pCur) = NULL;
				nbDNode(&(*pDel));
			}
			else //kondisi ketika pDel bukan merupakan last son
			{
				NB(pCur) = NB(*pDel);
				nbDNode(&(*pDel));
			}
		}
		return;	
	}
	else //kondisi node memiliki child
	{
		while( FS(pCur)!=NULL )
			pCur = FS(pCur); // pcur diisi dengan First son sampai null
		while (pCur != *pDel){
			nbUpgrade(&pCur);
			if (Parent(pCur)!=NULL)
				NB(pCur)=NB(Parent(pCur));
			else
				NB(pCur)=NULL;
			pCur= Parent(pCur);
		}
		
		pCur = *pDel;
		if(Parent(pCur) != NULL ) // ketika node memiliki parent 
		{
			if(FS(Parent(pCur)) == *pDel) //kondisi node merupakan first son dari parentnya
			{
				FS(Parent(pCur))=FS(pCur);
				Parent(FS(pCur)) = Parent(pCur);
				nbDNode(&(*pDel));
			}else //kondisi node bukan merupakan first son
			{
				pCur = FS(Parent(*pDel));
				while(NB(pCur) != *pDel) //pencarian node sebelum pDel
					pCur = NB(pCur);
				NB(pCur) = FS(*pDel);
				if(NB(*pDel) == NULL)
					NB(FS(*pDel)) = NULL;
				else
					NB(FS(*pDel)) = NB(*pDel);
				nbDNode(&(*pDel));
			}
			return;
		}
		else //kondisi ketika yang dihapus merupakan root
		{
			Root(*pTree) = FS(pCur)	;
			Parent(Root(*pTree)) = NULL;
			nbDNode(&(*pDel));
			return;
		}
	}	
}

void nbPrint(nbAddr node, char tab[]){
	char tempTab[255];	
	strcpy(tempTab, tab);
	strcat(tempTab, "-");
	if (node!=NULL){
		printf("%s%d\n",tab,Info(node));
		nbPrint(FS(node),tempTab);
		nbPrint(NB(node),tab);
	}
}

void nbtoBinary(bTree *btree, nbTree nbtree)
{
	bAddr bcur;
	bAddr temp;
	nbAddr cur;
	bool resmi;
	
	cur = Root(nbtree);
	bcur = bCNode(Info(cur));
	bRoot(*btree) = bcur;
	resmi = true;
	
	do
	{
		if(FS(cur) != NULL && resmi)
		{
			cur = FS(cur);
			bInsLeft(&bcur, Info(cur), &temp);
			bcur = temp;
		} else if (NB(cur) != NULL)
		{
			cur = NB(cur);
			bInsRight(&bcur, Info(cur), &temp);
			bcur = temp;
			resmi = true;
		} else
		{
			cur = Parent(cur);
			if(NB(cur)!= NULL)
				bcur = bSearch(bRoot(*btree), Info(cur));
			resmi = false;
		}
	} while(Parent(cur) != NULL);
}

void Preorder(nbAddr node)
{
	if (node!=NULL){
		printf("%d ",Info(node));
		Preorder(FS(node));
		Preorder(NB(node));
	}
}

void Postorder(nbAddr node)
{
	if (node!=NULL){
		Postorder(FS(node));
		printf("%d ",Info(node));
		Postorder(NB(node));
	}
}

void Inorder(nbAddr node)
{
	if (node!=NULL){
		Inorder(FS(node));
		Inorder(NB(node));
		printf("%d ",Info(node));
	}
}

	
