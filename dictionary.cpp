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
		void deleteKeysAndValues(TKey* keysToDel, TValue* valuesToDel){
			if(keysToDel)
				delete[] keysToDel;
			if(valuesToDel)
				delete[] valuesToDel;
			keys = NULL;
			values = NULL;
		}
		bool allocationError(TKey* keysToDel, TValue* valuesToDel){
			std::cout << "ERROR: Couldn't allocate memory. Try restarting the program.\n";
			deleteKeysAndValues(keysToDel, valuesToDel);
			usable = false;
			return false;
		}
		inline bool alreadyExistsError() const{
			std::cout << "The key you are trying to add already exists in the dictionary.\n";
			return false;
		}
		inline bool cantFindError() const{
			std::cout << "The key or key/value pair is not in the dictionary.\n";
			return false;
		}
		inline bool unusableError() const{
			std::cout << "ERROR: Dictionary is in an unusable state due to a memory allocation error. Try restarting the program.\n";
			return false;
		}
	public:
		Dictionary(const unsigned int c = DEFAULT_CAPACITY) : size(0), capacity(c), usable(true){
			keys = new TKey[capacity];
			values = new TValue[capacity];
			if(!keys || !values){
				allocationError(keys, values);
				capacity = 0;
			}
		}
		~Dictionary(){
			deleteKeysAndValues(keys, values);
		}
		unsigned int getSize() const{
			return size;
		}
		bool isUsable() const{
			return usable;
		}
		bool doubleCapacity(){
			if(!usable)
				return unusableError();
			unsigned int newCapacity = capacity * 2;
			TKey* newKeys = new TKey[newCapacity];
			TValue* newValues = new TValue[newCapacity];
			if(!keys || !values)
				return allocationError(newKeys, newValues);
			for(unsigned int i = 0; i < size; ++i){
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
		bool add(const TKey& key, const TValue& value){
			if(!usable)
				return unusableError();
			if(size + 1 == capacity)
				if(!doubleCapacity())
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
