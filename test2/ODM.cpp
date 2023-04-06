#include "soapH.h"
#include "soapStub.h"
#include <iostream>

int main(int argc, char **argv) {
    // Create a gSOAP context and set the endpoint and SOAP action for device discovery
    struct soap *soap = soap_new();
    const char *endpoint = "http://192.168.1.100/onvif/device_service";
    const char *action = "http://www.onvif.org/ver10/device/wsdl/GetSystemDateAndTime";

    // Create a GetSystemDateAndTime request and receive the response
    struct _tds__GetSystemDateAndTime req;
    struct _tds__GetSystemDateAndTimeResponse resp;
    soap_default___tds__GetSystemDateAndTime(soap, &req);
    if (soap_write___tds__GetSystemDateAndTime(soap, &endpoint, &action, &req, &resp) == SOAP_OK) {
        // Print the system date and time of the device
        auto timezone = resp.SystemDateAndTime->TimeZone->TZ;
        auto datetime = resp.SystemDateAndTime->UTCDateTime;
        std::cout << "System date and time:" << std::endl
                  << "  Timezone: " << timezone << std::endl
                  << "  Date: " << datetime->Date << std::endl
                  << "  Time: " << datetime->Time << std::endl;
    } else {
        std::cerr << "Error: " << soap->error << std::endl;
    }

    // Clean up and exit
    soap_destroy(soap);
    soap_end(soap);
    soap_free(soap);
    return 0;
}
