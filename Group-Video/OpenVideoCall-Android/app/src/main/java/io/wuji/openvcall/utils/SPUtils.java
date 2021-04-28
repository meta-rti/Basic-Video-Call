package io.wuji.openvcall.utils;

import com.tencent.mmkv.MMKV;

import java.util.HashSet;
import java.util.Set;

import io.wuji.openvcall.WJApplication;

/**
 * @author chunping
 * @time 2021/4/9 6:19 PM
 * @describe describe
 */
public class SPUtils {
    private MMKV mSharedPreferences ;

    private SPUtils() {
        mSharedPreferences = MMKV.mmkvWithID("wuji_openvideocall_sp");
    }

    public static SPUtils getInstance() {
        return SPUtilsHolder.HOLDER;
    }

    private static class SPUtilsHolder {
        public static final SPUtils HOLDER = new SPUtils();
    }

    public boolean contains(String key) {
        return mSharedPreferences.containsKey(key);
    }


    public void setInt(String key, int value) {
        mSharedPreferences.putInt(key, value);
    }


    public int getInt(String key, int defaultValue) {
        return mSharedPreferences.getInt(key, defaultValue);
    }


    public void setStringSet(String key, Set<String> value) {
        mSharedPreferences.putStringSet(key, value);
    }


    public Set<String> getStringSet(String key) {
        return mSharedPreferences.getStringSet(key, new HashSet<>());
    }


    public void setString(String key, String value) {
        mSharedPreferences.putString(key, value);
    }


    public String getString(String key, String defaultValue) {
        return mSharedPreferences.getString(key, defaultValue);
    }


    public void setLong(String key, long value) {
        mSharedPreferences.putLong(key, value);
    }


    public Long getLong(String key, Long defaultValue) {
        return mSharedPreferences.getLong(key, defaultValue);
    }


    public void setBoolean(String key, Boolean value) {
        mSharedPreferences.putBoolean(key, value);
    }


    public Boolean getBoolean(String key, Boolean defValue) {
        return mSharedPreferences.getBoolean(key, defValue);
    }


    public void setFloat(String key, Float value) {
        mSharedPreferences.putFloat(key, value);
    }


    public Float getFloat(String key, Float defValue) {
        return mSharedPreferences.getFloat(key, defValue);
    }


    public void removeKey(String key) {
        mSharedPreferences.remove(key);
    }


    public void removeAll() {
        mSharedPreferences.clearAll();
    }
}
