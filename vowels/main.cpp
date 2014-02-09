#include <algorithm>
#include <cctype>
#include <functional>
#include <iostream>
#include <locale>
#include <vector>

struct vowel : public std::ctype<char>
{
	static const mask* make_table()
	{
		static std::vector<mask> v(classic_table(), classic_table() + table_size);
		v['a'] |= upper;
		v['e'] |= upper;
		v['i'] |= upper;
		v['o'] |= upper;
		v['u'] |= upper;
		return &v[0];
	}
	vowel(std::size_t refs = 0) : ctype(make_table(), false, refs){}
};

int main(int argc, const char* argv[])
{
	std::string x("Elephant");

	std::transform(x.begin(), x.end(), x.begin(), std::function<int(char)>(std::tolower));

	std::sort(x.begin(), x.end());

	std::unique(x.begin(), x.end());

	int i = std::count_if(x.begin(), x.end(), [](const char c)
	{ 
		return std::isupper(c, std::locale(std::locale(""), new vowel)); 
	});

	std::cout << "Number of vowels:" << i << std::endl;

	return 0;
}

