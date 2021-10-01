#include "KeyValueDatabase.hpp"
KeyValueDatabase::KeyValueDatabase(const std::string& name, const std::string& location, const std::string& extension)
	:Object(name,location,extension){}

void KeyValueDatabase::add_entry(const std::pair<std::string, int>& entry)
{
	bool isOperationExecuted = true;
	for(std::pair<std::string,int>& x:this->keyAndValues)
	{
		if (x.first == entry.first)
		{
			isOperationExecuted = false;
			break;
		}
	}
	if (isOperationExecuted)
	{
		this->keyAndValues.push_back(entry);
	}
	else
	{
		throw std::invalid_argument("Item with same key already exists!");
	}
}
int KeyValueDatabase::get_value(const std::string& key) const
{
	for (std::pair<std::string, int> x : keyAndValues)
	{
		if (x.first == key)
		{
			return x.second;
		}
	}
	throw std::invalid_argument("No such item with this key inside collection!");
	
}


Object* KeyValueDatabase::clone()const
{
	return new KeyValueDatabase(*this);
}
std::string KeyValueDatabase::to_string()const
{
	std::string result;
	result.append(get_name());
	result.push_back('\n');
	result.append(get_location());
	result.push_back('\n');
	result.append(get_extension());
	result.push_back('\n');
	for (long unsigned int i = 0; i < keyAndValues.size(); i++)
	{
		result.append(keyAndValues[i].first);
		result.push_back(':');
		result.append(std::to_string(keyAndValues[i].second));
		result.push_back('\n');
	}
	return result;
}
void KeyValueDatabase::from_string(const std::string& source)
{
	if (source == "" || source[source.size() - 1] != '\n' || source == "\n")
	{
		return;
	}
	long unsigned int index = 0;
	std::string newName;
	std::string newLocation;
	std::string newExtension;

	//newName
	while (source[index] != '\n')
	{
		newName.push_back(source[index]);
		++index;
	}
	this->name = newName;
	++index;

	//newLocation
	while (source[index] != '\n')
	{
		newLocation.push_back(source[index]);
		++index;
	}
	this->location = newLocation;
	++index;


	//newExtension
	while (source[index] != '\n')
	{
		newExtension.push_back(source[index]);
		++index;
	}
	this->extension = newExtension;
	++index;




	this->keyAndValues.clear();



	std::string key;
	std::string value;

	//lineToAdd contains key and value in string format as follows-> {key:value}
	std::string lineToAdd;

	//toAdd is pair storing loaded information from current lineToAdd (key and value taken from lineToAdd)
	std::pair<std::string, int>toAdd;

	while (index!=source.size())
	{
		if (source[index] == '\n')
		{
			//we add \n char to end of lineToAdd, because we need to know where current lineToAdd ends
			lineToAdd.push_back(source[index]);


			long unsigned int indexLineToAdd = 0;
			for (indexLineToAdd=0; lineToAdd[indexLineToAdd]!=':'; indexLineToAdd++)
			{
				key.push_back(lineToAdd[indexLineToAdd]);
			}
			++indexLineToAdd;
			for (long unsigned int j=indexLineToAdd; lineToAdd[j]!='\n'; j++)
			{
				value.push_back(lineToAdd[j]);
			}
			toAdd.first = key;
			toAdd.second = std::stoi(value);
			this->keyAndValues.push_back(toAdd);


			key.clear();
			value.clear();
			lineToAdd.clear();


			++index;
			continue;
		}
		lineToAdd.push_back(source[index]);
		++index;
	
	}
	return;
}
std::string KeyValueDatabase::debug_print()const
{
	std::string result;
	if (keyAndValues.empty())
	{
		result.push_back('\n');
		return result;
	}
	for (long unsigned int i = 0; i < keyAndValues.size(); i++)
	{
		
		result.push_back('{');
		result.append(keyAndValues[i].first);
		result.push_back(':');
		result.append(std::to_string(keyAndValues[i].second));
		result.push_back('}');
		result.push_back('\n');
	}
	return result;
}
bool KeyValueDatabase::operator==(const Comparable* rhs)const
{
	KeyValueDatabase* isDatabaseRhs = dynamic_cast<KeyValueDatabase*>(const_cast<Comparable*>(rhs));
	if (isDatabaseRhs != nullptr)
	{
		if (keyAndValues.size() != isDatabaseRhs->keyAndValues.size())
		{
			return false;
		}
		else
		{
			for (long unsigned int i = 0; i < keyAndValues.size(); i++)
			{
				if (keyAndValues[i].first == isDatabaseRhs->keyAndValues[i].first)
				{
					if (keyAndValues[i].second == isDatabaseRhs->keyAndValues[i].second)
					{
						continue;
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
			return true;
		}
	}
	else
	{
		return false;
	}
}
bool KeyValueDatabase::	operator!=(const Comparable* rhs)const
{
	return !(*this == rhs);

}