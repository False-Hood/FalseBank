#include "CmdCheck.h"

CmdCheck::CmdCheck()
{
}

UserData* CmdCheck::raw2request(std::string _szInput)
{
	return nullptr;
}

std::string* CmdCheck::response2raw(UserData& _oUserData)
{
	return nullptr;
}

Irole* CmdCheck::GetMsgProcessor(UserDataMsg& _oUserDataMsg)
{
	return nullptr;
}

Ichannel* CmdCheck::GetMsgSender(BytesMsg& _oBytes)
{
	return nullptr;
}
