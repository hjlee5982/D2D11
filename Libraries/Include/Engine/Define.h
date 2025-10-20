#pragma once

#pragma warning(disable : 4244 4267 4819 4838 4996)

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define New DBG_NEW
#endif
#endif


#define SINGLETON(classname)				\
private:									\
	classname() { }							\
public:										\
	static classname* GetInstance()			\
	{										\
		static classname s_instance;		\
		return &s_instance;					\
	}

#define GET_SINGLETON(classname)	classname::GetInstance()

#define CLIENT   GET_SINGLETON(Client)
#define DX		 GET_SINGLETON(Device)
#define DEVICE	 GET_SINGLETON(Device)->GetDevice()
#define CONTEXT  GET_SINGLETON(Device)->GetContext()


