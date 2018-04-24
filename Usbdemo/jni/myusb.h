
#include <stdio.h>
#include "libusb.h"
#include "log.h"


/**
 * Connect to physical device(sensor).
 */
extern int devConnect(void);

/**
 * Disconnect physical device(sensor).
 */
extern int devDisconnect (void);

/**
 * Get sensor ID list which are connected to system.
 */
extern int devGetSensorList (char **);

/**
 * Activate a specific sensor by index
 */
extern int devActivateSensorWithIndex (int);

/**
 * Activate a specific sensor by ID
 */
extern int devActivateSensorWithID (const char *);

/**
 * Get devices count.
 */
extern int devGetTotalSensors (void);

/**
 * Get sensor ID of physical device(sensor).
 */
extern int devGetSensorID (char *);

/**
 * Get shutter speed.
 */
extern int devGetShutterSpeed (void);

/**
 * Get shutter speed limits.
 */
extern int devGetShutterSpeedLimits (int *, int *);

/**
 * Convert shutter speed to exposure time (unit: ms).
 */
extern int devShutterSpeedToExposureTime (int, int, double *);

/**
 * Convert exposure time (ms) to shutter speed.
 */
extern int devExposureTimeToShutterSpeed (int, double, int *);

/**
 * Change current shutter speed of a device(sensor).
 */
extern int devSetShutterSpeed (int);

/**
 * Get optimal shutter speed by AE.
 */
extern int devGetOptimalShutterSpeed (void);

/**
 * Get raw filter data from physical device(sensor).
 */
extern int devGetFilterData (double *, int);

/**
 * Get total number of nano-filters.
 */
extern int devGetNumOfFilters (int *);

/**
 * Set sensor registers.
 */
extern int devSetSensorParameters (int, int);

/**
 * Get settings of sensor registers.
 */
extern int devGetSensorParameters (int *, int *);









