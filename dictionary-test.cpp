#include "dictionary-test.h"
void DictionaryTest::sizeAndCapacityTest(){
	Dictionary<int, double> dict;
	messageSizeCapacity(dict, "Testing size and capacity reporting for key: int, value: double\nBefore: ");
	for(int i = 0; i < 20; ++i)
		dict.add(i + 1, (i + 1) * 3.14);
	assert(dict.getSize() == 20);
	assert(dict.getCapacity() == 32);
	messageSizeCapacity(dict, "After adding 20 elements: ");
	std::cout << std::endl;
}
void DictionaryTest::sizeAndCapacityTest2(){
	Dictionary<std::string, Vector> dict;
	messageSizeCapacity(dict, "Testing size and capacity reporting for key: string, value: vector\nBefore: ");
	Vector vect(2);
	vect.setNthValue(0, 5.55);
	vect.setNthValue(1, 6.66);
	for(int i = 0; i < 40; ++i)
		dict.add(std::string(i, 'a'), vect); 
	assert(dict.getSize() == 40);
	assert(dict.getCapacity() == 64);
	messageSizeCapacity(dict, "After adding 40 elements: ");
	std::cout << std::endl;
}
void DictionaryTest::customCapacityTest(){
	Dictionary<int, double> dict(10);
	messageSizeCapacity(dict, "Testing custom capacity expansion for key: int, value: double\nBefore: ");
	for(int i = 0; i < 30; ++i)
		dict.add(i, i * 1.11);
	assert(dict.getSize() == 30);
	assert(dict.getCapacity() == 40);
	messageSizeCapacity(dict, "After adding 30 elements: ");
	std::cout << std::endl;
}
void DictionaryTest::customCapacityTest2(){
	Dictionary<std::string, Vector> dict(3);
	messageSizeCapacity(dict, "Testing custom capacity expansion for key: string, value: vector\nBefore: ");
	Vector vect(3);
	for(int i = 0; i < 15; ++i){
		for(int j = 0; j < 3; ++j)
			vect.setNthValue(j, i + j);
		dict.add(std::string(15 - i, 'a'), vect);
	}
	assert(dict.getSize() == 15);
	assert(dict.getCapacity() == 24);
	messageSizeCapacity(dict, "After adding 15 elements: ");
	std::cout << std::endl;
}
void DictionaryTest::addExistingPairTest(){
	Dictionary<int, double> dict;
	for(int i = 0; i < 3; ++i)
		dict.add(i + 1, (i + 1) * 6.28);
	printSizeCapacity(dict, "Testing behavior when trying to add a key already in the dictionary. Before:\n");
	dict.add(1, 6.28);
	assert(dict.getSize() == 3);
	printSizeCapacity(dict, "After adding 1/6.28:\n");
	std::cout << std::endl;
}
void DictionaryTest::addExistingPairTest2(){
	Dictionary<std::string, Vector> dict;
	Vector vect(3), vect2(3);
	for(int i = 0; i < 3; ++i){
		for(int j = 0; j < 3; ++j)
			vect.setNthValue(j, i * j);
		dict.add(std::string(1, 'x' - i), vect);
	}
	printSizeCapacity(dict, "Testing behavior when trying to add a key already in the dictionary. Before:\n");
	dict.add(std::string(1, 'v'), vect2);
	assert(dict.getSize() == 3);
	printSizeCapacity(dict, "After adding 'v'/[0, 0, 0]:\n");
	std::cout << std::endl;
}
void DictionaryTest::removeTest(){
	Dictionary<long long, char> dict;
	for(char i = 'a'; i < 'd'; ++i)
		dict.add(i, i);
	printSizeCapacity(dict, "Testing removal. Before:\n");
	dict.remove((long long)'a', 'a');
	assert(dict.getSize() == 2);
	printSizeCapacity(dict, "After removing 97/'a':\n");
	std::cout << "Removing 97/'a' again\n";
	dict.remove((long long)'a', 'a');
	assert(dict.getSize() == 2);
	std::cout << std::endl;
}
void DictionaryTest::removeTest2(){
	Dictionary<std::string, Vector> dict;
	Vector vect(3);
	for(int i = 0; i < 3; ++i){
		for(int j = 0; j < 3; ++j)
			vect.setNthValue(j, i);
		dict.add(std::string(1, 'a' + i), vect);
	}
	printSizeCapacity(dict, "Testing removal. Before:\n");
	dict.remove(std::string(1, 'c'), vect);
	assert(dict.getSize() == 2);
	printSizeCapacity(dict, "After removing 'c'/[2,2,2]:\n");
	std::cout << "Removing 'b'/[2,2,2]\n";
	dict.remove(std::string(1, 'b'), vect);
	assert(dict.getSize() == 2);
	std::cout << std::endl;
}
void DictionaryTest::changeTest(){
	Dictionary<int, double> dict;
	for(int i = 0; i < 3; ++i)
		dict.add(i + 1, (i + 1) * (i + 2));
	printSizeCapacity(dict, "Testing changing. Before:\n");
	dict.change(1, 3.14);
	printSizeCapacity(dict, "After changing key: 1 to value: 3.14\n");
	std::cout << "Trying to change element with key 4\n";
	bool f = dict.change(4, 3.14);
	assert(!f);
	std::cout << "Confirming change happened\n";
	double confirm = 0;
	bool b = dict.find(1, confirm);
	assert(confirm == 3.14);
	assert(b);
	std::cout << "Test successful\n\n";
}
void DictionaryTest::changeTest2(){
	Dictionary<std::string, Vector> dict;
	Vector vect(3);
	for(int i = 0; i < 3; ++i){
		for(int j = 0; j < 3; ++j)
			vect.setNthValue(j, i + j);
		dict.add(std::string(1, 'n' - i), vect);
	}
	printSizeCapacity(dict, "Testing changing. Before:\n");
	for(int i = 0; i < 3; ++i)
		vect.setNthValue(i, 2 * (i + 1));
	dict.change(std::string(1, 'm'), vect);
	printSizeCapacity(dict, "After changing key: 'm' to value: [2,4,6]\n");
	Vector vect2(3);
	assert(dict.find(std::string(1, 'm'), vect2));
	assert(vect2 == vect);
	std::cout << "Change successful\n\n";
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
	std::cout << "Different sizes: " << (dict3 == dict1) << "\n\n";
}
void DictionaryTest::comparisonTest2(){
	std::cout << "Testing comparison with string/vector\n";
	Dictionary<std::string, Vector> dict1, dict2;
	Vector vect(3);
	for(int i = 0; i < 3; ++i){
		dict1.add(std::string(1, 'a' + i), vect);
		dict2.add(std::string(1, 'a' + i), vect);
	}
	assert(dict1 == dict2);
	std::cout << "Equal dictionaries: " << std::boolalpha << (dict1 == dict2) << std::endl;
	vect.setNthValue(1, 2);
	dict2.change(std::string(1, 'b'), vect);
	assert(!(dict1 == dict2));
	std::cout << "Different dictionaries: " << (dict1 == dict2) << "\n\n";
}
