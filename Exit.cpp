#include "Exit.h"



Exit::Exit(ApplicationManager * p)
	:Action(p)
{
}

void Exit::ReadActionParameters()
{
}


void Exit::Execute(ApplicationManager * p)
{
	delete pManager;
}

Exit::~Exit()
{
}
