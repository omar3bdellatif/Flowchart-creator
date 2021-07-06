#pragma once
#ifndef END_H
#define END_H

#include "Statements\Statement.h"
#include "ApplicationManager.h"


//Value Assignment statement class
//The value assignment statement assigns a value to a variable
class End : public Statement
{
private:
					//A point a connection leaves this statement
					//It's used as the (Start) point of the (Output) connector

	Point LeftCorner;	//left corenr of the statement block.

	virtual void UpdateStatementText();

public:
	End(Point Lcorner);
	virtual void Draw(Output* pOut) const;
	Point getLeftCorner()const;
	virtual bool PointInStatement(Point position);
	virtual void Save(ofstream &OutFile);
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
