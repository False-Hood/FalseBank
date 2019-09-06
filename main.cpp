#include "system.h"
#include <string>
#include <iostream>
#include <unistd.h>
using namespace std;
int main(int argc, char* argv[])
{
	system_info info;
	string str;

	str = info.get_system_create();
	if(!str.empty())
	{
		cout << str << endl;
	}
	str.clear();	

	str = info.get_system_name();
	if(!str.empty())
	{
		cout << str << endl;
	}
	str.clear();

	str = info.get_host_name();
	if(!str.empty())
	{
		cout << str << endl;
	}
	str.clear();

	str = info.get_system_version();
	if(!str.empty())
	{
		cout << str << endl;
	}
	str.clear();

	size_t len = 0;
	len = info.get_system_bit();
	if(len != 0)
	{
		cout << len << endl;
	}
	len = 0;

	len = info.get_system_disk();
	if(len != 0)
	{
		cout << len << endl;
	}
	len = 0;

	len = info.get_system_memory();
	if(len != 0)
	{
		cout << len << endl;
	}

	str = info.get_cpu_name();
	if(!str.empty())
	{
		cout << str << endl;
	}
	str.clear();

	str = info.get_local_ip();
	if(!str.empty())
	{
		cout << str << endl;
	}
	str.clear();

	str = info.get_system_mac();
	if(!str.empty())
	{
		cout << str << endl;
	}
	str.clear();

	str = info.get_system_bios();
	if(!str.empty())
	{
		cout << str << endl;
	}
	str.clear();


	string str_all;
	str_all = info.get_system_all();
	if(!str_all.empty())
	{
		cout << str_all << endl;
	}
	str_all.clear();

	return 0;
}
