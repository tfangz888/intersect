// g++ -o unique -std=c++2a unique.cpp -lstdc++
// 一个文件的行的去重，不改变原来的顺序

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

std::string& trim(std::string &s) 
{
    if (s.empty()) 
    {
        return s;
    }

    s.erase(0,s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);

    return s;
}

/*
 * It will iterate through all the lines in file and
 * put them in given vector
 */
bool getFileContent(std::string fileName, std::vector<std::string> & vecOfStrs)
{
    // Open the File
    std::ifstream in(fileName.c_str());

    // Check if object is valid
    if(!in)
    {
        std::cerr << "Cannot open the File : "<<fileName<<std::endl;

        return false;
    }

    std::string str;
    // Read the next line from File untill it reaches the end.
    while (std::getline(in, str))
    {
        // Line contains string of length > 0 then save it in vector
		str = trim(str);
        if(str.size() > 0)
            vecOfStrs.push_back(str);
    }
    //Close The File
    in.close();

    return true;
}

int main(int argc,char *argv[ ]) 
{
    string file = argv[1];
    // 检查文件存在
	fs::path f{ file };
	if (!fs::exists(f))
	{
	    cout << file << " not exist" << endl;

	    return -1;
	}
    
    vector<string> vect;
    bool result = getFileContent(file, vect);
	if(!result)
	{
	    cout << "read error " << file << endl;
	}
    
    set<string> s;
    for (string & line: vect)
    {  
        if (!s.contains(line))
        {
            std::cout<<line<<std::endl;
            s.insert(line);
        }
    }

    return 0;
}





