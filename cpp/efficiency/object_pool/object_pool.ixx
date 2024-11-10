module;
#include <cassert>

export module object_pool;

import std;

/**
 * @brief Provides an object pool that can be used with any class.
 *	@details acquireObject() returns an object from the list of free objects. If
 * there are no more free objects, acquireObject() creates a new chunk
 * of objects.
 * The pool only grows: objects are never removed from the pool, until
 * the pool is destroyed.
 * acquireObject() returns a std::shared_ptr with a custom deleter that
 * automatically puts the object back into the object pool when the
 * shared_ptr is destroyed and its reference count reaches 0.
 * @tparam TObj Object type
 * @tparam TAllocator Allocator used  for memory
 */
export template <typename TObj, typename TAllocator = std::allocator<TObj>>
class ObjectPool final
{
public:
   ObjectPool() = default;

   explicit ObjectPool(const TAllocator& allocator);

   ~ObjectPool();

   // Prevent move construction and move assignment.
   ObjectPool(ObjectPool&&) = delete;

   ObjectPool& operator=(ObjectPool&&) = delete;

   // Prevent copy construction and copy assignment.
   ObjectPool(const ObjectPool&) = delete;

   ObjectPool& operator=(const ObjectPool&) = delete;

   // 
   // 
   /**
    * @brief Reserves and returns an object from the pool.
    * Arguments can be provided which are perfectly forwarded to a constructor of TObj.
    * @tparam Args Type parameter for forwarded variable args of objects
    * @param args Args Passed objects
    * @return Allocated objects
    */
   template <typename... Args>
   std::shared_ptr<TObj> acquireObject(Args&&... args);

private:
   /**
    * @brief Creates a new block of uninitialized memory, big enough to hold
    * newChunkSize_ instances of T.
    */
   void addChunk();

   /**
    * @brief Contains chunks of memory in which instances of T will be created.
    * For each chunk, the pointer to its first object is stored.
    */
   std::vector<TObj*> pool_;

   /**
    * @brief Contains pointers to all free instances of T that
    *	are available in the pool.
    */
   std::vector<TObj*> freeObjects_;

   /**
    * @brief The number of T instances that should fit in the first allocated chunk.
    */
   static constexpr std::size_t initialChunkSize{5};

   /**
    * @brief The number of T instances that should fit in a newly allocated chunk.
    *	This value is doubled after each newly created chunk.
    */
   std::size_t newChunkSize_{initialChunkSize};

   /**
    * @brief The allocator to use for allocating and deallocating chunks.
    */
   TAllocator allocator_;
};

template <typename TObj, typename TAllocator>
ObjectPool<TObj, TAllocator>::ObjectPool(const TAllocator& allocator)
   : allocator_{allocator}
{
}

template <typename TObj, typename TAllocator>
ObjectPool<TObj, TAllocator>::~ObjectPool()
{
   // Note: this implementation assumes that all objects handed out by this
   //       pool have been returned to the pool before the pool is destroyed.
   //       The following statement asserts if that is not the case.
   assert(freeObjects_.size() == initialChunkSize * (std::pow(2, pool_.size()) - 1));

   // Deallocate all allocated memory.
   std::size_t chunkSize{initialChunkSize};
   for (auto* chunk : pool_)
   {
      allocator_.deallocate(chunk, chunkSize);
      chunkSize *= 2;
   }

   pool_.clear();
}

template <typename TObj, typename TAllocator>
template <typename... TArgs>
std::shared_ptr<TObj> ObjectPool<TObj, TAllocator>::acquireObject(TArgs&&... args)
{
   // If there are no free objects, allocate a new chunk.
   if (freeObjects_.empty())
   {
      addChunk();
   }

   // Get a free object.
   TObj* tObj{freeObjects_.back()};

   // Initialize, i.e. construct, an instance of T in an
   // uninitialized block of memory using placement new, and
   // perfectly forward any provided arguments to the constructor.
   ::new(tObj) TObj{std::forward<TArgs>(args)...};

   // Launder the object pointer.
   TObj* constructedObject{std::launder(tObj)};

   // Remove the object from the list of free objects.
   freeObjects_.pop_back();

   // Wrap the constructed object and return it.
   return std::shared_ptr<TObj>{
      constructedObject, [this](TObj* object)
      {
         // Destroy object.
         std::destroy_at(object);

         // Put the object back in the list of free objects.
         freeObjects_.push_back(object);
      }
   };
}

template <typename TObj, typename TAllocator>
void ObjectPool<TObj, TAllocator>::addChunk()
{
#ifndef NDEBUG
   std::println("Allocating new chunk...");
#endif

   // Allocate a new chunk of uninitialized memory big enough to hold
   // newChunkSize_ instances of T, and add the chunk to the pool.
   // Care is taken that everything is cleaned up in the event of an exception.
   pool_.push_back(nullptr);
   try
   {
      pool_.back() = allocator_.allocate(newChunkSize_);
   }
   catch (...)
   {
      pool_.pop_back();
      throw;
   }

   // Create pointers to each individual object in the new chunk
   // and store them in the list of free objects.
   auto oldFreeObjectsSize{freeObjects_.size()};
   freeObjects_.resize(oldFreeObjectsSize + newChunkSize_);
   std::iota(
      begin(freeObjects_) + oldFreeObjectsSize,
      end(freeObjects_),
      pool_.back()
   );

   // Double the chunk size for next time.
   newChunkSize_ *= 2;
}
