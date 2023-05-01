#ifndef HASHTABLELIN_H_
#define HASHTABLELIN_H_
//SHAKIR ALAM 400397108
#include <vector>

class HashTableLin
{
private:
	//must contain this private field
	std::vector<int> table;
	// define other private fields to store:
	// 1. the size of the table
	// 2. the number of keys stored in the table
	// 3. the maximum load factor allowed
	int size;
	int numKeys;
	float maxLoadFactor;

public:
	//required constructor
	HashTableLin(int maxNum, double load);
	//added constructor
	HashTableLin(int size, double load, bool p);
	//required methods
	void insert(int n);
	bool isIn(int n);
	void printKeys();
	void printKeysAndIndexes();
	int getNumKeys();
	int getTableSize();
	double getMaxLoadFactor();
	static std::vector<double> simProbeSuccess();
	static std::vector<double> simProbeUnsuccess(); // for bonus
	//added methods
	int probeInsert(int n);
	int indexFail(int n);
	//used for testing
	std::vector<int> getTable() {
		return table;
	};

private:
	//required methods
	void rehash();
};

#endif /* HASHTABLELIN_H_ */