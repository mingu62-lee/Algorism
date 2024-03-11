#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define MAX_CODE 100
#define MAX_ELEMENT 100
int s1[100];
int sum = 0;
typedef struct TreeNode {
	char data; //���ĺ�
	int count; //�󵵼�
	struct TreeNode *left_child;
	struct TreeNode *right_child;
	char code[MAX_CODE];
	int depth;
} TreeNode;
typedef struct {
	TreeNode *ptree;
	char key;
} element;
typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

void init(HeapType *h) {
	h->heap_size = 0;
}

void insert_min_heap(HeapType *h, element item) {
	int i;
i = ++(h->heap_size);

while ((i != 1) && (item.key < h->heap[i / 2].key)) {
	h->heap[i] = h->heap[i / 2];
	i /= 2;
}
h->heap[i] = item;
}

element delete_min_heap(HeapType *h) {
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		if ((child < h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key)
			child++;
		if (temp.key <= h->heap[child].key)
			break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}


TreeNode *make_tree(TreeNode *left, TreeNode *right) {
	TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
	if (node == NULL) {
		fprintf(stderr, "�޸� ����\n");
		exit(1);
	}
	node->left_child = left;
	node->right_child = right;
	return node;
}

void destroy_tree(TreeNode *root) {
	if (root == NULL) return;
	destroy_tree(root->left_child);
	destroy_tree(root->right_child);
	free(root);
}


void inorder_heap(element *e, int num, int heap_size) //���� ��������
{
	if (num < heap_size) { //�ε������� heap������� Ŀ�� �ȵȴ�..
		inorder_heap(e, num * 2, heap_size);//�����ڽ� ���Ǳ�
		printf("%c ", e[num].ptree->data);//��Ʈ ���ǰ�
		inorder_heap(e, num * 2 + 1, heap_size);  //�������ڽ� ���Ǳ�
	}
} //heap�� index�� 1���� �����̹Ƿ� size+1

void huffman_code(TreeNode* r, int n, char* code) {
	if (r) {
		n++;
		code[n] = '1';
		huffman_code(r->right_child, n, code);
		code[n] = '0';
		huffman_code(r->left_child, n, code);
		code[n] = '\0';
		
		if (r->left_child == NULL && r->right_child == NULL) {
			strcpy(r->code, code);
			r->depth = n;
		}
	}
}
void sub_order(TreeNode *r, int v) {
	int i = 0;
	if (r) {
		sub_order(r->right_child, v);
		sub_order(r->left_child, v);
		if ((r->left_child == NULL || r->right_child == NULL) && r->depth == v) {

			printf("�� �� = %d  data = %c, ������code = %s, depth=%d \n",
				r->count, r->data, r->code, r->depth);
			s1[i] = strlen(r->code)*r->count;
			sum = sum + s1[i];
			i++;

		}
	}
}


void level_order(TreeNode * r) {
	int i;
	for (i = 0; i < 10; i++) {
		sub_order(r, i);
	}
}


void huffman_tree(int freq[], char alpabet[], int n) {
	int i, j = 49; // 49�� �ƽ�Ű�ڵ� => ����1
	TreeNode *node;
	TreeNode *x;
	HeapType heap;
	element e, e1, e2;
	char* code = (char*)malloc(sizeof(char));

	init(&heap);
	for (i = 0; i < n; i++) {
		node = make_tree(NULL, NULL);
		e.key = node->count = freq[i]; //�󵵼� ����
		node->data = alpabet[i]; //���ĺ� ����
		e.ptree = node;
		insert_min_heap(&heap, e); //�ּ����� 

		inorder_heap(heap.heap, 1, heap.heap_size + 1); //������ȸ
		printf("\n");
	}

	for (i = 1; i < n; i++) { // n-1�� ����� ������ Ʈ���� ��
		e1 = delete_min_heap(&heap);
		e2 = delete_min_heap(&heap);
		
		x = make_tree(e1.ptree, e2.ptree);
		
		e.key = x->count = e1.key + e2.key; //�ּҰ� + �ι�° �ּҰ��� ����
	
		e.ptree = x;
		insert_min_heap(&heap, e);
	}
	printf("\n********************************************\n\n");
	printf("������ Ʈ�� \n\n");

	

	e = delete_min_heap(&heap);
	huffman_code(e.ptree, -1, code);
	level_order(e.ptree);
	destroy_tree(e.ptree);

}

int main(void) {
	int n = 0; //�Է��� ���� ������ ����
	int freq[100]; //�󵵼� ������ ����
	char alpabet[100]; //���ĺ� ������ ����
	int sum1 = 0;

	printf("**************������ Ʈ�� ���� *******************\n\n");
	printf("�Է��� ���� ���� :");
	scanf("%d", &n);

	for (int i = 0; i < n; i++) { //���������� �󵵼������� �Է� ����

		printf("\n��������  &&   �󵵼� ���� ->");
		scanf("%s  %d", &alpabet[i],  &freq[i]); //�Է¹��� ���ĺ� ����
		sum1 = sum1 + freq[i];
	}

	printf("\n������ȸ ������� ���\n");
	huffman_tree(freq, alpabet, n); //������ Ʈ�� ����

	printf("\n\n���� �ڵ� ��Ʈ ->%d bit\n", sum1*8);
	printf("\n������ �ڵ� ���� ->%d bit\n", sum);

	_getch();
	return 0;
}