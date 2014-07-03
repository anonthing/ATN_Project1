/*
 * Project_1.cpp
 *
 *  Created on: Jun 14, 2014
 *      Author: sidhhu
 */
#include<stdio.h>
#include<iostream>
//#include<conio.h>
#include<vector>
#include<algorithm>
#include<math.h>
#include<stdlib.h>
using namespace std;
int cost[500][500],a[500][500],b[500][500],dist[500][500];


//Dijkstra's algorithm
int djikstra(int n,int cost[][500],int s[],int d[],int source,int b[][500])
{

	int i,j,u,v,small,cost_shortest = 0;
	int previous[40];
	for(i=0;i<n-1;i++)
	{
		small=300;
		u=0;
		for(j=0;j<n;j++)
		{
			if(s[j]==0 && d[j]<small)
			{
				small=d[j];
				u=j;
				printf("tree trace prev: %d for source %d \n" , u, source);
			}
		}
		s[u]=1;
		printf("tree trace prev: %d for source %d \n" , u, source);
		for(v=0;v<n;v++)
		{
			if(d[u]+cost[u][v] < d[v] && s[v]==0){
				d[v]=d[u]+cost[u][v];

			}


		}
	}
//	for(i=0;i<n;i++)
//			printf("%d -> %d = %d\n",source,i,d[i]);

	//Calculating the total cost of the shortest path tree
	//for(int j=0;j<n;j++){
	for(i=0;i<n;i++)
	{
		cost_shortest = cost_shortest + (d[i] * b[source][i]);
	}
	//printf("Total cost of the shortest path tree is %d for node %d\n\n ",cost_shortest, j);
	//shortVec.push_back(cost_shortest);
	//cost_shortest = 0;
	//}
	//pos = std::min_element(shortVec.begin(), shortVec.end());
	//printf("Total cost of the shortest path tree is %d\n\n",cost_shortest);//Printing the total cost of the shortest path tree
	return cost_shortest;
}

int generateKRandom(int nodes){
	int k_random = rand() % nodes;
	return k_random;
}

int searchArray(int k_array[], int kRandom){
	int flag = 0;
	for(int i = 0; i<sizeof(k_array);i++){
		if(kRandom == k_array[i]){
			flag = 1;
		}
	}
	return flag;
}

int main()
{
	int i,j,source,s[500],d[500],K,x;
	int cost_shortest=0,sum = 0,nodes,p,q;

	FILE *file = fopen("unit_costs.xls","w");
	FILE *file1 = fopen("traffic_demand.xls","w");
	printf("Enter the number of nodes\n");
	scanf("%d",&nodes);

	printf("Enter the value of K\n");
	scanf("%d",&K);
	int k_array[K];
//	printf("Enter the source node\n");
//	scanf("%d",&source);

	for(i=0;i<nodes;i++)
	{
		for(j=0;j<nodes;j++)//initialising the arrays
		{
			a[i][j]=0;
			dist[i][j]=0;
			b[i][j]=0;
			cost[i][j]=0;
		}
	}



	/* Assigning values to a[i][j] */
	for(int i=0; i<K; i++){

		int kRandom = generateKRandom(nodes);
		while(searchArray(k_array, kRandom) == 1){
			kRandom = generateKRandom(nodes);
		}

		k_array[i] = kRandom;
		printf("the k_random array = %d", k_array[i]);

	}

	for(int i=0;i<nodes;i++){
			for(int j=0;j<nodes;j++){
				if(searchArray(k_array, j) == 1){
					a[i][j] = 1;
				}
				else
					a[i][j] = 300;
				cost[i][j] = a[i][j];
			}
	}



	/* Generating random traffic demand values edit--> pick bij from [0,1,2,3]*/
	for (i=0;i<nodes;i++)
	{
		for (j=0;j<nodes;j++)
		{
				b[i][j] = rand() % 4;
		}
	}

	/*displaying the link capacities */
	fprintf(file,"\n The unit costs of the links are \n");
	for (i=0;i<nodes;i++)
	{
		for (j=0;j<nodes;j++)
		{
			fprintf(file,"\n %d -> %d : %d",i,j,a[i][j]);
		}
	}

	//Executing the Dijkstra's algorithm to find the shortest path in the network topology
	printf("The shortest path tree constructed using Djikstra's algorithm is\n");
	vector<int> shortVec;
	vector<int>::iterator pos;
	for(int j=0;j<nodes;j++){
	for(i=0;i<nodes;i++)
	{
		s[i]=0;
		d[i]=cost[j][i];
	}

	s[j]=1;
	shortVec.push_back(djikstra(nodes,cost,s,d,j,b));
	}
	pos = min_element(shortVec.begin(), shortVec.end());

	int min_index = pos - shortVec.begin();
	for(i=0;i<nodes;i++)
			printf("%d -> %d = %d\n",min_index,i,d[i]);
	printf("Total cost of the shortest path tree is %d\n\n",*pos);
	/* Printing traffic demand values from source */
	fprintf(file1,"\n\nThe traffic demand values from source are\n\n");
	for(i=0;i<nodes;i++)
	{
		fprintf(file1,"%d -> %d : %d \n",source,i,b[source][i]);
	}

	fclose(file);
	fclose(file1);
	//getch();
	return 0;
}



