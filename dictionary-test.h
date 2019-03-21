/*Author: Piotr Sawicki*/
#ifndef DICTIONARY_TEST_H
#define DICTIONARY_TEST_H
#include <iostream>
#include <cassert>
#include <string>
#include <limits.h>
#include "dictionary.h"
#include "vector.h"
class DictionaryTest{
	private:
		template<class TKey, class TValue>
		inline void messageSize(Dictionary<TKey, TValue>& dict, const char* message){
			std::cout << message << "size: " << dict.getSize() << std::endl;
		}
		template<class TKey, class TValue>
		inline void printSize(Dictionary<TKey, TValue>& dict, const char* message){
			std::cout << message << dict;
			messageSize(dict, "");
		}
	public:
		void sizeAndCapacityTest();
		void sizeAndCapacityTest2();
		void customCapacityTest();
		void customCapacityTest2();
		void addExistingPairTest();
		void addExistingPairTest2();
		void removeTest();
		void removeTest2();
		void changeTest();
		void changeTest2();
		void comparisonTest();
		void comparisonTest2();
		void sortTest();
		void emptyTest();
};
#endif
