/******************************************
 ** yalerskript.h
 **
 ** This script gets uploaded to the yaler service. It is
 ** based the one in the yaler example.
 ** The length is limited by the Arduino RAM. The size of
 ** this script is close to that limit.
 **
 ** It reads two images from my own website andreas-wassmer.ch
 ********************************************/
 
const char html[] =
  "<html><head>"
   "<meta charset=\"utf-8\">"
   "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1, maximum-scale=1\">"
    "<script type=\"text/javascript\">"
    "var r;"
    "try {"
    "r = new XMLHttpRequest();"
     "} catch (e) {"
     "try {"
     "r = new ActiveXObject('Microsoft.XMLHTTP');"
     "} catch (e) {}"
     "}"
     "function set (c) {"
     "r.open('PUT', './led/' + c, false);"
     "r.send(null);"
     "}"
     "</script>"
  "</head>"
  "<p>Klicken auf die Bilder schaltet Feuer ein oder aus.</p>"
  "<body><table border=\"5px\">"
    "<tr>"
      "<td align=\"center\" valign=\"middle\" width=\"125px\">"
        "<input type=\"image\" src=\"http://andreas-wassmer.ch/campfire_on.jpg\" width=\"100%\" onclick=\"set('0')\" value=\"an\"/>"
        "<p>Feuer anz&uuml;nden</p>"
      "</td>"
      "<td align=\"center\" valign=\"middle\" width=\"125px\">"
        "<input type=\"image\" src=\"http://andreas-wassmer.ch/campfire_off.jpg\" width=\"100%\" onclick=\"set('1')\" value=\"aus\"/>"
        "<p>Feuer l&ouml;schen</p>"
      "</td>"
      "</tr>"
    "</table>"
      "<p>HTML von einem Arduino-Board, Zugriff &uuml;ber <a href=\"http://www.yaler.org/\">Yaler</a>.</p>"
  "</body></html>";

