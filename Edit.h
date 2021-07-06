#pragma once
#include "Actions\Action.h"
#include"ApplicationManager.h"
class Edit : public Action
{
public:
	Edit(ApplicationManager *pManager);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();

	~Edit();
};

