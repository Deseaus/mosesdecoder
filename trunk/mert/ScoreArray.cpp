/*
 *  ScoreArray.cpp
 *  met - Minimum Error Training
 *
 *  Created by Nicola Bertoldi on 13/05/08.
 *
 */

#include <fstream>
#include "ScoreArray.h"
#include "Util.h"


ScoreArray::ScoreArray(): idx(0)
{};

void ScoreArray::savetxt(std::ofstream& outFile)
{
        ScoreStats entry;

	outFile << SCORES_TXT_BEGIN << " " << idx << " " << array_.size() << std::endl;
	for (vector<ScoreStats>::iterator i = array_.begin(); i !=array_.end(); i++)
		(*i).savetxt(outFile);
	outFile << SCORES_TXT_END << std::endl;
}

void ScoreArray::savebin(std::ofstream& outFile)
{
        TRACE_ERR("binary saving is not yet implemented!" << std::endl);  

/*
NOT YET IMPLEMENTED
*/
        outFile << SCORES_BIN_BEGIN << " " << idx << " " << array_.size() << std::endl;
        outFile << SCORES_BIN_END << std::endl;

}


void ScoreArray::save(std::ofstream& inFile, bool bin)
{
        (bin)?savebin(inFile):savetxt(inFile);
}

void ScoreArray::save(const std::string &file, bool bin)
{
        TRACE_ERR("saving the array into " << file << std::endl);  

        std::ofstream outFile(file.c_str(), std::ios::out); // matches a stream with a file. Opens the file

        save(outFile);

        outFile.close();
}

void ScoreArray::loadtxt(ifstream& inFile)
{
        ScoreStats entry;

        int sentence_index;
        int number_of_entries;
	int nextPound;

        std::string substring, stringBuf, sentence_code = "";
        std::string::size_type loc;


	TRACE_ERR("starting loadtxt..." << std::endl);
	std::getline(inFile, stringBuf);
	if (stringBuf.empty()){
		TRACE_ERR("ERROR: Empty string" << std::endl);
		return;
	}         

	if (!stringBuf.empty()){         
//		TRACE_ERR("Reading: " << stringBuf << std::endl); 
		nextPound = getNextPound(stringBuf, substring);
		nextPound = getNextPound(stringBuf, substring);
       	        idx = atoi(substring.c_str());
		nextPound = getNextPound(stringBuf, substring);
       	        number_of_entries = atoi(substring.c_str());
//		TRACE_ERR("idx: " << idx " nbest: " << number_of_entries <<  std::endl);
	}

	for (int i=0 ; i < number_of_entries; i++)
	{
                entry.clear();
                std::getline(inFile, stringBuf);
		entry.set(stringBuf);
		add(entry);
	}

	std::getline(inFile, stringBuf);
	if (!stringBuf.empty()){         
//		TRACE_ERR("Reading: " << stringBuf << std::endl); 
                if ((loc = stringBuf.find(SCORES_TXT_END)) != 0){
			TRACE_ERR("ERROR: ScoreArray::loadtxt(): Wrong footer");
			return;
		}
	}
}

void ScoreArray::loadbin(ifstream& inFile)
{
        TRACE_ERR("binary saving is not yet implemented!" << std::endl);  

/*
NOT YET IMPLEMENTED
*/
}

void ScoreArray::load(ifstream& inFile, bool bin)
{
        (bin)?loadbin(inFile):loadtxt(inFile);
}

void ScoreArray::load(const std::string &file , bool bin)
{
	TRACE_ERR("loading data from " << file << std::endl);  

	std::ifstream inFile(file.c_str(), std::ios::in); // matches a stream with a file. Opens the file

	load(inFile, bin);
	inFile.close();
}
