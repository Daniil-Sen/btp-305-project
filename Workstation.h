// Name: Daniil Sen
// Seneca Student ID: 160970190
// Seneca email: dsen5@myseneca.ca
// Date of completion: 12/04/2021
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#ifndef SDDS_WOKSTATION_H_
#define SDDS_WOKSTATION_H_

#include <deque>
#include <iostream>

#include "CustomerOrder.h"

namespace sdds {
	
	inline std::deque<CustomerOrder> pending;
	inline std::deque<CustomerOrder> completed;
	inline std::deque<CustomerOrder> incomplete;

	class Workstation : public Station {
	public:
		Workstation(const std::string& arg) : Station(arg), 
			m_pNextStation(nullptr) {
		}
		Workstation& operator=(const Workstation&) = delete;
		Workstation(Workstation&&) = delete;
		Workstation& operator=(Workstation&&) = delete;

		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station);
		Workstation* getNextStation() const;
		void display(std::ostream& os) const;
		Workstation& operator+=(CustomerOrder&& newOrder);
	private:
		std::deque<CustomerOrder> m_orders;
		Workstation* m_pNextStation;
	};
}

#endif