package org.anddev.andengine.examples;

import org.anddev.andengine.entity.sprite.Sprite;
import org.anddev.andengine.opengl.texture.region.TextureRegion;
import org.anddev.andengine.opengl.vertex.RectangleVertexBuffer;

public class Jumper extends Enemy {
	// ===========================================================
	// Constants
	// ===========================================================
	private static final float SPEED = 20;
	private static final int HEALTH = 10;
	private static final String NAME = "Jumper";
	// ===========================================================
	// Fields
	// ===========================================================
	
	// ===========================================================
	// Constructors
	// ===========================================================

	public Jumper(float pX, float pY, TextureRegion pTextureRegion) {
		super(pX, pY, pTextureRegion);
		speed = SPEED;
		health = HEALTH;
		name = NAME;
		// TODO Auto-generated constructor stub
	}

	public Jumper(float pX, float pY, float pWidth, float pHeight,
			TextureRegion pTextureRegion) {
		super(pX, pY, pWidth, pHeight, pTextureRegion);
		speed = SPEED;
		health = HEALTH;
		name = NAME;
		// TODO Auto-generated constructor stub
	}

	public Jumper(float pX, float pY, TextureRegion pTextureRegion,
			RectangleVertexBuffer pRectangleVertexBuffer) {
		super(pX, pY, pTextureRegion, pRectangleVertexBuffer);
		speed = SPEED;
		health = HEALTH;
		name = NAME;
		// TODO Auto-generated constructor stub
	}

	public Jumper(float pX, float pY, float pWidth, float pHeight,
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
		//Travels forward, will only "jump" when hit
		
		this.setPosition(this.getX() - speed, this.getY());
	}
	
	@Override
	public void takeDamage(int dmg){
		//When hit, if it does not die, this enemy will "jump" forward.
		//The intended strategy is to take these out with one hit of a stronger spell, to prevent them from reaching the end.
		
		super.takeDamage(dmg);
		if (!isDead()){
			this.setPosition(getX() - 100, getY());
		}
	}

}