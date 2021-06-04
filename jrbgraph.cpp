#include "jrbgraph.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<time.h>
#include <queue>
#include <bits/stdc++.h>
#define max 999999
using namespace std;

Graph createGraph()
{
	Graph newGraph = make_jrb();
	return newGraph;
}

void addEdge_int(Graph graph, int v1, int v2, int weight)
{
	// do thi vo huong nen can co (v1 v2) va (v2 v1)
	// them canh v1 v2
	// check xem da co dinh tren cay chua
	JRB bn = jrb_find_int(graph, v1);
	if(bn==NULL) // neu chua co thi them vao
	{		
		JRB tree = make_jrb(); 
		jrb_insert_int(tree, v2, new_jval_i(weight));
		jrb_insert_int(graph, v1, new_jval_v((void*)tree));
	}
	else // dinh v1 da co tren cay
	{
		//node = jrb_find_int(g, v1);
		// them canh v1 v2
		JRB tree = (JRB) jval_v(bn->val);
		jrb_insert_int(tree, v2, new_jval_i(weight));			
	}
	
	// them canh v2 v1
	bn = jrb_find_int(graph, v2);
	if(bn==NULL) // neu chua co thi them vao
	{
		JRB tree = make_jrb();
		jrb_insert_int(tree, v1, new_jval_i(weight));
		jrb_insert_int(graph, v2, new_jval_v(tree));
	}
	else  // da co dinh v2 thi chi them canh v2 v1
	{
		JRB tree = (JRB) jval_v(bn->val);
		jrb_insert_int(tree, v1, new_jval_i(weight));
	}
}

void addEdge_str(Graph graph, char* v1, char* v2, int weight)
{
	// do thi vo huong nen can co (v1 v2) va (v2 v1)
	// them canh v1 v2
	// check xem da co dinh tren cay chua
	JRB bn = jrb_find_str(graph, v1);
	if(bn==NULL) // neu chua co thi them vao
	{		
		JRB tree = make_jrb(); 
		jrb_insert_str(tree, strdup(v2), new_jval_i(weight));
		jrb_insert_str(graph, strdup(v1), new_jval_v(tree));
	}
	else // dinh v1 da co tren cay
	{
		//node = jrb_find_int(g, v1);
		// them canh v1 v2
		JRB tree = (JRB) jval_v(bn->val);
		jrb_insert_str(tree, strdup(v2), new_jval_i(weight));			
	}
	// them canh v2 v1
	// check xem da co dinh tren cay chua
	bn = jrb_find_str(graph, v2);
	if(bn==NULL) // neu chua co thi them vao
	{		
		JRB tree = make_jrb(); 
		jrb_insert_str(tree, strdup(v1), new_jval_i(weight));
		jrb_insert_str(graph, strdup(v2), new_jval_v(tree));
	}
	else // dinh v2 da co tren cay
	{
		// them canh v1 v2
		JRB tree = (JRB) jval_v(bn->val);
		jrb_insert_str(tree, strdup(v1), new_jval_i(weight));			
	}
}

int getAdjacentVertices_str (Graph graph, char* v, char output[10][10])
{
	JRB node = jrb_find_str(graph, v);
	JRB tree = (JRB) jval_v(node->val);
	int total = 0;   
	jrb_traverse(node, tree)
	{
		strcpy(output[total],jval_s(node->key));
		total++;
	}    
	return total;
}

int getAdjacentVertices_int (Graph graph, int v, int* output)
{
	JRB node = jrb_find_int(graph, v);
	JRB tree = (JRB) jval_v(node->val);
	int total = 0;   
	jrb_traverse(node, tree)
	{
		output[total++] = jval_i(node->key);
	}    
	return total;
}

list<string> getAllVertexes(Graph graph)
{
	list<string> vertexes;
	for(JRB ptr = jrb_first(graph); ptr != jrb_nil(graph); ptr = jrb_next(ptr))
	{
		vertexes.push_back(jval_s(ptr->key));
	}
	return vertexes;
}

// hàm băm lụm trên gg
struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator () (std::pair<T1, T2> const &pair) const
    {
        std::size_t h1 = std::hash<T1>()(pair.first);
        std::size_t h2 = std::hash<T2>()(pair.second);
        return h1 ^ h2;
    }
};
int get_dist(unordered_set<pair<int,string>,pair_hash> dist,string u){
	for(auto const& p:dist){
		if(u.compare(p.second)==0) return p.first;
	}
}

void BFS(Graph g,char*start){

	unordered_set<pair<int,string>,pair_hash> dist;
	list<string> vertexes=getAllVertexes(g);
	for (auto const& p:vertexes) {
		if(p.compare(start)==0) dist.insert(make_pair(0,p));
		else dist.insert(make_pair(max,p));
	}
	queue<string> Q;
	Q.push(start);
	while(!Q.empty()){
		string u=Q.front();
		cout <<u<<'\t';
		Q.pop();
		int dist_u = get_dist(dist,u);
		char output[10][10];
		int n=getAdjacentVertices_str(g,strdup(u.c_str()),output);
		for(int i=0;i<n;i++){
			if(dist.find(make_pair(max,output[i]))!=dist.end()){
				Q.push(output[i]);
				dist.erase(make_pair(max,output[i]));
				dist.insert(make_pair(dist_u+1,output[i]));
			}
		}
	}
}

void DFS(Graph graph, char* start)
{
	stack<string> S;
	S.push(start);
	char v[10];
	// gan nhan cac dinh la chua duoc tham
	unordered_set <string> notvisitedList ;
	for(JRB ptr = jrb_first(graph); ptr != jrb_nil(graph); ptr = jrb_next(ptr))
	{
		notvisitedList.insert(jval_s(ptr->key));
	}
	
	int timecount = 1;
	// dinh bat dau chuyen thanh dang tham
	notvisitedList.erase(start);
	printf("Bat dau tham %5s tai %d\n",start, timecount);
	
	while(!S.empty())
	{
		timecount++;
		// xet dinh v o dau stack		
		strcpy(v, (S.top()).c_str());
		//printf("%5s, ", v);
		char output[10][10];
		
		// kiem tra co dinh nao ke voi v ma chua tham
		int n = getAdjacentVertices_str (graph, v, output);
		int check = 0;
		for (int i=0; i<n; i++) {
			if(notvisitedList.find(output[i]) != notvisitedList.end())
			{
				S.push(output[i]);
				notvisitedList.erase(output[i]);
				printf("Bat dau tham %5s tai %d\n", output[i], timecount);
				check = 1;
				break;
			}	
		}
		if(check==0) // khong ton tai dinh nao ma chua tham
		{
			S.pop();
			printf("Ket thuc tham %5s tai %d\n", v, timecount);
		}
	}
}

//nen cay bang ma purfer-code tu file.txt
// Dòng đầu tiên thể hiện số cạnh của cây; 
// mỗi dòng tiếp theo thể hiện một cạnh của cây.

void puffer_code(char *filename){
	int i,j,n,e;
    FILE *f1=fopen(filename,"r");
    fscanf(f1,"%d",&n);
	e=n-1;
   // int a[n][2];
    int **a=(int**)malloc((e+1)*sizeof(int*));
    for(i=0;i<=e;i++){
        a[i]=(int*)malloc(2*sizeof(int));
    }
    int *deg=(int*)malloc((n+1)*sizeof(int));
    for(i=0;i<=n;i++) deg[i]=0;
    for(i=0;i<e;i++){
        fscanf(f1,"%d\t%d\n",&a[i][0],&a[i][1]);
        for(j=1;j<=n;j++) if(j==a[i][0] || j==a[i][1]) deg[j]++;
    }
    fclose(f1);
  
    printf("ma prurfer code cua cay la:");
    
    for(i=1;i<n;i++){
        if(deg[i]==1){
            for(j=0;j<e;j++)
            {
                if(a[j][0]==i && deg[a[j][1]]>=1)
                {
                    printf("%d ",a[j][1]);
                    deg[i]--;
                    deg[a[j][1]]--;
                    if(deg[a[j][1]]==1 && a[j][1]<i && a[j][1]!=0){
                        i=a[j][1];
                        j=0;
                    }
                }
                if(a[j][1]==i && deg[a[j][0]]>=1)
                {
                    printf("%d ",a[j][0]);
                    deg[i]--;
                    deg[a[j][0]]--;
                    if(deg[a[j][0]]==1 && a[j][0]<i && a[j][0]!=0){
                        i=a[j][0];
                        j=0;
                    }
                }
            }

        }
    }
}

// to mau do thi tu file txt :
// Dòng đầu tiên ghi hai số nguyênnvàmlà số đỉnh và số cạnh của đồ thị;
// Ở m dòng tiếp theo, mỗi dòng ghi hai số nguyên tương ứng với một cạnh của đồ thị.

int iscolor(int *array,int color,int n){
    int i;
    for(i=0;i<n;i++) if(array[i]==color) return 1;
    return 0;
}
int* color_graph(int **array,int *deg,int n,int e){
    int i,j;
    int *color=(int*)malloc((n+1)*sizeof(int));
    for(i=1;i<=n;i++) color[i]=0;
    for(i=1;i<=n;i++){
        int*a=(int*)malloc(deg[i]*sizeof(int));
        color[i]=1;
        int k=-1;
        for(j=1;j<=e;j++){
            if(array[j][0]==i) a[++k]=color[array[j][1]];
            if(array[j][1]==i) a[++k]=color[array[j][0]];
        }
        while(iscolor(a,color[i],deg[i])) color[i]++;
    }
    return color;
}
void record_file(int k,int e,int n,int **array,int *color){
    FILE *f1=fopen("dothi.dot","w");
    int i,j;
        fputs("graph  tree {\n",f1);
        for(i=1;i<=k;i++){
                float s1 = rand() / (float) RAND_MAX;
                float s2 = rand() / (float) RAND_MAX;
                float s3 = rand() / (float) RAND_MAX;
            for(j=1;j<=n;j++){
                if(color[j]==i) {
                    fprintf(f1,"%d[fillcolor=\"%f,%f,%f\", style=filled];\n",j,s1,s2,s3);
                }
            }
        }
        for(i=1;i<=e;i++){
            fprintf(f1,"%d--%d;\n",array[i][0],array[i][1]);
        }
        fputs("}",f1);
        fclose(f1);

}
void output_file_ColoredGrarp(char *filename){
	int i,j,n,e;
    FILE *f1=fopen(filename,"r");
    fscanf(f1,"%d\t%d\n",&n,&e);
   // int a[n][2];
    int **a=(int**)malloc((e+1)*sizeof(int*));
    for(i=0;i<=e;i++){
        a[i]=(int*)malloc(2*sizeof(int));
    }
    int *deg=(int*)malloc((n+1)*sizeof(int));
    for(i=1;i<=n;i++) deg[i]=0;
    for(i=1;i<=e;i++){
        fscanf(f1,"%d\t%d\n",&a[i][0],&a[i][1]);
        for(j=1;j<=n;j++) if(j==a[i][0] || j==a[i][1]) deg[j]++;
    }
    fclose(f1);

    /*for(i=1;i<=e;i++){
        printf("%d %d\n",a[i][0],a[i][1]);
    }*/
    //for(i=1;i<=n;i++) printf("%d:%d\n",i,deg[i]);

    int *color=color_graph(a,deg,n,e);
     
    //for(i=1;i<=n;i++) printf("%d\t%d\n",i,color[i]);
   
    int k=0;
    for(i=1;i<=e;i++){
        if(color[i]>k) k=color[i];
    }
     record_file(k,e,n,a,color);
}


//cccccccccccccccccccccccccccccc
void dropGraph(Graph graph)
{
	JRB node;
	jrb_traverse(node, graph)
	{
		jrb_free_tree((jrb_node*) jval_v(node->val) );
	}
    
}
