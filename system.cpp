#include "system.h"
#include <sys/mount.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <linux/hdreg.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <sys/sysinfo.h>
#include <errno.h>
#include <sys/utsname.h>
#include <time.h>
#include <ifaddrs.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <linux/if.h>
#include <vector>
#include <fstream>
#include <time.h>

#define IP_SIZE  16

 //获取操作系统名称
std::string system_info::get_system_name()
{
    std::string str_temp;
    std::fstream fd;
    fd.open("/etc/issue",std::ios::in);
    if(!fd.is_open())
        return "";
    getline(fd,str_temp);
    int temp = str_temp.find('\\');
    std::string str = str_temp.substr(0,temp);
    return str;
}

//获取主机名
std::string  system_info::get_host_name()
{
    char hostname[32] = { 0 };
    int ret = gethostname(hostname,sizeof(hostname));
    if(ret == -1)
        return "";
    return hostname;
}

//获取操作系统位数
size_t system_info::get_system_bit()
{
    size_t len = sysconf(_SC_HOST_NAME_MAX);
    if(len == -1)
        return 0;
    return len;
}

//获取内存大小
size_t system_info::get_system_memory()
{
    size_t len  = (((long long)sysconf(_SC_PAGESIZE) * (long long)sysconf(_SC_PHYS_PAGES)));
    if(len < 0 )
        return 0;
    return len;
}

//获取内核版本
std::string system_info::get_system_version()
{
    struct utsname buffer;
    if (uname(&buffer) != 0)
       return "";
    return buffer.release;
}

//获取磁盘信息
size_t system_info::get_system_disk()
{
    int fd =  open("/dev/sda",O_RDONLY | O_NONBLOCK);
    size_t size = 0;
    if (fd < 0)
        return 0;
    if ((ioctl(fd, BLKGETSIZE64 , &size)) < 0)
        return 0;
    return size;

}

//获取cpu
std::string system_info::get_cpu_name()
{
    long cpu_thread = sysconf(_SC_NPROCESSORS_CONF);
    std::string cpu_info;
    int fd = open("/proc/cpuinfo",O_RDONLY);
    if(fd == -1)
        return "";
    while(1)
    {
        char cpuinfo_[1024] = { 0 };
        int ret = read(fd,cpuinfo_,sizeof(cpuinfo_));
        if(ret > 0)
        {
            cpu_info += cpuinfo_;
            continue;
        }
        break;
    }
    std::string temp_model_name_("model name\t: ");
    size_t temp_model_name_pos = cpu_info.find(temp_model_name_);
    if(temp_model_name_pos == std::string::npos)
        return "";
    std::string temp_model_name = cpu_info.substr(temp_model_name_pos);
    size_t temp_n = temp_model_name.find('\n');
    if(temp_n == std::string::npos)
        return "";
    std::string model_name = temp_model_name.substr(temp_model_name_.size(),temp_n - temp_model_name_.size());

    std::string temp_cpu_cores_("cpu cores\t: ");
    size_t temp_cpu_cores_pos = cpu_info.find(temp_cpu_cores_);
    if(temp_cpu_cores_pos == std::string::npos)
        return "";
    std::string temp_cpu_cores = cpu_info.substr(temp_cpu_cores_pos);
    size_t n = temp_cpu_cores.find('\n');
    if(n == std::string::npos)
        return "";
    std::string cpu_cores = temp_cpu_cores.substr(temp_cpu_cores_.size(),n - temp_cpu_cores_.size());

    std::string str = model_name + " " + cpu_cores + "(核)" + std::to_string(cpu_thread) + "(线程)"; 
    return str;
}

//系统安装日期
std::string system_info::get_system_create()
{
    struct stat t_stat;
    int ret = stat("/var", &t_stat);
    if(ret == -1)
        return "";
    struct tm * timeinfo = localtime(&t_stat.st_ctime);

    char buffer[64] = { 0 };
    strftime(buffer,64,"%Y年-%m月-%d日 %X",timeinfo);
  
    return buffer;
}
std::string system_info::get_system_bios()
{
    std::fstream fd;
    std::string str;
    fd.open("/sys/class/dmi/id/bios_version",std::ios::in);
    if(!fd.is_open())
        return "";
    getline(fd,str);

    return str;
}

std::string system_info::get_local_ip()
{  
    struct sockaddr_in sin;
    struct ifreq ifr;
    char ip[IP_SIZE];
    const char *test_eth = "ens33";
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (-1 == fd)
        return "";
    strncpy(ifr.ifr_name, test_eth, IFNAMSIZ);
    ifr.ifr_name[IFNAMSIZ - 1] = 0;
    if ( !ioctl(fd, SIOCGIFADDR, &ifr) < 0)  
    {  
        close(fd);
        return "";
    }  
    memcpy(&sin, &ifr.ifr_addr, sizeof(sin));
    snprintf(ip, IP_SIZE, "%s", inet_ntoa(sin.sin_addr));
    close(fd);
    return ip;
}

//获取本机MAC
std::string system_info::get_system_mac()
{
    struct ifreq ifr;
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    char local_mac[128] = { 0 };
    strcpy(ifr.ifr_name, "ens33");
    if (0 == ioctl(fd, SIOCGIFHWADDR, &ifr))
    {
        char temp_str[10] = { 0 };
        memcpy(temp_str, ifr.ifr_hwaddr.sa_data, 6);
        sprintf(local_mac, "%02x-%02x-%02x-%02x-%02x-%02x",temp_str[0]&0xff,
        temp_str[1]&0xff, temp_str[2]&0xff, temp_str[3]&0xff,
        temp_str[4]&0xff, temp_str[5]&0xff);
    }
    else
        return "";
    return local_mac;
}


//获取全部信息
std::string system_info::get_system_all()
{
    std::size_t len;
    std::string temp;
    std::string str_n(" \n");
    temp = get_system_create();
    if(temp.empty())
        return "";
    std::string str = temp + str_n;
    temp.clear();

    temp = get_system_name();
    if(temp.empty())
        return "";
    str += temp + str_n;
    temp.clear();

    temp = get_host_name();
    if(temp.empty())
        return "";
    str += temp + str_n;
    temp.clear();

    temp = get_system_version(); 
    if(temp.empty())
        return "";
    str += temp + str_n;
    temp.clear();

    len = get_system_bit();
    if(len < 0)
        return "";
    str +=std::to_string(len) +str_n;
    len = 0;

    len = get_system_disk();
    if(len < 0 )
        return "";
    str +=std::to_string(len) +str_n;
    len = 0;

    len = get_system_memory();
    if(len < 0 )
        return "";
    str +=std::to_string(len) +str_n;
    len = 0;

    temp = get_cpu_name();
    if(temp.empty())
        return "";
    str += temp +str_n;
    temp.clear();

    temp = get_local_ip();
    if(temp.empty())
        return "";
    str += temp + str_n;
    temp.clear();

    temp = get_system_mac() ;
    if(temp.empty())
        return "";
    str += temp + str_n;
    temp.clear();
    
    temp = get_system_bios() ;
    if(temp.empty())
        return "";
    str += temp + str_n;
    temp.clear();

    return str;
}