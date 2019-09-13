# include <vector>
#include <string>

class Solution {
public:
	std::string longestCommonPrefix(std::vector<std::string>& strs) {
		int length = strs.size();
		std::string s = "";

		if (strs.empty())
			return s;
		if (length < 2)
			return strs[0];
		else
		{
			for (int i = 0; i < strs[1].size(); ++i)
			{
				for (int j = 0; j < length - 1; ++j)
				{
					if (strs[j][i] != strs[j + 1][i])
					{
						return s;
					}
					else if (j == length - 2)
						s += strs[j][i];
				}

			}
		}

		return s;

	}
};