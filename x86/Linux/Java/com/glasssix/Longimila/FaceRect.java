package com.glasssix.Longimila;

public class FaceRect {
	public int x;
	public int y;
	public int width;
	public int height;
	public int neighbors;
	public double confidence;
	
	public FaceRect() {
		x = 0;
		y = 0;
		width = 0;
		height = 0;
		neighbors = 0;
		confidence = 0.0;
	}
	
	public FaceRect(int x, int y, int width, int height, int neighbors, double confidence) {
		this.x = x;
		this.y = y;
		this.width = width;
		this.height = height;
		this.neighbors = neighbors;
		this.confidence = confidence;
	}
}