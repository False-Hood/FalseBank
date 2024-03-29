﻿#pragma once
#include <ZinxTCP.h>
#include "GameProtocol.h"
class GameChannel :
	public ZinxTcpData
{
public:
	GameChannel(int _fd);
	virtual ~GameChannel();
	GameProtocol* m_proto = NULL;
	// 通过 ZinxTcpData 继承
	virtual AZinxHandler* GetInputNextStage(BytesMsg& _oInput) override;
};
class GameConnFact :public IZinxTcpConnFact
{
	// 通过 IZinxTcpConnFact 继承
	virtual ZinxTcpData* CreateTcpDataChannel(int _fd) override;
};

