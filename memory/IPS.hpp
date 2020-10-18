#include "hwlib.hpp"

using namespace hwlib;


class my_st7789 {
public:
   enum class commands : uint8_t {
      NOP        = 0x00,
      SWRESET    = 0x01,
      RDDID      = 0x04,
      RDDST      = 0x09,
      RDDPM      = 0x0A,
      RDDMADCTL  = 0x0B,
      RDDIM      = 0x0D,
      RDDSEM     = 0x0E,
      RDDSDR     = 0x0F,

      SLPIN      = 0x10,
      SLPOUT     = 0x11,
      PTLON      = 0x12,
      NORON      = 0x13,

      INVOFF     = 0x20,
      INVON      = 0x21,
      GAMSET     = 0x26,
      DISPOFF    = 0x28,
      DISPON     = 0x29,
      CASET      = 0x2A,
      RASET      = 0x2B,
      RAMWR      = 0x2C,
      RAMRD      = 0x2E,

      PTLAR      = 0x30,
      VSCRDEF    = 0x33,
      TEOFF      = 0x34,
      TEON       = 0x35,
      MADCTL     = 0x36,
      COLMOD     = 0x3A
   };
};

class my_st7789_spi_dc_cs_rst : public my_st7789, public window {
private:

   static auto constexpr wsize = xy( 240, 240 );

   bool_buffer<wsize.x * wsize.y> buffer;

   void write_implementation(
      xy pos,
      color col
   ) override {

   }

   void write_self_implementation( xy pos, bool x){
       buffer.set( pos.x + wsize.x * pos.y , x);

   }

   spi_bus & bus;
   pin_out & dc;
   pin_out & cs;
   pin_out & rst;

public:

   void command(
      commands c
   ){
      dc.write( 0 ); dc.flush();
      auto transaction = bus.transaction( cs );
      transaction.write( static_cast< uint8_t >( c ) );
      dc.write( 1 ); dc.flush();
   }

   void command(
      commands  c,
      uint8_t   d0
   ){
      dc.write( 0 ); dc.flush();
      auto transaction = bus.transaction( cs );
      transaction.write( static_cast< uint8_t >( c ) );
      dc.write( 1 ); dc.flush();
      transaction.write( d0 );
   }

   void command(
      commands c,
      uint8_t  d0,
      uint8_t  d1,
      uint8_t  d2,
      uint8_t  d3
   ){
      dc.write( 0 ); dc.flush();
      auto transaction = bus.transaction( cs );
      transaction.write( static_cast< uint8_t >( c ) );
      dc.write( 1 ); dc.flush();
      transaction.write( d0 );
      transaction.write( d1 );
      transaction.write( d2 );
      transaction.write( d3 );
   }

   my_st7789_spi_dc_cs_rst(
      spi_bus & bus,
      pin_out & dc,
      pin_out & cs,
      pin_out & rst
   ):
      window( wsize, white, black ),
      bus( bus ),
      dc( dc ),
      cs( cs ),
      rst( rst )
   {
      rst.write( 0 );rst.flush();
      wait_ms( 200 );
      rst.write( 1 );rst.flush();
      wait_ms( 200 );

      command( commands::SWRESET );
      wait_ms( 150 );

      command( commands::SLPOUT );
      wait_ms( 10 );

      command( commands::COLMOD, 0x66 );
      wait_ms( 10 );

      command( commands::MADCTL, 0x10 );
      command( commands::CASET, 0, 0, wsize.x >> 8, wsize.x & 0xFF );
      command( commands::RASET, 0, 0, wsize.y >> 8, wsize.y & 0xFF );

      command( commands::INVON );
      wait_ms( 10 );
      command( commands::NORON );
      wait_ms( 100 );
      command( commands::DISPON );
      wait_ms( 100 );

   }

   void clears( bool x){
       for( const auto p : all( size ) ){
          write_self_implementation( p, x );
       }

   }

   void flush() override {
      dc.write( 0 ); dc.flush();
      auto transaction = bus.transaction( cs );
      transaction.write( static_cast< uint8_t >( commands::RAMWR ) );
      dc.write( 1 ); dc.flush();
      for( int i = 0; i < 240 * 240 * 8; ++i ){
         transaction.write( buffer[ i ] );

      }
   }

};
