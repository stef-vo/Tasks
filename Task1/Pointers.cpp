#include "Pointers.h"

/* Initializes list */
void StringListInit(char*** list)
{
    if (list != NULL)
	{
		char** tmp = (char**)calloc(1, sizeof(char*));
		if (tmp != NULL)
		{
			*list = tmp;
			(*list)[0] = "";
			tmp = NULL;			
		}
		else
		{
			std::cout << "\n List is not initialized \n";
			return;
		}
	}
	else
	{
		std::cout << "\n List is not initialized. \n";
		return;
	}	
}

/*Returns the number of items in the list.*/
int StringListSize(char*** list)
{
	int i = 0;
	while((*list)[i][0] != '\0')
		i++;
	return i;
}

/* Inserts value at the end of the list. */
void StringListAdd(char*** list, char* str)
{
	int list_size = StringListSize(list);
	if (list != NULL)
	{
		char** tmp = (char**)realloc(*list, (list_size + 2) * sizeof(char*));
		if (tmp != NULL)
		{
			*list = tmp;
			tmp = NULL;
		}
		else
		{
			std::cout << "\n Cannot add string. Not enough memory. \n";
			return;
		}
		
		char* tmp2 = (char*)calloc(strlen(str) + 1, sizeof(char));
		if (tmp2 != NULL)
		{
			(*list)[list_size] = tmp2;
			tmp2 = NULL;
		}
		else
		{
			std::cout << "\n Can not add string. Not enough memory. \n";
			return;
		}
		
		strcpy((*list)[list_size], str);
		(*list)[list_size + 1] = "";	
	}
	else
	{
		std::cout << "\n List is not initialized \n";
		return;
	}
}


/* Returns the index position of the first occurrence of str in the list. */
int StringListIndexOf(char*** list, char* str)
{
	if (list != NULL)
	{
		int position = -1;
		int list_size = StringListSize(list);
		for (int i = 0; i < list_size; ++i)
		{
			if (strcmp((*list)[i], str) == 0)
			{
				position = i;
				break;
			}
		}
		return position;
	}
	else
	{
		std::cout << "\n List is not initialized \n";
		return -1;
	}
}


/* Replaces every occurrence of the before, in each of the string lists's strings,
   with after. */
void StringListReplaceInStrings(char*** list, char* before, char* after)
{
	if (list != NULL && *before != '\0' && *after != '\0')
	{
		int list_size = StringListSize(list);
		for (int i = 0; i < list_size; ++i)
			if (strcmp((*list)[i], before) == 0)
			{
				char* tmp = (char*)realloc((*list)[i], (strlen(after) + 1) * sizeof(char));
				if (tmp != NULL)
				{
					(*list)[i] = tmp;
					strcpy((*list)[i], after);
					tmp = NULL;
				}
				else
				{
					std::cout << "\n Not enough memory. \n";
					return;
				}
			}
	}
	else
	{
		std::cout << "\n List is not initialized or before_str is zero or after_string is zero. \n";
		return;
	}
}


/* Sorts the list of strings in ascending order (bubble sort) */
void StringListSort(char*** list)
{
	if (list != NULL)
	{
		int list_size = StringListSize(list);
		if (list_size == 0)
		{
			std::cout << "\nNo strings to sort\n";
			return;
		}
		else
		{
			char* tmp_string;
			bool if_swapped = false;
 			while (!if_swapped)
			{
				if_swapped = true;
				for (int i = 0; i < (list_size - 1); ++i)
					if (strcmp((*list)[i], (*list)[i + 1]) > 0)
					{
						char* tmp1 = (char*)calloc(strlen((*list)[i]) + 1, sizeof(char));
						if (tmp1 == NULL)
						{
							std::cout << "\n Not enough memory. \n";
							tmp1 = NULL;
							return;
						}
						else
						{
							strcpy(tmp1, (*list)[i]);
							char* tmp2 = (char*)realloc((*list)[i], (strlen((*list)[i + 1]) + 1) * sizeof(char));
							if (tmp2 == NULL)
							{
								std::cout << "\n Not enough memory. \n";
								return;
							}
							else
							{
								(*list)[i] = tmp2;
								strcpy((*list)[i], (*list)[i + 1]);
								tmp2 = NULL;
								char* tmp3 = (char*)realloc((*list)[i + 1], (strlen((*list)[i]) + 1) * sizeof(char));
								if (tmp3 == NULL)
								{
									std::cout << "\n Not enough memory. \n";
									return;
								}
								else
								{
									(*list)[i + 1] = tmp3;
									strcpy((*list)[i + 1], tmp1);
									tmp3 = NULL;
									tmp1 = NULL;
								}
							}
						}
						if_swapped = false;
					}
			}
		}
	}
	else
	{
		std::cout << "\n List is not initialized. \n";
		return;
	}
}
							
/* Removes all occurrences of str in the list. */
void StringListRemove(char*** list, char* str)
{
	if (list != NULL)
	{
		int list_size = StringListSize(list);
		if (*list == NULL || list_size == 0 || strcmp(str, "") == 0)
		{
			std::cout << "\nNo strings to remove\n";
			return;
		}
		else
		{
			int next_str_length;
			while(1)
			{
				int index = StringListIndexOf(list, str);
				if (StringListIndexOf(list, str) != -1)
				{
					for (int i = index; i < list_size; i++)
					{
						next_str_length = strlen((*list)[i + 1]);
						char* tmp = (char*)realloc((*list)[i], (next_str_length + 1) * sizeof(char));
						if (tmp != NULL)
						{
							(*list)[i] = tmp;
							tmp = NULL;
							strcpy((*list)[i], (*list)[i + 1]);
						}
						else
						{
							std::cout << "\n Not enough memory. \n";
							return;
						}
					}
				}
				else
				{
					break;		
				}
			}
		}
		int strings_found = list_size - StringListSize(list);
		std::cout << "\n" << str << " found: " << strings_found << " items.\n";
		for (int i = StringListSize(list) + 2; i <= list_size + 1; ++i)
		{
			(*list)[i] = NULL;
		}
		
		char** tmp2 = (char**)realloc(*list, (StringListSize(list) + 1) * sizeof(char*));
		if (tmp2 != NULL)
		{
			*list = tmp2;
			tmp2 = NULL;
		}
		else
		{
			std::cout << "\n Not enough memory. \n";
			return;
		}
	}
	else
	{
		std::cout << "\n List is not initialized. \n";
		return;
	}
}


/* Removes duplicate entries from the list. */
void StringListRemoveDuplicates(char*** list)
{
	if (list == NULL)
	{
		std::cout << "\n List is not initialized. \n";
		return;
	}
	else
	{
		int list_size = StringListSize(list);
		int size;
		if (list_size == 0)
		{
			std::cout << "\nList is empty. Nothing to remove. \n";
			return;
		}
		else
		{
			size = list_size;
			int next_str_length;
			for(int i = 0; i < size; ++i)
			{
				for (int j = i + 1; j < size; )
				{
					if (strcmp((*list)[i], (*list)[j]) == 0)
					{
						for (int k = j; k < size; ++k)
						{
							next_str_length = strlen((*list)[k + 1]);
							char* tmp = (char*)realloc((*list)[k], (next_str_length + 1) * sizeof(char));
							if (tmp != NULL)
							{
								(*list)[k] = tmp;
								strcpy((*list)[k], (*list)[k + 1]);
								tmp = NULL;
							}
							else
							{
								std::cout << "\nOut of memory.\n";
								return;
							}
						}
						--size;
					}
					else
					{
						++j;
					}
				}
			}
		}

		std::cout << "\nDuplicates found: " << list_size - size << "\n";
		for (int i = StringListSize(list) + 2; i <= list_size + 1; ++i)
		{
			(*list)[i] = NULL;
		}
		char** tmp = (char**)realloc(*list, (StringListSize(list) + 1) * sizeof(char*));
		if (tmp != NULL)
		{
			*list = tmp;
			tmp = NULL;
		}
		else
		{
			std::cout << "\n Not enough memory. \n";
			return;
		}

	}
}

/* Destroy list and set pointer to NULL. */
void StringListDestroy(char*** list)
{
	if (list != NULL)
	{
		int list_size = StringListSize(list);
		if (list_size != 0)
		{
			for (int i = 0; i <= list_size; ++i)
			{
				free((*list)[i]);
				(*list)[i] = NULL;
			}
			free(*list);
			*list = NULL;
		}
		else
		{
			std::cout << "\n List is empty. Nothing to destroy. \n";
			return;
		}
	}
	else
	{
		std::cout << "\n List is not initialized or already destroyed. \n";
		return;
	}
}

/* Prints the list of strings. */
void PrintList(char*** list)
{
	if (list != NULL)
	{
		int list_size = StringListSize(list);
		if (list_size != 0)
		{
			for (int word_index = 0; word_index < list_size; word_index++)
			std::cout << '\n' << "word[" << word_index << "] = " << (*list)[word_index];
		}
		else
		{
			std::cout << "\n Nothing to print. \n";
			return;
		}
	}
	else
	{
		std::cout << "\n List is not initialized. \n";
		return;
	}
}
