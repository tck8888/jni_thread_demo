#include <jni.h>
#include <string>
#include "pthread.h"
#include "AndroidLog.h"

pthread_t thread;

void *normalCallBack(void *data) {
    LOGD("create normal thread from C++!");
    pthread_exit(&thread);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_tck_jni_thread_ThreadTrain_normalThread(JNIEnv *env, jobject thiz) {

    pthread_create(&thread, nullptr, normalCallBack, nullptr);

}

#include "queue"
#include "unistd.h"
#include "JavaListener.h"

pthread_t product;
pthread_t custom;
pthread_mutex_t mutex;
pthread_cond_t cond;

std::queue<int> queue;

void *productFunc(void *data) {
    while (1) {
        pthread_mutex_lock(&mutex);
        queue.push(1);
        LOGD("生产者生产一个产品，通知消费者消费， 产品数量为 %d", queue.size());
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        sleep(5);
    }
    pthread_exit(&product);

    return nullptr;
}

void *customFunc(void *data) {
    while (1) {
        pthread_mutex_lock(&mutex);
        if (queue.size() > 0) {
            queue.pop();
            LOGD("消费者消费产品，产品数量还剩余 %d ", queue.size());
        } else {
            LOGD("没有产品可以消费， 等待中...");
            pthread_cond_wait(&cond, &mutex);
        }
        pthread_mutex_unlock(&mutex);
        usleep(500 * 1000);
    }
    pthread_exit(&custom);
    return nullptr;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_tck_jni_thread_ThreadTrain_mutexThread(JNIEnv *env, jobject thiz) {
    for (int i = 0; i < 5; ++i) {
        queue.push(i);
    }
    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&cond, nullptr);

    pthread_create(&product, nullptr, productFunc, nullptr);
    pthread_create(&custom, nullptr, customFunc, nullptr);
}

JavaVM *javaVM = nullptr;

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    javaVM = vm;
    return JNI_VERSION_1_6;
}

pthread_t childThread;

void *childCallback(void *data) {
    auto *javaListener1 = (JavaListener *) data;
    javaListener1->onError(101, "c++ call java method from child thread!", THREAD_CHILD);
    pthread_exit(&childThread);
    return nullptr;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_tck_jni_thread_ThreadTrain_callbackFromC(JNIEnv *env, jobject thiz) {

    auto javaListener = new JavaListener(javaVM, env, thiz);
    pthread_create(&childThread, nullptr, childCallback, javaListener);
}

