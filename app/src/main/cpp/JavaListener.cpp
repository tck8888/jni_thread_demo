//
// Created by tck on 2020/11/26.
//

#include "JavaListener.h"


JavaListener::~JavaListener() {
    env->DeleteGlobalRef(this->jobj);
    jobj = nullptr;
}

void JavaListener::onError(int code, const char *msg, int thread) {
    if (thread == THREAD_CHILD) {
        JNIEnv *jniEnv;
        if (javaVM->AttachCurrentThread(&jniEnv, nullptr) != JNI_OK) {
            return;
        }
        jstring jmsg = jniEnv->NewStringUTF(msg);
        jniEnv->CallVoidMethod(jobj, jmid_error, code, jmsg);
        jniEnv->DeleteLocalRef(jmsg);
        javaVM->DetachCurrentThread();
    } else {
        jstring jmsg = env->NewStringUTF(msg);
        env->CallVoidMethod(jobj, jmid_error, code, jmsg);
        env->DeleteLocalRef(jmsg);
    }
}

JavaListener::JavaListener(JavaVM *_javaVM, JNIEnv *_env, jobject &_jobj) : javaVM(_javaVM),
                                                                            env(_env) {
    jobj = env->NewGlobalRef(_jobj);
    jclass jclazz = env->GetObjectClass(jobj);
    jmid_error = env->GetMethodID(jclazz, "onError", "(ILjava/lang/String;)V");

}

