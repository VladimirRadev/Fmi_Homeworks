#include <vector>
#include <iostream>
#include <string>
struct SearchResult
{
    std::string fileName;
    unsigned line_number;
    std::string line;
};
class File
{
public:
    virtual std::vector<SearchResult> search(const std::string& str) const = 0;
    virtual ~File() {}
};
class Document : public File
{
    std::string name;
    std::string contents;

public:
    Document(const std::string& _name, const std::string& _contents) :name(_name),contents(_contents){}
    
    std::vector<SearchResult> search(const std::string& str) const
    {
        std::vector<SearchResult> result;
        unsigned int n=1;
        std::string line;
        unsigned long long size=0;
        while(size != this->contents.size())
        {
            
            if(this->contents[size]=='\n' || size== this->contents.size() - 1)
            {
                line+=this->contents[size];
                size_t find=line.find(str);
                if(find!=std::string::npos)
                {
                    if(line[line.size()-1] == '\n')
                    {
                        line.erase(line.begin()+line.size()-1);
                    }
                    result.push_back(SearchResult{this->name,n,line});
                }
                n++;
                line="";
            }  
            else
            {
                line+=this->contents[size];
            }
            size++;

        }
        return result;
    }
};
class Folder : public File
{
    std::vector<File*> files;
    std::string name;

public:
    Folder(const std::string& _name) : name(_name){}
    
    void addFile(File* f)
    {
        files.push_back(f);
    }
    std::vector<SearchResult> search(const std::string& str) const
    {
        std::vector<SearchResult> result;
        for(File* file : files)
        {
            std::vector<SearchResult> temp = file->search(str);
            for(SearchResult s: temp)
            {
                result.push_back(s);
            }
        }
        return result;
    }
};
int main()
{
    Document d1("employees.txt", "John Smith\nMaryia Ivanova\n"),
        d2("inventory.txt", "Computers: 3\nPrinters: 1"),
        d3("employees.txt", "Ivan Petrov\nJane Smith"),
        d4("inventory.txt", "Computers: 5, 3D Printers: 1");
    Folder root("root"), acme("ACME Soft, Inc."), best("Best Soft, OOD");
    acme.addFile(&d1);
    acme.addFile(&d2);
    best.addFile(&d3);
    best.addFile(&d4);
    root.addFile(&acme);
    root.addFile(&best);
    std::vector<SearchResult> results = root.search("Smith");
    for (unsigned i = 0; i < results.size(); ++i)
    {
        std::cout << results[i].fileName
                  << ", line " << results[i].line_number << ": "
                  << results[i].line << std::endl;
    }
}
