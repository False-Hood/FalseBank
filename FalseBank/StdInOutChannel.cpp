#include "StdInOutChannel.h"

StdInChannel::StdInChannel()
{
}

bool StdInChannel::Init()
{
	return false;
}

bool StdInChannel::ReadFd(std::string& _input)
{
	return false;
}

bool StdInChannel::WriteFd(std::string& _output)
{
	return false;
}

void StdInChannel::Fini()
{
}

int StdInChannel::GetFd()
{
	return 0;
}

std::string StdInChannel::GetChannelInfo()
{
	return std::string();
}

AZinxHandler* StdInChannel::GetInputNextStage(BytesMsg& _oInput)
{
	return nullptr;
}
