// Name: Daniil Sen
// Seneca Student ID: 160970190
// Seneca email: dsen5@myseneca.ca
// Date of completion: 11/20/2021
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#ifndef SDDS_UTILITIES_H_
#define SDDS_UTILITIES_H_

#include <string>

namespace sdds {
	class Utilities {
	public:
		Utilities();

		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;
		std::string extractToken(const std::string& str,
			size_t& next_pos, bool& more);

		static void setDelimiter(char newDelimiter);
		static char getDelimiter();
	private:
		size_t m_widthField;

		static char m_delimiter;
	};
}

#endif // !SDDS_UTILITIES_H_