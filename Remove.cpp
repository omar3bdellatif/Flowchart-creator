#include "Remove.h"
#include "Statements\Statement.h"
#include "ApplicationManager.h"

#include "GUI\input.h"
#include "GUI\Output.h"

#include <sstream>


Remove::Remove(ApplicationManager * pManager)
	:Action(pManager)
{
}


void Remove::Execute()
{
	Statement * pStat = pManager->GetSelectedStatement();

	if (pStat != NULL)
	{
		pManager->RemoveStatFromList(pStat);
		DeleteStatement(pManager, pStat);
		pManager->SetSelectedStatement(NULL);
		return;

	}
	Output *pOut = pManager->GetOutput();
	pOut->PrintMessage("No item selected to be deleted .. Please select and item the click Delete");
}

void Remove::DeleteConnector(Connector * pConn)
{
	Statement* Source = pConn->getSrcStat();
	Statement* Dest = pConn->getDstStat();
	if (Source->GetMaxOutConn() == 1)
	{
		Source->ReleaseConnector();
	}
	else
	{
		if (pConn == Source->GetConnecter(0))
		{
			Source->ReleaseConnector(0);
		}
		else
		{
			Source->ReleaseConnector(1);
		}
	}
	Connector * Conn = pManager->GetConnectorToStat(Dest);
	if (Conn == NULL)
	{
		Dest->SetIsInConnected(false);
	}
	Source->DecrAct();
	delete pConn;
	
}

void Remove::DeleteStatement(ApplicationManager * pManager, Statement * pStat)
{

	if (pStat->GetMaxOutConn() == 2)
	{
		Connector * Left = (pStat->GetConnecter(0));
		Connector * Right = (pStat->GetConnecter(1));
		if (Left != NULL)
		{
			pManager->RemoveConnFromList(Left);
			DeleteConnector(Left);
		}
		if (Right != NULL)
		{
			pManager->RemoveConnFromList(Right);
			DeleteConnector(Right);
		}
		pManager->RemoveStatFromList(pStat);
	}
	else if (pStat->GetMaxOutConn() == 1)
	{
		Connector * OutConn = (pStat)->GetConnecter();
		if (OutConn != NULL)
			pManager->RemoveConnFromList(OutConn);
	}
	if (pStat->CanBeConnected())
	{
		if (pStat->GetIsInConnected())
		{
			Connector * InConn = pManager->GetConnectorToStat(pStat);
			while (InConn != NULL)
			{
				pManager->RemoveConnFromList(InConn);
				DeleteConnector(InConn);
				InConn = pManager->GetConnectorToStat(pStat);
			}

		}
	}
}

Remove::~Remove()
{
}

