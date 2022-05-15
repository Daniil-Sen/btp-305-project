// Name: Daniil Sen
// Seneca Student ID: 160970190
// Seneca email: dsen5@myseneca.ca
// Date of completion: 11/27/2021
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#ifndef SDDS_CUSTOMER_ORDER_H_
#define SDDS_CUSTOMER_ORDER_H_

#include <iostream>
#include "Station.h"

namespace sdds {
	struct Item {
		std::string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };

		Item(const std::string& src) : m_itemName(src) {};
	};

	class CustomerOrder {
	public:
		CustomerOrder();
		CustomerOrder(const CustomerOrder& other); // copy constructor.
		CustomerOrder(const std::string& record);
		CustomerOrder(CustomerOrder&&) noexcept;
		~CustomerOrder();
		
		bool isFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;

		CustomerOrder& operator= (CustomerOrder&&) noexcept;
	private:
		std::string m_name;
		std::string m_product;
		size_t m_cntItem;
		Item** m_lstItem;
		static size_t m_widthField;
	};
}

#endif