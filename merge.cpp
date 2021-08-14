// g++ -o merge -std=c++2a merge.cpp -lstdc++
// union 合并多个文件的所有行，且去重复
// 文件可以有重复行，会改变原有顺序

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
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

//set、multiset都是集合类，差别在与set中不允许有重复元素，multiset中允许有重复元素
//注意前后不要有空格
std::set<string> merge (const std::vector<std::set<string>> &vecs) 
{
    std::set<string> last_intersection = vecs[0];
    std::set<string> curr_intersection;

    for (std::size_t i = 1; i < vecs.size(); ++i) 
    {
	    set<string> tmpVec = vecs[i];
        std::merge(last_intersection.begin(), last_intersection.end(),
            tmpVec.begin(), tmpVec.end(),
            std::inserter(curr_intersection, curr_intersection.begin()));
        std::swap(last_intersection, curr_intersection);
        curr_intersection.clear();
    }

    return last_intersection;
}


int main(int argc,char *argv[ ]) 
{
    vector<string> files;
    // 检查文件存在
    for (int i=1; i<argc; i++)
	{
	    string file = argv[i];
		fs::path f{ file };
		if (!fs::exists(f))
		{
		    cout << file << " not exist" << endl;

		    return -1;
		}
		files.push_back(file);
	}

	std::vector<std::set<string>> vecs;
	for (string & file : files)
	{
	    std::set<std::string> setOfStr;
	    // Get the contents of file in a vector
        bool result = getFileContent(file, setOfStr);
		if(result)
		{
		    vecs.push_back(setOfStr);
		}
		else
		{
		    cout << "read error " << file << endl;
		}
	}
	set<string> mergeSect = merge(vecs);
    for(string line : mergeSect)
	{
	    std::cout<<line<<std::endl;
    }

    return 0;
}





