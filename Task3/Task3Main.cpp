
// version 5.0
#include <boost/filesystem.hpp> 
#include <vector>
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

// Counts the number of files with extensions from vector ext_vector
// in directory dir including subdirectories 
unsigned HowManyFiles(const std::string dir, const std::vector<std::string> ext_vector)
{    
    unsigned files_counter = 0;
	for (unsigned i = 0; i < ext_vector.size(); i++)
	{
		std::string ext(ext_vector[i]);
		boost::filesystem::recursive_directory_iterator current(dir);  
		boost::filesystem::recursive_directory_iterator end;
		for (; current != end; current++)
			if (boost::filesystem::is_regular_file(current->status()) && ext.compare((*current).path().extension().string()) == 0)
				files_counter++;           
	}
	return files_counter;
}

/* Checks if str is blank. */
bool isBlank(const std::string str)
{
	int n = str.length();
	for (int i = 0; i < n; ++i)
		if (!isspace(str[i]))
			return false;
	return true;
}

/* Counts blank lines in file_str.*/
unsigned CountBlankLines(const std::string file_str)
{
    unsigned blank_lines = 0;
	std::ifstream file;
	file.open(file_str, std::ifstream::in);
	std::string line;
	while(getline(file, line))
	{
		if (isBlank(line))
			blank_lines++;
	}
	file.close();
	return blank_lines;
}

/* Counts lines in comments. */
unsigned CountCommentLines(const std::string file_str)
{
    unsigned comments = 0;
	std::ifstream file;
	file.open(file_str, std::ifstream::in);
	std::string line;
	bool in_multi_line_comment = false;
	while(getline(file, line))
	{
		if (!in_multi_line_comment && line.find("/*") != std::string::npos)
        in_multi_line_comment = true;

		if (in_multi_line_comment || line.find("//") != std::string::npos)
        comments++;

		if (in_multi_line_comment && line.find("*/") != std::string::npos)
        in_multi_line_comment = false;
	}
	file.close();
	return comments;
}

/* Counts all the lines in file_str. */
unsigned CountAllLines(const std::string file_str)
{
    unsigned lines = 0;
	std::ifstream file;
	file.open(file_str, std::ifstream::in);
	std::string line;
	while(getline(file, line))
	{
		lines++;
	}
	file.close();
	return lines;
}

/* Counts code lines in file_str. */
unsigned CountCodeLines(const std::string file_str)
{
    return CountAllLines(file_str) - CountCommentLines(file_str) - CountBlankLines(file_str);
}


int main()
{   
	std::vector<std::string> ext_vector;
	std::vector<std::string>::iterator it;
	ext_vector.push_back(".c");
	ext_vector.push_back(".cpp");
	ext_vector.push_back(".h");
	ext_vector.push_back(".hpp");

	std::cout << "Extensions:\n";
	for (it = ext_vector.begin(); it<ext_vector.end(); it++)
		std::cout << ' ' << *it;
	std::cout << "\n\n";

    std::cout << "Files with these extensions found: ";
	std::string dir("E:\\Root");
	std::cout << HowManyFiles(dir, ext_vector);
	std::cout << "\n\n";

	std::string file_name("E:\\Root\\file.cpp");
	
	std::cout << "The number of blank lines in " << file_name << " is: ";
	std::cout << CountBlankLines(file_name);
	std::cout << "\n\n";

	std::cout << "The number of comment lines in " << file_name << " is: ";
	std::cout << CountCommentLines(file_name);
	std::cout << "\n\n";

	std::cout << "Total number of lines in " << file_name << " is: ";
	std::cout << CountAllLines(file_name);
	std::cout << "\n\n";


	std::cout << "Code lines in " << file_name << " are: ";
	std::cout << CountCodeLines(file_name);
	std::cout << "\n\n";

	return 0;
}

