export module directed_graph:const_directed_graph_iterator_impl;

import std;

namespace proCpp
{
   // Forward declaration.
   export
   template <typename T>
   class DiGraph;

   template <typename TDiGraph>
   class ConstDiGraphIteratorImpl
   {
   public:
      using value_type = typename TDiGraph::value_type;
      using difference_type = std::ptrdiff_t;
      using IteratorCategory = std::bidirectional_iterator_tag;
      using Pointer = const value_type*;
      using Reference = const value_type&;
      using NodeContainerIterator = typename TDiGraph::NodeContainerType::const_iterator;

      // Bidirectional iterators must supply a default constructor.
      ConstDiGraphIteratorImpl() = default;

      explicit ConstDiGraphIteratorImpl(NodeContainerIterator iterator);

      Reference operator*() const;

      // Return type must be something to which -> can be applied.
      // So, return a pointer.
      Pointer operator->() const;

      ConstDiGraphIteratorImpl& operator++();

      ConstDiGraphIteratorImpl operator++(int);

      ConstDiGraphIteratorImpl& operator--();

      ConstDiGraphIteratorImpl operator--(int);

      // Defaulted operator==.
      bool operator==(const ConstDiGraphIteratorImpl&) const = default;

   private:
      friend class DiGraph<value_type>;

      NodeContainerIterator nodeIterator_;
   };

   template <typename TDiGraph>
   ConstDiGraphIteratorImpl<TDiGraph>::ConstDiGraphIteratorImpl(
      NodeContainerIterator iterator) : nodeIterator_{iterator}
   {
   }

   // Return a reference to the actual element.
   template <typename TDiGraph>
   typename ConstDiGraphIteratorImpl<TDiGraph>::Reference
   ConstDiGraphIteratorImpl<TDiGraph>::operator*() const
   {
      return nodeIterator_->value();
   }

   // Return a pointer to the actual element, so the compiler can
   // apply -> to it to access the actual desired field.
   template <typename TDiGraph>
   typename ConstDiGraphIteratorImpl<TDiGraph>::Pointer
   ConstDiGraphIteratorImpl<TDiGraph>::operator->() const
   {
      return &nodeIterator_->value();
   }

   template <typename TDiGraph>
   ConstDiGraphIteratorImpl<TDiGraph>&
   ConstDiGraphIteratorImpl<TDiGraph>::operator++()
   {
      ++nodeIterator_;
      return *this;
   }

   template <typename TDiGraph>
   ConstDiGraphIteratorImpl<TDiGraph>
   ConstDiGraphIteratorImpl<TDiGraph>::operator++(int)
   {
      auto oldIt{*this};
      ++*this;
      return oldIt;
   }

   template <typename TDiGraph>
   ConstDiGraphIteratorImpl<TDiGraph>&
   ConstDiGraphIteratorImpl<TDiGraph>::operator--()
   {
      --nodeIterator_;
      return *this;
   }

   template <typename TDiGraph>
   ConstDiGraphIteratorImpl<TDiGraph>
   ConstDiGraphIteratorImpl<TDiGraph>::operator--(int)
   {
      auto oldIt{*this};
      --*this;
      return oldIt;
   }
}
