#ifndef __BASE64
#define __BASE64


// decode a base64 encoded string into the buffer supplied.   
// length should originally contain the maximum size of the buffer.  
// On return, it will contain the actual length of data placed in the outbuffer.
int base64_decode(char *source, unsigned char *output, int *length);




#endif


