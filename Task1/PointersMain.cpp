#include <iostream>
#include "Pointers.h"
using namespace std;


int main()
{
	char** my_list = (char**)malloc(sizeof(char*));
	
	cout << "Initializing list. \n";
	StringListInit(&my_list);
	cout << "List size is " << StringListSize(&my_list) << "\n";

	cout << "\nAdding strings: \n";
	
	char* buffer = (char*)malloc(8);
	if (buffer != NULL)
	{
		strcpy(buffer, "string1");
		StringListAdd(&my_list, buffer);
		strcpy(buffer, "string2");
		StringListAdd(&my_list, buffer);
		strcpy(buffer, "string3");
		StringListAdd(&my_list, buffer);
		strcpy(buffer, "string4");
		StringListAdd(&my_list, buffer);
		strcpy(buffer, "string5");
		StringListAdd(&my_list, buffer);
		strcpy(buffer, "string6");
		StringListAdd(&my_list, buffer);
		strcpy(buffer, "string7");
		StringListAdd(&my_list, buffer);
		strcpy(buffer, "string8");
		StringListAdd(&my_list, buffer);
	}
	else
	{
		"\n Buffer list is not created \n";
	}

	free(buffer);

	PrintList(&my_list); cout << "\n";
	cout << "List size is " << StringListSize(&my_list) << "\n";

	cout << "Adding string 1:\n";
	StringListAdd(&my_list,"string1");
	PrintList(&my_list); cout << '\n';
	cout << "List size is " << StringListSize(&my_list) << "\n\n";

	cout << "Adding string 2:\n";
	StringListAdd(&my_list,"string2");
	PrintList(&my_list); cout << '\n';
	cout << "List size is " << StringListSize(&my_list) << "\n\n";

	cout << "Adding string 3:\n";
	StringListAdd(&my_list,"string3");
	PrintList(&my_list); cout << '\n';
	cout << "List size is " << StringListSize(&my_list) << "\n\n";

	cout << "Adding strings 4, 2, 3, 4, 5, 2, 1, 6:\n";
	StringListAdd(&my_list,"string4");
	StringListAdd(&my_list,"string2");
	StringListAdd(&my_list,"string3");
	StringListAdd(&my_list,"string4");
	StringListAdd(&my_list,"string5");
	StringListAdd(&my_list,"string2");
	StringListAdd(&my_list,"string1");
	StringListAdd(&my_list,"string6");
	PrintList(&my_list); cout << '\n';
	cout << "List size is " << StringListSize(&my_list) << "\n\n";

	

	cout << "First occurance of string3:\n";
	cout << "position of string 3 = " << StringListIndexOf(&my_list, "string3") << "\n\n";

	cout << "First occurance of string4:\n";
	cout << "position of string 4 = " << StringListIndexOf(&my_list, "string4") << "\n\n";

	cout << "First occurance of string10:\n";
	cout << "position of string 10 = " << StringListIndexOf(&my_list, "string10") << "\n\n";

	cout << "Replace string1 with string4:" << "\n";
	StringListReplaceInStrings(&my_list, "string1", "string4");
	PrintList(&my_list); cout << '\n';
	cout << "List size is " << StringListSize(&my_list) << "\n\n";

	cout << "Replace string2 with string7:" << "\n";
	StringListReplaceInStrings(&my_list, "string2", "string7");
	PrintList(&my_list); cout << '\n';
	cout << "List size is " << StringListSize(&my_list) << "\n\n";

	cout << "Sorting list (bubble sort):\n";
	StringListSort(&my_list);
	PrintList(&my_list); cout << '\n';
	cout << "List size is " << StringListSize(&my_list) << "\n\n";


	cout << "Adding strings 2, 2, 5, 3, 3, 4\n";
	StringListAdd(&my_list,"string2");
	StringListAdd(&my_list,"string2");
	StringListAdd(&my_list,"string5");
	StringListAdd(&my_list,"string3");
	StringListAdd(&my_list,"string3");
	StringListAdd(&my_list,"string4");
	PrintList(&my_list); cout << '\n';
	cout << "List size is " << StringListSize(&my_list) << "\n\n";

	cout << "\nRemoving string4 from the list:\n";
	StringListRemove(&my_list, "string4");
	PrintList(&my_list); cout << '\n';
	cout << "List size is " << StringListSize(&my_list) << "\n\n";

	cout << "Removing duplicates:\n";
	StringListRemoveDuplicates(&my_list);
	PrintList(&my_list); cout << '\n';
	cout << "List size is " << StringListSize(&my_list) << "\n\n";
	

	cout << "Destroying the list.\n";
	StringListDestroy(&my_list);

	free(my_list);

	cout << "\n\n";
	return 0;
}
