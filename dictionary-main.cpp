#include "dictionary-test.h"
int main(){
	DictionaryTest test;
	test.sizeAndCapacityTest();
	test.customCapacityTest();
	test.addExistingPairTest();
	test.removeTest();
	test.changeTest();
	test.comparisonTest();
	std::cout << std::endl;
	test.sizeAndCapacityTest2();
	test.customCapacityTest2();
	test.addExistingPairTest2();
	test.removeTest2();
	test.changeTest2();
	test.comparisonTest2();
	std::cout << std::endl;
	test.sortTest();
}
