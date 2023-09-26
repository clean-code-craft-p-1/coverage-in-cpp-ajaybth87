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

int checkAndAlert(AlertTarget alertTarget, EquipmentCharacter characteristic, double temperatureInC) 
{
int status=NOK;
  BreachType breachType = classifyTemperatureBreach(characteristic.coolingType, temperatureInC);

  switch(alertTarget) {
    case AlertTarget::TO_CONTROLLER:
      status=sendToController(breachType);
      break;
    case AlertTarget::TO_EMAIL:
      status=sendToEmail(breachType);
      break;
  }
  return status;
}

int sendToController(BreachType breachType) 
{
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
  
  return OK;
}

int sendToEmail(BreachType breachType) 
{
  int status=NOK; 
  const char* recepient = "a.b@c.com";
  if(BreachType::TOO_LOW == breachType)
  {
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too low\n");
	  status=OK;
  }
  else if(BreachType::TOO_HIGH == breachType)
  {
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too high\n");
	  status=OK;
  }
  else
  {
	  status=OK;
	//Do nothing    
  }
  
  return status;
}
