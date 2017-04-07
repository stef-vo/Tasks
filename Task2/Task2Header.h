#pragma once

#include <ostream>

namespace ISXMetadata
{
class WrongDataType;

enum class Type
{
    UNDEFINED,
    BOOL,
    SHORT,
    INT, 
    LONG, 
    LONG_LONG, 
    CHAR, 
    WCHAR_T, 
    FLOAT, 
    DOUBLE, 
    LONG_DOUBLE
};

class Metadata
{
public:
	/* Default constructor. */
	Metadata(); 
	/* Copy constructor. */
	Metadata(const Metadata&); 
	/* Move constructor. */
	Metadata(Metadata&&); 
	/* Parametrized constructors. */
	Metadata(bool bool_data);
	Metadata(short short_data);
	Metadata(int int_data);
	Metadata(long long_data);
	Metadata(long long long_long_data);
	Metadata(char char_data);
	Metadata(wchar_t wchar_t_data);
	Metadata(float float_data);
	Metadata(double double_data);
	Metadata(long double long_double_data);
	/* Destructor. */
	~Metadata();

	/* Copy assignment operator. */
	Metadata& operator=(const Metadata& rhs); 
	/* Move assignment operator. */
	Metadata& operator=(Metadata&& rhs);
		
	/* Gets type name. */
	const char* get_TypeName() const;

	/* Gets data. */
	bool get_Bool() const;
	short get_Short() const;
	int get_Int() const;
	long get_Long() const;
	long long get_LongLong() const;
	char get_Char() const;
	wchar_t get_WcharT() const;
	float get_Float() const;
	double get_Double() const;
	long double get_LongDouble() const;

	/* Overloads <<.  */
	friend std::ostream& operator << (std::ostream& os, const Metadata& rhs);

	/* Swaps data. */
	friend void swap(Metadata& lhs, Metadata& rhs);

	/* Gets the type of enum. */ 
	Type get_Type() const;
		
private:
	/* Type of enum. */ 
	Type m_type;
	/* Data. */
	union Var
	{
		bool bool_data;
		short short_data;
		int int_data;
		long long_data;
		long long long_long_data;
		char char_data;
		wchar_t wchar_t_data;
		float float_data;
		double double_data;
		long double long_double_data;
	};
	Var var;
};
}
