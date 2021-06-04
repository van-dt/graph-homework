#include "jrb.hpp"
#include <list>
#include <iterator>
using namespace std;
typedef JRB Graph;

Graph createGraph();
void addEdge_int(Graph graph, int v1, int v2, int weight);
void addEdge_str(Graph graph, char* v1, char* v2, int weight);
int getAdjacentVertices_int (Graph graph, int v, int* output);
int getAdjacentVertices_str (Graph graph, char* v, char output[10][10]);

//tra ve cac dinh hien co tren do thi
list<string> getAllVertexes(Graph graph);

// duyet do thi theo chieu rong, dinh bat dau l� start
void BFS(Graph graph, char* start);// duyet theo chieu rong
void DFS(Graph graph, char* start); // duyet theo chieu sau
//puffer_code
void puffer_code(char *filename);
//color_graph
int iscolor(int *array,int color,int n);
int* color_graph(int **array,int *deg,int n,int e);
void record_file(int k,int e,int n,int **array,int *color);
void output_file_ColoredGrarp(char *filename);
//
void dropGraph(Graph graph);
