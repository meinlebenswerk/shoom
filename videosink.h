#pragma once

#include <nan.h>

class VideoSink : public Nan::ObjectWrap {
    public:
        static void Init(v8::Local<v8::Object> exports);

    private:
        explicit VideoSink(char* path_in, int width_in, int height_in, int components_in);
        ~VideoSink();

        static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);
        static void WriteFrame(const Nan::FunctionCallbackInfo<v8::Value>& info);
        static Nan::Persistent<v8::Function> constructor;
};
