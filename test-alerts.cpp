
#include "typewise-alert.h"

#include "gtest/gtest.h"

TEST(TypewiseAlert, InferBreachAsPerLimits) {
  ASSERT_TRUE(inferBreach(0.0, 20.0, 30.0) == BreachType::TOO_LOW);
  ASSERT_TRUE(inferBreach(12.0, 20.0, 30.0) == BreachType::TOO_LOW);
  ASSERT_TRUE(inferBreach(20.0, 20.0, 30.0) == BreachType::NORMAL);
  ASSERT_TRUE(inferBreach(30.0, 20.0, 30.0) == BreachType::NORMAL);
  ASSERT_TRUE(inferBreach(31.0, 20.0, 30.0) == BreachType::TOO_HIGH);
  ASSERT_TRUE(inferBreach(50.0, 20.0, 30.0) == BreachType::TOO_HIGH);
}

TEST(TypewiseAlert, ClassifyTemperatureBreach) {
  ASSERT_TRUE(classifyTemperatureBreach(CoolingType::PASSIVE_COOLING,-40) == BreachType::TOO_LOW);
  ASSERT_TRUE(classifyTemperatureBreach(CoolingType::PASSIVE_COOLING,-1) == BreachType::TOO_LOW);
  ASSERT_TRUE(classifyTemperatureBreach(CoolingType::PASSIVE_COOLING,0) == BreachType::NORMAL);
  ASSERT_TRUE(classifyTemperatureBreach(CoolingType::PASSIVE_COOLING,25) == BreachType::NORMAL);
  ASSERT_TRUE(classifyTemperatureBreach(CoolingType::PASSIVE_COOLING,35) == BreachType::NORMAL);
  ASSERT_TRUE(classifyTemperatureBreach(CoolingType::PASSIVE_COOLING,36) == BreachType::TOO_HIGH);
  ASSERT_TRUE(classifyTemperatureBreach(CoolingType::PASSIVE_COOLING,40) == BreachType::TOO_HIGH);
  ASSERT_TRUE(classifyTemperatureBreach(CoolingType::PASSIVE_COOLING,45) == BreachType::TOO_HIGH);
  
  ASSERT_TRUE(classifyTemperatureBreach(CoolingType::MED_ACTIVE_COOLING,-40) == BreachType::TOO_LOW);
  ASSERT_TRUE(classifyTemperatureBreach(CoolingType::MED_ACTIVE_COOLING,-1) == BreachType::TOO_LOW);
  ASSERT_TRUE(classifyTemperatureBreach(CoolingType::MED_ACTIVE_COOLING,0) == BreachType::NORMAL);
  ASSERT_TRUE(classifyTemperatureBreach(CoolingType::MED_ACTIVE_COOLING,35) == BreachType::NORMAL);
  ASSERT_TRUE(classifyTemperatureBreach(CoolingType::MED_ACTIVE_COOLING,40) == BreachType::NORMAL);
  ASSERT_TRUE(classifyTemperatureBreach(CoolingType::MED_ACTIVE_COOLING,41) == BreachType::TOO_HIGH);
  ASSERT_TRUE(classifyTemperatureBreach(CoolingType::MED_ACTIVE_COOLING,45) == BreachType::TOO_HIGH);
  
  ASSERT_TRUE(classifyTemperatureBreach(CoolingType::HI_ACTIVE_COOLING,-40) == BreachType::TOO_LOW);
  ASSERT_TRUE(classifyTemperatureBreach(CoolingType::HI_ACTIVE_COOLING,-1) == BreachType::TOO_LOW);
  ASSERT_TRUE(classifyTemperatureBreach(CoolingType::HI_ACTIVE_COOLING,0) == BreachType::NORMAL);
  ASSERT_TRUE(classifyTemperatureBreach(CoolingType::HI_ACTIVE_COOLING,35) == BreachType::NORMAL);
  ASSERT_TRUE(classifyTemperatureBreach(CoolingType::HI_ACTIVE_COOLING,45) == BreachType::NORMAL);
  ASSERT_TRUE(classifyTemperatureBreach(CoolingType::HI_ACTIVE_COOLING,46) == BreachType::TOO_HIGH);
  ASSERT_TRUE(classifyTemperatureBreach(CoolingType::HI_ACTIVE_COOLING,50) == BreachType::TOO_HIGH);
}

TEST(TypewiseAlert, SendToController) 
{
  AlertTarget alertTarget = TO_CONTROLLER;
  double temperatureInC = 25.0;

  BreachType breachType = classifyTemperatureBreach(CoolingType::HI_ACTIVE_COOLING, temperatureInC);

  switch(alertTarget) 
  {
	case TO_CONTROLLER:
      ASSERT_TRUE(OK==sendToController(breachType));
      break;
    case TO_EMAIL:
      // Check if sendToController is not called
      ASSERT_TRUE(breachType==BreachType::TOO_HIGH);
      break;
  }
}

TEST(TypewiseAlert, sendToEmail)
{
  AlertTarget alertTarget = TO_EMAIL;

  BreachType breachType1 = classifyTemperatureBreach(CoolingType::PASSIVE_COOLING, -1);
  BreachType breachType2 = classifyTemperatureBreach(CoolingType::HI_ACTIVE_COOLING, 46);
  BreachType breachType3 = classifyTemperatureBreach(CoolingType::MED_ACTIVE_COOLING, 35);

  switch(alertTarget) 
  {
	case TO_CONTROLLER:
       // Check if sendToEmail is not called
      ASSERT_TRUE(breachType1==BreachType::TOO_HIGH);
      break;
    case TO_EMAIL:
      ASSERT_TRUE(OK==sendToEmail(breachType1));
	  ASSERT_TRUE(OK==sendToEmail(breachType2));
	  ASSERT_TRUE(OK==sendToEmail(breachType3));
      break;
  }
}

TEST(TypewiseAlert,CheckAndAlertTest)
{
  AlertTarget alertTarget={};
  EquipmentCharacter characteristic={};
  double temperatureInC
  
  alertTarget=AlertTarget::NONE;
  characteristic.coolingType=CoolingType::PASSIVE_COOLING;
  temperatureInC=10;
  ASSERT_TRUE(NOK==checkAndAlert(alertTarget, characteristic, temperatureInC); 
  
  alertTarget=AlertTarget::TO_EMAIL;
  characteristic.coolingType=CoolingType::PASSIVE_COOLING;
  temperatureInC=10;
  ASSERT_TRUE(OK==checkAndAlert(alertTarget, characteristic, temperatureInC);
  
  alertTarget=AlertTarget::TO_CONTROLLER;
  characteristic.coolingType=CoolingType::PASSIVE_COOLING;
  temperatureInC=10;
  ASSERT_TRUE(OK==checkAndAlert(alertTarget, characteristic, temperatureInC);

}