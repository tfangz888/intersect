// g++ -o difference -std=c++2a difference.cpp -lstdc++
// 求文件差集, 允许有重复行, 会改变原来行的顺序

#include <iostream>
#include <fstream>
#include <string>
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
 * put them in given set
 */
bool getFileContent(std::string fileName, std::set<std::string> & setOfStrs)
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
            setOfStrs.insert(str);
    }
    //Close The File
    in.close();

    return true;
}

int main(int argc,char *argv[ ]) 
{
    string first = argv[1];
    string second = argv[2];    
    
    // 检查文件存在
    string file = first;
	fs::path f1{ file };
	if (!fs::exists(f1))
	{
	    cout << file << " not exist" << endl;

	    return -1;
	}
    file = second;
	fs::path f2{ file };
	if (!fs::exists(f2))
	{
	    cout << file << " not exist" << endl;

	    return -1;
	}
    
    set<string> firstSet;
    bool result = getFileContent(first, firstSet);
	if(!result)
	{
	    cout << "read error " << first << endl;
	}
    set<string> secondSet;
    result = getFileContent(second, secondSet);
	if(!result)
	{
	    cout << "read error " << second << endl;
	}
    
    set<string> difference;
    std::set_difference (firstSet.begin(), firstSet.end(),
            secondSet.begin(), secondSet.end(),
            std::inserter(difference, difference.begin()));
    
    for(string line : difference)
	{
	    std::cout<<line<<std::endl;
    }

    return 0;
}





