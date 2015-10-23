// ********************** START OF MODEM.H **********************
//
//
// This header file has all of the definitions and prototypes
// needed to use the Modem class.  This file should be included
// by any module that uses the Modem class.

#ifndef _MODEM_DOT_H
#define _MODEM_DOT_H

#include "rs232.h"

enum ModemError {   MODEM_SUCCESS                 = 0,
                    MODEM_NO_RESPONSE             = -100,
                    MODEM_NO_CONNECTION           = -101,
                    MODEM_DISCONNECT_FAILED       = -102,
                    MODEM_USER_ABORT              = -103 };

// This structure defines the layout of the modem capability
// database elements.  At present, all of the definitions that
// can be used to define a particular brand or type of modem
// are stored in a static array in MODEM.CPP.  A commercial
// application might store these off line in a datatbase.

struct ModemCapabilities {
    char *name;
    char *initialization_string;
    char *fail_strings;
    char *compression_strings;
    char *protocol_strings;
    long initial_baud_rate;
    int locked_baud_rate;
    int handshaking;
};

// The Modem class definition

class Modem {
    protected :
        RS232 *port;
        ModemCapabilities *modem_data;
        long local_baud_rate;
        int tone_dial;
        int protocol;
        int compressing;
        ModemError wait_for_response( void );
        ModemError wait_for_connection( void );
        long carrier_timeout;
        virtual void echo( char c ) { cout << c; }
        void read_line( char *buffer, int buf_size );

    public :
        Modem( RS232 &rs232_port, char *modem_name );
        ModemError Initialize( void );
        ModemError Answer( void );
        ModemError Dial( char *number );
        ModemError Disconnect( void );
        ModemError SendCommand( char * );
        int ReadRegister( int reg );
        virtual ModemError UserAbort( void );
        void PulseDial( void ){ tone_dial = 0; }
        void ToneDial( void ){ tone_dial = 1; }
        void SetCarrierTimeout( long length ){ carrier_timeout = length; }
        char *ErrorName( ModemError status );
        virtual void DumpState( void );
        int Protocol( void ){ return protocol; }
        int Compressing( void ){ return compressing; }
};


#endif // #ifdef _MODEM_DOT_H

// ********************** END OF MODEM.H **********************

