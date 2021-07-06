#pragma once
#ifndef READ_H
#define READ_H

#include "Statements\Statement.h"
#include "ApplicationManager.h"


//Value Assignment statement class
//The value assignment statement assigns a value to a variable
class Read : public Statement
{
private:
	string Variable;

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
	Read(Point Lcorner, string rVariable="");

	void setVariable(const string &rVariable);


	virtual void Draw(Output* pOut) const;
	Point getLeftCorner()const;
	virtual bool PointInStatement(Point position);
	virtual void Save(ofstream &OutFile);
	virtual void Load(ifstream &Infile);
	virtual void setOutlet();
	virtual void setIntlet();
	virtual void SetDrawingPoint(Point P);

	virtual Statement * Clone();

	virtual bool CheckVariables(string *&arr, int & c);
	virtual bool Simulate(ApplicationManager *pManager = NULL);
	virtual void Edit(ApplicationManager *pManager = NULL);
};

#endif