#include"id3.h"

using namespace std;

int main(int argc,  char** argv)
{
  	int x, y; 
	int count =0;
	int line=0;
	int ch;
	vector<vector<int> > data1;
	vector<int> attrib_feature;
	ifstream file1(argv[1]);
	ifstream file2(argv[2]);
	file3.open(argv[3]);
	file1>>x;
	file1>>y;
	vector<int> d1;
	while(!file1.eof())
		{
			file1>>ch;
			d1.push_back(ch);
			count++;
			if(count == y+1)
				{
					count=0;
					line++;
					data.push_back(d1);
					d1.clear();
				}
		}


	d1.clear();
	count=0;
	while(!file2.eof())
		{
			file2>>ch;
			d1.push_back(ch);
			count++;
			if(count == y+1)
				{
					count=0;
					line++;
					test_data.push_back(d1);
					d1.clear();
				}
		}
	for(int i=0;i<y;i++)
		attrib_feature.push_back(1);


	file3<<"EFFECT OF EARLY STOPPING"<<"\n";
//	file3<<"Depth"<<"\t"<<"    Total Nodes"<<"\t"<<"  Terminal Nodes"<<"\t"<<"  Training Error"<<"\t"<<"    Test Error"<<"\n";
	file3<<"Depth	    Total Nodes	  Terminal Nodes  Training Error     Test Error"<<"\n";
	for(int k=9;k<=y;k=k+10)	
	{
	initialise(y);
	tree *root=create_id3(data,attrib_feature,NULL,327,k);
	file3<<display_tree(root)<<"\t"<<"\t";
	file3<<count_nodes(root)<<"\t"<<"\t";
	file3<<count_terminal_nodes(root)<<"\t"<<"\t";
	double train_error=calc_error(root,data,y);
	double test_error=calc_error(root,test_data,y);
	file3<<train_error<<"\t"<<"\t"<<test_error<<"\n";
	for(int i=0;i<y;i++)
		attrib_feature[i]=1;
	}
	initialise(y);
	tree *root=create_id3(data,attrib_feature,NULL,327,y);
	file3<<display_tree(root)<<"\t"<<"\t";
	file3<<count_nodes(root)<<"\t"<<"\t";
	file3<<count_terminal_nodes(root)<<"\t"<<"\t";
	double train_error=calc_error(root,data,y);
	double test_error=calc_error(root,test_data,y);
	file3<<train_error<<"\t"<<"\t"<<test_error<<"\n";
	file3<<"\n";	
	file3<<"Number of times an attribute is used as the splitting function"<<"\n";
	file3<<"Attribute"<<"\t"<<"Frequency"<<"\n";	
	map<int,int>::iterator it1;		
	for(it1=attrib_freq.begin();it1!=attrib_freq.end();it1++)
	{	
	file3<<it1->first<<"\t"<<"\t"<<it1->second<<"\n";
	}
	file1.close();
	file2.close();
	file3.close();
	return 0;
}
