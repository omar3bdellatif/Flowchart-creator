#pragma once
#ifndef ADD_SELECT_H
#define ADD_SELECT_H
#include "ApplicationManager.h"
#include"Actions\Action.h"

class Select:public Action {
	Point Position;
public:
	Select(ApplicationManager *pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();
};
#endif