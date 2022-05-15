// Name: Daniil Sen
// Seneca Student ID: 160970190
// Seneca email: dsen5@myseneca.ca
// Date of completion: 11/27/2021
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#include <algorithm>
#include <iomanip>
#include <vector>

#include "CustomerOrder.h"
#include "Utilities.h"

size_t sdds::CustomerOrder::m_widthField = 0;

sdds::CustomerOrder::CustomerOrder() : m_lstItem(nullptr) {
	m_name = std::string();
	m_product = std::string();
	m_cntItem = 0;
	m_lstItem = nullptr;
}

sdds::CustomerOrder::CustomerOrder(const CustomerOrder& other) {
	throw std::runtime_error("No copy cunstructors allowed.");
}

sdds::CustomerOrder::CustomerOrder(const std::string& record) : m_lstItem(nullptr) {
	if (!record.empty()) {
		bool more = true;
		size_t pos = 0;
		Utilities util;
		std::vector<std::string> v;

		while (more) {
			v.push_back(util.extractToken(record, pos, more));
		}
		this->m_cntItem = v.size() - 2;
		this->m_lstItem = new Item * [m_cntItem];
		this->m_name = v[0];
		this->m_product = v[1];
		// reused pos
		for (size_t i = 0, pos = 2; i < this->m_cntItem; ++i, ++pos) {
			this->m_lstItem[i] = new Item(v[pos]);
			this->m_widthField = std::max(this->m_widthField, v[pos].size());
		}
		this->m_widthField = std::max(this->m_widthField, util.getFieldWidth());
	}
}

sdds::CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept : m_lstItem(nullptr) {
	*this = std::move(other);
}

sdds::CustomerOrder::~CustomerOrder() {
	if (m_lstItem != nullptr) {
		for (size_t i = 0u; i < m_cntItem; ++i)
			if (m_lstItem[i] != nullptr)
				delete m_lstItem[i];
		delete[] m_lstItem;
	}
}

bool sdds::CustomerOrder::isFilled() const {
	return m_lstItem != nullptr ? std::all_of(&m_lstItem[0],
		&m_lstItem[0] + m_cntItem, [](Item* item) { return item->m_isFilled; }) : false;
}

bool sdds::CustomerOrder::isItemFilled(const std::string& itemName) const {
	auto filled = [&](Item* item) {
		bool isFilled = true;
		if (item->m_itemName == itemName) {
			isFilled = item->m_isFilled;
		}
		return isFilled;
	};
	return m_lstItem != nullptr ? std::all_of(&m_lstItem[0],
		&m_lstItem[0] + m_cntItem, filled) : false;
}

void sdds::CustomerOrder::fillItem(Station& station, std::ostream& os) {
	// had to modify this code as previous code block did not produce desired output for ms3 but did for ms2.
	std::transform(&m_lstItem[0], &m_lstItem[0] + m_cntItem, &m_lstItem[0], [&](Item* item) {
		if (station.getItemName() == item->m_itemName) {
			if (station.getQuantity() > 0) {
				item->m_serialNumber = station.getNextSerialNumber();
				station.updateQuantity();
				item->m_isFilled = true;
				std::cout << "    Filled " << m_name << ", " << m_product << " [" << station.getItemName() << "]\n";
			}
			else {
				std::cout << "    Unable to fill " << m_name << ", " << m_product << " [" << station.getItemName() << "]\n";
			}
		}
		return item;
		});
}

void sdds::CustomerOrder::display(std::ostream& os) const {
	auto print = [&](Item* item) {
		os << "[" << std::setfill('0') << std::setw(6) << std::right << item->m_serialNumber << "] ";
		os << std::setfill(' ') << std::setw(CustomerOrder::m_widthField) << std::left << item->m_itemName << " - ";
		os << (!item->m_isFilled ? "TO BE FILLED" : "FILLED") << '\n';
	};
	os << this->m_name << " - " << this->m_product << '\n';
	std::for_each(&this->m_lstItem[0], &this->m_lstItem[0] + this->m_cntItem, print);
}

sdds::CustomerOrder& sdds::CustomerOrder::operator=(CustomerOrder&& other) noexcept {
	this->m_name = other.m_name;
	this->m_product = other.m_product;

	/*other.m_name = std::string();
	other.m_product = std::string();
	other.m_cntItem = 0;*/

	if (this->m_lstItem != nullptr) {
		for (size_t i = 0u; i < this->m_cntItem; ++i)
			if (this->m_lstItem[i] != nullptr)
				delete this->m_lstItem[i];
		delete[] this->m_lstItem;
	}
	this->m_cntItem = other.m_cntItem;
	this->m_lstItem = other.m_lstItem;
	other.m_lstItem = nullptr;
	return *this;
}
