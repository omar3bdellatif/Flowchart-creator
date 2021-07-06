#pragma once
#include "ApplicationManager.h"
#include "Actions\Action.h"
class Validate :public Action
{
private:
	bool AllValid;
public:
	Validate(ApplicationManager*ApM);
	virtual void ReadActionParameters();
	virtual void Execute();
	bool ValidStart();
	bool ValidEnd();
	bool ValidNumConn();
	bool ValidConnection();
	bool ValuesInitialized(Statement * pStat, int c = 0, string * arr = NULL);
	bool IsAllValid();
	~Validate();
};

