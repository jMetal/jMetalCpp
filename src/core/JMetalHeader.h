#ifndef __JMETAL_HEADER__
#define __JMETAL_HEADER__

#ifdef MSVC
	#ifdef _DEBUG
		#define snew new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
	#endif
#else
	#define snew new
#endif

#endif