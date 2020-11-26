package com.tck.jni.thread

/**
 *<p>description:</p>
 *<p>created on: 2020/11/26 15:59</p>
 * @author tck
 *
 */
class ThreadTrain {

    companion object {
        init {
            System.loadLibrary("native-lib")
        }
    }

    private var onErrorListener: OnErrorListener? = null

    fun setOnErrorListener(onErrorListener: OnErrorListener?) {
        this.onErrorListener = onErrorListener
    }

    fun onError(code: Int, msg: String) {
        onErrorListener?.onError(code, msg)
    }

    external fun normalThread()

    external fun mutexThread()

    external fun callbackFromC()
}