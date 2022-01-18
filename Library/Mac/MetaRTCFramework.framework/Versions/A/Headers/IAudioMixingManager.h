#ifndef META_AUDIO_MIXING_MGR_INTERFACE_H
#define META_AUDIO_MIXING_MGR_INTERFACE_H

#include <map>
#include <vector>

namespace meta {
namespace rtc {

class IAudioMixingManager {
 public:
  static std::unique_ptr<IAudioMixingManager> create();

 public:
  virtual ~IAudioMixingManager() {}

  //设置mix后的输出参数
  virtual int setOutputParameters(int outputSampleRate, int outputChannels) = 0;

  virtual int addSource(int ssrc, int inputSampleRate, int inputChannels) = 0;

  virtual int AddRecordedData(int32_t ssrc, const void* data, int32_t size) = 0;

  virtual int removeSource(int ssrc) = 0;

  //返回值为字节数,每次调用只混音各个source中10ms的数据
  virtual int mix(void* outputBuffer) = 0;

  //以本方法调用间隔为周期，计算此周期内ssrc对应的音频能量
  virtual int getAudioVolume(int32_t ssrc) = 0;
};

}  // namespace rtc

}  // namespace meta

#endif  // META_MEDIA_ENGINE_H
