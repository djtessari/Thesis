package org.anddev.andengine.examples;

import java.io.IOException;
import org.anddev.andengine.audio.music.Music;
import org.anddev.andengine.audio.music.MusicFactory;
import org.anddev.andengine.engine.Engine;
import org.anddev.andengine.engine.camera.Camera;
import org.anddev.andengine.engine.handler.IUpdateHandler;
import org.anddev.andengine.engine.options.EngineOptions;
import org.anddev.andengine.engine.options.EngineOptions.ScreenOrientation;
import org.anddev.andengine.engine.options.resolutionpolicy.RatioResolutionPolicy;
import org.anddev.andengine.entity.scene.CameraScene;
import org.anddev.andengine.entity.scene.Scene;
import org.anddev.andengine.entity.scene.Scene.IOnSceneTouchListener;
import org.anddev.andengine.entity.sprite.Sprite;
import org.anddev.andengine.entity.util.FPSLogger;
import org.anddev.andengine.input.touch.TouchEvent;
import org.anddev.andengine.opengl.texture.TextureOptions;
import org.anddev.andengine.opengl.texture.atlas.bitmap.BitmapTextureAtlas;
import org.anddev.andengine.opengl.texture.atlas.bitmap.BitmapTextureAtlasTextureRegionFactory;
import org.anddev.andengine.opengl.texture.region.TextureRegion;
import org.anddev.andengine.ui.activity.BaseGameActivity;
import org.anddev.andengine.util.Debug;
import org.anddev.andengine.entity.scene.background.AutoParallaxBackground;
import org.anddev.andengine.entity.scene.background.ParallaxBackground.ParallaxEntity;


import android.view.KeyEvent;

public class ProjectActivity extends BaseGameActivity {
 
        private static final int CAMERA_WIDTH = 720;
        private static final int CAMERA_HEIGHT = 480;
 
        private Camera mCamera;
        private BitmapTextureAtlas mBitmapTextureAtlas;
        private TextureRegion mEnemyTextureRegion;
        private TextureRegion mFireTextureRegion;
        private TextureRegion mEndRegion;
        private TextureRegion mPausedRegion;
        private Scene mMainScene;
        private CameraScene mEndScene;
    	private CameraScene mPauseScene;
    	private Music mBackgroundMusic;
    	private BitmapTextureAtlas mAutoParallaxBackgroundTexture;
    	private TextureRegion mParallaxLayerBack;
    	private TextureRegion mParallaxLayerMid;
    	private TextureRegion mParallaxLayerFront;
    	
        private boolean fireExists;
        private boolean enemyExists;

        @Override
        public Engine onLoadEngine() {
                this.mCamera = new Camera(0, 0, CAMERA_WIDTH, CAMERA_HEIGHT);
                return new Engine(new EngineOptions(true, ScreenOrientation.LANDSCAPE, 
                		new RatioResolutionPolicy(CAMERA_WIDTH, CAMERA_HEIGHT), this.mCamera).setNeedsMusic(true));
        
        }
        
        @Override
        public void onLoadResources() {
        	this.mBitmapTextureAtlas = new BitmapTextureAtlas(256, 256, TextureOptions.BILINEAR_PREMULTIPLYALPHA);
            BitmapTextureAtlasTextureRegionFactory.setAssetBasePath("gfx/");
    		this.mEnemyTextureRegion = BitmapTextureAtlasTextureRegionFactory.createFromAsset(this.mBitmapTextureAtlas, this, "face_box.png", 0, 0);
            this.mFireTextureRegion = BitmapTextureAtlasTextureRegionFactory.createFromAsset(this.mBitmapTextureAtlas, this, "fire.png", 0, 128);
            this.mEndRegion = BitmapTextureAtlasTextureRegionFactory.createFromAsset(this.mBitmapTextureAtlas, this, "game_over.png", 40, 0);
    		this.mPausedRegion = BitmapTextureAtlasTextureRegionFactory.createFromAsset(this.mBitmapTextureAtlas, this, "game_paused.png", 40, 0);
    		
    		this.mAutoParallaxBackgroundTexture = new BitmapTextureAtlas(1024, 1024, TextureOptions.DEFAULT);
    		this.mParallaxLayerFront = BitmapTextureAtlasTextureRegionFactory.createFromAsset(this.mAutoParallaxBackgroundTexture, this, "parallax_background_layer_front.png", 0, 0);
    		this.mParallaxLayerBack = BitmapTextureAtlasTextureRegionFactory.createFromAsset(this.mAutoParallaxBackgroundTexture, this, "parallax_background_layer_back.png", 0, 188);
    		this.mParallaxLayerMid = BitmapTextureAtlasTextureRegionFactory.createFromAsset(this.mAutoParallaxBackgroundTexture, this, "parallax_background_layer_mid.png", 0, 669);
    		this.mEngine.getTextureManager().loadTextures(this.mBitmapTextureAtlas, this.mAutoParallaxBackgroundTexture);
    		
            fireExists = false;
            enemyExists = true;

    		MusicFactory.setAssetBasePath("sound/");
    		try {
    			this.mBackgroundMusic = MusicFactory.createMusicFromAsset(this.mEngine.getMusicManager(), this, "Background.mp3");
    			this.mBackgroundMusic.setLooping(true);
    		} catch (final IOException e) {
    			Debug.e(e);
    		}
        }
 
        @Override
        public Scene onLoadScene() {
        	
    		this.mEngine.registerUpdateHandler(new FPSLogger());

    		mMainScene = new Scene();
    		final AutoParallaxBackground autoParallaxBackground = new AutoParallaxBackground(0, 0, 0, 5);
    		autoParallaxBackground.attachParallaxEntity(new ParallaxEntity(0.0f, new Sprite(0, CAMERA_HEIGHT - this.mParallaxLayerBack.getHeight(), this.mParallaxLayerBack)));
    		autoParallaxBackground.attachParallaxEntity(new ParallaxEntity(-5.0f, new Sprite(0, 80, this.mParallaxLayerMid)));
    		autoParallaxBackground.attachParallaxEntity(new ParallaxEntity(-10.0f, new Sprite(0, CAMERA_HEIGHT - this.mParallaxLayerFront.getHeight(), this.mParallaxLayerFront)));
    		mMainScene.setBackground(autoParallaxBackground);

    		final int EndX = CAMERA_WIDTH / 2 - this.mEndRegion.getWidth() / 2;
    		final Sprite EndSprite = new Sprite(EndX, EndX, this.mEndRegion);
    		final Sprite pausedSprite = new Sprite(EndX, EndX, this.mPausedRegion);
    		
    		this.mEndScene = new CameraScene(this.mCamera);
    		this.mEndScene.attachChild(EndSprite);
    		this.mEndScene.setBackgroundEnabled(false);
    		
    		this.mPauseScene = new CameraScene(this.mCamera);
    		this.mPauseScene.attachChild(pausedSprite);
    		this.mPauseScene.setBackgroundEnabled(false);
    		
    		this.mBackgroundMusic.play();
    		
            final Sprite enemy = new Sprite(CAMERA_WIDTH + 20, 100, this.mEnemyTextureRegion);
            final Sprite fire = new Sprite(CAMERA_WIDTH + 50, CAMERA_HEIGHT + 50, this.mFireTextureRegion);
           
            mMainScene.attachChild(fire);
            mMainScene.attachChild(enemy);

            mMainScene.setOnSceneTouchListener(new IOnSceneTouchListener() {
    			@Override
    			public boolean onSceneTouchEvent(final Scene pScene, final TouchEvent pSceneTouchEvent) {
    					fire.setPosition(pSceneTouchEvent.getX(), pSceneTouchEvent.getY());
    					fireExists = true;
    				return true;
    			}
    		});
    		
    		this.mEngine.registerUpdateHandler(new IUpdateHandler(){

				@Override
					public void onUpdate(float pSecondsElapsed) {
						if (enemyExists){						
							if (fireExists){
								if (fire.collidesWith(enemy)){
									enemy.setPosition(enemy.getX() + 500, (int)(Math.random() * CAMERA_HEIGHT ));		
									fire.setPosition(fire.getX(), CAMERA_HEIGHT + 100);
								}
								if (fire.getX() > CAMERA_WIDTH || fire.getY() > CAMERA_HEIGHT){
									fireExists = false;
								}
								else {
									fire.setPosition(fire.getX() + 10, fire.getY());
								}
							}
							
							enemy.setPosition(enemy.getX() - 5, enemy.getY());				
							if (enemy.getX() < 0){
								enemyExists = false;
							}
						}
					if (!enemyExists){
						mMainScene.clearChildScene();
						mMainScene.setChildScene(mEndScene, false, true, true);
						mEngine.stop();
					}
					
				}

				@Override
				public void reset() {
					// TODO Auto-generated method stub
					
				}
        	
        	});
            return mMainScene;
        }
 
        @Override
        public void onLoadComplete() {
 
        }
        
    	public boolean onKeyDown(final int pKeyCode, final KeyEvent pEvent) {
    		if(pKeyCode == KeyEvent.KEYCODE_P && pEvent.getAction() == KeyEvent.ACTION_DOWN) {
    			if(this.mEngine.isRunning()) {
    				this.mMainScene.setChildScene(this.mPauseScene, false, true, true);
    				this.mEngine.stop();
    			} else {
    				this.mMainScene.clearChildScene();
    				this.mEngine.start();
    			}
    			return true;
    		} 
    		else if(pKeyCode == KeyEvent.KEYCODE_E && pEvent.getAction() == KeyEvent.ACTION_DOWN) {
    			    this.mMainScene.setChildScene(this.mEndScene, false, true, true);
				    this.mEngine.stop();
    			    return true;
    		}
    		else {
    			return super.onKeyDown(pKeyCode, pEvent);
    		}
    	}
}