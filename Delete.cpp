#include "Delete.h"
#include "Statements\Statement.h"
#include "ApplicationManager.h"

#include "GUI\input.h"
#include "GUI\Output.h"

#include <sstream>


Delete::Delete(ApplicationManager * pManager)
	:Remove(pManager)
{
}

void Delete::ReadActionParameters()
{
	return;
}

void Delete::Execute()
{
	Connector * pConn = pManager->GetSelectedConnector();
	Statement * pStat = pManager->GetSelectedStatement();
	if (pConn != NULL)
	{
		pManager->RemoveConnFromList(pConn);
		DeleteConnector(pConn);
		pManager->SetSelectedConnector(NULL);
		return;
	}
	else if (pStat != NULL)
	{
		Remove::Execute();
		delete pStat;
		return;
	}
	Output * pOut = pManager->GetOutput();
	pOut->PrintMessage("No Statement or Connector is selected to be Deleted ");


}

Delete::~Delete()
{
}
