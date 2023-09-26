#pragma once

#define OK  0
#define NOK 1

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

typedef enum 
{
  TO_CONTROLLER,
  TO_EMAIL,
  NONE     //Add new alerter above the NONE.
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} EquipmentCharacter;

int checkAndAlert(
  AlertTarget alertTarget, EquipmentCharacter characteristic, double temperatureInC);

int sendToController(BreachType breachType);
int sendToEmail(BreachType breachType);
