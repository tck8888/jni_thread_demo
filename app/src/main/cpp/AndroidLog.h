//
// Created by tck on 2020/11/26.
//

#ifndef JNI_THREAD_DEMO_ANDROIDLOG_H
#define JNI_THREAD_DEMO_ANDROIDLOG_H

#endif //JNI_THREAD_DEMO_ANDROIDLOG_H

#include <android/log.h>
#define LOGD(FORMAT,...) __android_log_print(ANDROID_LOG_DEBUG, "tck6666", FORMAT, ##__VA_ARGS__);