// File: ExampleService.h  
#ifndef ANDROID_EXAMPLE_SERVICE_H  
#define ANDROID_EXAMPLE_SERVICE_H  
#include <utils/threads.h>  
#include <utils/RefBase.h>  
#include <binder/IInterface.h>  
#include <binder/BpBinder.h>  
#include <binder/Parcel.h>  
  
namespace android {  
    class ExampleService : public BBinder  
    {  
        mutable Mutex mLock;  
        int32_t mNextConnId;  
        public:  
            static int instantiate();  
            ExampleService();  
            virtual ~ExampleService();  
            virtual status_t onTransact(uint32_t, const Parcel&, Parcel*, uint32_t);  
    };  
}; //namespace  
#endif  