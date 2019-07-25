package com.glasssix.Irisvika;

public class Irisvika {
	static {
		System.loadLibrary("Irisvika");
	}
	
	private long mObject;
	
	public Irisvika(float[][] baseData) {
		initwithData(baseData);
	}
	
	public Irisvika(int dimension) {
		init(dimension);
	}
	
	public static native String getVersion();
	public native int buildGraph();
	public native int buildGraphwithData(float[][] baseData);
	public native void saveGraph(String graphPath);
	public native void saveGraphwithData(String graphPath, String baseDataPath);
	public native float[][] getBaseData();
	public native void loadGraph(String graphPath);
	public native void loadGraphwithData(String graphPath, String basedataPath);
	public native void optimizeGraph();
	public native void searchVector(float[][] queryData, int topK, int[][] returnIDs, float[][] returnSimilarities);
	public native void saveResult(String resultPath, int[][] returnIDs);
	private native void initwithData(float[][] baseData);
	private native void init(int dimension);
	protected native void finalize();
}