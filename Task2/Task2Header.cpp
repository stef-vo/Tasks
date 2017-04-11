#include "Task2Header.h"
#include "WrongDataType.h"

namespace ISXMetadata
{
Metadata::Metadata() : m_type(Type::UNDEFINED), var() {}
Metadata::Metadata(const Metadata& data)
{
	m_type = data.m_type;
	var = data.var;
}
Metadata::Metadata(Metadata&& data)
{
	this->var = std::move(data.var);
	this->m_type = std::move(data.m_type);
	data.m_type = Type::UNDEFINED;
}
Metadata::Metadata(bool bool_data) : m_type(Type::BOOL)
{
	var.bool_data = bool_data;
}
Metadata::Metadata(short short_data) : m_type(Type::SHORT)
{
	var.short_data = short_data;
}
Metadata::Metadata(int int_data) : m_type(Type::INT)
{
	var.int_data = int_data;
}
Metadata::Metadata(long long_data) : m_type(Type::LONG)
{
	var.long_data = long_data;
}
Metadata::Metadata(long long long_long_data) : m_type(Type::LONG_LONG)
{
	var.long_long_data = long_long_data;
}
Metadata::Metadata(char char_data) : m_type(Type::CHAR)
{
	var.char_data = char_data;
}
Metadata::Metadata(wchar_t wchar_t_data) : m_type(Type::WCHAR_T)
{
	var.wchar_t_data = wchar_t_data;
}
Metadata::Metadata(float float_data) : m_type(Type::FLOAT)
{
	var.float_data = float_data;
}
Metadata::Metadata(double double_data) : m_type(Type::DOUBLE)
{
	var.double_data = double_data;
}
Metadata::Metadata(long double long_double_data) : m_type(Type::LONG_DOUBLE)
{
	var.long_double_data = long_double_data;
}
Metadata:: ~Metadata() {}

Metadata& Metadata::operator=(const Metadata& rhs) 
{
	if (this != &rhs)
		var = rhs.var;
	return *this;
}

Metadata& Metadata::operator = (Metadata&& rhs) 
{
	if (this != &rhs)
	{
		this->var = std::move(rhs.var);
		this->m_type = std::move(rhs.m_type);
		rhs.m_type = Type::UNDEFINED;
	}
	return *this;
}


const char* Metadata::get_TypeName() const
{
	switch (m_type)
	{
	case Type::BOOL: return "bool"; 
	case Type::SHORT: return "short"; 
	case Type::INT: return "int"; 
	case Type::LONG: return "long"; 
	case Type::LONG_LONG: return "long long"; 
	case Type::CHAR: return "char"; 
	case Type::WCHAR_T: return "wchar_t"; 
	case Type::FLOAT: return "float"; 
	case Type::DOUBLE: return "double"; 
	case Type::LONG_DOUBLE: return "long double";
	case Type::UNDEFINED: return "undefined";
	defaut: return "undefined";
}
}


void swap(Metadata& lhs, Metadata& rhs)
{
	std::swap(lhs.var, rhs.var);
	std::swap(lhs.m_type, rhs.m_type);
}


bool Metadata::get_Bool() const
{
	if (m_type != Type::BOOL)
		throw WrongDataType();
	else
		return var.bool_data;
}
short Metadata::get_Short() const
{
	if (m_type != Type::SHORT)
		throw WrongDataType();
	else
		return var.short_data;
}
int Metadata::get_Int() const
{
	if (m_type != Type::INT)
		throw WrongDataType();
	else
		return var.int_data;
}
long Metadata::get_Long() const
{
	if (m_type != Type::LONG)
		throw WrongDataType();
	else
		return var.long_data;
}
long long Metadata::get_LongLong() const
{
	if (m_type != Type::LONG_LONG)
		throw WrongDataType();
	else
		return var.long_long_data;
}
char Metadata::get_Char() const
{
	if (m_type != Type::CHAR)
		throw WrongDataType();
	else
		return var.char_data;
}
wchar_t Metadata::get_WcharT() const
{
	if (m_type != Type::WCHAR_T)
		throw WrongDataType();
	else
		return var.wchar_t_data;
}
float Metadata::get_Float() const
{
	if (m_type != Type::FLOAT)
		throw WrongDataType();
	else
		return var.float_data;
}
double Metadata::get_Double() const
{
	if (m_type != Type::DOUBLE)
		throw WrongDataType();
	else
		return var.double_data;
}
long double Metadata::get_LongDouble() const
{
	if (m_type != Type::LONG_DOUBLE)
		throw WrongDataType();
	else
		return var.long_double_data;
}


std::ostream& operator<<(std::ostream& os, const Metadata  &rhs)
{
	if (rhs.get_Type() == Type::UNDEFINED)
	{
		os <<  "Impossible to print data.\n";
	}
	else
	{
		os << rhs.get_TypeName() << "(";
		switch (rhs.get_Type())
		{
		case Type::BOOL: os << rhs.get_Bool(); break;
		case Type::SHORT: os << rhs.get_Short(); break;
		case Type::INT: os << rhs.get_Int(); break;
		case Type::LONG: os << rhs.get_Long(); break;
		case Type::LONG_LONG:  os << rhs.get_LongLong(); break;
		case Type::CHAR:  os << rhs.get_Char(); break;
		case Type::WCHAR_T:  os << rhs.get_WcharT(); break;
		case Type::FLOAT:  os << rhs.get_Float(); break;
		case Type::DOUBLE:  os <<  rhs.get_Double(); break;
		case Type::LONG_DOUBLE:  os << rhs.get_LongDouble();break;
		case Type::UNDEFINED:  os << "Impossible to print data.";break;
		default: os << "Impossible to print data.";
		} // end of switch
		os << ")" << std::endl;
	} // end of else
	return os;
} // end of method

Type Metadata::get_Type() const
{
	return m_type;
}

} // end of namespace
