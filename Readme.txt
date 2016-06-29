连连看

点击相同的图片，就可以消除掉它们。

声音

  太阳神三国杀中声音很流畅亮丽.实现采用开源跨平台的游戏声音引擎fmod,详细内容请参见:http://baike.baidu.com/view/656662.htm.内部将fmod操作封装在Sound类中,这个类很简单,数行代码而已.

class Sound;

static FMOD_SYSTEM *System;
static FMOD_SOUND *BGM;
static FMOD_CHANNEL *BGMChannel;

class Sound{
public:
    Sound(const QString &filename)
	:sound(NULL), channel(NULL)
    {
	FMOD_System_CreateSound(System, filename.toAscii(), FMOD_DEFAULT, NULL, &sound);
    }

    ~Sound(){
	if(sound)
	    FMOD_Sound_Release(sound);
    }

    void play(){
	if(sound){
	    FMOD_RESULT result = FMOD_System_PlaySound(System, FMOD_CHANNEL_FREE, sound, false, &channel);

	    if(result == FMOD_OK){
		FMOD_Channel_SetVolume(channel, 1.000/*Config.EffectVolume*/);
		FMOD_System_Update(System);
	    }
	}
    }

    bool isPlaying() const{
	if(channel == NULL)
	    return false;

	FMOD_BOOL is_playing = false;
	FMOD_Channel_IsPlaying(channel, &is_playing);
	return is_playing;
    }

private:
    FMOD_SOUND *sound;
    FMOD_CHANNEL *channel;
};

在项目启动时初始化fmod:

    FMOD_RESULT result = FMOD_System_Create(&System);

    if(result == FMOD_OK){
	FMOD_System_Init(System, 100, 0, NULL);
    }

在项目结束时释放fmod:

    if(System){
	SoundCache.clear();
	FMOD_System_Release(System);

	System = NULL;
    }

注意,fmod需要6个头文件:fmod.h,fmod_codec.h,fmod_dsp.h,fmod_errors.h,fmod_memoryinfo.h,fmod_output.h,以及一个lib文件fmodex.lib,一个dll文件fmodex.dll.
可以直接将上面的类和8个文件移植到自己的项目中使用,测试通过.唯一需要注意的是Sound对象的析构函数中会结束音频播放,因此如果声明了一个临时变量,需要等待声音播放完毕才能跳出Sound对象的作用域,否则声音未等播放已经结束了.
