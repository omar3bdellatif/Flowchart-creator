#include "OperatorAssign.h"
#include <sstream>

using namespace std;

OperatorAssign::OperatorAssign(Point Lcorner, string LeftHS, string RightHS):Statement(1, true)
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

void OperatorAssign::setLHS(const string &L)
{
	LHS = L;
	UpdateStatementText();
}

void OperatorAssign::setRHS(const string &R)
{
	RHS = R;
	UpdateStatementText();/////////
}

void OperatorAssign::setRHS1(const string & R)
{
	RHS1 = R;
	UpdateStatementText();
}

void OperatorAssign::setOperator(const string & R)
{
	arithmeticoperator = R;
	UpdateStatementText();
}

void OperatorAssign::setRHS3(const string & R)
{
	RHS3 = R;
	UpdateStatementText();
}




void OperatorAssign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);

}

Point OperatorAssign::getLeftCorner() const
{
	return LeftCorner;
}

bool OperatorAssign::PointInStatement(Point position)
{
	if (position.x >= LeftCorner.x&&position.x <= LeftCorner.x + UI.ASSGN_WDTH&&position.y >= LeftCorner.y&&position.y <= LeftCorner.y + UI.ASSGN_HI) {
		return true;
	}
	return false;
}

void OperatorAssign::Save(ofstream & OutFile)
{
	string type = getOperator();
	OutFile << "OP_ASSIGN  " << ID << "  " << LeftCorner.x << "  " << LeftCorner.y << "  " << LHS << "  " << RHS1 << "  " << type <<"  "<< RHS3 << endl;
}

string OperatorAssign::getOperator()
{
	if (arithmeticoperator == "+") {
		return "PLUS";
	}
	else if (arithmeticoperator == "-") {
		return"MINUS";
	}
	else if (arithmeticoperator == "/") {
		return "DIVIDE";
	}
	else {
		return"MUL";
	}

}

void OperatorAssign::Load(ifstream & Infile)
{
	string Operator;
	Infile >> ID >> LeftCorner.x >> LeftCorner.y >> LHS >> RHS1 >> Operator >> RHS3;
	ReversegetOperator(Operator);
	setOutlet();
	setIntlet();
	UpdateStatementText();
}

void OperatorAssign::ReversegetOperator(string S)
{
	if (S == "PLUS") {
		arithmeticoperator= "+";
	}
	else if (S == "MINUS") {
		arithmeticoperator = "-";
	}
	else if (S == "DIVIDE") {
		arithmeticoperator = "/";
	}
	else {
		arithmeticoperator = "*";
	}
}

void OperatorAssign::setOutlet()
{
	Outlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

void OperatorAssign::setIntlet()
{
	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

}


//This function should be called when LHS or RHS changes
void OperatorAssign::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T << LHS << " = " << RHS1<<" "<<arithmeticoperator<<" "<<RHS3;
	Text = T.str();
}

Statement * OperatorAssign::Clone()
{
	Statement* Clone = new OperatorAssign(Point(0, 0), ((OperatorAssign*)this)->LHS, ((OperatorAssign*)this)->RHS);
	return Clone;
}
void OperatorAssign::SetDrawingPoint(Point P)
{
	LeftCorner = P;
	LeftCorner.x = P.x - UI.ASSGN_WDTH / 2;
	LeftCorner.y = P.y;

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

bool OperatorAssign::CheckVariables(string * &arr, int & c)
{
	
	if (c == 0)
	{
		if (IsVariable(RHS1) || IsVariable(RHS3))
		{
			return false;
		}
		else
		{
			arr[0] = LHS;
			c++;
			return true;
		}
	}
	if (IsVariable(RHS1))
	{
		int i = 0;
		while (i < c)
		{
			if (arr[i] == RHS1)
			{
				break;
			}
			else
			{
				i++;
			}
			
		}
		if (i == c)return false;
	}

	if (IsVariable(RHS3))
	{
		int i = 0;
		while (i < c)
		{
			if (arr[i] == RHS3)
				break;
			else
			{
				i++;
			}
		}
		if (i == c)return false;
	}
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


bool OperatorAssign::Simulate(ApplicationManager *pManager)
{
	
	double D1, D3;
	if (IsValue(RHS1))
	{
		D1 = atof(RHS1.c_str());
	}
	else
	{
		D1 = pManager->ReturnValue(RHS1);
	}

	if (IsValue(RHS3))
	{
		D3 = atof(RHS3.c_str());
	}
	else
	{
		D3 = pManager->ReturnValue(RHS3);
	}
	if (arithmeticoperator == "+")
	{
		pManager->AddIntVariable(LHS, D1 + D3);
	}
	else if (arithmeticoperator == "-")
	{
		pManager->AddIntVariable(LHS, D1 - D3);
	}
	else if (arithmeticoperator == "*")
	{
		pManager->AddIntVariable(LHS, D1 * D3);
	}
	else
	{
		pManager->AddIntVariable(LHS, D1 / D3);
	}
	return true;
}

void OperatorAssign::Edit(ApplicationManager *pManager)
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	Point Position;
	//Read the (Position) parameter
	pOut->PrintMessage("Operator Assignment Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();

	//TODO: Ask the user in the status bar to enter the LHS and set the data member
	pOut->PrintMessage("Please enter The LHS parameter");
	LHS = pIn->GetVariable(pOut);

	//TODO: Ask the user in the status bar to enter the RHS and set the data member
	pOut->PrintMessage("Please enter The RHS parameter,click anywhere to continue");
	Point P;
	pIn->GetPointClicked(P);
	pOut->PrintMessage("Please enter the parameter to the left of the arithmetic operator");
	string temp1;
	RHS1 = pIn->GetString(pOut);
	while (ValueOrVariable(RHS1) == 2) {
		pOut->PrintMessage("Please enter a valid parameter to the right of the arithmetic operator");
		RHS1 = pIn->GetString(pOut);
	}
	pOut->PrintMessage("Please enter an arithmetic operator");
	int x = pIn->GetArithOperator(pOut);
	string temp;
	if (x == 0) {
		arithmeticoperator = '+';
	}
	else if (x == 1) {
		arithmeticoperator = '-';
	}
	else if (x == 2) {
		arithmeticoperator = '*';
	}
	else {
		arithmeticoperator = '/';
	}

	pOut->PrintMessage("Please enter the parameter to the right of the arithmetic operator");
	string temp2;
	RHS3 = pIn->GetString(pOut);
	while (ValueOrVariable(RHS3) != 0 && ValueOrVariable(RHS3) != 1) {
		pOut->PrintMessage("Please enter a valid parameter to the right of the arithmetic operator");
		RHS3 = pIn->GetString(pOut);
	}
	RHS = temp1 + temp + temp2;

	UpdateStatementText();
}
