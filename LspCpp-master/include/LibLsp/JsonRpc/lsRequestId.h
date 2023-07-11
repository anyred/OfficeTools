#pragma once

#include "LibLsp/JsonRpc/serializer.h"

struct lsRequestId {
	// The client can send the request id as an int or a string. We should output
	// the same format we received.
		// 客户端可以看将请求ID作为int或者字符串发送
		// 我们应该输出与我们收到的格式相同.
	enum Type { kNone, kInt, kString };
	Type type = kNone;

	int value = -1;
	std::string  k_string;
	bool has_value() const { return type != kNone; }
	void swap(lsRequestId& arg) noexcept
	{
		std::swap(arg, *this);
	}
	void set(int v)
	{
		value = v;
		type = kInt;
	}
	void set(const std::string& v)
	{
		k_string = v;
		type = kString;
	}
	bool operator==(const lsRequestId& rhs) const
	{
		if (type != rhs.type) return  false;
		if (type == kInt)
			return  value == rhs.value;
		return  k_string == rhs.k_string;
	}
	bool operator!=(const lsRequestId& rhs) const
	{
		return !operator==(rhs);
	}
	bool operator<(const lsRequestId& rhs) const
	{
		if (type != rhs.type) return  false;
		if (type == kInt)
			return  value < rhs.value;
		return  k_string < rhs.k_string;
	}
};
void Reflect(Reader& visitor, lsRequestId& value);
void Reflect(Writer& visitor, lsRequestId& value);

// Debug method to convert an id to a string.
// 将id转换为字符串
std::string ToString(const lsRequestId& id);