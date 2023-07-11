#pragma once
#include <string>
#include <functional>

// 消息发生器
class MessageProducer
{
public:
	
	
	typedef  std::function< void(std::string&&) >  MessageConsumer;
	virtual  ~MessageProducer() = default;
	virtual void listen(MessageConsumer) = 0;
};
