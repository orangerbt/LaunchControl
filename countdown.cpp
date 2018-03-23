//Launch program
#include "gpioHandle.h"
#include <iostream>
#include <cstdlib>
#include <unistd.h>

using namespace std;

char * launchCode = "Fly you Fools!";
int valveOpenTime = 2;
int ignitionKeepOnTime = 10;

int main ()
{
  system("clear");
  /*Initialize GPIO communication*/
  gpioHandle gpio;
  gpio.initializePin(60,0,0);
  gpio.initializePin(30,0,0);


  /*Set rocket to launch if code correct*/
  string enteredCode;
  cout << "ready to launch!" << endl;
  cout << "To cancel: press 'Control' and 'C' simultaneously." << endl;
  cout << "To start countdown: Enter the phrase: 'Fly you Fools!' and press enter." << endl;
  cin >> enteredCode;
  if (enteredCode == "Fly you Fools!"){
    cout << "\nLaunch Initiated" << endl;
    cout << "Clear all personelle from the launch zone" << endl;
    /* Launch Countdown*/
    for (int i = 15; i >= 0; i--){
      sleep(1);
	    }

    /*Launching rocket*/
    gpio.setPinVal(30,1);
    sleep(ignitionKeepOnTime); //in air?

    /*Shut down rocket booster*/
    gpio.setPinVal(30,0);
    gpio.setPinVal(60,0);
    cout << "Launch Complete!" << endl;
  } else {
    cout << "The launch phrase did not match! Aborting!" << endl;
  }//end else
  /*Sets the pin mode to IN*/
  gpio.setPinMode(60,1,0);
  gpio.setPinMode(30,1,0);

  /*Deconstructs the gpio*/
  gpio.pinClose(30);
  gpio.pinClose(60);

}//ense main()
