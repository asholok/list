#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <iostream> 
#include <stdlib.h>

#include "MemoryError.h"
#include "SegFault.h"

template <class Type>
class ArrayList {
	private:
		Type* array;
		size_t volume;
		size_t quantity;
		
	public:
		ArrayList();
		ArrayList(size_t quantity, const Type& value = '0');
		ArrayList(const ArrayList& list);
		~ArrayList();
		Type* getArr() const;
		size_t size() const;
		size_t capacity() const;
		void push_back(const Type& value);
		void pop_back();
		void copy(const ArrayList& list);
		Type* begin();
		Type* end();
		bool empty();
		Type& at(size_t index);
		void operator=(const ArrayList& list);
		Type& operator[](size_t index);
		Type& back();
		void assign(Type* begin, Type* last);
		void assign(size_t index, const Type& value = 0);
		const Type* cbegin() const;
		const Type* cend() const;
		void clear();
		Type* data();
		Type& front();
		void resize (size_t n, const Type& val = 0);
		void shrink_to_fit();
		void erase(Type* first, Type* last = NULL);
		Type* insert(Type* start, Type* begin, Type* last);
		
		
		void check(size_t len = 0);
		

};


#endif // ARRAYLIST_H