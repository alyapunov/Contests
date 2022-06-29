#include <alya.h>
#include <array>
#include <cassert>

using namespace std;

struct Stat {
	uint8_t arr[32];
	void clear()
	{
		memset(arr, 0, 32);
	}
	void add(char c)
	{
		arr[c - 'a']++;
	}

	bool operator==(const Stat& a) const
	{
		return memcmp(arr, a.arr, 32) == 0;
	}
};

class Solution {
public:
	Stat stat1[32][32];
	Stat stat2[32][32];

	bool isScramble(const std::string& s1, size_t b1, size_t e1,
			const std::string& s2, size_t b2, size_t e2)
	{
		assert(e1 - b1 == e2 - b2);
		assert(e1 - b1 > 0);
		if (e1 - b1 == 1)
			return s1[b1] == s2[b2];
		if (!(stat1[b1][e1] == stat2[b2][e2]))
			return false;
		for (size_t i = 0; b1 + i < e1; i++) {
			if (isScramble(s1, b1, b1 + i, s2, b2, b2 + i) &&
				isScramble(s1, b1 + i, e1, s2, b2 + i, e2))
				return true;
			if (isScramble(s1, b1, b1 + i, s2, e2 - i, e2) &&
			    isScramble(s1, b1 + i, e1, s2, b2 + i, e2))
				return true;
		}

	}
	bool isScramble(const std::string &s1, const std::string &s2) {
		return isScramble(s1, 0, s1.size(), s2, 0, s2.size());

	}
};

void
check(const std::string &s1, const std::string &s2, bool exp)
{
	Solution sol;
	bool res = sol.isScramble(s1, s2);
	if (res != exp) {
		std::cout << s1 << " and " << s2 << " : "
			  << "expected " << exp << " got " << res << std::endl;
		abort();
	}
}


int main()
{
	check("great", "rgeat", true);
	check("abcde", "caebd", false);
	check("a", "a", true);
}
