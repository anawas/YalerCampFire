/******************************************
 ** webdefs.h
 **
 ** Definition of variables and constants
 ** for the functions in the yaler API
 **
 ** This code is taken from yaler example
 **
 ********************************************/

const char http200[] = "HTTP/1.1 200 OK";
const char contentLength[] = "Content-Length: ";
const char connectionClose[] = "Connection: close";
const char contentTypeTextHtml[] = "Content-Type: text/html";
const char contentTypeTextPlain[] = "Content-Type: text/plain";

const byte RECEIVING = 0, READ_CR = 1, READ_CRLF = 2, READ_CRLFCR = 3, DONE = 4;
const byte YALER_RECEIVING = 0, YALER_UPGRADING = 1, YALER_TIMEOUT = 2, YALER_UPGRADED = 3;

const char yalerId[] = "gsiot-3yzj-r9dq"; // My yaler account
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0x18, 0x32 }; // My Arduino
byte server[] = { 46, 137, 106, 125 }; // try.yaler.net

boolean isPut;
int count;
byte ledIndex;
byte ledUriOffset;
int htmlLength;

byte state;
byte yalerState;
int yalerCount;

