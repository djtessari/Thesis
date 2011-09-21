package org.anddev.andengine.examples;

import org.anddev.andengine.entity.sprite.Sprite;
import org.anddev.andengine.opengl.texture.atlas.bitmap.BitmapTextureAtlas;
import org.anddev.andengine.opengl.texture.region.TextureRegion;
import org.anddev.andengine.opengl.vertex.RectangleVertexBuffer;

public abstract class Enemy extends Sprite {
	// ===========================================================
	// Constants
	// ===========================================================

	// ===========================================================
	// Fields
	// ===========================================================
	
	protected float speed;
	protected int health;
	protected String name;
	protected int typeReturn;
	protected BitmapTextureAtlas mBitmapTextureAtlas;
	
	
	// ===========================================================
	// Constructors
	// ===========================================================

	public Enemy(float pX, float pY, TextureRegion pTextureRegion) {
		super(pX, pY, pTextureRegion);
		typeReturn = 0;
		// TODO Auto-generated constructor stub
	}

	public Enemy(float pX, float pY, float pWidth, float pHeight,
			TextureRegion pTextureRegion) {
		super(pX, pY, pWidth, pHeight, pTextureRegion);
		typeReturn = 0;
		// TODO Auto-generated constructor stub
	}

	public Enemy(float pX, float pY, TextureRegion pTextureRegion,
			RectangleVertexBuffer pRectangleVertexBuffer) {
		super(pX, pY, pTextureRegion, pRectangleVertexBuffer);
		typeReturn = 0;
		// TODO Auto-generated constructor stub
	}

	public Enemy(float pX, float pY, float pWidth, float pHeight,
			TextureRegion pTextureRegion,
			RectangleVertexBuffer pRectangleVertexBuffer) {
		super(pX, pY, pWidth, pHeight, pTextureRegion, pRectangleVertexBuffer);
		typeReturn = 0;
		// TODO Auto-generated constructor stub
	}
	
	// ===========================================================
	// Getter & Setter
	// ===========================================================
	
	public float getSpeed()	{
		return speed;
	}
	
	public void setSpeed(float s) {
		speed = s;
	}
	
	public int getHP()	{
		return health;
	}
	
	public void setHP(int hp) {
		health = hp;
	}
	
	public void takeDamage(int dmg){
		health-=dmg;
	}
	
	public String getName()	{
		return name;
	}
	
	public void setName(String n) {
		name = n;
	}

	// ===========================================================
	// Methods for/from SuperClass/Interfaces
	// ===========================================================
	
	// ===========================================================
	// Methods
	// ===========================================================
	
	/*
	 * This method will contain the movement logic and AI for the enemy.  
	 * It will be called on each update and determines the next move of the enemy.
	 */
	public abstract void move();
	
	//Will return an "Enemy" object
	public Enemy returnEnemy(){
		return null;
	}
	//Will return an "effect" from the enemy
	public Effect returnEffect(){
		return null;
	}
	
	public int hasReturn(){
		/*
		 * This method determines if the enemy has something to return to the main scene, and what followup method to call.
		 * 0 = Nothing to return
		 * 1 = returnEnemy, will only affect player + player abilities
		 * 2 = returnEffect, will only affect enemies
		 */		
		return typeReturn;		
	}
	
	public boolean isDead(){
		if (health <= 0){
			return true;
		}
		return false;
	}
	

	


	

	// ===========================================================
	// Inner and Anonymous Classes
	// ===========================================================

}
