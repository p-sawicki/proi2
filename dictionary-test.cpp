#include "dictionary-test.h"
void DictionaryTest::sizeAndCapacityTest(){
	std::cout << "Testing size and capacity reporting for key: int, value: double\n";
	Dictionary<int, double> dict;
	std::cout << "After instantiation: size: " << dict.getSize() << ", capacity: " << dict.getCapacity() << std::endl;	
	for(int i = 0; i < 20; ++i)
		dict.add(i + 1, (i + 1) * 3.14);
	assert(dict.getSize() == 20);
	assert(dict.getCapacity() == 32);
	std::cout << "After adding 20 elements: size: " << dict.getSize() << ", capacity: " << dict.getCapacity() << std::endl;
}
void DictionaryTest::customCapacityTest(){
	std::cout << "Testing custom capacity expansion for key: int, value: double\n";
	Dictionary<int, double> dict(10);
	std::cout << "After instantiation: size: " << dict.getSize() << ", capacity: " << dict.getCapacity() << std::endl;
	for(int i = 0; i < 30; ++i)
		dict.add(i, i * 1.11);
	assert(dict.getSize() == 30);
	assert(dict.getCapacity() == 40);
	std::cout << "After adding 30 elements: size: " << dict.getSize() << ", capacity: " << dict.getCapacity() << std::endl;
}
void DictionaryTest::addExistingPairTest(){
	std::cout << "Testing behavior when trying to add a pair already in the dictionary.\n";
	Dictionary<int, double> dict;
	for(int i = 0; i < 3; ++i)
		dict.add(i + 1, (i + 1) * 6.28);
	std::cout << "Before: \n" << dict;
	std::cout << "size: " << dict.getSize() << std::endl << "Adding key: 1 and value: 6.28\n";
	dict.add(1, 6.28);
	assert(dict.getSize() == 3);
	std::cout << "After: \n" << dict;
	std::cout << "size: " << dict.getSize() << std::endl;
}
void DictionaryTest::removeTest(){
	std::cout << "Testing removal\n";
	Dictionary<long long, char> dict;
	for(char i = 'a'; i < 'd'; ++i)
		dict.add(i, i);
	std::cout << "Before: \n" << dict;
	std::cout << "size: " << dict.getSize() << std::endl << "Removing key: " << (long long)'a' << " and value: 'a'\n";
	dict.remove((long long)'a', 'a');
	assert(dict.getSize() == 2);
	std::cout << "After: \n" << dict;
	std::cout << "size: " << dict.getSize() << "\nremoving the same key/value\n";
	dict.remove((long long)'a', 'a');
	assert(dict.getSize() == 2);
}
void DictionaryTest::changeTest(){
	std::cout << "Testing changing\n";
	Dictionary<int, double> dict;
	for(int i = 0; i < 3; ++i)
		dict.add(i + 1, (i + 1) * (i + 2));
	std::cout << "Before: \n" << dict;
	std::cout << "Changing first element to 3.14.\n";
	dict.change(1, 3.14);
	std::cout << "After: \n" << dict;
	std::cout << "Trying element with key 4\n";
	bool f = dict.change(4, 3.14);
	assert(!f);
	std::cout << "Confirming change happened\n";
	double confirm = 0;
	bool b = dict.find(1, confirm);
	assert(confirm == 3.14);
	assert(b);
	std::cout << "Test successful\n";
}
void DictionaryTest::comparisonTest(){
	std::cout << "Testing comparison\n";
	Dictionary<int, double> dict1, dict2;
	for(int i = 0; i < 3; ++i){
		dict1.add(i, i);
		dict2.add(i, i);
	}
	assert(dict1 == dict2);
	std::cout << "Equal dictionaries: " << std::boolalpha << (dict1 == dict2) << std::endl;
	dict2.change(0, 3.14);
	assert(!(dict1 == dict2));
	std::cout << "Different dictionaries: " << (dict1 == dict2) << std::endl;
	Dictionary<int, double> dict3;
	assert(!(dict3 == dict1));
	std::cout << "Different sizes: " << (dict3 == dict1) << std::endl;
}
