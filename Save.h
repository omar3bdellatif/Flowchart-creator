#pragma once
#ifndef SAVE_H
#define SAVE_H
#include "ApplicationManager.h"
#include"Actions\Action.h"
#include<fstream>

class Save :public Action {
	string FileName;
public:
	Save (ApplicationManager *pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();
};
#endif
