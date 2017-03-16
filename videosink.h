#pragma once

#include <nan.h>

class VideoSink : public Nan::ObjectWrap {
    public:
        static void Init(v8::Local<v8::Object> exports);

    private:
        explicit VideoSink(char* path, int num_pages, size_t page_size);
        ~VideoSink();

        static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);
        static void WriteFrame(const Nan::FunctionCallbackInfo<v8::Value>& info);
        static Nan::Persistent<v8::Function> constructor;

        int num_pages_;
        size_t page_size_;
};
