#pragma once
#include <zinx.h>
#include <google/protobuf/message.h>
#include <list>

class GameMsg :
	public UserData
{
public:
	//用户的请求信息
	google::protobuf::Message* pMsg = NULL;
	//消息类型
	enum MSG_TYPE {
		MSG_TYPE_LOGIN_ID_NAME = 1,//登陆ID
		MSG_TYPE_CHAT_CONTENT = 2,//聊天内容
		MSG_TYPE_NEW_POSTION = 3,//新的位置
		MSG_TYPE_BROADCAST = 200,//广播消息
		MSG_TYPE_LOGOFF_ID_NAME = 201,//退出登陆
		MSG_TYPE_SRD_POSTION = 202
	}enMsgType;

	//已知消息内容创建消息对象
	GameMsg(MSG_TYPE _type, google::protobuf::Message* _pMsg);
	//将字节流内容转换成消息结构
	GameMsg(MSG_TYPE _type, std::string _stream);

	//序列化本消息
	std::string serialize();

	virtual ~GameMsg();
};

class MultiMsg :public UserData {
public:
	std::list<GameMsg*>m_Msgs;
};
