/* 
** HBWLinkDimmerAdvanced
**
** Direkte Verknuepfung (Peering), zu Schaltausgaengen
** Ein Link-Objekt steht immer fuer alle (direkt aufeinander folgenden) Verknuepfungen
** des entsprechenden Typs.
**
** http://loetmeister.de/Elektronik/homematic/
*/

#include "HBWLinkDimmerAdvanced.h"

#define EEPROM_SIZE 42   // "address_step" in XML

#define NUM_PEER_PARAMS 18   // number of bytes for long and short peering action each (without address and channel)

HBWLinkDimmerAdvanced::HBWLinkDimmerAdvanced(uint8_t _numLinks, uint16_t _eepromStart) {
	numLinks = _numLinks;
	eepromStart = _eepromStart;
}
 
// receiveKeyEvent wird aufgerufen, wenn ein Tastendruck empfangen wurde
// TODO: Der Beginn aller Verknuepfungen ist gleich. Eigentlich koennte man 
//       das meiste in einer gemeinsamen Basisklasse abhandeln
void HBWLinkDimmerAdvanced::receiveKeyEvent(HBWDevice* device, uint32_t senderAddress, uint8_t senderChannel, 
                                          uint8_t targetChannel, uint8_t keyPressNum, boolean longPress) {
  
  uint32_t sndAddrEEPROM;
  uint8_t channelEEPROM;
  uint8_t actionType;

  uint8_t data[NUM_PEER_PARAMS +1];  // store all peer parameter (use extra element for keyPressNum)
  data[NUM_PEER_PARAMS] = keyPressNum;
  
  // read what to do from EEPROM
  for(byte i = 0; i < numLinks; i++) {
	  device->readEEPROM(&sndAddrEEPROM, eepromStart + EEPROM_SIZE * i, 4, true);
	  // TODO: is the following really ok?
	  //       it reads to all links, even if none is set 
	  if(sndAddrEEPROM == 0xFFFFFFFF) continue;
	  if(sndAddrEEPROM != senderAddress) continue;
	  // compare sender channel
	  device->readEEPROM(&channelEEPROM, eepromStart + EEPROM_SIZE * i + 4, 1);
	  if(channelEEPROM != senderChannel) continue;
	  // compare target channel
	  device->readEEPROM(&channelEEPROM, eepromStart + EEPROM_SIZE * i + 5, 1);
	  if(channelEEPROM != targetChannel) continue;
	  // ok, we have found a match
    if (!longPress) { // differs for short and long
      device->readEEPROM(&actionType, eepromStart + EEPROM_SIZE * i + 6, 1);      // read shortPress actionType
      if (actionType & B00001111) {   // SHORT_ACTION_TYPE, ACTIVE
        // when active, read all other values and call channel set()
        device->readEEPROM(&data, eepromStart + EEPROM_SIZE * i + 6, NUM_PEER_PARAMS);     // read all parameters (must be consecutive)
     //         + 6       //  SHORT_ACTION_TYPE
     //         + 7       //  SHORT_ONDELAY_TIME
     //         + 8       //  SHORT_ON_TIME
     //         + 9       //  SHORT_OFFDELAY_TIME
     //         + 10      //  SHORT_OFF_TIME
     //         + 11, 12, 13   //  SHORT_JT_* table
     //         + 14      // SHORT_OFF_LEVEL
     //         + 15      // SHORT_ON_MIN_LEVEL
     //         + 16      // SHORT_ON_LEVEL
     //         + 17      // SHORT_ONDELAY_MODE, SHORT_ON_LEVEL_PRIO, SHORT_OFFDELAY_BLINK, SHORT_RAMP_START_STEP
     //         + 18      // SHORT_RAMPON_TIME
     //         + 19      // SHORT_RAMPOFF_TIME
     //         + 20      // SHORT_DIM_MIN_LEVEL
     //         + 21      // SHORT_DIM_MAX_LEVEL
     //         + 22      // SHORT_DIM_STEP, SHORT_OFFDELAY_STEP
     //         + 23      // SHORT_OFFDELAY_NEWTIME, SHORT_OFFDELAY_OLDTIME
        device->set(targetChannel, NUM_PEER_PARAMS +1, data);    // channel, data length, data
      }
    }
    // read specific long action eeprom section
    else {
      device->readEEPROM(&actionType, eepromStart + EEPROM_SIZE * i + 6 + NUM_PEER_PARAMS, 1); // read longPress actionType
      if (actionType & B00001111) {  // LONG_ACTION_TYPE, ACTIVE
        // when active, read all other values and call channel set()
        device->readEEPROM(&data, eepromStart + EEPROM_SIZE * i + 6 + NUM_PEER_PARAMS, NUM_PEER_PARAMS);     // read all parameters (must be consecutive)
     //         + 6+ NUM_PEER_PARAMS      //  LONG_ACTION_TYPE
     //         + 7+ NUM_PEER_PARAMS      //  LONG_ONDELAY_TIME
     // ... and so on. Layout for LONG_* and SHORT_* must be the same
        device->set(targetChannel, NUM_PEER_PARAMS +1, data);    // channel, data length, data
      }
    }
  }
}

