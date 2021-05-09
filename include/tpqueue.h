// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <cassert>

struct SYM {
public:
	SYM* pNext;
	char data;
	int prior;

	SYM(char data, int prior, SYM* pNext = nullptr) {
		this->data = data;
		this->prior = prior;
		this->pNext = pNext;
	}
};

template<typename T>
class TPQueue {
public:
	TPQueue();
	~TPQueue();

	char pop_front();
	void push_back(SYM item);
	void push_front(SYM item);
	void push(SYM item);
	int GetSize() { return Size; };
private:
	int Size;
	SYM *head;
};

template<typename T>
TPQueue<T>::TPQueue() {
	Size = 0;
	head = nullptr;
}

template<typename T>
TPQueue<T>::~TPQueue() {
}

template<typename T>
char TPQueue<T>::pop_front() {
	SYM *temp = head;
	head = head->pNext;
	char data = temp->data;
	delete temp;
	Size--;
	return data;
}

template<typename T>
void TPQueue<T>::push_back(SYM item) {
	if (head == nullptr) {
		head = new SYM(item);
	} else {
		SYM* current = this->head;
		while (current->pNext != nullptr) {
			current = current->pNext;
		}
		current->pNext = new SYM(item);
	}
	Size++;
}

template<typename T>
void TPQueue<T>::push_front(SYM item) {
	head = new SYM(item);
	Size++;
}

template<typename T>
void TPQueue<T>::push(SYM item) {
	if (head == nullptr) {
		//push front
		head = new SYM(item.data, item.prior, head);
		Size++;
	} else {
		SYM* current = this->head;
		//Если входящий элемент имеет высокий приоритет
		if (current->prior < item.prior) {
			//push front
			head = new SYM(item.data, item.prior, head);
			Size++;
			return;
		}
		//Проход по списку в поисках того самого элемента
		while (current->pNext != nullptr) {
			if (current->pNext->prior > item.prior) {
				current = current->pNext;
			} else {
				break;
			}
		}
		SYM* newNode = new SYM(item.data, item.prior, current->pNext);
		current->pNext = newNode;
		Size++;
	}
}


#endif // INCLUDE_TPQUEUE_H_
