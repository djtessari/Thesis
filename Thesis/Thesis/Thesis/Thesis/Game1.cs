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



        //Stuff used for creating the game grid and resizing all objects
        private int gridUnitSize = 20; //Determines length and width of a 'space' on the grid.
        private int rows;  //num rows and cols in grid
        private int cols;
        private WObject[,] grid; //the actual grid.  Stores information of location of obejcts
        private int numAgents = 20;

        //Determine the framerate
        private SpriteFont font;

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

            rows = SCREEN_HEIGHT / gridUnitSize;
            cols = SCREEN_WIDTH / gridUnitSize;
            grid = new WObject[rows, cols];
            for (int r = 0; r < rows; r++)
            {
                for (int c = 0; c < cols; c++)
                {
                    grid[r, c] = null;
                }
            }

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
            font = Content.Load<SpriteFont>("Font");

            Texture2D agentTexture = Content.Load<Texture2D>("EntityTex/agentTex");
            Texture2D playerTexture = Content.Load<Texture2D>("EntityTex/playerTex");
            Texture2D farmTexture = Content.Load<Texture2D>("EntityTex/farmTex");
            Texture2D emptyTexture = Content.Load<Texture2D>("EntityTex/emptyTexture");
            Texture2D homeTexture = Content.Load<Texture2D>("EntityTex/homeTex");

            background = Content.Load<Texture2D>("Background/background");
            player = new Player(playerTexture, new Vector2(400, 200));

            

            /*
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
            objects.Add(home);*/

            //Generates all of the agents, gives them a home, and assigns them property
            for (int i = 0; i < numAgents; i++)
            {
                Agent a = new Agent(agentTexture, new Vector2(0, 0), massLogic, i);

                Boolean done = false;
                while (!done)
                {
                    Random rnd = new Random();
                    int r = rnd.Next(2, rows-4);
                    int c = rnd.Next(2, cols-4);
                    if (grid[r, c] == null)
                    {
                        WObject aHome = new Home(homeTexture, new Vector2(r*gridUnitSize, c*gridUnitSize), i);
                        a.home = aHome;
                        objects.Add(aHome);
                        a.AddProperty(aHome);
                        grid[r, c] = aHome;
                        //int wealth = rnd.Next(0, 3);
                        //Assign ownership
                        for (int x = -1; x < 2; x++)
                            for (int y = -1; y < 2; y++)
                            {
                                if (x != 0 || y != 0)
                                {
                                    int farmChance = rnd.Next(0,101);
                                    if (farmChance < 70)
                                    {
                                        WObject farm = new Farmland(farmTexture, new Vector2((r+y)*gridUnitSize, (c+x)*gridUnitSize), i);
                                        a.AddProperty(farm);
                                        objects.Add(farm);
                                        grid[r + y, c + x] = farm;
                                    }
                                    else
                                    {
                                        WObject emptyProperty = new EmptyProperty(emptyTexture, new Vector2((r + y) * gridUnitSize, (c + x) * gridUnitSize), i);
                                        a.AddProperty(emptyProperty);
                                        objects.Add(emptyProperty);
                                        grid[r + y, c + x] = emptyProperty;
                                    }
                                }
                            }                        
                        done = true;
                        a.position = new Vector2(r * gridUnitSize, c * gridUnitSize);
                        agents.Add(a);
                    }
                }

            }
            


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
            float frameRate = 1 / (float)gameTime.ElapsedGameTime.TotalSeconds;

            spriteBatch.Begin();
            spriteBatch.Draw(background, new Rectangle(0, 0, 800, 600), Color.White);
            spriteBatch.DrawString(font, "FPS: " + frameRate, new Vector2(20, 20), Color.Black);
            
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

        public static void playerAttack( )
        {

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
