#include <boost/filesystem.hpp>
#include <thread>
#include <queue>
#include <mutex>

std::mutex create_queue_mutex;
std::mutex result_mutex;
std::mutex file_mutex;

using namespace std::chrono;

/* Creates queue of files Tasks with extensions ext_vector in directory dir. */
void CreateQueue(std::string dir, std::vector<std::string> ext_vector,
					  std::queue <std::string> & Tasks, unsigned & total_files)
{
	total_files = 0;
	boost::filesystem::recursive_directory_iterator current(dir);  
	boost::filesystem::recursive_directory_iterator end;
	for (; current != end; current++)
	{
		for (unsigned i = 0; i < ext_vector.size(); i++)
		{
			std::string ext(ext_vector[i]);
			if (boost::filesystem::is_regular_file(current->status())
				&& ext.compare((*current).path().extension().string()) == 0)
				{
					total_files++;
					create_queue_mutex.lock();
					Tasks.push((*current).path().string());
					create_queue_mutex.unlock();
				}
		}
	}
}

/* Checks if str is blank. */
bool IsBlank(const std::string & str)
{
	int n = str.length();
	for (int i = 0; i < n; ++i)
		if (!isspace(str[i]))
			return false;
	return true;
}

/* Counts lines in file. */
void CountLines(std::fstream & file, unsigned & lines, unsigned & code_lines,
	unsigned & blank_lines, unsigned & comment_lines)
{
    lines = 0;
	blank_lines = 0;
	comment_lines = 0;
	bool in_multi_line_comment = false;
	std::string line;
	file_mutex.lock();
	while(getline(file, line))
	{
		lines++;
		if (!in_multi_line_comment && line.find("/*") != std::string::npos)
			in_multi_line_comment = true;

		if (in_multi_line_comment || line.find("//") != std::string::npos)
			comment_lines++;

		if (in_multi_line_comment && line.find("*/") != std::string::npos)
			in_multi_line_comment = false;

		if (IsBlank(line))
		{
			blank_lines++;
		}
	}
	file_mutex.unlock();
	code_lines = lines - blank_lines - comment_lines;
}

/* Gets files from the queue. */
void GetResult(std::queue <std::string> & Tasks, unsigned & total_lines,
	unsigned & total_code_lines, unsigned & total_blank_lines,
	unsigned & total_comment_lines)
{
	unsigned lines;
	unsigned blank_lines;
	unsigned comment_lines;
	unsigned code_lines;
		
	total_lines = 0;
	total_blank_lines = 0;
	total_comment_lines = 0;
	total_code_lines = 0;

	while(!Tasks.empty())
	{
		std::string file_str(Tasks.front());
		std::fstream file;
		file.open(file_str);
		if (file.fail())
		{
			std::cout << "Problems with opening files.\n";
			return;
		}
		result_mutex.lock();
		CountLines(file, lines, code_lines, blank_lines, comment_lines);
		total_lines += lines;
		total_code_lines += code_lines;
		total_blank_lines += blank_lines;
		total_comment_lines += comment_lines;
		file.close();
		Tasks.pop();
		result_mutex.unlock();
	}
}

// Prints files info
void PrintResult(unsigned & total_files, unsigned & total_lines, unsigned & total_code_lines,
	unsigned & total_blank_lines, unsigned & total_comment_lines)
{
	std::ofstream output_file;
	output_file.open("E:\\info.txt");
	if (output_file.fail())
	{
		std::cout << "Impossible to create output file!\n";
	}
	output_file << "Total files: " << total_files << "\n";
	output_file << "Total lines: " << total_lines << "\n";
	output_file << "Total code lines: " << total_code_lines << "\n";
	output_file << "Total blank lines: " << total_blank_lines << "\n";
	output_file << "Total comment lines: " << total_comment_lines << "\n";
	output_file.close();
	std::cout << "Total files: " << total_files << "\n";
	std::cout << "Total lines: " << total_lines << "\n";
	std::cout << "Total code lines: " << total_code_lines << "\n";
	std::cout << "Total blank lines: " << total_blank_lines << "\n";
	std::cout << "Total comment lines: " << total_comment_lines << "\n";
}

int main()
{
	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	// Create vector of extensions
	std::vector<std::string> ext_vector;
	std::vector<std::string>::iterator it;
	ext_vector.push_back(".c");
	ext_vector.push_back(".cpp");
	ext_vector.push_back(".h");
	ext_vector.push_back(".hpp");

	std::cout << "The task is to print info about all the files\n";
	std::cout << "with the extensions ";
	for (it = ext_vector.begin(); it<ext_vector.end(); it++)
		std::cout << ' ' << *it;
	//std::cout << "\n";

    std::string dir("E:\\Boost\\boost_1_52_0\\boost\\asio"); // path to the root directory may be changed as you wish
	std::queue <std::string> file_names; // vector of file names with given extensions
	std::cout << "\n" << "in directory " << dir << "\n\n";
	std::cout << "Wait a little!" << "\n\n";
	unsigned num_files;
	CreateQueue(dir, ext_vector, file_names, num_files);
	
	unsigned total_lines;
	unsigned total_code_lines;
	unsigned total_blank_lines;
	unsigned total_comment_lines;

	GetResult(file_names, total_lines, total_code_lines, total_blank_lines, total_comment_lines);

	PrintResult(num_files, total_lines, total_code_lines, total_blank_lines, total_comment_lines);
	
	unsigned num_threads = std::thread::hardware_concurrency();

		std::thread *tt = new std::thread[num_threads];
		for (unsigned j = 0; j < num_threads; ++j)
		{
			tt[j] = std::thread(GetResult, std::ref(file_names), std::ref(total_lines),
				std::ref(total_code_lines), std::ref(total_blank_lines),
				std::ref(total_comment_lines));
		}

		for (unsigned j = 0; j < num_threads; ++j)
			tt[j].join();
		
		delete[] tt;
	
	std::cout << "\nIt took the program ";
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>( t2 - t1 ).count();
	std::cout << duration << " milliseconds to run with " << num_threads << " threads";
	std::cout << "\n\n";

	return 0;
}