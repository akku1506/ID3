#include"id3.h"

int main(int argc,  char** argv)
{
  	int x, y; 
	int count =0;
	int line=0;
	int ch;
	vector<vector<int> > data1;
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


	vector<int> attrib_feature;
	for(int i=0;i<y;i++)
		attrib_feature.push_back(1);
	vector<double> noise;
	noise.push_back(0.5);
	noise.push_back(1);
	noise.push_back(5);
	noise.push_back(10);
	file3<<"Noise%		Depth	    Total Nodes	   Terminal Nodes  Training Error     Test Error"<<"\n";
	tree *root=create_id3(data,attrib_feature,NULL,327,y);
	file3<<"0"<<"\t"<<"\t";
	file3<<display_tree(root)<<"\t"<<"\t";
	file3<<count_nodes(root)<<"\t"<<"\t";
	file3<<count_terminal_nodes(root)<<"\t"<<"\t";
	double train_error=calc_error(root,data,y);
	double test_error=calc_error(root,test_data,y);
	file3<<train_error<<"\t"<<"\t"<<test_error<<"\n";

for(int k=0;k<noise.size();k++)
	{
	int change=(noise[k]*data.size())/100;
	cout<<change;
	for(int i=0;i<change;i++)
	{
	int n=rand() % 1000;
	if(data[n][y]==1)
		data[n][y]=0;
	else
		data[n][y]=1;
	}
	root=create_id3(data,attrib_feature,NULL,327,y);
	file3<<noise[k]<<"\t"<<"\t";
	file3<<display_tree(root)<<"\t"<<"\t";
	file3<<count_nodes(root)<<"\t"<<"\t";
	file3<<count_terminal_nodes(root)<<"\t"<<"\t";
	train_error=calc_error(root,data,y);
	test_error=calc_error(root,test_data,y);
	file3<<train_error<<"\t"<<"\t"<<test_error<<"\n";
	for(int i=0;i<y;i++)
		attrib_feature[i]=1;
	}	
	file1.close();
	file2.close();
	file3.close();
	return 0;

}
