// Name: Daniil Sen
// Seneca Student ID: 160970190
// Seneca email: dsen5@myseneca.ca
// Date of completion: 12/04/2021
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#ifndef SDDS_LINEMANAGER_H_
#define SDDS_LINEMANAGER_H_

#include <vector>

#include "Workstation.h"

namespace sdds {
	class LineManager {
	public:
		LineManager(const std::string& file, 
			const std::vector<Workstation*>& stations);
		void linkStations();
		bool run(std::ostream& os);
		void display(std::ostream& os) const;

	private:
		std::vector<Workstation*> activeLine;
		size_t m_cntCustomerOrder;
		Workstation* m_firstStation;
	};
}

#endif // !SDDS_LINEMANAGER_H_
