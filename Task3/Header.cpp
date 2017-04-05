#include "Header.h"

// Counts the number of files with extensions from vector ext_vector
// in directory dir including subdirectories 
unsigned HowManyFiles(const std::string dir, const std::vector<std::string> ext_vector,
					  std::vector <std::string> & file_names)
{    
    unsigned files_counter = 0;
	for (unsigned i = 0; i < ext_vector.size(); i++)
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
		lines++;
	file.close();
	return lines;
}

/* Counts code lines in file_str. */
unsigned CountCodeLines(const std::string file_str)
{
    return CountAllLines(file_str) - CountCommentLines(file_str) - CountBlankLines(file_str);
}

/* Gets information on file_str. */
void GetFileInfo(const std::string file_str, unsigned& all_lines, unsigned& code_lines,
					 unsigned& blank_lines, unsigned& comment_lines)
{
    all_lines = CountAllLines(file_str);
	code_lines = CountCodeLines(file_str);
	blank_lines = CountBlankLines(file_str);
	comment_lines = CountCommentLines(file_str);
}