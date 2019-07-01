﻿#include "RandomName.h"
#include <random>
#include <iostream>
#include <fstream>

static std::default_random_engine rand_engine(time(NULL));

RandomName::RandomName()
{
}

std::string RandomName::GetName()
{
	//取姓
	auto num = rand_engine() % m_pool.size();
	auto first = m_pool[num]->m_first;

	//取名
	auto last = m_pool[num]->m_last_list[rand_engine() % m_pool[num]->m_last_list.size()];
	//如果本姓的所有名取完   删掉姓
	if (m_pool[num]->m_last_list.size() <= 0)
	{
		delete m_pool[num];
		m_pool.erase(m_pool.begin() + num);
	}
	return first + " " + last;
}

void RandomName::Release(std::string _name)
{
	//分割姓名  得到姓和名
	auto space_pos = _name.find(" ", 0);
	auto first = _name.substr(0, space_pos);
	auto last = _name.substr(space_pos + 1, _name.size() - space_pos - 1);

	bool found = false;
	for (auto first_name : m_pool)
	{
		if (first_name->m_first == first)
		{
			found = true;
			first_name->m_last_list.push_back(last);
			break;
		}
	}

	if (false == found)
	{
		auto first_name = new FirstName();
		first_name->m_last_list.push_back(last);
		m_pool.push_back(first_name);
	}
}

void RandomName::LoadFile()
{
	std::ifstream first("random_first.txt");
	std::ifstream last("random_last.txt");

	//读取所有名字的一个线性表
	std::string last_name;
	std::vector<std::string>tmp;
	while (getline(last,last_name))
	{
		tmp.push_back(last_name);
	}
	std::string first_name;
	while (getline(first,first_name))
	{
		auto first_name_list = new FirstName();
		first_name_list->m_first = first_name;
		first_name_list->m_last_list = tmp;
		m_pool.push_back(first_name_list);
	}
}

RandomName::~RandomName()
{
}
