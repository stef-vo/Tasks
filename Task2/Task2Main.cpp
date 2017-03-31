#include <iostream>
#include "Task2Header.h"
#include "WrongDataType.h"

using namespace ISXMetadata;

int main()
{
	std::cout << "Using of constructors:" << std::endl << std::endl;
	
	std::cout << "Default constructor \"Metadata var0;\"   ";
	Metadata var0;
	std::cout << var0 << std::endl;

	std::cout << "Parametrized constructors: \n \"Metadata var1(true);\"   ";
	Metadata var1(true);
	std::cout << var1 << std::endl;

	std::cout << "Parametrized constructors: \n \"Metadata var2(false);\"   ";
	Metadata var2(false);
	std::cout << var2 << std::endl;

	std::cout << "Copy assignment operator: \n \"Metadata var3 = var2;\"   ";
	Metadata var3 = var2;
	std::cout << var3 << std::endl;

	std::cout << "Parametrized constructors: \n \"Metadata var4(1);\"   ";
	Metadata var4(1);
	std::cout << var4 << std::endl;

	std::cout << "var4 = 1.5;" << std::endl;
	var4 = 1.5;
	std::cout << var4 << std::endl;

	std::cout << "var4 = \'c\';" << std::endl;
	var4 = 'c';
	std::cout << var4 << std::endl;

	
	std::cout << "Parametrized constructors: \n \"Metadata var5(1.5);\"   ";
	Metadata var5(1.5);
	std::cout << var5 << std::endl;

	std::cout << "Using of exceptions: \n \"int int_number = var5.get_Int();\"   ";
	try
	{
		int int_number = var5.get_Int();
	}
	catch (WrongDataType& bt)
	{
		std::cout << bt.what() << std::endl;
	}

	std::cout << "\nCopy assignment operator: \n \"Metadata var6 = (int)('X');\"   ";
	Metadata var6 = (int)('X');
	std::cout << var6 << std::endl;

	std::cout << "Copy assignment operator: \n \"Metadata var7 = (char)('X');\"   ";
	Metadata var7 = (char)('X');
	std::cout << var7 << std::endl;
	
	std::cout << "Parametrized constructors: \n \"Metadata var8(1.5L);\"   ";
	Metadata var8(1.5L);
	std::cout << var8 << std::endl;

	std::cout << "Swapping of var7 and var8:\n\n";
	std::swap(var7, var8);

	std::cout << "Var7: " << var7;
	std::cout << "Var8: " << var8 << std::endl;

	std::cout << "Getting type_names:\n";
	std::cout << "Type of var7 is " << var7.get_TypeName() << std::endl;
	std::cout << "Type of var8 is " << var8.get_TypeName() << std::endl;

	std::cout << "\nMove assignment operator:\n\n";
	std::cout << "Metadata var9(std::move(var8));\n";
	std::cout << "var8 = std::move(var9);\n\n";
	
	Metadata var9(std::move(var8));
	var8 = std::move(var9);

	std::cout << "Var9: " << var9;
	std::cout << "Var8: " << var8 << std::endl;

	return 0;
}