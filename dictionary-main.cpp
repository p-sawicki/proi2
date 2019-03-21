/*Author: Piotr Sawicki*/
#include "dictionary-test.h"
int main(){
	DictionaryTest test;
	test.sizeAndCapacityTest();
	test.addExistingPairTest();
	test.removeTest();
	test.changeTest();
	test.comparisonTest();
	std::cout << std::endl;
	test.sizeAndCapacityTest2();
	test.addExistingPairTest2();
	test.removeTest2();
	test.changeTest2();
	test.comparisonTest2();
	test.emptyTest();
	std::cout << std::endl;
	test.sortTest();
}
