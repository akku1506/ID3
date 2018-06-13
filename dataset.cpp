#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
using namespace std;
struct label_comparison
{
	bool operator()(const vector<int>& lhs,const vector<int>& rhs)const	
	{
		return lhs[85]<rhs[85];
	}
};


ofstream file3;
ofstream file4;
int main(int argc,  char** argv)
{
  	int x, y; 
	int count =0;
	int line=0;
	int ch;
	vector<vector<int> > data1;
	vector <int> d1;
	ifstream file1(argv[1]);
	ifstream file2(argv[2]);
	file3.open(argv[3]);
	file4.open(argv[4]);
	file1>>x;
	file1>>y;
	while(!file1.eof())
		{
			file1>>ch;
			d1.push_back(ch);
			count++;
			if(count == y+1)
				{
					count=0;
					line++;
					data1.push_back(d1);
					d1.clear();
				}
		}

	sort(data1.begin(),data1.end(),label_comparison());
	count=0;
	file3<<1000<<"\n";
	file3<<y<<"\n";
	
	for(int i=data1.size()-1;i>=0;i--)
	{				
		count++;		
		for(int j=0;j<data1[i].size();j++)		
			file3<<data1[i][j]<<"\t";
		file3<<"\n";			
		if(count==1000)
			break;

	}
	count=0;
	d1.clear();
	data1.clear();
	while(!file2.eof())
		{
			file2>>ch;
			d1.push_back(ch);
			count++;
			if(count == y+1)
				{
					count=0;
					line++;
					data1.push_back(d1);
					d1.clear();
				}
		}


	sort(data1.begin(),data1.end(),label_comparison());
	count=0;
	for(int i=data1.size()-1;i>=0;i--)
	{				
		count++;		
		for(int j=0;j<data1[i].size();j++)		
			file4<<data1[i][j]<<"\t";
		file4<<"\n";			
//		if(count==2000)
//			break;

	}
	file1.close();
	file2.close();
	file3.close();
	file4.close();
	return 0;
}
