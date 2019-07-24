package com.glasssix.Longimila;

public class FaceRectwithFaceInfo extends FaceRect {
	public Point[] pts = new Point[5];
	public float yaw;
	public float pitch;
	public float roll;
	
	public FaceRectwithFaceInfo() {
		yaw = 0.0f;
		pitch = 0.0f;
		roll = 0.0f;
	}
	
	public FaceRectwithFaceInfo(FaceRect rect) {
		super.x = rect.x;
		super.y = rect.y;
		super.width = rect.width;
		super.height = rect.height;
		super.neighbors = rect.neighbors;
		super.confidence = rect.confidence;
		yaw = 0.0f;
		pitch = 0.0f;
		roll = 0.0f;
	}
}