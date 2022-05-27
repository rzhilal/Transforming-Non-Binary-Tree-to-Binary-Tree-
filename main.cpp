#include <conio.h>
#include <windows.h>
#include <stdio.h>

#include "nbtree.h"
#include "btree.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() 
{
	nbTree pTree;
	nbAddr srcNode;
	nbCreate(&pTree);
	int inputan1,inputan2;
	char str[]="";
	
	bTree Tree, AVL, AVL_edit;
	bCreate(&Tree);
	bCreate(&AVL);
	bCreate(&AVL_edit);
	
	int pilihan;
	bool edit = true;
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tProgram Konversi Non Biner ke Biner");
	printf("\n\t\t\t\t\t");
	system("pause");
	system("cls");
	printf("=============================================   Pembuatan Non Binary Tree   ============================================\n");
	printf("Masukan nilal untuk root : ");
	scanf("%d", &inputan1);
	nbInsert(&pTree, NULL, inputan1);
	
	while(edit)
	{
		system("cls");
		printf("=============================================   Pembuatan Non Binary Tree   ============================================\n");
		nbPrint(Root(pTree), str);
		printf("\n1. Input nilai\n");
		printf("2. Delete nilai\n");
		printf("3. Selesai membuat tree\n");
		printf("Tentukan pilihan : ");
		scanf("%d", &pilihan);
		switch(pilihan)
		{
			case 1:
				{
					printf("\nTentukan Parent 	: ");
					scanf("%d", &inputan1);
					printf("\nMasukan Nilai 	: ");
					scanf("%d", &inputan2);
					nbInsert(&pTree, nbSearch(Root(pTree), inputan1), inputan2);
					break;
				}
			case 2:
				{
					printf("\nMasukan Nilai yang ingin di delete	: ");
					scanf("%d", &inputan1);
					srcNode = nbSearch(Root(pTree), inputan1);
					nbDelete(&srcNode, &pTree);
					break;
				}
			case 3:
				{
					edit = false;
					break;
				}
			default:
				{
					printf("pilihan tidak ada\n");
					system("pause");
					system("cls");
				}
		}
	}
	
	nbtoBinary(&Tree, pTree);
	
	toAVL(bRoot(Tree), &bRoot(AVL));
	toAVL(bRoot(Tree), &bRoot(AVL_edit));
	
	for(;;)
	{
		system("cls");
		printf("==============================================   Program Konversi Tree   ==============================================\n");
		printf("1. Proses Konversi Tree dari Non ke Binary\n");
		printf("2. Edit AVL Tree\n");
		printf("3. Traverse Tree\n");
		printf("4. Exit\n");
		printf("Tentukan pilihan : ");
		scanf("%d", &pilihan);
		switch(pilihan)
		{
			case 1:
				{
					printf("========================================================================================================================");
					printf("\nTree Non Binary : \n");
					nbPrint(Root(pTree), str);
					printf("\nPreorder : ");
					Preorder(Root(pTree));
					printf("\n");
					printf("========================================================================================================================");
					printf("\nHasil Konversi Non Binary ke Binary : \n");
					printBT(bRoot(Tree));
					printf("\nPreorder : ");
					printPreorder(bRoot(Tree));
					printf("\n");
					printf("========================================================================================================================");
					printf("\nPenerapan Algoritma AVL : \n");
					printBT(bRoot(AVL));
					system("pause");
					system("cls");
					break;
				}
			case 2:
				{
					edit = true;
					while(edit)
					{
						system("cls");
						printf("==================================================   Edit AVL Tree   =================================================\n");
						printBT(bRoot(AVL_edit));
						printf("\n1. Insert\n");
						printf("2. Delete\n");
						printf("3. Selesai\n");
						printf("Tentukan pilihan : ");
						scanf("%d", &pilihan);
						switch(pilihan)
						{
							case 1:
								{
									printf("\nMasukan Nilai : ");
									scanf("%d", &inputan1);
									bRoot(AVL_edit) = insertNode(&bRoot(AVL_edit), inputan1);
									break;
								}
							case 2:
								{
									printf("\nMasukan Nilai : ");
									scanf("%d", &inputan1);
									if(Info(bRoot(AVL_edit)) == inputan1)
									{
										printf("\nDeletion tidak dapat dilakukan pada root\n");
										system("pause");
									}
									else
										bRoot(AVL_edit) = deleteNode(&bRoot(AVL_edit), inputan1);
									break;
								}
							case 3:
								{
									edit = false;
									break;
								}
							default:
								{
									printf("\n Pilihan tidak ada");
									break;
								}
						}
					}
					break;
				}
			case 3:
				{
					system("cls");
					printf("================================================   Traverse Tree   ===============================================\n");
					printf("\n1. Non Binary Tree\n");
					printf("2. AVL Tree\n");
					printf("Tentukan pilihan : ");
					scanf("%d", &pilihan);
					switch(pilihan)
					{
						case 1:
							{
								nbPrint(Root(pTree), str);
								printf("\n1. Preorder\n");
								printf("2. Postorder\n");
								printf("3. Inorder\n");
								printf("Tentukan pilihan : ");
								scanf("%d", &pilihan);
								switch(pilihan)
								{
									case 1:
										{
											printf("Hasil preorder : ");
											Preorder(Root(pTree));
											printf("\n");
											system("pause");
											system("cls");
											break;
										}
									case 2:
										{
											printf("Hasil Postorder : ");
											Postorder(Root(pTree));
											printf("\n");
											system("pause");
											system("cls");
											break;
											
										}
									case 3:
										{
											printf("Hasil Inorder : ");
											Inorder(Root(pTree));
											printf("\n");
											system("pause");
											system("cls");
											break;
										}
									default:
										{
											printf("Pilihan tidak ada");
											break;
										}
								}
								break;
							}
						case 2:
							{
								printBT(bRoot(AVL_edit));
								printf("\n1. Preorder\n");
								printf("2. Postorder\n");
								printf("3. Inorder\n");
								printf("Tentukan pilihan : ");
								scanf("%d", &pilihan);
								switch(pilihan)
								{
									case 1:
										{
											printf("Hasil preorder : ");
											printPreorder(bRoot(AVL_edit));
											printf("\n");
											system("pause");
											system("cls");
											break;
										}
									case 2:
										{
											printf("Hasil Postorder : ");
											printPostorder(bRoot(AVL_edit));
											printf("\n");
											system("pause");
											system("cls");
											break;
											
										}
									case 3:
										{
											printf("Hasil Inorder : ");
											printInorder(bRoot(AVL_edit));
											printf("\n");
											system("pause");
											system("cls");
											break;
										}
									default:
										printf("Pilihan tidak ada");
								}
								break;	
							}
					}
					break;
				}
			case 4:
				return 0;
			default:
				{
					printf("\n Pilihan tidak ada");
					break;
				}		
			
		}
	}
	return 0;
}

	