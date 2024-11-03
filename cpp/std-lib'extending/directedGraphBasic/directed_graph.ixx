export module directed_graph;

import :node;
import std;

namespace proCpp
{
   export
   template <typename T>
   class DirectedGraph
   {
   public:
      // For insert to be successful, the value shall not be in the graph yet. 
      // Returns true if a new node with given value has been added to
      // the graph, and false if there was already a node with the given value.
      bool insert(T nodeValue);

      // Returns true if the given node value was erased, false otherwise.
      bool erase(const T& nodeValue);

      // Returns true if the edge was successfully created, false otherwise.
      bool insertEdge(const T& fromNodeValue, const T& toNodeValue);

      // Returns true if the given edge was erased, false otherwise.
      bool eraseEdge(const T& fromNodeValue, const T& toNodeValue);

      // Removes all nodes from the graph.
      void clear() noexcept;

      // Returns a reference to the value in the node with given index
      // without bounds checking.
      const T& operator[](std::size_t index) const;

      // Two directed graphs are equal if their sets of nodes are equal (where
      // nodes with the same T value are considered equal) and the same number
      // of edges between each corresponding pair of nodes.
      // The order in which the nodes and edges have been added does not
      // affect equality.
      bool operator==(const DirectedGraph& rhs) const;

      // Swaps all nodes between this graph and the given graph.
      void swap(DirectedGraph& otherGraph) noexcept;

      // Returns the number of nodes in the graph.
      [[nodiscard]] std::size_t size() const noexcept;

      // Returns a set with the adjacent nodes of a given node.
      // If the given node does not exist, an empty set is returned.
      [[nodiscard]] std::set<T> getAdjacentNodesValues(const T& nodeValue) const;

   private:
      friend details::GraphNode<T>;

      using NodeContainerType = std::vector<details::GraphNode<T>>;

      NodeContainerType nodes_;

      // Helper member functions to return an iterator to the given node, or the
      // end iterator if the given node is not in the graph.
      typename NodeContainerType::iterator findNode(const T& nodeValue);

      typename NodeContainerType::const_iterator findNode(const T& nodeValue) const;

      // Given an iterator to a node, removes that node from all adjacency lists
      // of all other nodes.
      void removeAllLinksTo(typename NodeContainerType::const_iterator nodeIter);

      // Given a set of adjacency node indices, returns the corresponding
      // set of node values.
      [[nodiscard]] std::set<T> getAdjacentNodesValues(
         const typename details::GraphNode<T>::AdjacencyListType& indices) const;

      // Given an iterator to a node, returns the index of that node in the nodes' container.
      [[nodiscard]] std::size_t getIndexOfNode(typename NodeContainerType::const_iterator node) const noexcept;
   };

   // The following stand-alone swap() function simply
   // forwards to the swap() member function.
   export
   template <typename T>
   void Swap(DirectedGraph<T>& first, DirectedGraph<T>& second) noexcept
   {
      first.swap(second);
   }

   template <typename T>
   bool DirectedGraph<T>::insert(T nodeValue)
   {
      auto iter{
         findNode(nodeValue)
      };
      if (iter != std::end(nodes_))
      {
         // Value is already in the graph, return false.
         return false;
      }

      nodes_.emplace_back(this, std::move(nodeValue));

      // Value successfully added to the graph, return true.
      return true;
   }

   template <typename T>
   std::size_t DirectedGraph<T>::getIndexOfNode(typename NodeContainerType::const_iterator node) const noexcept
   {
      return node - std::cbegin(nodes_);
   }

   template <typename T>
   bool DirectedGraph<T>::insertEdge(const T& fromNodeValue, const T& toNodeValue)
   {
      const auto from{
         findNode(fromNodeValue)
      };
      const auto to{
         findNode(toNodeValue)
      };
      if (from == std::end(nodes_) || to == std::end(nodes_))
      {
         return false;
      }

      const std::size_t toIndex{
         getIndexOfNode(to)
      };

      return from->getAdjacentNodesIndices().insert(toIndex).second;
   }

   template <typename T>
   bool DirectedGraph<T>::eraseEdge(const T& fromNodeValue, const T& toNodeValue)
   {
      const auto from{
         findNode(fromNodeValue)
      };
      const auto to{
         findNode(toNodeValue)
      };
      if (from == std::end(nodes_) || to == std::end(nodes_))
      {
         return false; // nothing to erase
      }

      const std::size_t toIndex{
         getIndexOfNode(to)
      };
      from->getAdjacentNodesIndices().erase(toIndex);

      return true;
   }

   template <typename T>
   void DirectedGraph<T>::removeAllLinksTo(typename NodeContainerType::const_iterator nodeIter)
   {
      const std::size_t nodeIndex{
         getIndexOfNode(nodeIter)
      };
      for (auto&& node : nodes_)
      {
         node.removeNodeIndex(nodeIndex);
      }
   }

   template <typename T>
   bool DirectedGraph<T>::erase(const T& nodeValue)
   {
      auto iter{
         findNode(nodeValue)
      };
      if (iter == std::end(nodes_))
      {
         return false;
      }

      removeAllLinksTo(iter);
      nodes_.erase(iter);

      return true;
   }

   template <typename T>
   void DirectedGraph<T>::clear() noexcept
   {
      nodes_.clear();
   }

   template <typename T>
   typename DirectedGraph<T>::NodeContainerType::iterator
   DirectedGraph<T>::findNode(const T& nodeValue)
   {
      return std::find_if(
         std::begin(nodes_),
         std::end(nodes_),
         [&](const auto& node)
         {
            return node.value() == nodeValue;
         }
      );
   }

   template <typename T>
   typename DirectedGraph<T>::NodeContainerType::const_iterator
   DirectedGraph<T>::findNode(const T& nodeValue) const
   {
      return std::find_if(
         std::begin(nodes_),
         std::end(nodes_),
         [&](const auto& node)
         {
            return node.value() == nodeValue;
         }
      );
   }

   template <typename T>
   const T& DirectedGraph<T>::operator[](std::size_t index) const
   {
      return nodes_[index].value();
   }

   template <typename T>
   std::set<T> DirectedGraph<T>::getAdjacentNodesValues(
      const typename details::GraphNode<T>::AdjacencyListType& indices) const
   {
      std::set<T> values;
      for (auto&& index : indices)
      {
         values.insert(nodes_[index].value());
      }

      return values;
   }

   template <typename T>
   std::set<T> DirectedGraph<T>::getAdjacentNodesValues(const T& nodeValue) const
   {
      auto iter{
         findNode(nodeValue)
      };
      if (iter == std::end(nodes_))
      {
         return {};
      }

      return getAdjacentNodesValues(iter->getAdjacentNodesIndices());
   }

   template <typename T>
   bool DirectedGraph<T>::operator==(const DirectedGraph& rhs) const
   {
      if (nodes_.size() != rhs.nodes_.size())
      {
         return false;
      }

      for (auto&& node : nodes_)
      {
         const auto rhsNodeIter{rhs.findNode(node.value())};
         if (rhsNodeIter == std::end(rhs.nodes_))
         {
            return false;
         }

         const auto adjacentValuesLhs{
            getAdjacentNodesValues(node.getAdjacentNodesIndices())
         };
         const auto adjacentValuesRhs{
            rhs.getAdjacentNodesValues(rhsNodeIter->getAdjacentNodesIndices())
         };

         if (adjacentValuesLhs != adjacentValuesRhs)
         {
            return false;
         }
      }

      return true;
   }

   template <typename T>
   void DirectedGraph<T>::swap(DirectedGraph& otherGraph) noexcept
   {
      nodes_.swap(otherGraph.nodes_);
   }

   template <typename T>
   std::size_t DirectedGraph<T>::size() const noexcept
   {
      return nodes_.size();
   }
}
