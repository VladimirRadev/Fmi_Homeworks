#include "Document.hpp"
Document::Document(const std::string& name, const std::string& location, const std::string& extension)
	:Object(name, location, extension), readingLine(1) {}

void Document::write_line(const std::string& line)
{
	this->lines.push_back(line);
}
std::string Document::read_line()
{
	if (((long unsigned int)this->readingLine > (long unsigned int)this->lines.size()))
	{
		throw std::out_of_range("No more lines to read at this document!");
	}
	else
	{
		std::string line_to_read = this->lines[this->readingLine - 1];
		this->readingLine++;
		return line_to_read;

	}

}
std::string Document::read_line(const unsigned line)
{
	if (((long unsigned int)line > (long unsigned int)this->lines.size()) || line==0)
	{
		throw std::out_of_range("Given line is out of range the document!");
	}
	else
	{
		std::string line_to_read = this->lines[(long unsigned int)line - 1];
		this->readingLine = (int)line + 1;
		return line_to_read;

	}
}
Object* Document::clone()const
{
	return new Document(*this);
}
std::string Document::to_string()const
{
	std::string result;
	result.append(get_name());
	result.push_back('\n');
	result.append(get_location());
	result.push_back('\n');
	result.append(get_extension());
	result.push_back('\n');
	for (long unsigned int i = 0; i < lines.size(); i++)
	{
		result.append(lines[i]);
		result.push_back('\n');
	}
	return result;
}
void Document::from_string(const std::string& source)
{
	if (source == "" || source[source.size()-1]!='\n' || source=="\n")
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





	//lines

	this->lines.clear();
	this->readingLine = 1;

	std::string lineToAdd;
	while (index!=source.size())
	{
		if (source[index] == '\n')
		{
			this->lines.push_back(lineToAdd);
			lineToAdd.clear();
			++index;
			continue;
		}
		lineToAdd.push_back(source[index]);
		++index;
	}
	return;
}
std::string Document::debug_print()const
{
	std::string result;
	if (lines.size() == 0)
	{
		result.push_back('\n');
		return result;
	}
	for (long unsigned int i = 0; i < lines.size(); i++)
	{
		result.append("Line ");
		result.append(std::to_string(i + 1));
		result.push_back(':');
		result.append(lines[i]);
		result.push_back('\n');
	}
	return result;
}
bool Document::operator==(const Comparable* rhs)const
{
	Document* isDocumentRhs = dynamic_cast<Document*>(const_cast<Comparable*>(rhs));
	if (isDocumentRhs != nullptr)
	{
		if (lines.size() != isDocumentRhs->lines.size())
		{
			return false;
		}
		else
		{
			for (long unsigned int i = 0; i < lines.size(); i++)
			{
				if (lines[i] != isDocumentRhs->lines[i])
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
bool Document::	operator!=(const Comparable* rhs)const
{
	return !(*this == rhs);

}