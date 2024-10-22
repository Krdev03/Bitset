#include "Set.h"
#include <iostream>
void Set::copyFrom(const Set& other) {
	this->n = other.n;
	this->bucket_count = other.bucket_count;
	this->arr = new char[bucket_count] {'\0'};

	for (int i = 0; i < bucket_count; i++) {
		this->arr[i] = other.arr[i];
	}
}
void Set::moveFrom(Set&& other){
	this->n = other.n;
	this->bucket_count = other.bucket_count;
	this->arr = other.arr;

	other.n = 0;
	other.bucket_count = 0;
	other.arr = nullptr;
}
void Set::free() {
	this->n = 0;
	this->bucket_count = 0;
	delete[] arr;
	arr = nullptr;
}
void Set::setArray(int n) {
	bucket_count = n  / elements_in_bucket + 1;
	arr = new char[bucket_count] {'\0'};
}
void Set::setN(int n) {
	this->n = n;
}
Set::Set(int n) {
	if (n < 0)
		throw std::invalid_argument("Collection supports only positive numbers");

	setN(n);
	setArray(n);
}
Set::~Set() {
	delete[] arr;
	arr = nullptr;
	bucket_count = 0;
}
Set::Set(const Set& other) {
	copyFrom(other);
}
Set::Set(Set&& other) noexcept{
	moveFrom(std::move(other));
}
Set& Set::operator=(const Set& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}
Set& Set::operator=(Set&& other) noexcept{
	if (this != &other) {
		moveFrom(std::move(other));
	}
	return *this;
}
int Set::getBucketIndex(int x) const{
	return x / elements_in_bucket;
}
int Set::getPosInBucket(int x) const{
	return x % elements_in_bucket;
}
void Set::bitFlip(int x) {
	arr[getBucketIndex(x)] ^= (1 << getPosInBucket(x));
}
bool Set::isInSet(int x) const {
	return x >= 0 && x <= n && ((arr[getBucketIndex(x)] >> getPosInBucket(x)) & 1);
}
bool Set::isEmpty() const {
	const char s[1] = { '\0' };

	for (int i = 0; i < bucket_count; i++) {
		const char* bucket = &arr[i];
		
		if (strcmp(bucket, s) != 0) {
			return false;
		}
	}
	return true;
}
void Set::add(int x) {
	if(x >= 0 && x <= n && !isInSet(x))
		bitFlip(x);
}
void Set::remove(int x) {
	if (x >= 0 && x <= n && isInSet(x))
		bitFlip(x);
}
void Set::print() const{
	int num = 0;
	for (int i = 0; i < bucket_count; i++) {
		for (int j = 0; j < elements_in_bucket; j++) {
			if ((arr[i] >> j) & 1) {
				std::cout << num << ' ';
			}
			num++;
		}
	}
}
Set intersection(const Set& x,const Set& y) {
	int res_n = x.n <= y.n ? x.n : y.n;
	Set result(res_n);
	
	for (int i = 0; i < result.bucket_count; i++) {
		result.arr[i] = (x.arr[i] & y.arr[i]);
	}

	return result;
}
Set Union(const Set& x, const Set& y) {
	int res_n = x.n <= y.n ? y.n : x.n;
	Set result(res_n);

	for (int i = 0; i < result.bucket_count; i++) {
		if (i < x.bucket_count && i < y.bucket_count) {
			result.arr[i] = (x.arr[i] | y.arr[i]);
		}
		else if (i >= y.bucket_count) {
			result.arr[i] |= x.arr[i];
		}
		else {
			result.arr[i] |= y.arr[i];
		}	
	}

	return result;
}
Set complement(const Set& x) {
	Set result(x.n);

	for (int i = 0; i < x.bucket_count; i++) {
		result.arr[i] = ~ x.arr[i];
	}

	return result;
}
Set sym_difference(const Set& x, const Set& y) {
	int res_n = x.n <= y.n ? y.n : x.n;
	Set result(res_n);

	for (int i = 0; i < result.bucket_count; i++) {
		if (i < x.bucket_count && i < y.bucket_count) {
			result.arr[i] = (x.arr[i] ^ y.arr[i]);
		}
		else if (i >= y.bucket_count) {
			result.arr[i] ^= x.arr[i];
		}
		else {
			result.arr[i] ^= y.arr[i];
		}
	}
	return result;
}
Set difference(const Set& x, const Set& y) {
	return intersection(sym_difference(x, y), x);
}
bool Set::isSubset(const Set& y) const{
	return difference(*this, y).isEmpty();
}
bool operator==(const Set& x, const Set& y) {
	return x.isSubset(y) && y.isSubset(x);
} // Checks is the two sets are equivalent
bool operator!=(const Set& x, const Set& y) {
	return !(x == y);
} // Checks if the two sets are not equivalent
std::ostream& operator<<(std::ostream& os, const Set& x) {
	x.print();
	return os;
};