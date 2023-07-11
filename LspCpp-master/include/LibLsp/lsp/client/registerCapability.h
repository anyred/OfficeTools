#pragma once
#include "LibLsp/JsonRpc/message.h"
#include "LibLsp/lsp/lsDocumentUri.h"

/**
 * General parameters to register for a capability.
 * 常规参数 注册一个功能
 */

struct Registration {
	static  Registration Create(const std::string& method);
	/**
	 * The id used to register the request. The id can be used to deregister
	 * the request again.
	 * 用于注册请求的ID,该ID可用于取消注册或者再次请求
	 */
	std::string id;

	/**
	 * The method / capability to register for.
	 * 注册方法和能力
	 */

	std::string method;
	
	MAKE_SWAP_METHOD(Registration, id, method);
};


MAKE_REFLECT_STRUCT(Registration, id, method);

/**
 * The client/registerCapability request is sent from the server to the client to register
 * for a new capability on the client side. Not all clients need to support dynamic
 * capability registration. A client opts in via the dynamicRegistration property on the
 * specific client capabilities. A client can even provide dynamic registration for
 * capability A but not for capability B (see TextDocumentClientCapabilities as an example).
 * 客户端/注册功能请求从服务器发送到客户端,以在客户端注册新的功能,并非所有的客户端都需要支持动态功能注册
 * 客户端通过特定客户端功能的动态注册属性选择性将加入.客户端甚至可以为功能A提供动态注册
 */
struct RegistrationParams
{
	std::vector<Registration> registrations;
	MAKE_SWAP_METHOD(RegistrationParams, registrations);
};
/**
 * The client/registerCapability request is sent from the server to the client
 * to register for a new capability on the client side.
 * Not all clients need to support dynamic capability registration.
 * A client opts in via the ClientCapabilities.dynamicRegistration property
 * 
 */
MAKE_REFLECT_STRUCT(RegistrationParams, registrations);

DEFINE_REQUEST_RESPONSE_TYPE(Req_ClientRegisterCapability, RegistrationParams,JsonNull, "client/registerCapability");