#pragma once

#include <atomic>
#include <string>
#include <iostream>
#include <LibLsp/JsonRpc/serializer.h>
#include "LibLsp/lsp/method_type.h"

struct LspMessage
{
public:
	std::string jsonrpc = "2.0";
	virtual void ReflectWriter(Writer&)   = 0;

	// Send the message to the language client by writing it to stdout.
	// 通过将消息写入标准输入输出将消息发送到语言客户端
	void Write(std::ostream& out);
	

	// 获取消息类型
	virtual MethodType GetMethodType() const = 0;
	// 设置消息类型
	virtual void SetMethodType(MethodType) = 0;
	
	virtual ~LspMessage()=default;
	// 种类
	enum Kind
	{
		REQUEST_MESSAGE,      //  请求消息
		RESPONCE_MESSAGE,     //  RESPONCSE回复消息
		NOTIFICATION_MESSAGE  //  通知消息
	};

	
	virtual  Kind GetKid() = 0;  
	virtual std::string ToJson()  ;
	
};

