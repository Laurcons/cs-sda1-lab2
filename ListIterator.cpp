#include "ListIterator.h"
#include "IteratedList.h"
#include <exception>

// O(1)
ListIterator::ListIterator(const IteratedList& list) : list(list) {
	first();
}

// O(1)
void ListIterator::first() {
	current = list._head;
}

// O(1)
void ListIterator::next() {
	if (!valid())
		throw std::exception("DON'T DO THAT");
	current = current->next;
}

// O(1)
bool ListIterator::valid() const {
	return current != nullptr;
}

// O(1)
TElem ListIterator::getCurrent() const {
	if (!valid())
		throw std::exception("DON'T DO THAT");
	return current->info;
}



