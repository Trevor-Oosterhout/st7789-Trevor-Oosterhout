#include "hwlib.hpp"
#include "myspi.hpp"
#include "buffer.hpp"
#include "IPS.hpp"

namespace target = hwlib::target;

int main( void ){

   // wait for the terminal emulator to start up
   hwlib::wait_ms( 2'000 );
   hwlib::cout << "ST7789 demo\n" << hwlib::flush;

   // auto _sclk = hwlib::target::pin_out{ hwlib::target::pins::d3 };
   // auto sclk = hwlib::invert( _sclk );
   // auto mosi = hwlib::target::pin_out{ hwlib::target::pins::d4 };
   pin_out_port_c clock_pin = pin_out_port_c(28);
   pin_out_port_c mosi_pin = pin_out_port_c(26);

   //
   // auto spi  = my_spi_bus_bit_banged_sclk_mosi_miso{
   //    sclk, mosi, hwlib::pin_in_dummy, clock_pin, mosi_pin };

   auto spi  = my_spi_bus_bit_banged_sclk_mosi_miso{
      hwlib::pin_out_dummy, hwlib::pin_out_dummy, hwlib::pin_in_dummy, clock_pin, mosi_pin };

   auto dc    = hwlib::target::pin_out{ hwlib::target::pins::d6 };
   auto & cs  = hwlib::pin_out_dummy;
   auto blk   = hwlib::target::pin_out{ hwlib::target::pins::d7 };
   auto rst   = hwlib::target::pin_out{ hwlib::target::pins::d5 };

   blk.write( 1 );blk.flush();

   auto display     = my_st7789_spi_dc_cs_rst( spi, dc, cs, rst );


   for(;;){

       display.clears( 1 );
       display.flush();

       display.clears( 0 );
       display.flush();


   }

}
