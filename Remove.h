#pragma once
#include"Actions\Action.h"
#include "Conditional.h"
#include "End.h"
#include "OperatorAssign.h"
#include "Read.h"
#include "Start.h"
#include "VariableAssign.h"
#include "Write.h"
#include "Statements\ValueAssign.h"
class Remove : public Action
{
public:
	Remove(ApplicationManager * P);

	virtual void Execute();

	void DeleteConnector(Connector * pConn);

	void DeleteStatement(ApplicationManager * pManager, Statement * pStat);



	~Remove();
};

