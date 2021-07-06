#ifndef STATEMENT_H
#define STATEMENT_H

#include "..\defs.h"
#include "..\Connector.h"
//class Output;
#include "..\GUI\Output.h"
#include<fstream>
#include<string>
class ApplicationManager;
//Base class for all Statements
class Statement
{
protected:
	const bool CanInconn; // false if it is of type  Start ,, tells if a  connect can connect another statement to it
	bool IsInConnected; // tells if there's an Input Connector connected 
	const int MaxOutConn; // 0 if (End)... 2 if(Conditional) ... 1 (all other Statements)   
	Connector * OutputConn[2];
	int ID;			//Each Statement has an ID --> must be unique
	string Text;	//Statement text (e.g.  "X = 5" OR "salary > 3000" and so on)
	bool Selected;	//true if the statement is selected on the folwchart
	Point Inlet;
	Point Outlet;
	int ActualOutConnectors;

	virtual void UpdateStatementText() = 0;	//is called when any part of the stat. is edited	

	/// Add more parameters if needed.

public:
	Statement(int Num, bool CanConn);
	void SetSelected(bool s);
	bool IsSelected() const;

	virtual void Draw(Output* pOut) const  = 0 ;	//Draw the statement
	virtual bool PointInStatement(Point position) = 0;
	void ReleaseConnector(int i = 0); // Sets the chosen Connector to NULL(i must be 0 or 1)
	int GetMaxOutConn()const;// Gets the max number of output connectors for each type 

	virtual Connector * GetConnecter(int i = 0);// Gets the chosen Connector (i must be 0 or 1 or else it returns NULL)
	void setConnector(Connector*C,int i=0);

	void SetIsInConnected(bool B);// Sets the tha parameter IsInConnected

	bool GetIsInConnected()const; //Gets the tha parameter IsInConnected

	bool CanBeConnected()const; //Gets the parameter CanInconn 
	Point getInlet()const;
	Point getOutlet()const;
	int getID();
	virtual void setOutlet()=0 ;
	virtual void setIntlet()=0 ;

	virtual Statement * Clone() = 0;

	virtual void SetDrawingPoint(Point P) = 0;

	int GetActOutConn()const;
	void AddActual();
	void DecrAct();
	// Function used to Clone this Statement and returns pointer to the Cloned statement

	
	

	///TODO:The following functions should be supported by the Statement class
	///		It should then be overridden by each derived Statement
	///		Decide the parameters that you should pass to each function and its return type

	virtual void Save(ofstream &OutFile) = 0;	//Save the Statement parameters to a file
	virtual void Load(ifstream &Infile) = 0;	//Load the Statement parameters from a file

	virtual void Edit(ApplicationManager *pManager) = 0;		//Edit the Statement parameter

	virtual bool Simulate(ApplicationManager *pManager = NULL);	//Execute the statement in the simulation mode

	virtual bool CheckVariables(string *&arr, int & c) = 0;
	//[BONUS] virtual void GenerateCode(ofstream &OutFile) = 0;	//write the statement code to a file


	///TODO: Add more functions if needed

	
};

#endif