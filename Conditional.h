#pragma once
#ifndef CONDITIONAL_H
#define CONDITIONAL_H

#include "Statements\Statement.h"
#include "ApplicationManager.h"

//Value Assignment statement class
//The value assignment statement assigns a value to a variable
class Conditional : public Statement
{
private:
	string LHS;	//Left Handside of the assignment (name of a variable)
	string Comparator;
	string RHS;	//Right Handside (Value)

						//Each statement type in flowchart has a predefined number of (output) connectors
							//For example, conditional statement always has 2 output connectors

							//Note: We don't need to keep track with input connectors
							//      Whenever we want to iterate on all statements of the flowchart
							//      we will begin with start statement then its output connector
							//      then the connector's destination statement and so on (follow the connectors)

				//A point where connections enters this statement 
					//It's used as the (End) point of the (Input) connectors
					//A point a connection leaves this statement
	Point OutletF;				//It's used as the (Start) point of the (Output) connector

	Point LeftCorner;	//left corenr of the statement block.

	virtual void UpdateStatementText();
	virtual void Save(ofstream &OutFile);
	string getOperator();
	void ReversegetOperator(string S);

public:
	Conditional(Point Lcorner, string LeftHS = "", string RightHS = "",string rComparator="");

	void setLHS(const string &L);
	void setRHS(const string &R);
	void setComparator(const string &C);
	Point getLeftCorner()const;
	Point getFalseOutlet();

	virtual void Draw(Output* pOut) const;
	virtual bool PointInStatement(Point position);
	virtual void Load(ifstream &Infile);
	void CenterToLeftCorner(Point C);
	virtual void setOutlet();
	virtual void setIntlet();
	
	virtual void SetDrawingPoint(Point P);

	virtual Statement * Clone();

	virtual bool CheckVariables(string *&arr, int & c);

	virtual bool Simulate(ApplicationManager *pManager = NULL);
	virtual void Edit(ApplicationManager *pManager = NULL);

};

#endif