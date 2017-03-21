#include <iostream>
#include <fstream> // std::fstream
#include <string>  // std::string
#include <sstream> // std::stringstream
#include <vector>  // std::vector
#include <utility> // std::pair
#include <thread>  // std::this_thread::sleep_for
#include <chrono>  // std::chrono::seconds
#include <iomanip> // std::setprecision
#include <boost/filesystem.hpp> // boost::filesystem
#include <unistd.h> // long sysconf()
#include <cmath>

// Struct to save informations about cpu
struct CpuInfo{
	std::string cpu;
	double active;
	double total;

	CpuInfo(std::string _cpu) : cpu{_cpu}, active{0}, total{0}{}
};

int check_cpu_usage(int sleep_time, std::pair< int, int > & total_time){

	// Defining path file
	std::string path = "/proc/stat";
	std::string input, cpu;
	double usage;
	std::ifstream cpu_status_file;
	std::stringstream ss;

	cpu_status_file.open(path, std::ifstream::in);
	cpu = ""; usage = 0;

	// Reading /proc/stat file 
	getline(cpu_status_file, input);
	ss << input;
	ss >> cpu;
	
	// Storing prev use of each cpu
	CpuInfo prev_cpu_usage = CpuInfo("Total");
	for(int i = 0; i < 4; ++i){
		ss >> usage;
		if(i < 3) prev_cpu_usage.active += usage;
		else prev_cpu_usage.total = prev_cpu_usage.active + usage;
	}
	ss.str(std::string());
	ss.clear();
	cpu_status_file.close();

	// Sleeping
	std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));

	cpu_status_file.open(path, std::ifstream::in);
	cpu = ""; usage = 0;

	// Reading /proc/stat file again
	getline(cpu_status_file, input);
	ss << input;
	ss >> cpu;
	
	// Storing curr use of each cpu
	CpuInfo curr_cpu_usage = CpuInfo("Total");
	for(int i = 0; i < 4; ++i){
		ss >> usage;
		if(i < 3) curr_cpu_usage.active += usage;
		else curr_cpu_usage.total = curr_cpu_usage.active + usage;
	}
	ss.str(std::string());
	ss.clear();
	cpu_status_file.close();

	total_time = std::make_pair(prev_cpu_usage.total, curr_cpu_usage.total);

	return 100 * (curr_cpu_usage.active - prev_cpu_usage.active) / (curr_cpu_usage.total - prev_cpu_usage.total);
}

bool is_number(const std::string & s){
    return !s.empty() && std::find_if(s.begin(),s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

bool comp(CpuInfo a, CpuInfo b){
	return a.total > b.total;
}

std::string check_process_usage(int sleep_time){
	boost::filesystem::path p("/proc");

    boost::filesystem::directory_iterator end_itr;
    std::vector< CpuInfo > proc_use;
    std::stringstream ss;

    int uptime;
    long hertz;
    std::string input;

    std::ifstream uptime_file("/proc/uptime", std::ifstream::in);
    
    std::getline(uptime_file, input);
    ss << input; ss >> uptime;
    ss.str(std::string());
    ss.clear();

    uptime_file.close();
    
    hertz = sysconf(_SC_CLK_TCK);

    for (boost::filesystem::directory_iterator itr(p); itr != end_itr; ++itr) {
    	if( boost::filesystem::is_directory( itr->path() ) && is_number(itr->path().leaf().string()) ){

    		// Getting information about PID, PPID and NAME PROCESS
    		std::ifstream file(itr->path().string() + "/stat", std::ifstream::in);

    		std::string pid = itr->path().leaf().string();
    		std::getline(file, input);
    		
    		int utime, stime, cutime, cstime, starttime;

    		ss << input;
    		int counter = 0;
    		while(ss >> input){
    			counter++;
    			if(input[0] == '(' && input[input.size() - 1] != ')'){
    				counter--;
    			}
    			if(counter < 14) continue;

    			std::stringstream convert(input);

    			switch(counter){
    				case 14:
						convert >> utime;
    				break;
    				case 15:
    					convert >> stime;
    				break;
    				case 16:
    					convert >> cutime;
    				break;
    				case 17:
    					convert >> cstime;
    				break;
    				case 22:
    					convert >> starttime;
    				break;
    				default:
    				break;
    			}
    			if(counter >= 22) break;
    		}

    		CpuInfo x(pid);
    		x.active = utime + stime;
    		proc_use.push_back( x );

    		file.close();
    		ss.str(std::string());
    		ss.clear();
    	}
    } 

    std::pair<int,int> totaltime;
    check_cpu_usage(sleep_time, totaltime);

    for(int i = 0; i < proc_use.size(); ++i){

    	if( boost::filesystem::exists( "/proc/" + proc_use[i].cpu ) ){

    		// Getting information about PID, PPID and NAME PROCESS
    		std::ifstream file( "/proc/" + proc_use[i].cpu + "/stat", std::ifstream::in);

    		std::getline(file, input);
    		
    		int utime, stime, cutime, cstime, starttime;

    		ss << input;
    		int counter = 0;
    		while(ss >> input){
    			counter++;
    			if(input[0] == '(' && input[input.size() - 1] != ')'){
    				counter--;
    			}
    			if(counter < 14) continue;

    			std::stringstream convert(input);

    			switch(counter){
    				case 14:
						convert >> utime;
    				break;
    				case 15:
    					convert >> stime;
    				break;
    				case 16:
    					convert >> cutime;
    				break;
    				case 17:
    					convert >> cstime;
    				break;
    				case 22:
    					convert >> starttime;
    				break;
    				default:
    				break;
    			}
    			if(counter >= 22) break;
    		}

    		double curr = utime + stime;
    		proc_use[i].total = 100 * (std::abs(curr - proc_use[i].active ) / std::abs( totaltime.first - totaltime.second ));

    		file.close();
    		ss.str(std::string());
    		ss.clear();
    	}

    }

    sort(proc_use.begin(), proc_use.end(), comp);

    for(int i = 0; i < 5 && i < proc_use.size(); ++i){
    	std::cout <<"PID: " << proc_use[i].cpu << " " << proc_use[i].total << std::endl;
    }
    std::cout << "-------------------\n";

    return proc_use.empty() ? "-1" : proc_use.front().cpu;
}

int main(int argn, char * argv[]){
	
	int sleep_time = 1000;

	// Setting interval time in milliseconds to get cpu info
	if(argn > 1){
		sleep_time = atoi(argv[1]);
	}

	while(true){
		//std::cout << check_cpu_usage(sleep_time) << std::endl;
		std::cout << "Proc most used: " << check_process_usage(sleep_time) << std::endl;		
	}

	return 0;
}
