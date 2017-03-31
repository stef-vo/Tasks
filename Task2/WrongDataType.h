#pragma once

#include <exception>

namespace ISXMetadata
{
	class WrongDataType : public std::exception
	{
	public:	
		virtual const char* what() const throw()
		{
			return "Wrong data type!";
		}
	};
}