/******************************************
 ** yalerapi
 **
 ** API to access the yaler service. This code is 
 ** taken from yaler example, available from yaler.org
 **
 ** I changed some lines in function parseRequestChar() in order
 ** to set the LED intensity.
 ********************************************/

const int dIntensity = 150;

byte byteFromHexChar (char ch) {
  byte result;
  if ((ch >= '0') && (ch <= '9')) {
    result = ch - '0';
  } else if ((ch >= 'a') && (ch <= 'f')) {
    result = 10 + (ch - 'a');
  } else if ((ch >= 'A') && (ch <= 'F')) {
    result = 10 + (ch - 'A');
  } else {
    result = 0;
  }
  return result;
}

void parseRequestChar (char ch) {

  // PUT /<yaler-id>/led/ff0000 ... \r\n\r\n
  // GET /<yaler-id>/led ... \r\n\r\n

  // the following lines contain code that was not in the example release
  // originally by yaler.
  //Serial.print("count: "); Serial.print(count); Serial.print(" ch = "); Serial.println(ch);
  if (count == 0) {
    isPut = ch == 'P';
  } else if ((count >= ledUriOffset) && (count < ledUriOffset + 1)) {
    if (ch == '0') {
      fireIntensity = dIntensity;
    } else if (ch == '1') {
      fireIntensity = 0;
    } else if (ch == '2') {
      fireIntensity = fireIntensity + dIntensity;
      if (fireIntensity >= 250) {
        fireIntensity = 250;
      }
    } else if (ch == '3') {
      fireIntensity = fireIntensity - dIntensity;
      if (fireIntensity < 0) {
        fireIntensity = 0;
      }

    }
    Serial.print("fire intensity = "); Serial.println(fireIntensity);
  }

  if (state == RECEIVING) {
    if (ch == '\r') {
      state = READ_CR;
    }
  } else if (state == READ_CR) {
    // assert ch == '\n'
    state = READ_CRLF;
  } else if (state == READ_CRLF) {
    if (ch == '\r') {
      state = READ_CRLFCR;
    } else {
      state = RECEIVING;
    }
  } else if (state == READ_CRLFCR) {
    // assert ch == '\n'
    state = DONE;
  }
  count++;

}

void parseYalerResponseChar (char ch) {
  // HTTP/1.1 101 ... \r\n\r\n
  // HTTP/1.1 204 ... \r\n\r\n
  if (yalerState == YALER_RECEIVING) {
    if (yalerCount == 9) { // sizeof("HTTP/1.1 ?") - 1;
      if (ch == '1') { // 101
        yalerState = YALER_UPGRADING;
      } else { // 204
        // assert ch == '2'
        yalerState = YALER_TIMEOUT;
      }
    }
  } else if (yalerState == YALER_UPGRADING) {
    if (yalerCount == 56) { // sizeof("HTTP/1.1 101 ... \r\n\r\n") - 1
      yalerState = YALER_UPGRADED;
    }
  }
  yalerCount++;
  
}

void sendYalerPostRequest (EthernetClient c) {
  c.print("POST /");
  c.print(yalerId);
  c.println(" HTTP/1.1");
  c.println("Upgrade: PTTH/1.0");
  c.println("Connection: Upgrade");
  c.println("Host: www.yaler.net");
  c.print(contentLength);
  c.println("0");
  c.println();
  c.flush();
}

void receiveYalerResponse (EthernetClient c) {
  yalerCount = 0;
  yalerState = YALER_RECEIVING;
  while (c.connected() && (c.available() <= 0)) {} // Yaler sends 101 or 204 in < 30s
  Serial.print("**** Yaler response:");
  while (c.connected() && (c.available() > 0) &&
    (yalerState != YALER_UPGRADED) &&
    (yalerState != YALER_TIMEOUT)) 
  {
    char ch = c.read();
    Serial.print(ch);
    parseYalerResponseChar(ch);
  }
}

void sendPutResponse (EthernetClient c) {
  c.println(http200);
  c.println(contentTypeTextPlain);
  c.print(contentLength);
  c.println("3");
  c.println(connectionClose);
  c.println();
  c.print("200");
  c.flush();
}

void sendGetResponse (EthernetClient c) {
  c.println(http200);
  c.println(contentTypeTextHtml);
  c.print(contentLength);
  c.println(htmlLength);
  c.println(connectionClose);
  c.println();
  c.print(html);
  c.flush();
}

void receiveRequest (EthernetClient c) {
  count = 0;
  ledIndex = 0;
  state = RECEIVING;
  
  //if (!c.connected()) Serial.println("!!! not connected !!!");
  while (c.connected() && (c.available() > 0) && (state != DONE)) {
    char ch = c.read();
    //Serial.print(ch);
    //Serial.println("   *** RARSING REQUEST ***");
    parseRequestChar(ch);
  }
  Serial.println("*** DONE ***");
}

