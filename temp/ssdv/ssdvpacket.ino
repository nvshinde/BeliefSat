#include <RadioLib.h>
#include <util/crc16.h>

SX1268 radio = new Module(7,2,3,4);
uint8_t ccsds_sync_word[4]={0x1A,0xCF,0xFC,0x1D};
byte imgPacket[768] = {55, 66, 9D, 15, FC, 73, 01, 00, 00, 0A, 0A, 02, 00, 00, 00, F4, 0A, 28, 01, 92, 76, A8, F2, 7D, 68, 00, C9, F5, A3, 27, D6, 80, 0C, 9F, 5A, 32, 7D, 68, 00, C9, F5, A3, 27, D6, 80, 0C, 9F, 5A, 32, 7D, 68, 00, C9, F5, A3, 27, D6, 80, 24, 4F, BB, 4F, A0, 02, 8A, 00, 28, A0, 02, 8A, 00, 8E, 4E, D4, CA, 00, 28, A0, 02, 8A, 00, 28, A0, 02, 8A, 00, 28, A0, 09, 23, FB, B4, FA, 00, 28, A0, 02, 8A, 00, 28, A0, 08, E4, ED, 4C, A0, 02, 8A, 00, 28, A0, 02, 8A, 00, 28, A0, 02, 8A, 00, 92, 3F, BB, 4F, A0, 02, 8A, 00, 28, A0, 02, 8A, 00, 8E, 4E, D4, CA, 00, 28, A0, 02, 8A, 00, 28, A0, 02, 8A, 00, 28, A0, 09, 23, FB, B4, FA, 00, 28, A0, 02, 8A, 00, 28, A0, 08, E4, ED, 4C, A0, 02, 8A, 00, 28, A0, 02, 8A, 00, 28, A0, 02, 8A, 00, 92, 3F, BB, 4F, A0, 02, 8A, 00, 28, A0, 02, 8A, 00, 8E, 4E, D4, CA, 00, 28, A0, 02, 8A, 00, 28, A0, 02, 8A, 00, 28, A0, 09, 23, FB, B4, FA, 00, 28, A0, 02, 8A, 95, 2D, BD, EE, A9, A3, C2, B7, D1, E9, 6C, F5, DC, C2, 9B, 49, 06, EE, 37, 76, E9, 1A, 18, 97, 00, 2F, B5, 8D, 4D, F4, FF, CB, 3D, 1F, 5E, 04, 55, 66, 9D, 15, FC, 73, 01, 00, 01, 0A, 0A, 02, 04, 00, 3D, 00, 28, A0, 0F, EF, 24, ED, 4C, A0, 02, 8A, 00, 28, A0, 02, 8A, 00, 31, 46, 28, 00, C5, 18, A0, 09, 13, EE, D3, E8, 00, A2, 80, 0A, 28, 00, A2, 80, 23, 93, B5, 32, 80, 0A, 28, 00, A2, 80, 0A, 92, 3E, 86, 80, 1F, 45, 00, 14, 50, 02, 13, 81, 9A, 67, 99, ED, 40, 07, 99, ED, 47, 99, ED, 40, 07, 99, ED, 4F, 07, 23, 34, 00, B4, 50, 04, 72, 76, A6, 50, 01, 45, 00, 14, 50, 01, 52, 47, D0, D0, 03, E8, A0, 02, 8A, 00, 46, FB, A6, A1, A0, 02, 8A, 00, 2A, 54, FB, A2, 80, 1D, 45, 00, 47, 27, 6A, 65, 00, 14, 50, 01, 45, 00, 15, 24, 7D, 0D, 00, 3E, 8A, 00, 28, A0, 04, 6F, BA, 6A, 1A, 00, 28, A0, 02, A5, 4F, BA, 28, 01, D4, 50, 04, 72, 76, A6, 50, 01, 45, 00, 14, 50, 01, 52, 47, D0, D0, 03, E8, A0, 02, 8A, 00, 46, FB, A6, A1, A0, 02, 8A, 00, 2A, 54, FB, A2, 80, 1D, 45, 00, 32, 41, 9C, 53, 30, 7D, 0D, 00, 18, 3E, 86, 8C, 1F, 62, C9, 50, F4, A8, CD, 44, 17, 67, E6, BA, AD, 38, 9C, 86, 20, 2C, 21, A6, 2A, 1C, 40, 69, 66, FD, 1A, BB, CF, 3C, 53, 3E, 1E, 1B, 31, 82, B6, 55, 66, 9D, 15, FC, 73, 01, 00, 02, 0A, 0A, 02, 03, 00, 71, 43, 40, 1F, EE, B0, 7D, 0D, 18, 3E, 86, 80, 0C, 1F, 43, 4F, 41, 80, 68, 01, F4, 50, 01, 45, 00, 23, 7D, D3, 51, 60, FA, 1A, 00, 30, 7D, 0D, 18, 3E, 86, 80, 0C, 1F, 43, 52, 2F, DD, 14, 00, EA, 28, 00, A4, A0, 02, 8A, 00, 28, A0, 02, 8F, F3, 40, 0B, 45, 00, 14, 50, 01, 49, 40, 05, 14, 00, 52, FF, 9F, F3, 40, 05, 14, 00, 84, E0, 66, 9B, E6, 0F, 43, 40, 0E, A4, 66, DB, 40, 09, E6, 0F, 43, 47, 98, 3D, E8, 01, C1, 81, E8, 69, 68, 01, A5, C0, 38, C5, 27, 98, 3D, 0D, 00, 1E, 60, F4, 34, 79, 83, D0, D0, 03, A8, A0, 04, 2E, 05, 37, CC, F6, FF, 34, 00, A1, C7, 7E, 29, D4, 00, B4, 50, 02, 11, 91, 83, 51, 11, 86, 22, 80, 25, A6, 49, DA, 80, 05, 40, 46, 69, 7C, B1, EF, 40, 0C, 20, A9, A9, 14, E4, 50, 03, 1F, EF, 53, 82, 02, 05, 00, 2E, C5, A3, 62, D0, 02, D3, 1D, B2, 70, 3A, 50, 00, A9, 9E, 4D, 3B, 62, FA, 50, 02, 18, C7, AC, 24, 68, 03, 8B, 5A, 65, 89, AD, A3, BD, 36, 99, 5C, D2, F1, 5E, 5A, 8A, 48, 8B, FA, 30, 9F, 5D, A4, B1, 6F, 2F, 69, 4A, 1B, D3, 2E, 31, B6};

void setup()
{
radio.beginFSK(435.5,1.2,0.3,14.6,0,140,64,0.5,3.3);
radio.setSyncWord(ccsds_sync_word,4);
radio.fixedPacketLengthMode(768);
Serial.begin(9600);
Serial.println("Sending");
  for(int i=0, i < 3, i++){
    byte sendpacket[255];
    memcpy(sendpacket,&imgPacket[((i*256)+1)], 255);
    radio.transmit(sendpacket,255)
  }
}

void loop() {
}
