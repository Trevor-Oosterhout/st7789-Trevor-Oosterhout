class pin_out_port_a{
private:
    int pin;

public:
    pin_out_port_a(int pin): pin (pin)
    {
        WDT->WDT_MR = WDT_MR_WDDIS;
        PIOA->PIO_OER = 0x01 << pin;
    }

    void write(bool x){
        if(x){
            PIOA->PIO_SODR = 0x01 << pin;
        }
        else{
            PIOA->PIO_CODR = 0x01 << pin;
        }
    }

    void invert_write(bool x){
        if(!x){
            PIOA->PIO_SODR = 0x01 << pin;
        }
        else{
            PIOA->PIO_CODR = 0x01 << pin;
        }
    }

};


class pin_out_port_b{
private:
    int pin;

public:
    pin_out_port_b(int pin): pin (pin)
    {
        WDT->WDT_MR = WDT_MR_WDDIS;
        PIOB->PIO_OER = 0x01 << pin;
    }

    void write(bool x){
        if(x){
            PIOB->PIO_SODR = 0x01 << pin;
        }
        else{
            PIOB->PIO_CODR = 0x01 << pin;
        }
    }

    void invert_write(bool x){
        if(!x){
            PIOB->PIO_SODR = 0x01 << pin;
        }
        else{
            PIOB->PIO_CODR = 0x01 << pin;
        }
    }

};


class pin_out_port_c{
private:
    int pin;

public:
    pin_out_port_c( int pin): pin (pin)
    {
        WDT->WDT_MR = WDT_MR_WDDIS;
        PIOC->PIO_OER = 0x01 << pin;
    }

    void write(bool x){
        if(x){
            PIOC->PIO_SODR = 0x01 << pin;
        }
        else{
            PIOC->PIO_CODR = 0x01 << pin;
        }
    }

    void invert_write(bool x){
        if(!x){
            PIOC->PIO_SODR = 0x01 << pin;
        }
        else{
            PIOC->PIO_CODR = 0x01 << pin;
        }
    }

};


class pin_out_port_d{
private:
    int pin;

public:
    pin_out_port_d(int pin): pin (pin)
    {
        WDT->WDT_MR = WDT_MR_WDDIS;
        PIOD->PIO_OER = 0x01 << pin;
    }

    void write(bool x){
        if(x){
            PIOD->PIO_SODR = 0x01 << pin;
        }
        else{
            PIOD->PIO_CODR = 0x01 << pin;
        }
    }

    void invert_write(bool x){
        if(!x){
            PIOD->PIO_SODR = 0x01 << pin;
        }
        else{
            PIOD->PIO_CODR = 0x01 << pin;
        }
    }

};
