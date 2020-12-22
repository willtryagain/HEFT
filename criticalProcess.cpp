#include <bits/stdc++.h>

#define SIZE 100
#define NUM_PROCESSES 10
#define max(a, b) a > b ? a:b

class Graph
{
public:
	int numberOfTasks;
	int adjMat[SIZE][SIZE]; //vector it
	std::vector<int> pred[SIZE];
	std::vector<int> succ[SIZE];
	float AFT[SIZE];
	int VM[size];
	void information();
};

class Process
{
public:
	int numberOfProcessors;
	float upwardRank[SIZE];
	int processTime[SIZE][SIZE];
	double avgTime[SIZE];
	void computeAvgTime(Graph g);
	void upRankFill(Graph g);
	std::vector<float> Tavailable[SIZE];
};


void Process::computeAvgTime(Graph g)
{
	double total = 0;
	for (int i = 0; i < g.numberOfTasks; ++i)
	{
		total = 0;
		for (int j = 0; j < numberOfProcessors; ++j)
		{
			total += processTime[i][j];
		}
		avgTime[i] = total/numberOfProcessors;
	}
}


class Assignment
{
public:
	std::vector< std::pair<int, int> > available[SIZE];
	int assignedProcessor[SIZE];
	void schedule(Graph graph, Process process, int node);
	bool ready[SIZE];
	bool visited[SIZE];
	std::pair<int, int> AT[SIZE];
	Assignment();
};
using namespace std;


void Graph::information()
{
	for(int i = 0; i < numberOfTasks; i++)
	{
		for(int j = 0; j < numberOfTasks; j++)
		{
			if(adjMat[i][j] > 0)
			{
				succ[i].push_back(j);
				pred[j].push_back(i);
			}
		}
	}
}


void Process::upRankFill(Graph graph)
{	
	double mx = 0, avg;
	for (int i = graph.numberOfTasks - 1; i >= 0; --i)
	{
		mx = 0;
		for (auto it: graph.succ[i])
		{
			mx = max(mx, upwardRank[it] + graph.adjMat[i][it]);
		}
		upwardRank[i] = mx + avgTime[i];
	}
}


Assignment::Assignment()
{
	for (int i = 0; i < SIZE; ++i)
	{
		ready[i] = false;
		visited[i] = false;
	}
}
	
void Assignment::schedule(Graph graph, Process process, int node)
{
	pair<float, int> rankIndex[graph.numberOfTasks];
	for (int i = 0; i < graph.numberOfTasks; ++i)
		rankIndex[i] = {process.upwardRank[i], i};
	sort(rankIndex, rankIndex + graph.numberOfTasks);
	for (int i = graph.numberOfTasks-1; i >= 0; --i) {
		int ti = rankIndex[i].second;
		if (ti == graph.numberOfTasks-1) //entry task
			
		else {
			int getLastParent = -1;
			int VMparent = -1;
			float dataArrivalTime = -1;
			int mx = -1;
		
			for (int p : graph.pred[ti]) {
				if (mx < EFT[p]) {
					mx = EFT[p];
					getLastParent = p;
				}
			}
			VMparent = VM[getLastParent];
			dataArrivalTime = EFT[getLastParent];
			//is pred ti including the last parent?
			for (int tp : graph.pred[ti]) 
				dataArrivalTime = max(dataArrivalTime, EFT[tp] + //TT?
			if (dataArrivalTime == AT[VMparent].back()) {
				VM[ti] = VMparent;
			}	
			else {
				AFT[ti] = INT_MAX; 
				int processor = -1;
				for(int p = 0; p < process.numberOfProcessors; ++p) {
					float EST = 0;
					if (!Tavailable[p].empty())
						EST = Tavailable[p].back();
					for(int tm : graph.pred[ni]) {
						EST = max(EST, AFT[nm] + adjMat[tm][ti]);
						
					}	
					EFT = EST + processTime[ti][p];
					if (AFT[ti] > EFT) {
						AFT[ti] = EFT; 
						processor = P;
					}
				}	
			}	
				
		}
	}
}

int main(int argc, char const *argv[])
{
	Graph graph;
	Process process;
	Assignment assignment;
	std::unordered_set<int>::iterator it; 
	ifstream inputFile("Input11.txt");
	ofstream outputFile("outputFile.txt");
	inputFile>> graph.numberOfTasks;
	inputFile>> process.numberOfProcessors;
	//perror("");
	for (int i = 0; i < graph.numberOfTasks; ++i)
	{
		for (int j = 0; j < process.numberOfProcessors; ++j)
		{
			inputFile >> process.processTime[i][j];
		}
	}

	for (int i = 0; i < graph.numberOfTasks; ++i)
	{
		for (int j = 0; j < graph.numberOfTasks; ++j)
		{
			inputFile >> graph.adjMat[i][j];
			//cout<<graph.adjMat[i][j]<<" ";
		}
		
	}
	//for (int i = 0; i < graph.numberOfTasks; ++i)
	//	printf("%f ", process.upwardRank[i]);
	graph.information();
	process.computeAvgTime(graph);
	process.upRankFill(graph);
	assignment.schedule(graph, process, 0);
	
	for(int i = 0; i < process.numberOfProcessors; ++i)
	{
		for(auto it: assignment.available[i])
		{
			outputFile<<"( "<<assignment.AT[it.first].first<<"/ task"<<it.first + 1<<" /"<<it.second<<"), ";
		}
		outputFile<<endl;
	}

	return 0;
}
