#pragma once
#include "ApplicationManager.h"
#include "Actions\Action.h"
#include "Validate.h"
class Run : public Action
{
public:
	Run(ApplicationManager *ApM);
	virtual void ReadActionParameters();
	virtual void Execute();
	~Run();
};

