#pragma once
#include <fstream>
class Set{
public:
	Set(int n);
	Set(const Set& other);
	Set(Set&& other) noexcept;
	Set& operator=(const Set& other);
	Set& operator=(Set&& other) noexcept;
	~Set();

	void add(int x);
	void remove(int x);
	bool isEmpty() const;
	bool isInSet(int x) const;
	bool isSubset(const Set& y) const;

	friend Set intersection(const Set& x, const Set& y);
	friend Set Union(const Set& x, const Set& y);
	friend Set difference(const Set& x, const Set& y);
	friend Set complement(const Set& x);
	friend Set sym_difference(const Set& x, const Set& y);
	friend bool operator==(const Set& x, const Set& y);
	friend bool operator!=(const Set& x, const Set& y);
	friend std::ostream& operator<<(std::ostream& os,const Set& x);

private:
	int n = 0;
	char* arr = nullptr; 
	int bucket_count = 0;
	const int elements_in_bucket = sizeof(char) * 8;

	void copyFrom(const Set& other);
	void moveFrom(Set&& other);
	void free();
	void setArray(int n);
	void setN(int n);
	void print() const;

	int getBucketIndex(int x) const;
	int getPosInBucket(int x) const;
	void bitFlip(int x);
	
	
	
};

