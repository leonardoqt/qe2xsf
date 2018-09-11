#include <iostream>
#include <cstring>
#include "vec.h"

using namespace std;

int main()
{
	int el_num, at_num;
	vec *at_l;
	vec cell[3];
	string *el_l;
	int *at_type;
	string tmp;
	string flag_at_num = "number of atoms/cell", flag_el_num = "number of atomic types", flag_end_param = "nstep", flag_el_type = "atomic species";
	string flag_cell = "CELL_PARAMETERS", flag_atom = "ATOMIC_POSITIONS", flag_ang = "angstrom", flag_cry= "crystal";

	// find number of atoms and elements
	getline(cin, tmp, '=');
	while(tmp.find(flag_end_param) == string::npos)
	{
		if(tmp.find(flag_at_num) != string::npos)
			cin >> at_num;
		if(tmp.find(flag_el_num) != string::npos)
			cin >> el_num;
		getline(cin, tmp, '=');
	}

	// define atom, elements related arrays;
	el_l = new string[el_num];
	at_l = new vec[at_num];
	at_type = new int[at_num];

	// get element symbol
	while(tmp.find(flag_el_type) == string::npos)
		getline(cin,tmp);
	for(int t1=0; t1<el_num; t1++)
	{
		cin>>el_l[t1];
		getline(cin,tmp);
	}

	// find cell and atom position
	while(!cin.eof())
	{
		if (tmp.find(flag_cell) != string::npos)
		{
			if(tmp.find(flag_ang) != string::npos)
			{
				cin>>cell[0]>>cell[1]>>cell[2];
			}
			else
			{
				cout<<"Error: only valid for angstrom in CELL_PARAMETERS"<<endl;
				return 0;
			}
		}
		else if (tmp.find(flag_atom) != string::npos)
		{
			if(tmp.find(flag_ang) != string::npos)
			{
				for(int t1=0; t1<at_num; t1++)
				{
					cin>>tmp>>at_l[t1];
					for(int t2=0; t2<el_num; t2++)
						if(el_l[t2] == tmp)
						{
							at_type[t1] = t2;
							break;
						}
				}
			}
			else if(tmp.find(flag_cry) != string:: npos)
			{
				for(int t1=0; t1<at_num; t1++)
				{
					cin>>tmp>>at_l[t1];
					at_l[t1] = cell[0]*at_l[t1].x[0] + cell[1]*at_l[t1].x[1] + cell[2]*at_l[t1].x[2];
					for(int t2=0; t2<el_num; t2++)
						if(el_l[t2] == tmp)
						{
							at_type[t1] = t2;
							break;
						}
				}
			}
			else
			{
				cout<<"Error: ATOMIC_POSITIONS should either be crystal or anstrom"<<endl;
				return 0;
			}
		}
		getline(cin, tmp);
	}

	// Printing out
	cout<<"PRIMVEC"<<endl;
	cout<<cell[0]<<endl<<cell[1]<<endl<<cell[2]<<endl;
	cout<<"PRIMCOORD"<<endl;
	cout<<at_num<<"  "<<1<<endl;
	for(int t1=0; t1<at_num; t1++)
	{
		if (el_l[at_type[t1]].length() == 1)
			cout<<el_l[at_type[t1]]<<' '<<at_l[t1]<<endl;
		else
			cout<<el_l[at_type[t1]]<<' '<<at_l[t1]<<endl;
	}
	return 0;
}
