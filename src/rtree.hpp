#include "binding.hpp"
#include <spatialindex/SpatialIndex.h>

using namespace SpatialIndex;

class NodeRTree: public ObjectWrap {
    private:
        IStorageManager* memory;
        ISpatialIndex* index;

    public:

        NodeRTree(double fillFactor, uint32_t indexCapacity, uint32_t leafCapacity, uint32_t dimension);
        ~NodeRTree();

        static void Initialize(Handle<Object> target);

    protected:
        static Handle<Value> New(const Arguments& args);
        static Handle<Value> InsertData(const Arguments& args);


};
