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
		unsigned int size;
		unsigned int capacity;
		TKey* keys;
		TValue* values;
		inline unsigned int max(const unsigned int&& a, const unsigned int&& b) const{
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
		Dictionary(const unsigned int c = DEFAULT_CAPACITY) : size(0), capacity(c){
			keys = new TKey[capacity];
			values = new TValue[capacity];
		}
		~Dictionary(){
			if(keys)
				delete[] keys;
			if(values)
				delete[] values;
			keys = NULL;
			values = NULL;
		}
		unsigned int getSize() const{
			return size;
		}
		unsigned int getCapacity() const{
			return capacity;
		}
		void doubleCapacity(){
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
		}
		bool add(const TKey& key, const TValue& value){
			if(size + 1 == capacity)
				doubleCapacity();
			unsigned int index = findIndex(key);
			if(size && index < size && key == keys[index])
				return alreadyExistsError();
			for(unsigned int i = size; i > index; --i){
				keys[i] = keys[i - 1];
				values[i] = values[i - 1];
			}
			keys[index] = key;
			values[index] = value;
			++size;
			return true;
		}
		bool remove(const TKey& key, const TValue& value){
			unsigned int index = findIndex(key);
			if(!size || index >= size || key != keys[index] || value != values[index])
				return cantFindError();
			for(unsigned int i = index; i < size; ++i){
				keys[i] = keys[i + 1];
				values[i] = values[i + 1];
			}
			--size;
			return true;
		}
		bool change(const TKey& key, const TValue& newValue){
			unsigned int index = findIndex(key);
			if(!size || index >= size || key != keys[index])
				return cantFindError();
			values[index] = newValue;
			return true;
		}
		bool find(const TKey& key, TValue& foundValue) const{
			unsigned int index = findIndex(key);
			if(!size || index >= size || key != keys[index])
				return cantFindError();
			foundValue = values[index];
			return true;
		}
		bool operator==(const Dictionary<TKey, TValue>& lhs) const{
			if(size != lhs.size)
				return false;
			for(unsigned int i = 0; i < size; ++i)
				if(!(keys[i] == lhs.keys[i] && values[i] == lhs.values[i]))
					return false;
			return true;
		}
		friend std::ostream& operator<<(std::ostream& os, const Dictionary<TKey, TValue>& dict){
			if(dict.size)
				os << "Keys: \t\t\t Values:\n";
			else
				os << "Dictionary is empty.\n";
			for(int i = 0; i < dict.size; ++i)
				os << dict.keys[i] << "\t\t\t" << dict.values[i] << std::endl;
			return os;
		}
};
#endif
