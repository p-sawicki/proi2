/*Author: Piotr Sawicki*/
#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <iostream>
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
		ListNode* findNode(const TKey& key) const{
			ListNode* result = head;
			if(!size || key < head->key)
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
			while(head && head->next){
				ListNode* next = head->next;
				delete head;
				head = next;
			}
			delete head;
		}
		unsigned int getSize() const{
			return size;
		}
		bool add(const TKey& key, const TValue& value){
			ListNode* spot = findNode(key);
			if(spot && spot->key == key)
				return alreadyExistsError();
			ListNode* newNode = new ListNode;
			newNode->key = key;
			newNode->value = value;
			ListNode* next = NULL;
			if(spot){
				next = spot->next;
				spot->next = newNode;
				spot->next->next = next;
			}
			else{
				if(head)
					next = head;
				head = newNode;
				head->next = next;
			}
			++size;
			return true;
		}
		bool remove(const TKey& key, const TValue& value){
			ListNode* spot = findNode(key);
			if(!spot || spot->key != key || spot->value != value)
				return cantFindError();
			ListNode* next = NULL;
			if(spot != head){
				ListNode* prev = head;
				while(prev && prev->next && prev->next != spot)
					prev = prev->next;
				prev->next = spot->next;
			}
			else
				next = head->next;
			delete spot;
			if(next)
				head = next;
			--size;
			return true;
		}
		bool change(const TKey& key, const TValue& newValue){
			ListNode* spot = findNode(key);
			if(!spot || spot->key != key)
				return cantFindError();
			spot->value = newValue;
			return true;
		}
		bool find(const TKey& key, TValue& foundValue) const{
			ListNode* spot = findNode(key);
			if(!spot || spot->key != key)
				return cantFindError();
			foundValue = spot->value;
			return true;
		}
		bool operator==(const Dictionary<TKey, TValue>& lhs) const{
			if(size != lhs.size)
				return false;
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
