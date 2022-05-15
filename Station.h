// Name: Daniil Sen
// Seneca Student ID: 160970190
// Seneca email: dsen5@myseneca.ca
// Date of completion: 11/20/2021
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#ifndef SDDS_STATION_H_
#define SDDS_STATION_H_

#include <string>

namespace sdds {
	class Station {
	public:
		Station(const std::string& record);

		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	private:
		int m_id;
		std::string m_itemName;
		std::string m_description;
		size_t m_nextSerialNumber;
		size_t m_itemsInStock;

		static size_t m_widthField;
		static size_t id_generator;
	};
}

#endif // !SDDS_STATION_H_
