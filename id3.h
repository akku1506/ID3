#ifndef id3_INCLUDE
#define id3_INCLUDE

#include<iostream>
#include<fstream>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<map>
#include<queue>
#include<iterator>
#include<algorithm>

using namespace std;

struct node
{
	int positive;
	int negative;
	double entropy;
	int feature;
};

struct tree
{
	tree* parent;
	vector<tree*> child;
	node obj;	
	int value;
	int label;
};

struct label_comparison
{
	bool operator()(const vector<int>& lhs,const vector<int>& rhs)const	
	{
		return lhs[85]<rhs[85];
	}
};

struct pos_neg
{
	int positive;
	int negative;
};

vector<vector<int> > data;
vector<vector<int> > test_data;
double ig;
map<int,node> map_final;
map<int,int> attrib_freq;
ofstream file3;

void initialise(int y)
{
	for(int i=0;i<y;i++)
		attrib_freq[i]=0;
}

double compute_entropy(pos_neg n1)
{
		
	int total = n1.positive + n1.negative;		
	double pi = (double)n1.positive / (double)total;
    	double result = 0.0;
    	if (pi == 1.0 || pi == 0.0)
    		{

        		return result;
    
		}
    	result = pi * (log(pi) / log((double)2)) + (1 - pi)*(log(1 - pi)/log((double)2));
//	cout<<"POSITIVE"<<n1.positive<<"NEGATIVE"<<n1.negative<<"result"<<result;  
  	return -result;
}

int compute_decision_attrib(vector<vector <int> > &data1, vector<int> &attrib)
{
	map<int,node> map_count;
	vector<int> d1;
	int pos;
	ig=37267;
	map_final.clear();
	
	for(int i=0;i<attrib.size();i++)
	{
		if(attrib[i]==-1)
		{							
			continue;		
		}		
		
		for(int j=0;j<data1.size();j++)
		{
			map<int,node>::iterator it(map_count.find(data1[j][i]));		
			if(it!=map_count.end())
			{
				if(data1[j][attrib.size()]==1)
					it->second.positive++;
				else
					it->second.negative++;
			}
			else
			{	
				map_count[data1[j][i]].positive=0;
				map_count[data1[j][i]].negative=0;
				map_count[data1[j][i]].entropy=0;
				map_count[data1[j][i]].feature=i;
				if(data[j][attrib.size()]==1)
					map_count[data1[j][i]].positive=1;
				else
					map_count[data1[j][i]].negative=1;
			}		
		}
		map<int,node>::iterator it;
		double ig_temp=0;
		double split_info=0;
		for(it=map_count.begin();it!=map_count.end();it++)
		{
			pos_neg n2;
			n2.positive=it->second.positive;
			n2.negative=it->second.negative;
			double entropy = compute_entropy(n2);
			it->second.entropy= entropy;
//			cout<<"Value="<<it->first<<"\t"<<"Positive="<<it->second.positive<<"\t"<<"Negative="<<it->second.negative<<"\t "<<"feature="<<it->second.feature<<"entropy="<<it->second.entropy<<"\n";
			//cout<<"\n"<<"Next attribute"<<"\n";		
			double prob=(double) (it->second.positive + it->second.negative)/(double)data.size();
			double split= prob * (log(prob) / log((double)2));
			split_info= split_info - split;
			ig_temp= ig_temp+(prob*it->second.entropy);	
			//cout<<"POSITIVE="<<it->second.positive<<"NEGATIVE="<<it->second.negative<<"PROB="<<prob<<"IG="<<ig_temp<<"\n";		
		}
		if(ig_temp<ig)
		{
			ig=ig_temp;
			map_final.clear();
			map_final.insert(map_count.begin(),map_count.end());
			pos=i;
		}	
		map_count.clear();
	}
	//if(pos==32767)
	//	exit();
	return pos;
}



pos_neg separate_labels(vector<vector <int> > &v1, int attrib)
{
	int positives=0;
	int negatives=0;	
	for(int i=0; i<v1.size();i++)
		{
			if(v1[i][attrib]==0)
				negatives++;
			else
				positives++;
		}
	pos_neg n1;
	n1.negative=negatives;
	n1.positive=positives;
	return n1;
}

int calc_label(vector<vector <int> > &v1, int attrib)
{
	pos_neg n1;
	n1= separate_labels(v1,attrib);		
	if(n1.positive==0)
		return 0;
	else if(n1.negative==0)
		return 1;
	else return 2;
}

tree* create_id3(vector<vector <int> > &v1, vector<int> attrib, tree *p,int k,int depth)
{
	tree *root= new tree;
	root->parent= p;
	root->label=-1;
	root->value=k;
	
//	file3<<"VALUE="<<root->value<<"\t";;
//	root.key=feature;
	//obj?
	//cout<<attrib.size();
	pos_neg n1 = separate_labels(v1,attrib.size());
	//cout<<"positive"<<n1.positive<<"negative"<<n1.negative<<"\n";
	double entropy = compute_entropy(n1);
	root->obj.positive = n1.positive;
	root->obj.negative = n1.negative;
	root->obj.entropy= entropy;
	root->obj.feature=-1;	
	//cout<<"ENTROPY"<<entropy<<"\n";
	if(entropy==0)
	{
	int l=calc_label(v1,attrib.size());
	if(l==0)
		{
		root->label=0;
		}
	else if(l==1)
		{
		root->label=1;
		}
	return root;	
	}
/*	if(find(attrib.begin(),attrib.end(),1)==attrib.end())
	{

	//	tree *c=NULL;
		pos_neg majority= separate_labels(v1,attrib.size());
		if(majority.negative>majority.positive)
		{
			root->label=0;
			//root->child.push_back(c);

		}
		else
		{
			root->label=1;	
			//root->child.push_back(c);

		}
	//file3<<"ROOT"<<root->label<<"\n";
	return root;	
	}	
*/
	int count=0;
	for(int i=0;i<attrib.size();i++)
	{
		if(attrib[i]==-1)
			count++;
		if(count==depth)
		{
			pos_neg majority= separate_labels(v1,attrib.size());
			if(majority.negative>majority.positive)
			{
				root->label=0;
				//root->child.push_back(c);

			}	
		else
		{
			root->label=1;	
			//root->child.push_back(c);

		}
	//file3<<"ROOT"<<root->label<<"\n";
	return root;	
	
		}
	}

//	node new1;
//	new1.positive=n1.positive;
//	new1.negative=n1.negative;
//	new1.entropy=entropy;
			
//	cout<<"VALUE"<<root->value<<"\t"<<root->label<<"\n";
	int pos = compute_decision_attrib(v1,attrib);						
//	file3<<"\n"<<"POS="<<pos;
	root->obj.feature=pos;
	map<int,int>::iterator it1(attrib_freq.find(pos));		
	if(it1!=attrib_freq.end())
	{
	it1->second++;
	}

//	new1.feature=pos;
//	root->obj=new1;
	map<int,node> map_count1;
	map_count1.insert(map_final.begin(),map_final.end());
	map<int,node>::iterator it;
	attrib[pos]=-1;
	vector<vector <int> > v2;
	for(it=map_count1.begin();it!=map_count1.end();it++)
		{		
		v2.clear();
		//cout<<"Value="<<it->first<<"\t"<<"Positive="<<it->second.positive<<"\t"<<"Negative="<<it->second.negative<<"\t "<<"feature="<<it->second.feature<<"entropy="<<it->second.entropy<<"\n";
		for(int i=0;i<v1.size();i++)
		{
			if(v1[i][pos]==it->first)
			{
			v2.push_back(v1[i]);
			}				
		
		}
		tree *k=create_id3(v2,attrib,root,it->first,depth);
		root->child.push_back(k);
		}
	return root;
}

int display_tree(tree *root)
{
	int depth=0;
	queue<tree*> q1;
	queue<tree*> q2;
	q1.push(root);
	while(!q1.empty()||!q2.empty())
	{	int flag=0;
		while(!q1.empty())
		{
		flag=1;
//		file3<<"FEATURE="<<q1.front()->obj.feature<<"VALUE="<<q1.front()->value<<"LABEL="<<q1.front()->label;
		for(int i=0;i<q1.front()->child.size();i++)
			q2.push(q1.front()->child[i]);	
		q1.pop();
		}
		if(flag==1)
		{
		depth++;
		flag=0;
		}			
//	file3<<"\n";
		while(!q2.empty())
		{		
		flag=1;		
//		file3<<"FEATURE="<<q2.front()->obj.feature<<"VALUE="<<q2.front()->value<<"LABEL="<<q2.front()->label;
		for(int i=0;i<q2.front()->child.size();i++)
			q1.push(q2.front()->child[i]);	
		q2.pop();
		}
		if(flag==1)
		{
		depth++;
		flag=0;
		}			

//	file3<<"\n";
 	}
	return depth;
}

int calc_label_classified(tree *root,vector<int> &v1)
{
	if(root->label!=-1)
		return root->label;	
	int val= v1[root->obj.feature];
	for(int i=0;i<root->child.size();i++)
	{
	if(root->child[i]->value==val)
	{
	calc_label_classified(root->child[i],v1);
	break;
	}
	}
}

double calc_error(tree *root, vector< vector <int> > &v1,int y)
{
	int correct=0;
	int incorrect=0;
	for(int i=0;i<v1.size();i++)
	{
	if(v1[i][y]==calc_label_classified(root,v1[i]))	
		correct++;
	else
		incorrect++;	
	}
//	cout<<"CORRECT"<<correct<<"INCORRECT"<<incorrect<<"\n";
	double per= (double)incorrect/double(v1.size());
	return per*100;
}

int count_nodes(tree *root)
{
	if(root==NULL)	
		return 0;

	int nodes=1;
	for(int i=0;i<root->child.size();i++)
		nodes=nodes+count_nodes(root->child[i]);	

	return nodes;
}

int count_terminal_nodes(tree *root)
{
	if(root==NULL)	
		return 0;
	if(root->child.empty())
		return 1;
	int ter_nodes=0;
	for(int i=0;i<root->child.size();i++)
	ter_nodes=ter_nodes + count_terminal_nodes(root->child[i]);	

	return ter_nodes;
}

#endif
