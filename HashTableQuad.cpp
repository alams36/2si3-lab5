#include "HashTableQuad.h"
#include <cmath>
#include <iostream>
using namespace std;

//SHAKIR ALAM 400397108

HashTableQuad::HashTableQuad(int maxNum, double load)
{
	//T(n) = Theta(n^2)
	//S(n) = Theta(n)
	//set table size, number of keys stored and maximum load factor
	size = std::ceil(maxNum /load);
	numKeys = 0 ;
	maxLoadFactor = load;
	//bool p stores prime
	bool primeNum = false;
	//check if table size greater than 3
	if (3 < size) {
		//while prime not found
		while (!primeNum) {
			//if even table size, increment 1
			if (0 == size % 2) {
				size ++; continue;
			}
			primeNum = true;
			//test if size is divisible by odd number >= 3
			for (int candidate = 3; candidate * candidate <= size && primeNum;candidate += 2) {
				//if size divisble by odd num, increment 1
				if (size % candidate == 0) {
					primeNum = false;
					size++;
					candidate = 1;
				}//start again from i=3
			}
		}
	} //fill table with zeroes upon prime
	table.resize(size, 0);
}
HashTableQuad::HashTableQuad(int sizeNew, double load, bool p)
{
	//T(n) = Theta(n^2)
	//S(n) = Theta(n)
	//size is now a provided parameter
	size = sizeNew;
	//set number of keys stored and maximum load factor
	numKeys = 0 ;
	maxLoadFactor = load;
	//bool primeNum stores prime
	bool primeNum = false;
	//check if table size greater than 3
	if (3 < size) {
		//while prime not found
		while (!primeNum) {
			//if even table size, increment 1
			if (0 == size %2) {
				size ++; continue;
			}
			primeNum = true;
			//test if size is divisible by odd number >= 3
			for (int candidate = 3; candidate * candidate <= size && primeNum; candidate += 2) {
				//if size divisble by odd num, increment 1
				if (size % candidate == 0) {
					primeNum = false;
					size++;
					candidate = 1;
				}//start again from i=3
			}
		}
	}//fill table with zeroes upon prime
	table.resize(size, 0);
}
void HashTableQuad::insert(int n)
{
	//T(n) = Theta(n^2)
	//S(n) = Theta(n)
	if (isIn(n)) {
		return;
	}
	numKeys++;
	int initialIndex = n % size;
	int currentIndex = initialIndex;
	int probingStep = 1;
	while (table[currentIndex] != 0) {
		currentIndex = (initialIndex + (probingStep * probingStep)) % size;
		probingStep++;
		if (probingStep > size) {
			numKeys--;
			return;
		}
	}
	table[currentIndex] = n;
	if (numKeys > maxLoadFactor * size) {
		rehash();
	}
}
void HashTableQuad::rehash()
{
	//T(n) = Theta(n)
	//S(n) = Theta(n)
	//double hash table size
	int sizeNew = size * 2;
	//create new hash table with new size and max load factor
	HashTableQuad newTable(sizeNew, maxLoadFactor, true);
	//copy all non-zeroes from old to new table
	for (int x : table) {
		if (x != 0) {
			newTable.insert(x);
		}
	}
	//update table with new table
	table = newTable.table;
	//update current size and numKeys
	size = newTable.size;
	numKeys = newTable.numKeys;
}
bool HashTableQuad::isIn(int n)
{
	//T(n) = Theta(n)
	//S(n) = Theta(n)
	//calculate hash for the integer
	int hash = n % size;

	//initialize offset variable to 1 and set index to hash
	int offset = 1;
	int index = hash;

	//check if the value at hash index is equal to the input value
	if (table[hash] == n) {
		return true;
	}
	//if value at hash index is not equal to input quadratic probing until an empty slot or the input found
	while (n != table[index] && 0 != table[index]) {
		index = (offset * offset + hash) % size;
		offset++;
		if (offset >= size) {
			return false;
		}
		//if the input value is found during quadratic probing, return true
		if (table[index] == n) {
			return true;
		}
	}

	// If the input value is not found during quadratic probing, return false
	return false;
}
void HashTableQuad::printKeys()
{
	//T(n) = Theta(n)
	//S(n) = Theta(n)
	//traverse table and print non-zeroes
	for (int element : table) {
		if (element != 0) {
			cout << element << std::endl;
		}
	}
}
void HashTableQuad::printKeysAndIndexes()
{
	//T(n) = Theta(n)
	//S(n) = Theta(n)
	//traverse table and print non-zeroes and index
	int index = 0;
	for (int& element : table) {
		if (element) {
			cout << index << ", " << element << std::endl;
		}
		index++;
	}
}
int HashTableQuad::getNumKeys() {
	//T(n) = Theta(1)
	//S(n) = Theta(1)
    return numKeys;
}//following functions just retrieve values
int HashTableQuad::getTableSize() {
	//T(n) = Theta(1)
	//S(n) = Theta(1)
    return size;
}
double HashTableQuad::getMaxLoadFactor() {
	//T(n) = Theta(1)
	//S(n) = Theta(1)
    return maxLoadFactor;
}
int HashTableQuad::probeInsert(int n)
{
	//T(n) = Theta(n)
	//S(n) = Theta(n)
	//if element exists return 0
	if (isIn(n)) {
		return 0;
	}
	int index = n % size;
	int probeCount = 1;
	//quadratic probing until empty slot found
	while (table[index] != 0) {
		index = (probeCount * probeCount+ index) % size;
		probeCount++;
		//if probed more than half the table size,
		//then rehash and try again
		if (probeCount >= size / 2) {
			rehash();
			return probeInsert(n);
		}
	}
	//insert the element at the found index
	table[index] = n;
	//increment number of keys
	numKeys++;
	//check need to rehash
	if (numKeys > maxLoadFactor * size) {
		rehash();
	}
	return probeCount;
}
std::vector<double> HashTableQuad::simProbeSuccess()
{
	vector<double> ans; //declare vector to store ans
	const int numTests = 1000; //define the number of tests to be run for each load factor.
	//loop through different load factors from 0.1 to 1, incrementing by 0.1
	for (double loadFactor = 0.1; loadFactor < 1; loadFactor += 0.1) {
		double avg = 0; // Initialize the average number of probes for this load factor.
		for (int testNum = 0; testNum < 100; testNum++) { //run 100 tests for each load factor
			int totalProbeCount = 0; //Initialize the total number of probes for each test
			HashTableQuad newTable(numTests, loadFactor); //create a new hash table with specified parameters
			while (newTable.numKeys < numTests) {
				totalProbeCount += newTable.probeInsert(rand()); //Insert random keys and get the total number of probes.
			}
			avg += double(totalProbeCount) /numTests; //update the average number of probes for each test
		}
		ans.push_back(avg / 100); //store the average number of probes for this load factor to ans vector
	}
	return ans;
}