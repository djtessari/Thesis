using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;



namespace Thesis
{

    /// <summary>
    /// This is the main type for your game
    /// </summary>
    public class Game1 : Microsoft.Xna.Framework.Game
    {
        private int SCREEN_WIDTH = 800;
        private int SCREEN_HEIGHT = 600;

        GraphicsDeviceManager graphics;
        SpriteBatch spriteBatch;
        private List<Agent> agents;
        private List<WObject> objects;
        private Player player;
        private Texture2D background;
        private int massLogic = 1; //0 = basic, 1 = maslow

        public Game1()
        {
            graphics = new GraphicsDeviceManager(this);
            Content.RootDirectory = "Content";
        }

        /// <summary>
        /// Allows the game to perform any initialization it needs to before starting to run.
        /// This is where it can query for any required services and load any non-graphic
        /// related content.  Calling base.Initialize will enumerate through any components
        /// and initialize them as well.
        /// </summary>
        protected override void Initialize()
        {
            // TODO: Add your initialization logic here
            graphics.PreferredBackBufferWidth = SCREEN_WIDTH;
            graphics.PreferredBackBufferHeight = SCREEN_HEIGHT;
            graphics.ApplyChanges();

            base.Initialize();
        }

        /// <summary>
        /// LoadContent will be called once per game and is the place to load
        /// all of your content.
        /// </summary>
        protected override void LoadContent()
        {
            // Create a new SpriteBatch, which can be used to draw textures.
            spriteBatch = new SpriteBatch(GraphicsDevice);
            agents = new List<Agent>();
            objects = new List<WObject>();

            Texture2D agentTexture = Content.Load<Texture2D>("EntityTex/agentTex");
            Texture2D playerTexture = Content.Load<Texture2D>("EntityTex/playerTex");
            Texture2D farmTexture = Content.Load<Texture2D>("EntityTex/farmTex");

            background = Content.Load<Texture2D>("Background/background");
            player = new Player(playerTexture, new Vector2(400, 200));

            


            //objects.Add(new WObject(playerTexture, new Vector2(300,300)));
            objects.Add(new WObject(playerTexture, new Vector2(400, 500)));
            WObject farm1 = new Farmland(farmTexture, new Vector2(50, 200), 1);
            WObject farm2 = new Farmland(farmTexture, new Vector2(150, 200), 1);
            WObject home = new Home(playerTexture, new Vector2(250, 250), 1);
            //a.AddKnowledge(farm);

            Agent a = new Agent(agentTexture, new Vector2(200, 200), massLogic, 1);

            a.AddProperty(farm1);
            a.AddProperty(farm2);
            a.AddProperty(home);

            a.home = home;
            Console.WriteLine("Foodstores Farm1 = " + farm1.util.foodStores);
            Console.WriteLine("Foodstores Farm2 = " + farm2.util.foodStores);
            agents.Add(a);

            objects.Add(farm1);
            objects.Add(farm2);
            objects.Add(home);
            
                
            


            // TODO: use this.Content to load your game content here
        }

        /// <summary>
        /// UnloadContent will be called once per game and is the place to unload
        /// all content.
        /// </summary>
        protected override void UnloadContent()
        {
            // TODO: Unload any non ContentManager content here
        }

        /// <summary>
        /// Allows the game to run logic such as updating the world,
        /// checking for collisions, gathering input, and playing audio.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Update(GameTime gameTime)
        {
            // Allows the game to exit
            if (GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed)
                this.Exit();

            // TODO: Add your update logic here
            player.Update(gameTime);
            for (int i = 0; i < agents.Count; i++)
            {
                agents.ElementAt(i).Update(gameTime);
            }
            for (int i = 0; i < objects.Count; i++)
            {
                objects.ElementAt(i).Update(gameTime);
            }

            for (int i = 0; i < objects.Count; i++)
            {
                //Checks to see if player hit any objects, then checks for if agents have hit anything

                WObject o = objects.ElementAt(i);

                int collide = CollisionMain.RectangleCD(o.getRec(), player.getRec());
                if (collide != 0)
                {
                    if (collide != 0)
                    {
                        if (o.canCollide())
                        {

                            if (collide == 1)
                            {
                                Console.WriteLine("LR Collision");
                                player.resolveLR(o);
                            }
                            else if (collide == 2)
                            {
                                Console.WriteLine("UD Collision");
                                player.resolveUD(o);
                            }
                        }
                    }

                }

                for (int j = 0; j < agents.Count; j++)
                {
                    Agent a = agents.ElementAt(j);

                    collide = CollisionMain.RectangleCD(o.getRec(), a.getRec());
                    if (collide != 0)
                    {
                        if (o.canCollide())
                        {

                            if (collide == 1)
                            {
                                Console.WriteLine("LR Collision");
                                a.resolveLR(o);
                            }
                            else if (collide == 2)
                            {
                                Console.WriteLine("UD Collision");
                                a.resolveUD(o);
                            }
                        }

                    }
                }
              
            }

            base.Update(gameTime);
        }

        /// <summary>
        /// This is called when the game should draw itself.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(Color.CornflowerBlue);

            spriteBatch.Begin();
            spriteBatch.Draw(background, new Rectangle(0, 0, 800, 600), Color.White);
            
            for (int i = 0; i < objects.Count; i++)
            {
                objects.ElementAt(i).Draw(spriteBatch);
            }
            for (int i = 0; i < agents.Count; i++)
            {
                agents.ElementAt(i).Draw(spriteBatch);
            }
            player.Draw(spriteBatch);

            spriteBatch.End();
            // TODO: Add your drawing code here

            base.Draw(gameTime);
        }

        private void resolveCollision(Entity e1, Entity e2)
        {
            if (e1.canCollide() && e2.canCollide())
            {
                if (e1.isStatic())
                {
                }
            }
        }
    }
}
