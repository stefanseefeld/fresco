#include "Berlin/Provider.hh"
#include "Berlin/RegionImpl.hh"
#include "Berlin/TransformImpl.hh"
#include "Berlin/AllocationImpl.hh"

using namespace Prague;

stack<RegionImpl *> Provider<RegionImpl>::pool;
Mutex Provider<RegionImpl>::mutex;
stack<TransformImpl *> Provider<TransformImpl>::pool;
Mutex Provider<TransformImpl>::mutex;
stack<AllocationImpl *> Provider<AllocationImpl>::pool;  
Mutex Provider<AllocationImpl>::mutex;
