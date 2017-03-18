#include <iostream>
#include <fstream> // std::fstream
#include <string>  // std::string
#include <sstream> // std::stringstream
#include <vector>  // std::vector
#include <utility> // std::pair
#include <thread>  // std::this_thread::sleep_for
#include <chrono>  // std::chrono::seconds
#include <iomanip> // std::setprecision

// Struct to save informations about cpu
struct CpuInfo{
	std::string cpu;
	double active;
	double total;

	CpuInfo(std::string _cpu) : cpu{_cpu}, active{0}, total{0}{}
};

int main(int argn, char * argv[]){
	
	int sleep_time = 1000;

	// Setting interval time to get cpu info
	if(argn > 1){
		sleep_time = atoi(argv[1]) * 1000;
	}

	// Defining path file
	std::string path = "/proc/stat";
	std::string input, cpu;
	double usage;
	std::ifstream cpu_status_file;
	std::stringstream ss;
	
	std::vector< CpuInfo > prev_cpu_usage;
	std::vector< CpuInfo > curr_cpu_usage;

	bool first_time = true;
	while(true){
		cpu_status_file.open(path, std::ifstream::in);
		cpu = ""; usage = 0;
		// Reading /proc/stat file 
		while(getline(cpu_status_file, input)){
			ss << input;
			ss >> cpu;
			// Checking if all cpus was read
			if(cpu.compare("intr") == 0) {
				ss.str(std::string());
				ss.clear();
				break;
			}else{
				// Storing current use of each cpu 		
				curr_cpu_usage.push_back(CpuInfo(!cpu.compare("cpu") ? "Total" : cpu));
				for(int i = 0; i < 4; ++i){
					ss >> usage;
					if(i < 3) curr_cpu_usage.back().active += usage;
					else curr_cpu_usage.back().total = curr_cpu_usage.back().active + usage;
				}
				ss.str(std::string());
				ss.clear();
			}
		}
		cpu_status_file.close();

		if(first_time){
			prev_cpu_usage = curr_cpu_usage;
			first_time = false;
		}else{
			// Printing cpu usage using prev_cpu_usage as reference (The same form of top and htop applications)
			for(int i = 0; i < curr_cpu_usage.size(); ++i)
				std::cout << curr_cpu_usage[i].cpu << ": " << std::setprecision(3) << 100 * (curr_cpu_usage[i].active - prev_cpu_usage[i].active) / (curr_cpu_usage[i].total - prev_cpu_usage[i].total) << "% | ";
			std::cout << std::endl;
			
			// Updating prev_cpu_usage	
			prev_cpu_usage = curr_cpu_usage;
		}
		curr_cpu_usage.clear();		
		// Sleeping
		std::this_thread::sleep_for (std::chrono::milliseconds(sleep_time));
	}

	return 0;
}