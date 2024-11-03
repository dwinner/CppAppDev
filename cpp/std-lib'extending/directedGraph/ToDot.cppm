export module directed_graph.to_dot;

import directed_graph;
import std;

namespace proCpp
{
   // Returns a given graph in DOT format.
   export
   template <typename T>
   std::string ToDot(const DiGraph<T>& graph, std::string_view graphName)
   {
      std::ostringstream output;

      std::println(output, "digraph {} {{", graphName);
      for (auto&& node : graph)
      {
         auto adjacentNodes{graph.nodesAdjacentTo(node)};
         if (adjacentNodes->begin() == adjacentNodes->end())
         {
            std::println(output, "{}", node);
         }
         else
         {
            for (const auto& adjacentNode : *adjacentNodes)
            {
               std::println(output, "{} -> {}", node, adjacentNode);
            }
         }
      }

      std::println(output, "}}");

      return std::move(output).str();
   }
}
