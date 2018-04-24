#include <jni.h>

#include <stdio.h>

#include "myusb.h"
#include "log.h"




extern "C" {

JNIEXPORT jstring JNICALL
Java_cn_jungu_soft_usbdemo_USBTools_sayHello(JNIEnv *env, jclass)
{
	LOGD("Hello JNI!");
    return env->NewStringUTF("Hello JNI!");
}



JNIEXPORT jint JNICALL
Java_cn_jungu_soft_usbdemo_USBTools_connectDevice(JNIEnv *env, jclass)
{

	int var = devConnect();

	return var;
}










}
