//
//  MainViewController.m
//  BLE_iPad
//
//  Created by Aurél on 10.06.14.
//  Copyright (c) 2014 Aurelien Merz. All rights reserved.
//

#import "MainViewController.h"

#define UIColorFromRGB(rgbValue) [UIColor colorWithRed:((float)((rgbValue & 0xFF0000) >> 16))/255.0 green:((float)((rgbValue & 0xFF00) >> 8))/255.0 blue:((float)(rgbValue & 0xFF))/255.0 alpha:1.0]

@interface MainViewController ()

@property (strong, nonatomic) CBCentralManager *centralManager;
@property (strong, nonatomic) CBPeripheral *discoveredPeripheral;
@property (strong, nonatomic) NSMutableData *data;
@property (strong, nonatomic) CBCharacteristic *aChar;
@property (strong, nonatomic) CBCharacteristic *batteryChar;

@property(strong, nonatomic) NSData  *charVal;

@property(strong, nonatomic) NSMutableArray *samples;

@property (strong, nonatomic) IBOutlet UILabel *scanningState;
@property (strong, nonatomic) IBOutlet UIActivityIndicatorView *connectionActivity;
@property (strong, nonatomic) IBOutlet UILabel *foundPeripheral;
@property (strong, nonatomic) IBOutlet UILabel *connectionState;
@property (strong, nonatomic) IBOutlet UIActivityIndicatorView *scanningActivity;
@property (strong, nonatomic) IBOutlet UISwitch *connection_sw;
@property (strong, nonatomic) IBOutlet UILabel *measuredVal;
@property (strong, nonatomic) IBOutlet UILabel *amplitudeVal;
@property (strong, nonatomic) IBOutlet UILabel *batteryLevel;

@property (strong, nonatomic) IBOutlet UIBarButtonItem *sideBarButton;
@property (strong, nonatomic) IBOutlet UISlider *tuningValueSlider;

@property (strong, nonatomic) IBOutlet UILabel *note;
@property (strong, nonatomic) IBOutlet UISlider *sliderTone;
@property (strong, nonatomic) IBOutlet UILabel *sliderValue;

@end

@implementation MainViewController

NSData *adcValue;
NSData *val;
NSTimer *timer;
UIAlertView *scanningAlert;

NSMutableIndexSet *indexes;

uint8_t buffer[8];
float freq_avg = 0.0f;
Float32 count_avg = 0;

Float32 frequency = 0.0f;

uint16_t receivedFreq;

int n_avg = 0;
float actual_avg = 0;
uint16_t n = 0;


int nb_samples = 1000;
uint32_t pass;
uint32_t count;
float t_total = 0.0f;

typedef enum
{            E2 ,
             A2 ,
             D3 ,
             G3 ,
             B3 ,
             E4,
             NO_NOTE
}NOTE;

NOTE actualNote;

uint16_t periodCount = 0;

#pragma mark - View Lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];

    
    [self preferredStatusBarStyle];
    self.data = nil;
    
    self.view.backgroundColor = UIColorFromRGB(0x22313F);
    [self.sliderTone setThumbTintColor:UIColorFromRGB(0xc0392b)];
    
    [self setSliderMaximas:100.0:0];
    self.sliderTone.value = 50.0;
    
    // Start up the CBCentralManager
    
    _centralManager = [[CBCentralManager alloc] initWithDelegate:self queue:nil];
    
    //And somewhere to store the incoming data
    
    _data = [[NSMutableData alloc] init];
    _aChar =[[CBCharacteristic alloc] init];
    
    [_sliderTone addTarget:self action:@selector(sliderValueChanged:) forControlEvents:UIControlEventValueChanged];
    
    actualNote = NO_NOTE;
    
    
    _charVal = [[NSData alloc]init];
    
    t_total = nb_samples * t_4kHz;
    
}

- (IBAction)sliderValueChanged:(UISlider *)sender {
    [self.sliderValue setText:[NSString stringWithFormat:@"%f",[self.sliderTone value]]];
}

-(void)viewWillDisappear:(BOOL)animated
{
    // Don't keep it going while we're not showing
    //[self.centralManager stopScan];
    //NSLog(@"Scanning stopped");
    
    [super viewWillDisappear:animated];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
    
    
}

-(UIStatusBarStyle)preferredStatusBarStyle
{
    return UIStatusBarStyleLightContent;
}

#pragma mark - Central Methods

/*********************************************************************************************************************
 *                                                                                                                   *
 *    SCANNING FOR PERIPHERALS FUNCTION
 *
 *    Scan for peripherals - specifically for our service's 128bit CBUUID                                            *
 *********************************************************************************************************************/

- (void)scan
{
    [self.scanningActivity startAnimating];
    
    [self.centralManager scanForPeripheralsWithServices:@[[CBUUID UUIDWithString:TRANSFER_SERVICE_UUID]]
                                                options:@{ CBCentralManagerScanOptionAllowDuplicatesKey : @YES }];
    //    [self.centralManager scanForPeripheralsWithServices:nil
    //                                                options:@{ CBCentralManagerScanOptionAllowDuplicatesKey : @YES }];
    //
    
    [self.scanningState setText:@"Scanning for peripherals..."];
    
    
    [self.connectionActivity startAnimating];
    NSLog(@"Scanning started");
}
/*********************************************************************************************************************
 *                                                                                                                   *
 *    CENTRAL MANAGER DID UPDATE STATE                                                                               *
 *                                                                                                                   *
 *********************************************************************************************************************/

-(void)centralManagerDidUpdateState:(CBCentralManager *)central
{
    
    
    // You should test all scenarios
    if ((central.state == CBCentralManagerStatePoweredOn)) {
        // Scan for devices, nil used for any devices
        NSLog(@"CoreBluetooth BLE hardware is powered on and ready");
        
        [self scan];
    }
    
    if(central.state == CBCentralManagerStateUnknown){
        NSLog(@"CoreBluetooth BLE state is unknown");
        return;
    }
    
    if(central.state == CBCentralManagerStateResetting){
        NSLog(@"Reset State");
        return;
    }
    
    if(central.state == CBCentralManagerStateUnsupported){
        NSLog(@"CoreBluetooth BLE hardware is unsupported on this platform");
        return;
    }
    
    if(central.state == CBCentralManagerStateUnauthorized)
    {
        NSLog(@"CoreBluetooth BLE state is unauthorized");
        return;
    }
    
    if(central.state == CBCentralManagerStatePoweredOff)
    {
        NSLog(@"CoreBluetooth BLE hardware is powered off");
        return;
    }
    
}
/*********************************************************************************************************************
 *  This callback comes whenever a peripheral that is advertising the TRANSFER_SERVICE_UUID is discovered.
 *  We check the RSSI, to make sure it's close enough that we're interested in it, and if it is, we start the connection
 *  process.
 *  This is called with the CBPeripheral class as its main input parameter.
 *  This contains most of the information there is to know about a BLE peripheral.
 *********************************************************************************************************************/


-(void)centralManager:(CBCentralManager *)central didDiscoverPeripheral:(CBPeripheral *)peripheral advertisementData:(NSDictionary *)advertisementData RSSI:(NSNumber *)RSSI
{
    // Reject any where the value is above reasonable range
    /* if(RSSI.integerValue > -15)
     {
     return;
     }
     
     // Reject if the signal strenght is too low to be close enough (Close is around -22dB)
     if(RSSI.integerValue < -35)
     {
     return;
     }*/
    
    //[self.connectionActivity stopAnimating];
    
    [scanningAlert dismissWithClickedButtonIndex:0 animated:YES];
    
    NSLog(@"Discovered %@ at %@", peripheral.name, RSSI);
    [self.scanningState setText:@"Discovered peripheral"];
    
    // Ok, it's in range - have we already seen it?
    if(self.discoveredPeripheral != peripheral)
    {
        // Save a local copy of the peripheral, so Corebluetooth doesn't get rid of it
        self.discoveredPeripheral = peripheral;
        
        // And connect
        NSLog(@"Connecting to peripheral %@", peripheral);
        [self.scanningState setText:@"Connecting to peripheral"];
        
        [self.centralManager connectPeripheral:peripheral options:nil];
    }
}


/** If the connection fails for whatever reason, we need to deal with it
 */

-(void)centralManager:(CBCentralManager *)central didFailToConnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error
{
    NSLog(@"Failed to connect to %@. (%@)", peripheral, [error localizedDescription]);
    [self.scanningState setText:@"Failed to connect to peripheral"];
    
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Connection failed!" message:@"Failed to connect to peripheral" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil, nil];
    
    [alert show];
    //[self.scanningActivity stopAnimating];
    [self cleanup];
}


/** We've connected to the peripheral, now we need to discover the services and characteristics to find the 'transfer2
 characteristic.
 // method called whenever you have successfully connected to the BLE peripheral
 */

-(void)centralManager:(CBCentralManager *)central didConnectPeripheral:(CBPeripheral *)peripheral
{
    NSLog(@"Peripheral connected");
    

    [self.scanningActivity stopAnimating];
    
    [self.connectionState setText:@"Connected"];
    
    self.connected = [NSString stringWithFormat:@"Connected: %@", peripheral.state == CBPeripheralStateConnected ? @"YES" : @"NO"];
    
    NSLog(@"%@", self.connected);
    
    // Stop scanning
    [self.centralManager stopScan];
    [self.scanningState setText:@"Scanning stopped!"];
    NSLog(@"Scanning stopped");
    
    // Clear the data that we may already have
    [self.data setLength:0];
    
    //Make sure we get the discovery call back
    peripheral.delegate = self;
    
    //Search only for services that match our UUID
    [peripheral discoverServices:@[[CBUUID UUIDWithString:TRANSFER_SERVICE_UUID]]];//,[CBUUID UUIDWithString:BLE_UUID_BATTERY_SERVICE]]];
    //[peripheral discoverServices:@[[CBUUID UUIDWithString:BLE_UUID_BATTERY_SERVICE]]];
}


/** The service was discovered
 */
-(void)peripheral:(CBPeripheral *)peripheral didDiscoverServices:(NSError *)error
{
    if (error) {
        NSLog(@"Error discovering services: %@",[error localizedDescription]);
        [self cleanup];
        return;
    }
    
    //Discover the characteristic we want...
    // Loop through the newly filled peripheral.services array, just in case there's more than one.
    
    for (CBService *service in peripheral.services) {
        NSLog(@"Discovered service: %@", service.UUID);
        
        [peripheral discoverCharacteristics:@[[CBUUID UUIDWithString:TRANSFER_CHARACTERISTIC_UUID]]
                                 forService:service];
        
        //        [peripheral discoverCharacteristics:@[[CBUUID UUIDWithString:BLE_UUID_BATTERY_LEVEL_STATE_CHAR]]
        //                                 forService:service];
        
    }
}


/** The tranfer characteristic was discovered
 *  Once this found, we want to subscribe to it, which lets the peripheral know we want the data it contains
 */

-(void)peripheral:(CBPeripheral *)peripheral didDiscoverCharacteristicsForService:(CBService *)service error:(NSError *)error
{
    if(error){
        NSLog(@"Error discovering characteristics: %@", [error localizedDescription]);
        [self cleanup];
        return;
    }
    
    // Again we loop through the array, just in case
    for(CBCharacteristic *characteristic in service.characteristics)
    {
        // And check if it's the right one
        if([characteristic.UUID isEqual:[CBUUID UUIDWithString:TRANSFER_CHARACTERISTIC_UUID]])
        {
            //If it is, subscribe to it
            self.aChar = characteristic;
            [peripheral setNotifyValue:YES forCharacteristic:characteristic];
            
            
            NSLog(@"Subscribed to characteristic");
            //NSLog(@"Characteristic value: %@",[characteristic value]);
        }
    }
    
    // Once this is complete, we just need to wait for the data to come in.
}

// Invoked when you retrieve a specified characteristic's value, or when the peripheral device notifies your app that the characteristic's value has changed.
- (void)peripheral:(CBPeripheral *)peripheral didUpdateValueForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error
{
    if (error) {
        NSLog(@"Error changing notification state: %@", error.localizedDescription);
    }
    //uint16_t freq = 0;
    //NSLog(@"Char Value: %@",[characteristic value]);
    
    
    
    [self extractByteFromNSData:[characteristic value]];
  
    
    
   
   
    
    t_total = count / 4500.0;
    frequency = pass / t_total;
  
    n_avg++;
    
   
    freq_avg += frequency;
    
    if (n_avg == N_AVG)
    {
       
        freq_avg /= n_avg;
        
        if((freq_avg > E2_L_LIMIT) && (freq_avg < E2_H_LIMIT))
        {
            [self setSliderMaximas:E2_SLIDER_UPPER_LIMIT : E2_SLIDER_LOWER_LIMIT];
            freq_avg -= DELTA_E2;
            [self.sliderTone setValue:freq_avg];
        }
        
        else if((freq_avg > A2_L_LIMIT) && (freq_avg < A2_H_LIMIT))
        {
            [self setSliderMaximas:A2_SLIDER_UPPER_LIMIT : A2_SLIDER_LOWER_LIMIT];
            freq_avg -= DELTA_A2 ;
            [self.sliderTone setValue:freq_avg];
        }
        else if((freq_avg > D3_L_LIMIT) && (freq_avg < D3_H_LIMIT))
        {
            [self setSliderMaximas:D3_SLIDER_UPPER_LIMIT : D3_SLIDER_LOWER_LIMIT];
            freq_avg -= DELTA_D3;
            [self.sliderTone setValue:freq_avg];
        }
        else if((freq_avg > G3_L_LIMIT) && (freq_avg < G3_H_LIMIT))
        {
            [self setSliderMaximas:G3_SLIDER_UPPER_LIMIT : G3_SLIDER_LOWER_LIMIT];
            freq_avg -= DELTA_G3;
            [self.sliderTone setValue:freq_avg];
        }
        else if((freq_avg > E4_L_LIMIT) && (freq_avg < E4_H_LIMIT))
        {
            [self setSliderMaximas:E4_SLIDER_UPPER_LIMIT : E4_SLIDER_LOWER_LIMIT];
            freq_avg -= DELTA_E4;
            [self.sliderTone setValue:freq_avg];
        }

        
        [self.measuredVal setText:[NSString stringWithFormat:@"%f",freq_avg]];
        
       
        [self tuning:freq_avg];
        [self printNote:actualNote];
        
    
        n_avg = 0;
    }
   
    
    // Notification has started
    if (characteristic.isNotifying) {
        
    }
    
}

- (void)peripheral:(CBPeripheral *)peripheral didUpdateNotificationStateForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error{
    
    if (error) {
        NSLog(@"Error changing notification state: %@", error.localizedDescription);
    }
    
    // Notification has started
    if (characteristic.isNotifying) {
        
    }
}

/** Once the disconnection happens, we need to clean up our local copy of the peripheral
 */
-(void)centralManager:(CBCentralManager *)central didDisconnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error
{
    NSLog(@"Peripheral Disconnected");
    self.discoveredPeripheral = nil;
    [self.connectionState setText:@"Disconnected"];
    [self.measuredVal setText:@"" ];
    
    //We're disconnected, so start scanning again
    [self scan];
}



/** Call this when things either go wrong, or you're done with connection.
 *  This cancels any subscriptions if there are any, or straight disconnects if not.
 */

-(void)cleanup
{
    // Don't do anything if we're not connected
    if(self.discoveredPeripheral.state == 0)
    {
        return;
    }
    
    // See if we are subscribed to a characteristic on the peripheral
    if(self.discoveredPeripheral.services != nil)
    {
        for(CBService *service in self.discoveredPeripheral.services)
        {
            if (service.characteristics != nil)
            {
                for(CBCharacteristic *characteristic in service.characteristics)
                {
                    if([characteristic.UUID isEqual:[CBUUID UUIDWithString:TRANSFER_CHARACTERISTIC_UUID]])
                    {
                        if (characteristic.isNotifying) {
                            //It is notifying, so unsubscribe
                            [self.discoveredPeripheral setNotifyValue:NO
                                                    forCharacteristic:characteristic];
                            // And we're done
                            return;
                        }
                    }
                }
            }
        }
    }
    // If we've got this far, we're connected, but we're not subscribed, so we just disconnect
    [self.centralManager cancelPeripheralConnection:self.discoveredPeripheral];
}



#pragma mark - CBCharacteristic helpers

// Instance method to get the heart rate BPM information
- (void) getADCData:(CBCharacteristic *)characteristic error:(NSError *)error
{
    NSData *adc = [characteristic value];
    //const uint8_t *reportData = [adc bytes];
    
    NSString *s;
    s = [NSString stringWithFormat:@"%@",adc];
    
    [self.measuredVal setText:s];
    
    //    if((characteristic.value) || !error)
    //    {
    //        NSLog(@"Characteristic Value is ok");
    //
    //    }
}




// Instance method to get the manufacturer name of the device
- (void) getManufacturerName:(CBCharacteristic *)characteristic
{
    NSString *manufacturerName = [[NSString alloc] initWithData:characteristic.value encoding:NSUTF8StringEncoding];  // 1
    self.manufacturer = [NSString stringWithFormat:@"Manufacturer: %@ :)", manufacturerName];    // 2
    return;
}

/*********************************************************************************************************************
 *  This function will extract the  data out of the bytes sent from the nRF51
 *********************************************************************************************************************/

-(void)extractByteFromNSData:(NSData *)data
{
    
    [data getBytes:&buffer length:8];
    
    count |= buffer[3];
    count = count << 24;
    count |= buffer[2];
    count |= count << 16;
    count |= buffer[1];
    count = count << 8;
    count |= buffer[0];
    
    pass |= buffer[7];
    pass = pass << 24;
    pass |= buffer[6];
    pass |= pass << 16;
    pass |= buffer[5];
    pass = pass << 8;
    pass |= buffer[4];
    
}
//-(void)extractCountFromNSData:(NSData *)data
//{
//  
//    
//    [data getBytes:&periodCount length:2];
//    
//    NSLog(@"periodCount: %d", periodCount);
//}
//
//-(void)extractFrequencyFromNSData:(NSData *)data
//{
//    [data getBytes:&receivedFreq length:2];
//    //NSLog(@"Freq received: %d", receivedFreq);
//}


/*
 * This function determines the actual note
 */
-(void)tuning:(float)frequency
{
    if((frequency > E2_LOWER_LIMIT) && (frequency < E2_UPPER_LIMIT))
    {
        actualNote = E2;
    }
    
    else if((frequency > A2_LOWER_LIMIT) && (frequency < A2_UPPER_LIMIT))
    {
        actualNote = A2;
    }
    else if((frequency > D3_LOWER_LIMIT) && (frequency < D3_UPPER_LIMIT))
    {
        actualNote = D3;
    }
    else if((frequency > G3_LOWER_LIMIT) && (frequency < G3_UPPER_LIMIT))
    {
        actualNote = G3;
    }
    else if((frequency > B3_LOWER_LIMIT) && (frequency < B3_UPPER_LIMIT))
    {
        actualNote = B3;
    }
    else if((frequency > E4_LOWER_LIMIT) && (frequency < E4_UPPER_LIMIT))
    {
        actualNote = E4;
    }
    
}
// Displays the actual note on screen and update slider for visualisation
-(void)printNote:(NOTE)note
{
    switch (note) {
            
        case E2:
            [self.note setText:@"E2"];
            self.view.backgroundColor = UIColorFromRGB(0x2ecc71);
            [self.sliderTone setThumbTintColor:UIColorFromRGB(0x27ae60)];
           // NSLog(@"E2");
            break;
            
        case A2:
            [self.note setText:@"A2"];
            self.view.backgroundColor = UIColorFromRGB(0x2ecc71);
            [self.sliderTone setThumbTintColor:UIColorFromRGB(0x27ae60)];
            //NSLog(@"A2");
            break;
            
        case D3:
            [self.note setText:@"D3"];
            self.view.backgroundColor = UIColorFromRGB(0x2ecc71);
            [self.sliderTone setThumbTintColor:UIColorFromRGB(0x27ae60)];
            //NSLog(@"D3");
            break;
            
        case G3:
            [self.note setText:@"G3"];
            self.view.backgroundColor = UIColorFromRGB(0x2ecc71);
            [self.sliderTone setThumbTintColor:UIColorFromRGB(0x27ae60)];
            //NSLog(@"G3");
            break;
            
        case B3:
            [self.note setText:@"B3"];
            self.view.backgroundColor = UIColorFromRGB(0x2ecc71);
            [self.sliderTone setThumbTintColor:UIColorFromRGB(0x27ae60)];
            //NSLog(@"B3");
            break;
            
        case E4:
            [self.note setText:@"E4"];
            self.view.backgroundColor = UIColorFromRGB(0x2ecc71);
            [self.sliderTone setThumbTintColor:UIColorFromRGB(0x27ae60)];
            //NSLog(@"E4");
            break;
            
        default:
            [self.note setText:@""];
            self.view.backgroundColor = UIColorFromRGB(0x22313F);
            [self.sliderTone setThumbTintColor:UIColorFromRGB(0xc0392b)];
            break;
    }
}

-(void)setSliderMaximas:(float)max : (float)min
{
    self.sliderTone.maximumValue = max;
    self.sliderTone.minimumValue = min;
}

@end
