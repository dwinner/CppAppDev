export module directed_graph:const_adjacent_nodes_iterator_impl;

import std;

namespace proCpp
{
   template <typename TDiGraph>
   class ConstAdjacentNodesIteratorImpl
   {
   public:
      using value_type = typename TDiGraph::value_type;
      using difference_type = std::ptrdiff_t;
      using IteratorCategory = std::bidirectional_iterator_tag;
      using Pointer = const value_type*;
      using Reference = const value_type&;
      using IteratorType = std::set<std::size_t>::const_iterator;

      // Bidirectional iterators must supply a default constructor.
      // In this case, the default-constructed iterator serves as an
      // end iterator.
      ConstAdjacentNodesIteratorImpl() = default;

      // No transfer of ownership of graph.
      explicit ConstAdjacentNodesIteratorImpl(const IteratorType& iteratorType, const TDiGraph* graph);

      Reference operator*() const;

      // Return type must be something to which -> can be applied.
      // Return a pointer to a node, to which the compiler
      // will apply -> again.
      Pointer operator->() const;

      ConstAdjacentNodesIteratorImpl& operator++();

      ConstAdjacentNodesIteratorImpl operator++(int);

      ConstAdjacentNodesIteratorImpl& operator--();

      ConstAdjacentNodesIteratorImpl operator--(int);

      // The following are ok as member functions because we don't
      // support comparisons of different types to this one.
      bool operator==(const ConstAdjacentNodesIteratorImpl& rhs) const;

      bool operator!=(const ConstAdjacentNodesIteratorImpl& rhs) const;

   protected:
      IteratorType adjacentNodeIterator_;

      // If nullptr, then this instance is an end iterator.
      const TDiGraph* graph_{nullptr};
   };

   template <typename TDiGraph>
   ConstAdjacentNodesIteratorImpl<TDiGraph>::ConstAdjacentNodesIteratorImpl(
      const IteratorType& iteratorType, const TDiGraph* graph) :
      adjacentNodeIterator_{iteratorType},
      graph_{graph}
   {
   }

   // Return a reference to the node.
   template <typename TDiGraph>
   typename ConstAdjacentNodesIteratorImpl<TDiGraph>::Reference
   ConstAdjacentNodesIteratorImpl<TDiGraph>::operator*() const
   {
      // Return a reference to the actual node, not the index to the node.
      return (*graph_)[*adjacentNodeIterator_];
   }

   // Return a pointer to the actual node, so the compiler can
   // apply -> to it to access the actual desired field.
   template <typename TDiGraph>
   typename ConstAdjacentNodesIteratorImpl<TDiGraph>::Pointer
   ConstAdjacentNodesIteratorImpl<TDiGraph>::operator->() const
   {
      return &((*graph_)[*adjacentNodeIterator_]);
   }

   template <typename TDiGraph>
   ConstAdjacentNodesIteratorImpl<TDiGraph>&
   ConstAdjacentNodesIteratorImpl<TDiGraph>::operator++()
   {
      ++adjacentNodeIterator_;
      return *this;
   }

   template <typename TDiGraph>
   ConstAdjacentNodesIteratorImpl<TDiGraph>
   ConstAdjacentNodesIteratorImpl<TDiGraph>::operator++(int)
   {
      auto oldIt{*this};
      ++*this;
      return oldIt;
   }

   template <typename TDiGraph>
   ConstAdjacentNodesIteratorImpl<TDiGraph>&
   ConstAdjacentNodesIteratorImpl<TDiGraph>::operator--()
   {
      --adjacentNodeIterator_;
      return *this;
   }

   template <typename TDiGraph>
   ConstAdjacentNodesIteratorImpl<TDiGraph>
   ConstAdjacentNodesIteratorImpl<TDiGraph>::operator--(int)
   {
      auto oldIt{*this};
      --*this;
      return oldIt;
   }

   template <typename TDiGraph>
   bool ConstAdjacentNodesIteratorImpl<TDiGraph>::operator==(
      const ConstAdjacentNodesIteratorImpl<TDiGraph>& rhs) const
   {
      if (!graph_ && !rhs.graph_)
      {
         // They are both end iterators.
         return true;
      }

      return (graph_ == rhs.graph_
         && adjacentNodeIterator_ == rhs.adjacentNodeIterator_);
   }

   template <typename TDiGraph>
   bool ConstAdjacentNodesIteratorImpl<TDiGraph>::operator!=(
      const ConstAdjacentNodesIteratorImpl<TDiGraph>& rhs) const
   {
      return !(*this == rhs);
   }
}
