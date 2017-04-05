#include "Header.h"

// Counts files 
int CountFiles(std::string dir, std::vector<std::string> ext_vector, std::vector <std::string> & file_names)
{    
	int files_counter = 0;
	for (int i = 0; i < ext_vector.size(); i++)
	{
		
		std::string ext(ext_vector[i]);
		boost::filesystem::recursive_directory_iterator current(dir);  
		boost::filesystem::recursive_directory_iterator end;
		for (; current != end; current++)
			if (boost::filesystem::is_regular_file(current->status()) && ext.compare((*current).path().extension().string()) == 0)
			{
				files_counter++;
				file_names.push_back((*current).path().string());
			}
	}
	return files_counter;
}

/* Checks if str is blank. */
bool IsBlank(const std::string str)
{
	int n = str.length();
	for (int i = 0; i < n; ++i)
		if (!isspace(str[i]))
			return false;
	return true;
}

/* Counts lines in file_str. */
void CountLines(std::string file_str, int & blank_lines, int & comment_lines, int & code_lines, int & all_lines)
{
	blank_lines = 0;
	comment_lines = 0;
	code_lines = 0;
	all_lines = 0;
	
	std::ifstream file;
	file.open(file_str, std::ifstream::in);
	if (file.fail())
	{
		std::cout << "Error opening files.\n";
		return;
	}

	std::string line;
	bool in_multi_line_comment = false;
	while(getline(file, line))
	{
		all_lines++;

		if (IsBlank(line))
		{
		blank_lines++;
		}
		else
		{
			if (!in_multi_line_comment && line.find("/*") != std::string::npos)
			in_multi_line_comment = true;

			if (in_multi_line_comment || line.find("//") != std::string::npos)
			comment_lines++;

			if (in_multi_line_comment && line.find("*/") != std::string::npos)
			in_multi_line_comment = false;
		}
	}
	code_lines = all_lines - blank_lines - comment_lines; 
	file.close();
	return;
}

