package com.glasssix.Gaiulinya;

public class Gaiulinya {
	static {
		System.loadLibrary("Gaiulinya");
	}
	
	private long mObject;
	
	public Gaiulinya(int device) {
		init(device);
	}
	
	public static native String getVersion();
	public native float[][] ForwardbyMetaData(byte[] data, int faceCount, int order);
	private native void init(int device);
	protected native void finalize();

	private static float innerproduct(float[] feat1, float[] feat2)
	{
		float output = 0.0f;
		if (feat1.length != feat2.length)
			return Float.MIN_VALUE;
		for (int i = 0; i < feat1.length; i++)
		{
			output += feat1[i] * feat2[i];
		}
		return output;
	}

	public static float CosineDistanceProb(float[] feat1, float[] feat2)
	{
		double output = 0.0f;
		if (feat1.length != feat2.length)
			return Float.MIN_VALUE;
		output = innerproduct(feat1, feat2)
				/ Math.sqrt(innerproduct(feat1, feat1) * innerproduct(feat2, feat2));
		return (float)output;
	}
}