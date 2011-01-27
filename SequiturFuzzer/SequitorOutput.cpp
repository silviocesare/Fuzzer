#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>
#include <sstream>

static void
decompress(std::vector<std::string> &rules, std::string &rule)
{
	unsigned int ruleNum;
	std::stringstream strStream(rule);

	strStream >> ruleNum;
	while (!strStream.eof()) {
		char type;
		unsigned int num;

		strStream >> type;
		if (strStream.eof())
			break;
		strStream >> num;	
		if (type == 't') {
			printf("%c", num);
		} else {
			assert(type == 'n');
			decompress(rules, rules[num]);
		}
	}
}

int
main(int argc, char *argv[])
{
	std::vector<std::string> rules;
	std::string s;

	while (getline(std::cin, s)) {
		rules.push_back(s);
	}
	decompress(rules, rules[0]);
	return 0;
}
