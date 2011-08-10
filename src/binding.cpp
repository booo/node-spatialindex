#include "binding.hpp"
#include "rtree.hpp"

#include <spatialindex/SpatialIndex.h>

using namespace SpatialIndex;

extern "C" {
    void init (Handle<Object> target) {
        HandleScope scope;
        NodeRTree::Initialize(target);
    }

    NODE_MODULE(spatialindex, init);

}
