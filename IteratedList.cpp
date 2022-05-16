
#include <exception>
#include "ListIterator.h"
#include "IteratedList.h"

// theta(1)
IteratedList::IteratedList() {
	_head = nullptr;
	_tail = nullptr;
	_size = 0;
}

// theta(1)
int IteratedList::size() const {
	return _size;
}

// theta(1)
bool IteratedList::isEmpty() const {
	return _size == 0;
}

// theta(1)
ListIterator IteratedList::first() const {
	return ListIterator(*this);
}

// theta(1)
TElem IteratedList::getElement(ListIterator pos) const {
	return pos.getCurrent();
}

// best theta(1)
// worst theta(n)
// total O(n)
TElem IteratedList::remove(ListIterator& pos) {
	// search for the element and redo the links
	if (!pos.valid())
		throw std::exception("DON'T DO THAT");
	_size--;
	auto prev = _head;
	if (prev == pos.current) {
		// remove head element
		Node* p = _head;
		TElem val = p->info;
		_head = _head->next;
		pos.current = _head;
		if (_head == nullptr)
			_tail = nullptr;
		delete p;
		return val;
	}
	// go to our element
	while (prev->next != pos.current)
		prev = prev->next;
	// prev is now the element just before our target
	// save pointer
	Node* p = prev->next;
	if (p == _tail)
		_tail = prev;
	// redo link
	prev->next = p->next;
	TElem val = p->info;
	delete p;
	return val;
}

// best theta(1)
// worst theta(n)
// total O(n)
ListIterator IteratedList::search(TElem e) const{
	auto it = ListIterator(*this);	
	while (it.valid() && it.getCurrent() != e)
		it.next();
	return it;
}

// theta(1)
TElem IteratedList::setElement(ListIterator pos, TElem e) {
	if (!pos.valid())
		throw std::exception("DON'T DO THAT");
	TElem old = pos.current->info;
	pos.current->info = e;
	return old;
}

// theta(1)
void IteratedList::addToBeginning(TElem e) {
	Node* p = new Node;
	p->info = e;
	p->next = _head;
	_head = p;
	if (_tail == nullptr)
		_tail = _head;
	_size++;
}

// theta(1)
void IteratedList::addToPosition(ListIterator& pos, TElem e) {
	if (!pos.valid())
		throw std::exception("DON'T DO THAT");
	// add an element _after_ pos
	// create the node
	Node* p = new Node;
	p->info = e;
	// link it
	p->next = pos.current->next;
	if (pos.current == _tail)
		_tail = p;
	pos.current->next = p;
	// reset iterator
	pos.current = p;
	_size++;
}

// theta(1)
void IteratedList::addToEnd(TElem e) {
	Node* p = new Node;
	p->info = e;
	p->next = nullptr;
	_size++;
	if (_tail == nullptr) {
		// is empty
		_head = p;
		_tail = p;
		return;
	}
	// add to end
	_tail->next = p;
	_tail = p;
}

// theta(n)
void IteratedList::filter(Condition cond) {
	auto it = first();
	// remove first elements that do NOT satisfy cond
	while (it.valid() && !cond(it.getCurrent())) {
		remove(it); // removing the first element is always theta(1)
	}
	if (!it.valid())
		// we removed everything
		return;
	// we are now sure that the first element does NOT satisfy cond
	while (it.current->next != nullptr) {
		if (!cond(it.current->next->info)) {
			// remove current->next
			auto p = it.current->next;
			it.current->next = p->next;
			delete p;
			_size--;
		}
		else it.next();
	}
}

// theta(n)
IteratedList::~IteratedList() {
	auto curr = _head;
	while (curr != nullptr) {
		Node* p = curr;
		curr = curr->next;
		delete p;
	}
}
