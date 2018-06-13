#include"id3.h"

using namespace std;

vector<int> attrib_feature;

void feature_bagging(int num_tree,int y)
{
	
	vector<tree *> bagging;
	
	for(int i=0;i< num_tree;i++)
	{
	for(int k=0;k<y;k++)
		attrib_feature[k]=-1;

	for(int j=0;j<sqrt(y);j++)
	{
	int n=rand() % y;
	attrib_feature[n]=1;		
	}		
	tree *root=create_id3(data,attrib_feature,NULL,327,y);
	bagging.push_back(root);
	}

	int correct=0;
	int incorrect=0;

	for(int i=0;i<data.size();i++)
	{
	int pos_label=0;
	int neg_label=0;
	int bagging_label=-1;
	for(int j=0;j<bagging.size();j++)
		{
		int label = calc_label_classified(bagging[j],data[i]);					
		if(label==1)
			pos_label++;
		else
			neg_label++;		
		}
	if(pos_label>neg_label)
		bagging_label=1;
	else
		bagging_label=0;		
	if(test_data[i][y]==bagging_label)	
		correct++;
	else
		incorrect++;	
	}
	//cout<<"CORRECT"<<correct<<"INCORRECT"<<incorrect<<"\n";
	double per= (double)incorrect/double(data.size());
	file3<<num_tree<<"\t\t\t"<<per*100;


	for(int i=0;i<test_data.size();i++)
	{
	int pos_label=0;
	int neg_label=0;
	int bagging_label=-1;
	for(int j=0;j<bagging.size();j++)
		{
		int label = calc_label_classified(bagging[j],test_data[i]);					
		if(label==1)
			pos_label++;
		else
			neg_label++;		
		}
	if(pos_label>neg_label)
		bagging_label=1;
	else
		bagging_label=0;		
	if(test_data[i][y]==bagging_label)	
		correct++;
	else
		incorrect++;	
	}
	//cout<<"CORRECT"<<correct<<"INCORRECT"<<incorrect<<"\n";
	per= (double)incorrect/double(test_data.size());
	file3<<"\t\t\t"<<per*100<<"\n";


}




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
	for(int i=0;i<y;i++)
		attrib_feature.push_back(-1);
	initialise(y);
	file3<<"Effect of number of trees in the forest on train and test accuracies"<<"\n"<<"\n";	
	//file3<<"Number of trees"<<"\t"<<"Training Error"<<"\t"<<"Testing Error"<<"\n";
	file3<<"Number of trees	    Training Error	   Testing Error"<<"\n";
	int number_tree=5;
	
	for(int x=0;x<10;x++)
		{
			feature_bagging(number_tree,y);
			number_tree=number_tree+5;
		}

	file1.close();
	file2.close();
	file3.close();
	return 0;
}
