/* Declaration of Disjoint Set Structure */
struct node{
  char data;
  struct node *parent;
} ;
/* Declaration Edge Structure */
struct edge{
  int weight;
  struct node *Node1;
  struct node *Node2;
};
/* Declaration Graph Structure */
  struct Graph{
    struct node **Letters;
    struct edge **Connections;
    };


struct node* FindMyParents(struct node *i){
  struct node *current;
  current=i;
  if(current->parent->data==current->data){
    // printf("Parent is %c",current->data);
    return current;
  }
  else{
    current=FindMyParents(current->parent);
  }
  return current;
}

void Union(struct node *i, struct node *j){
  struct node *current1;
  struct node *current2;
  current1=FindMyParents(i);
  current2=FindMyParents(j);
  if (current1==NULL || current2==NULL){
    printf("Should not be here");}
  else{
    //printf("%c",current1->data);
    //printf("%c",current2->data);
    current1->parent=current2;}
}

struct node* MakeDisjoint(char letter){
  struct node *a=NULL;
  a=(struct node*)malloc(sizeof(struct node)); 
  a->data=letter;
  a->parent=a;
  return a;
} 

struct edge* MakeEdge(struct node *a,struct node *b,int length)
{
  struct edge *maker=(struct edge*)malloc(sizeof(struct edge));
  maker->Node1=(struct node*)malloc(sizeof(struct node));
  maker->Node2=(struct node*)malloc(sizeof(struct node));
  maker->Node1=a;
  maker->Node2=b;
  maker->weight=length;
  return maker;
}

struct Graph* MakeGraph(int numberofnodes, int numberofedges){
  struct Graph* g;
  g=malloc(sizeof(struct Graph));
  g->Letters = malloc(sizeof(struct node * )*numberofnodes);
  g->Connections=malloc(sizeof(struct edge *)*numberofedges);
  for(int j=0;j<numberofnodes;j++){
  g->Letters[j]=(struct node*)malloc(sizeof(struct node));
  }
  for(int j=0;j<numberofedges;j++){
  g->Connections[j]=(struct edge*)malloc(sizeof(struct edge));
  }
  return g;
  
}

void PrintGraph(struct Graph *g,int connectsize){
 printf("The Graph is \n");
  for(int i=0;i<connectsize;i++){
    printf("%c",g->Connections[i]->Node1->data);
    printf("<--%d-->",g->Connections[i]->weight);  
    printf("%c",g->Connections[i]->Node2->data);
    printf("\n");
  }

  
}


int compare(const void *p1, const void *p2){
  
  const struct edge* const* Edge1=p1;
  const struct edge* const* Edge2=p2;
  // printf("%d\n",(int)((*Edge1)->weight));
  //printf("%d\n",(int)((*Edge2)->weight));
  return (int)((*Edge1)->weight-(*Edge2)->weight);
  
   
}

void Kruskal(struct Graph *g, int connectsize){
  qsort(g->Connections,connectsize,sizeof(struct edge*),compare);
  printf("The MST calculated using Kruskal is\n");
  for(int i=0;i<connectsize;i++){
    if(FindMyParents(g->Connections[i]->Node1)!=FindMyParents(g->Connections[i]->Node2)){
	Union(g->Connections[i]->Node1,g->Connections[i]->Node2);
	printf("%c",g->Connections[i]->Node1->data);
	printf("<--%d-->",g->Connections[i]->weight);  
	printf("%c",g->Connections[i]->Node2->data);
	printf("\n");
      }
      
  }
}


int FindNeighbor(struct node* Node1, struct Graph* g,int nodenumber){
  for(int i=0;i<nodenumber;i++){
    if(Node1->data==g->Letters[i]->data){
      return i;
    }
  }
  return 0;
}

int PrimDone(int array[],int nodenumber,int MaxEdge){
  int check=0;
  for(int i=0;i<nodenumber;i++){
    if(array[i]!=MaxEdge){check=1;}
  }
  return check;
}


int FindMaxWeight(struct Graph* g, int connectsize){
  int l=0;
    for(int i=0;i<connectsize;i++)
    {
      if(g->Connections[i]->weight > l)
	{
	  l=g->Connections[i]->weight;
	}
    }
return l;
}

int FindMinElement(int array[],int nodenumber){
  
  int index=0;
  int check=array[0];

  for(int i=1;i<nodenumber;i++){
    if(array[i]<check){ check=array[i];
      index=i;
    }
  }
 return index;
 
}

void Prims(struct Graph* g,int nodenumber, int connectsize)
{
  printf("The MST calculated using Prims is\n");
  int key[nodenumber];
  int Maxedge=FindMaxWeight(g,connectsize)+1;
  int min;

  for(int i=0;i<nodenumber;i++){
    key[i]=1000;  
  }
  key[0]=Maxedge;
  int neighbor, checker;
  checker=1;

  while(checker==1){
    min= FindMinElement(key,nodenumber);
    key[min]=Maxedge;
    if(g->Letters[min]->parent != g->Letters[min]){
      printf("%c",g->Letters[min]->data);  
      printf("<---------->");
      printf("%c",g->Letters[min]->parent->data);
      printf("\n");
    }

    for(int j=0;j<connectsize;j++){
    if(g->Connections[j]->Node1->data == g->Letters[min]->data){
      neighbor=FindNeighbor(g->Connections[j]->Node2,g,nodenumber);

      if(g->Connections[j]->weight<key[neighbor] && key[neighbor]!=Maxedge){
	key[neighbor]=g->Connections[j]->weight;
	g->Connections[j]->Node2->parent=g->Connections[j]->Node1;
      } 
    
    }
    else if(g->Connections[j]->Node2->data == g->Letters[min]->data){
      neighbor=FindNeighbor(g->Connections[j]->Node1,g,nodenumber); 
      if(g->Connections[j]->weight<key[neighbor] && key[neighbor]!=Maxedge){
	key[neighbor]=g->Connections[j]->weight;
	g->Connections[j]->Node1->parent=g->Connections[j]->Node2;
      }
    
    }
    }
    checker=PrimDone(key,nodenumber,Maxedge);
   
  }


}
void ResetGraph(struct Graph *g, int nodenumber){
  for(int i=0;i<nodenumber;i++){
    g->Letters[i]->parent=g->Letters[i];
  }
}

void Dijkstra(int nodenumber,int connectsize,int distance,int MaxEdge, struct node *TheNode, struct Graph *g,int stack[], char neighbor[], int complete[]) 
{
  int distance1,index1;
  
   for(int j=0;j<connectsize;j++){
    if(g->Connections[j]->Node1->data==TheNode->data)
      {
	index1=FindNeighbor(g->Connections[j]->Node2,g,nodenumber);
	distance1=distance+g->Connections[j]->weight;
	if (distance1<stack[index1] && stack[index1] != MaxEdge){
	stack[index1]=distance1;
	neighbor[index1]=TheNode->data;
	complete[index1]=stack[index1];
	  }
      }
    else if(g->Connections[j]->Node2->data==TheNode->data) 
      {
	index1=FindNeighbor(g->Connections[j]->Node1,g,nodenumber);
	distance1=distance+g->Connections[j]->weight;
	if (distance1<stack[index1] && stack[index1] != MaxEdge){
	stack[index1]=distance1;
	neighbor[index1]=TheNode->data;
	complete[index1]=stack[index1];
	  }
	  }
     }
   stack[FindNeighbor(TheNode,g,nodenumber)]=MaxEdge;
   index1=FindMinElement(stack,nodenumber);

   if(stack[index1]!=MaxEdge){
     Dijkstra(nodenumber,connectsize,stack[index1],MaxEdge,g->Letters[index1],g,stack,neighbor,complete); 
     }
  
}
  

void FindShortestPathFrom(int TheLetter,int connectsize, int nodenumber,struct Graph *g ){
  int stack[nodenumber],complete[nodenumber];
  char neighbor[nodenumber]; // keeps track of reachable from "xx" Node 
  int Maxedge=999;//FindMaxWeight(g,connectsize)+1;
  for(int i=0;i<nodenumber;i++){
    stack[i]=1000;
    complete[i]=1000;
  }
  complete[TheLetter]=0;
  Dijkstra(nodenumber,connectsize,0,Maxedge,g->Letters[TheLetter],g,stack,neighbor,complete);
  printf("Shortest paths from %c are ",g->Letters[TheLetter]->data);
  for(int i=0;i<nodenumber;i++){
    printf("%d ",complete[i]);
  }
  printf("\n");
  }

int **Matrix(int nodenumber,struct Graph *g,int connectsize)
{ 
  int i,j;
  
  /* Can also be done as:
    int**AdjacencyMat=(int **)calloc(nodenumber,sizeof(int *));
  for (int i=0;i<nodenumber;i++){
    AdjacencyMat[i]=(int *)calloc(nodenumber,sizeof(int));
    }*/

  // Malloc-Pointer to pointers allocates dead-end street populates it with driveways
  // Malloc-Pointers determines what goes in each driveway 

  int**AdjacencyMat=(int **)malloc(sizeof(int *)*nodenumber);
  for (int i=0;i<nodenumber;i++){
    AdjacencyMat[i]=(int *)malloc(sizeof(int)*nodenumber);
    }

  
  /*for(int i=0;i<nodenumber;i++){
    for(int j=0;j<nodenumber;j++){
      printf("How about now?\n");
     AdjacencyMat[i][j]=0;
      }
  }*/
  //printf("%d",AdjacencyMat[1][2]);
  
  for(int k=0;k<connectsize;k++){
    i=FindNeighbor(g->Connections[k]->Node1,g,nodenumber);
    j=FindNeighbor(g->Connections[k]->Node2,g,nodenumber); 
    AdjacencyMat[i][j]=1;
    AdjacencyMat[j][i]=1;
  }

  printf("The Adjacency Matrix is\n");
 for(int i=0;i<nodenumber;i++){
    for(int j=0;j<nodenumber;j++){
      printf("%d",AdjacencyMat[i][j]);
      }
    printf("\n");
  }
 
  return AdjacencyMat;

}
