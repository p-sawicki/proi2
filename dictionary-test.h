#ifndef DICTIONARY_TEST_H
#define DICTIONARY_TEST_H
#include <iostream>
#include <cassert>
#include <string>
#include <limits.h>
#include "dictionary.cpp"
#include "vector.h"
class DictionaryTest{
	private:
		template<class TKey, class TValue>
		inline void messageSizeCapacity(Dictionary<TKey, TValue>& dict, const char* message){
			std::cout << message << "size: " << dict.getSize() << ", capacity: " << dict.getCapacity() << std::endl;
		}
		template<class TKey, class TValue>
		inline void printSizeCapacity(Dictionary<TKey, TValue>& dict, const char* message){
			std::cout << message << dict;
			messageSizeCapacity(dict, "");
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
};
#endif
