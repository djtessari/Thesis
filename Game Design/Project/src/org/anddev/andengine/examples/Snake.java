package org.anddev.andengine.examples;

import org.anddev.andengine.entity.sprite.Sprite;
import org.anddev.andengine.opengl.texture.region.TextureRegion;
import org.anddev.andengine.opengl.vertex.RectangleVertexBuffer;

public class Snake extends Enemy {
	// ===========================================================
	// Constants
	// ===========================================================
	private static final float SPEED = 10;
	private static final int HEALTH = 5;
	private static final String NAME = "Snake";
	// ===========================================================
	// Fields
	// ===========================================================
	
	// ===========================================================
	// Constructors
	// ===========================================================

	public Snake(float pX, float pY, TextureRegion pTextureRegion) {
		super(pX, pY, pTextureRegion);
		speed = SPEED;
		health = HEALTH;
		name = NAME;
		// TODO Auto-generated constructor stub
	}

	public Snake(float pX, float pY, float pWidth, float pHeight,
			TextureRegion pTextureRegion) {
		super(pX, pY, pWidth, pHeight, pTextureRegion);
		speed = SPEED;
		health = HEALTH;
		name = NAME;
		// TODO Auto-generated constructor stub
	}

	public Snake(float pX, float pY, TextureRegion pTextureRegion,
			RectangleVertexBuffer pRectangleVertexBuffer) {
		super(pX, pY, pTextureRegion, pRectangleVertexBuffer);
		speed = SPEED;
		health = HEALTH;
		name = NAME;
		// TODO Auto-generated constructor stub
	}

	public Snake(float pX, float pY, float pWidth, float pHeight,
			TextureRegion pTextureRegion,
			RectangleVertexBuffer pRectangleVertexBuffer) {
		super(pX, pY, pWidth, pHeight, pTextureRegion, pRectangleVertexBuffer);
		speed = SPEED;
		health = HEALTH;
		name = NAME;
		// TODO Auto-generated constructor stub
	}

	@Override
	public void move() {
		//Move up and down as it travels forward
		
		//TO IMPLEMENT
	}
	
}
