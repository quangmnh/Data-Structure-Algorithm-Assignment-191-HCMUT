/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dsaLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#ifndef DSA191_A1_DSALIB_H
#define DSA191_A1_DSALIB_H
#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>


using namespace std;

class DSAException {
    int     _error;
    string  _text;
public:

    DSAException() : _error(0), _text("Success") {}
    DSAException(int err) : _error(err), _text("Unknown Error") {}
    DSAException(int err, const char* text) : _error(err), _text(text) {}

    int getError() { return _error; }
    string& getErrorText() { return _text; }
};

template <class T>
struct L1Item {
    T data;
    L1Item<T> *pNext;
    L1Item() : pNext(NULL) {}
    L1Item(T &a) : data(a), pNext(NULL) {}
};

template <class T>
class L1List {
    L1Item<T>   *_pHead;// The head pointer of linked list
    size_t      _size;// number of elements in this list
public:
    L1List() : _pHead(NULL), _size(0) {}
	~L1List() ;

    void    clean();
    bool    isEmpty() {
        return _pHead == NULL;
    }
    size_t  getSize() {
        return _size;
    }

    T&      at(int i);// give the reference to the element i-th in the list
    //T&      operator[](int i);// give the reference to the element i-th in the list

  //  bool    find(T& a, int& idx);// find an element similar to a in the list. Set the found index to idx, set idx to -1 if failed. Return true if success.
	//int     findCityID(string s);
	int     insert(int i, L1Item<T>* p);// insert an element into the list at location i. Return 0 if success, -1 otherwise
    int     remove(int i);// remove an element at position i in the list. Return 0 if success, -1 otherwise.

    int     push_back(L1Item<T>* p);// insert to the end of the list
    int     insertHead(L1Item<T>* p);// insert to the beginning of the list

    int     removeHead();// remove the beginning element of the list
    int     removeLast();// remove the last element of the list
	L1Item<T>* head();
    //void    reverse();
	/*
    void    traverse(void (*op)(T&)) {
        // TODO: Your code goes here

    }
    void    traverse(void (*op)(T&, void*), void* pParam) {
        // TODO: Your code goes here
    }
	*/
};

/// Insert item to the end of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::push_back(L1Item<T>* p) {
    // TODO: Your code goes here
	if (this->_size == 0) this->insertHead(p);
	else {
		L1Item<T>* b = this->_pHead;
		while (b->pNext) b = b->pNext;
		b->pNext = p;
		//b->pNext->pNext = NULL;
		this->_size++;
	}
    return 0;
}

/// Insert item to the front of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::insertHead(L1Item<T>* p) {
    // TODO: Your code goes here
	if (p == NULL) return -1;
	if (this->_pHead!=NULL) {
		p->pNext = this->_pHead->pNext;
		this->_pHead = p;
	}
	else {
		this->_pHead = p;
		//this->_pHead->pNext = NULL;
	}
	
	this->_size++;
    return 0;
}

/// Remove the first item of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::removeHead() {
    // TODO: Your code goes here
	if (this->getSize() ==0) return -1;
	else {
		L1Item<T>* b = this->_pHead;
		this->_pHead = this->_pHead->pNext;
		this->_size--;
		return 0;
	}
}

/// Remove the last item of the list
/// Return 0 if success, -1 otherwise
template <class T>
int L1List<T>::removeLast() {
    // TODO: Your code goes here
	if (this->_size == 0) return -1;
	else {
		L1Item<T>* a = this->_pHead;
		L1Item<T>* b = this->_pHead;
		while (b->pNext) {
			a = b;
			b = b->pNext;
		}
		a->pNext = NULL;
		delete b;
		this->_size--;
		return 0;
	}
}
/*
template <class T>
bool L1List<T>::find(T& a, int& idx) {
	L1Item<T>* b = this->_pHead;
	int i = 0;
	while (b->pNext) {
		if (b->data == a) {
			idx = i;
			return true;
		}
		i++;
		b = b->pNext;
	}
	idx = -1;
	return false;
}
*/
// insert an element into the list at location i. Return 0 if success, -1 otherwise

template <class T>
int L1List<T>::insert(int i, L1Item<T>* p) {
	if (i == 0) {
		this->insertHead(p);
		return 0;
	}
	else if (i == this->getSize()) {
		this->push_back(p);
		return 0;
	}
	else if (i > this->getSize() || i < 0) return -1;
	else {
		int order = 0;
		L1Item<T>* b = this->_pHead;
		while (b->pNext) {
			if (order == i-1) {
				p->pNext = b->pNext;
				b->pNext = p;
				this->_size++;
				return 0;
			}
			order++;
			b = b->pNext;
		}
	}
	return -1;
}

// remove an element at position i in the list. Return 0 if success, -1 otherwise.
template <class T>
int L1List<T>::remove(int i) {
	if (this->_pHead == NULL) return -1;
	else if (i == 0) return this->removeHead();
	else if (i == this->getSize() - 1) return this->removeLast();
	else if (i >= this->getSize() || i < 0) return -1;
	else {
		int order = 0;
		L1Item<T>* c = NULL;
		L1Item<T>* b = this->_pHead;
		while (b) {
			if (order == i) {
				c->pNext=b->pNext;
				delete b;
				b = NULL;
				this->_size--;
				return 0;
			}
			order++;
			c = b;
			b = b->pNext;
		}
		return -1;
	}
}/*
template <class T>
void L1List<T>::reverse() {
	L1Item<T>* pre = NULL;
	L1Item<T>* nex = NULL;
	L1Item<T>* cur = this->head;
	while (cur != NULL) {
		nex = cur->nex;
		cur->nex = pre;
		pre = cur;
		cur = nex;
	}
	this->head = pre;
}
*/
// give the reference to the element i-th in the list
template <class T>
T& L1List<T>::at(int i) {
	int order = 0;
	L1Item<T>* b = this->_pHead;
	while (b->pNext) {
		if (order == i) return b->data;
		b = b->pNext;
		order++;
	}
}
/*
// give the reference to the element i-th in the list
template <class T>
T& L1List<T>::operator[](int i) {
	int order = 0;
	L1Item<T>* b = this->_pHead;
	while (b->pNext) {
		if (order == i) return b->data;
		order++;
	}
}

template <class T>
void L1List<T>::clean() {
	L1Item<T>* b = this->_pHead;
	while (b) {
		this->removeHead();
		b = this->_pHead;
	}
}
*/
template <class T>
L1Item<T>* L1List<T>::head() {
	return this->_pHead;
}
#endif //DSA191_A1_DSALIB_H
