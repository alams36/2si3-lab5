#ifndef HASHTABLEQUAD_H_
#define HASHTABLEQUAD_H_
//SHAKIR ALAM 400397108
#include <vector>

class HashTableQuad
{
private:
	// must contain this private field
	std::vector<int> table;
	// define other private fields to store:
	// 1. the size of the table
	// 2. the number of keys stored in the table
	// 3. the maximum load factor allowed
	int size;
	int numKeys;
	float maxLoadFactor;
public:
	// required constructor
	HashTableQuad(int maxNum, double load);
	//added constructor
	HashTableQuad(int size, double load, bool p);
	// required methods
	void insert(int n);
	bool isIn(int n);
	void printKeys();
	void printKeysAndIndexes();
	int getNumKeys();
	int getTableSize();
	double getMaxLoadFactor();
	static std::vector<double> simProbeSuccess();
	//added method
	int probeInsert(int n);

	// used for testing
	std::vector<int> getTable() {
		return table;
	};

private:
	// required methods
	void rehash();
};

#endif /* HASHTABLEQUAD_H_ */
