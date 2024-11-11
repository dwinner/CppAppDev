#pragma once

#include "pch.h"
#include <CppUnitTest.h>

namespace objectPoolTest
{
   TEST_CLASS(ObjectPoolTest)
   {
   public:
      TEST_CLASS_INITIALIZE(setUp);

      TEST_CLASS_CLEANUP(tearDown);

      TEST_METHOD(testSimple);

      TEST_METHOD(testException);

      TEST_METHOD(testCreation);

      TEST_METHOD(testAcquire);

      TEST_METHOD(testExclusivity);

      TEST_METHOD(testRelease);
   };
}
