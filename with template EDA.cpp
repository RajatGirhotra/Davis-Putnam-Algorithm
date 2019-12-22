/*
 * Equivalence Checker for netlists
 *
 *
 * Name 1: ...
 * Matriculation Number 1: ...
 * 
 * Name 2: ...
 * Matriculation Number 2: ...
 *
 */

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <cstdlib>

using namespace std;

typedef enum
{
	AND,
	OR,
	INV,
	XOR,
	ZERO,
	ONE,
	UNDEFINED
} GateType;

typedef struct
{
	GateType type;
	vector<int> nets;
} Gate;

typedef vector<Gate> GateList;

int netCount1, netCount2;
vector<string> inputs1, outputs1, inputs2, outputs2;
map<string, int> map1, map2;
GateList gates1, gates2;

int readFile(string filename, int & netCount, vector<string> & inputs, vector<string> & outputs, map<string, int> & map, GateList & gates)
{
	ifstream file(filename.c_str());
	if (! file.is_open())
	{
		return -1;
	}
	string curLine;
	// net count
	getline(file, curLine);
	netCount = atoi(curLine.c_str());
	// inputs
	getline(file, curLine);
	stringstream inputsStream(curLine);
	string buf;
	while (inputsStream >> buf)
	{
		inputs.push_back(buf);
	}
	// outputs
	getline(file, curLine);
	stringstream outputsStream(curLine);
	while (outputsStream >> buf)
	{
		outputs.push_back(buf);
	}
	// mapping
	for (size_t i=0; i<inputs1.size() + outputs1.size(); i++)
	{
		getline(file, curLine);
		stringstream mappingStream(curLine);
		mappingStream >> buf;
		int curNet = atoi(buf.c_str());
		mappingStream >> buf;
		map[buf] = curNet;
	}
	// empty line
	getline(file, curLine);
	if (curLine.length() > 1)
	{
		return -1;
	}
	// gates
	while (getline(file, curLine))
	{
		stringstream gateStream(curLine);
		gateStream >> buf;
		Gate curGate;
		curGate.type = (buf == "and" ? AND : buf == "or" ? OR : buf == "inv" ? INV : buf == "xor" ? XOR : buf == "zero" ? ZERO : buf == "one" ? ONE : UNDEFINED);
		if (curGate.type == UNDEFINED)
		{
			return -1;
		}
		while (gateStream >> buf)
		{
			int curNet = atoi(buf.c_str());
			curGate.nets.push_back(curNet);
		}
		gates.push_back(curGate);
	}
	return 0;
}

int readFiles(string filename1, string filename2)
{
	if (readFile(filename1, netCount1, inputs1, outputs1, map1, gates1) != 0)
	{
		return -1;
	}
	if (readFile(filename2, netCount2, inputs2, outputs2, map2, gates2) != 0)
	{
		return -1;
	}
	return 0;
}

// Prints internal data structure
void printData(int & netCount, vector<string> & inputs, vector<string> & outputs, map<string, int> & map, GateList & gates)
{
	cout << "Net count: " << netCount << "\n\n";
	cout << "Inputs:\n";
	for (size_t i=0; i<inputs.size(); i++)
	{
		cout << inputs[i] << "\n";
	}
	cout << "\n";
	cout << "Outputs:\n";
	for (size_t i=0; i<outputs.size(); i++)
	{
		cout << outputs[i] << "\n";
	}
	cout << "\n";
	cout << "Mapping (input/output port to net number):\n";
	for (size_t i=0; i<inputs.size(); i++)
	{
		cout << inputs[i] << " -> "<< map[inputs[i]] << "\n";
	}
	for (size_t i=0; i<outputs.size(); i++)
	{
		cout << outputs[i] << " -> "<< map[outputs[i]] << "\n";
	}
	cout << "\n";
	cout << "Gates:\n";
	for (size_t i=0; i<gates.size(); i++)
	{
		Gate & curGate = gates[i];
		cout << (curGate.type == AND ? "AND" : curGate.type == OR ? "OR" : curGate.type == INV ? "INV" : curGate.type == XOR ? "XOR" : curGate.type == ZERO ? "ZERO" : curGate.type == ONE ? "ONE" : "ERROR");
		cout << ": ";
		for (size_t j=0; j<curGate.nets.size(); j++)
		{
			cout << curGate.nets[j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

// Prints the internal data structure for netlist 1 or 2
void printDataForNetlist(int netlistNumber)
{
	if (netlistNumber == 1)
	{
		printData(netCount1, inputs1, outputs1, map1, gates1);
	}
	else if (netlistNumber == 2)
	{
		printData(netCount2, inputs2, outputs2, map2, gates2);
	}
	else
	{
		cout << "Invalid netlist number " << netlistNumber << " (must be 1 or 2)\n";
	}
}


//
// Add auxiliary functions here (if necessary)
//

void printcnf(vector<vector<int>>&cnf) {
    for size_c i=0; i<cnf.size(); i++){
        cout<< "CNF is ( ";
        for size_c j=0; j<cnf[i].size(); j++) {
            cout<< cnf[i][j] << " ";
        }
        cout<< ")\n";
    }
    cout << endl;
}

int test_emptyclause(vector<vector<int>>cnf)
{
    vector<int>::size_type CNF = cnf.size();
    for (size_c i=0; i<cnf; i++) {
        if (cnf[i].size()==0){
            return 1;
        }
    }
    return 0;
}


void DP(vector< vector<int> > cnf)
{
	//
	// Add code for Davis Putnam algorithm here
	//
    
    vector<int>::size_type input1 = inputs1.size();
    vector<int>::size_type output1 = outputs1.size();
    vector<int>::size_type output2 = outputs2.size();
    
    //Unit clause rule
    
    //declare an int
    
    int icnf; //maybe a value
    
    for (size_c i=0; i<cnf; i++){
        
        if (cnf[i].size()==1 {
    
            //to write find icnf
            
            for icnf!=0;
            
            //inside cnf find icnf
            
            for (size_c j=0; j<cnf; j++)
            
            {
                if (cnf[i][j]==icnf)
            
                {
                    cnf.erase(cnf.begin(), cnf.end(), j); //might remove end
                    break;
                }
                
                else if (cnf[i][j]==-icnf)
                
                {
                    cnf.erase(cnf.begin(), cnf.end(), i); //might remove end
                    
                }
            
            }
            
            
            //Terminal conditions
            
            if (cnf.empty()) //check or change to cnf.size
                
                cout << "Not Equivalent \n";
            cout << "cnf is empty \n";
            cout << "Need counter example for solution \n";
            
            //printing counter example
            
            for (size_c i=0; i<inputs1.size(); i++) {
                int m = map1[inputs1[i]]; //might change int i
                
                for (size_c j=0; j<temporary.size(); j++) //check temporary
                    
                    
                    }
            
            else
                
                
                //BACKTRACKING
            {
                
                vector<vector<int> > backtrack(int backtrack_var) //or directly change to int backtrack_var
                {
                    vector<vector<int> > cnf0;
                    cnf0=cnf;
                    
                    if (backtrack_var > 0);
                    
                    {
                        arr[backtrack_var] = 0;
                    }
                    else
                    {
                        arr[-backtrack_var] = 1;
                    }
                    
                    for int i = cnf0().size-1; i>-1 ; i--;
                    {
                        for int j =cnf0[i].size()-1; j>-1; j--;
                        {
                            if (cnf0[i][j]== -backtrack_var)
                            {
                                cnf.erase(cnf0.begin()+i); //try using push back here
                                break;
                            }
                            else if (cnf0[i][j]== backtrack_var)
                            {
                                cnf.erase(cnf0[i].begin()+j);
                            }
                        }
                    }
                    
                    DP(cnf0);
                    
                    vector<vector<int> > cnf1;
                    cnf1=cnf;
                    
                    if (backtrack_var > 0);
                    
                    {
                        arr[backtrack_var] = 1
                    }
                    else
                    {
                        arr[-backtrack_var] = 0
                    }
                    for int i = cnf1().size-1; i>-1; i--;
                    {
                        for int j = cnf1[i].size-1; i>1; i--;
                        {
                            if (cnf[i][j]== -backtrack_var)
                            {
                                cnf.erase(cnf0[i].begin()+j);
                            }
                            else if (cnf[i][j]== backtrack_var)
                            {
                                cnf.erase(cnf0.begin()+i);
                                break;
                            }
                        }
                        
                    }
                    DP(cnf1);
                    
                }
}

int main(int argc, char ** argv)
{
	if (argc != 3)
	{
		cerr << "Wrong argument count!\n";
		return -1;
	}
	if (readFiles(argv[1], argv[2]) != 0)
	{
		cerr << "Error while reading files!\n";
		return -1;
	}

	// The following global variables are now defined (examples are for file xor2.net):
	//
	// int netCount1, netCount2
	// - total number of nets in netlist 1 / 2
	// - e.g. netCount1 is 3
	//
	// vector<string> inputs1, outputs1, inputs2, outputs2
	// - names of inputs / outputs in netlist 1 / 2
	// - e.g. inputs1[0] contains "a_0"
	//
	// map<string, int> map1, map2
	// - mapping from input / output names to net numbers in netlist 1 / 2
	// - e.g. map1["a_0"] is 1, map1["b_0"] is 2, ...
	//
	// GateList gates1, gates2
	// - list (std::vector<Gate>) of all gates in netlist 1 / 2
	// - e.g.:
	//   - gates1[0].type is XOR
	//   - gates1[0].nets is std::vector<int> and contains three ints (one for each XOR port)
	//   - gates1[0].nets[0] is 1 (first XOR input port)
	//   - gates1[0].nets[1] is 2 (second XOR input port)
	//   - gates1[0].nets[2] is 3 (XOR output port)
	
	// Print out data structure - (for debugging)
	cout << "Netlist 1:\n==========\n";
	printDataForNetlist(1);
	cout << "\nNetlist 2:\n==========\n";
	printDataForNetlist(2);

	
    vector< vector<int> > cnf;
    int i;
    int j;
    int k;
    
    for (i=0;i>g1.size();i++) //check if int i to replace or not
    {
        if (g1[i].type == AND )
        {
            vector<int> clause1;
            vector<int> clause2;
            vector<int> clause3;
            clause1.push_back (g1[i].nets[0]);
            clause1.push_back (-(g1[i].nets[2]));
            cnf.push_back(caluse1);
            clause2.push_back (g1[i].nets[1]);
            clause2.push_back (-(g1[i].nets[2]));
            cnf.push_back(caluse2);
            clause3.push_back (-(g1[i].nets[0]));
            clause3.push_back (-(g1[i].nets[1]));
            clause3.push_back (g1[i].nets[2]);
            cnf.push_back(clause3);
        }
        if (g1[i].type == OR)
        {
            vector<int> clause1;
            vector<int> clause2;
            vector<int> clause3;
            clause1.push_back (-(g1[i].nets[0]);
            clause1.push_back (g1[i].nets[2]));
            cnf.push_back(caluse1);
            clause2.push_back (-(g1[i].nets[1]));
            clause2.push_back (g1[i].nets[2]));
            cnf.push_back(caluse2);
            clause3.push_back (g1[i].nets[0]));
            clause3.push_back (g1[i].nets[1]));
            clause3.push_back (-(g1[i].nets[2]));
            cnf.push_back(clause3)
        }
        if (g1[i].type == INV)
        {
            vector<int> clause1;
            vector<int> clause2;
            clause1.push_back (g1[i].nets[0]);
            clause1.push_back (g1[i].nets[1]);
            cnf.push_back(clause1);
            clause2.push_back (-(g1[i].nets[0]);
            clause2.push_back (-(g1[i].nets[1]);
            cnf.push_back(clause2);
        }
        if (g1[i].type == XOR)
          {
           vector<int> clause1;
           vector<int> clause2;
           vector<int> clause3;
           vector<int> clause4;
           clause1.push_back (g1[i].nets[0]);
           clause1.push_back (g1[i].nets[1]);
           clause1.push_back (-(g1[i].nets[2]));
           cnf.push_back(clause1)
           clause2.push_back (-(g1[i].nets[0]));
           clause2.push_back (-(g1[i].nets[1]));
           clause2.push_back (-(g1[i].nets[2]));
           cnf.push_back(clause2);
           clause3.push_back (-(g1[i].nets[0]));
           clause3.push_back (g1[i].nets[1]);
           clause3.push_back (g1[i].nets[2]);
           cnf.push_back(clause3);
           clause4.push_back (g1[i].nets[0]);
           clause4.push_back (-(g1[i].nets[1]));
           clause4.push_back (g1[i].nets[2]);
           cnf.push_back(clause4);
          }
       if (g1[i].type == ZERO)
       {
           vector<int> clause1;
           clause1.push_back (-(g1[i].nets[0]));
           cnf.push_back(clause1);
       }
       if (g1[i].type == ONE)
       vector<int> clause1;
       clause1.push_back (g1[i].nets[0]);
       cnf.push_back(clause1);
       }
       for (j=0;j<g2.size();j++)
       {
       if (g1[j].type == AND )
       {
           vector<int> clause1;
           vector<int> clause2;
           vector<int> clause3;
           clause1.push_back (g1[j].nets[0]+ 1000);
           clause1.push_back (-(g1[j].nets[2]+ 1000));
           cnf.push_back(caluse1);
           clause2.push_back (g1[j].nets[1]+ 1000);
           clause2.push_back (-(g1[j].nets[2]+ 1000));
           cnf.push_back(caluse2);
           clause3.push_back (-(g1[j].nets[0]+ 1000));
           clause3.push_back (-(g1[j].nets[1]+ 1000));
           clause3.push_back (g1[j].nets[2]+ 1000);
           cnf.push_back(clause3);
           }
       if (g1[j].type == OR)
       {
           vector<int> clause1;
           vector<int> clause2;
           vector<int> clause3;
           clause1.push_back (-(g1[j].nets[0]+ 1000);
                              clause1.push_back (g1[j].nets[2]+ 1000));
           cnf.push_back(caluse1);
           clause2.push_back (-(g1[j].nets[1]+ 1000));
           clause2.push_back (g1[j].nets[2]+ 1000));
           cnf.push_back(caluse2);
           clause3.push_back (g1[j].nets[0]+ 1000));
           clause3.push_back (g1[j].nets[1]+ 1000));
           clause3.push_back (-(g1[j].nets[2]+ 1000));
           cnf.push_back(clause3)
       }
        if (g1[j].type == INV)
       {
           vector<int> clause1;
           vector<int> clause2;
           clause1.push_back (g1[j].nets[0]+ 1000);
           clause1.push_back (g1[j].nets[1]+ 1000);
           cnf.push_back(clause1);
           clause2.push_back (-(g1[j].nets[0]+ 1000);
           clause2.push_back (-(g1[j].nets[1]+ 1000);
           cnf.push_back(clause2);
        }
        if (g1[j].type == XOR)
        {
         vector<int> clause1;
         vector<int> clause2;
         vector<int> clause3;
         vector<int> clause4;
         clause1.push_back (g1[j].nets[0]+ 1000);
         clause1.push_back (g1[j].nets[1]+ 1000);
         clause1.push_back (-(g1[j].nets[2]+ 1000));
         cnf.push_back(clause1)
         clause2.push_back (-(g1[j].nets[0]+ 1000));
         clause2.push_back (-(g1[j].nets[1]+ 1000));
         clause2.push_back (-(g1[j].nets[2]+ 1000));
         cnf.push_back(clause2);
         clause3.push_back (-(g1[j].nets[0]+ 1000));
         clause3.push_back (g1[j].nets[1]+ 1000);
         clause3.push_back (g1[j].nets[2]+ 1000);
         cnf.push_back(clause3);
         clause4.push_back (g1[j].nets[0]+ 1000);
         clause4.push_back (-(g1[j].nets[1]+ 1000));
         clause4.push_back (g1[j].nets[2]+ 1000);
         cnf.push_back(clause4);
        }

        if (g1[j].type == ZERO)
        {
         vector<int> clause1;
         clause1.push_back (-(g1[j].nets[0]+ 1000));
         cnf.push_back(clause1);
        }
         if (g1[j].type == ONE)
         vector<int> clause1;
         clause1.push_back (g1[j].nets[0]+ 1000);
         cnf.push_back(clause1);
        }
}
                              
      //
      //
      // last phase
      
      for (size_t i=0; i<inputs1.size; i++)
      
      {
      vector<int> clause1;
      vector<int> clause2;
      
      clause1.push_back (-(map1 [ inputs1 [i] ] ));
      clause1.push_back (map2[ inputs1 [i] ] + 1000 );
      cnf.pus_back(clause1);
      
      clause2.push_back(map1[ inputs [i] ] );
      clause2.push_back (-(map2 [ inputs1 [i] ] + 1000 ));
      cnf.push_back(clause2);
      }
      
      vector<int> CoR; //change name
      for(size_t j=0; j <outputs2.size(); j++) //change j maybe
      {
          vector<int> clause1;
          vector<int> clause2;
          vector<int> clause3;
          vector<int> clause4;
          
          int idNum = 1000+1000+j+1; //change this and learn what
          clause1.push_back (map1 [ outputs2 [j] ] );
          clause1.push_back (map2 [ outputs2 [j] ] + 1000);
          clause1.push_back (-idNum); //check the minus sign edit to plus if poss
          cnf.push_back(clause1);
          clause2.push_back (-(map1 [ outputs2 [j] ] ));
          clause2.push_back (-(map2 [ outputs2 [j] ] +1000 ));
          clause2.push_back (-idNum);
          cnf.push_back(clause2);
          clause3.push_back (-(map1 [ outputs2 [j] ] ));
          clause3.push_back (map2 [ outputs2 [j] ] +1000 );
          clause3.push_back (-idNum);
          cnf.push_back(clause3);
          clause4.push_back (map1 [ outputs2 [j] ] );
          clause4.push_back (-(map2 [ outputs2 [j] ] +1000 ));
          clause4.push_back (-idNum);
          cnf.push_back(clause4);
          
          CoR.push_back( idNum); //change name
      }
      
      cnf.push_back (CoR); //change name
      
      printCNF(cnf);
      
      DP(cnf);
      cout<<"Equivalent"<<endl;
      return 0;
      
      }
