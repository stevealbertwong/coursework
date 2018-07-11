/*
https://leetcode.com/problems/string-compression/description/
https://leetcode.com/articles/string-compression/
https://www.youtube.com/watch?v=XMKMgzU1uiw&index=7&list=PLNmW52ef0uwsjnM06LweaYEZr-wjPKBnj

https://leetcode.com/problems/string-compression/discuss/129997/short-C++-solution-with-sentinel
https://leetcode.com/problems/string-compression/discuss/92563/C++-O(N)
*/

#include <iostream>
#include <string>
#define LOG(x) std::cout << x << std::endl;

void compress(const std::string& s){
	std::string output;
	int cnt = 0;
	char start = s[0];

	for (int i = 0; i < (int)s.size(); ++i)
	{				
		if(start != s[i]){			
			output += start;
			output += cnt+'0';
			start = s[i];
			cnt = 1;
		} else {			
			cnt++;
		}
	}
	
	output += start;
	output += cnt+'0';
	LOG(output)

}

int main(int argc, char const *argv[])
{
	/* code */
	std::string s = "aaaaabbbcccc";
	compress(s);
	return 0;
}

