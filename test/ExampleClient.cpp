// File: ExampleClient.cpp  
#define LOG_TAG "ExampleClient"
#include <cutils/log.h>

#include <binder/IServiceManager.h>  
#include <binder/IPCThreadState.h>  
#include "ExampleClient.h"  
  
#define __unused__ __attribute__((unused))  

namespace android  
{  
    sp<IBinder> BpExampleSevice;  
    void ExampleClient::add100(int n)  
    {  
        getExampleService();  
        Parcel data, reply;  
        int answer;  
          
        data.writeInt32(getpid());  
        data.writeInt32(n);  
        ALOGE("BpExampleService::create remote()->transact()/n");  
        BpExampleSevice->transact(0, data, &reply);  
        answer = reply.readInt32();  
        printf("answner=%d/n", answer);      
        return;  
    }  
  
    void ExampleClient::getExampleService()  
    {  
        sp<IServiceManager> sm = defaultServiceManager();  
        BpExampleSevice = sm->getService(String16("example.native.service"));  
        ALOGE("Example::getExampleService %p/n",sm.get());  
        if (BpExampleSevice == 0) {  
            ALOGW("ExampleService not published, waiting...");  
        return;  
        }  
    }  
}; //namespace  
  
using namespace android;  
  
int main(__unused__ int argc, __unused__ char** argv)  
{  
    ExampleClient* p = new ExampleClient();  
    p->add100(1);  
    return 0;  
}  