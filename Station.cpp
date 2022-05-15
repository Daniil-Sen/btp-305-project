// Name: Daniil Sen
// Seneca Student ID: 160970190
// Seneca email: dsen5@myseneca.ca
// Date of completion: 11/20/2021
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#include <iomanip>
#include <iostream>

#include "Station.h"
#include "Utilities.h"

size_t sdds::Station::m_widthField = 0;
size_t sdds::Station::id_generator = 0;

sdds::Station::Station(const std::string& record) {
	m_id = ++id_generator;

	m_itemName = std::string();
	m_description = std::string();
	m_nextSerialNumber = 0;
	m_itemsInStock = 0;
	
	if (!record.empty()) {
		Utilities util;
		size_t pos = 0;
		bool more = true;
		
		m_itemName = util.extractToken(record, pos, more);
		if (more) {
			m_nextSerialNumber = std::stoi(util.extractToken(record, pos, more));
		}
		if (more) {
			m_itemsInStock = std::stoi(util.extractToken(record, pos, more));
		}
		if (more) {
			m_widthField = std::max(m_widthField, util.getFieldWidth());
			m_description = util.extractToken(record, pos, more);
		}
	}
}

const std::string& sdds::Station::getItemName() const {
	return m_itemName;
}

size_t sdds::Station::getNextSerialNumber() {
	return m_nextSerialNumber++;
}

size_t sdds::Station::getQuantity() const {
	return m_itemsInStock;
}

void sdds::Station::updateQuantity() {
	if (m_itemsInStock > 0) {
		m_itemsInStock--;
	}
}

void sdds::Station::display(std::ostream& os, bool full) const {
	if (!full) {
		os << "[" << std::setw(3) << std::setfill('0') << std::right << m_id << "] Item: "
			<< std::setw(m_widthField) << std::setfill(' ') << std::left << m_itemName << " ["
			<< std::setw(6) << std::setfill('0') << std::right << m_nextSerialNumber << "]\n";
	}
	else {
		os << "[" << std::setw(3) << std::setfill('0') << std::right << m_id << "] Item: "
			<< std::setw(m_widthField) << std::setfill(' ') << std::left << m_itemName << " ["
			<< std::setw(6) << std::setfill('0') << std::right << m_nextSerialNumber << "] Quantity: "
			<< std::setw(m_widthField) << std::setfill(' ') << std::left << m_itemsInStock
			<< " Description: " << m_description << std::endl;
	}
}
