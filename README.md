# ID3
Implemented ID3 decision tree algorithm (in c++)

### Dataset: Insurance Company Benchmark (COIL 2000) data set[2]

ID3 algorithm involves choosing attribute for creating the decision function at every node in the decision tree. Using information gain as the measure to select the best attribute for splitting a node. 

Also implemented a functionality of given a text file containing test instances, the code should classify the test data and output the prediction accuracy.

The following things were implemented using this dataset:

1. Splitted the data set into a training and a test set. Create a training set containing a random sample of 1000 observations, and a test set containing the remaining observations. Use the training set to learn a decision tree. Discussed the statistics of the learned tree, for example, effect of early stopping on the number of terminal nodes, effect of early stopping on the prediction accuracy on the training dataset and the left out test dataset, attributes that are most frequently used as split functions in the internal nodes of the tree, etc.

2. Added some noise to the dataset and observe its effect on the decision tree. Add 0.5, 1, 5 and 10% noise to the dataset. This noise was added by randomly switching the label of a proportion of data points. Construct the decision tree for each noise setting and quantify the complexity of the learned decision tree using the number of nodes in the tree. Discussed our observations about the quality of the model learned under these noise conditions.

3. Produced a pruned tree corresponding to the optimal tree size by computing the prediction accuracy on the test set. Used a post-pruning strategy to prune the tree that has been learned without applying any early stopping criteria. The change in the prediction accuracy as a function of pruning is discussed (reduction in the number of nodes or rules/clauses obtained from the tree).

4.  Learnt a decision forest that used feature bagging. Use majority voting for predicting the label for a test data point. Study the effect of number of trees in the forest on the prediction accuracy of the test data set.

### Input Format:
The input to the code is the name of the file containing the dataset and the experiment number. There are four experiments to be conducted as listed above. The format of the dataset is as follows
```
N
D
x11 	x12 ... x1D 		y1
x21 	x22 	...	x2D 	y2
⋮
xN1 	xN2  ... xND 		yN
```

N- total number of data points
D – number of attributes describing the dataset. 
This is followed by the dataset itself, one instance in one line with the attribute values delimited by space. The last value in
each line is the value of the target attribute (y).

### Output Format:
Ouput of code is different for each experiment.

### Training and test data creation:
Executable filename dataset.cpp
Script: Compile: g++ dataset.cpp
Run: . /a.out traindata.txt testdata.txt training.txt test.txt

We noticed that the there is a class imabalance problem. So, with this, we make sure that positive and negative classes are equally distributed in dataset.

### Compile and Run the header file named id3.h
Script: g++ id3.h –o id3 (compile only)

Note: In output#.txt file the output of respect experiment will be stored.

#### Experiment Number 1: 
Executable filename – experiment1.cpp
Script: Compile: g++ experiment1.cpp
Run: ./a.out training.txt test.txt output1.txt

#### Experiment Number 2: 
Executable filename – experiment2.cpp
Script: Compile: g++ experiment2.cpp
Run: ./a.out training.txt test.txt output2.txt

#### Experiment Number 3: 
Executable filename – experiment3.cpp
Script: Compile: g++ experiment3.cpp
Run: ./a.out training.txt test.txt output3.txt

#### Experiment Number 4: 
Executable filename – experiment4.cpp
Script: Compile: g++ experiment4.cpp
Run: ./a.out training.txt test.txt output4.txt


### Reference
[1] P. van der Putten and M. van Someren (eds). CoIL Challenge 2000: The Insurance Company
Case. Published by Sentient Machine Research, Amsterdam. Also a Leiden Institute of Advanced
Computer Science Technical Report 2000-09. June 22, 2000.
[2] https://archive.ics.uci.edu/ml/datasets/Insurance+Company+Benchmark+(COIL+2000)	
