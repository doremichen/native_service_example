// File: ExampleService.cpp
#define LOG_TAG "ExampleService"
#include <cutils/log.h>
  
#include "ExampleService.h"  
#include <binder/IServiceManager.h>  
#include <binder/IPCThreadState.h>  

namespace android {  
  
    static struct sigaction oldact;  
    static pthread_key_t sigbuskey;  
      
    int ExampleService::instantiate()  
    {  
        ALOGE("ExampleService instantiate");  
        //  
        int r = defaultServiceManager()->addService(String16("altek.example.service"), new ExampleService());  
        ALOGE("ExampleService r = %d/n", r);  
        return r;  
    }  
  
    ExampleService::ExampleService()  
    {   
        ALOGV("ExampleService created");  
        mNextConnId = 1;  
        pthread_key_create(&sigbuskey, NULL);  
    }  
  
    ExampleService::~ExampleService()  
    {  
        pthread_key_delete(sigbuskey);  
        ALOGV("ExampleService destroyed");  
    }  
 
    status_t ExampleService::onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)  
    {  
        switch(code)  
        {  
            case 0: {  
                pid_t pid = data.readInt32();  
                int num   = data.readInt32();  
                num = num + 100;  
                reply->writeInt32(num);  
                return NO_ERROR;  
                }  
                break;  
            default:  
                return BBinder::onTransact(code, data, reply, flags);  
        }  
    }  
}; //namespace  