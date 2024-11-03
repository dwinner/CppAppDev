import directed_graph;
import directed_graph.to_dot;
import std;

using namespace proCpp;
using namespace std;

namespace proCpp
{
   // Force all code to be compiled for testing.
   template class DiGraph<string>;
}

int main()
{
   DiGraph graph{11, 22, 33};
   graph.insert({44, 55});

   vector moreNodes{66, 77};
   graph.insertRange(moreNodes);

   // Insert some edges.
   graph.insertEdge(11, 33);
   graph.insertEdge(22, 33);
   graph.insertEdge(22, 44);
   graph.insertEdge(22, 55);
   graph.insertEdge(33, 44);
   graph.insertEdge(44, 55);

   // Try to insert a duplicate, and use structured bindings for the result.
   auto [iter22, inserted] = graph.insert(22);
   if (!inserted)
   {
      println("Duplicate element.");
   }

   // Print nodes using a for loop and iterators.
   for (auto iter{graph.cbegin()}; iter != graph.cend(); ++iter)
   {
      print("{} ", *iter);
   }
   println("");

   // Print nodes using a for loop and iterators retrieved with the non-member
   // functions cbegin() and cend().
   for (auto iter{cbegin(graph)}; iter != cend(graph); ++iter)
   {
      print("{} ", *iter);
   }

   println("");

   // Print nodes using a range-based for loop.
   for (auto& node : graph)
   {
      print("{} ", node);
   }

   println("");

   // Search a node using the find() Standard Library algorithm.
   auto result{find(begin(graph), end(graph), 22)};
   if (result != end(graph))
   {
      println("Node 22 found.");
   }
   else
   {
      println("Node 22 NOT found.");
   }

   // Count all nodes with values > 22.
   auto count{
      count_if(begin(graph), end(graph),
               [](const auto& node)
               {
                  return node > 22;
               })
   };
   println("{} nodes > 22", count);

   // Use the iterator-based erase() member function in combination with find().
   graph.erase(find(begin(graph), end(graph), 44));

   // Print nodes in reverse order.
   for (auto iter{graph.rbegin()}; iter != graph.rend(); ++iter)
   {
      print("{} ", *iter);
   }

   println("");

   // Test adjacency lists.
   {
      print("Adjacency list for node 22: ");

      auto nodesAdjacentTo22{graph.nodesAdjacentTo(22)};
      if (!nodesAdjacentTo22.has_value())
      {
         println("Value 22 not found.");
      }
      else
      {
         for (const auto& node : *nodesAdjacentTo22)
         {
            print("{} ", node);
         }
      }

      println("");
   }

   // Remove an edge.
   graph.eraseEdge(22, 44);

   // Remove a node.
   graph.erase(44);
   graph.erase(find(begin(graph), end(graph), 44));

   {
      // Test begin()/end() non-const
      print("Nodes: ");
      for (auto iter{graph.begin()}; iter != graph.end(); ++iter)
      {
         print("{} ", *iter);
      }

      println("");
   }

   {
      // Test begin()/end() const
      print("Nodes: ");
      const auto& cgraph = graph;
      for (auto iter{cgraph.begin()}; iter != cgraph.end(); ++iter)
      {
         print("{} ", *iter);
      }

      println("");
   }

   {
      // Test cbegin()/cend()
      print("Nodes: ");
      for (auto iter{graph.cbegin()}; iter != graph.cend(); ++iter)
      {
         print("{} ", *iter);
      }

      println("");
   }

   {
      // Test rbegin()/rend()
      print("Nodes: ");
      for (auto iter{graph.rbegin()}; iter != graph.rend(); ++iter)
      {
         print("{} ", *iter);
      }

      println("");
   }

   println("{}", ToDot(graph, "Graph1"));

   // Query information of a graph.	
   println("Size: {}", graph.size());
   println("MaxSize: {}", graph.maxSize());
   println("IsEmpty?: {}", graph.empty());

   // Test swapping graphs.
   DiGraph<int> otherGraph;
   Swap(graph, otherGraph);

   println("After swapping:");
   println("Size: {}", graph.size());
   println("MaxSize: {}", graph.maxSize());
   println("IsEmpty?: {}", graph.empty());

   // Test copying graphs.
   DiGraph<int> graphCopy{otherGraph};
   println("otherGraph == graphCopy? {}", (otherGraph == graphCopy));

   graphCopy.erase(find(begin(graphCopy), end(graphCopy), 33));
   println("otherGraph == graphCopy? {}", (otherGraph == graphCopy));

   // Find a node using find(), and erase the node.
   result = find(begin(graphCopy), end(graphCopy), 22);
   if (result != end(graphCopy))
   {
      println("Node 22 found.");
      auto next{graphCopy.erase(result)};
      if (next != end(graphCopy))
      {
         println("Next after erasing 22: {}", *next);
      }
   }
   else
   {
      println("Node 22 NOT found.");
   }

   // Erase a range of nodes.
   result = find(begin(graphCopy), end(graphCopy), 55);
   auto result2{find(begin(graphCopy), end(graphCopy), 33)};
   auto next = graphCopy.erase(result, result2);
   if (next != end(graphCopy))
   {
      println("Next after erasing range [55,33): {}", *next);
   }
   println("{}", ToDot(graphCopy, "Graph1"));

   // Clear the graph.
   graph.clear();

   // Test equality
   DiGraph<int> graph1;
   graph1.insert(11);
   graph1.insert(22);
   graph1.insert(33);
   graph1.insertEdge(11, 22);
   graph1.insertEdge(11, 33);
   graph1.insertEdge(22, 33);

   DiGraph<int> graph2;
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
   DiGraph<int> graph3;
   graph3 = graph2;
   println("{}", ToDot(graph3, "graph3"));

   // Test a graph with strings.
   DiGraph<string> graphStrings;
   graphStrings.insert("String 1");
   string str{"String 2"};
   graphStrings.insert(str);
   graphStrings.insert("String 3");
   graphStrings.insert("String 4");
   graphStrings.insertEdge("String 1", str);
   graphStrings.insertEdge("String 2", str);
   graphStrings.insertEdge("String 3", str);

   println("{}", ToDot(graphStrings, "String Graph"));

   {
      // Test rbegin()/rend()
      print("Nodes: ");
      for (auto iter{graphStrings.rbegin()}; iter != graphStrings.rend(); ++iter)
      {
         print("{} ", *iter);
      }

      println("");
   }

   auto result3{find(begin(graphStrings), end(graphStrings), "String 3")};
   if (result3 != end(graphStrings))
   {
      println("Node String 3 found.");
   }
   else
   {
      println("Node String 3 NOT found.");
   }
}
