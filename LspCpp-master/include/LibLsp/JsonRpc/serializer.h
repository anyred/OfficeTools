#pragma once

#include "macro_map.h"

#include <cassert>
#include <memory>
#include <optional>
#include <string>
#include <type_traits>
#include <vector>
#include <functional>
#include <map>
#include <algorithm>


// 绝对路径
struct AbsolutePath;

// 串行格式化属性
enum class SerializeFormat { Json, MessagePack };

// A tag type that can be used to write `null` to json.
// 可用于将'null'写入json的标记类型
struct JsonNull
{
	void swap(JsonNull& arg) noexcept;
};


// 读取器
class Reader {
public:
	virtual ~Reader() {}
	virtual SerializeFormat Format() const = 0;

	virtual bool IsBool() = 0;
	virtual bool IsNull() = 0;
	virtual bool IsArray() = 0;
	virtual bool IsInt() = 0;
	virtual bool IsInt64() = 0;
	virtual bool IsUint64() = 0;
	virtual bool IsDouble() = 0;
  virtual bool IsNumber() = 0;
  virtual bool IsString() = 0;

	virtual void GetNull() = 0;
	virtual bool GetBool() = 0;
	virtual int GetInt() = 0;
	virtual uint32_t GetUint32() = 0;
	virtual int64_t GetInt64() = 0;
	virtual uint64_t GetUint64() = 0;
	virtual double GetDouble() = 0;
	virtual std::string GetString() = 0;

	virtual bool HasMember(const char* x) = 0;
	virtual std::unique_ptr<Reader> operator[](const char* x) = 0;
	virtual void IterMap( std::function<void(const char*, Reader&)> fn) = 0;
	virtual void IterArray(std::function<void(Reader&)> fn) = 0;
	virtual void DoMember(const char* name, std::function<void(Reader&)> fn) = 0;
	virtual std::string ToString() const = 0;
};



class Writer {
public:
	virtual ~Writer() {}
	virtual SerializeFormat Format() const = 0;

	virtual void Null() = 0;
	virtual void Bool(bool x) = 0;
	virtual void Int(int x) = 0;
	virtual void Uint32(uint32_t x) = 0;
	virtual void Int64(int64_t x) = 0;
	virtual void Uint64(uint64_t x) = 0;
	virtual void Double(double x) = 0;
	virtual void String(const char* x) = 0;
	virtual void String(const char* x, size_t len) = 0;
	virtual void StartArray(size_t) = 0;
	virtual void EndArray() = 0;
	virtual void StartObject() = 0;
	virtual void EndObject() = 0;
	virtual void Key(const char* name) = 0;
};



struct optionals_mandatory_tag {};

// 反射成员开始  访问者 成员
#define REFLECT_MEMBER_START() ReflectMemberStart(visitor, value)
// 反射成员结束
#define REFLECT_MEMBER_END() ReflectMemberEnd(visitor, value);
// 反射成员结束 带返回值
#define REFLECT_MEMBER_END1(value) ReflectMemberEnd(visitor, value);
// 反射成员 名字  值
#define REFLECT_MEMBER(name) ReflectMember(visitor, #name, value.name)
// 反射成员操作
#define REFLECT_MEMBER_OPTIONALS(name) \
  ReflectMember(visitor, #name, value.name, optionals_mandatory_tag{})
// 反射成员2 带值
#define REFLECT_MEMBER2(name, value) ReflectMember(visitor, name, value)

// 构建反射类型代理
// 参数为类型, 然后通过类型获取基类的类型
// 传递给MAKE_REFLECT_TYPE_PROXY2
// MAKE_REFLECT_TYPE_PROXY2
// 功能是创建Reflect/ Reader与Writer 函数
#define MAKE_REFLECT_TYPE_PROXY(type_name) \
  MAKE_REFLECT_TYPE_PROXY2(type_name, std::underlying_type<type_name>::type)

//给Reflect创建Reader和Writer函数
#define MAKE_REFLECT_TYPE_PROXY2(type, as_type)       \
  inline void Reflect(Reader& visitor, type& value) { \
    as_type value0;                                   \
    ::Reflect(visitor, value0);                       \
    value = static_cast<type>(value0);                \
  }                                                   \
  inline void Reflect(Writer& visitor, type& value) { \
    auto value0 = static_cast<as_type>(value);        \
    ::Reflect(visitor, value0);                       \
  }

#define _MAPPABLE_REFLECT_MEMBER(name) REFLECT_MEMBER(name);
#define _MAPPABLE_REFLECT_MEMBER_OPTIONALS(name) REFLECT_MEMBER_OPTIONALS(name);

// 创建空的反射结构体
#define MAKE_REFLECT_EMPTY_STRUCT(type, ...)     \
  template <typename TVisitor>                   \
  void Reflect(TVisitor& visitor, type& value) { \
    REFLECT_MEMBER_START();                      \
    REFLECT_MEMBER_END();                        \
  }

// 创建反射结构体
#define MAKE_REFLECT_STRUCT(type, ...)               \
  template <typename TVisitor>                       \
  void Reflect(TVisitor& visitor, type& value) {     \
    REFLECT_MEMBER_START();                          \
    MACRO_MAP(_MAPPABLE_REFLECT_MEMBER, __VA_ARGS__) \
    REFLECT_MEMBER_END();                            \
  }

// 与arg交换
#define _MAPPABLE_SWAP_MEMBER(name)  std::swap(name,arg.name);

// 创建交换方法
// 利用了MACRO_MAP方法进行多项交换
#define  MAKE_SWAP_METHOD(type, ...)			\
void swap(type& arg) noexcept{			\
	MACRO_MAP(_MAPPABLE_SWAP_MEMBER, __VA_ARGS__) \
}

// 构建反射结构体选择强制性????
#define MAKE_REFLECT_STRUCT_OPTIONALS_MANDATORY(type, ...)     \
  template <typename TVisitor>                                 \
  void Reflect(TVisitor& visitor, type& value) {               \
    REFLECT_MEMBER_START();                                    \
    MACRO_MAP(_MAPPABLE_REFLECT_MEMBER_OPTIONALS, __VA_ARGS__) \
    REFLECT_MEMBER_END();                                      \
  }

// clang-format off
// Config has many fields, we need to support at least its number of fields.
// Config 有很多字段, 我们至少需要支持他的字段数量
#define NUM_VA_ARGS_IMPL(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,N,...) N
#define NUM_VA_ARGS(...) NUM_VA_ARGS_IMPL(__VA_ARGS__,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1)
// clang-format on

// 可用反射数组
#define _MAPPABLE_REFLECT_ARRAY(name) Reflect(visitor, value.name);

// Reflects the struct so it is serialized as an array instead of an object.
// This currently only supports writers.
// 反射结构体, 因此将其串行化为数组,而不是对象
// 目前支持写入器
#define MAKE_REFLECT_STRUCT_WRITER_AS_ARRAY(type, ...) \
  inline void Reflect(Writer& visitor, type& value) {  \
    visitor.StartArray(NUM_VA_ARGS(__VA_ARGS__));      \
    MACRO_MAP(_MAPPABLE_REFLECT_ARRAY, __VA_ARGS__)    \
    visitor.EndArray();                                \
  }

//// Elementary types 基本类型

void Reflect(Reader& visitor, uint8_t& value);
void Reflect(Writer& visitor, uint8_t& value);

void Reflect(Reader& visitor, short& value);
void Reflect(Writer& visitor, short& value);

void Reflect(Reader& visitor, unsigned short& value);
void Reflect(Writer& visitor, unsigned short& value);

void Reflect(Reader& visitor, int& value);
void Reflect(Writer& visitor, int& value);

void Reflect(Reader& visitor, unsigned& value);
void Reflect(Writer& visitor, unsigned& value);

void Reflect(Reader& visitor, long& value);
void Reflect(Writer& visitor, long& value);

void Reflect(Reader& visitor, unsigned long& value);
void Reflect(Writer& visitor, unsigned long& value);

void Reflect(Reader& visitor, long long& value);
void Reflect(Writer& visitor, long long& value);

void Reflect(Reader& visitor, unsigned long long& value);
void Reflect(Writer& visitor, unsigned long long& value);

void Reflect(Reader& visitor, double& value);
void Reflect(Writer& visitor, double& value);

void Reflect(Reader& visitor, bool& value);
void Reflect(Writer& visitor, bool& value);

void Reflect(Reader& visitor, std::string& value);
void Reflect(Writer& visitor, std::string& value);

void Reflect(Reader& visitor, JsonNull& value);
void Reflect(Writer& visitor, JsonNull& value);

void Reflect(Reader& visitor, SerializeFormat& value);
void Reflect(Writer& visitor, SerializeFormat& value);

//// Type constructors
//// 类型构造器
template <typename T>
void Reflect(Reader& visitor, std::optional<T>& value) {
	if (visitor.IsNull()) {
		visitor.GetNull();
		return;
	}
	T real_value;
	Reflect(visitor, real_value);
	value = std::move(real_value);
}
template <typename T>
void Reflect(Writer& visitor, std::optional<T>& value) {
	if (value)
		Reflect(visitor, *value);
	else
		visitor.Null();
}


template <typename T>
void ReflectMember(Writer& visitor, const char* name, std::optional<T>& value) {
	// For TypeScript optional property key?: value in the spec,
	// We omit both key and value if value is std::nullopt (null) for JsonWriter
	// to reduce output. But keep it for other serialization formats.
	if (value || visitor.Format() != SerializeFormat::Json) {
		visitor.Key(name);
		Reflect(visitor, value);
	}
}


template <typename T>
void ReflectMember(Writer& visitor,
	const char* name,
	T& value,
	optionals_mandatory_tag) {
	visitor.Key(name);
	Reflect(visitor, value);
}
template <typename T>
void ReflectMember(Reader& visitor,
	const char* name,
	T& value,
	optionals_mandatory_tag) {
	Reflect(visitor, value);
}

template<class T >
void Reflect(Reader& visitor, std::map<std::string, T>& value)
{
	visitor.IterMap([&](const char* name,Reader& entry) {
		T entry_value;
		Reflect(entry, entry_value);
		value[name]=(std::move(entry_value));
	});
}
template<class _Ty >
void Reflect(Writer& visitor, std::map<std::string, _Ty>& value)
{
	REFLECT_MEMBER_START();
	for (auto& it : value)
	{
		visitor.Key(it.first.c_str());
		Reflect(visitor, it.second);
	}
	REFLECT_MEMBER_END();
}

// std::vector
template <typename T>
void Reflect(Reader& visitor, std::vector<T>& values) {
	visitor.IterArray([&](Reader& entry) {
		T entry_value;
		Reflect(entry, entry_value);
		values.push_back(std::move(entry_value));
		});
}


template <typename T>
void Reflect(Writer& visitor, std::vector<T>& values) {
	visitor.StartArray(values.size());
	for (auto& value : values)
		Reflect(visitor, value);
	visitor.EndArray();
}

// ReflectMember

inline void DefaultReflectMemberStart(Writer& visitor) {
	visitor.StartObject();
}
inline void DefaultReflectMemberStart(Reader& visitor) {}

template <typename T>
bool ReflectMemberStart(Reader& visitor, T& value) {
	return false;
}
template <typename T>
bool ReflectMemberStart(Writer& visitor, T& value) {
	visitor.StartObject();
	return true;
}

template <typename T>
void ReflectMemberEnd(Reader& visitor, T& value) {}
template <typename T>
void ReflectMemberEnd(Writer& visitor, T& value) {
	visitor.EndObject();
}

template <typename T>
void ReflectMember(Reader& visitor, const char* name, T& value) {
	visitor.DoMember(name, [&](Reader& child) { Reflect(child, value); });
}
template <typename T>
void ReflectMember(Writer& visitor, const char* name, T& value) {
	visitor.Key(name);
	Reflect(visitor, value);
}

template<class _Ty1, class _Ty2>
void Reflect(Writer& visitor, std::pair<  std::optional<_Ty1>, std::optional<_Ty2> >& value)
{
	if (value.first)
	{
		Reflect(visitor, value.first);
	}
	else
	{
		Reflect(visitor, value.second);
	}
}
template<class _Ty2>
void Reflect(Reader& visitor, std::pair<  std::optional<bool>, std::optional<_Ty2> >& value)
{
	if(visitor.IsBool())
	{
		Reflect(visitor, value.first);
		return;
	}

	Reflect(visitor, value.second);
}
template<class _Ty2>
void Reflect(Reader& visitor, std::pair<  std::optional<std::string>, std::optional<_Ty2> >& value)
{
	if (visitor.IsString())
	{
		Reflect(visitor, value.first);
		return;
	}

	Reflect(visitor, value.second);
}


template<class _Ty1, class _Ty2>
void Reflect(Reader& visitor, std::pair<  std::optional<_Ty1>, std::optional<_Ty2> >& value)
{
	try
	{
		Reflect(visitor, value.second);
	}
	catch (...)
	{
		Reflect(visitor, value.first);
	}
}
