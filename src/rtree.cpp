#include "rtree.hpp"
#include <spatialindex/SpatialIndex.h>

using namespace SpatialIndex;

NodeRTree::NodeRTree(double fillFactor, uint32_t indexCapacity, uint32_t leafCapacity, uint32_t dimension) {

    memory = StorageManager::createNewMemoryStorageManager();
    id_type indexIdentifier;
    index = createNewRTree(*memory, fillFactor, indexCapacity, leafCapacity, dimension, SpatialIndex::RTree::RV_RSTAR, indexIdentifier);

}
NodeRTree::~NodeRTree() {}

Handle<Value> NodeRTree::New(const Arguments& args) {
    NodeRTree* rtree;
    HandleScope scope;

    rtree = new NodeRTree(args[0]->ToNumber()->NumberValue(),
            args[1]->ToNumber()->Uint32Value(),
            args[2]->ToNumber()->Uint32Value(),
            args[3]->ToNumber()->Uint32Value());

    rtree->Wrap(args.This());
    return args.This();

}
//required bounds (region) and identifier
//optional data
Handle<Value> NodeRTree::InsertData(const Arguments& args) {
    NodeRTree* rtree;
    HandleScope scope;
    rtree = ObjectWrap::Unwrap<NodeRTree>(args.This());

    id_type id;
    id = args[1]->ToInteger()->IntegerValue();

    double plow[2], phigh[2];

    Local<Object> bounds = args[0]->ToObject();
    plow[0] = bounds->Get(String::New("x1"))->ToNumber()->NumberValue();
    plow[1] = bounds->Get(String::New("y1"))->ToNumber()->NumberValue();
    phigh[0] = bounds->Get(String::New("x2"))->ToNumber()->NumberValue();
    phigh[1] = bounds->Get(String::New("y2"))->ToNumber()->NumberValue();

    Region r = Region(plow, phigh, 2);
    rtree->index->insertData(0,0,r,0);
    return True();

}

static Persistent<FunctionTemplate> s_ct;

void NodeRTree::Initialize(Handle<Object> target) {
    HandleScope scope;

    Local<FunctionTemplate> t = FunctionTemplate::New(New);

    s_ct = Persistent<FunctionTemplate>::New(t);
    s_ct->InstanceTemplate()->SetInternalFieldCount(1);
    s_ct->SetClassName(String::NewSymbol("RTree"));

    NODE_SET_PROTOTYPE_METHOD(s_ct, "insertData", InsertData);

    target->Set(String::NewSymbol("RTree"), s_ct->GetFunction());

}
