#include "videosink.h"

Nan::Persistent<v8::Function> VideoSink::constructor;

VideoSink::VideoSink(char *path_in,
    int width_in, int height_in, int cotsponents_in) {
    // muffin
}

VideoSink::~VideoSink() {
    // muffin
}

void VideoSink::Init(v8::Local<v8::Object> exports) {
    Nan::HandleScope scope;

    // Prepare constructor template
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("VideoSink").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    // Prototype
    Nan::SetPrototypeMethod(tpl, "writeFrame", WriteFrame);

    constructor.Reset(tpl->GetFunction());
    exports->Set(Nan::New("VideoSink").ToLocalChecked(), tpl->GetFunction());
}

void VideoSink::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
    if (!info.IsConstructCall()) {
        Nan::ThrowError("VideoSink must be called as a constructor");
        return;
    }

    if (!info[0]->IsObject()) {
        Nan::ThrowError("VideoSink constructor expects an object");
        return;
    }

    auto opts = Nan::To<v8::Object>(info[0]).ToLocalChecked();

    VideoSink *sink = new VideoSink(
        "/capsule.shm", 800, 600, 4);
    sink->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
}

void VideoSink::WriteFrame(const Nan::FunctionCallbackInfo<v8::Value>& info) {
    info.GetReturnValue().Set(Nan::New("WriteFrame: stub").ToLocalChecked());
}

