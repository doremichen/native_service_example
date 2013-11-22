// File: ExampleClient.cpp  
#define LOG_TAG "ExampleClient"
#include <cutils/log.h>

#include <binder/IServiceManager.h>  
#include <binder/IPCThreadState.h>  
#include "ExampleClient.h"  
  
namespace android  
{  
    sp<IBinder> binder;  
    void ExampleClient::add100(int n)  
    {  
        getExampleService();  
        Parcel data, reply;  
        int answer;  
          
        data.writeInt32(getpid());  
        data.writeInt32(n);  
        ALOGE("BpExampleService::create remote()->transact()/n");  
        binder->transact(0, data, &reply);  
        answer = reply.readInt32();  
        printf("answner=%d/n", answer);      
        return;  
    }  
  
    const void ExampleClient::getExampleService()  
    {  
        sp<IServiceManager> sm = defaultServiceManager();  
        binder = sm->getService(String16("altek.example.service"));  
        ALOGE("Example::getExampleService %p/n",sm.get());  
        if (binder == 0) {  
            ALOGW("ExampleService not published, waiting...");  
        return;  
        }  
    }  
}; //namespace  
  
using namespace android;  
  
int main(int argc, char** argv)  
{  
    ExampleClient* p = new ExampleClient();  
    p->add100(1);  
    return 0;  
}  