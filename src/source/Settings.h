#ifndef CLUSTERLIST_SETTINGS_H
#define CLUSTERLIST_SETTINGS_H

#define IS_ARDUINO_FRAMEWORK    1 // (0/1)
#define USE_AUTO_TYPE_AMOUNT    1 // (0/1) this option enable to switch if IS_ARDUINO_FRAMEWORK == 1

#if IS_ARDUINO_FRAMEWORK == 1
    #define size_t size_t
#else
    #define size_t std::size_t
#endif

#if USE_AUTO_TYPE_AMOUNT == 1 && IS_ARDUINO_FRAMEWORK == 1
    #if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__) // Arduino Uno
        #define AMOUNT_CLUSTERS uint8_t
        #define AMOUNT_ELEMENTS uint8_t
    #elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) // Arduino Mega
        #define AMOUNT_CLUSTERS uint8_t
        #define AMOUNT_ELEMENTS uint16_t
    #else // other boards
        #define AMOUNT_CLUSTERS uint8_t
        #define AMOUNT_ELEMENTS uint16_t
    #endif
#else
    #define AMOUNT_CLUSTERS size_t
    #define AMOUNT_ELEMENTS size_t
#endif

// cluster type
namespace clt {
    typedef AMOUNT_CLUSTERS type_clAmount;
    typedef AMOUNT_ELEMENTS type_elemAmount;
}

#endif //CLUSTERLIST_SETTINGS_H
