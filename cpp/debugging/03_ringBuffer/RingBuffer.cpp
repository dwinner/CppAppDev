module ring_buffer;

import std;

using namespace std;

// Initialize the vector to hold exactly numEntries. The vector size
// does not need to change during the lifetime of the object.
// Initialize the other members.
RingBuffer::RingBuffer(size_t numEntries, ostream* outStream)
   : entries_{numEntries},
     outStream_{outStream},
     wrapped_{false}
{
   if (numEntries == 0)
   {
      throw invalid_argument{"Number of entries must be > 0."};
   }

   next_ = begin(entries_);
}

// The addStringEntry algorithm is pretty simple: add the entry to the next
// free spot, then reset next_ to indicate the free spot after
// that. If next_ reaches the end of the vector, it starts over at 0.
//
// The buffer needs to know if the buffer has wrapped or not so
// that it knows whether to print the entries past next_ in operator<<.
void RingBuffer::addStringEntry(string entry)
{
   // If there is a valid outStream_, write this entry to it.
   if (outStream_)
   {
      *outStream_ << entry << endl;
   }

   // Move the entry to the next free spot and increment
   // next_ to point to the free spot after that.
   *next_ = std::move(entry);
   ++next_;

   // Check if we've reached the end of the buffer. If so, we need to wrap.
   if (next_ == end(entries_))
   {
      next_ = begin(entries_);
      wrapped_ = true;
   }
}

// Set the output stream.
ostream* RingBuffer::setOutput(ostream* newOutStream)
{
   return exchange(outStream_, newOutStream);
}

// operator<< uses an ostream_iterator to "copy" entries directly
// from the vector to the output stream.
//
// operator<< must print the entries in order. If the buffer has wrapped,
// the earliest entry is one past the most recent entry, which is the entry
// indicated by m_next. So, first print from entry m_next to the end.
//
// Then (even if the buffer hasn't wrapped) print from beginning to m_next-1.
ostream& operator<<(ostream& outStream, RingBuffer& ringBuffer)
{
   if (ringBuffer.wrapped_)
   {
      // If the buffer has wrapped, print the elements from
      // the earliest entry to the end.
      copy(ringBuffer.next_, end(ringBuffer.entries_), ostream_iterator<string>{outStream, "\n"});
   }

   // Now, print up to the most recent entry.
   // Go up to next_ because the range is not inclusive on the right side.
   copy(begin(ringBuffer.entries_), ringBuffer.next_, ostream_iterator<string>{outStream, "\n"});

   return outStream;
}
