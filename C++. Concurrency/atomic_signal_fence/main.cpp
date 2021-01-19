/**
 * atomic_signal_fence() example
 */

#include <atomic>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <csignal>

static_assert(ATOMIC_INT_LOCK_FREE == 2,
              "atomic_int must be lock-free in the signal handler.");

std::atomic_int guide = ATOMIC_VAR_INIT(0),
    data = ATOMIC_VAR_INIT(0);

void SIGTERM_handler(int sig)
{
   if (std::atomic_load_explicit(&guide, std::memory_order_relaxed) == 1)
   {
      std::atomic_signal_fence(std::memory_order_acquire);
      int d = std::atomic_load_explicit(&data, std::memory_order_relaxed);
      assert(d == 100);               // Condition fulfilled!
   }

   _Exit(0);
}

int main()
{
   if (signal(SIGTERM, SIGTERM_handler) == SIG_ERR)
   {
      perror("signal"), exit(1);
   }

   atomic_store_explicit(&data, 100, std::memory_order_relaxed);
   atomic_signal_fence(std::memory_order_release);
   atomic_store_explicit(&guide, 1, std::memory_order_relaxed);

   return 0;
}
