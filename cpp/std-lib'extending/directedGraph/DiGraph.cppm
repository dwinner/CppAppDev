export module directed_graph;

export import :const_directed_graph_iterator_impl;
export import :const_adjacent_nodes_iterator_impl;
import :node;
import std;

namespace proCpp
{
   export
   template <typename T>
   class DiGraph
   {
   public:
      using value_type = T;
      using Reference = value_type&;
      using ConstReference = const value_type&;
      using SizeType = std::size_t;
      using difference_type = std::ptrdiff_t;
      using Iterator = ConstDiGraphIteratorImpl<DiGraph>;
      using ConstIterator = ConstDiGraphIteratorImpl<DiGraph>;
      using ReverseIterator = std::reverse_iterator<Iterator>;
      using ConstReverseIterator = std::reverse_iterator<ConstIterator>;
      using ConstAdjacentNodesIterator = ConstAdjacentNodesIteratorImpl<DiGraph>;

      // Default, copy, and move constructors.
      DiGraph() = default;

      DiGraph(const DiGraph&) = default;

      DiGraph(DiGraph&&) noexcept = default;

      // initializer_list constructor.
      DiGraph(std::initializer_list<T> il);

      // Iterator range constructor.
      template <std::input_iterator Iter>
      explicit DiGraph(Iter first, Iter last);

      // Copy and move assignment operators.
      DiGraph& operator=(const DiGraph&) = default;

      DiGraph& operator=(DiGraph&&) noexcept = default;

      // dtor
      ~DiGraph() = default;

      // initializer_list assignment operator.
      DiGraph& operator=(std::initializer_list<T> il);

      void assign(std::initializer_list<T> il);

      template <std::input_iterator Iter>
      void assign(Iter first, Iter last);

      // For an insert to be successful, the value shall not be in the graph yet. 
      // The iterator in the returned pair points to the inserted node, or to the
      // node that was already in the graph with the given value.
      // The boolean is true if a new node with given value has been added to
      // the graph, and false if there was already a node with the given value.
      std::pair<Iterator, bool> insert(T nodeValue);

      Iterator insert(ConstIterator hint, T nodeValue);

      template <std::input_iterator Iter>
      void insert(Iter first, Iter last);

      void insert(std::initializer_list<T> il);

      template <std::ranges::input_range Range>
      void insertRange(Range&& range);

      // Returns an iterator to the element after the last deleted element.
      Iterator erase(ConstIterator pos);

      Iterator erase(ConstIterator first, ConstIterator last);

      SizeType erase(const T& nodeValue);

      // Returns true if the edge was successfully created, false otherwise.
      bool insertEdge(const T& fromNodeValue, const T& toNodeValue);

      // Returns true if the given edge was erased, false otherwise.
      bool eraseEdge(const T& fromNodeValue, const T& toNodeValue);

      // Removes all nodes from the graph.
      void clear() noexcept;

      // Returns a reference to the value in the node with given index
      // without bounds checking.
      ConstReference operator[](SizeType index) const;

      // Returns a reference to the value in the node with given index
      // with bounds checking.
      ConstReference at(SizeType index) const;

      // Iterator member functions.
      Iterator begin() noexcept;

      Iterator end() noexcept;

      ConstIterator begin() const noexcept;

      ConstIterator end() const noexcept;

      ConstIterator cbegin() const noexcept;

      ConstIterator cend() const noexcept;

      ReverseIterator rbegin() noexcept;

      ReverseIterator rend() noexcept;

      ConstReverseIterator rbegin() const noexcept;

      ConstReverseIterator rend() const noexcept;

      ConstReverseIterator crbegin() const noexcept;

      ConstReverseIterator crend() const noexcept;

      // Helper structure to represent a range of adjacent nodes.
      struct NodesAdjacentToResult
      {
         ConstAdjacentNodesIterator mBegin;
         ConstAdjacentNodesIterator mEnd;

         ConstAdjacentNodesIterator begin() const noexcept
         {
            return mBegin;
         }

         ConstAdjacentNodesIterator end() const noexcept
         {
            return mEnd;
         }
      };

      // Returns a range with the adjacent nodes for the given node value.
      std::optional<NodesAdjacentToResult> nodesAdjacentTo(const T& nodeValue) const noexcept;

      // Two directed graphs are equal if their sets of nodes are equal (where
      // nodes with the same T value are considered equal) and the same number
      // of edges between each corresponding pair of nodes.
      // The order in which the nodes and edges have been added does not
      // affect equality.
      bool operator==(const DiGraph& rhs) const;

      // Swaps all nodes between this graph and the given graph.
      void swap(DiGraph& otherGraph) noexcept;

      // Returns the number of nodes in the graph.
      [[nodiscard]] SizeType size() const noexcept;

      [[nodiscard]] SizeType maxSize() const noexcept;

      [[nodiscard]] bool empty() const noexcept;

      // Finds an element in the graph.
      // Returns an end iterator if not found.
      ConstIterator find(const T& nodeValue) const;

      // Returns true if node_value is in the graph, false otherwise.
      bool contains(const T& nodeValue) const;

   private:
      friend class ConstDiGraphIteratorImpl<DiGraph>;
      friend class details::GraphNode<T>;

      using NodeContainerType = std::vector<details::GraphNode<T>>;

      NodeContainerType nodes_;

      // Helper member functions to return an iterator to the given node, or the end iterator
      // if the given node is not in the graph.
      [[nodiscard]] typename NodeContainerType::iterator findNode(const T& nodeValue);

      [[nodiscard]] typename NodeContainerType::const_iterator findNode(const T& nodeValue) const;

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
   void Swap(DiGraph<T>& first, DiGraph<T>& second) noexcept
   {
      first.swap(second);
   }

   template <typename T>
   DiGraph<T>::DiGraph(std::initializer_list<T> il)
   {
      assign(std::begin(il), std::end(il));
   }

   template <typename T>
   template <std::input_iterator Iter>
   DiGraph<T>::DiGraph(Iter first, Iter last)
   {
      assign(first, last);
   }

   template <typename T>
   template <std::input_iterator Iter>
   void DiGraph<T>::assign(Iter first, Iter last)
   {
      clear();
      for (auto iter{first}; iter != last; ++iter)
      {
         insert(*iter);
      }
   }

   template <typename T>
   void DiGraph<T>::assign(std::initializer_list<T> il)
   {
      assign(std::begin(il), std::end(il));
   }

   template <typename T>
   DiGraph<T>& DiGraph<T>::operator=(std::initializer_list<T> il)
   {
      // Use a copy-and-swap-like algorithm to guarantee strong exception safety.
      // Do all the work in a temporary instance.
      DiGraph newGraph{il};
      swap(newGraph); // Commit the work with only non-throwing operations.
      return *this;
   }

   template <typename T>
   std::pair<typename DiGraph<T>::Iterator, bool> DiGraph<T>::insert(T nodeValue)
   {
      auto iter{findNode(nodeValue)};
      if (iter != std::end(nodes_))
      {
         // Value is already in the graph.
         return {Iterator{iter}, false};
      }

      nodes_.emplace_back(this, std::move(nodeValue));

      // Value successfully added to the graph.
      return {
         Iterator{std::prev(std::end(nodes_))},
         true
      };
   }

   template <typename T>
   typename DiGraph<T>::Iterator DiGraph<T>::insert(ConstIterator hint, T nodeValue)
   {
      // Ignore the hint, just forward to another insert().
      return insert(std::move(nodeValue)).first;
   }

   template <typename T>
   template <std::input_iterator Iter>
   void DiGraph<T>::insert(Iter first, Iter last)
   {
      // Copy each element in the range by using an insert_iterator adapter.
      // Give end() as a dummy position -- insert ignores it anyway.
      std::copy(first, last, std::insert_iterator{*this, end()});
   }

   template <typename T>
   void DiGraph<T>::insert(std::initializer_list<T> il)
   {
      insert(std::begin(il), std::end(il));
   }

   template <typename T>
   template <std::ranges::input_range Range>
   void DiGraph<T>::insertRange(Range&& range)
   {
      insert(std::ranges::begin(range), std::ranges::end(range));
   }

   template <typename T>
   std::size_t DiGraph<T>::getIndexOfNode(typename NodeContainerType::const_iterator node) const noexcept
   {
      return node - std::cbegin(nodes_);
   }

   template <typename T>
   bool DiGraph<T>::insertEdge(const T& fromNodeValue, const T& toNodeValue)
   {
      const auto from{findNode(fromNodeValue)};
      const auto to{findNode(toNodeValue)};
      if (from == std::end(nodes_) || to == std::end(nodes_))
      {
         return false;
      }

      const std::size_t toIndex{getIndexOfNode(to)};
      return from->getAdjacentNodesIndices().insert(toIndex).second;
   }

   template <typename T>
   bool DiGraph<T>::eraseEdge(const T& fromNodeValue, const T& toNodeValue)
   {
      const auto from{findNode(fromNodeValue)};
      const auto to{findNode(toNodeValue)};
      if (from == std::end(nodes_) || to == std::end(nodes_))
      {
         return false; // nothing to erase
      }

      const std::size_t toIndex{getIndexOfNode(to)};
      from->getAdjacentNodesIndices().erase(toIndex);

      return true;
   }

   template <typename T>
   void DiGraph<T>::removeAllLinksTo(typename NodeContainerType::const_iterator nodeIter)
   {
      const std::size_t nodeIndex{getIndexOfNode(nodeIter)};
      for (auto&& node : nodes_)
      {
         node.removeNodeIndex(nodeIndex);
      }
   }

   template <typename T>
   typename DiGraph<T>::Iterator
   DiGraph<T>::erase(ConstIterator pos)
   {
      if (pos.nodeIterator_ == std::end(nodes_))
      {
         return end();
      }

      removeAllLinksTo(pos.nodeIterator_);
      return Iterator{nodes_.erase(pos.nodeIterator_)};
   }

   template <typename T>
   typename DiGraph<T>::Iterator
   DiGraph<T>::erase(ConstIterator first, ConstIterator last)
   {
      for (auto iter{first}; iter != last; ++iter)
      {
         removeAllLinksTo(iter.nodeIterator_);
      }

      return Iterator{
         nodes_.erase(first.nodeIterator_, last.nodeIterator_)
      };
   }

   template <typename T>
   typename DiGraph<T>::SizeType DiGraph<T>::erase(const T& nodeValue)
   {
      const auto iter{findNode(nodeValue)};
      if (iter != std::end(nodes_))
      {
         removeAllLinksTo(iter);
         nodes_.erase(iter);
         return 1;
      }

      return 0;
   }

   template <typename T>
   void DiGraph<T>::clear() noexcept
   {
      nodes_.clear();
   }

   template <typename T>
   typename DiGraph<T>::NodeContainerType::iterator
   DiGraph<T>::findNode(const T& nodeValue)
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
   typename DiGraph<T>::NodeContainerType::const_iterator
   DiGraph<T>::findNode(const T& nodeValue) const
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
   typename DiGraph<T>::ConstReference
   DiGraph<T>::operator[](SizeType index) const
   {
      return nodes_[index].value();
   }

   template <typename T>
   typename DiGraph<T>::ConstReference
   DiGraph<T>::at(SizeType index) const
   {
      return nodes_.at(index).value();
   }

   template <typename T>
   typename DiGraph<T>::Iterator
   DiGraph<T>::begin() noexcept
   {
      return Iterator{std::begin(nodes_)};
   }

   template <typename T>
   typename DiGraph<T>::Iterator
   DiGraph<T>::end() noexcept
   {
      return Iterator{std::end(nodes_)};
   }

   template <typename T>
   typename DiGraph<T>::ConstIterator
   DiGraph<T>::begin() const noexcept
   {
      return ConstIterator{std::begin(nodes_)};
   }

   template <typename T>
   typename DiGraph<T>::ConstIterator
   DiGraph<T>::end() const noexcept
   {
      return ConstIterator{std::end(nodes_)};
   }

   template <typename T>
   typename DiGraph<T>::ConstIterator
   DiGraph<T>::cbegin() const noexcept
   {
      return begin();
   }

   template <typename T>
   typename DiGraph<T>::ConstIterator
   DiGraph<T>::cend() const noexcept
   {
      return end();
   }

   template <typename T>
   typename DiGraph<T>::ReverseIterator
   DiGraph<T>::rbegin() noexcept
   {
      return ReverseIterator{end()};
   }

   template <typename T>
   typename DiGraph<T>::ReverseIterator
   DiGraph<T>::rend() noexcept
   {
      return ReverseIterator{begin()};
   }

   template <typename T>
   typename DiGraph<T>::ConstReverseIterator
   DiGraph<T>::rbegin() const noexcept
   {
      return ConstReverseIterator{end()};
   }

   template <typename T>
   typename DiGraph<T>::ConstReverseIterator
   DiGraph<T>::rend() const noexcept
   {
      return ConstReverseIterator{begin()};
   }

   template <typename T>
   typename DiGraph<T>::ConstReverseIterator
   DiGraph<T>::crbegin() const noexcept
   {
      return rbegin();
   }

   template <typename T>
   typename DiGraph<T>::ConstReverseIterator
   DiGraph<T>::crend() const noexcept
   {
      return rend();
   }

   template <typename T>
   std::optional<typename DiGraph<T>::NodesAdjacentToResult>
   DiGraph<T>::nodesAdjacentTo(const T& nodeValue) const noexcept
   {
      auto iter{findNode(nodeValue)};
      if (iter == std::end(nodes_))
      {
         return {};
      }

      return NodesAdjacentToResult{
         ConstAdjacentNodesIterator{std::cbegin(iter->getAdjacentNodesIndices()), this},
         ConstAdjacentNodesIterator{std::cend(iter->getAdjacentNodesIndices()), this}
      };
   }

   template <typename T>
   std::set<T> DiGraph<T>::getAdjacentNodesValues(
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
   bool DiGraph<T>::operator==(const DiGraph& rhs) const
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
   void DiGraph<T>::swap(DiGraph& otherGraph) noexcept
   {
      nodes_.swap(otherGraph.nodes_);
   }

   template <typename T>
   typename DiGraph<T>::SizeType DiGraph<T>::size() const noexcept
   {
      return nodes_.size();
   }

   template <typename T>
   typename DiGraph<T>::SizeType DiGraph<T>::maxSize() const noexcept
   {
      return nodes_.max_size();
   }

   template <typename T>
   bool DiGraph<T>::empty() const noexcept
   {
      return nodes_.empty();
   }

   template <typename T>
   typename DiGraph<T>::ConstIterator DiGraph<T>::find(const T& nodeValue) const
   {
      auto iter{findNode(nodeValue)};
      return ConstIterator{iter};
   }

   template <typename T>
   bool DiGraph<T>::contains(const T& nodeValue) const
   {
      const auto iter{findNode(nodeValue)};
      return iter != std::end(nodes_);
   }
}
