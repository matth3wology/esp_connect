#ifndef _H_WEBSITE_H_
#define _H_WEBSITE_H_

const char* web_header = 
"""<!DOCTYPE html><html>\
<head>\
<title>SNEED IO - STATION 1</title>\
<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
<link rel=\"icon\" href=\"data:,\">\
<style>\
    html { font-family: Verdana, Geneva, Tahoma, sans-serif; display: inline-block; margin: 0px auto; text-align: center;}\
    body{background-color: #212121; color: #efefef;}\
    .button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;\
        text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}\
    .button2 {background-color: #77878A;}\
</style>\
</head>\
<body>\
    <h1>Robotic Arm Control</h1>""";

const char* web_endtag = """</body>""";

#endif