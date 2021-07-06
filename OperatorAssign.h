#pragma once
#ifndef OPERATOR_ASSIGN_H
#define OPERATOR_ASSIGN_H

#include"Statements\Statement.h"
#include "ApplicationManager.h"

//Value Assignment statement class
//The value assignment statement assigns a value to a variable
class OperatorAssign : public Statement
{
private:
	string LHS;	//Left Handside of the assignment (name of a variable)
	string RHS;	//Right Handside (Value)
	string RHS1;
	string arithmeticoperator;
	string RHS3;

	//Value Assignment Stat. has one Connector to next statement
							//Each statement type in flowchart has a predefined number of (output) connectors
							//For example, conditional statement always has 2 output connectors

							//Note: We don't need to keep track with input connectors
							//      Whenever we want to iterate on all statements of the flowchart
							//      we will begin with start statement then its output connector
							//      then the connector's destination statement and so on (follow the connectors)

					//A point a connection leaves this statement
					//It's used as the (Start) point of the (Output) connector

	Point LeftCorner;	//left corenr of the statement block.

	virtual void UpdateStatementText();

public:
	OperatorAssign(Point Lcorner, string LeftHS = "", string RightHS = "");

	void setLHS(const string &L);
	void setRHS(const string &R);
	void setRHS1(const string &R);
	void setOperator(const string &R);
	void setRHS3(const string &R);

	virtual void Draw(Output* pOut) const;
	Point getLeftCorner()const;
	virtual bool PointInStatement(Point position);
	virtual void Save(ofstream &OutFile);
	string getOperator();
	virtual void Load(ifstream &Infile);
	void ReversegetOperator(string S);
	virtual void setOutlet();
	virtual void setIntlet();

	virtual void SetDrawingPoint(Point P);

	virtual Statement * Clone();

	virtual bool CheckVariables(string *&arr, int & c);

	virtual bool Simulate(ApplicationManager *pManager = NULL);
	virtual void Edit(ApplicationManager *pManager = NULL);
};

#endif