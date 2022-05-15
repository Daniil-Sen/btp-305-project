// Name: Daniil Sen
// Seneca Student ID: 160970190
// Seneca email: dsen5@myseneca.ca
// Date of completion: 11/20/2021
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#include <stdexcept>

#include "Utilities.h"

char sdds::Utilities::m_delimiter = 1;

sdds::Utilities::Utilities() {
	m_widthField = 1;
}

void sdds::Utilities::setFieldWidth(size_t newWidth) {
	m_widthField = newWidth;
}

size_t sdds::Utilities::getFieldWidth() const {
	return m_widthField;
}

std::string sdds::Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
	if (str[next_pos] == m_delimiter) {
		more = false;
		throw std::runtime_error("error: pos is delimiter");
	}
	
	std::string substr;
	size_t initial = next_pos;
	
	while (str[next_pos] != m_delimiter && next_pos != str.length()) {
		next_pos++;
	}
	substr = str.substr(initial, next_pos - initial);
	m_widthField = std::max(m_widthField, next_pos - initial);
	if (str[next_pos] == m_delimiter) {
		next_pos++;
		more = true;
	}
	else {
		more = false;
	}
	return substr;
}

void sdds::Utilities::setDelimiter(char newDelimiter) {
	m_delimiter = newDelimiter;
}

char sdds::Utilities::getDelimiter() {
	return m_delimiter;
}
