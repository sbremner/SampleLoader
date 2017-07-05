#include "API.h"

// Main entry point for the malware coding to begin
// (Called after the main is setup and API is configured)
int execution(API * api);

// This will take a raw payload and execute it
BOOL RunPayload(API * api, PVOID Payload, DWORD dwPayloadLength);