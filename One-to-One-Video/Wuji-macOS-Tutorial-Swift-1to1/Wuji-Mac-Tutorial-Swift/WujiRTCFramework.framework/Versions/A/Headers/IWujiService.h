//  Wuji SDK
//
//  Copyright (c) 2019 Wuji.io. All rights reserved.
//
#ifndef WUJI_SERVICE_H
#define WUJI_SERVICE_H

#include "WujiBase.h"

namespace wuji {
namespace rtc {
class IRtcEngine;
}
namespace rtm {
class IRtmService;
}
namespace base {

struct WujiServiceContext {};

class IWujiService {
 protected:
  virtual ~IWujiService() {}

 public:
  WUJI_CPP_API static void release();

  /** Initializes the engine.

@param context RtcEngine context.
@return
- 0: Success.
- < 0: Failure.
*/
  virtual int initialize(const WujiServiceContext& context) = 0;

  /** Retrieves the SDK version number.
   * @param build Build number.
   * @return The current SDK version in the string format. For example, 2.4.0
   */
  virtual const char* getVersion(int* build) = 0;

  virtual rtm::IRtmService* createRtmService() = 0;
};

}  // namespace base
}  // namespace wuji

/** Gets the SDK version number.

 @param build Build number of the Wuji SDK.
 @return
 - 0: Success.
 - < 0: Failure.
*/
WUJI_API const char* WUJI_CALL getWujiSdkVersion(int* build);

/**
 * Creates the RtcEngine object and returns the pointer.
 * @param err Error code
 * @return returns Description of the error code
 */
WUJI_API const char* WUJI_CALL getWujiSdkErrorDescription(int err);

/**
 * Creates the Wuji Service object and returns the pointer.
 * @return returns Pointer of the Wuji Service object
 */
WUJI_API wuji::base::IWujiService* WUJI_CALL createWujiService();

WUJI_API int WUJI_CALL
setWujiSdkExternalSymbolLoader(void* (*func)(const char* symname));

#endif  // WUJI_SERVICE_H
