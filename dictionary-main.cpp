#include "dictionary-test.h"
int main(){
	DictionaryTest test;
	test.sizeAndCapacityTest();
	test.customCapacityTest();
	test.addExistingPairTest();
	test.removeTest();
	test.changeTest();
	test.comparisonTest();
}
