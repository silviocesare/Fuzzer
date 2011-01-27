#include "MaximumCoverage.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

std::set<Addr>*
MaximumCoverage::BuildSetFromBinaryFilename(std::string &filename)
{
	std::set<Addr> *set;
	std::ifstream stream;

	stream.open(filename.c_str(), std::ifstream::in);
	if (!stream)
		return NULL;

	set = new std::set<Addr>();
	if (set == NULL) {
		stream.close();
		return NULL;
	}
	while (!stream.eof()) {
		Addr address;

		stream.read((char *)&address, 4);
		set->insert(address);
		m_AllBlocks.insert(address);
	}	
	stream.close();
	return set;
}

std::set<Addr>*
MaximumCoverage::BuildSetFromFilename(std::string &filename)
{
	std::set<Addr> *set;
	std::ifstream stream;

	stream.open(filename.c_str(), std::ifstream::in);
	if (!stream)
		return NULL;

	set = new std::set<Addr>();
	if (set == NULL) {
		stream.close();
		return NULL;
	}
	while (!stream.eof()) {
		std::string line;
		Addr address;

		// ho ho, how very un c++ like
		getline(stream, line);
		address = strtoul(line.c_str(), NULL, 16);
		set->insert(address);
		m_AllBlocks.insert(address);
	}	
	stream.close();
	return set;
}
