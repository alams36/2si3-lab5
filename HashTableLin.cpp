#include "HashTableLin.h"
#include <iostream>
#include <cmath>
using namespace std;

//SHAKIR ALAM 400397108

HashTableLin::HashTableLin(int maxNum, double load)
{
	//T(n) = Theta(n^2)
	//S(n) = Theta(n)
	//set table size, number of keys stored and maximum load factor
	size = std::ceil(maxNum / load);
	numKeys = 0 ;
	maxLoadFactor = load;
	//bool p stores prime
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
			for (int candidate = 3; candidate * candidate <= size && primeNum;candidate += 2) {
				//if size divisble by odd num, increment 1
				if (0 == size % candidate) {
					primeNum = false;
					size++;
					candidate = 1;
				}//start again from i=3
			}
		}
	} //fill table with zeroes upon prime
	table.resize(size, 0);
}
HashTableLin::HashTableLin(int sizeNew, double load, bool p)
{
	//T(n) = Theta(n^2)
	//S(n) = Theta(n)
	size = sizeNew; //size is now a provided parameter
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
				if (0==size % candidate) {
					primeNum = false;
					size++;
					candidate = 1;
				}//start again from i=3
			}
		}
	} //fill table with zeroes upon prime
	table.resize(size, 0);
}
void HashTableLin::insert(int n)
{
	//T(n) = Theta(n^2)
	//S(n) = Theta(n)
	//return if element is already present
	if (isIn(n)) {
		return;
	}
	//increment number of keys
	numKeys ++;
	//calculate the index of the element
	int index = n % size;
	//linear probing to find an empty slot
	int i = 0;
	while (table[index] != 0) {
		i++;
		index = (index + 1) % size;
		//if probed more than half the table size,
		//then rehash and try again
		if (i >= size /2) {
			rehash();
			insert(n);
			return;
		}
	} //insert the element at the found index
	table[index] = n;
	//check need to rehash
	if (numKeys > maxLoadFactor * size) {
		rehash();
	}
}
void HashTableLin::rehash()
{
	//T(n) = Theta(n)
	//S(n) = Theta(n)
	//double hash table size
	int sizeNew = size * 2;
	//create new hash table with new size and max load factor
	HashTableLin newTable(sizeNew, maxLoadFactor, true);
	//copy all non-zeroes from old to new table
	for (int x : table) {
		if (x != 0) {
			newTable.insert(x);
		}
	}
	//update current table with new table
	table = newTable.table;
	//update current size and numKeys
	size = newTable.size;
	numKeys = newTable.numKeys;
}

bool HashTableLin::isIn(int n)
{
	//T(n) = Theta(n)
	//S(n) = Theta(n)
	//find n's index
	int i = n%size;
	int originalIndex = i;
	//loop until an empty cell is found or the number is found
	while (0 != table[i]) {
		if (n == table[i]) {
			return true;
		}
		i = (1+ i) % size;
		if (i == originalIndex) {
			break;
		}
	}
	//not found
	return false;
}
void HashTableLin::printKeys()
{
	//T(n) = Theta(n)
	//S(n) = Theta(1)
	//traverse table and print non-zeroes
	for (int element:table) {
		if (element != 0) {
			cout << element << std::endl;
		}
	}
}
void HashTableLin::printKeysAndIndexes()
{
	//T(n) = Theta(n)
	//S(n) = Theta(1)
	//traverse table and print non-zeroes and index
	int index = 0;
	for (int& element : table) {
		if (element) {
			cout << index << ", " << element << std::endl;
		}
		index++;
	}
}//following functions just retrieve values
int HashTableLin::getNumKeys() {
	//T(n) = Theta(1)
	//S(n) = Theta(1)
	return numKeys;
}
int HashTableLin::getTableSize() {
	//T(n) = Theta(1)
	//S(n) = Theta(1)
	return size;
}
double HashTableLin::getMaxLoadFactor() { 
	//T(n) = Theta(1)
	//S(n) = Theta(1)
	return maxLoadFactor; 
}
int HashTableLin::probeInsert(int n)
{
	//T(n) = Theta(n)
	//S(n) = Theta(n)
	//if element exists return 0
	if (isIn(n)) {
		return 0;
	}
	int x = n %size;
	int probeCount = 1;
	//linear probing until empty slot found
	while (table[x] != 0) {
		probeCount++;
		x = (1 + x) % size;
		//if probed more than half the table size,
		//then rehash and try again
		if (probeCount >= size / 2) {
			rehash();
			return probeInsert(n);
		}
	}
	//insert the element at the found index
	table[x] = n;
	//increment number of keys
	numKeys++;
	//check need to rehash
	if (numKeys > maxLoadFactor * size) {
		rehash();
	}
	return probeCount;
}
std::vector<double> HashTableLin::simProbeSuccess()
{
	vector<double> ans; //declare vector to store ans
	const int numTests = 1000; //define the number of tests to be run for each load factor.
	//loop through different load factors from 0.1 to 1, incrementing by 0.1
	for (double loadFactor = 0.1; loadFactor < 1; loadFactor += 0.1) {
		double avg = 0; // Initialize the average number of probes for this load factor.
		//loop through number of tests specified
		for (int testNum = 0; testNum < 100; testNum++) {
			int totalProbeCount = 0; //initialize total number of probes for test
			//create new hash table with specified load factor
			HashTableLin table(numTests, loadFactor);
			//loop until hash table is filled with numTests
			while (table.numKeys < numTests) {
				//insert a random key and add num of probes to totalProbeCount
				totalProbeCount += table.probeInsert(rand());
			}
			//add avg num of probes for test to the total
			avg += double(totalProbeCount) / numTests;
		}
		//calculate and store avg num of probes for load factor
		ans.push_back(avg / 100);
	}
	return ans; //return vector containing ans
}

//bonus
std::vector<double> HashTableLin::simProbeUnsuccess()
{
	vector<double> ans; //declare vector to store ans
	const int numTests = 2500; //define the number of tests to be run for each load factor.
	//loop through different load factors from 0.1 to 1, incrementing by 0.1
	for (double loadFactor = 0.1; loadFactor < 1; loadFactor += 0.1) {
		double avgProbes = 0; //initialize the average number of probes for this load factor
		//run the experiment 100 times to calculate the average number of probes needed for this load factor
		for (int repetition = 0; repetition < 100; repetition++) {
			int numProbes = 0; //initialize the number of probes
			int numFailures = 0; //initialize the number of failed searches
			HashTableLin newTable(numTests, loadFactor); //create a new hash table with the current load factor
			//fill the hash table to its capacity
			while (newTable.numKeys != numTests) {
				newTable.probeInsert(rand()); //insert a random number into the hash table
			}
			//perform searches for keys that are not in the hash table and calculate the number of probes needed for each search
			while (numTests > numFailures) {
				int searchKey = rand(); //generate a random search key
				if (!newTable.isIn(searchKey)) { //if the search key is not in the hash table
					int probe = newTable.indexFail(searchKey); //calculate the number of probes needed to find the next available index
					numProbes += probe; //update the total number of probes
					numFailures++; //update the number of failed searches
				}
			}
			avgProbes += double(numProbes) / numTests; //update the average number of probes for this load factor
		}
		double avgNumProbes = avgProbes / 100; //calculate the average number of probes across all experiments
		ans.push_back(avgNumProbes); //store the average number of probes for this load factor in the ans vector
	}
	return ans; //return the ans vector
}

//helper function for indexing failures
int HashTableLin::indexFail(int n)
{
	int numProbes = 0; //initialize the number of probes
	int i = n % size; //calculate the initial index for the search key
	while (true) {
		if (table[i] == n) { //if the search key is found at the current index
			numProbes++; //update the number of probes
			break;
		}
		else if (table[i] == 0) { //if an empty slot is found at the current index
			numProbes++; //update the number of probes
			break;
		}
		else { //if the current slot is occupied by another key
			numProbes++; //update the number of probes
			i = (i + 1) % size; //move to the next slot
		}
	}
	return numProbes; //return the number of probes needed to find the next available index
}