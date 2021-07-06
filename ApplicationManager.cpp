#include "ApplicationManager.h"
#include "Actions\AddValueAssign.h"
#include"AddConditional.h"
#include"AddOperatorAssign.h"
#include"AddRead.h"
#include"AddStart.h"
#include "Paste.h"
#include "Copy.h"
#include"AddVariableAssign.h"
#include "Run.h"
#include "Validate.h"
#include"AddWrite.h"
#include"Switch.h"
#include"AddEnd.h"
#include "Cut.h"
#include"Select.h"
#include"AddConnectors.h"
#include"Save.h"
#include"Load.h"
#include "Delete.h"
#include "Edit.h"
#include "GUI\Input.h"
#include "GUI\Output.h"


//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	
	StatCount = 0;
	ConnCount = 0;
	pSelectedStat = NULL;	//no Statement is selected yet
	pClipboard = NULL;
	pSelectedConnector = NULL;

	IntVariableCount = 0;
	IntVariables = new string[MaxCount];
	
	//Create an array of Statement pointers and set them to NULL		
	for(int i=0; i<MaxCount; i++)
	{
		StatList[i] = NULL;	
		ConnList[i] = NULL;
	}
}


//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//


ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;
	
	//According to ActioType, create the corresponding action object
	if (UI.AppMode == DESIGN)
	{
		//According to ActioType, create the corresponding action object
		switch (ActType)
		{
		case ADD_VALUE_ASSIGN:
			pAct = new AddValueAssign(this);
			break;

		case ADD_CONDITION:
			pAct = new AddConditional(this);
			break;

		case SELECT:
			pAct = new Select(this);
			break;

		case EXIT:
			///create Exit Action here

			break;

		case STATUS:
			return;
		case ADD_VAR_ASSIGN:
			pAct = new AddVariableAssign(this);

			break;
		case ADD_OPER_ASSIGN:
			pAct = new AddOperatorAssign(this);

			break;
		case ADD_READ:
			pAct = new AddRead(this);

			break;

		case ADD_START:
			pAct = new AddStart(this);

			break;

		case ADD_END:
			pAct = new AddEnd(this);

			break;

		case ADD_WRITE:
			pAct = new AddWrite(this);

			break;
		case DEL:
			pAct = new Delete(this);
			break;
		case CUT:
			pAct = new Cut(this);
			break;
		case COPY:
			pAct = new Copy(this);
			break;
		case PASTE:
			pAct = new Paste(this);
			break;
		case ADD_CONNECTOR:
			pAct = new AddConnectors(this);

			break;
		case SWITCH_SIM_MODE:
			pAct = new Switch(this);

			break;
		case EDIT_STAT:
			pAct = new Edit(this);

			break;
		case SAVE:
			pAct = new Save(this);
			break;
		case LOAD:
			pAct = new Load(this);
			break;
		}
	}
	else
	{
		switch (ActType)
		{
		case SWITCH_DSN_MODE:
			pAct = new Switch(this);
			break;
		case VALIDATE:
			pAct = new Validate(this);
			break;
		case RUN:
			pAct = new Run(this);
			break;


		}
	}
	//Execute the created action
	if (pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
	}

}



//==================================================================================//
//						Statements Management Functions								//
//==================================================================================//


//Add a statement to the list of statements
void ApplicationManager::AddStatement(Statement *pStat)
{
	if(StatCount < MaxCount)
		StatList[StatCount++] = pStat;
	
}

////////////////////////////////////////////////////////////////////////////////////
Statement *ApplicationManager::GetStatement(Point P) const
{
	//If this point P(x,y) belongs to a statement return a pointer to it.
	//otherwise, return NULL
	//Note:Add another test here to check whether you're inside the drawing area

	for (int i = 0; i < StatCount; i++) {
		Conditional*TestConditional = dynamic_cast<Conditional*>(StatList[i]);
		if (TestConditional) {
			if (TestConditional->PointInStatement(P)) {
				return StatList[i];
			}
			else {
				continue;
			}
		}
		End*TestEnd = dynamic_cast<End*>(StatList[i]);
		if (TestEnd) {
			if (TestEnd->PointInStatement(P)) {
				return StatList[i];
			}
			else {
				continue;
			}
			
		}
		Start*TestStart = dynamic_cast<Start*>(StatList[i]);
		if (TestStart) {
			if (TestStart->PointInStatement(P)) {
				return StatList[i];
			}
			else {
				continue;
			}
		}
		Read*TestRead = dynamic_cast<Read*>(StatList[i]);
		if (TestRead) {
			if (TestRead->PointInStatement(P)) {
				return StatList[i];
			}
			else {
				continue;
			}
		}
		Write*TestWrite = dynamic_cast<Write*>(StatList[i]);
		if (TestWrite) {
			if (TestWrite->PointInStatement(P)) {
				return StatList[i];
			}
			else {
				continue;
			}
		}
		ValueAssign*TestValue = dynamic_cast<ValueAssign*>(StatList[i]);
		if (TestValue) {
			if (TestValue->PointInStatement(P)) {
				return StatList[i];
			}
			else {
				continue;
			}
		}
		VariableAssign*TestVariable = dynamic_cast<VariableAssign*>(StatList[i]);
		if (TestVariable) {
			if (TestVariable->PointInStatement(P)) {
				return StatList[i];
			}
			else {
				continue;
			}
		}
		OperatorAssign*TestOperator = dynamic_cast<OperatorAssign*>(StatList[i]);
		if (TestOperator) {
			if (TestOperator->PointInStatement(P)) {
				return StatList[i];
			}
			else {
				continue;
			}
		}

	}

	return NULL;
}
////////////////////////////////////////////////////////////////////////////////////
//Returns the selected statement
Statement *ApplicationManager::GetSelectedStatement() const
{	return pSelectedStat;	}

////////////////////////////////////////////////////////////////////////////////////
//Set the statement selected by the user
void ApplicationManager::SetSelectedStatement(Statement *pStat)
{	pSelectedStat = pStat;	}

////////////////////////////////////////////////////////////////////////////////////
//Returns the Clipboard
Statement *ApplicationManager::GetClipboard() const
{	return pClipboard;	}

////////////////////////////////////////////////////////////////////////////////////
//Set the Clipboard
void ApplicationManager::SetClipboard(Statement *pStat)
{	pClipboard = pStat;	}

void ApplicationManager::SetSelectedConnector(Connector * pCon)
{
	pSelectedConnector = pCon;
}

Connector * ApplicationManager::GetSelectedConnector() const
{
	return pSelectedConnector;
}

Statement * ApplicationManager::GetStatementFromID(int ID)
{
	for(int i = 0; i < StatCount; i++) {
		if (StatList[i]->getID() == ID) {
			return StatList[i];
		}
	}
	return NULL;
}


//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//


//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
	pOut->ClearDrawArea();

	//Draw all statements
	for(int i=0; i<StatCount; i++)
		StatList[i]->Draw(pOut);
	
	//Draw all connections
	for(int i=0; i<ConnCount; i++)
		ConnList[i]->Draw(pOut);

}
void ApplicationManager::SaveAll(ofstream & Outputfile)
{
	Outputfile << StatCount << endl;
	for (int i = 0; i < StatCount; i++) {
		StatList[i]->Save(Outputfile);
	}
	Outputfile << ConnCount << endl;
	for (int i = 0; i < ConnCount; i++) {
		ConnList[i]->Save(Outputfile);
	}
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
////////////////////////////////////////////////////////////////////////////////////


//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<StatCount; i++)
		delete StatList[i];
	for(int i=0; i<StatCount; i++)
		delete ConnList[i];
	delete pIn;
	delete pOut;
	
}

void ApplicationManager::AddConnector(Connector * pConn)
{
	if (ConnCount != MaxCount)
	{
		pConn->getDstStat()->SetIsInConnected(true);
		ConnList[ConnCount] = pConn;
		ConnCount++;
	}
}

Connector * ApplicationManager::GetConnector(Point P) const
{
	for (int i = 0; i < ConnCount; i++) {
		if (ConnList[i]->isInConnector(P)) {
			return ConnList[i];
		}
	}
	return NULL;
}


void ApplicationManager::RemoveConnFromList(Connector * pConn)
{
	int i = 0;
	while (i < ConnCount && pConn != ConnList[i])
		i++;
	if (i < ConnCount)
	{
		ConnList[i] = ConnList[ConnCount - 1];
		ConnList[ConnCount - 1] = NULL;
		ConnCount--;
	}
} 
void ApplicationManager::RemoveStatFromList(Statement * pStat)
{
	int i = 0;
	while (i < StatCount && pStat != StatList[i])
		i++;
	if (i < StatCount)
	{
		StatList[i] = StatList[StatCount - 1];
		StatList[StatCount - 1] = NULL;
		StatCount--;
	}

}
Connector * ApplicationManager::GetConnectorToStat(Statement * pStat)
{
	for (int i = 0; i < ConnCount; i++)
	{
		if (pStat == ConnList[i]->getDstStat())
		{
			return ConnList[i];
		}
	}
	return NULL;
}

Statement * ApplicationManager::GetStart()
{
	for (int i = 0; i < StatCount; i++)
	{
		if (!(StatList[i]->CanBeConnected()))
		{
			return StatList[i];
		}
	}
	return nullptr;
}

int ApplicationManager::GetStatCount() const
{
	return StatCount;
}
int ApplicationManager::GetConnCount() const
{
	return ConnCount;
}
Statement ** ApplicationManager::getStatList()
{
	return StatList;
}
const Connector * ApplicationManager::getConnList()
{
	return *ConnList;
}

void ApplicationManager::EmptyAllLists()
{
	for (int i = 0; i < ConnCount; i++)
	{
		delete ConnList[i];
	}
	for (int i = 0; i < StatCount; i++)
	{
		delete StatList[i];
	}
	ConnCount = 0;
	StatCount = 0;
}



void ApplicationManager::AddIntVariable(string x, double a)
{
	int found = 0;
	if (IntVariableCount < MaxCount)
	{
		for (int i = 0; i < IntVariableCount; i++)
		{
			if (IntVariables[i] == x)
			{
				found++;
			}
		}
		if (found == 0)
		{
			IntVariables[IntVariableCount] = x;
			IntVariableValues[IntVariableCount] = a;
			IntVariableCount++;
		}
		if (found != 0)
		{
			for (int i = 0; i < IntVariableCount; i++)
			{
				if (IntVariables[i] == x)
				{
					IntVariableValues[i] = a;
				}
			}
		}
	}
}

const string *  ApplicationManager::GetIntVariable()
{
	return IntVariables;
}



int ApplicationManager::GetIntVariableCount() const
{
	return IntVariableCount;
}

double ApplicationManager::ReturnValue(string x)
{
	for (int i = 0; i < IntVariableCount; i++)
	{
		if (IntVariables[i] == x)
		{
			return IntVariableValues[i];
		}
	}
	return 0.0;
}


