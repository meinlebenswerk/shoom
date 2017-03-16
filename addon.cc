#include <nan.h>
#include "videosink.h"

void InitAll(v8::Local<v8::Object> exports) {
    VideoSink::Init(exports);
}

NODE_MODULE(capsule_videosink, InitAll)