#include"id3.h"

using namespace std;
int c=1;
void pruning(tree *root,tree *root_temp,int y)
{
	vector<tree *> temp;
	int label=root->label;
	if(root==NULL||root->child.empty())
	return;

	for(int i=0;i<root->child.size();i++)
	{
		pruning(root->child[i],root_temp,y);
		temp.push_back(root->child[i]);
	}
	double test_error=calc_error(root_temp,test_data,y);
	//file3<<"TEST ERROR="<<test_error<<"\n";
//c++;


	root->child.clear();
	if(root->obj.negative>root->obj.positive)
		root->label=0;
	else
		root->label=1;
	double new_test_error=calc_error(root_temp,test_data,y);
	//file3<<"newTEST ERROR="<<new_test_error<<"\n";
	if(new_test_error>=test_error)
	{
	for(int i=0;i<temp.size();i++)
		root->child.push_back(temp[i]);
	root->label=label; 
	}
	else
	{
//	file3<<display_tree(root_temp)<<"\t"<<"\t";
	file3<<count_nodes(root_temp)<<"\t"<<"\t";
	file3<<count_terminal_nodes(root_temp)<<"\t"<<"\t";
	double train_error=calc_error(root_temp,data,y);
	file3<<train_error<<"\t"<<"\t"<<new_test_error<<"\n";

	}	
}


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
	initialise(y);
	tree *root=create_id3(data,attrib_feature,NULL,327,y);
//	file3<<"Depth"<<"\t"
	file3<<"Total Nodes"<<"\t"<<"Terminal Nodes"<<"\t"<<"Training Error"<<"Test Error"<<"\n";
//	file3<<display_tree(root)<<"\t"<<"\t";
	file3<<count_nodes(root)<<"\t"<<"\t";
	file3<<count_terminal_nodes(root)<<"\t"<<"\t";
	double train_error=calc_error(root,data,y);
	double test_error=calc_error(root,test_data,y);
	file3<<train_error<<"\t"<<"\t"<<test_error<<"\n";

	/*cout<<"BEFORE PRUNING"<<"\n";
	cout<<"DEPTH="<<display_tree(root);
	cout<<"Total nodes="<<count_nodes(root);
//	cout<<"Terminal nodes="<<count_terminal_nodes(root);

	double train_error=calc_error(root,data,y);
	double test_error=calc_error(root,test_data,y);
	cout<<"TRAIN ERR"<<train_error<<"\t"<<"TEST ERR"<<test_error;./*/
	tree *root_temp= root;	
	pruning(root,root_temp,y);

/*	cout<<"after PRUNING"<<"\n";
	cout<<"DEPTH="<<display_tree(root);
	cout<<"Total nodes="<<count_nodes(root);
//	cout<<"Terminal nodes="<<count_terminal_nodes(root);

	train_error=calc_error(root,data,y);
	test_error=calc_error(root,test_data,y);
	cout<<"TRAIN ERR"<<train_error<<"\t"<<"TEST ERR"<<test_error;
*/
//	file3<<display_tree(root)<<"\t"<<"\t";
	file3<<count_nodes(root)<<"\t"<<"\t";
	file3<<count_terminal_nodes(root)<<"\t"<<"\t";
	train_error=calc_error(root,data,y);
	test_error=calc_error(root,test_data,y);
	file3<<train_error<<"\t"<<"\t"<<test_error<<"\n";

	file1.close();
	file2.close();
	file3.close();
	return 0;

}
