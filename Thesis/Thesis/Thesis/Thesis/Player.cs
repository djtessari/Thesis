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

        private bool CDresolved = true;


        public Player(Texture2D spriteSheet, Vector2 startPos): base(spriteSheet, startPos)
        {
        }

        new public void Update(GameTime gameTime)
        {
            //Get input

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
