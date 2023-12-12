#include<iostream>
#include<ctime>

#define MIN 0
#define MAX 100
#define M 11
using namespace std;


struct Node {
	int data;
	Node* next;
};

bool check(int a[], int size, int x) {
	for (int i = 0; i < size; i++) {
		if (x == a[i])
			return false;
	}
	return true;
}

void init(int a[], int n) {
	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		a[i] = MIN + rand() % (MAX - MIN + 1);
//		while (!check(a, i, a[i])) {
//			a[i] = MIN + rand() % (MAX - MIN + 1);
//		}
	}
}

// Bam phan tu
int Hashing(int x) {
	return x % M;
}

// them phan tu moi vao duoi moi ngan cua bang bam
void addTail(Node*& last, int x) {
	Node* temp = new Node{ x,NULL };
	if (last == NULL)
		last = temp;
	else {
		Node* l = last;
		while (l != NULL && l->next != NULL)
			l = l->next;
		l->next = temp;
	}
}

void addTable(Node* table[], int x) {
	int key = Hashing(x); // Bam x thanh dia chi trong bang bam
	addTail(table[key], x); // them x vao ngan "key" cua bang bam
}

void deleteFirst(Node*& bot) {
	bot = bot->next;
}
void deleteLast(Node*& bot) {
	Node* temp = bot;
	while (temp->next->next != NULL)
		temp = temp->next;
	temp->next = NULL;
}
void deleteMid(Node*& bot, int n) {
	Node* temp = bot;
	for (int i = 0; i < n; i++)
		temp = temp->next;
	temp->next = temp->next->next;
}

void deleteTable(Node* table[], int x) {
	int key = Hashing(x);
	Node* temp = table[key];
	for (int i = 0; ; i++, temp = temp->next) {
		if (x == temp->data) {
			if (i == 0)
				deleteFirst(temp);
			else if (temp->next == NULL)
				deleteLast(temp);
			else
				deleteMid(temp, i);

			if (temp == NULL)
				break;
		}
	}
}

// Duyet qua cac phan tu trong 1 danh sach lien ket
void travel(Node* bot) {
	while (bot != NULL) {
		cout << "\t" << bot->data;
		bot = bot->next;
	}
}
// Xuat ra tat ca
void travelTable(Node* table[]) {
	for (int i = 0; i < M; i++) {
		if (table[i] != NULL) {
			cout << "Bucket " << i << ": ";
			travel(table[i]);
			cout << endl;
		}
	}
}


int main() {
	int a[100000];
	int n;
	cout << "n = "; cin >> n;
	init(a, n);
	for (int i = 0; i < n; i++) {
		cout << " " << a[i];
	}
	cout << endl;
	///////////////////////////////  
	Node* table[M];
	for (int i = 0; i < M; i++) {
		table[i] = NULL;
	}
	for (int i = 0; i < n; i++) {
		addTable(table, a[i]);
	}
	travelTable(table);
	int x;
	cout << "\nx = "; cin >> x;
	deleteTable(table, x);
	travelTable(table);
	return 0;
}