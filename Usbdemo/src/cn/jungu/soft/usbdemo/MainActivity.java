package cn.jungu.soft.usbdemo;

import java.util.HashMap;
import java.util.Iterator;

import android.app.Activity;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.PackageManager;
import android.hardware.usb.UsbDevice;
import android.hardware.usb.UsbDeviceConnection;
import android.hardware.usb.UsbManager;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;
import cn.jungu.soft.usbdemo.utils.CommUtils;

public class MainActivity extends Activity implements OnClickListener{

	
	static {
        System.loadLibrary("myusb");
    }
	
	public static final String ACTION_USB_PERMISSION = "cn.jungu.soft.USB_PERMISSION";
	public static final String TAG = "MainActivity_usb";
	
	private TextView txt;
	private Button btn;
	
	/**
     * 权限处理结果
     */
	@Override
	public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
//		super.onRequestPermissionsResult(requestCode, permissions, grantResults);
		CommUtils.setIsPremission(true);
        if(requestCode == 123) {
            for(int i = 0; i < grantResults.length; i++) {
                if(grantResults[i] != PackageManager.PERMISSION_GRANTED) {
                    CommUtils.setIsPremission(false);
                    Toast.makeText(MainActivity.this, permissions[i] + " 授权失败", Toast.LENGTH_SHORT).show();
                }
            }
        }
	}
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		CommUtils.permissionCheck(this);
		setContentView(R.layout.activity_main);
		
		initView();
		
		initUSB();
	}
	
    @Override
    protected void onStart() {
    	super.onStart();
    	
    	//For checking when the device is detached
        IntentFilter filter_Det = new IntentFilter();
        filter_Det.addAction(UsbManager.ACTION_USB_DEVICE_DETACHED);
        registerReceiver(mUsbReceiver_Det, filter_Det);

        // usb 权限处理广播接收
        IntentFilter filter = new IntentFilter(ACTION_USB_PERMISSION);
        registerReceiver(mUsbReceiver, filter);
    }
    
	
    @Override
    protected void onResume() {
    	super.onResume();

    	initDevice();
    	
    }
    
    
    private void initDevice() {
    	int var = USBTools.connectDevice();
    	txt.setText("" + var);
    }
    
	private void initView() {
		txt = (TextView)findViewById(R.id.hello);
		btn = (Button)findViewById(R.id.btn);
		btn.setOnClickListener(this);
	}


	private void initUSB() {
        UsbManager manager = (UsbManager) getSystemService(Context.USB_SERVICE);
        // Device was not found by intent, try by enumeration
//        device = UsbTools.getDeviceByEnumeration(manager);
        UsbDevice mDevice = null;

        HashMap<String, UsbDevice> deviceList = manager.getDeviceList();
        Iterator<UsbDevice> deviceIterator = deviceList.values().iterator();
        UsbDevice device = null;
        while (deviceIterator.hasNext()) {
            device = deviceIterator.next();
            if (device != null && device.getVendorId() == 1155) {
                mDevice = device;
                break; // 目前只选择一个设备
            }
        }
        
        if(null == mDevice) {
        	txt.setText("没有找到设备");
        	return;
        }
        
        // 申请权限
        PendingIntent mPermissionIntent = PendingIntent.getBroadcast(this, 0, new Intent(ACTION_USB_PERMISSION), 0);
        manager.requestPermission(mDevice, mPermissionIntent);
        
        // usb 设备声明接口  独占设备
        UsbDeviceConnection connection = manager.openDevice(mDevice);
        int fd = connection.getFileDescriptor();
        if (fd == -1)
            Log.d("Interface", "Not Claimed");
        else Log.d("Interface", "Claimed");
        connection.claimInterface(mDevice.getInterface(0), true);    // Claim interface to read/write to device
        
    }
	
	
	@Override
	public void onClick(View v) {
			
		if(v.getId() == R.id.btn) {
			
			initDevice();
			
		}
	
	}
	
	private BroadcastReceiver mUsbReceiver_Det = new BroadcastReceiver() {
        public void onReceive(Context context_Det, Intent intent_Det) {
            String action = intent_Det.getAction();
            if (action.equals(UsbManager.ACTION_USB_DEVICE_DETACHED)) {
                System.exit(0); // usb拔出 关闭程序
            }
        }
    };
	
    private BroadcastReceiver mUsbReceiver = new BroadcastReceiver() {

        public void onReceive(Context context, Intent intent) {
            String action = intent.getAction();
            if (ACTION_USB_PERMISSION.equals(action)) {
                synchronized (this) {
                    UsbDevice device = (UsbDevice) intent.getParcelableExtra(UsbManager.EXTRA_DEVICE);

                    if (intent.getBooleanExtra(UsbManager.EXTRA_PERMISSION_GRANTED, false)) {
                        if (device != null) {
                            Log.d(TAG, "Android has granted permission to use Apollo");
                        }
                    } else {
                        Log.d(TAG, "Android has denied permission to use Apollo" + device);
                    }
                }
            }
        }
    };
	
	
}
