#pragma once
#include "Actions\Action.h"
#include "ApplicationManager.h"
class Switch : public Action
{
public:
	Switch(ApplicationManager * P);

	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();

	~Switch();
};

