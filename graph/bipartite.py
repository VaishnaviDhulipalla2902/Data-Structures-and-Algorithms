# Python program to find out whether a 
# given graph is Bipartite or not
 
class Graph():
 
    def __init__(self, V):
        self.V = V
        self.graph = [[0 for column in range(V)] \
                                for row in range(V)]
 
    # This function returns true if graph G[V][V] 
    # is Bipartite, else false
    def isBipartite(self, src):
 
        # Create a color array to store colors 
        # assigned to all veritces. Vertex
        # number is used as index in this array. 
        # The value '-1' of  colorArr[i] is used to 
        # indicate that no color is assigned to 
        # vertex 'i'. The value 1 is used to indicate 
        # first color is assigned and value 0
        # indicates second color is assigned.
        colorArr = [-1] * self.V
 
        # Assign first color to source
        colorArr[src] = 1
 
        # Create a queue (FIFO) of vertex numbers and 
        # enqueue source vertex for BFS traversal
        queue = []
        queue.append(src)
 
        # Run while there are vertices in queue 
        # (Similar to BFS)
        while queue:
 
            u = queue.pop()
 
            // Return false if there is a self-loop
            if self.graph[u][u] == 1:
                return False;
 
            for v in range(self.V):
 
                # An edge from u to v exists and destination 
                # v is not colored
                if self.graph[u][v] == 1 and colorArr[v] == -1:
 
                    # Assign alternate color to this 
                    # adjacent v of u
                    colorArr[v] = 1 - colorArr[u]
                    queue.append(v)
 
                # An edge from u to v exists and destination 
                # v is colored with same color as u
                elif self.graph[u][v] == 1 and colorArr[v] == colorArr[u]:
                    return False
 
        # If we reach here, then all adjacent 
        # vertices can be colored with alternate 
        # color
        return True
 
# Driver program to test above function
g = Graph(4)
g.graph = [[0, 1, 0, 1],
            [1, 0, 1, 0],
            [0, 1, 0, 1],
            [1, 0, 1, 0]
            ]
             
print "Yes" if g.isBipartite(0) else "No"
 
# This code is contributed by Divyanshu Mehta
Run on IDE

Output:
Yes
The above algorithm works only if the graph is strongly connected. In above code, we always start with source 0 and assume that vertices are visited from it. One important observation is a graph with no edges is also Bipiartite. Note that the Bipartite condition says all edges should be from one set to another.

We can extend the above code to handle cases when a graph is not connected. The idea is repeatedly call above method for all not yet visited vertices.
// C++ program to find out whether a given graph is Bipartite or not.
// It works for disconnected graph also.
#include <bits/stdc++.h>
using namespace std;
 
const int V = 4;
 
// This function returns true if graph G[V][V] is Bipartite,
// else false
bool isBipartiteUtil(int G[][V], int src, int colorArr[])
{
    colorArr[src] = 1;
 
    // Create a queue (FIFO) of vertex numbers and enqueue
    // source vertex for BFS traversal
    queue <int> q;
    q.push(src);
 
    // Run while there are vertices in queue (Similar to BFS)
    while (!q.empty())
    {
        // Dequeue a vertex from queue ( Refer http://goo.gl/35oz8 )
        int u = q.front();
        q.pop();
 
        // Return false if there is a self-loop 
        if (G[u][u] == 1)
           return false;  
 
         // Find all non-colored adjacent vertices
        for (int v = 0; v < V; ++v)
        {
            // An edge from u to v exists and
            // destination v is not colored
            if (G[u][v] && colorArr[v] == -1)
            {
                // Assign alternate color to this
                // adjacent v of u
                colorArr[v] = 1 - colorArr[u];
                q.push(v);
            }
 
            // An edge from u to v exists and destination
            // v is colored with same color as u
            else if (G[u][v] && colorArr[v] == colorArr[u])
                return false;
        }
    }
 
    // If we reach here, then all adjacent vertices can
    // be colored with alternate color
    return true;
}
 
// Returns true if G[][] is Bipartite, else false
bool isBipartite(int G[][V])
{
    // Create a color array to store colors assigned to all
    // veritces. Vertex/ number is used as index in this
    // array. The value '-1' of  colorArr[i] is used to
    // ndicate that no color is assigned to vertex 'i'.
    // The value 1 is used to indicate first color is
    // assigned and value 0 indicates second color is
    // assigned.
    int colorArr[V];
    for (int i = 0; i < V; ++i)
        colorArr[i] = -1;
 
    // This code is to handle disconnected graoh
    for (int i = 0; i < V; i++)
      if (colorArr[i] == -1)
        if (isBipartiteUtil(G, i, colorArr) == false)
           return false;
 
     return true;
}
 
// Driver program to test above function
int main()
{
    int G[][V] = {{0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}
    };
 
    isBipartite(G) ? cout << "Yes" : cout << "No";
    return 0;
}
