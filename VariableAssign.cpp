#include "VariableAssign.h"
#include <sstream>

using namespace std;

VariableAssign::VariableAssign(Point Lcorner, string LeftHS, string RightHS):Statement(1, true)
{
	// Note: The LeftHS and RightHS should be validated inside (AddValueAssign) action
	//       before passing it to the constructor of ValueAssign
	LHS = LeftHS;
	RHS = RightHS;

	UpdateStatementText();

	LeftCorner = Lcorner;

//No connectors yet

	setOutlet();
	setIntlet();
}

void VariableAssign::setLHS(const string &L)
{
	LHS = L;
	UpdateStatementText();
}

void VariableAssign::setRHS(const string &R)
{
	RHS = R;
	UpdateStatementText();
}


void VariableAssign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);

}

Point VariableAssign::getLeftCorner() const
{
	return LeftCorner;
}

bool VariableAssign::PointInStatement(Point position)
{
	if (position.x >= LeftCorner.x&&position.x <= LeftCorner.x + UI.ASSGN_WDTH&&position.y >= LeftCorner.y&&position.y <= LeftCorner.y + UI.ASSGN_HI) {
		return true;
	}
	return false;
}

void VariableAssign::Save(ofstream & OutFile)
{ 
	OutFile << "VRBL_ASSIGN  " << ID << "  " << LeftCorner.x << "  " << LeftCorner.y << "  " << LHS << "  " << RHS << endl;
}

void VariableAssign::Load(ifstream & Infile)
{
	Infile >> ID >> LeftCorner.x >> LeftCorner.y >> LHS >> RHS;
	setOutlet();
	setIntlet();
	UpdateStatementText();
}

void VariableAssign::setOutlet()
{
	Outlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

void VariableAssign::setIntlet()
{
	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;
}


//This function should be called when LHS or RHS changes
void VariableAssign::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T << LHS << " = " << RHS;
	Text = T.str();
}

void VariableAssign::SetDrawingPoint(Point P)
{
	LeftCorner = P;
	LeftCorner.x = P.x - UI.ASSGN_WDTH / 2;
	LeftCorner.y = P.y;
	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

Statement * VariableAssign::Clone()
{
	Statement* Clone = new VariableAssign(Point(0, 0), ((VariableAssign*)this)->LHS, ((VariableAssign*)this)->RHS);
	return Clone;
}


bool VariableAssign::CheckVariables(string *&arr, int & c)
{
	if (c == 0)
	{
		return false;
	}
	int z = 0;
	for (int i = 0; i < c; z = ++i)
	{
		if (arr[i] == RHS)
			break;

	}
	if (z == c)
	{
		return false;
	}
	else
	{
		for (int i = 0; i < c; i++)
		{
			if (arr[i] == LHS)
			{

				return true;
			}

		}
		string * temp = new string[c + 1];
		for (int i = 0; i < c; i++)
		{
			temp[i] = arr[i];
		}
		delete[] arr;
		arr = temp;
		arr[c] = LHS;
		c++;
		return true;

	}

}

bool VariableAssign::Simulate(ApplicationManager *pManager)
{
	double Value = pManager->ReturnValue(RHS);
	pManager->AddIntVariable(LHS, Value);
	return true;
}

void VariableAssign::Edit(ApplicationManager *pManager)
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	Point Position;
	//Read the (Position) parameter
	pOut->PrintMessage("Value Assignment Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();

	//TODO: Ask the user in the status bar to enter the LHS and set the data member
	pOut->PrintMessage("Please enter The LHS parameter");
	LHS = pIn->GetVariable(pOut);

	//TODO: Ask the user in the status bar to enter the RHS and set the data member
	pOut->PrintMessage("Please enter The RHS value");
	RHS = pIn->GetVariable(pOut);
	UpdateStatementText();
}