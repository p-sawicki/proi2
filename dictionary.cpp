#include <iostream>
#define DEFAULT_CAPACITY = 16;
/*TKey must implement the '<' '==' and '<<' operators.
  TValue must implement the '==' and '<<' operators. */
template<class TKey, class TValue>
class Dictionary{
	private:
		unsigned int size;
		unsigned int capacity;
		bool usable;
		TKey* keys;
		TValue* values;
		bool increaseCapacity(){
			if(!usable)
				return unusableError();
			unsigned int newCapacity = capacity * 2;
			TKey* newKeys = new TKey[newCapacity];
			TValue* newValues = new TValue[newCapacity];
			if(!keys || !values)
				return allocationError(newKeys, newValues);
			for(unsigned int i = 0; i < capacity; ++i){
				newKeys[i] = keys[i];
				newValues[i] = values[i];
			}
			delete[] keys;
			delete[] values;
			capacity = newCapacity;
			keys = newKeys;
			values = newValues;
			return true;
		}
		unsigned int findIndex(TKey key) const{
			if(!size)
				return 0;
			unsigned int difference = size / 4;
			unsigned int position = size / 2;
			while(true){
				if(key < keys[position]){
					if(position && key < keys[position - 1]){
						position -= difference;
						difference /= 2;
					}
					else
						return position;
				}
				else{
					if(position != size - 1 && !(key < keys[position + 1])){
						position += difference;
						difference /= 2;
					}
					else
						return position + 1;
				}
			}
		}
		void deleteKeysAndValues(TKey* keys, TValue* values){
			if(keys)
				delete[] keys;
			if(values)
				delete[] values;
			keys = NULL;
			values = NULL;
		}
		bool allocationError(TKey* keys, TValue* values){
			std::cout << "ERROR: Couldn't allocate memory. Try restarting the program.\n";
			deleteKeysAndValues(keys, values);
			size = 0;
			capacity = 0;
			usable = false;
			return false;
		}
		inline bool alreadyExistsError(){
			std::cout << "The key you are trying to add already exists in the dictionary.\n";
			return false;
		}
		inline bool cantFindError(){
			std::cout << "The key or key/value pair is not in the dictionary.\n";
			return false;
		}
		inline bool unusableError(){
			std::cout << "ERROR: Dictionary is in unusable state due to memory allocation error. Try restarting the program.\n";
			return false;
		}
	public:
		Dictionary() : size(0), capacity(DEFAULT_CAPACITY), usable(true){
			keys = new TKey[capacity];
			values = new TValue[capacity];
			if(!keys || !values)
				allocationError(keys, values);
		}
		bool isUsable(){
			return usable;
		}
		bool add(const TKey& key, const TValue& value){
			if(!usable)
				return unusableError();
			if(size + 1 == capacity)
				if(!increaseCapacity())
					return false;
			unsigned int index = findIndex(key);
			if(key == keys[index])
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
			if(!usable)
				return unusableError();
			unsigned int index = findIndex(key);
			if(!size || key != keys[index] || value != values[index])
				return cantFindError();
			for(unsigned int i = index; i < size; ++i){
				keys[i] = keys[i + 1];
				values[i] = values[i + 1];
			}
			--size;
			return true;
		}
		bool change(const TKey& key, const TValue& newValue){
			if(!usable)
				return unusableError();
			unsigned int index = findIndex(key);
			if(!size || key != keys[index])
				return cantFindError();
			vales[index] = newValue;
			return true;
		}
		bool find(const TKey& key, TValue& foundValue) const{
			if(!usable)
				return unusableError();
			unsigned int index = findIndex(key);
			if(!size || key != keys[index])
				return cantFindError();
			foundValue = values[index];
			return true;
		}
		unsigned int getSize() const{
			return size;
		}
		bool operator==(const Dictionary<TKey, TValue>& lhs) const{
			if(size != lhs.size)
				return false;
			for(unsigned int i = 0; i < size; ++i)
				if(!(keys[i] == lhs.keys[i] && values[i] == lhs.values[i]))
					return false;
			return true;
		}
		friend istream& operator<<(const std::istream& is, const Dictionary<TKey, TValue>& dict);
};
template<class TKey, class TValue>
istream& operator<<(const std::istream& is, const Dictionary<TKey, TValue>& dict){
	if(dict.size)
		is << "Keys: \t\t\t Values:\n";
	else
		is << "Dictionary is empty.\n";
	for(int i = 0; i < dict.size; ++i)
		is << dict.keys[i] << "\t\t\t" << dict.values[i] << std::endl;
	return is;
}
