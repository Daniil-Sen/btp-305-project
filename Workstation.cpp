// Name: Daniil Sen
// Seneca Student ID: 160970190
// Seneca email: dsen5@myseneca.ca
// Date of completion: 12/04/2021
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#include "Workstation.h"

void sdds::Workstation::fill(std::ostream& os) {
	if (!this->m_orders.empty()) {
		this->m_orders.front().fillItem(*this, os);
	}
}

bool sdds::Workstation::attemptToMoveOrder() {
	bool moved = false;
	if (!m_orders.empty() && (m_orders.front().isItemFilled(this->getItemName()) || this->getQuantity() <= 0)) {
		if (m_pNextStation != nullptr) {
			*m_pNextStation += std::move(m_orders.front());
		}
		else if (m_orders.front().isFilled()) {
			completed.push_back(std::move(m_orders.front()));
		}
		else {
			incomplete.push_back(std::move(m_orders.front()));
		}
		m_orders.pop_front();
		moved = true;
	}
	return moved;
}

void sdds::Workstation::setNextStation(Workstation* station = nullptr) {
	this->m_pNextStation = station;
}

sdds::Workstation* sdds::Workstation::getNextStation() const {
	return this->m_pNextStation;
}

void sdds::Workstation::display(std::ostream& os) const {
	sdds::Station::display(os, true);
	os << " --> ";
	Workstation* temp = m_pNextStation;
	if (temp != nullptr) {
		while (temp != nullptr) {
			Station* s = temp;
			s->display(os, true);
			os << " --> ";
			temp = temp->m_pNextStation;
		}
	}
	os << " END OF LINE\n";
}

sdds::Workstation& sdds::Workstation::operator+=(CustomerOrder&& newOrder) {
	this->m_orders.push_back(std::move(newOrder)); // might need rework with move
	return *this;
}
