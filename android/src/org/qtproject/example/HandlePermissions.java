package org.qtproject.example;

import android.Manifest;
import android.annotation.SuppressLint;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.IntentFilter;
import android.os.Bundle;
import android.hardware.usb.UsbDevice;
import android.hardware.usb.UsbManager;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.graphics.Color;
import android.hardware.usb.UsbDeviceConnection;
import android.util.Log;
import java.util.HashMap;
import java.util.Map;
import java.util.ArrayList;
import android.app.Activity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import java.lang.ref.WeakReference;
import android.util.Log;

public class HandlePermissions {
    private static Context appContext;
    private static final String ACTION_USB_PERMISSION = "com.android.example.USB_PERMISSION";
    public static final String ACTION_USB_ATTACHED = "android.hardware.usb.action.USB_DEVICE_ATTACHED";
    public static final String ACTION_USB_DETACHED = "android.hardware.usb.action.USB_DEVICE_DETACHED";

    public static native void sendParamsToCpp(String usbfsPath, int fd, int vid, int pid);

    public void setupUSB(UsbDevice usbDevice) {

        UsbManager manager = (UsbManager) appContext.getSystemService(Context.USB_SERVICE);
        UsbDeviceConnection connection = manager.openDevice(usbDevice);

        int fd = connection.getFileDescriptor();
        String usbfsPath = usbDevice.getDeviceName();
        int vid = usbDevice.getVendorId();
        int pid = usbDevice.getProductId();

        Log.i("TAG","usbfsPath:" + usbfsPath);
        Log.i("TAG","fd:" + fd);
        Log.i("TAG","vid:" + vid);
        Log.i("TAG","pid:" + pid);

        sendParamsToCpp(usbfsPath,fd, vid , pid);
    }

    // https://github.com/tzyhj/usbAndroid/blob/7e14a872592a1326e0f11e10ff3019ec038d5324/app/src/main/java/com/qc/usbandroid/UsbService.java
    private final BroadcastReceiver usbReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context arg0, Intent intent) {
            if (intent.getAction().equals(ACTION_USB_PERMISSION)) {
                boolean granted = intent.getExtras().getBoolean(UsbManager.EXTRA_PERMISSION_GRANTED);
                if (granted)
                {
                    // User accepted our USB connection. Try to open the device as a serial port
                    UsbDevice device = intent.getParcelableExtra(UsbManager.EXTRA_DEVICE);
                    setupUSB(device);
                }
                else
                {
                    // User not accepted our USB connection. Send an Intent to the Main Activity
                    Log.i("TAG","--------------------------- not granted ---------------------------");
                }
            }
            else if (intent.getAction().equals(ACTION_USB_ATTACHED))
            {
                // A USB device has been attached. Try to open it as a Serial port
                Log.i("TAG","--------------------------- ACTION_USB_ATTACHED ---------------------------");
            }
            else if (intent.getAction().equals(ACTION_USB_DETACHED))
            {
                Log.i("TAG","--------------------------- ACTION_USB_DETACHED ---------------------------");
                // Usb device was disconnected. send an intent to the Main Activity
            }
        }
    };

    public void registerServiceBroadcastReceiver(Context context) {
        IntentFilter filter = new IntentFilter();
        filter.addAction(ACTION_USB_PERMISSION);
        context.registerReceiver(usbReceiver, filter);

        Log.i("TAG", "Registered broadcast receiver");
    }

    // https://github.com/tzyhj/usbAndroid/blob/7e14a872592a1326e0f11e10ff3019ec038d5324/app/src/main/java/com/qc/usbandroid/UsbService.java
    public static void checkHWPermission(Activity context) {
        UsbManager manager = (UsbManager) context.getSystemService(Context.USB_SERVICE);
        HashMap<String, UsbDevice> usbDevices = manager.getDeviceList();

        if (!usbDevices.isEmpty()) {
            for (Map.Entry<String, UsbDevice> entry : usbDevices.entrySet()) {
                UsbDevice device = entry.getValue();
                int deviceVID = device.getVendorId();
                int devicePID = device.getProductId();

                if (deviceVID == 0x1D50 && devicePID == 0x6089) {
                    // There is a device connected to our Android device. Try to open it as a Serial Port.
                    PendingIntent mPendingIntent = PendingIntent.getBroadcast(context, 0, new Intent(ACTION_USB_PERMISSION), 0);


                    manager.requestPermission(device, mPendingIntent);
                    // requestUserPermission(manager, device);

                }
                else {
                    // make device and connection null
                }
            }
         }
         else
         {
             // There is no USB devices connected. Send an intent to MainActivity
         }
    }

    public static void checkStoragePermission(Activity context, String s) {
        appContext = context;
        if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.M) {
            int permissionResult = context.checkSelfPermission(Manifest.permission.WRITE_EXTERNAL_STORAGE);

            if (permissionResult != PackageManager.PERMISSION_GRANTED) {
                context.requestPermissions( new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE}, 123);
            }
            else {
                if (ActivityCompat.checkSelfPermission(context,  Manifest.permission.WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED) {
                }
                else {
                    checkHWPermission(context);
                }
            }
        }else{
        }
    }
}
