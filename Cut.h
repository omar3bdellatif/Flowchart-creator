#pragma once
#include "Conditional.h"
#include "End.h"
#include "OperatorAssign.h"
#include "Read.h"
#include "Start.h"
#include "VariableAssign.h"
#include "Write.h"
#include "Statements\ValueAssign.h"
#include"Remove.h"
class Cut : public Remove
{
public:
	Cut(ApplicationManager * pManager);

	virtual void ReadActionParameters();

	virtual void Execute();

	~Cut();
};

