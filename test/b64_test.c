#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <base64.h>

char *test_str = "VGhlcmUgYXJlIHNldmVyYWwgd2ViLWJhc2VkIEJhc2U2NCBlbmNvZGVycy9kZWNvZGVycywgYW5kIG9ubHkgYSBjb3VwbGUgSmF2YXNjcmlwdCBlbmNvZGVycy9kZWNvZGVycy4gVGhlIEphdmFzY3JpcHQgb25lcyB3ZXJlIGFsbCByYXRoZXIgY29tcGxleCAocmVsYXRpdmVseSBzcGVha2luZyksIGFuZCBub25lIHVzZWQgdGhlIGZ1bmN0aW9ucyBmb3Igd29ya2luZyB3aXRoIEJhc2U2NCB0aGF0IGFyZSBidWlsdCBpbnRvIHRoZSBKYXZhU2NyaXB0IGVuZ2luZSBpbiBOZXRzY2FwZSBDb21tdW5pY2F0b3IgNCx4IGFuZCB1cCwgYW5kIE1vemlsbGEuIFRoaXMgdXNlcyB0aG9zZSBidWlsdCBpbiBmdW5jdGlvbnMsIGFuZCBzbyBpdCBkb2Vzbid0IHdvcmsgaW4gSW50ZXJuZXQgRXhwbG9yZXIsIG9yIE9wZXJhLiA=";


int main(void) 
{
	int rr;
	char *full;
	int length;

	
	length = strlen(test_str)+200;
	full = malloc(length);

	printf("buffer length: %d\n", length);

	rr = base64_decode(test_str, full, &length);

	full[length] = 0;
	printf("rr=%d\n", rr);
	printf("length=%d\n", length);
	printf("output='%s'\n", full);
	printf("strlen(output)=%d\n", strlen(full));

	free(full);

	return 0;
}
