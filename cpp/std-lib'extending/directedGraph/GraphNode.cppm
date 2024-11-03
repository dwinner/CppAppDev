export module directed_graph:node;

import std;

namespace proCpp
{
   // Forward declaration.
   export
   template <typename T>
   class DiGraph;

   namespace details
   {
      template <typename T>
      class GraphNode
      {
      public:
         // Constructs a graph_node for the given value.
         explicit GraphNode(DiGraph<T>* graph, T nodeData):
            graph_{graph},
            data_(std::move(nodeData))
         {
         }

         // Returns a reference to the stored value.
         [[nodiscard]] const T& value() const noexcept
         {
            return data_;
         }

         // A type alias for the container type used to store the adjacency list.
         using AdjacencyListType = std::set<std::size_t>;

         // Returns a reference to the adjacency list.
         [[nodiscard]] auto& getAdjacentNodesIndices()
         {
            return adjacentNodeIndices_;
         }

         [[nodiscard]] const auto& getAdjacentNodesIndices() const
         {
            return adjacentNodeIndices_;
         }

         // Removes a given node index from the adjacency list and updates
         // the remaining indices to account for the shift in indices.
         void removeNodeIndex(std::size_t nodeIndex);

      private:
         // A pointer to the graph this node is in.
         DiGraph<T>* graph_;

         T data_;
         AdjacencyListType adjacentNodeIndices_;
      };

      template <typename T>
      void GraphNode<T>::removeNodeIndex(std::size_t nodeIndex)
      {
         // First, remove references to the to-be-deleted node.
         adjacentNodeIndices_.erase(nodeIndex);

         // Second, modify all adjacency indices to account for the removal of a node.
         // std::set doesn't let us modify its elements in place,
         // so we rebuild the set from scratch.
         std::vector<std::size_t> indices(
            std::begin(adjacentNodeIndices_),
            std::end(adjacentNodeIndices_)
         );
         std::for_each(std::begin(indices), std::end(indices),
                       [nodeIndex](std::size_t& index)
                       {
                          if (index > nodeIndex)
                          {
                             --index;
                          }
                       });
         adjacentNodeIndices_.clear();
         adjacentNodeIndices_.insert(std::begin(indices), std::end(indices));
      }
   }
}
