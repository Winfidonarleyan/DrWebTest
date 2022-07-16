#include "DRWebTest.h"
#include "Dictionary.h"
#include "NotFoundException.h"
//#include <mutex>
#include <unordered_map>

template <class Key>
class NotFoundExceptionImpl : public not_found_exception<Key>
{
public:
	NotFoundExceptionImpl(Key key) : _key(key) { }

	const Key& get_key() const noexcept override
	{
		return _key;
	}

	const char* what() const noexcept override
	{
		return "Key not found";
	}

private:
	Key _key;
};

template <class Key, class Value>
class DictoranryImpl : public dictionary<Key, Value>
{
public:
	DictoranryImpl() = default;
	~DictoranryImpl() = default;

	const Value& get(const Key& key) const override
	{
		auto itr = _store.find(key);
		if (itr == _store.end())
			throw NotFoundExceptionImpl(key);

		return itr->second;
	}

	void set(const Key& key, const Value& value) override
	{
		//std::lock_guard<std::mutex> guard(_mutex);

		auto itr = _store.find(key);
		if (itr != _store.end())
		{
			itr->second = value;
			return;
		}

		_store.emplace(key, value);
	}

	bool is_set(const Key& key) const override
	{
		return _store.find(key) != _store.end();
	}

private:
	DictoranryImpl(DictoranryImpl const&) = delete;
	DictoranryImpl(DictoranryImpl&&) = delete;
	DictoranryImpl operator=(DictoranryImpl const&) = delete;
	DictoranryImpl operator=(DictoranryImpl&&) = delete;

	//std::mutex _mutex;
	std::unordered_map<Key, Value> _store;
};


int main()
{
	using KeyType = int32_t;
	using ValueType = int32_t;

	try
	{
		DictoranryImpl<KeyType, ValueType> dictonary;

		// Add keys
		dictonary.set(1, 1);
		dictonary.set(2, 1);
		dictonary.set(3, 1);

		// Check is set keys
		std::cout << "> Is set 1? " << std::boolalpha << dictonary.is_set(1) << std::endl;
		std::cout << "> Is set 2? " << std::boolalpha << dictonary.is_set(2) << std::endl;
		std::cout << "> Is set 3? " << std::boolalpha << dictonary.is_set(3) << std::endl;
		std::cout << "> Is set 4? " << std::boolalpha << dictonary.is_set(4) << std::endl;

		// Get value from keys
		std::cout << "> Key 1: " << dictonary.get(1) << std::endl;
		std::cout << "> Key 2: " << dictonary.get(2) << std::endl;
		std::cout << "> Key 3: " << dictonary.get(3) << std::endl;
		std::cout << "> Key 4: " << dictonary.get(4) << std::endl;
	}
	catch (NotFoundExceptionImpl<KeyType> const& e)
	{
		std::cout << "\n\n" << e.what() << ". Key: " << e.get_key() << std::endl;
	}

	return 0;
}
