/*
 * myusb.c
 *
 *  Created on: 2018年4月24日
 *      Author: feichao
 */
#include "myusb.h"


static libusb_device **devs = NULL; //pointer to pointer of device, used to retrieve a list of devices
static libusb_context *ctx = NULL; //a libusb session
static libusb_device **nano_devs = NULL; // 所有连接的nano设备
static int dev_cnt = 0; // 连接的nano设备数量

//void printdev(libusb_device *dev) {
//	struct libusb_device_descriptor desc;
//    int r = libusb_get_device_descriptor(dev, &desc);
//    if (r < 0) {
//    	LOGD("failed to get device descriptor\n");
//        return;
//    }
//
//    LOGD("Number of possible configurations: %d  ", (int)desc.bNumConfigurations);
//    LOGD("Device Class: %d  ", (int)desc.bDeviceClass);
//    LOGD("VendorID: %d  ", desc.idVendor);
//    LOGD("ProductID: %d\n", desc.idProduct);
//    struct libusb_config_descriptor *config;
//    libusb_get_config_descriptor(dev, 0, &config);
//    LOGD("Interfaces: %d ||| ", (int)config->bNumInterfaces);
//    const struct libusb_interface *inter;
//    const struct libusb_interface_descriptor *interdesc;
//    const struct libusb_endpoint_descriptor *epdesc;
//
//    for(int i=0; i<(int)config->bNumInterfaces; i++) {
//        inter = &config->interface[i];
//        LOGD("Number of alternate settings: %d | ", inter->num_altsetting);
//        for(int j=0; j<inter->num_altsetting; j++) {
//            interdesc = &inter->altsetting[j];
//            LOGD("Interface Number: %d | ", (int)interdesc->bInterfaceNumber);
//            LOGD("Number of endpoints: %d | ", (int)interdesc->bNumEndpoints);
//
//            for(int k=0; k<(int)interdesc->bNumEndpoints; k++) {
//                epdesc = &interdesc->endpoint[k];
//                LOGD("Descriptor Type: %d | ", (int)epdesc->bDescriptorType);
//                LOGD("EP Address: %d | ", (int)epdesc->bEndpointAddress);
//            }
//        }
//    }
//    LOGD("\n\n\n\n");
//    libusb_free_config_descriptor(config);
//}






/**
 * Connect to physical device(sensor).
 */
extern int devConnect()
{


	int r; //for return values
	ssize_t cnt; //holding number of devices in list
	r = libusb_init(&ctx); //initialize a library session
	if(r < 0) {
		LOGD("Init Error \n"); //there was an error
		return 1;
	}
	libusb_set_debug(ctx, 3); //set verbosity level to 3, as suggested in the documentation
	cnt = libusb_get_device_list(ctx, &devs); //get the list of devices

	if(cnt < 0) {
		LOGD("Get Device Error\n"); //there was an error
	}
	LOGD(" Devices in list.\n"); //print total number of usb device
	ssize_t i; //for iterating through the list

	// 计数重置
	dev_cnt = 0;

	// 使用 vendorid 选取正确的设备
	for(i = 0; i < cnt; i++) {
		// 获取usb设备的
		struct libusb_device_descriptor desc;
		int r = libusb_get_device_descriptor(devs[i], &desc);
		if (r < 0) {
			LOGD("failed to get device descriptor\n");
			continue;
		}

		LOGD("VendorID: %d  ", desc.idVendor);

		if(desc.idVendor == 1155) {
			dev_cnt++;
		}

		// TODO 内存分配问题
		nano_devs = (libusb_device **)malloc(sizeof(libusb_device) * dev_cnt);

	}



	return 0;
}

/**
 * Disconnect physical device(sensor).
 */
extern int devDisconnect ()
{
	if(NULL != devs)
	{
		libusb_free_device_list(devs, 1); //free the list, unref the devices in it
	}

	if(NULL != ctx)
	{
		libusb_exit(ctx); //close the session
	}

	return 0;
}

/**
 * Get sensor ID list which are connected to system.
 */
extern int devGetSensorList (char **sensor_list_out)
{
	int ret = 0;
	int i = 0;
	// 获取所有id
	for(i = 0; i < dev_cnt; i++) {
		char *sensorId = NULL;
		ret = devGetSensorID(sensorId);
		if(ret < 0) {
			LOGD("获取sensorID 异常");
		}
		// 将id 拼接起来
		sensor_list_out += sensorId;
	}

	return ret;
}

/**
 * Activate a specific sensor by index
 */
extern int devActivateSensorWithIndex (int sensor_index)
{
	return 0;
}

/**
 * Activate a specific sensor by ID
 */
extern int devActivateSensorWithID (const char *sensor_id_str)
{
	return 0;
}

/**
 * Get devices count.
 */
extern int devGetTotalSensors ()
{
	return dev_cnt;
}

/**
 * Get sensor ID of physical device(sensor).
 */
extern int devGetSensorID (char *sensor_id)
{

	// 发送指令 获取sensorID



	return 0;
}

/**
 * Get shutter speed.
 */
extern int devGetShutterSpeed ()
{
	// 发送指令获取快门速度

	return 0;
}

/**
 * Get shutter speed limits.
 */
extern int devGetShutterSpeedLimits (int *min_limit, int *max_limit)
{
	// 获取快门速度的范围


	return 0;
}

/**
 * Convert shutter speed to exposure time (unit: ms).
 */
extern int devShutterSpeedToExposureTime (int master_clock, int shutter_speed, double * exposure_time_val)
{
	return 0;
}

/**
 * Convert exposure time (ms) to shutter speed.
 */
extern int devExposureTimeToShutterSpeed (int master_clock, double exposure_time_val, int *shutter_speed)
{
	return 0;
}

/**
 * Change current shutter speed of a device(sensor).
 */
extern int devSetShutterSpeed (int shutter)
{
	return 0;
}

/**
 * Get optimal shutter speed by AE.
 */
extern int devGetOptimalShutterSpeed ()
{

	// ????????

	return 0;
}

/**
 * Get raw filter data from physical device(sensor).
 */
extern int devGetFilterData (double *output, int number_of_averages)
{
	return 0;
}

/**
 * Get total number of nano-filters.
 */
extern int devGetNumOfFilters (int *num_filter)
{
	return 0;
}

/**
 * Set sensor registers.
 */
extern int devSetSensorParameters (int _adc_gain, int _adc_range)
{
	return 0;
}

/**
 * Get settings of sensor registers.
 */
extern int devGetSensorParameters (int *_adc_gain, int *_adc_range)
{
	return 0;
}





