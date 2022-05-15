// Name: Daniil Sen
// Seneca Student ID: 160970190
// Seneca email: dsen5@myseneca.ca
// Date of completion: 12/04/2021
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#include <algorithm>
#include <fstream>

#include "LineManager.h"
#include "Utilities.h"

sdds::LineManager::LineManager(const std::string& file,
	const std::vector<Workstation*>& stations) {
	try
	{
		std::ifstream assemblyFile;
		assemblyFile.open(file);

		if (assemblyFile.is_open()) {
			Utilities util;
			util.setDelimiter('|');
			size_t pos = 0;
			bool notdone = false;

			while (!assemblyFile.eof()) {
				std::string line;
				std::getline(assemblyFile, line);
				std::string s1 = util.extractToken(line, pos, notdone);
				auto w1 = std::find_if(stations.begin(), stations.end(), [&](Workstation* ws) { return (ws->getItemName() == s1); });
				if (notdone) {
					std::string s2 = util.extractToken(line, pos, notdone);
					auto w2 = std::find_if(stations.begin(), stations.end(), [&](Workstation* ws) { return (ws->getItemName() == s2); });
					(*w1)->setNextStation(*w2);
				}
				activeLine.push_back(*w1);
				pos = 0;
				notdone = true;
			}
			assemblyFile.close();
			m_firstStation = *std::find_if(stations.begin(), stations.end(), [&](Workstation* ws) { return (ws->getItemName() == activeLine[0]->getItemName()); });
			m_cntCustomerOrder = pending.size();
		}
		else {
			throw "bad";
		}
	}
	catch (...)
	{
		std::cout << "EXCEPTION AT LINE MANGER\n\n";
	}	
}

void sdds::LineManager::linkStations() {
	for (size_t i = 0; i < activeLine.size() - 1; ++i) {
		if (activeLine[i]->getNextStation() != nullptr) {
			for (size_t j = 0; j < activeLine.size(); ++j) {
				if (activeLine[i]->getNextStation()->getItemName() == activeLine[j]->getItemName()) {
					Workstation* t = activeLine[i + 1];
					activeLine[i + 1] = activeLine[j];
					activeLine[j] = t;
				}
			}
		}
	}
}

bool sdds::LineManager::run(std::ostream& os) {
	static size_t it = 1;
	os << "Line Manager Iteration: " << it++ << '\n';
	if (!pending.empty()) {
		*m_firstStation += std::move(pending.front());
		pending.pop_front();
	}
	std::for_each(activeLine.begin(), activeLine.end(), [&](Workstation* w) { w->fill(os); });
	std::for_each(activeLine.begin(), activeLine.end(), [&](Workstation* w) { w->attemptToMoveOrder(); });
	return !incomplete.empty();
}

void sdds::LineManager::display(std::ostream& os) const {
	for (auto it = activeLine.begin(); it != activeLine.end(); it++) {
		os << (*it)->getItemName();
		if ((*it)->getNextStation() != nullptr) {
			os << " --> " << (*it)->getNextStation()->getItemName();
		}
		else {
			os << " --> End of Line";
		}
		os << '\n';
	}
}
