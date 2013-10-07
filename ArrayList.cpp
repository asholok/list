#include "ArrayList.h"


#define ARRAYMIN 10
#define INCREASE 1.2
#define DECREASE 0.6


template <class Type>
ArrayList<Type>::ArrayList() {
	Type* newData;

	newData = (Type*) malloc(ARRAYMIN*sizeof(Type));	 
	if ( newData == NULL ) {
		throw MemoryError();
	}
	this->volume = ARRAYMIN;
	this->array = newData;
	this->quantity = 0;
}

template <class Type>
ArrayList<Type>::ArrayList(size_t quantity, const Type& value) {
	size_t size = quantity;
	Type* newData;
	
	if ( quantity < ARRAYMIN ) {
		size = ARRAYMIN;
	}
	newData = (Type*) malloc(size*sizeof(Type));
	if ( newData == NULL ) {
		throw MemoryError();
	}
	
	this->volume = size;
	this->quantity = quantity;
	for ( int i = 0; i < quantity; i++ ) {
		array[i] = value;
	}
}
template <class Type>
ArrayList<Type>::ArrayList(const ArrayList& list) {
	copy(list);
}

template <class Type>
ArrayList<Type>::~ArrayList() {
	free(array);
}

template <class Type>
Type* ArrayList<Type>::getArr() const {
	return this->array;
}

template <class Type>
size_t ArrayList<Type>::size() const {
	return this->quantity;
}

template <class Type>
size_t ArrayList<Type>::capacity() const {
	return this->volume;
}

template <class Type>
void ArrayList<Type>::push_back(const Type& value) {
	check(1);
	this->array[this->quantity] = value;
	this->quantity += 1;
}

template <class Type>
void ArrayList<Type>::pop_back() {
	if ( quantity == 0 ) {
		throw SegFault();
	}
	this->quantity -= 1;
	check();
}

template <class Type>
void ArrayList<Type>::copy(const ArrayList& list) {
	Type* newData;
	
	newData = (Type*) malloc(list.volume*sizeof(Type));
	if ( newData == NULL ) {
		throw MemoryError();
	}
	this->quantity = list.quantity;
	this->volume = list.volume;
	this->array = newData;
	for ( int i = 0; i < this->quantity; i++ ) {
		this->array[i] = list.array[i];
	}
}

template <class Type>
Type* ArrayList<Type>::begin() {
	return this->array;
}

template <class Type>	
Type* ArrayList<Type>::end() {
	return &array[quantity];
}

template <class Type>
bool ArrayList<Type>::empty() {
	if ( quantity == 0 ) {
		return true;
	}
	return false;
}

template <class Type>
Type& ArrayList<Type>::at(size_t index) {
	return array[index];
}

template <class Type>
void ArrayList<Type>::operator=(const ArrayList& list) {
	copy(list);
}

template <class Type>
Type& ArrayList<Type>::operator[](size_t index) {
	return array[index];
}

template <class Type>
Type& ArrayList<Type>::back() {
	return array[quantity-1];
}

template <class Type>
void ArrayList<Type>::assign(Type* begin, Type* last) {
	size_t size = last - begin;
	Type* i = begin;
	size_t k = 0;

	this->quantity = size;
	check();
	for ( ; i < last; i++, k++) {
		this->array[k] = *i;
	}
}

template <class Type>
void ArrayList<Type>::assign(size_t index, const Type& value) {
	this->quantity = index;
	check();
	for ( size_t i = 0 ; i < index; i++ ) {
		this->array[i] = value;
	}
}

template <class Type>
const Type* ArrayList<Type>::cbegin() const {
	return this->array;
}

template <class Type>
const Type* ArrayList<Type>::cend() const {
	return &array[quantity];
}

template <class Type>
void ArrayList<Type>::clear() {
	this->quantity = 0;
	check();
}

template <class Type>
Type* ArrayList<Type>::data() {
	return this->array;
}

template <class Type>
Type& ArrayList<Type>::front() {
	return array[0];
}

template <class Type>
void ArrayList<Type>::resize(size_t n, const Type& val) {
	size_t buff = this->quantity;
	
	this->quantity = n;
	for ( size_t i = buff; i < n; i++ ) {
		this->array[i] = val;
	}
}

template <class Type>
void ArrayList<Type>::shrink_to_fit() {
	this->volume = this->quantity;
	this->array = (Type*)realloc(this->array, this->volume*sizeof(Type));
}

template <class Type>
void ArrayList<Type>::erase(Type* first, Type* last) {
	size_t shift = 1;
	Type* j = last;
	
	if ( first > end() || last > end() ) {
		throw SegFault();
	}
	if ( last != NULL ) {
		shift = last - first;
	}
	
	for ( Type* i = first; j < end() ; i++, j++ ) {
		*i = *j;
	}
	
	this->quantity -= shift;
	check();
}

template <class Type>
Type* ArrayList<Type>::insert(Type* start, Type* begin, Type* last) {
	size_t stap = last - begin;
	size_t k = stap;
	Type* j = start;
	
	if ( start > end() ) {
		throw SegFault();
	}
	check(stap);
	
	
	for ( Type* i = end(); k > 0; k--, i ++, j++, begin++ ) {
		*i = *j;
		*j = *begin;
	}
	this->quantity += stap;
}


template <class Type>	
void ArrayList<Type>::check(size_t len) {
	size_t newLen = this->quantity + len;
	double factor = (double)newLen / (double)this->volume;
	if ( factor == 0 ) {
		this->volume = ARRAYMIN;
		this->array = (Type*)realloc(this->array, this->volume*sizeof(Type));
	}
	if ( factor > 0.95 ) {
		Type* newData;
	
		newLen *= INCREASE;
		
		newData = (Type*)realloc(this->array, newLen*sizeof(Type));
		 
		if ( newData == NULL ) {
			throw MemoryError();
		}
		 
		this->volume = newLen;
		this->array = newData;
	}
	if ( factor < 0.5 && this->volume > ARRAYMIN ) {
		this->volume *= DECREASE;
		this->array = (Type*)realloc(this->array, this->volume*sizeof(Type));
	}
}

template class ArrayList<size_t>;
template class ArrayList<double>;
template class ArrayList<int>;
template class ArrayList<char>;