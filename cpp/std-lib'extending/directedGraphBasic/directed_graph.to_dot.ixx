export module directed_graph.to_dot;

import directed_graph;
import std;

namespace proCpp
{
   // Returns a given graph in DOT format.
   export
   template <typename T>
   std::string ToDot(const DirectedGraph<T>& graph, std::string_view graphName)
   {
      std::ostringstream output;

      std::println(output, "digraph {} {{", graphName);
      for (std::size_t index{0}; index < graph.size(); ++index)
      {
         const auto& nodeValue{graph[index]};
         const auto adjacentValues{graph.getAdjacentNodesValues(nodeValue)};
         if (adjacentValues.empty())
         {
            std::println(output, "{}", nodeValue);
         }
         else
         {
            for (auto&& neighbor : adjacentValues)
            {
               std::println(output, "{} -> {}", nodeValue, neighbor);
            }
         }
      }

      std::println(output, "}}");

      return std::move(output).str();
   }
}
