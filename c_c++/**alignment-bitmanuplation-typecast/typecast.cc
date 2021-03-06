/*
g++ -std=c++14 typecast.cc -o typecast
*/
#include <stdio.h>      /* printf */
#include <string.h>     /* strcat, memcpy */
#include <stdlib.h>     /* strtol */
#include <math.h>       /* pow */
#include <iostream>
#include <stack>
using namespace std;

template<class T>
void byte_to_binary(T x)
{
    size_t s = sizeof(T); // sizeof(x) same
    char b[s*8];
    b[0] = '\0';
    char *p = b;

    size_t t = pow(2, s*8) - pow(2, s*8-1); // 10000000 00000000 00000000 00000000
        
    for (size_t z = t ; z > 0; z >>= 1) 
    {
        // strcat(b, ((x & z) == z) ? "1" : "0");
        *p++ = (x & z) ? '1' : '0';        
    }
    *p++ = '\0';
    cout << b << endl;
    // printf("%s\n", b);   
}

/*
print binary bits of any data type
i.e. convert bits into any data type
*/
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0') 

void binaryPrint(int num){
  // printf("print 1 byte data type " BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY('a'));
  printf(BYTE_TO_BINARY_PATTERN BYTE_TO_BINARY_PATTERN BYTE_TO_BINARY_PATTERN BYTE_TO_BINARY_PATTERN "\n",
  BYTE_TO_BINARY(num>>24), BYTE_TO_BINARY(num>>16), BYTE_TO_BINARY(num>>8), BYTE_TO_BINARY(num));
}

void printstack(stack <int> gq)
{
    stack <int> g = gq;
    while (!g.empty())
    {
        cout << g.top();
        g.pop();
    }
    cout << '\n';
}

template<class T>
void binaryPrint2(T n){
  int count = 0;
  std::stack<int> bits;
  while(n){
    // (n & 0x01) ? '1' : '0';  
    bits.push(n & 0x01);
    // printf("%d", n & 0x01); // TODO: store in int/char stack
    n >>= 1;    
    count ++;
  }
  for (int i = 0; i < (sizeof(T)*8 - count); ++i)
  {    
    bits.push(0);
  }
  printstack(bits);
}

template<class T>
void binaryPrint3(T x)
{
    size_t s = sizeof(T); // sizeof(x) same
    char b[s*8];
    b[0] = '\0';
    char *p = b;

    size_t t = pow(2, s*8) - pow(2, s*8-1); // 10000000 00000000 00000000 00000000
        
    for (size_t z = t ; z > 0; z >>= 1) 
    {
        // strcat(b, ((x & z) == z) ? "1" : "0");
        *p++ = (x & z) ? '1' : '0';        
    }
    *p++ = '\0';
    cout << b << endl;
    // printf("%s\n", b);
}



void sixteenToEightBytes(){
  uint16_t fields[4] = {300, 301, 302, 303}; // 0000 0001 0010 1101, 0000 0001 0010 1110 ...
  uint8_t *byte_array = new uint8_t(8); // recvfrom() uses byte/char array
  for (int i = 0; i < 8; i+=2)
  {
    byte_array[i] = fields[i/2] >> 8; // upper 8 bits
    byte_array[i+1] = fields[i/2] & 0xFF; // lower 8 bits, actually no need 0xFF
  }
  byte_array[8] = '\0';

  for (int i = 0; i < 4; ++i){
      binaryPrint3(fields[i]);
  }
  
  for (int i = 0; i < 8; ++i){
    binaryPrint3(byte_array[i]);
  }

  // 8 bytes back to 16 bytes
  for (int i = 0; i < 4; ++i){
      fields[i] = (byte_array[i*2] << 8) | (byte_array[i*2+1]);
  }

  // fields has not changed
  for (int i = 0; i < 4; ++i){
      binaryPrint3(fields[i]);
  }
}

void sixteenToEightBytes2(){
    uint16_t value = 0xAAFF;
    uint8_t hi_lo_big_endian[] = { (uint8_t)(value >> 8), (uint8_t)value }; // { 0xAA, 0xFF }
    uint8_t lo_hi_little_endian[] = { (uint8_t)(value & 0xFF), (uint8_t)(value >> 8) }; // { 0xFF, 0xAA }
    // cout << int(hi_lo_big_endian) << endl;
    // cout << unsigned(hi_lo_big_endian) << endl;
    // printf("%#010x\n", value);
    // printf("%#010x\n", hi_lo_big_endian);
}

void structToByteArray(){
    struct ip_header{
        uint8_t iph_ttl;
        uint8_t iph_protocol;
    } m_theader;
    
    struct udp_header{
        uint16_t seq;
        uint16_t ack;
        uint16_t win;
        uint16_t flag;
        void setFlag(bool ACK, bool SYN, bool FIN){ flag |= (ACK << 2) | (SYN << 1) | FIN ;}
    } m_header; // stack

    m_header.seq = 10;
    m_header.ack = 10;
    m_header.win = 10;
    m_header.setFlag(1,0,1);
    
    udp_header *th = new udp_header; // heap
    th->seq = 10;
    th->ack = 2;
    th->win = 5;
    th->setFlag(1,0,1);

    uint8_t *pt = (uint8_t*)th;
    uint8_t *h_pt = (uint8_t*)&m_header;
    
    for (int i = 0; i < sizeof(udp_header); ++i)
    {
        binaryPrint3(pt[i]); // mac uses x86-64 that is little endian
        binaryPrint3(h_pt[i]);        
    }
    
    // memcpy or strncpy or declare new byte array to concatenate byte array 
    // declare long enough array, find each struct pointer starting pos
    size_t totalsize = sizeof(ip_header) + sizeof(udp_header);
    char *buffer = new char(totalsize);
    
    // typecast back to struct ptr
    ip_header *ip_h = (struct ip_header *)buffer;
    // pointer arithmetic 
    udp_header *udp_h = (struct udp_header *)(buffer + sizeof(struct ip_header)); 
    
    udp_h->seq = 10;
    udp_h->ack = 2;
    udp_h->win = 5;
    udp_h->setFlag(1,0,1);
    ip_h->iph_ttl = 64; // hops
    ip_h->iph_protocol = 17; // udp


    // typecast back to struct ptr
    cout << ((struct udp_header *)pt)->ack << endl;
    cout << ((struct udp_header *)h_pt)->ack << endl;

    for (int i = 0; i < totalsize; ++i)
    {
        binaryPrint3(buffer[i]);
    }

    char *buffer2 = new char(totalsize);
    // memcpy(buffer2, buffer, totalsize);
    memcpy(buffer2, ip_h, sizeof(ip_header));
    memcpy(buffer2 + sizeof(ip_header), udp_h, sizeof(udp_header));

    cout << (int)((struct ip_header *)buffer2)->iph_ttl << endl;

    for (int i = 0; i < totalsize; ++i)
    {
        binaryPrint3(buffer2[i]);
    }

}


int main(void)
{
    structToByteArray();
    return 0;
}