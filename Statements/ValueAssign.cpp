#include "ValueAssign.h"
#include <sstream>
#include "..\ApplicationManager.h"
using namespace std;

ValueAssign::ValueAssign(Point Lcorner, string LeftHS, double RightHS):Statement(1, true)
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

void ValueAssign::setLHS(const string &L)
{
	LHS = L;
	UpdateStatementText();
}

void ValueAssign::setRHS(double R)
{
	RHS = R;
	UpdateStatementText();
}


void ValueAssign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
	
}

Point ValueAssign::getLeftCorner() const
{
	return LeftCorner;
}

bool ValueAssign::PointInStatement(Point position)
{
	if (position.x >= LeftCorner.x&&position.x <= LeftCorner.x + UI.ASSGN_WDTH&&position.y >= LeftCorner.y&&position.y <= LeftCorner.y + UI.ASSGN_HI) {
		return true;
	}
	return false;
}

void ValueAssign::Save(ofstream & OutFile)
{
	OutFile << "VALUE_ASSIGN  " << ID << "  " << LeftCorner.x << "  " << LeftCorner.y << "  " << LHS << "  " << RHS << endl;
}

void ValueAssign::Load(ifstream & Infile)
{
	Infile >> ID >> LeftCorner.x >> LeftCorner.y >> LHS >> RHS;
	setOutlet();
	setIntlet();
	UpdateStatementText();
}

void ValueAssign::setOutlet()
{
	Outlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

void ValueAssign::setIntlet()
{
	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

}


//This function should be called when LHS or RHS changes
void ValueAssign::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T<<LHS<<" = "<<RHS;	
	Text = T.str();
}


void ValueAssign::SetDrawingPoint(Point P)
{
	LeftCorner = P;
	LeftCorner.x = P.x - UI.ASSGN_WDTH / 2;
	LeftCorner.y = P.y;

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

Statement * ValueAssign::Clone()
{
	Statement* Clone = new ValueAssign(Point(0, 0), ((ValueAssign*)this)->LHS, ((ValueAssign*)this)->RHS);
	return Clone;
}

bool ValueAssign::CheckVariables(string *&arr, int & c)
{
	if (c == 0)
	{
		arr[0] = LHS;
		c++;
		return true;
	}
	for (int i = 0; i < c ; i++)
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

bool ValueAssign::Simulate(ApplicationManager *pManager)
{

	pManager->AddIntVariable(LHS, RHS);
	return true;
}
void ValueAssign::Edit(ApplicationManager * pManager)
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
	RHS = pIn->GetValue(pOut);
	UpdateStatementText();
}