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
    "<style type=\"text/css\">"
      ".b {width:95%; height:95%;}"
      ".g {color:lightgrey}"
    "</style>"
  "</head>"
  "<p>Klicken auf die Bilder &auml;ndert die Helligkeit des Feuers</p>"
  "<body><table border=\"3px\">"
    "<tr>"
      "<td align=\"center\" valign=\"middle\" width=\"200px\">"
        "<input type=\"image\" src=\"http://andreas-wassmer.ch/campfire_big.jpg\" style=\"width:150px;\" onclick=\"set('0')\" value=\"Feuer anz&uuml;nden\"/>"
        "<p>Feuer st&auml;rker</p>"
      "</td>"
	  "</tr>"
	  "<tr>"
      "<td align=\"center\" valign=\"middle\" width=\"200px\">"
        "<input type=\"image\" src=\"http://andreas-wassmer.ch/campfire_small.jpg\" style=\"width:150px;\" onclick=\"set('1')\" value=\"Feuer dimmen\"/>"
        "<p>Feuer schw&auml;cher</p>"
      "</td>"
    "</tr>"
    "</table>"
      "<p>HTML geliefert von einem Arduino-Board, Zugriff &uuml;ber <a href=\"http://www.yaler.org/\">Yaler</a>.</p>"
  "</body></html>";

