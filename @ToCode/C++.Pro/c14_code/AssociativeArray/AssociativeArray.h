#pragma once

#include <string>
#include <vector>
#include <stdexcept>

template <typename T>
class AssociativeArray
{
public:
	AssociativeArray();
	virtual ~AssociativeArray();
	
	T& operator[](const std::string& key);
	const T& operator[](const std::string& key) const;

private:
	class Element
	{
	public:
		Element(const std::string& key, const T& value) :
			mKey(key), mValue(value) {}
		std::string mKey;
		T mValue;
	};

	std::vector<Element> mData;
};

template <typename T>
AssociativeArray<T>::AssociativeArray()
{
}

template <typename T>
AssociativeArray<T>::~AssociativeArray()
{
}

template <typename T>
T& AssociativeArray<T>::operator[](const std::string& key)
{
	// See if key already exist
	for (auto& element : mData) {
		if (element.mKey == key)
			return element.mValue;
	}

	// If we arrive here, the key doesn't exist, add it
	return mData.insert(end(mData), Element(key, T()))->mValue;
}

template <typename T>
const T& AssociativeArray<T>::operator[](const std::string& key) const
{
	for (auto& element : mData) {
		if (element.mKey == key)
			return element.mValue;
	}
	throw invalid_argument("Key '" + key + "' doesn't exist");
}