#include "videosink.h"

Nan::Persistent<v8::Function> VideoSink::constructor;

VideoSink::VideoSink(std::string path, size_t size) {
    shm_ = new shoom::Shm(path, size);
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
    Nan::SetPrototypeMethod(tpl, "create", Create);
    Nan::SetPrototypeMethod(tpl, "open", Open);
    Nan::SetPrototypeMethod(tpl, "write", Write);
    Nan::SetPrototypeMethod(tpl, "read", Read);

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

    auto path = Nan::Get(opts, Nan::New("path").ToLocalChecked()).ToLocalChecked();
    if (path->IsUndefined()) {
        Nan::ThrowError("VideoSink constructor: opts must have a 'path' property that's a string");
        return;
    }

    auto size = Nan::Get(opts, Nan::New("size").ToLocalChecked()).ToLocalChecked();
    if (size->IsUndefined()) {
        Nan::ThrowError("VideoSink constructor: opts must have a 'size' property that's a number");
        return;
    }

    Nan::Utf8String path_chars{path};
    std::string path_string{*path_chars};

    VideoSink *sink = new VideoSink(
        path_string,
        static_cast<size_t>(size->NumberValue())
    );
    sink->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
}

void VideoSink::Create(const Nan::FunctionCallbackInfo<v8::Value>& info) {
    VideoSink* sink = ObjectWrap::Unwrap<VideoSink>(info.Holder());
    auto ret = sink->shm_->Create();
    if (ret != shoom::kOK) {
        Nan::ThrowError("Could not create shared memory object");
        return;
    }
}

void VideoSink::Open(const Nan::FunctionCallbackInfo<v8::Value>& info) {
    VideoSink* sink = ObjectWrap::Unwrap<VideoSink>(info.Holder());
    auto ret = sink->shm_->Open();
    if (ret != shoom::kOK) {
        Nan::ThrowError("Could not open shared memory object");
        return;
    }
}

void VideoSink::Write(const Nan::FunctionCallbackInfo<v8::Value>& info) {
    VideoSink* sink = ObjectWrap::Unwrap<VideoSink>(info.Holder());

    if (!info[0]->IsNumber()) {
        Nan::ThrowError("First argument to write must be a number (offset)");
        return;
    }

    if (!info[1]->IsArrayBufferView()) {
        Nan::ThrowError("Second argument to write must be an array buffer view (src)");
        return;
    }

    ptrdiff_t offset = static_cast<ptrdiff_t>(info[0]->NumberValue());

    Nan::TypedArrayContents<uint8_t> contents{info[1]};

    char *dst = reinterpret_cast<char*>(sink->shm_->Data() + offset);
    char *src = reinterpret_cast<char*>(*contents);
    memcpy(dst, src, contents.length());
}

void VideoSink::Read(const Nan::FunctionCallbackInfo<v8::Value>& info) {
    VideoSink* sink = ObjectWrap::Unwrap<VideoSink>(info.Holder());

    if (!info[0]->IsNumber()) {
        Nan::ThrowError("First argument to write must be a number (offset)");
        return;
    }

    if (!info[1]->IsArrayBufferView()) {
        Nan::ThrowError("Second argument to write must be an array buffer view (dst)");
        return;
    }

    ptrdiff_t offset = static_cast<ptrdiff_t>(info[0]->NumberValue());

    Nan::TypedArrayContents<uint8_t> contents{info[1]};

    char *dst = reinterpret_cast<char*>(*contents);
    char *src = reinterpret_cast<char*>(sink->shm_->Data() + offset);
    memcpy(dst, src, contents.length());
}
