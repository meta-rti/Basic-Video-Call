//  Meta SDK
//
//  Copyright (c) 2019 Meta.io. All rights reserved.
//
#ifndef META_SERVICE_H
#define META_SERVICE_H

#include "MetaBase.h"

namespace meta {
namespace rtc {
class IRtcEngine;
}
namespace rtm {
class IRtmService;
}
namespace base {

struct MetaServiceContext {};

class IMetaService {
 protected:
  virtual ~IMetaService() {}

 public:
  META_CPP_API static void release();

  /** Initializes the engine.

@param context RtcEngine context.
@return
- 0: Success.
- < 0: Failure.
*/
  virtual int initialize(const MetaServiceContext& context) = 0;

  /** Retrieves the SDK version number.
   * @param build Build number.
   * @return The current SDK version in the string format. For example, 2.4.0
   */
  virtual const char* getVersion(int* build) = 0;

  virtual rtm::IRtmService* createRtmService() = 0;
};

}  // namespace base
}  // namespace meta

/** Gets the SDK version number.

 @param build Build number of the Meta SDK.
 @return
 - 0: Success.
 - < 0: Failure.
*/
META_API const char* META_CALL getMetaSdkVersion(int* build);

/**
 * Creates the RtcEngine object and returns the pointer.
 * @param err Error code
 * @return returns Description of the error code
 */
META_API const char* META_CALL getMetaSdkErrorDescription(int err);

/**
 * Creates the Meta Service object and returns the pointer.
 * @return returns Pointer of the Meta Service object
 */
META_API meta::base::IMetaService* META_CALL createMetaService();

META_API int META_CALL
setMetaSdkExternalSymbolLoader(void* (*func)(const char* symname));

#endif  // META_SERVICE_H
