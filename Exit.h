#pragma once
#include "Actions\Action.h"
class Exit : public Action
{
public:
	Exit(ApplicationManager * p);

	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute(ApplicationManager * p);

	~Exit();
};

