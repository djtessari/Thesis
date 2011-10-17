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
    class Entity
    {
        public Texture2D sprite { get; set; }
        public Vector2 position { get; set; }
        private bool _canCollide;
        private bool _isStatic;


        public Entity(Texture2D spriteSheet, Vector2 startPos)
        {
            _canCollide = false;
            _isStatic = false;
            sprite = spriteSheet;
            position = startPos;
        }

        public Vector2 getPos()
        {
            return position;
        }

        public void Update(GameTime gameTime)
        {
        }

        public void Draw(SpriteBatch spriteBatch)
        {
            spriteBatch.Draw(sprite, position, Color.White);
        }

        public Rectangle getRec()
        {
            Rectangle r = new Rectangle((int)position.X, (int)position.Y, sprite.Width, sprite.Height);
            return r;
        }

        public bool canCollide()
        {
            return _canCollide;
        }

        public void setCollide(bool b)
        {
            _canCollide = b;
        }

        public void setStatic(bool b)
        {
            _isStatic = b;
        }

        public bool isStatic()
        {
            return _isStatic;
        }
    }
}
