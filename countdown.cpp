//Launch program
#include "gpioHandle.h"
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#define IGNITION 48
#define OXIDIZER 51
#define MAINPOWER 60

using namespace std;

string launchCode = "Fly you Fools!";
int valveOpenTime = 2;
int ignitionKeepOnTime = 2;
int engineOnTime = 10;

int main ()
{
  int res;
  system("clear");
  /*Initialize GPIO communication*/
  gpioHandle gpio;
  res = gpio.initializePin(IGNITION,0,0);
  if (res != 0){
    cout << "Ignition initialization failed" << endl;
    return(-1);
  }
  res = gpio.initializePin(OXIDIZER,0,0);
  if (res != 0){
    cout << "Oxidizer initialization failed" << endl;
    return(-1);
  }
  res = gpio.initializePin(MAINPOWER,0,0);
  if (res != 0)
    cout << "Main power initialization failed" << endl;

  /*Set rocket to launch if code correct*/
  string enteredCode;
  cout << "ready to launch!" << endl;
  cout << "To cancel: press 'Control' and 'C' simultaneously." << endl;
  cout << "To start countdown: Enter the phrase: 'Fly you Fools!' and press enter." << endl;
  getline(cin,enteredCode);
  if (enteredCode == "Fly you Fools!"){
    gpio.setPinVal(MAINPOWER,1);
    cout << "\nLaunch Initiated" << endl;
    cout << "Clear all personnel from the launch zone" << endl;
    /* Launch Countdown*/
    for (int i = 7; i > valveOpenTime; i--){
      cout << i << endl;
      sleep(1);
	    }
      gpio.setPinVal(OXIDIZER,1);
    cout << "Opening valve" << endl;
    for (int i = valveOpenTime; i >= 0; i--){
      cout << i << endl;
      sleep(1);

    }
    /*Launching rocket*/
    gpio.setPinVal(IGNITION,1);
    cout << "Launching" << endl;
    for (int i = 0; i < ignitionKeepOnTime; i++){
      cout << i << endl;
      sleep(1);
  }

    /*Shut down rocket booster*/
    //gpio.setPinVal(OXIDIZER,0);
    gpio.setPinVal(IGNITION,0);
    cout << "Ignition turned off" << endl;
    for(int i = ignitionKeepOnTime; i < engineOnTime; i++){
      cout << i << endl;
      sleep(1);
    }
    gpio.setPinVal(OXIDIZER,0);
    cout << "Launch Complete!" << endl;
  } else {
    cout << "The launch phrase did not match! Aborting!" << endl;
  }//end else
  /*Sets the pin mode to IN*/
  gpio.setPinMode(IGNITION,1,0);
  gpio.setPinMode(OXIDIZER,1,0);


  /*Deconstructs the gpio*/
  //don't shut off the main power

  gpio.pinClose(OXIDIZER);
  gpio.pinClose(IGNITION);
  gpio.setPinVal(MAINPOWER,0);
  return(0);

}//ense main()
