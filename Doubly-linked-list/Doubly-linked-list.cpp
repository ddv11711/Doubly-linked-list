#include <iostream>
using namespace std;
template<typename T>
class List{
public:
	List();
	~List();
	int GetSize() {return Size;}
	void push_back(int data);
	void pop_front();
	void pop_back();
	void clear();
	void removeAt(int index);
	T& operator[](const int index);
private:
	class Node {
	public:
		Node* pNext;
		Node* pPrev;
		int data;
		Node (int data, Node* pPrev=nullptr,Node*pNext=nullptr) {
			this->data = data;
			this->pNext = pNext;
			this->pPrev = pPrev;
		}
		~Node(){}
	};
	int Size;
	Node* head;
	Node* tail;
};
template<typename T>
List<T>::List(){
	Size = 0;
	head = nullptr;
	tail = nullptr;
}
template<typename T>
List<T>::~List(){
	clear();
}
template<typename T>
void List<T>::push_back(int data){
	if (head == nullptr) head =tail= new Node(data);
	else {
		Node* current = tail;
		tail= new Node(data, current);
		current->pNext = tail;		
	}
	Size++;
}
template<typename T>
T& List<T>::operator[](const int index){
	int counter;
	Node* current;
	if (index > (Size-1)  / 2) {
		current = this->tail;
		for (counter = Size-1; current != nullptr; counter--) {
			  if (counter == index)return current->data;
			  current = current->pPrev; 
		}
	}
	else {
		 current = this->head;
		 for (counter = 0; current != nullptr;counter++) {
			   if (counter == index)return current->data;
			   current = current->pNext;
		}
	}	
}
template<typename T>
void List<T>::pop_front(){
	Node* temp = head;
	head = head->pNext;
	delete temp;
	Size--;
}
template<typename T>
void List<T>::pop_back(){
	Node* temp = tail;
	tail = tail->pPrev;
	delete temp;
	Size--;
}
template<typename T>
void List<T>::clear(){
	while (Size) pop_front();
}
template<typename T>
void List<T>::removeAt(int index){
	if (index == 0 || index == (Size - 1)) {
		if (index == 0) pop_front();
		else pop_back();
	}
	else {
		if (index > (Size - 1) / 2) {
			Node* previous;
			previous = this->tail;
			for (int i = Size-1; i > index+1; i--) previous = previous->pPrev; 
			Node* toDelete = previous->pPrev;
			Node* toPrev = toDelete->pPrev;
			toPrev->pNext = previous;
			previous->pPrev = toPrev;
		    delete toDelete;
			Size--;
		}
		else {
			Node* previous;
			previous = this->head;
			for (int i = 0; i < index-1; i++) previous = previous->pNext;
			Node* toDelete = previous->pNext;
			Node* toNext = toDelete->pNext;
			previous->pNext = toNext;
			toNext -> pPrev = previous;
			delete toDelete;
			Size--;
		}
	}
}
int main(){
	setlocale(LC_ALL, "ru");
	List<int> lst;
	int l, b;
	cout << "Введите количество элементов которое хотите ввести" << endl;
	cin >> l;
	while (l < 1) {
		cout << "Колличество элементов не может быть < 1" << endl;
		cin >> l;
	}
	cout << "Заполните его" << endl;
	for (int i = 0; i < l; i++) {
		cin >> b;
		lst.push_back(b);
	}
	int pMax, pMin, iMax=0, iMin=0;
	pMax = pMin = lst[0];
	for (int i = 1; i < lst.GetSize(); i++) {
		if (pMax < lst[i]) {
			pMax = lst[i];
			iMax = i;
		}
		if (pMin > lst[i]) {
			pMin = lst[i];
			iMin = i;
		}
	}
	if (iMax > iMin) {
		lst.removeAt(iMax);
		lst.removeAt(iMin);
	}
	else if (iMax < iMin) {
		lst.removeAt(iMin);
		lst.removeAt(iMax);
	}
	else lst.removeAt(iMax);
	cout << "Новая последовательность" << endl;
	for(int i=0;i<lst.GetSize();i++)cout << lst[i] <<" ";
	cout << endl;
	return 0;
}