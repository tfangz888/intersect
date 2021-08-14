// g++ -o difference -std=c++2a difference.cpp -lstdc++
// 求两文件差集, 允许有重复行, 不会改变原来行的顺序.  如果第一个文件有重复行，会继续保留

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
 * put them in given vector
 */
bool getFileContent(std::string fileName, std::vector<std::string> & vectOfStrs)
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
            vectOfStrs.push_back(str);
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
    
    vector<string> firstVect;
    bool result = getFileContent(first, firstVect);
	if(!result)
	{
	    cout << "read error " << first << endl;
	}
    vector<string> secondVect; 
    result = getFileContent(second, secondVect);
	if(!result)
	{
	    cout << "read error " << second << endl;
	}
    set<string> s(secondVect.begin(), secondVect.end()); // set本身内部就会排序
    
    for (string & line: firstVect)
    {  
        if (!s.contains(line))
        {
            std::cout<<line<<std::endl;
        }
    }

    return 0;
}





