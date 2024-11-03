import directed_graph;
import directed_graph.to_dot;
import std;

using namespace proCpp;
using namespace std;

// Force all code to be compiled for testing.
template class DirectedGraph<string>;

int main()
{
   DirectedGraph<int> graph;

   // Insert some nodes and edges.
   graph.insert(11);
   graph.insert(22);
   graph.insert(33);
   graph.insert(44);
   graph.insert(55);
   graph.insertEdge(11, 33);
   graph.insertEdge(22, 33);
   graph.insertEdge(22, 44);
   graph.insertEdge(22, 55);
   graph.insertEdge(33, 44);
   graph.insertEdge(44, 55);
   println("{}", ToDot(graph, "Graph1"));

   // Remove an edge and a node.
   graph.eraseEdge(22, 44);
   graph.erase(44);
   println("{}", ToDot(graph, "Graph1"));

   // Print the size of the graph.
   println("Size: {}", graph.size());

   // Test swapping graphs.
   DirectedGraph<int> otherGraph;
   otherGraph.swap(graph);

   println("After swapping:");
   println("Size: {}", graph.size());

   // Test copying graphs.
   DirectedGraph<int> graphCopy{otherGraph};
   println("otherGraph == graphCopy? {}", (otherGraph == graphCopy));

   graphCopy.erase(33);
   println("otherGraph == graphCopy? {}", (otherGraph == graphCopy));

   // Test equality
   DirectedGraph<int> graph1;
   graph1.insert(11);
   graph1.insert(22);
   graph1.insert(33);
   graph1.insertEdge(11, 22);
   graph1.insertEdge(11, 33);
   graph1.insertEdge(22, 33);

   DirectedGraph<int> graph2;
   graph2.insert(22);
   graph2.insert(11);
   graph2.insert(33);
   graph2.insertEdge(22, 33);
   graph2.insertEdge(11, 22);
   graph2.insertEdge(11, 33);

   println("{}", ToDot(graph1, "graph1"));
   println("{}", ToDot(graph2, "graph2"));

   println("are equal: {}", (graph1 == graph2));

   // Test assignment of graphs.
   DirectedGraph<int> graph3;
   graph3 = graph2;
   println("{}", ToDot(graph3, "graph3"));

   // Test a graph with strings.
   DirectedGraph<string> graphStrings;
   graphStrings.insert("String 1");
   string str{"String 2"};
   graphStrings.insert(str);
   graphStrings.insert("String 3");
   graphStrings.insert("String 4");
   graphStrings.insertEdge("String 1", str);
   graphStrings.insertEdge("String 2", str);
   graphStrings.insertEdge("String 3", str);

   println("{}", ToDot(graphStrings, "String Graph"));
}
