// g++ -o intersect -std=c++2a intersect.cpp -lstdc++
// 文件不允许有重复行，排序后会改变原有顺序

#include <iostream>
#include <fstream>
#include <string>
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

//set、multiset都是集合类，差别在与set中不允许有重复元素，multiset中允许有重复元素
//注意前后不要有空格
std::vector<string> intersection (const std::vector<std::vector<string>> &vecs) 
{
    auto last_intersection = vecs[0];
    std::vector<string> curr_intersection;

    for (std::size_t i = 1; i < vecs.size(); ++i) 
    {
	    vector<string> tmpVec = vecs[i];
		std::sort(last_intersection.begin(), last_intersection.end());
		std::sort(tmpVec.begin(), tmpVec.end());
        std::set_intersection(last_intersection.begin(), last_intersection.end(),
            tmpVec.begin(), tmpVec.end(),
            std::back_inserter(curr_intersection));
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

	std::vector<std::vector<string>> vecs;
	for (string & file : files)
	{
	    std::vector<std::string> vecOfStr;
	    // Get the contents of file in a vector
        bool result = getFileContent(file, vecOfStr);
		if(result)
		{
		    vecs.push_back(vecOfStr);
		}
		else
		{
		    cout << "read error " << file << endl;
		}
	}
	vector<string> interSect = intersection(vecs);
	for(string & line : interSect)
	{
	    std::cout<<line<<std::endl;
    }

    return 0;
}





