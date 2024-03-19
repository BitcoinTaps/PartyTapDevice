#ifndef BITCOIN_H
#define BITCOIN_H

#define MAX_BECH32_SIZE 1000 // for lightning

int bech32_encode(char *output, const char *hrp, const uint8_t *data, size_t data_len);

int convert_bits(uint8_t* out, size_t* outlen, int outbits, const uint8_t* in, size_t inlen, int inbits, int pad);

#endif