#include<stdio.h>
#include<conio.h>
#include<stdlib.h>


//deklarasi awal struct bst
struct Node{
	int info;
	Node *right, *left;
};

//array untuk input data otomatis
int arr[] = {7131, 4785, 8820, 654, 2306, 3029, 6587, 5371, 2069, 7816, 8119, 3096, 6909, 697, 3764, 3756, 6115, 8477, 9594, 8856, 3741, 8500, 8693, 1090, 7461, 3007, 1162, 6303, 6279, 3310};
Node *tree = NULL;

//fungsi insert 
void insertNode(Node **root, int bilBaru){
	if((*root) ==  NULL){
		//Node baru;
		Node *baru = NULL;
		//alokasi memori dari Node yang telah dibuat
		baru = (Node *)malloc(sizeof(Node));
		//inisialisasi node awal yang telah dibuat
		baru->info = bilBaru;
		baru->left = NULL;
		baru->right = NULL;
		(*root) = baru;
		(*root) -> left = NULL;
		(*root) -> right = NULL;
	}
	//jika data yang di insert lebih kecil dari element root
	//maka diletakan disebelah kiri
	else if(bilBaru < (*root)->info){
		insertNode(&(*root)->left, bilBaru);
	}
	//jika data yang di insert lebih besar dari element root
	//maka diletakan disebelah kanan
	else if(bilBaru > (*root)->info){
		insertNode(&(*root)->right, bilBaru);
	}
	//jika data yang di insert memiliki nilai yang sama dengan data yg ada
	else if(bilBaru == (*root)->info){
		printf("\nData sudah ada!");
	}
}

//fungsi mencetak secara preOrder
void preOrder(Node *root){
	if(root != NULL){
		printf("%i -> ", root->info);
		preOrder(root->left);
		preOrder(root->right);
	}
}

//fungsi mencetak secara inOrder
void inOrder(Node *root){
	if(root != NULL){
		inOrder(root->left);
		printf("%i -> ", root->info);
		inOrder(root->right);
	}
}

//fungsi mencetak secara postOrder
void postOrder(Node *root){
	if(root != NULL){
		postOrder(root->left);
		postOrder(root->right);
		printf("%i -> ", root->info);
	}
}

//fungsi mengetahui jumlah Node yang terdapat didalam program
int count(Node *root){
	if(root == NULL)
		return 0;
	else{
		return count(root->left) + count(root->right) + 1;
	}
}

//fungsi searchBST untuk mencari ketersediaan Node
Node* search(Node **root, int src){
	if((*root) == NULL){
		printf("\nDATA TIDAK DITEMUKAN");
	}
	//jika data lebih kecil dari isi root
	else if(src < (*root)->info){
		printf("%i -> ", (*root)->info);
		search(&(*root)->left, src);
	}
	//jika data lebih besar dari isi root
	else if(src > (*root)->info){
		printf("%i -> ", (*root)->info);
		search(&(*root)->right, src);
	}
	//jika data cocok dengan isi root
	else if(src == (*root)->info)
		printf("\nDATA DITEMUKAN!");
}

//fungsi mengukur kedalaman BST
int deep(Node *root){
	if(root == NULL)
		return -1;
	else{
		int f, l;
		f = deep(root->left);
		l = deep(root->right);
		if(f > l)
			return f + 1;
		else
			return l + 1;
	}
}

//fungsi deleteNode untuk menghapus Node
void delNode(Node **root, int del){
	Node *curr;
	Node *parent;
	curr = (*root);
	
	bool flag = false;
	
	while(curr != NULL){
		if(curr->info == del){
			flag = true;
			printf("\nData berhasil dihapus.");
			break;
		}
		else{
			parent = curr;
			if(del > curr->info)
				curr = curr->right;
			else
				curr = curr->left;
		}
	}
	
	if(!flag){
		printf("\nData tidak ditemukan. Tidak ada penghapusan.");
		return;
	}
	
	
	//jika hanya memiliki 1 level kedalaman, atau hanya terdapat root
	//maka curr tidak memiliki parent
	if(deep(tree) == 0){
		if(curr->left == NULL && curr->right == NULL){
			(*root) = NULL;
			return;
		}
	}
	
	//jika memiliki lebih dari 1 level kedalaman, sehingga curr memiliki parent
	else if(deep(tree) > 0){
		//Node yang dihapus tidak memiliki anak
		if(curr->left == NULL && curr->right == NULL){
			//Node yang ingin dihapus merupakan anak kiri parentnya
            if(parent->left == curr){
				//ganti parent->left menjadi NULL
                parent->left = NULL;
                delete curr;
			}
            //Node yang ingin dihapus merupakan anak kanan parentnya
            else{
				//ganti parent->right menjadi NULL
                parent->right = NULL;
                delete curr;
        	}
			return;
    	}
		
		//Node yang dihapus memiliki anak tunggal anak (kiri/kanan)
		if((curr->left == NULL && curr->right != NULL) || (curr->left != NULL && curr->right == NULL)){
			//Node memiliki anak tunggal kanan
			if(curr->left == NULL && curr->right != NULL){
				//Node yang ingin dihapus merupakan anak kiri parentnya
				if(parent->left == curr){
					parent->left = curr->right;
					delete curr;
				}
				//Node yang ingin dihapus merupakan anak kanan parentnya
				else{
					parent->right = curr->right;
					delete curr;
				}
			}
			//Node memiliki anak tunggal kiri
			else{
				//Node yang ingin dihapus merupakan anak kiri parentnya
				if(parent->left == curr){
					parent->left = curr->left;
					delete curr;
				}
				//Node yang ingin dihapus merupakan anak kanan parentnya
				else{
					parent->right = curr->left;
					delete curr;
				}
			}
			return;
		}
		
		//Node yang dihapus memiliki 2(dua) anak
		//maka node akan diganti dengan nilai terkecil dari sub tree kanan
		if(curr->left != NULL && curr->right != NULL){
			//menggunakan variabel help supaya posisi curr asli tetap pada posisi yang akan dihapus
			//variable help digunakan untuk mengarahkan ke suatu Node
			Node *help;
			help = curr->right;
			
			//jika subtree kanan dari posisi node yang akan dihapus tidak memiliki anak
			if((help->left == NULL) && (help->right == NULL)){
				//ganti curr dengan help
				curr = help;
				delete help;
				curr->right = NULL;
			}
			//jika anak kanan dari curr memiliki curr
			else{
				//jika node anak kanan dari node curr memiliki anak kiri
				if((curr->right)->left != NULL){
					//variable help2 dan help3 digunakan agar posisi curr asli tetap diposisinya,
					//digunakan untuk mengarahkan ke suatu Node
					Node *help2;
					Node *help3; //berlaku sbg parent dari help
					
					help2 = curr->right;
					help3 = (curr->right)->left ;
					
					//mengarahkan posisi node ke node paling kiri(menuju node yang memiliki nilai terkecil)
					while(help2->left != NULL){
						help3 = help2;
						help2 = help2->left;
					}
					//ganti nilai node curr dengan nilai dari node help
					curr->info = help2->info;
					delete help2;
					help3->left = NULL;
				}
				//jika node anak kanan dari node curr tidak memiliki anak kiri
				else{
					Node* tmp;
					tmp = curr->right;
					//ganti nilai dari node curr dengan nilai dari node tmp
					curr->info = tmp->info;
					curr->right = tmp->right;
					delete tmp;
				}
			}
			return;
		}
	}	
}

int MaxNode(Node **root){
	Node *curr;
	curr = (*root);
	
	while(curr->right != NULL)
		curr = curr->right;
	return (curr->info);
}

int MinNode(Node **root){
	Node *curr;
	curr = (*root);
	
	while(curr->left != NULL)
		curr = curr->left;
	return (curr->info);
}

//main function
int main(){
	char menu;
	int del, src;
	Node *root;
	root = NULL;
	
	//array untuk input data otomatis
	int arr[] = {7131, 4785, 8820, 654, 2306, 3029, 6587, 5371, 2069, 7816, 8119, 3096, 6909, 697, 3764, 3756, 6115, 8477, 9594, 8856, 3741, 8500, 8693, 1090, 7461, 3007, 1162, 6303, 6279, 3310};
		
	//perulangan menu
	while(true){
		system("cls");
		int info;
		printf("\tMini C Program BST\n");
		printf("\t==================");
		printf("\n\n Menu Navigasi ");
		printf("\n-=============-\n");
		printf(">A< Masukkan bilangan otomatis\n");
        printf(">B< Masukkan bilangan secara manual\n");
		printf(">C< Print Pre-Order\n");
        printf(">D< Print In-Order\n");
        printf(">E< Print Post-Order\n");
        printf(">F< Delete\n");
        printf(">G< Search Node\n");
        printf(">H< Hitung Node pada Tree\n");
        printf(">I< Kedalaman Tree\n");
        printf(">J< Kosongkan Data\n");
        printf(">K< Nilai Node Terbesar\n");
        printf(">L< Nilai Node Terkecil\n");
        printf(">X< Keluar\n");
        printf("Pilihan Anda (Aktifkan Capslock): ");
        scanf("%c",&menu);
        switch(menu){
        	case 'A':{
        		//insert node secara otomatis
				for(int i = 0; i < 30; i++){
        			insertNode(&tree, arr[i]);
				}
				printf("\nData telah diinput otomatis.");
				printf("\n\nPress Any Key.");
				_getch();
				break;
			}
			
			case 'B':{
				//insert node secara manual
				if(tree != NULL){
					printf("\n>INPUT<\n\n");
					printf("Masukkan data dengan format bilangan bulat(int).\n");
					printf("-> ");
					scanf("%d", &info);
					insertNode(&tree, info);
				}
				else{
					printf("\n>INPUT<\n\n");
					printf("Masukkan data dengan format bilangan bulat(int).\n");
					printf("-> ");
					scanf("%d", &info);
					insertNode(&tree, info);
				}
				printf("\nData berhasil diinput!");
				printf("\n\nPress Any Key.");
				_getch();
				break;
			}
			
			case 'C':{
				//mencetak data secara preOrder
				printf("\n>PRE-ORDER<\n\n");
				printf("Output Bilangan Pre-Order: \n");
				printf("----------------------->>>\n");
				if(tree != NULL)
					preOrder(tree);
				else{
					printf("Data kosong!. Silahkan isi secara otomatis atau manual.");
				}
				printf("\n\nPress Any Key.");
				_getch();
				break;
			}
			
			case 'D':{
				//mencetak data secara inOrder
				printf("\n>IN-ORDER<\n\n");
				printf("Output Bilangan In-Order: \n");
				printf("----------------------->>>\n");
				if(tree != NULL)
					inOrder(tree);
				else{
					printf("Data kosong!. Silahkan isi secara otomatis atau manual.");
				}
				printf("\n\nPress Any Key.");
				_getch();
				break;
			}
			
			case 'E':{
				//mencetak data secara postOrder
				printf("\n>POST-ORDER<\n\n");
				printf("Output Bilangan Post-Order: \n");
				printf("----------------------->>>\n");
				if(tree != NULL)
					postOrder(tree);
				else{
					printf("Data kosong!. Silahkan isi secara otomatis atau manual.");
				}
				printf("\n\nPress Any Key.");
				_getch();
				break;
			}
			
			case 'F':{
				//menghapus node pilihan
				//sebelum dihapus
				printf("\n>DELETE<\n\n");
				if(tree != NULL){
					printf("Isi Tree sebelum node pilihan dihapus: ");
					printf("\n\nPre-Order: \n");
					printf("-------->>>\n");
					preOrder(tree);
					printf("\n\nIn-Order: \n");
					printf("-------->>>\n");
					inOrder(tree);
					printf("\n\nPost-Order: \n");
					printf("-------->>>\n");
					postOrder(tree);
					
					//input bilangan node yang akan dihapus
					printf("\n\nMasukkan data yang ingin dihapus: ");
	                scanf("%d", &del);
	                delNode(&tree, del);
	                
				}
				else{
					printf("Data kosong!. Silahkan isi secara otomatis atau manual.");
				}
				
				printf("\n\nPress Any Key.");
				_getch();
				break;
			}
			
						
			case 'G':{
				//mencari sebuah nilai dalam tree
				printf("\n>SEARCH<\n\n");
				printf("\nOUTPUT -> Hanya untuk mengecek apakah data dimaksud terdapat dalam tree");
				if(tree != NULL){
					printf("\n\nPre-Order: \n");
					printf("-------->>>\n");
					preOrder(tree);
					printf("\n\nIn-Order: \n");
					printf("-------->>>\n");
					inOrder(tree);
					printf("\n\nPost-Order: \n");
					printf("-------->>>\n");
					postOrder(tree);
					printf("\n\nMasukkan data yang ingin dicari : ");
                    scanf("%d", &src);
					printf("\nSimpul yang dilewati untuk pencarian: \n");
					search(&tree, src);
				}
				else{
					printf("Data kosong!. Silahkan isi secara otomatis atau manual.");
				}
	    		printf("\n\nPress Any Key.");
				_getch();
				break;
			}
			
			case 'H':{
				//menghitung jumlah node pada tree
				printf("\n>COUNT NODE IN TREE<\n\n");
				if(tree != NULL){
					printf("Jumlah Node dalam Tree : %d\n", count(tree));
				}
				else{
					printf("Data kosong!. Silahkan isi secara otomatis atau manual.");
				}
				printf("\n\nPress Any Key.");
				_getch();
				break;
			}
			
			case 'I':{
				//melihat kedalaman/jumlah level dari tree
				printf("\n>DEPTH TREE<\n\n");
				if(tree != NULL){
					printf("Kedalaman BST : %d\n", deep(tree));
				}
				else{
					printf("Data kosong!. Silahkan isi secara otomatis atau manual.");
				}
				printf("\n\nPress Any Key.");
				_getch();
				break;
			}
			
			case 'J':{
				//reset BST
				if(tree != NULL){
					tree = NULL;
					printf("\n>RESET TREE<\n\n");
					printf("BST Kosong. Data BST telah direset.");
				}
				else{
					printf("Data kosong!. Silahkan isi secara otomatis atau manual.");
				}
				printf("\n\nPress Any Key.");
				_getch();
				break;
			}
			
			case 'K':{
				if(tree != NULL){
					printf("\n>NILAI TERBESAR<\n\n");
					printf("Nilai terbesar dalam tree adalah %i ", MaxNode(&tree));
				}
				else{
					printf("Data kosong!. Silahkan isi secara otomatis atau manual.");
				}
				printf("\n\nPress Any Key.");
				_getch();
				break;
			}
			
			case 'L':{
				if(tree != NULL){
					printf("\n>NILAI TERKECIL<\n\n");
					printf("Nilai terkecil dalam tree adalah %i ", MinNode(&tree));
				}
				else{
					printf("Data kosong!. Silahkan isi secara otomatis atau manual.");
				}
				printf("\n\nPress Any Key.");
				_getch();
				break;
			}
			
			case 'X':{
				printf("\nPROGRAM DITUTUP.");
				exit(0);
				break;
			}
		}
	}
}


