//
// Created by tck on 2020/11/26.
//

#ifndef JNI_THREAD_DEMO_JAVALISTENER_H
#define JNI_THREAD_DEMO_JAVALISTENER_H


#include "jni.h"

#define THREAD_MAIN 1
#define THREAD_CHILD 2

class JavaListener {


public:
    JavaVM *javaVM;
    JNIEnv *env;
    jobject jobj;
    jmethodID jmid_error;

public:
    JavaListener(JavaVM *_javaVM, JNIEnv *_env, jobject &_jobj);

    ~JavaListener();

public:
    /**
    * 1:主线程
    * 0：子线程
    * @param type
    * @param code
    * @param msg
    */
    void onError(int code, const char *msg, int thread = THREAD_MAIN);
};


#endif //JNI_THREAD_DEMO_JAVALISTENER_H
