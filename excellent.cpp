// g++ -o excellent -std=c++2a excellent.cpp -lstdc++  
// 求多个科目的优秀学生，保留原有优秀顺序。第一个参数为优秀的前百分位   
// 如果 ./excellent 0.3 subject1.txt subject2.txt subject3.txt     
// 0.3表示每个科目名次在30%以内, subject是成绩排名，第一名是为最优秀  
// 从每科目的第一名开始找，求各科目的交集

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

//set、multiset都是集合类，差别在与set中不允许有重复元素，multiset中允许有重复元素
//注意前后不要有空格
std::set<string> intersection (const std::vector<std::set<string>> &vects) 
{
    std::set<string> last_intersection = vects[0];
    std::set<string> curr_intersection;

    for (std::size_t i = 1; i < vects.size(); ++i) 
    {
	    set<string> tmpVec = vects[i];
        std::set_intersection(last_intersection.begin(), last_intersection.end(),
            tmpVec.begin(), tmpVec.end(),
            std::inserter(curr_intersection, curr_intersection.begin()));
        std::swap(last_intersection, curr_intersection);
        curr_intersection.clear();
    }

    return last_intersection;
}

const set<string> getVectorRange(const vector<string>& vect, int count)
{
    set<string> result;
    if (count <= 0 || count > vect.size())
    {
        cout << "error count <= 0 or count > vect.size() in getVectorRange()" << endl;
        
        return result;
    }
    for (int i=0; i<count; i++)
    {
        result.insert(vect[i]);
    }
    
    return result;
}

int main(int argc,char *argv[ ]) 
{
    float percent = std::atof(argv[1]); // 0.3
    vector<string> files;
    // 检查文件存在
    for (int i=2; i<argc; i++)
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

	std::vector<std::vector<string>> vects;
	for (string & file : files)
	{
	    std::vector<std::string> vectOfStr;
	    // Get the contents of file in a vector
        bool result = getFileContent(file, vectOfStr);
		if(result)
		{
		    vects.push_back(vectOfStr);
		}
		else
		{
		    cout << "read error " << file << endl;
		}
	}
    // vector to set
    std::vector<std::set<string>> vects_set;
    for(std::vector<string> vec : vects)
    {
        std::set s(vec.begin(), vec.end());
        vects_set.push_back(s);
    }
    
    // 求交集
	set<string> interSect = intersection(vects_set);
    if (interSect.size() <= 0)
    {
        cout << "no inter sect of subjects" << endl;
        
        return -1;
    }
    
    // 只保留交集和顺序
    std::vector<std::vector<string>> vects_intersect;
    for(std::vector<string> vec : vects)
    {
        std::vector<string> vec_intersect;
        for(string line : vec)
        {
            // 如果在交集里有，而还vec_intersect没有。如果vec_intersect已经有了，为避免重复就不再插入了
            if (interSect.contains(line) && !std::count(vec_intersect.begin(), vec_intersect.end(), line))
                vec_intersect.push_back(line);
        }
    }
    
    // 检查每个Vector 的数目相等，且等于交集的数目
    for(std::vector<string> vec : vects_intersect)
    {
        if (vec.size() != interSect.size())
        {
            cout << "size of interSect is not equal every every vector" << endl;
            
            return -1;
        }
    }
    
    // 先求各科目第一名的交集，再求各科目前两名的交集，再求各科目前三名的交集....
    // 排过名的学生不再参与排名
    int topPercent = int(interSect.size() * percent);
    vector<string> topVect;
    for (int count = 1; count < topPercent; count ++)
    {
        std::vector<std::set<string>> vects_set_top;
        for(std::vector<string> vec : vects_intersect)
        {
            vects_set_top.push_back(getVectorRange(vec, count));            
        }
        // 求交集
	    set<string> interSect_top = intersection(vects_set_top);
        for (string student : interSect_top)
        {
            // 如果还没有参与排名，就进入排名
            if (!std::count(topVect.begin(), topVect.end(), student))
            {
                topVect.push_back(student);
            }   
        }        
    }
    
    for (string student : topVect)
    {
        cout << student << endl;
    }

    return 0;
}

