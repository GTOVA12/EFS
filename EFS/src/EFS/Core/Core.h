#pragma once
#include "log.h"
#ifdef _WIN32

#if defined(EFS_STATIC)
	#define EFSAPI
#elif defined(BUILD_API)
	#define EFSAPI __declspec(dllexport)
#else
	#define EFSAPI __declspec(dllimport)
#endif

#else
#error "EFS supports only Windows!"
#endif

#define BIT(x) (1<<x)
#define STRNGIFY(x) #x

#ifdef EFS_ENABLE_ASSERTS
	#define EFS_ASSERTS(x,...) {if(!x){ EFS_ERROR("Assertion Failed : {0}",__VA_ARGS__); __debugbreak();}}
	#define EFS_CORE_ASSERTS(x,...) {if(!x){EFS_Core_ERROR("Assertion Failed : {0}",__VA_ARGS__); __debugbreak();}}
#else
	#define EFS_ASSERTS(x,...) 
	#define EFS_CORE_ASSERTS(x,...)
#endif