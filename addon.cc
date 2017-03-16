#include <nan.h>
#include "node_shoom.h"

void InitAll(v8::Local<v8::Object> exports) {
    node_shoom::Shm::Init(exports);
}

NODE_MODULE(capsule_videosink, InitAll)