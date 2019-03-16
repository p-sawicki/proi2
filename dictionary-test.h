#ifndef DICTIONARY_TEST_H
#define DICTIONARY_TEST_H
#include <iostream>
#include <cassert>
#include "dictionary.cpp"
class DictionaryTest{
	public:
		void sizeAndCapacityTest();
		void customCapacityTest();
		void addExistingPairTest();
		void removeTest();
		void changeTest();
		void comparisonTest();
};
#endif
