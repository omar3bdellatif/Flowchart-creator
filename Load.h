#pragma once
#ifndef LOAD_H
#define LOAD_H
#include "ApplicationManager.h"
#include"Actions\Action.h"
#include<fstream>

class Load :public Action {
	string FileName;
public:
	Load(ApplicationManager *pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();
};
#endif
