//
//  TransferService.h
//  BTLE Tuner
//
//  Created by Aurél on 06.04.14.
//  Copyright (c) 2014 Aurelien Merz. All rights reserved.
//

#ifndef BTLE_Tuner_TransferService_h
#define BTLE_Tuner_TransferService_h

/*
 
 File: TransferService.h
 
 Abstract: The UUIDs generated to identify the Service and Characteristics
 used in the App.
 
 Version: 1.0



#ifndef LE_Transfer_TransferService_h
#define LE_Transfer_TransferService_h*/

#define TRANSFER_SERVICE_UUID           @"00001823-1212-EFDE-1823-785FEABCD123"
#define TRANSFER_CHARACTERISTIC_UUID    @"00001824-1212-EFDE-1823-785FEABCD123"

/** @defgroup UUID_SERVICES Service UUID definitions
 * @{ */
#define BLE_UUID_ALERT_NOTIFICATION_SERVICE                      0x1811     /**< Alert Notification service UUID. */
#define BLE_UUID_BATTERY_SERVICE                                 @"180F"     /**< Battery service UUID. */
#define BLE_UUID_BLOOD_PRESSURE_SERVICE                          0x1810     /**< Blood Pressure service UUID. */
#define BLE_UUID_CURRENT_TIME_SERVICE                            0x1805     /**< Current Time service UUID. */
#define BLE_UUID_CYCLING_SPEED_AND_CADENCE                       0x1816     /**< Cycling Speed and Cadence service UUID. */
#define BLE_UUID_DEVICE_INFORMATION_SERVICE                      0x180A     /**< Device Information service UUID. */
#define BLE_UUID_GLUCOSE_SERVICE                                 0x1808     /**< Glucose service UUID. */
#define BLE_UUID_HEALTH_THERMOMETER_SERVICE                      0x1809     /**< Health Thermometer service UUID. */
#define BLE_UUID_HEART_RATE_SERVICE                              0x180D     /**< Heart Rate service UUID. */
#define BLE_UUID_HUMAN_INTERFACE_DEVICE_SERVICE                  0x1812     /**< Human Interface Device service UUID. */
#define BLE_UUID_IMMEDIATE_ALERT_SERVICE                         0x1802     /**< Immediate Alert service UUID. */
#define BLE_UUID_LINK_LOSS_SERVICE                               0x1803     /**< Link Loss service UUID. */
#define BLE_UUID_NEXT_DST_CHANGE_SERVICE                         0x1807     /**< Next Dst Change service UUID. */
#define BLE_UUID_PHONE_ALERT_STATUS_SERVICE                      0x180E     /**< Phone Alert Status service UUID. */
#define BLE_UUID_REFERENCE_TIME_UPDATE_SERVICE                   0x1806     /**< Reference Time Update service UUID. */
#define BLE_UUID_RUNNING_SPEED_AND_CADENCE                       0x1814     /**< Running Speed and Cadence service UUID. */
#define BLE_UUID_SCAN_PARAMETERS_SERVICE                         0x1813     /**< Scan Parameters service UUID. */
#define BLE_UUID_TX_POWER_SERVICE                                0x1804     /**< TX Power service UUID. */

// My custom UUID
#define BLE_UUID_TRANSFER_SERVICE                                0x1825     /**<ADC Transfer service UUID*/
/** @} */

/** @defgroup UUID_CHARACTERISTICS Characteristic UUID definitions
 * @{ */
#define BLE_UUID_BATTERY_LEVEL_STATE_CHAR                        @"2A1B"     /**< Battery Level State characteristic UUID. */
#define BLE_UUID_BATTERY_POWER_STATE_CHAR                        0x2A1A     /**< Battery Power State characteristic UUID. */
#define BLE_UUID_REMOVABLE_CHAR                                  0x2A3A     /**< Removable characteristic UUID. */
#define BLE_UUID_SERVICE_REQUIRED_CHAR                           0x2A3B     /**< Service Required characteristic UUID. */
#define BLE_UUID_ALERT_CATEGORY_ID_CHAR                          0x2A43     /**< Alert Category Id characteristic UUID. */
#define BLE_UUID_ALERT_CATEGORY_ID_BIT_MASK_CHAR                 0x2A42     /**< Alert Category Id Bit Mask characteristic UUID. */
#define BLE_UUID_ALERT_LEVEL_CHAR                                0x2A06     /**< Alert Level characteristic UUID. */
#define BLE_UUID_ALERT_NOTIFICATION_CONTROL_POINT_CHAR           0x2A44     /**< Alert Notification Control Point characteristic UUID. */
#define BLE_UUID_ALERT_STATUS_CHAR                               0x2A3F     /**< Alert Status characteristic UUID. */
#define BLE_UUID_BATTERY_LEVEL_CHAR                              0x2A19     /**< Battery Level characteristic UUID. */
#define BLE_UUID_BLOOD_PRESSURE_FEATURE_CHAR                     0x2A49     /**< Blood Pressure Feature characteristic UUID. */
#define BLE_UUID_BLOOD_PRESSURE_MEASUREMENT_CHAR                 0x2A35     /**< Blood Pressure Measurement characteristic UUID. */
#define BLE_UUID_BODY_SENSOR_LOCATION_CHAR                       0x2A38     /**< Body Sensor Location characteristic UUID. */
#define BLE_UUID_BOOT_KEYBOARD_INPUT_REPORT_CHAR                 0x2A22     /**< Boot Keyboard Input Report characteristic UUID. */
#define BLE_UUID_BOOT_KEYBOARD_OUTPUT_REPORT_CHAR                0x2A32     /**< Boot Keyboard Output Report characteristic UUID. */
#define BLE_UUID_BOOT_MOUSE_INPUT_REPORT_CHAR                    0x2A33     /**< Boot Mouse Input Report characteristic UUID. */
#define BLE_UUID_CURRENT_TIME_CHAR                               0x2A2B     /**< Current Time characteristic UUID. */
#define BLE_UUID_DATE_TIME_CHAR                                  0x2A08     /**< Date Time characteristic UUID. */
#define BLE_UUID_DAY_DATE_TIME_CHAR                              0x2A0A     /**< Day Date Time characteristic UUID. */
#define BLE_UUID_DAY_OF_WEEK_CHAR                                0x2A09     /**< Day Of Week characteristic UUID. */
#define BLE_UUID_DST_OFFSET_CHAR                                 0x2A0D     /**< Dst Offset characteristic UUID. */
#define BLE_UUID_EXACT_TIME_256_CHAR                             0x2A0C     /**< Exact Time 256 characteristic UUID. */
#define BLE_UUID_FIRMWARE_REVISION_STRING_CHAR                   0x2A26     /**< Firmware Revision String characteristic UUID. */
#define BLE_UUID_GLUCOSE_FEATURE_CHAR                            0x2A51     /**< Glucose Feature characteristic UUID. */
#define BLE_UUID_GLUCOSE_MEASUREMENT_CHAR                        0x2A18     /**< Glucose Measurement characteristic UUID. */
#define BLE_UUID_GLUCOSE_MEASUREMENT_CONTEXT_CHAR                0x2A34     /**< Glucose Measurement Context characteristic UUID. */
#define BLE_UUID_HARDWARE_REVISION_STRING_CHAR                   0x2A27     /**< Hardware Revision String characteristic UUID. */
#define BLE_UUID_HEART_RATE_CONTROL_POINT_CHAR                   0x2A39     /**< Heart Rate Control Point characteristic UUID. */
#define BLE_UUID_HEART_RATE_MEASUREMENT_CHAR                     0x2A37     /**< Heart Rate Measurement characteristic UUID. */
#define BLE_UUID_HID_CONTROL_POINT_CHAR                          0x2A4C     /**< Hid Control Point characteristic UUID. */
#define BLE_UUID_HID_INFORMATION_CHAR                            0x2A4A     /**< Hid Information characteristic UUID. */
#define BLE_UUID_IEEE_REGULATORY_CERTIFICATION_DATA_LIST_CHAR    0x2A2A     /**< IEEE Regulatory Certification Data List characteristic UUID. */
#define BLE_UUID_INTERMEDIATE_CUFF_PRESSURE_CHAR                 0x2A36     /**< Intermediate Cuff Pressure characteristic UUID. */
#define BLE_UUID_INTERMEDIATE_TEMPERATURE_CHAR                   0x2A1E     /**< Intermediate Temperature characteristic UUID. */
#define BLE_UUID_LOCAL_TIME_INFORMATION_CHAR                     0x2A0F     /**< Local Time Information characteristic UUID. */
#define BLE_UUID_MANUFACTURER_NAME_STRING_CHAR                   0x2A29     /**< Manufacturer Name String characteristic UUID. */
#define BLE_UUID_MEASUREMENT_INTERVAL_CHAR                       0x2A21     /**< Measurement Interval characteristic UUID. */
#define BLE_UUID_MODEL_NUMBER_STRING_CHAR                        0x2A24     /**< Model Number String characteristic UUID. */
#define BLE_UUID_UNREAD_ALERT_CHAR                               0x2A45     /**< Unread Alert characteristic UUID. */
#define BLE_UUID_NEW_ALERT_CHAR                                  0x2A46     /**< New Alert characteristic UUID. */
#define BLE_UUID_PNP_ID_CHAR                                     0x2A50     /**< PNP Id characteristic UUID. */
#define BLE_UUID_PROTOCOL_MODE_CHAR                              0x2A4E     /**< Protocol Mode characteristic UUID. */
#define BLE_UUID_RECORD_ACCESS_CONTROL_POINT_CHAR                0x2A52     /**< Record Access Control Point characteristic UUID. */
#define BLE_UUID_REFERENCE_TIME_INFORMATION_CHAR                 0x2A14     /**< Reference Time Information characteristic UUID. */
#define BLE_UUID_REPORT_CHAR                                     0x2A4D     /**< Report characteristic UUID. */
#define BLE_UUID_REPORT_MAP_CHAR                                 0x2A4B     /**< Report Map characteristic UUID. */
#define BLE_UUID_RINGER_CONTROL_POINT_CHAR                       0x2A40     /**< Ringer Control Point characteristic UUID. */
#define BLE_UUID_RINGER_SETTING_CHAR                             0x2A41     /**< Ringer Setting characteristic UUID. */
#define BLE_UUID_SCAN_INTERVAL_WINDOW_CHAR                       0x2A4F     /**< Scan Interval Window characteristic UUID. */
#define BLE_UUID_SCAN_REFRESH_CHAR                               0x2A31     /**< Scan Refresh characteristic UUID. */
#define BLE_UUID_SERIAL_NUMBER_STRING_CHAR                       0x2A25     /**< Serial Number String characteristic UUID. */
#define BLE_UUID_SOFTWARE_REVISION_STRING_CHAR                   0x2A28     /**< Software Revision String characteristic UUID. */
#define BLE_UUID_SUPPORTED_NEW_ALERT_CATEGORY_CHAR               0x2A47     /**< Supported New Alert Category characteristic UUID. */
#define BLE_UUID_SUPPORTED_UNREAD_ALERT_CATEGORY_CHAR            0x2A48     /**< Supported Unread Alert Category characteristic UUID. */
#define BLE_UUID_SYSTEM_ID_CHAR                                  0x2A23     /**< System Id characteristic UUID. */
#define BLE_UUID_TEMPERATURE_MEASUREMENT_CHAR                    0x2A1C     /**< Temperature Measurement characteristic UUID. */
#define BLE_UUID_TEMPERATURE_TYPE_CHAR                           0x2A1D     /**< Temperature Type characteristic UUID. */
#define BLE_UUID_TIME_ACCURACY_CHAR                              0x2A12     /**< Time Accuracy characteristic UUID. */
#define BLE_UUID_TIME_SOURCE_CHAR                                0x2A13     /**< Time Source characteristic UUID. */
#define BLE_UUID_TIME_UPDATE_CONTROL_POINT_CHAR                  0x2A16     /**< Time Update Control Point characteristic UUID. */
#define BLE_UUID_TIME_UPDATE_STATE_CHAR                          0x2A17     /**< Time Update State characteristic UUID. */
#define BLE_UUID_TIME_WITH_DST_CHAR                              0x2A11     /**< Time With Dst characteristic UUID. */
#define BLE_UUID_TIME_ZONE_CHAR                                  0x2A0E     /**< Time Zone characteristic UUID. */
#define BLE_UUID_TX_POWER_LEVEL_CHAR                             0x2A07     /**< TX Power Level characteristic UUID. */
#define BLE_UUID_CSC_FEATURE_CHAR                                0x2A5C     /**< Cycling Speed and Cadence Feature characteristic UUID. */
#define BLE_UUID_CSC_MEASUREMENT_CHAR                            0x2A5B     /**< Cycling Speed and Cadence Measurement characteristic UUID. */
#define BLE_UUID_RSC_FEATURE_CHAR                                0x2A54     /**< Running Speed and Cadence Feature characteristic UUID. */
#define BLE_UUID_RSC_MEASUREMENT_CHAR                            0x2A53     /**< Running Speed and Cadence Measurement characteristic UUID. */
/** @} */

/** @defgroup UUID_CHARACTERISTICS Characteristic UUID definitions
 * @{ */
#define BLE_UUID_EXTERNAL_REPORT_REF_DESCR                       0x2907     /**< External Report Reference descriptor UUID. */
#define BLE_UUID_REPORT_REF_DESCR                                0x2908     /**< Report Reference descriptor UUID. */
/** @} */

/** @defgroup CCCD_BITS CCCD bit definitions
 * @{ */
#define BLE_CCCD_NOTIFY_BIT_MASK                                 0x0001     /**< Enable Notification bit. */
#define BLE_CCCD_INDICATE_BIT_MASK                               0x0002     /**< Enable Indication bit. */
/** @} */

/** @defgroup ALERT_LEVEL_VALUES Definitions for the Alert Level characteristic values
 * @{ */
#define BLE_CHAR_ALERT_LEVEL_NO_ALERT                            0x00       /**< No Alert. */
#define BLE_CHAR_ALERT_LEVEL_MILD_ALERT                          0x01       /**< Mild Alert. */
#define BLE_CHAR_ALERT_LEVEL_HIGH_ALERT                          0x02       /**< High Alert. */
/** @} */

#define BLE_SRV_ENCODED_REPORT_REF_LEN                           2          /**< The length of an encoded Report Reference Descriptor. */
#define BLE_CCCD_VALUE_LEN                                       2          /**< The length of a CCCD value. */

#endif

