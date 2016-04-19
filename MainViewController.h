//
//  MainViewController.h
//  BLE_iPad
//
//  Created by Aurél on 10.06.14.
//  Copyright (c) 2014 Aurelien Merz. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import "bitpacker.h"
#import "TransferService.h"
#import "timerConstants.h"
#import "samplingPeriods.h"

#define NB_SAMPLES 1000
#define SAMPLING_PERIOD 0.000250
#define N_AVG 100

/*******************************************
 *
 ******************************************/

#define E2_UPPER_LIMIT 84
#define E2_LOWER_LIMIT 80

#define A2_UPPER_LIMIT 112
#define A2_LOWER_LIMIT 108

#define D3_UPPER_LIMIT 148
#define D3_LOWER_LIMIT 144

#define G3_UPPER_LIMIT 198
#define G3_LOWER_LIMIT 190

#define B3_UPPER_LIMIT 248
#define B3_LOWER_LIMIT 245

#define E4_UPPER_LIMIT 331
#define E4_LOWER_LIMIT 327

/*******************************************
 *
 ******************************************/

#define DELTA_E2 12
#define DELTA_A2 15
#define DELTA_D3 15
#define DELTA_G3 9
#define DELTA_E4 11


/*******************************************
 *
 ******************************************/

#define E2_H_LIMIT 96
#define E2_L_LIMIT 92

#define A2_H_LIMIT 127
#define A2_L_LIMIT 120

#define D3_H_LIMIT 163
#define D3_L_LIMIT 160


#define G3_H_LIMIT 207
#define G3_L_LIMIT 202

#define E4_H_LIMIT 343
#define E4_L_LIMIT 340

/*******************************************
 *  SLIDERS MAXIMA
 ******************************************/

#define E2_SLIDER_UPPER_LIMIT 92
#define E2_SLIDER_LOWER_LIMIT 72

#define A2_SLIDER_UPPER_LIMIT 100
#define A2_SLIDER_LOWER_LIMIT 120

#define D3_SLIDER_UPPER_LIMIT 156
#define D3_SLIDER_LOWER_LIMIT 136

#define G3_SLIDER_UPPER_LIMIT 206
#define G3_SLIDER_LOWER_LIMIT 186

#define B3_SLIDER_UPPER_LIMIT 256
#define B3_SLIDER_LOWER_LIMIT 236

#define E4_SLIDER_UPPER_LIMIT 339
#define E4_SLIDER_LOWER_LIMIT 319

@interface MainViewController : UIViewController <CBCentralManagerDelegate, CBPeripheralDelegate>
{
    NSUUID *serviceUUID;
    NSUUID *charUUID;
    
}

@property (nonatomic, strong) NSString   *connected;
@property (nonatomic, strong) NSString   *dataADC;
@property (nonatomic, strong) NSString   *manufacturer;
@property (nonatomic, strong) NSString   *peripheralData;

// Instance method to get the heart rate BPM information
- (void) getADCData:(CBCharacteristic *)characteristic error:(NSError *)error;

// Instance methods to grab device Manufacturer Name, Body Location
- (void) getManufacturerName:(CBCharacteristic *)characteristic;

@end
