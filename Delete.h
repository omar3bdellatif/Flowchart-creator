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
#include"Remove.h"

class Delete : public Remove
{
public:
	Delete(ApplicationManager * pManager);

	virtual void ReadActionParameters();

	virtual void Execute();



	~Delete();
};

