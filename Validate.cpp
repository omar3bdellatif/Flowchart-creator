#include "Validate.h"

#include "GUI\input.h"
#include "GUI\Output.h"
#include <sstream>
using namespace std;

Validate::Validate(ApplicationManager * ApM)
	:Action(ApM)
{
	AllValid = true;
}

void Validate::ReadActionParameters()
{

}

void Validate::Execute()
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();

	if (ValidStart() && ValidEnd() && ValidNumConn())
	{
		Statement* pStat = pManager->GetStart();
		pStat = (pStat->GetConnecter())->getDstStat();
		string * arr=new string[1] ;
		int c = 0;
		AllValid = ValuesInitialized(pStat,c,arr);
		if (AllValid)
		{
			pOut->PrintMessage("Flowchart is Valid");
		}
		else
		{
			pOut->PrintMessage("Flowchart is InValid");
		}
		
		
	}
	else
	{
		AllValid = false;
		pOut->PrintMessage("ERROR !!  Invalid Flowchart");
	}
}

bool Validate::ValidStart()
{
	Statement ** Arr = pManager->getStatList();
	int CountS = 0; //count number of starts 
	for (int i = 0; i < (pManager->GetStatCount()); i++)
	{
		// Ensures only One Start 

		if ((Arr[i]->CanBeConnected()) == false)
		{
			CountS++;
		}

	}
	//Start Check
	if (CountS != 1)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Validate::ValidEnd()
{
	ReadActionParameters();
	Statement ** Arr = pManager->getStatList();
	int CountE = 0; //count number of ends
	for (int i = 0; i < pManager->GetStatCount(); i++)
	{
		// Ensures only One End per Flowchart

		if (Arr[i]->GetMaxOutConn() == 0)
		{
			CountE++;
		}

	}
	//End Check
	if (CountE != 1)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Validate::ValidNumConn()
{
	ReadActionParameters();
	Statement ** Arr = pManager->getStatList();
	int SumOfConnectors = 0; //Sum of possible Connectors
	for (int i = 0; i < pManager->GetStatCount(); i++)
	{
		//Ensures that Flowchart is fully connected 

		SumOfConnectors += Arr[i]->GetMaxOutConn();

	}

	//Connection Check
	if (SumOfConnectors != pManager->GetConnCount())
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Validate::ValidConnection()
{
	ReadActionParameters();
	Statement ** arr = pManager->getStatList();
	int sCount = pManager->GetStatCount();
	for (int i = 0; i < sCount; i++)
	{
		if (!(arr[i]->CanBeConnected()))
		{
			if (arr[i]->GetActOutConn() != 1)
				return false;
		}
		else
		{
			if (!(arr[i]->GetIsInConnected()))
			{
				return false;
			}
			int max = arr[i]->GetMaxOutConn();
			if (arr[i]->GetActOutConn() != max)
			{
				return false;
			}
		}
	}
	return true;
}

bool Validate::ValuesInitialized(Statement *pStat, int c, string * arr)
{
	
	if (pStat == NULL)
		return false;
	if (pStat->GetMaxOutConn() == 0)
	{
		delete [] arr;
		return true;
	}
	if (pStat->CheckVariables(arr, c))
	{
		if (pStat->GetMaxOutConn() == 1)
		{
			Statement * Next = (pStat->GetConnecter())->getDstStat();
			return ValuesInitialized(Next, c, arr);
		}
		else if (pStat->GetMaxOutConn() == 2)
		{
			Statement * Left = (pStat->GetConnecter())->getDstStat();
			Statement * Right = (pStat->GetConnecter(1))->getDstStat();
			string * arr1 = new string[c];
			string * arr2 = new string[c];
			for (int i = 0; i < c; i++)
			{
				arr1[i] = arr2[i] = arr[i];
			}
			delete arr;
			bool L= ValuesInitialized(Left, c, arr1);
			bool R = ValuesInitialized(Right, c, arr2);
			if ((!R) || (!L))
			{
				delete[] arr1;
				delete[]arr2;
				return false;
			}
		}

	}
	else
	{

		return false;
	}
	return true;

}

bool Validate::IsAllValid()
{
	return AllValid;
}

Validate::~Validate()
{
}
