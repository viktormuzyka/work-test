#pragma once
#include <string>
#include <vector>
#include "filewriters.h"
#include <windows.h>

class writercreator
{
public:	
	virtual write* createnewfilewriter(WIN32_FIND_DATA &data) = 0;
	virtual ~writercreator() = default;
};

class txtwritercreator : public virtual writercreator
{
public:
	 writer* createnewfilewriter(WIN32_FIND_DATA &data) override{
	 	return (new txtwriter(data));
	 }
};

class csvwritercreator : public virtual writercreator
{
public:
	writer* createnewfilewriter(WIN32_FIND_DATA &data) override {
		return (new csvwriter(data));
	}
};
