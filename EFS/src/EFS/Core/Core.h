#pragma once
#ifdef _WIN32

	#ifdef BUILD_API
		#define EFSAPI __declspec(dllexport)
	#else
		#define EFSAPI __declspec(dllimport)
	#endif
#else
	#error "EFS supports only Windows!"
#endif

#define BIT(x) (1<<x)
#define STRNGIFY(x) #x