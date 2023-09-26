#include "typewise-alert.h"
#include <stdio.h>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) 
{
  if(value < lowerLimit) {
    return BreachType::TOO_LOW;
  }
  if(value > upperLimit) {
    return BreachType::TOO_HIGH;
  }
  return BreachType::NORMAL;
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) 
{
  int lowerLimit = 0;
  int upperLimit = 0;
  if (CoolingType::PASSIVE_COOLING == coolingType) 
  {
    lowerLimit = 0;
    upperLimit = 35;
  }  
  else if (CoolingType::MED_ACTIVE_COOLING == coolingType) 
  {
    lowerLimit = 0;
    upperLimit = 40;
  }
  else
  {
    lowerLimit = 0;
    upperLimit = 45;
  }
  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

void checkAndAlert(AlertTarget alertTarget, EquipmentCharacter characteristic, double temperatureInC) 
{

  BreachType breachType = classifyTemperatureBreach(characteristic.coolingType, temperatureInC);

  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
  }
}

void sendToController(BreachType breachType) 
{
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) 
{
  const char* recepient = "a.b@c.com";
  if(BreachType::TOO_LOW == breachType)
  {
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too low\n");
  }
  else if(BreachType::TOO_HIGH == breachType)
  {
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too high\n");
  }
  else
  {
	//Do nothing    
  }
}
