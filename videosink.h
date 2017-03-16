#pragma once

#include <string>

#include <nan.h>
#include <shoom.h>

class VideoSink : public Nan::ObjectWrap {
    public:
        static void Init(v8::Local<v8::Object> exports);

    private:
        explicit VideoSink(std::string path, size_t size);
        ~VideoSink();

        static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);
        static void Create(const Nan::FunctionCallbackInfo<v8::Value>& info);
        static void Open(const Nan::FunctionCallbackInfo<v8::Value>& info);
        static void Write(const Nan::FunctionCallbackInfo<v8::Value>& info);
        static void Read(const Nan::FunctionCallbackInfo<v8::Value>& info);
        static Nan::Persistent<v8::Function> constructor;

        shoom::Shm *shm_;
};
