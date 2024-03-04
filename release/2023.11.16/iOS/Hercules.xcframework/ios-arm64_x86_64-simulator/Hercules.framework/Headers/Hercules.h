/* ******************************************************************
 *
 * Hercules.h - Hercules Common Header (Distribution)
 *
 * Created by Yongbin Jeong
 * ⓒ Com2uS Platform Corp.
 *
 * 한글 ENG 123 日本語 ♧♡◇♤
 *
 * ******************************************************************/

#ifndef _HERCULES_H_
#define _HERCULES_H_

#if defined(_WIN32)
#define HERCULES_INLINE static
#else
#define HERCULES_INLINE __attribute__((unused)) static // inline: c++ only
#endif

#if defined(__APPLE__)
#include <TargetConditionals.h>
#endif

#if defined(__ANDROID__) || defined(TARGET_OS_IOS) || defined(TARGET_OS_SIMULATOR) || defined(_WIN32)
#define InitializeHercules            H000
#define InitializeHerculesUnity        H001
#define UninitializeHercules        H002
#define HerculesAddVar                H003
#define HerculesRemoveVar            H004
#define HerculesSetVar                H005
#define HerculesGetVar                H006
#define HerculesIsEmulator            H007 // Android
#define HerculesIsRootedDevice        H008 // Android
#define HerculesIsJailbrokenDevice    H009 // iOS
#define HerculesFreeMem                H00A
#define HerculesSetUserId            H00B
#define HerculesTouchEvent            H00C
 //#define HerculesSubmitLog            H00D // Deprecated
 //#define HerculesSetCallback        H00E // Deprecated
 //#define IsOfficialBuild           H00F // Deprecated
#define HerculesGetVersion            H010
#define HerculesIsUnofficialBuild   H011 // iOS
#define HerculesGetFunnels            H012 // Android
#define HerculesIsRepackaged        H013 // Android
#define HerculesSetScreenSize        H014
#define HerculesAddArray            H015
#define HerculesRemoveArray         H016
#define HerculesSetArray            H017
#define HerculesGetArray            H018
#define HerculesOpenAuth            H019
#define HerculesSetGameData            H01A
#define HerculesGetCertHash            H01B // Android
#define HerculesGetCertDesc            H01C
#define HerculesGetTeamId            H01D // iOS
#define HerculesSetPlayerId            H01E
#define HerculesGetApkSignedTime    H01F // Android
#define HerculesAddString           H020
#define HerculesGetString           H021
#define HerculesPrefsGetInt         H022
#define HerculesPrefsGetFloat       H023
#define HerculesPrefsGetString      H024
#define HerculesPrefsSetInt         H025
#define HerculesPrefsSetFloat       H026
#define HerculesPrefsSetString      H027
#define HerculesPrefsHasKey         H028
#define HerculesPrefsDeleteKey      H029
#define HerculesPrefsDeleteAll      H02A
#define HerculesPrefsSave           H02B
#define HerculesGetUniqueInstanceId H02C
#define HerculesSetAppGuardData     H02D
#define HerculesSetDeviceId         H02E
#endif

// DETECT TYPE
#define HERCULES_MEMORY_HACK1        0x1     // 1
#define HERCULES_MEMORY_HACK2        0x2     // 2
#define HERCULES_SPEED_HACK1        0x4     // 3
#define HERCULES_SPEED_HACK2        0x8     // 4
#define HERCULES_PAY_HACK            0x10    // 5
#define HERCULES_EMULATOR            0x20    // 6
#define HERCULES_ROOT_DEV            0x40    // 7
#define HERCULES_JAILBROKEN            0x80    // 8
#define HERCULES_BAD_APP_EXEC        0x100   // 9
#define HERCULES_BAD_APP_INST        0x200   // 10
#define HERCULES_ROOT_APP_EXEC        0x400   // 11
#define HERCULES_INTEGRITY_LIB        0x800   // 12
#define HERCULES_SPEED_HACK3        0x1000  // 13

// Flags for InitializeHercules
#define HERCULES_NONE               0
#define HERCULES_REPORT_ANDROID_ID  1

// Flags for HerculesOpenAuth
#define HERCULES_AUTH_NORMAL        0
#define HERCULES_AUTH_SAVE_ID       1
#define HERCULES_AUTH_SAVE_PW       2
#define HERCULES_AUTH_AUTO_LOGIN    3

#define HERCULES_AUTH_PRESENTATION  1 // iOS

#ifdef __cplusplus
extern "C" {
#endif
    typedef unsigned long long HERCULES;
    typedef void(*HERCULES_DETECT_CALLBACK)(int code, const char *msg);
    typedef void(*HERCULES_AUTH_CALLBACK)(void);

#if defined(__ANDROID__)
    unsigned int InitializeHercules(const char *appName, HERCULES_DETECT_CALLBACK callback, unsigned int flags, void *jniEnv, void *activity);
    void UninitializeHercules(void);
    HERCULES_INLINE unsigned int HerculesIsJailbrokenDevice() { return 0; }
    HERCULES_INLINE unsigned int HerculesIsUnofficialBuild() { return 0; }
    HERCULES_INLINE const char *HerculesGetTeamId() { return ""; }
    unsigned int HerculesIsRootedDevice(void);  // 순정: 0, 루팅: 0이 아닌 값.
    unsigned int HerculesIsEmulator(void);        // 순정: 0, 에뮬레이터: 0이 아닌 값.
    unsigned int HerculesIsRepackaged(void);    // 원본: 0, 리패키징: 1. (디버그 키스토어 등 다른 서명을 할 경우 리패키징으로 표시될 수 있음)
    const char *HerculesGetFunnels(void);        // 설치경로. (예: ADB, Google Play Store, Amazon Appstore, 파일탐색기 등의 앱으로 설치한 경우 그 앱의 패키지명)
    const char *HerculesGetCertHash(void);
    const char *HerculesGetCertDesc(void);
    unsigned int HerculesGetApkSignedTime(void);
    HERCULES_INLINE void HerculesSetAppGuardData(int code, const char *data) { }
#elif defined(TARGET_OS_IOS) || defined(TARGET_OS_SIMULATOR)
    unsigned int InitializeHercules(const char *appName, HERCULES_DETECT_CALLBACK callback, unsigned int flags);
    void UninitializeHercules(void);
    unsigned int HerculesIsJailbrokenDevice(void);   // 순정: 0, 탈옥: 1이상.
    unsigned int HerculesIsUnofficialBuild(void);    // 공식빌드(앱스토어 다운로드): 0 / 비공식(QA,납품,크랙 등): 1, 확인실패: 2이상.
    const char *HerculesGetTeamId(void);
    HERCULES_INLINE unsigned int HerculesIsRootedDevice() { return 0; }
    HERCULES_INLINE unsigned int HerculesIsEmulator() { return 0; }
    HERCULES_INLINE unsigned int HerculesIsRepackaged() { return 0; }
    HERCULES_INLINE const char *HerculesGetFunnels() { return  ""; }
    HERCULES_INLINE const char *HerculesGetCertHash() { return  ""; }
    const char *HerculesGetCertDesc(void);
    HERCULES_INLINE unsigned int HerculesGetApkSignedTime() { return 0; }
    void HerculesSetAppGuardData(int code, const char *data);
#elif defined(_WIN32)
    unsigned int InitializeHercules(const char* appName, HERCULES_DETECT_CALLBACK callback, unsigned int flags, const char* appId, const char* appVersion);
    void UninitializeHercules(void);
    HERCULES_INLINE void HerculesSetAppGuardData(int code, const char *data) { }
#else
    // 기타 플랫폼.
    HERCULES_INLINE unsigned int InitializeHercules(const char *appName, HERCULES_DETECT_CALLBACK callback, unsigned int flags) { return 0; }
    HERCULES_INLINE void UninitializeHercules(void) { }
    HERCULES_INLINE unsigned int HerculesIsJailbrokenDevice() { return 0; }
    HERCULES_INLINE unsigned int HerculesIsUnofficialBuild() { return 0; }
    HERCULES_INLINE const char *HerculesGetTeamId() { return ""; }
    HERCULES_INLINE unsigned int HerculesIsRootedDevice() { return 0; }
    HERCULES_INLINE unsigned int HerculesIsEmulator() { return 0; }
    HERCULES_INLINE unsigned int HerculesIsRepackaged() { return 0; }
    HERCULES_INLINE const char *HerculesGetFunnels() { return  ""; }
    HERCULES_INLINE const char *HerculesGetCertHash() { return  ""; }
    HERCULES_INLINE const char *HerculesGetCertDesc() { return  ""; }
    HERCULES_INLINE unsigned int HerculesGetApkSignedTime() { return 0; }
    HERCULES_INLINE void HerculesSetAppGuardData(int code, const char *data) { }
#endif

#if defined(__ANDROID__) || defined(TARGET_OS_IOS) || defined(TARGET_OS_SIMULATOR) || defined(_WIN32)
    // Android, iOS
    HERCULES HerculesAddVar(const void *data, unsigned int size);
    HERCULES HerculesAddArray(unsigned int elementSize, unsigned int arrayLength);
    HERCULES HerculesAddString(const char *str);
    int HerculesGetVar(HERCULES seq, void *data);
    int HerculesGetArray(HERCULES seq, unsigned int index, void **data);
    char* HerculesGetString(HERCULES seq);  // 리턴된 버퍼는 HerculesFreeMem으로 해제, 혹은 충분한 로컬 버퍼를 확보한 후에 HerculesGetVar를 사용할 수 있음.
    void HerculesSetVar(HERCULES seq, const void *data);
    void HerculesSetArray(HERCULES seq, unsigned int index, const void *data);
    void HerculesRemoveVar(HERCULES seq);
    void HerculesRemoveArray(HERCULES seq);
    void HerculesFreeMem(void *ptr);

    unsigned int HerculesGetVersion(void);
    const char *HerculesGetUniqueInstanceId(void);
    void HerculesSetUserId(const char *userId);
    void HerculesSetPlayerId(const char *playerId);
    void HerculesSetDeviceId(const char *deviceId);
    void HerculesSetScreenSize(unsigned int width, unsigned int height);
    unsigned int HerculesSetGameData(const char *jsonString);
    void HerculesTouchEvent(int x, int y, int flag);

#ifdef __cplusplus
    int HerculesPrefsGetInt(const char *key, int defaultValue = 0);
    float HerculesPrefsGetFloat(const char *key, float defaultValue = 0);
    char* HerculesPrefsGetString(const char *key, const char *defaultValue = "");   // 리턴된 버퍼는 HerculesFreeMem으로 해제.
#else
    int HerculesPrefsGetInt(const char *key, int defaultValue);
    float HerculesPrefsGetFloat(const char *key, float defaultValue);
    char* HerculesPrefsGetString(const char *key, const char *defaultValue);   // 리턴된 버퍼는 HerculesFreeMem으로 해제.
#endif

#if defined(TARGET_OS_IOS) || defined(TARGET_OS_SIMULATOR)
    int HerculesOpenAuth(int loginType, HERCULES_AUTH_CALLBACK callback, int viewType);
#else
    int HerculesOpenAuth(int loginType, HERCULES_AUTH_CALLBACK callback);
#endif

    void HerculesPrefsSetInt(const char *key, int value);
    void HerculesPrefsSetFloat(const char *key, float value);
    void HerculesPrefsSetString(const char *key, const char *value);
    unsigned int HerculesPrefsHasKey(const char *key);
    void HerculesPrefsDeleteKey(const char *key);
    void HerculesPrefsDeleteAll(void);
    void HerculesPrefsSave(void);
#else
    // 기타 플랫폼.
    // HERCULES HerculesAddVar(const void *data, unsigned int size);
    // HERCULES HerculesAddArray(unsigned int elementSize, unsigned int arrayLength);
    // HERCULES HerculesAddString(const char *str);
    // int HerculesGetVar(HERCULES seq, void *data);
    // int HerculesGetArray(HERCULES seq, unsigned int index, void **data);
    // char* HerculesGetString(HERCULES seq);
    // void HerculesSetVar(HERCULES seq, const void *data);
    // void HerculesSetArray(HERCULES seq, unsigned int index, const void *data);
    // void HerculesRemoveVar(HERCULES seq);
    // void HerculesRemoveArray(HERCULES seq);
    // HERCULES_INLINE void HerculesFreeMem(void *ptr) { }

    HERCULES_INLINE unsigned int HerculesGetVersion() { return 0; }
    HERCULES_INLINE const char *HerculesGetUniqueInstanceId() { return "0000-0000-0000"; }
    HERCULES_INLINE void HerculesSetUserId(const char *userId) { }
    HERCULES_INLINE void HerculesSetPlayerId(const char *playerId) { }
    HERCULES_INLINE void HerculesSetDeviceId(const char *deviceId) { }
    HERCULES_INLINE void HerculesSetScreenSize(unsigned int width, unsigned int height) { }
    HERCULES_INLINE unsigned int HerculesSetGameData(const char *jsonString) { return 0; }
    HERCULES_INLINE void HerculesTouchEvent(int x, int y, int flag) { }
    HERCULES_INLINE int HerculesOpenAuth(int loginType, HERCULES_AUTH_CALLBACK callback) { if (callback) callback(); return 0; }

    // int HerculesPrefsGetInt(const char *key, int defaultValue = 0);
    // float HerculesPrefsGetFloat(const char *key, float defaultValue = 0);
    // char* HerculesPrefsGetString(const char *key, const char *defaultValue = "");   // 리턴된 버퍼는 HerculesFreeMem으로 해제.
    // void HerculesPrefsSetInt(const char *key, int value);
    // void HerculesPrefsSetFloat(const char *key, float value);
    // void HerculesPrefsSetString(const char *key, const char *value);
    // unsigned int HerculesPrefsHasKey(const char *key);
    // void HerculesPrefsDeleteKey(const char *key);
    // void HerculesPrefsDeleteAll(void);
    // void HerculesPrefsSave(void);
#endif

#ifdef __cplusplus
}

#include <string>

#if defined(__ANDROID__) || defined(TARGET_OS_IOS) || defined(TARGET_OS_SIMULATOR)
template<typename T> class CHercules
{
private:
    HERCULES m_id;

public:
    CHercules()
    {
        T v;
        m_id = HerculesAddVar(&v, sizeof(v));
    }

    CHercules(const T &v)
    {
        m_id = HerculesAddVar(&v, sizeof(v));
    }

    CHercules(const CHercules<T> &r)
    {
        T v = r.Get();
        m_id = HerculesAddVar(&v, sizeof(v));
    }

    ~CHercules()
    {
        HerculesRemoveVar(m_id);
    }

    inline T Get() const
    {
        T v;
        HerculesGetVar(m_id, &v);
        return v;
    }

    inline void Set(const T &v)
    {
        HerculesSetVar(m_id, &v);
    }

    // obj = value;
    const T& operator =(const T& v)
    {
        Set(v);
        return v;
    }

    // obj = obj;
    inline const T operator =(const CHercules<T> &r)
    {
        T v = r.Get();
        Set(v);
        return v;
    }

    // value = obj;
    inline operator T()
    {
        return Get();
    }
};

class CHerculesString
{
private:
    HERCULES m_id;

public:
    CHerculesString(const char *str)
    {
        m_id = HerculesAddString(str);
    }

    CHerculesString(const CHerculesString &r)
    {
        char *buffer = HerculesGetString(r.m_id);
        if (buffer) {
            m_id = HerculesAddString(buffer);
            HerculesFreeMem(buffer);
        }
        else {
            m_id = HerculesAddString("");
        }
    }

    ~CHerculesString()
    {
        HerculesRemoveVar(m_id);
        m_id = 0;
    }

    // obj = value;
    const char * operator =(const char *str)
    {
        HerculesRemoveVar(m_id);
        m_id = HerculesAddString(str);
        return str;
    }

    // obj = obj;
    inline const CHerculesString operator =(const CHerculesString &r)
    {
        char *buffer = HerculesGetString(r.m_id);
        if (buffer == nullptr)
            return r;
        *this = buffer;
        HerculesFreeMem(buffer);
        return r;
    }

    // value = obj;
    inline operator std::string()
    {
        char *buffer = HerculesGetString(m_id);
        if (buffer == nullptr)
            return "";
        std::string str = buffer;
        HerculesFreeMem(buffer);
        return str;
    }
};
#else
template<typename T> class CHercules
{
private:
    T m_var;

public:
    CHercules()
    {
        m_var = 0;
    }

    CHercules(const T &v)
    {
        m_var = v;
    }

    CHercules(const CHercules<T> &r)
    {
        m_var = r.m_var;
    }

    ~CHercules()
    {
        m_var = 0;
    }

    inline T Get() const
    {
        return m_var;
    }

    inline void Set(const T &v)
    {
        m_var = v;
    }

    // obj = value;
    const T& operator =(const T& v)
    {
        m_var = v;
        return m_var;
    }

    // obj = obj;
    inline const T operator =(const CHercules<T> &r)
    {
        m_var = r.m_var;
        return r;
    }

    // value = obj;
    inline operator T()
    {
        return m_var;
    }
};

class CHerculesString
{
private:
    std::string m_str;

public:
    CHerculesString(const char *str)
    {
        m_str = str;
    }

    CHerculesString(const CHerculesString &r)
    {
        m_str = r.m_str;
    }

    ~CHerculesString()
    {
        m_str.clear();
    }

    // obj = value;
    const char * operator =(const char *str)
    {
        m_str = str;
        return str;
    }

    // obj = obj;
    inline const CHerculesString operator =(const CHerculesString &r)
    {
        m_str = r.m_str;
        return r;
    }

    // value = obj;
    inline operator std::string()
    {
        return m_str;
    }
};
#endif // defined(__ANDROID__) || defined(TARGET_OS_IOS) || defined(TARGET_OS_SIMULATOR)

#endif // __cplusplus
#endif // _HERCULES_H_
