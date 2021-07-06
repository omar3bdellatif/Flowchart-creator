#include "Conditional.h"
#include <sstream>

using namespace std;

Conditional::Conditional(Point Lcorner, string LeftHS, string RightHS,string rComparator):Statement(2, true)
{
	// Note: The LeftHS and RightHS should be validated inside (AddValueAssign) action
	//       before passing it to the constructor of ValueAssign
	LHS = LeftHS;
	RHS = RightHS;
	Comparator = rComparator;

	UpdateStatementText();

	LeftCorner = Lcorner;



	setOutlet();
	setIntlet();
}

void Conditional::setLHS(const string &L)
{
	LHS = L;
	UpdateStatementText();
}

void Conditional::setRHS(const string &R)
{
	RHS = R;
	UpdateStatementText();
}

void Conditional::setComparator(const string &C)
{
	Comparator = C;
	UpdateStatementText();
}

Point Conditional::getLeftCorner() const
{
	return LeftCorner;
}

Point Conditional::getFalseOutlet()
{
	if (this) {
		return OutletF;
	}
	else {
		return Point(0, 0);
	}
}


void Conditional::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawConditionalStat(LeftCorner, UI.CON_WDTH, UI.CON_HI, Text, Selected);

}

bool Conditional::PointInStatement(Point position)
{
	if (position.x >= LeftCorner.x&&position.x <= LeftCorner.x + UI.CON_WDTH&&position.y >= LeftCorner.y - UI.CON_HI / 2 && position.y <= LeftCorner.y + UI.CON_HI / 2) {
		return true;
	}
	return false;
}

void Conditional::Load(ifstream & Infile)
{
	Point P;
	string S;
	Infile >> ID >> P.x >> P.y >> LHS >> S >> RHS;
	CenterToLeftCorner(P);
	ReversegetOperator(S);
	setOutlet();
	setIntlet();
	UpdateStatementText();
}

void Conditional::CenterToLeftCorner(Point C)
{
	LeftCorner.x = C.x - (0.5)*UI.CON_WDTH;
	LeftCorner.y = C.y - (0.5)*UI.CON_HI;
}

void Conditional::setOutlet()
{
	OutletF.x = LeftCorner.x;
	OutletF.y = LeftCorner.y;

	Outlet.x = LeftCorner.x + UI.CON_WDTH;
	Outlet.y = LeftCorner.y;
}

void Conditional::setIntlet()
{
	Inlet.x = LeftCorner.x + UI.CON_WDTH / 2;
	Inlet.y = LeftCorner.y - UI.CON_HI / 2;
}


//This function should be called when LHS or RHS changes
void Conditional::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T << LHS << Comparator << RHS;
	Text = T.str();
}

void Conditional::Save(ofstream & OutFile)
{
	string opr = getOperator();
	OutFile << "COND  " << ID << "  " << LeftCorner.x + (0.5)*UI.CON_WDTH << "  " << LeftCorner.y + (0.5)*UI.CON_HI << "  " << LHS << "  "<<opr<<"  " << RHS << endl;
}

string Conditional::getOperator()
{
	if (Comparator == ">") {
		return "GRT";
	}
	else if (Comparator == "<") {
		return "SML";
	}
	else if (Comparator == ">=") {
		return "GRTEQL";
	}
	else if (Comparator == "<=") {
		return "SMLEQL";
	}
	else if (Comparator == "==") {
		return "EQL";
	}
	else {
		return "NOTEQL";
	}
}

void Conditional::ReversegetOperator(string S)
{
	if (S == "GRT") {
		Comparator=">";
	}
	else if (S == "SML") {
		Comparator = "<";
	}
	else if (S == "GRTEQL") {
		Comparator = ">=";
	}
	else if (S == "SMLEQL") {
		Comparator = "<=";
	}
	else if (S == "EQL") {
		Comparator = "==";
	}
	else {
		Comparator = "!=";
	}

}
Statement * Conditional::Clone()
{
	Statement *clone = new Conditional(Point(0, 0), ((Conditional*)this)->LHS, ((Conditional*)this)->RHS, ((Conditional*)this)->Comparator);
	return clone;

}
void Conditional::SetDrawingPoint(Point P)
{
	LeftCorner = P;
	LeftCorner.x = P.x - UI.CON_WDTH / 2;
	LeftCorner.y = P.y + UI.CON_HI / 2;

	setOutlet();
	setIntlet();
}

bool Conditional::CheckVariables(string * &arr, int & c)
{
	if (c == 0)
	{
		return false;
	}
	if (IsVariable(LHS))
	{
		int i = 0;
		while (i < c )
		{
			if (arr[i] == LHS)
			{
				break;
			}
			else
			{
				i++;
			}
		}
		if (i == c )return false;
	}

	if (IsVariable(RHS))
	{
		int i = 0;
		while (i < c )
		{
			if (arr[i] == RHS)
			{
				break;
			}
			else
			{
				i++;
			}
		}
		if (i == c )return false;
	}
	return true;
}

bool Conditional::Simulate(ApplicationManager *pManager)
{
	double D1, D2;
	if (IsValue(LHS))
	{
		D1 = atof(LHS.c_str());
	}
	else
	{
		D1 = pManager->ReturnValue(LHS);
	}
	if (IsValue(RHS))
	{
		D2 = atof(RHS.c_str());
	}
	else
	{
		D2 = pManager->ReturnValue(RHS);
	}

	if (Comparator == ">")
	{
		return (D1 > D2);
	}
	else if (Comparator == ">=")
	{
		return (D1 >= D2);
	}
	else if (Comparator == "<")
	{
		return (D1 < D2);
	}
	else if (Comparator == "<=")
	{
		return (D1 <= D2);
	}
	else if (Comparator == "==")
	{
		return (D1 == D2);
	}
	else if (Comparator == "!=")
	{
		return (D1 != D2);
	}
}
void Conditional::Edit(ApplicationManager *pManager)
{
	Input *pIn = pManager->GetInput();
	Output *pOut = pManager->GetOutput();
	Point Position;
	//Read the (Position) parameter
	pOut->PrintMessage("Conditional Assignment Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();

	//TODO: Ask the user in the status bar to enter the LHS and set the data member
	pOut->PrintMessage("Please enter The LHS parameter");
	LHS = pIn->GetString(pOut);
	int x = ValueOrVariable(LHS);
	while (x == 2) {
		pOut->PrintMessage("Please enter a valid LHS parameter");
		LHS = pIn->GetString(pOut);
		x = ValueOrVariable(LHS);
	}

	pOut->PrintMessage("Please enter an arithmetic comparator");
	Comparator = pIn->GetCompOperator(pOut);

	if (x == 0) {
		pOut->PrintMessage("Please enter the RHS parameter (variable)");
		RHS = pIn->GetVariable(pOut);
	}
	else {
		pOut->PrintMessage("Please enter the RHS parameter");
		RHS = pIn->GetString(pOut);
		x = ValueOrVariable(RHS);
		while (x == 2) {
			pOut->PrintMessage("Please enter a valid RHS parameter");
			RHS = pIn->GetString(pOut);
			x = ValueOrVariable(RHS);
		}
	}
	UpdateStatementText();
}

