using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;

namespace Thesis
{
    class Player: Entity
    {
        private const int COOLDOWN = 1500;
        public float speed = 5.0f;
        public int facing = 0;
        private bool CDresolved = true;
        private bool attackReady = true;
        private bool helpReady = true;
        private int attackCD = 0;
        private int helpCD = 0;


        public Player(Texture2D spriteSheet, Vector2 startPos): base(spriteSheet, startPos)
        {
        }

        new public void Update(GameTime gameTime)
        {
            //Get input
            KeyboardState keyState = Keyboard.GetState();
            
            //Move Commands
            if (keyState.IsKeyDown(Keys.Down))
            {
                newPos(position.X, position.Y + speed);
                facing = 0;
            }
            if (keyState.IsKeyDown(Keys.Up))
            {
                newPos(position.X, position.Y - speed);
                facing = 1;
            }
            if (keyState.IsKeyDown(Keys.Right))
            {
                newPos(position.X + speed, position.Y);
                facing = 2;
            }
            if (keyState.IsKeyDown(Keys.Left))
            {
                newPos(position.X - speed, position.Y);
                facing = 3;
            }

            if (attackCD <= 0)
            {
                attackCD = 0;
                attackReady = true;
            }
            else
            {
                attackCD -= gameTime.ElapsedGameTime.Milliseconds;
            }

            if (helpCD <= 0)
            {
                helpCD = 0;
                helpReady = true;
            }
            else
            {
                helpCD -= gameTime.ElapsedGameTime.Milliseconds;
            }

            //Attack Commands
            if (attackReady && keyState.IsKeyDown(Keys.A))
            {
                attack();
                attackReady = false;
            }
            //Help Commands
            if (helpReady && keyState.IsKeyDown(Keys.D))
            {
                help();
                helpReady = false;
            }
        }

        public void resolveLR(WObject wobject)
        {
            CDresolved = false;
            if (position.Y > wobject.getPos().Y)  //vertical position reset to under object
            {
                newPos(position.X, wobject.getPos().Y + wobject.sprite.Height);
            }
            else  //vertical position reset to above object
            {
                newPos(position.X, wobject.getPos().Y - sprite.Height);
            }      

        }
        public void resolveUD(WObject wobject)
        {
            if (position.X > wobject.getPos().X)  //horizontal position reset to right of object
            {
                newPos(wobject.getPos().X + wobject.sprite.Width, position.Y);
            }
            else  //horizontal position reset to left of object
            {
                newPos(wobject.getPos().X - sprite.Width, position.Y);
            }            
        }

        public void attack()
        {

        }
        public void help()
        {

        }

        private void newPos(int x, int y)
        {
            position = new Vector2(x, y);
        }
        private void newPos(float x, float y)
        {
            position = new Vector2(x, y);
        }

    }
}
