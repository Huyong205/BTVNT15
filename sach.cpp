#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
  char name[100];
  int pages;
  struct Node *sibling;  
  struct Node *child;    
};

typedef struct Node Node;

Node* makeNode(const char* name, int pages) { 
  Node* newNode = (Node*)malloc(sizeof(Node));
  strcpy(newNode->name, name);
  newNode->pages = pages;  
  newNode->sibling = NULL;
  newNode->child = NULL;
  return newNode;
}

void addNodeChild(Node** parent, const char* name, int pages){ 
  Node* newNode = makeNode(name, pages);
  if((*parent)->child == NULL){
    (*parent)->child = newNode;
  } 
	else{
    Node* current = (*parent)->child;
    while (current->sibling != NULL) {
      current = current->sibling;
    }
    current->sibling = newNode;
  }
}

void updatePages(Node* root) {
  if (root == NULL) return;

  int totalPages = root->pages;

  Node* child = root->child;
  while (child != NULL) {
    updatePages(child); 
    totalPages += child->pages;
    child = child->sibling;
  }

  root->pages = totalPages;
}


int dem(Node* head){
	int cnt = 0;
	Node* con = head->child;
	while(con != NULL){
		cnt++;
		con = con->sibling;
	}
	return cnt;
}

int demHet(Node* head){
	if(head == NULL) return 0;
	return 1 + demHet(head->child) + demHet(head->sibling);
}

Node* chuongDaiNhat(Node* head){
	Node* chuong1 = head->child;
	Node* ret = NULL;
	int res = 0;
	while(chuong1 != NULL){
		int tmp = demHet(chuong1->child);
		if(tmp > res){
			res = tmp;
			ret = chuong1;
		}
		chuong1 = chuong1->sibling;
	}
	return ret;
}

// Tìm node bằng DFS
Node* findDfs(Node* current, const char* Name) {
  if (current == NULL) return NULL;
  if (strcmp(current->name, Name) == 0) {
    return current;
  }
  // Tìm trong các node con
  Node* foundInChild = findDfs(current->child, Name);
  if (foundInChild != NULL) return foundInChild;

  return findDfs(current->sibling, Name);
}

void in(Node* roots, int cnt) {
  Node* tmp = roots;
  while (tmp != NULL) {
    printf("|");
    for (int i = 0; i < cnt; i++) printf(" ");
    printf("%s ", tmp->name);
    for(int i = 0; i < 90 - cnt - strlen(tmp->name); i++) printf(" ");
    printf("|So trang: %-6d", tmp->pages);
    printf("|\n");
    in(tmp->child, cnt + 1);
    tmp = tmp->sibling;
  }
}


void inCon(Node* roots){
	printf("Ten: %s\n", roots->name);
	Node* con = roots->child;
	while(con != NULL){
		printf("   Ten: %s\n", con->name);
		con = con->sibling;
	}
}

Node* findAE(Node* head, const char* name){
	Node* tmp = head;
	while(tmp != NULL){
		if(strcmp(tmp->name, name) == 0) return tmp;
		tmp = tmp->sibling;
	}
	return NULL;
}

void freeTree(Node* node) {
  if (node == NULL) return;
  freeTree(node->child);    // Giải phóng cây con
  freeTree(node->sibling);  // Giải phóng các node anh em
  free(node);
}

void xoaAE(Node** head, const char* name){
    Node* del = findAE(*head, name);
    if (del == NULL) return;  // Không tìm thấy node cần xóa
    
    if (del == *head) {
        // Nếu node cần xóa là node đầu tiên của danh sách
        *head = del->sibling;
        freeTree(del->child);
        free(del);
    } else {
        Node* tmp = *head;
        while (tmp != NULL && tmp->sibling != del) {
            tmp = tmp->sibling;
        }

        if (tmp != NULL) {
            tmp->sibling = del->sibling;  // Cập nhật con trỏ sibling của node cha
            freeTree(del->child);  // Giải phóng cây con của node bị xóa
            free(del);
        }
    }
}




int main(){
	Node* Book = makeNode("Giai tich 2", 0);
	addNodeChild(&Book, "Chuong 1: Cac ung dung cua phep vi phan trong hinh hoc", 0);
	addNodeChild(&Book, "Chuong 2: Tich phan boi", 0);
	addNodeChild(&Book, "Chuong 3: Tich phan phu thuoc tham so", 0);
	addNodeChild(&Book, "Chuong 4: Tich phan duong", 0);
	addNodeChild(&Book, "Chuong 5: Tich phan mat", 0);
	addNodeChild(&Book, "Chuong 6: Ly thuyet truong", 0);
	addNodeChild(&(Book->child), "1. Cac ung dung cua phep tinh vi phan trong hinh hoc phang", 0);
	addNodeChild(&(Book->child), "2. Cac ung dung cua phep tinh vi phan trong hinh hoc khong gian", 0);
	
	addNodeChild(&(Book->child->child), "1.1. Phuong trinh tiep tuyen va phap tuyen cua duong cong tai 1 diem", 12);
	addNodeChild(&(Book->child->child), "1.2. Do cong cua duong cong", 32);
	addNodeChild(&(Book->child->child), "1.3. Hinh bao cua ho duong cong phu thuoc mot tham so", 43);
	
	addNodeChild(&(Book->child->child->sibling), "2.1. Ham vector", 43);
	addNodeChild(&(Book->child->child->sibling), "2.2 Phuong tinh tiep tuyen va phap dien cua duong cong cho duoi dang tham so", 54);
	addNodeChild(&(Book->child->child->sibling), "2.3 Phuong trinh phap tuyen va tiep dien cua mat cong", 54);
	addNodeChild(&(Book->child->child->sibling), "2.4 Phuong trinh tiep tuyen va phap dien cua duong cong cho duoi dang giao cua hai mat", 31);
	updatePages(Book);
	while(1){
		system("cls");
		printf("+----------------------------------------------------------------------------------+\n");
		printf("|%46s%-36s|\n", Book->name, " ");
		printf("+----------------------------------------------------------------------------------+\n");
		Node* con = Book->child;
		while(con != NULL){
			printf("|%-65s|So trang: %-6d|\n", con->name, con->pages);
			con = con->sibling;
		}
		printf("+----------------------------------------------------------------------------------+\n");
		printf("|So chuong: %-71d|\n", dem(Book));
		printf("|Tong so trang: %-67d|\n", Book->pages);
		printf("+----------------------------------------------------------------------------------+\n");
		printf("Nhap chuong muon chon (-1 de thoat): ");
		int lc; scanf("%d", &lc);
		if(lc == -1) break;
		else{   
			char name[100];
				
			while(lc != 1 && lc != 2 && lc != 3 && lc != 4 && lc != 5 && lc != 6){
				printf("Loi!\n");
				printf("Vui long nhap lai: "); 
				scanf("%d", &lc);
			}
			if(lc == 1) strcpy(name, "Chuong 1: Cac ung dung cua phep vi phan trong hinh hoc");
			else if(lc == 2) strcpy(name, "Chuong 2: Tich phan boi");
			else if(lc == 3) strcpy(name, "Chuong 3: Tich phan phu thuoc tham so");
			else if(lc == 4) strcpy(name, "Chuong 4: Tich phan duong");
			else if(lc == 5) strcpy(name, "Chuong 5: Tich phan mat");
			else if(lc == 6) strcpy(name, "Chuong 6: Ly thuyet truong");
				
			Node* chuong = findDfs(Book, name);
			while(1){
				system("cls");
				printf("+------------------------------------------------------------------------------------------------------------+\n");
				printf("|%s/%-96s|\n", Book->name, name);
				printf("+------------------------------------------------------------------------------------------------------------+\n");
				Node* con = chuong->child;
				in(con, 0);
				printf("+------------------------------------------------------------------------------------------------------------+\n");
				printf("|Tong so trang: %-93d|\n", chuong->pages);
				printf("+------------------------------------------------------------------------------------------------------------+\n");
				printf(" 1. Them muc con\n");
				printf(" 2. Xoa muc con\n");
				printf("-1. Thoat\n");
				printf("Nhap lua chon: ");
				int lc2; scanf("%d", &lc2);
				if(lc2 == -1) break;
				else if(lc2 == 1){
					getchar();
					char ten[100];
					int pages;
					printf("Nhap ten muc muon them: "); gets(ten);
					printf("Nhap so trang: "); scanf("%d", &pages);
					addNodeChild(&chuong, ten, pages);
				}
				else if(lc2 == 2){
					getchar();
					char ten[100];
					printf("Nhap ten muc muon xoa: "); gets(ten);
					Node* del = findDfs(chuong, ten);
					if(del == NULL){
						printf("Khong ton tai muc\n");
						printf("Nhap phim bat ky de tiep tuc...");
						getchar();
					}
					else{
						xoaAE(&chuong, ten);
						printf("Da xoa thanh cong\n");
						printf("Nhap phim bat ky de tiep tuc...");
						getchar();
					}
				}
			}
		}		                    
	}
	
	return 0;
}
