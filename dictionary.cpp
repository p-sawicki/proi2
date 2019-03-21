/*Author: Piotr Sawicki*/
#ifndef DICTIONARY_CPP
#define DICTIONARY_CPP
#include <iostream>
#define DEFAULT_CAPACITY 16
/*TKey must implement the '<' '==' and '<<' operators.
  TValue must implement the '==' and '<<' operators.
  Both TKey and TValue must have parameterless constructors. */
template<class TKey, class TValue>
class Dictionary{
	private:
		struct ListNode{
			TKey key;
			TValue value;
			ListNode* next;
		};
		unsigned int size;
		ListNode* head;
		/*inline unsigned int max(const unsigned int&& a, const unsigned int&& b) const{
			unsigned int result = a > b ? a : b;
			return result;	
		}
		unsigned int findIndex(const TKey& key) const{
			if(!size)
				return 0;
			unsigned int position = size / 2;
			unsigned int difference = (size - position) / 2;
			while(true){
				if(key == keys[position])
					return position;
				if(key < keys[position]){
					if(position && key < keys[position - 1]){
						position -= difference;
						difference = max(1, difference / 2);
					}
					else if(!position)
						return 0;
					else if(key == keys[position - 1])
						return position - 1;
					else 
						return position;
				}
				else{
					if(position != size - 1 && key < keys[position + 1])
						return position + 1;
					else if(position == size - 1)
						return size;
					else if(key == keys[position + 1])
						return position + 1;
					else{
						position += difference;
						difference = max(1, difference / 2);
					}
				}
			}
		}*/
		ListNode* findNode(const TKey& key) const{
			ListNode* result = head;
			if(!size)
				return NULL;
			while(result->next && result->next->key < key)
				result = result->next;
			if(result->next && result->next->key == key)
				return result->next;
			else
				return result;
		}
		inline bool alreadyExistsError() const{
			std::cout << "The key you are trying to add already exists in the dictionary.\n";
			return false;
		}
		inline bool cantFindError() const{
			std::cout << "The key or key/value pair is not in the dictionary.\n";
			return false;
		}
	public:
		Dictionary() : size(0), head(NULL) {}
		~Dictionary(){
			while(head->next){
				ListNode* next = head->next;
				delete head;
				head = next;
			}
		}
		unsigned int getSize() const{
			return size;
		}
		/*unsigned int getCapacity() const{
			return capacity;
		}*/
		/*void doubleCapacity(){
			unsigned int newCapacity = capacity * 2;
			TKey* newKeys = new TKey[newCapacity];
			TValue* newValues = new TValue[newCapacity];
			for(unsigned int i = 0; i < size; ++i){
				newKeys[i] = keys[i];
				newValues[i] = values[i];
			}
			delete[] keys;
			delete[] values;
			capacity = newCapacity;
			keys = newKeys;
			values = newValues;
		}*/
		bool add(const TKey& key, const TValue& value){
			/*if(size + 1 == capacity)
				doubleCapacity();
			unsigned int index = findIndex(key);*/
			/*if(size && index < size && key == keys[index])*/
			ListNode* spot = findNode(key);
			if(spot && spot->key == key)
				return alreadyExistsError();
			/*for(unsigned int i = size; i > index; --i){
				keys[i] = keys[i - 1];
				values[i] = values[i - 1];
			}
			keys[index] = key;
			values[index] = value;*/
			ListNode* newNode = new ListNode;
			newNode->key = key;
			newNode->value = value;
			if(spot){
				ListNode* next = spot->next;
				spot->next = newNode;
				spot->next->next = next;
			}
			else{
				head = newNode;
				head->next = NULL;
			}
			++size;
			return true;
		}
		bool remove(const TKey& key, const TValue& value){
			/*unsigned int index = findIndex(key);
			if(!size || index >= size || key != keys[index] || value != values[index])*/
			ListNode* spot = findNode(key);
			if(!spot || spot->key != key || spot->value != value)
				return cantFindError();
			/*for(unsigned int i = index; i < size; ++i){
				keys[i] = keys[i + 1];
				values[i] = values[i + 1];
			}*/
			if(spot == head && head->key == key){
				ListNode* next = head->next;
				delete head;
				head = next;
				--size;	
				return true;
			}
			ListNode* prev = head;
			while(prev && prev->next && prev->next != spot)
				prev = prev->next;
			prev->next = spot->next;
			delete spot;
			--size;
			return true;
		}
		bool change(const TKey& key, const TValue& newValue){
			/*unsigned int index = findIndex(key);
			if(!size || index >= size || key != keys[index])*/
			ListNode* spot = findNode(key);
			if(!spot || spot->key != key)
				return cantFindError();
			spot->value = newValue;
			return true;
		}
		bool find(const TKey& key, TValue& foundValue) const{
			/*unsigned int index = findIndex(key);
			if(!size || index >= size || key != keys[index])*/
			ListNode* spot = findNode(key);
			if(!spot || spot->key != key)
				return cantFindError();
			foundValue = spot->value;
			return true;
		}
		bool operator==(const Dictionary<TKey, TValue>& lhs) const{
			if(size != lhs.size)
				return false;
			/*for(unsigned int i = 0; i < size; ++i)
				if(!(keys[i] == lhs.keys[i] && values[i] == lhs.values[i]))
					return false;*/
			ListNode* nodeRight = head;
			ListNode* nodeLeft = lhs.head;
			while(nodeRight && nodeLeft){
				if(nodeRight->key != nodeLeft->key || nodeRight->value != nodeLeft->value)
					return false;
				nodeRight = nodeRight->next;
				nodeLeft = nodeLeft->next;
			}
			return true;
		}
		friend std::ostream& operator<<(std::ostream& os, const Dictionary<TKey, TValue>& dict){
			if(dict.size)
				os << "Keys: \t\t\t Values:\n";
			else
				os << "Dictionary is empty.\n";
			ListNode* node = dict.head;
			while(node){
				os << node->key << "\t\t\t" << node->value << std::endl;
				node = node->next;
			}
			return os;
		}
};
#endif
