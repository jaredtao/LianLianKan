������
��������

  ̫��������ɱ����������������.ʵ�ֲ��ÿ�Դ��ƽ̨����Ϸ��������fmod,��ϸ������μ�:http://baike.baidu.com/view/656662.htm.�ڲ���fmod������װ��Sound����,�����ܼ�,���д������.

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

����Ŀ����ʱ��ʼ��fmod:

    FMOD_RESULT result = FMOD_System_Create(&System);

    if(result == FMOD_OK){
	FMOD_System_Init(System, 100, 0, NULL);
    }

����Ŀ����ʱ�ͷ�fmod:

    if(System){
	SoundCache.clear();
	FMOD_System_Release(System);

	System = NULL;
    }

ע��,fmod��Ҫ6��ͷ�ļ�:fmod.h,fmod_codec.h,fmod_dsp.h,fmod_errors.h,fmod_memoryinfo.h,fmod_output.h,�Լ�һ��lib�ļ�fmodex.lib,һ��dll�ļ�fmodex.dll.
����ֱ�ӽ���������8���ļ���ֲ���Լ�����Ŀ��ʹ��,����ͨ��.Ψһ��Ҫע�����Sound��������������л������Ƶ����,������������һ����ʱ����,��Ҫ�ȴ�����������ϲ�������Sound�����������,��������δ�Ȳ����Ѿ�������.
