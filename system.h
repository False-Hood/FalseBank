#include <string>

struct system_info
{
	//获取全部信息
	std::string get_system_all();

	//系统安装日期
	std::string  get_system_create();

	//操作系统
	std::string get_system_name();
	
	//主机名
	std::string get_host_name();

	//系统位数
	size_t get_system_bit();

	//内核版本
	std::string get_system_version();

	//内存大小
	size_t get_system_memory(); 

	//磁盘大小
	size_t get_system_disk();

	//cpu信息
	std::string get_cpu_name();

	//BIOS版本
	std::string get_system_bios();

	//IP地址
	std::string get_local_ip();

	//MAC地址
 	std::string get_system_mac();
};