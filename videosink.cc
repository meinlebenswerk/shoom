#include "videosink.h"

Nan::Persistent<v8::Function> VideoSink::constructor;

VideoSink::VideoSink(char *path, int num_pages, size_t page_size) :
    num_pages_(num_pages), page_size_(page_size) {
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

    auto page_size = Nan::Get(opts, Nan::New("page_size").ToLocalChecked()).ToLocalChecked();
    if (page_size->IsUndefined()) {
        Nan::ThrowError("VideoSink constructor: opts must have a 'page_size' property that's a number");
        return;
    }

    auto page_count = Nan::Get(opts, Nan::New("page_count").ToLocalChecked()).ToLocalChecked();
    if (page_count->IsUndefined()) {
        Nan::ThrowError("VideoSink constructor: opts must have a 'page_count' property that's a number");
    }

    VideoSink *sink = new VideoSink("/capsule.shm", 2, 800 * 600 * 4);
    sink->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
}

void VideoSink::WriteFrame(const Nan::FunctionCallbackInfo<v8::Value>& info) {
    info.GetReturnValue().Set(Nan::New("WriteFrame: stub").ToLocalChecked());
}

