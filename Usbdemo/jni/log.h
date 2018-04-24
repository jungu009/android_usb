/*
 * log.h
 *
 *  Created on: 2018年4月24日
 *      Author: XT-003
 */

#ifndef LOG_H_
#define LOG_H_

#include  <android/log.h>
#define TAG    "DroidMage" // 这个是自定义的LOG的标识
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__) // 定义LOGD类型


#endif /* LOG_H_ */
