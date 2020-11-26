package com.tck.jni.thread

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.TextView
import com.tck.jni.thread.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var threadTrain: ThreadTrain
    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        threadTrain = ThreadTrain()

        threadTrain.setOnErrorListener(object : OnErrorListener {
            override fun onError(code: Int, msg: String) {
                Log.d("tck6666", "code:$code,msg:$msg")
            }
        })

        binding.btnNormalThread.setOnClickListener {
            createNormalThread()

        }

        binding.btnMutexThread.setOnClickListener {
            createMutexThread()
        }

        binding.btnCCallJava.setOnClickListener {
            callBackFromC()
        }
    }


    private fun createNormalThread() {
        threadTrain.normalThread()
    }

    private fun createMutexThread() {
        threadTrain.mutexThread()
    }


    private fun callBackFromC() {
        threadTrain.callbackFromC()
    }


}