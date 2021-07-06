#ifndef DEFS_H
#define DEFS_H

//This file contains some global constants and definitions to be used in the project.

enum  MODE	//Modes of operation
{
	DESIGN,
	SIMULATION
};

// TODO: Add any action type here
enum ActionType // The actions supported
{
	ADD_START, //Add start statement
	ADD_END,   //Add end statement
	ADD_VALUE_ASSIGN, //Add value assignment statement
	ADD_VAR_ASSIGN,	  //Add variable assignment statement
	ADD_OPER_ASSIGN,  //Add operator assignment statement
	ADD_CONDITION,    //Add a conditional statement (for if and while-loop statements)
	ADD_READ,  //Add read statement
	ADD_WRITE, //Add write statemetn

	ADD_CONNECTOR, //Add a connector between two statements

	SELECT,		//Select a statement, a connector
	EDIT_STAT,	//Edit a statement

	DEL,   //Delete a figure
	COPY,  //Copy a figure
	CUT,   //Cut a figure
	PASTE, //Paste a figure

	SAVE,		//Save the whole graph to a file
	LOAD,		//Load a graph from a file

	VALIDATE,
	RUN,

	SWITCH_DSN_MODE,	//Switch to Design mode
	SWITCH_SIM_MODE,	//Switch to simulatiom mode

	EXIT,		//Exit the application


				//TODO: ADD THE ACTIONS OF SIMULATION MODE


				DRAWING_AREA,  //A click on the drawing area
				OUTPUT_AREA,   //A click on the output area
				DSN_TOOL,	   //A click on an empty place in the design tool bar
				STATUS, 		   //A click on the status bar
				SIM_TOOL           //A click on an empty place in the design tool bar
};

// TODO: you should add more items
enum DesignMenuItem //The items of the design menu --> THE ORDER MATTERS
{
	//Note: Items are ordered here as they appear in menu
	//If you change the menu items order, change the order here too

	ITM_SAVE,
	ITM_LOAD,


	ITM_START,
	ITM_END,////////
	ITM_VALUE_ASSIGN,//simple assignment statement
	ITM_VARIABLE_ASSIGN,///////
	ITM_OPERATOR_ASSIGN,////////
	ITM_COND,		//conditional statement
	ITM_READ,/////////
	ITM_WRITE,/////
	ITM_CONNECT,
	ITM_CPY,
	ITM_CUT,
	ITM_PST,
	ITM_EDIT,
	ITM_DELETE,
	ITM_S_US,
	ITM_SWITCH,


	ITM_EXIT,		//Exit
	ITM_DESIGN_MENU,

	//TODO: Add more items names here

	DSN_ITM_CNT		//no. of design menu items ==> This should be the last line in this enum

};

// TODO: you should add more items if needed
enum SimMenuItem //The items of the simulation menu
{
	//Note: Items are ordered here as they appear in menu
	ITM_VALIDATE,	//Validate
	ITM_RUN,	    //Run
	ITM_SWITCH_,

	//TODO:Add more items names here

	SIM_ITM_CNT		//no. of simulation menu items ==> This should be the last line in this enum

};


enum ArithOp
{
	ADD,
	SUB,
	MULTI,
	DIV,
	INVALID_AOP
};

enum CompOp
{
	EQUAL,
	NOT_EQUAL,
	LESS_THAN,
	LESS_OR_EQUAL,
	MORE_THAN,
	MORE_OR_EQUAL,
	INVALID_COP
};

#ifndef NULL
#define NULL 0
#endif

#endif