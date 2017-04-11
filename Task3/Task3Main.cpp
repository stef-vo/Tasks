#include "Header.h"

using namespace std::chrono;

int main()
{
	// Create vector of extensions
	std::vector<std::string> ext_vector;
	std::vector<std::string>::iterator it;
	ext_vector.push_back(".c");
	ext_vector.push_back(".cpp");
	ext_vector.push_back(".h");
	ext_vector.push_back(".hpp");

	std::cout << "The task is to print info about all the files\n";
	std::cout << "with the extensions ";
	for (it = ext_vector.begin(); it<ext_vector.end(); ++it)
		std::cout << ' ' << *it;
	
	std::string dir;
	unsigned input_counter = 0;
	const unsigned max_input_num = 2; 
	for (int i = 0; i <= max_input_num; ++i)
	{
		std::cout << "\n\n" << "Please input the correct path to root directory:";
		std::cout << "\n" << "For example: E:\\\\Boost\\\\boost_1_52_0" 
			<< " or E:/Boost/boost_1_52_0" << "\n";
		std::cin >> dir;

		if (boost::filesystem::is_directory(dir))
		{
			break;
		}
		else if (i == max_input_num)
		{
			std::cout << "\n\n" << "You couldn't input the right path to root directory." << "\n";
			std::cout << "Exit program." << "\n";
			return 1;
		}
	}
				
	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	std::queue <std::string> file_names; // vector of file names with given extensions
	std::cout << "\n" << "Wait a little!" << "\n\n";
	unsigned num_files;
	CreateQueue(dir, ext_vector, file_names, num_files);
	
	std::atomic<unsigned int> total_lines(0);
	std::atomic<unsigned int> total_code_lines(0);
	std::atomic<unsigned int> total_blank_lines(0);
	std::atomic<unsigned int> total_comment_lines(0);

	unsigned num_threads = std::thread::hardware_concurrency();

	std::thread *threads = new std::thread[num_threads];
	for (unsigned j = 0; j < num_threads; ++j)
	{
		threads[j] = std::thread(GetResult, std::ref(file_names), std::ref(total_lines),
			std::ref(total_code_lines), std::ref(total_blank_lines),
			std::ref(total_comment_lines));
	}

	for (unsigned j = 0; j < num_threads; ++j)
		threads[j].join();
		
	delete[] threads;


	std::cout << "\nIt took the program ";
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>( t2 - t1 ).count();
	std::cout << duration << " milliseconds to search with " << num_threads << " threads";
	std::cout << "\n\n";

	PrintResult(num_files, total_lines, total_code_lines, total_blank_lines, total_comment_lines,
		duration, num_threads);
	
	std::cout << "\n\n";

	return 0;
}