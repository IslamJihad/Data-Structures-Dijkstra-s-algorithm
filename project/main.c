/*
ISLAM JIHAD JOMA
     1191375
     SEC 3
*/
#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#define INFINITY 9999
#define SIZE 300


typedef struct node *Node;
struct node
{
    int length;
    char city[30];
};
Node arr[SIZE][SIZE];

void dikt(int startnode, int endnode);
void readFromFile();



int main()
{

    readFromFile();


    int x=0,y=0;
    while(1)
    {
        printf("\n\nenter the two points to find the shortest road between:\n");
        printf("the first point: ");
        scanf("%d", &y);
        printf("the second point: ");
        scanf("%d", &x);

        if(x>0&&y>0&& x<=300&&y<=300)
        {
            dikt(y,x);
        }
        else if(x<0||y<0)
        {
            exit(1);
        }
        else
        {
            printf("the numbers you enteres are out of range try again\n\n");
        }
    }


    return 0;
}




//digkestra function to find the shortest road between 2 points
void dikt(int endnode, int startnode)
{
    // cost to save the cost(length) for all nodes in a seperated array
    //distance to save all the lengths from the node we choose to all posiple nodes(adjecent)
    //sequn to save the nodes sequntally(as stack) each index point to the previous index element
    //visited for marking each element if visited or not
    int cost[SIZE][SIZE], distance[SIZE], sequn[SIZE], visited[SIZE];

    int counter, minimum, nextnode, i, j;

// any cell that it's empty is filled with infinity so we never get close to it
    for(i=0; i<SIZE; i++)
        for(j=0; j<SIZE; j++)
            if(arr[i][j]->length==0)
                cost[i][j]=INFINITY;
            else
                cost[i][j]=arr[i][j]->length;


// visited is set to zero for all elements
//sequnatall is set to the start node
//distance for the first node with all other points is set in the array
    for(i=0; i<SIZE; i++)
    {
        distance[i]=cost[startnode][i];
        sequn[i]=startnode;
        visited[i]=0;
    }
    distance[startnode]=0;
    visited[startnode]=1;
    counter=1;


    while(counter<SIZE && nextnode!=endnode)
    {
        minimum=INFINITY;
//minimum distance between the node and the adjecent is stored in virable
        for(i=0; i<SIZE; i++)
            if(distance[i]<minimum&&!visited[i])
            {
                minimum=distance[i];
                nextnode=i;
            }

//check if there is a shorter bath
// save the road in the sequantall array
        visited[nextnode]=1;
        for(i=0; i<SIZE; i++)
            if(!visited[i])
                if(minimum+cost[nextnode][i]<distance[i])
                {
                    //if a->b->c is less than a->c then chose it
                    distance[i]=minimum+cost[nextnode][i];
                    sequn[i]=nextnode;
                }
        counter++;
    }


//print the road between the 2 points

    FILE* wfile = fopen("route.txt", "a");

    if(endnode != startnode)
    {
        printf("\nDistance from  node %d to node %d = %d KM",endnode, startnode, distance[endnode]);
        fprintf(wfile, "\nDistance from  node %d to node %d = %d KM",endnode, startnode, distance[endnode]);
        printf("\nPath= %s", arr[sequn[endnode]][endnode]->city);
        fprintf(wfile, "\nPath= %s", arr[sequn[endnode]][endnode]->city);

        i=endnode;
        do
        {
            //printing every index element and switch to the previous element that point to it
            i=sequn[i];
            printf("--> %s",arr[sequn[i]][i]->city);
            fprintf(wfile, "--> %s",arr[sequn[i]][i]->city);
        }
        while(sequn[i]!=startnode);
        fprintf(wfile, "\n");
    }
    else
    {
        printf("you entered the same node to start and end\n");
    }
    fclose(wfile);

}



//reading from file and store in the graph as a matrix
void readFromFile()
{

    //mallco all the index nodes
    for(int i=0; i<SIZE; i++)
    {
        for(int j=0; j<SIZE; j++)
        {
            arr[i][j]= (Node)malloc( sizeof( struct node ));
            arr[i][j]->length=0;
            for(int k=0; k<30; k++)
            {
                arr[i][j]->city[k]=NULL;
            }
        }
    }
//segments.txt
    char fileName[30];
    printf("please enter the file name you want to read data from with it's extention\n");
    scanf("%s", fileName);

    FILE* rfile = fopen(fileName, "r");


    char line[80];
    char temp[4][30];
    int p1, p2, dis;
    char cname[30];


    while (fgets(line, sizeof(line), rfile))
    {
        // splitting and casting from strings to integers
        char * token = strtok(line, " ");

        for(int i=0; i<4; i++)
        {
            strcpy(temp[i],token);
            token = strtok(NULL, " ");
        }
        // as the split depends on spaces so it may cut some words of the city name, this is to fix it
        if(atoi(temp[3])==0)
        {
            strcat(temp[2], " ");
            strcat(temp[2], temp[3]);
            strcpy(temp[3],token);
        }
        if(atoi(temp[3])==0)
        {
            strcat(temp[2], " ");
            strcat(temp[2], temp[3]);
            token = strtok(NULL, " ");
            strcpy(temp[3],token);
        }
        if(atoi(temp[3])==0)
        {
            strcat(temp[2], " ");
            strcat(temp[2], temp[3]);
            token = strtok(NULL, " ");
            strcpy(temp[3],token);
        }
        // casting to intgers
        p1= atoi(temp[0]);
        p2= atoi(temp[1]);
        strcpy(cname, temp[2]);
        dis= atoi(temp[3]);

        //storing data in the array  and as directed I stored it twice
        arr[p1][p2]->length=dis;
        strcpy(arr[p1][p2]->city, cname);
        arr[p2][p1]->length=dis;
        strcpy(arr[p2][p1]->city, cname);
    }
    fclose(rfile);
}

