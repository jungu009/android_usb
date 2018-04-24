package cn.jungu.soft.usbdemo.utils;

import android.Manifest;
import android.app.Activity;
import android.content.pm.PackageManager;
import android.os.Build;

import java.util.ArrayList;

/**
 * Created by feichao on 2018/3/27.
 */

public final class CommUtils {

    // 获取权限
    private static boolean isPremission = false;

    public static void setIsPremission(boolean isPremission) {
        CommUtils.isPremission = isPremission;
    }

    /**
     * 检测权限，申请权限
     */
    public static void permissionCheck(Activity context) {
        String[] permissionStrs = {
//                Manifest.permission.CAMERA,
//                Manifest.permission.FLASHLIGHT,
                Manifest.permission.WRITE_EXTERNAL_STORAGE,
//                Manifest.permission.INTERNET,
//                Manifest.permission.ACCESS_NETWORK_STATE,
//            Manifest.permission.SYSTEM_ALERT_WINDOW,
        };

        // 获取必要的权限, 6.0之后动态获取权限
        if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.M && !isPremission) {
            ArrayList<String> permissions = new ArrayList<String>();

            for (String permissionStr : permissionStrs) {
                if (context.checkSelfPermission(permissionStr) != PackageManager.PERMISSION_GRANTED) {
                    permissions.add(permissionStr);
                }
            }

            String[] strs = permissions.toArray(new String[permissions.size()]);
            if(strs != null && strs.length >0) {
                context.requestPermissions(strs, 123);
            }
        }
    }


}
