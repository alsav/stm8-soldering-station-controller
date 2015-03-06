
#define get_flag(flagvar) (flags>>flagvar) & 1
#define set_flag(flagvar) flags |= (1<<flagvar)
#define reset_flag(flagvar) flags &= ~(1<<flagvar)


#define CHECK_SWITCH_PERIOD 5
#define TEMP_LEVELS 8

//#define HEAT_CYCLES 30
#define HEAT_IDLE_CYCLES 10
//#define HEAT_IDLE_CYCLES 15

typedef enum {
    FLAG_SWITCH_EVENT,		//need switch event processing
    FLAG_SWITCH_PRESSED,
    FLAG_HEATER_ENABLED,
    FLAG_END_TEMP_MEASURE,
    FLAG_END_ADC_CONV
} FLAGS;


//void switch_event_processing(void);
void zero_detection_event_processing(void);
