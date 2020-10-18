#include "hwlib.hpp"
#include "mypin.hpp"


using namespace hwlib;

class my_spi_bus_bit_banged_sclk_mosi_miso : public spi_bus {
 private:

    pin_direct_from_out_t sclk;
    pin_direct_from_out_t mosi;
    pin_direct_from_in_t  miso;
    pin_out_port_c clock_pin, mosi_pin;

    // very crude;
    // delay should be a constructor parameter
    void HWLIB_INLINE wait_half_period(){
       wait_us( 1 );
    }

    void write_and_read(
       const size_t n,
       const uint8_t data_out[],
       uint8_t data_in[]
    ) override {

       for( uint_fast8_t i = 0; i < n; ++i ){

          uint_fast8_t d = *data_out++;

          for( uint_fast8_t j = 0; j < 8; ++j ){
             mosi_pin.write(( d & 0x80 ) != 0);
             clock_pin.invert_write(1);
             d = d << 1;
             clock_pin.invert_write(0);

          }

       }
    }

 public:

    my_spi_bus_bit_banged_sclk_mosi_miso(
       pin_out & _sclk,
       pin_out & _mosi,
       pin_in  & _miso,
       pin_out_port_c & clock_pin,
       pin_out_port_c & mosi_pin
    ):
       //sclk( direct( _sclk ) ),
       //mosi( direct( _mosi ) ),
       //miso( direct( _miso ) )

       sclk( _sclk ),
       mosi( _mosi ),
       miso( _miso ),
       clock_pin( clock_pin ),
       mosi_pin( mosi_pin )
       {
       sclk.write( 0 );
       clock_pin.invert_write(0);
        }

 };


 // dit was om te testen of mijn oplossing iets deed.
 // void clock_write(bool x){
 //     if(!x){
 //         PIOC->PIO_SODR = 0x01 << 28;
 //     }
 //     else{
 //         PIOC->PIO_CODR = 0x01 << 28;
 //     }
 // }
 //
 //
 // void mosi_write(bool x){
 //     if(x){
 //         PIOC->PIO_SODR = 0x01 << 26;
 //     }
 //     else{
 //         PIOC->PIO_CODR = 0x01 << 26;
 //     }
 // }
