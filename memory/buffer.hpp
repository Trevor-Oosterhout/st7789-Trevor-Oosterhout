
template< unsigned int N >
class bool_buffer {
private:
    unsigned char buffer[ ( N + 7) /8];

public:
    bool operator[](int i) const {
        return (( buffer[ i / 8 ] >> ( i % 8 )) & 0x01 ) != 0;
    }

    void set( int i , bool x){
        if(x){
            buffer[i / 8] |= (0x01 << (i % 8));
        }
        else{
            buffer[i / 8] &= ~(0x01 << (i % 8));
        }
    }

    bool get(int i) const{
        return (( buffer[ i / 8 ] >> ( i % 8 )) & 0x01 ) != 0;
    }

    class reference{
    private:
        bool_buffer & subject;
        int n;
    public:
        reference( bool_buffer & subject, int n): subject ( subject), n (n){}

        reference & operator=( bool x){
            subject.set(n, x);
            return *this;
        }

        operator bool(){
            return subject.get(n);
        }


    };

    reference operator[]( int i){
        return reference(*this, i);
    }

};
