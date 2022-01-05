#ifndef __SHARE_CPPRESTSDK__
#define __SHARE_CPPRESTSDK__
#pragma once

#include "cpprest/filestream.h"
#include "cpprest/http_client.h"
#include "cpprest/http_headers.h"

using namespace web::http;
using namespace web::http::client;
using namespace utility;
using namespace concurrency::streams;

#if  _DEBUG
#pragma comment(lib,"cpprest_2_10d.lib")
#else
#pragma comment(lib,"cpprest_2_10.lib")
#endif //  _DEBUG


#endif // !__SHARE_CPPRESTSDK__
