#include "CodeCoverageSoFar.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

unsigned int
CodeCoverageSoFar::FindUncovered(std::set<Addr> *set)
{
        std::set<Addr>::iterator iter;
        unsigned int count;

        count = 0;
        for (   iter  = set->begin();
                iter != set->end();
                iter++)
        {
                if (m_RemainingBlocks.find(*iter) != m_RemainingBlocks.end()) {
			m_RemainingBlocks.erase(*iter);
                        count++;
                }
        }
        return count;
}

std::set<Addr>*
CodeCoverageSoFar::BuildSetFromBinaryFilename(std::string &filename)
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
CodeCoverageSoFar::BuildSetFromFilename(std::string &filename)
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

void
CodeCoverageSoFar::Build(std::list<std::string> &filenameList, std::list<std::pair<std::string, double> > &resultsList)
{
	std::list<std::string>::iterator fileIter;
	std::map<std::string, std::set<Addr> *>::iterator setIter;
	double soFar;

	for (	fileIter  = filenameList.begin();
		fileIter != filenameList.end();
		fileIter++)
	{
		m_SetsByFilename[*fileIter] = BuildSetFromBinaryFilename(*fileIter);
	}
	m_RemainingBlocks = m_AllBlocks;
	soFar = 0.0;
	for (	fileIter  = filenameList.begin();
		fileIter != filenameList.end();
		fileIter++)
	{
		double d;
		unsigned int u;

		u = FindUncovered(m_SetsByFilename[*fileIter]);
		d = (double)u / (double)m_AllBlocks.size();
		soFar += d;
		resultsList.push_back(std::pair<std::string, double>(*fileIter, soFar));
	}
	for (	setIter  = m_SetsByFilename.begin();
		setIter != m_SetsByFilename.end();
		setIter++)
	{
		delete setIter->second;
	}
}
