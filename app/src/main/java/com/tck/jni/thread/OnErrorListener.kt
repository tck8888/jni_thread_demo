package com.tck.jni.thread

/**
 *<p>description:</p>
 *<p>created on: 2020/11/26 15:59</p>
 * @author tck
 * @version
 *
 */
interface OnErrorListener {

    fun onError(code: Int, msg: String)
}