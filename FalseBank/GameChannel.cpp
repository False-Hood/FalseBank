#include "GameChannel.h"
#include "GameRole.h"
GameChannel::GameChannel(int _fd):ZinxTcpData(_fd)
{
}

GameChannel::~GameChannel()
{
	std::cout << "析构m_protp" << std::endl;
	if (NULL != m_proto)
	{
		ZinxKernel::Zinx_Del_Proto(*m_proto);
		delete m_proto;
	}
}

AZinxHandler* GameChannel::GetInputNextStage(BytesMsg& _oInput)
{
	std::cout << "Channel 返回 m_protp" << std::endl;
	return m_proto;
}

ZinxTcpData* GameConnFact::CreateTcpDataChannel(int _fd)
{
	std::cout << "创建通道、协议" << std::endl;
	//创建TCP通道对象
	auto pChannel = new GameChannel(_fd);
	//创建协议对象
	auto pProtocol = new GameProtocol();

	auto pRole = new GameRole();
	
	//绑定协议对象和通道对象
	pChannel->m_proto = pProtocol;
	pProtocol->m_channel = pChannel;

	pProtocol->m_Role = pRole;
	pRole->m_pProto = pProtocol;

	//将协议对象添加到框架上
	ZinxKernel::Zinx_Add_Proto(*pProtocol);
	ZinxKernel::Zinx_Add_Role(*pRole);
	return pChannel;
}
